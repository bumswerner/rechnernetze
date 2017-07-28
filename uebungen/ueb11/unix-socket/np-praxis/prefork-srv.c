#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <syslog.h>
#include <unistd.h>

#include "server.h"

int daemon_exit = 0, child[NUM_PROCS];

void sig_handler( int sig )
{
  pid_t pid;
  int i;

  switch( sig )
  {
    case SIGTERM:
      daemon_exit = 1;
      break;
    case SIGCHLD:
      while( ( pid = waitpid( -1, NULL, WNOHANG ) ) > 0 )
        for( i = 0; i < NUM_PROCS; i++ )
          if( pid == child[i] )
            child[i] = 0; /* Proze�-ID austragen */
      break;
    default:
      break;
  }
  return;
}

void accept_handler( int sd )
{
  int client;
  socklen_t slen;
  struct sockaddr_storage sa;

  for(;;)
  {
    slen = sizeof( sa );

    /* Neue Socketverbindung annehmen */
    if( ( client = accept( sd, (struct sockaddr *)&sa,
        &slen ) ) < 0 )
    {
      if( daemon_exit ) /* Falls ein SIGTERM kam: Ende */
        break;

      /* accept() wurde nicht durch SIGTERM unterbrochen */
      syslog( LOG_ERR, "accept() failed: %s",
        strerror( errno ) );

      /* Trotz Fehler brechen wir nicht ab! */
      continue;
    }

    /* Clientverbindung behandeln */
    handle_client( client );

    /* Socketdeskriptor schlie�en, Verbindung beenden */
    close( client );
  }

  return;
}

int main( int argc, char *argv[] )
{
  int i, sd;
  struct sigaction action;

  /* horchenden Socket �ffnen (passive open) */
  if( ( sd = tcp_listen( NULL, SRVPORT, BACKLOG ) ) < 0 )
    exit( EXIT_FAILURE );

  /* Signalbehandlung f�r SIGTERM u. SIGCHLD installieren */
  action.sa_handler = sig_handler;
  sigemptyset( &action.sa_mask );
  action.sa_flags = 0;

  if( sigaction( SIGTERM, &action, NULL ) < 0 )
  {
    fprintf( stderr, "sigaction(SIGTERM) failed: %s",
      strerror( errno ) );
    close( sd ); /* passiven Socket schlie�en */
    exit( EXIT_FAILURE );
  }

  if( sigaction( SIGCHLD, &action, NULL ) < 0 )
  {
    fprintf( stderr, "sigaction(SIGCHLD) failed: %s",
      strerror( errno ) );
    close( sd ); /* passiven Socket schlie�en */
    exit( EXIT_FAILURE );
  }

  /* Proze� in einen Daemon umwandeln */
  daemon_init( argv[0], PIDFILE, LOG_DAEMON );

  init_srv_stats(); /* CPU-Statistik initialisieren */

  /*
   * Da es sich um ein Beispiel f�r einen nebenl�ufigen
   * Server mit Preforking handelt, wird ein Pool von
   * Prozessen erzeugt, die dann die Clientverbindungen
   * annehmen und behandeln.
   */
  
  for( i = 0; i < NUM_PROCS; i++ )
  {
    switch( child[i] = fork() )
    {
      case -1: /* Fehler */
        syslog( LOG_ERR, "fork() failed: %s",
          strerror( errno ) );
        /* Trotz Fehler brechen wir nicht ab! */
        break;
      case 0: /* Kindproze� �bernimmt Accept-Handling */
        accept_handler( sd ); /* Accept-Handler starten */
        exit( EXIT_SUCCESS ); /* Kindproze� beenden */
        break;
      default: /* Elternproze�: weiter mit accept() */
        break;
    }
  }

  close( sd ); /* passiven Socket schlie�en */

  for(;;)
  {
    pause(); /* Nur noch auf SIGTERM warten */
    if( daemon_exit ) /* Falls ein SIGTERM kam: Ende */
      break;
  }

  /* Alle Kinder beenden und auf deren Ende warten */
  for( i = 0; i < NUM_PROCS; i++ )
    if( child[i] > 0 )
      kill( child[i], SIGTERM );
  while( wait( NULL ) > 0 )
    ;

  print_srv_stats(); /* CPU-Statistik ausgeben */

  unlink( PIDFILE ); /* PID-Datei entfernen */
  exit( EXIT_SUCCESS ); /* Dummy, ... wird nie erreicht */
}
