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

int daemon_exit = 0;

void sig_handler( int sig )
{
  pid_t pid;

  switch( sig )
  {
    case SIGTERM:
      daemon_exit = 1;
      break;
    case SIGCHLD:
      while( ( pid = waitpid( -1, NULL, WNOHANG ) ) > 0 )
        ; /* leere Schleife, nur Statuswerte entsorgen */
      break;
    default:
      break;
  }
  return;
}

void accept_handler( int sd )
{
  int client, pid;
  socklen_t slen;
  struct sockaddr_storage sa;

  /*
   * In einer Endlosschleife verarbeiten der Server nun die
   * eingehenden Clientverbindungen. Da es sich um ein
   * Beispiel f�r einen nebenl�ufigen Server mit Prozessen
   * handelt, wird f�r jede Clientverbindung ein neuer
   * Proze� erzeugt.
   */
  
  for(;;)
  {
    slen = sizeof( sa );

    /* Neue Socketverbindung annehmen */
    if( ( client = accept( sd, (struct sockaddr *)&sa,
        &slen ) ) < 0 )
    {
      if( daemon_exit ) /* Falls ein SIGTERM kam: Ende */
        break;
      if( errno != EINTR )
      {
        /* accept() wurde durch kein Signal unterbrochen */
        syslog( LOG_ERR, "accept() failed: %s",
          strerror( errno ) );
        /* Trotz Fehler brechen wir nicht ab! */
      }
      continue;
    }

    switch( pid = fork() )
    {
      case -1: /* Fehler */
        syslog( LOG_ERR, "fork() failed: %s",
          strerror( errno ) );
        /* Trotz Fehler brechen wir nicht ab! */
        break;
      case 0: /* Kindproze� �bernimmt Clientverbindung */
        close( sd ); /* passiven Socket schlie�en */
        handle_client( client ); /* Client behandeln */
        close( client ); /* Clientverbindung schlie�en */
        exit( EXIT_SUCCESS ); /* Kindproze� beenden */
        break;
      default: /* Elternproze�: weiter mit accept() */
        break;
    }

    /* Elternproze� schlie�t die Clientverbindung */
    close( client );
  }
}

int main( int argc, char *argv[] )
{
  int sd;
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

  accept_handler( sd ); /* Accept-Handler aufrufen */

  /* Falls die Schleife durch SIGTERM beendet wurde */
  print_srv_stats(); /* CPU-Statistik ausgeben */

  unlink( PIDFILE ); /* PID-Datei entfernen */
  exit( EXIT_SUCCESS ); /* Daemon beenden */
}
