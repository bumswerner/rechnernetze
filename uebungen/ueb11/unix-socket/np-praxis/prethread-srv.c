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

void *accept_handler( void *arg )
{
  int client, sd = (int)arg; /* passiven Socket ermitteln */
  socklen_t slen;
  struct sockaddr_storage sa;

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

    /* Clientverbindung behandeln */
    handle_client( client );

    /* Socketdeskriptor schließen, Verbindung beenden */
    close( client );
  }

  return( NULL ); /* Dummy, ... wird nie erreicht */
}

int main( int argc, char *argv[] )
{
  int i, sd, status;
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

  /*
   * Da es sich um ein Beispiel für einen nebenläufigen
   * Server mit Prethreading handelt, wird ein Pool von
   * Threads erzeugt, die dann die Clientverbindungen
   * annehmen und behandeln.
   */

  for( i = 0; i < NUM_THREADS; i++ )
  {
    /* Neuen Accept-Handler starten (SIGTERM geblockt) */
    status = pthread_create( &tid, NULL, accept_handler,
      (void *)sd ); /* passiven Socket übergeben */
    if( status != 0 )
    {
      syslog( LOG_ERR, "pthread_create() failed: %s\n",
        strerror( status ) );
      close( sd ); /* passiven Socket schließen */
      unlink( PIDFILE ); /* PID-Datei entfernen */
      exit( EXIT_FAILURE );
    }
    pthread_detach( tid );
  }
  
  sigcatcher(); /* Der Hauptthread behandelt die Signale */

  /* Falls der Prozeß durch SIGTERM beendet wird */
  print_srv_stats(); /* CPU-Statistik ausgeben */

  unlink( PIDFILE ); /* PID-Datei entfernen */
  exit( EXIT_SUCCESS ); /* Daemon beenden */
}
