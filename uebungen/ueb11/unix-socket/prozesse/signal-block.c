#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_handler( int sig )
{
  printf( "Abbruchtaste gedrückt.\n" );
}

int main( int argc, char *argv[] )
{
  struct sigaction action;
  sigset_t sigset, oldset;

  action.sa_handler = signal_handler;
  sigemptyset( &action.sa_mask );
  action.sa_flags = 0;

  if( sigaction( SIGINT, &action, NULL ) < 0 )
  {
    printf( "Konnte Handler nicht installieren: %s.\n",
      strerror( errno ) );
    return( EXIT_FAILURE );
  }

  sigemptyset( &sigset );
  sigaddset( &sigset, SIGINT );
  sigprocmask( SIG_BLOCK, &sigset, &oldset );

  printf( "Bitte nicht stören ...\n" );
  sleep( 10 );
  printf( "Danke.\n" );

  sigprocmask( SIG_SETMASK, &oldset, NULL );

  printf( "Drücken Sie jetzt die Abbruchtaste ...\n" );
  sleep( 10 );
  printf( "Ende.\n" );

  exit( EXIT_SUCCESS );
}
