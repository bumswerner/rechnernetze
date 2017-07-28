#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
  printf( "Prozeﬂ-ID (PID) = %d\n", getpid() );
  printf( "Elternprozeﬂ-ID (PPID) = %d\n", getppid() );
  printf( "User-ID (UID) = %d\n", getuid() );
  printf( "effektive User-ID (EUID) = %d\n", geteuid() );
  printf( "Group-ID (GID) = %d\n", getgid() );
  printf( "effektive Group-ID (EGID) = %d\n", getegid() );

  exit( EXIT_SUCCESS );
}
