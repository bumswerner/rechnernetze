#include <errno.h>
#include <unistd.h>

ssize_t readn( int fildes, void *buf, size_t nbyte )
{
  size_t n;
  ssize_t br;
  char *ptr = buf;

  for( n = nbyte; n > 0; n -= br, ptr += br )
  {
    if( ( br = read( fildes, ptr, n ) ) < 0 )
    {
      if( errno == EINTR ) /* Unterbrechung */
        br = 0;
      else
        return( -1 ); /* Fehler */
    }
    else if( br == 0 ) /* EOF */
      return( nbyte - n );
  }

  return( nbyte );
}
