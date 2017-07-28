#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
  char data[45];
  ssize_t br, bw;

  br = read( STDIN_FILENO, data, sizeof( data ) );
  if( br != sizeof( data ) )
  {
    if( br < 0 )
    {
      printf( "Lesefehler: %s\n", strerror( errno ) );
      exit( EXIT_FAILURE );
    }
    else
      printf( "Konnte nur %d Bytes lesen.\n", br );
  }

  bw = write( STDOUT_FILENO, data, br );
  if( bw != br )
  {
    printf( "Konnte nur %d Bytes schreiben.\n", bw );
    exit( EXIT_FAILURE );
  }

  return( EXIT_SUCCESS );
}
