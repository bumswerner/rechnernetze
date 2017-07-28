#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
  int sig, error;
  sigset_t sigset;

  sigemptyset( &sigset );
  sigaddset( &sigset, SIGINT );
  sigprocmask( SIG_BLOCK, &sigset, NULL );

  printf( "Bitte nicht stören ...\n" );

  error = sigwait( &sigset, &sig );
  if( error != 0 )
  {
    printf( "Fehler: %s.\n", strerror( error ) );
    return( EXIT_FAILURE );
  }

  printf( "Störung durch Signal %d (SIGINT=%d)!\n",
    sig, SIGINT );

  exit( EXIT_SUCCESS );
}
