#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void show_ids( void )
{
  pid_t my_pid;

  my_pid = getpid();

  printf( "Prozeﬂ %d: PPID = %d\n", my_pid, getppid() );
  printf( "Prozeﬂ %d: UID  = %d\n", my_pid, getuid() );
  printf( "Prozeﬂ %d: EUID = %d\n", my_pid, geteuid() );
  printf( "Prozeﬂ %d: GID  = %d\n", my_pid, getgid() );
  printf( "Prozeﬂ %d: EGID = %d\n", my_pid, getegid() );
}

int main( int argc, char *argv[] )
{
  pid_t pid;

  printf( "Prozeﬂ %d: Starte fork()\n", getpid() );

  switch( pid = fork() )
  {
    case -1: /* Fehler */
      printf( "Prozeﬂ %d: Fehler in fork(): %s.\n",
        getpid(), strerror( errno ) );
      exit( EXIT_FAILURE );
      break;
    case 0: /* Kindprozeﬂ */
      printf( "Prozeﬂ %d: Ich bin der neue Kindprozeﬂ\n",
        getpid() );
      break;
    default: /* Elternprozeﬂ */
      printf( "Prozeﬂ %d: Kindprozeﬂ l‰uft: PID = %d.\n",
        getpid(), pid );
      break;
  }

  sleep( 1 ); /* kurze Kunstpause */

  show_ids();
  exit( EXIT_SUCCESS );
}
