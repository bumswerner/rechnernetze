#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <syslog.h>
#include <unistd.h>

#include "server.h"

int daemon_exit = 0;

void sig_handler( int sig )
{
  daemon_exit = 1;
  return;
}

int main( int argc, char *argv[] )
{
  int sd, client;
  socklen_t slen;
  struct sockaddr_storage sa;
  struct sigaction action;

  /* horchenden Socket öffnen (passive open) */
  if( ( sd = tcp_listen( NULL, SRVPORT, BACKLOG ) ) < 0 )
    exit( EXIT_FAILURE );

  /* Signalbehandlungsroutine für SIGTERM installieren */
  action.sa_handler = sig_handler;
  sigemptyset( &action.sa_mask );
  action.sa_flags = 0;

  if( sigaction( SIGTERM, &action, NULL ) < 0 )
  {
    fprintf( stderr, "sigaction() failed: %s",
      strerror( errno ) );
    close( sd ); /* passiven Socket schließen */
    exit( EXIT_FAILURE );
  }

  /* Prozeß in einen Daemon umwandeln */
  daemon_init( argv[0], PIDFILE, LOG_DAEMON );

  init_srv_stats(); /* CPU-Statistik initialisieren */

  /*
   * In einer Endlosschleife verarbeitet der Server nun die
   * eingehenden Clientverbindungen. Da es sich um ein
   * Beispiel für einen inkrementellen Server handelt,
   * erfolgt die Bearbeitung strikt sequentiell.
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

      /* accept() wurde nicht durch SIGTERM unterbrochen */
      syslog( LOG_ERR, "accept() failed: %s",
        strerror( errno ) );

      /* Trotz Fehler brechen wir nicht ab! */
      continue;
    }

    /* Clientverbindung sequentiell behandeln */
    handle_client( client );

    /* Socketdeskriptor schließen, Verbindung beenden */
    close( client );
  }

  /* Falls die Schleife durch SIGTERM beendet wurde */
  print_srv_stats(); /* CPU-Statistik ausgeben */

  unlink( PIDFILE ); /* PID-Datei entfernen */
  exit( EXIT_SUCCESS ); /* Daemon beenden */
}
