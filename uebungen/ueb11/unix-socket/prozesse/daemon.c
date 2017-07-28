#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

void daemon_init( const char *program, int facility )
{
  pid_t pid;
  int i, sigs[] = { SIGHUP, SIGINT, SIGQUIT, SIGTSTP,
    SIGTTIN, SIGTTOU };
  struct sigaction action;

  /* Schritt 1: Terminalgenerierte Signale ignorieren */

  action.sa_handler = SIG_IGN;
  sigemptyset( &action.sa_mask );
  action.sa_flags = 0;

  for( i = 0; i < sizeof( sigs ) / sizeof( int ); i++ )
  {
    if( sigaction( sigs[i], &action, NULL ) < 0 )
    {
      fprintf( stderr, "%s: Fehler in sigaction(): %s.\n",
        program, strerror( errno ) );
      exit( EXIT_FAILURE );
    }
  }

  /* Schritt 2: Umwandlung in einen Hintergrundprozeß */

  switch( pid = fork() )
  {
    case -1: /* Fehler */
      fprintf( stderr, "%s: Fehler in fork(): %s.\n",
        program, strerror( errno ) );
      exit( EXIT_FAILURE );
      break;
    case 0: /* Kindprozeß läuft weiter */
      openlog( program, LOG_PID, facility );
      break;
    default: /* Elternprozeß terminiert umgehend */
      exit( EXIT_SUCCESS );
      break;
  }

  /* Schritt 3: Assoziation zum Terminal aufbrechen */

  if( setsid() < 0 )
  {
    syslog( LOG_ERR, "Fehler in setsid(): %s.\n",
      strerror( errno ) );
    exit( EXIT_FAILURE );
  }

  switch( pid = fork() )
  {
    case -1: /* Fehler */
      syslog( LOG_ERR, "Fehler in fork(): %s.\n",
        strerror( errno ) );
      exit( EXIT_FAILURE );
      break;
    case 0: /* Kindprozeß läuft weiter */
      break;
    default: /* Elternprozeß terminiert umgehend */
      exit( EXIT_SUCCESS );
      break;
  }

  /* Schritt 4: Schließen unbenötigter Dateideskriptoren */

  close( STDIN_FILENO );
  close( STDOUT_FILENO );
  close( STDERR_FILENO );

  /* Schritt 5: Arbeitsverzeichnis wechseln */

  chdir( "/" );

  /* Schritt 6: Dateimodusmaske zurücksetzen */

  umask( 0 );
}

int main( int argc, char *argv[] )
{
  daemon_init( argv[0], LOG_DAEMON );

  sleep( 60 ); /* Kunstpause für 'ps jax' */

  return( EXIT_SUCCESS );
}
