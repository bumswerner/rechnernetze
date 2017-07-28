#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <syslog.h>
#include <unistd.h>

#include "server.h"

void sigcatcher( void )
{
  int signal;
  sigset_t sigset;

  /* Signalmaske initialisieren */
  sigemptyset( &sigset );
  sigaddset( &sigset, SIGTERM );

  for(;;)
  {
    /* eintreffende Signale synchron annehmen */
    sigwait( &sigset, &signal );
    if( signal == SIGTERM )
      break;
  }

  return;
}

void *worker( void *arg )
{
  int client = (int)arg; /* Socketdeskriptor ermitteln */

  /* Clientverbindung behandeln */
  handle_client( client );

  /* Socketdeskriptor schließen und Thread beenden */
  close( client );
  return( NULL );
}

void *accept_handler( void *arg )
{
  int sd = (int)arg; /* passiven Socket ermitteln */
  socklen_t slen;
  struct sockaddr_storage sa;
  pthread_t tid;
  int client, status;

  /*
   * In einer Endlosschleife verarbeitet der Server die
   * eingehenden Clientverbindungen. Da es sich um ein
   * Beispiel für einen nebenläufigen Server mit Threads
   * handelt, wird für jede Clientverbindung ein neuer
   * Thread erzeugt.
   */
  
  for(;;)
  {
    slen = sizeof( sa );

    /* Neue Socketverbindung annehmen */
    if( ( client = accept( sd, (struct sockaddr *)&sa,
        &slen ) ) < 0 )
    {
      /* Fehler protokollieren */
      syslog( LOG_ERR, "accept() failed: %s",
        strerror( errno ) );

      /* Trotz Fehler brechen wir nicht ab! */
      continue;
    }

    /* Neuen Thread zur Behandlun der Verbindung starten */
    status = pthread_create( &tid, NULL, worker,
      (void *)client ); /* Socketdeskriptor als Argument */
    if( status != 0 )
    {
      syslog( LOG_ERR, "pthread_create() failed: %s\n",
        strerror( status ) );
      close( client );

      /* Trotz Fehler brechen wir nicht ab! */
      continue;
    }
    pthread_detach( tid );
  }

  return( NULL ); /* Dummy, ... wird nie erreicht */
}

int main( int argc, char *argv[] )
{
  int sd, status;
  sigset_t sigset;
  pthread_t tid;

  /* horchenden Socket öffnen (passive open) */
  if( ( sd = tcp_listen( NULL, SRVPORT, BACKLOG ) ) < 0 )
    exit( EXIT_FAILURE );

  /* Signalmaske initialisieren */
  sigemptyset( &sigset );
  sigaddset( &sigset, SIGTERM );

  /* Signalmaske für den main()-Thread setzen  */
  status = pthread_sigmask( SIG_BLOCK, &sigset, NULL );
  if( status != 0 )
  {
    fprintf( stderr, "pthread_sigmask() failed: %s",
      strerror( status ) );
    close( sd ); /* passiven Socket schließen */
    exit( EXIT_FAILURE );
  }

  /* Prozeß in einen Daemon umwandeln */
  daemon_init( argv[0], PIDFILE, LOG_DAEMON );

  init_srv_stats(); /* CPU-Statistik initialisieren */

  /* Accept-Handler starten */
  status = pthread_create( &tid, NULL, accept_handler,
    (void *)sd );
  if( status != 0 )
  {
    syslog( LOG_ERR, "pthread_create(): %s",
      strerror( status ) );
     exit( EXIT_FAILURE );
  }
  pthread_detach( tid );

  sigcatcher(); /* Der Hauptthread behandelt die Signale */

  /* Falls der Prozeß durch SIGTERM beendet wird */
  print_srv_stats(); /* CPU-Statistik ausgeben */

  unlink( PIDFILE ); /* PID-Datei entfernen */
  exit( EXIT_SUCCESS ); /* Daemon beenden */
}
