#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

int user_exists( char *user )
{
  int ok = 0;
  char buffer[8]; /* Achtung! */

  printf( "Startadresse von ok: %x\n"
    "Startadresse von buffer: %x\n", (unsigned int)&ok,
    (unsigned int)buffer );

  strcpy( buffer, user ); /* Achtung! */

  if( getpwnam( buffer ) )
    ok = 1;

  return( ok );
}

int main( int argc, char *argv[] )
{
  if( argc < 2 )
  {
    printf( "Bitte Username eingeben.\n" );
    return( EXIT_FAILURE );
  }

  if( ! user_exists( argv[1] ) ) /* Achtung! */
  {
    printf( "Ungültiger User.\n" );
    return( EXIT_FAILURE );
  }

  printf( "Alles klar. User %s existiert.\n", argv[1] );

  return( EXIT_SUCCESS );
}
