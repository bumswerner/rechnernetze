#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
  int fd;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  char filename[] = "read.data";
  char text[] = "0123\n" "4567\n" "89ab\n" "cdef\n"
    "ghij\n" "klmn\n" "opqr\n" "stuv\n" "wxyz\n";
  ssize_t bw;

  fd = open( filename, O_WRONLY | O_CREAT | O_TRUNC, mode );
  if( fd < 0 )
  {
    printf( "Kann die Datei '%s' nicht öffnen: %s\n",
      filename, strerror( errno ) );
    exit( EXIT_FAILURE );
  }

  bw = write( fd, text, strlen( text ) );
  if( bw != strlen( text ) )
  {
    printf( "Konnte nur %d Bytes schreiben.\n", bw );
    exit( EXIT_FAILURE );
  }

  if( close( fd ) != 0 )
  {
    printf( "Konnte die Datei '%s' nicht schließen: %s\n",
      filename, strerror( errno ) );
    exit( EXIT_FAILURE );
  }

  return( EXIT_SUCCESS );
}
