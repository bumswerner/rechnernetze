#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
  char buffer[256];

  while( fgets( buffer, 256, stdin ) )
    printf( "%s", buffer );

  return( EXIT_SUCCESS );
}
