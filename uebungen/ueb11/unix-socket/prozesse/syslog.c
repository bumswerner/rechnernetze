#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main( int argc, char *argv[] )
{
  FILE *passwd;

  openlog( "syslogtest", LOG_PID, LOG_LOCAL0 );

  syslog( LOG_DEBUG, "Start von %s mit %d Argument(en).",
    argv[0], argc );

  if( ( passwd = fopen( "/etc/shadow", "r" ) ) == NULL )
  {
    syslog( LOG_ERR, "Öffnen der Datei /etc/shadow: %m" );
    return( EXIT_FAILURE );
  }

  /* wichtige Arbeiten */

  closelog();
  return( EXIT_SUCCESS );
}
