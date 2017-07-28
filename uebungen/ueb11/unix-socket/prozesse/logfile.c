#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
  FILE *log, *passwd;

  if( ( log = fopen( "logfile.log", "a" ) ) == NULL )
    return( EXIT_FAILURE );

  setvbuf( log, NULL, _IONBF, 0 ); /* keine Pufferung */

#ifdef DEBUG
  fprintf( log, "Start von %s mit %d Argument(en).\n",
    argv[0], argc );
#endif

  if( ( passwd = fopen( "/etc/shadow", "r" ) ) == NULL )
  {
    fprintf( log, "Öffnen der Datei /etc/shadow: %s\n",
      strerror( errno ) );
    return( EXIT_FAILURE );
  }

  /* wichtige Arbeiten */

  return( EXIT_SUCCESS );
}
