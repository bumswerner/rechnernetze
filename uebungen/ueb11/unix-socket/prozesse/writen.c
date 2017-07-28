#include <errno.h>
#include <unistd.h>

ssize_t writen( int fildes, const void *buf, size_t nbyte )
{
  size_t n;
  ssize_t bw;
  const char *ptr = buf;

  for( n = nbyte; n > 0; n -= bw, ptr += bw )
  {
    if( ( bw = write( fildes, ptr, n ) ) < 0 )
    {
      if( errno == EINTR ) /* Unterbrechung */
        bw = 0;
      else
        return( -1 ); /* Fehler */
    }
    else if( bw == 0 ) /* Fehler */
      return( nbyte - n );
  }

  return( nbyte );
}
