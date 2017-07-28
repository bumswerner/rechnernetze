#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char *argv[] )
{
  int ret;
  char *env_vector[] = { "DISPLAY=:0", "TERM=xterm", NULL };
  char *arg_vector[] = { "ps", "auxww", NULL };

  printf( "Meine Prozeﬂ-ID (PID) = %d.\n\n", getpid() );

  ret = execl( "/bin/ps", "ps", "-ja", NULL );
  if( ret == -1 )
    printf( "execl(): %s.\n", strerror( errno ) );

  ret = execle( "/bin/ps", "ps", "-e", "-f", NULL,
    env_vector );
  if( ret == -1 )
    printf( "execle(): %s.\n", strerror( errno ) );

  ret = execvp( "ps", arg_vector );
  if( ret == -1 )
    printf( "execvp(): %s.\n", strerror( errno ) );

  exit( EXIT_FAILURE );
}
