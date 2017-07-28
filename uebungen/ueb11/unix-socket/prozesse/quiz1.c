#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_handler( int sig )
{
  switch( sig )
  {
    case SIGINT:
      printf( "Habe Signal SIGINT erhalten ...\n" );
      break;
    case SIGALRM:
      printf( "Habe Signal SIGALRM erhalten ...\n" );
      break;
    default:
      break;
  }
}

int main( int argc, char *argv[] )
{
  char antwort[] = "Himbeerjoghurt\n";
  char eingabe[20];
  struct sigaction action, old_action;

  action.sa_handler = signal_handler;
  sigemptyset( &action.sa_mask );
  action.sa_flags = 0;

  if( sigaction( SIGINT, &action, &old_action ) < 0 )
  {
    printf( "Konnte Handler nicht installieren: %s.\n",
      strerror( errno ) );
    return( EXIT_FAILURE );
  }

  if( sigaction( SIGALRM, &action, &old_action ) < 0 )
  {
    printf( "Konnte Handler nicht installieren: %s.\n",
      strerror( errno ) );
    return( EXIT_FAILURE );
  }

  printf( "Sie haben 20 Sekunden für die Antwort:\n" );
  printf( "Was ißt Sir Quickly am liebsten?\n" );

  alarm( 20 );

  if( fgets( eingabe, sizeof( eingabe ), stdin ) == NULL )
  {
    printf( "Oha: %s ...\n", strerror( errno ) );
    return( EXIT_FAILURE );
  }

  if( strcmp( eingabe, antwort ) == 0 )
    printf( "Die Antwort ist richtig. Gratulation.\n" );
  else
    printf( "Leider falsch, richtig ist: %s", antwort );

  exit( EXIT_SUCCESS );
}
