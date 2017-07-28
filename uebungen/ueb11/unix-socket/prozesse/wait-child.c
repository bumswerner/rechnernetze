#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char *argv[] )
{
  pid_t pid;
  int status;

  printf( "Prozeﬂ %d: Starte fork().\n", getpid() );

  switch( pid = fork() )
  {
    case -1: /* Fehler */
      printf( "Prozeﬂ %d: Fehler in fork(): %s.\n",
        getpid(), strerror( errno ) );
      exit( EXIT_FAILURE );
      break;
    case 0: /* Kindprozeﬂ */
      printf( "Prozeﬂ %d: Ich bin der neue Kindprozeﬂ.\n",
        getpid() );
      sleep( 20 ); /* Brotzeitpause */
      printf( "Prozeﬂ %d: Genug gewartet. Bye-bye.\n",
        getpid() );
      exit( 7 ); /* Willk¸rlicher R¸ckgabewert zum Test */
      break;
    default: /* Elternprozeﬂ */
      printf( "Prozeﬂ %d: Kindprozeﬂ l‰uft: PID = %d.\n",
        getpid(), pid );
      waitpid( pid, &status, 0 );
      printf( "Prozeﬂ %d: Kind hat sich verabschiedet.\n",
        getpid() );
      printf( "Prozeﬂ %d: R¸ckgabewert: %d.\n",
        getpid(), WEXITSTATUS( status ) );
      printf( "Prozeﬂ %d: Kind normal beendet: %s.\n",
        getpid(), WIFEXITED( status ) ? "ja" : "nein" );
      if( WIFSIGNALED( status ) )
        printf( "Prozeﬂ %d: Kind von Signal %d beendet.\n",
          getpid(), WTERMSIG( status ) );
      break;
  }

  exit( EXIT_SUCCESS );
}
