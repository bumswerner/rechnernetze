#include <errno.h>
#include <unistd.h>

#include "server.h"

#define READCBUF 512

typedef struct
{
  int count;
  char *current;
  char buf[READCBUF];
} readline_t;

ssize_t readcbuf( int fildes, char *buf, readline_t *rl );

ssize_t readline( int fildes, void *buf, size_t nbyte,
  void **help )
{
  size_t n;
  ssize_t br;
  char c, *ptr = buf;
  readline_t *rl = *help;

  /* Beim ersten Aufruf von readline(): Puffer anlegen */
  if( rl == NULL )
  {
    if( ( rl = malloc( sizeof( readline_t ) ) ) == NULL )
      return( -1 );
    rl->count = 0; /* Der Puffer enthält noch keine Daten */
    rl->current = rl->buf; /* Hilfzeiger auf Pufferanfang */
    *help = rl; /* Adresse für Aufrufer hinterlegen */
  }

  for( n = 1; n < nbyte; n++ ) /* max. nbyte-1 Zeichen */
  {
    if( ( br = readcbuf( fildes, &c, rl ) ) < 0 )
      return( -1 ); /* Fehler */

    *ptr++ = c; /* Zeichen im Puffer hinterlegen */

    /* Bei EOF oder Zeilenumbruch: Schleife verlassen */
    if( ( br == 0 ) || ( c == '\n' ) )
      break;
  }

  /* Noch gar nichts gelesen und schon EOF? */
  if( ( br == 0 ) && ( n == 1 ) )
    return( 0 ); /* EOF zurückgeben */

  *ptr = 0; /* Ergebnis mit Nullbyte terminieren ... */
  return( n ); /* ... und Anzahl der Zeichen zurückgeben */
}

ssize_t readcbuf( int fildes, char *buf, readline_t *rl )
{
  while( rl->count < 1 )
  {
    if( ( rl->count = read( fildes, rl->buf,
        sizeof( rl->buf ) ) ) < 0 )
    {
      if( errno == EINTR ) /* Unterbrechung */
        rl->count = 0;
      else
        return( -1 ); /* Fehler */
    }
    else if( rl->count == 0 ) /* EOF */
      return( 0 );

    rl->current = rl->buf;
  }

  *buf = *rl->current++;
  rl->count--;

  return( 1 );
}

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
