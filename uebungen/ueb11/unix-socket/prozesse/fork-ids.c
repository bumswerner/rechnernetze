#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void show_ids( void )
{
  pid_t my_pid;

  my_pid = getpid();

  printf( "Proze� %d: PPID = %d\n", my_pid, getppid() );
  printf( "Proze� %d: UID  = %d\n", my_pid, getuid() );
  printf( "Proze� %d: EUID = %d\n", my_pid, geteuid() );
  printf( "Proze� %d: GID  = %d\n", my_pid, getgid() );
  printf( "Proze� %d: EGID = %d\n", my_pid, getegid() );
}

int main( int argc, char *argv[] )
{
  pid_t pid;

  printf( "Proze� %d: Starte fork()\n", getpid() );

  switch( pid = fork() )
  {
    case -1: /* Fehler */
      printf( "Proze� %d: Fehler in fork(): %s.\n",
        getpid(), strerror( errno ) );
      exit( EXIT_FAILURE );
      break;
    case 0: /* Kindproze� */
      printf( "Proze� %d: Ich bin der neue Kindproze�\n",
        getpid() );
      break;
    default: /* Elternproze� */
      printf( "Proze� %d: Kindproze� l�uft: PID = %d.\n",
        getpid(), pid );
      break;
  }

  sleep( 1 ); /* kurze Kunstpause */

  show_ids();
  exit( EXIT_SUCCESS );
}
