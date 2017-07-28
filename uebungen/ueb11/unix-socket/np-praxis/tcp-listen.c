#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

int tcp_listen( const char *nodename,
  const char *servname, int backlog )
{
  int sd, reuseaddr, status;
  struct addrinfo hints, *ai, *aptr;

  /* Initialisierung der Hints-Adreﬂstruktur */
  memset( &hints, 0, sizeof( hints ) ); /* alles auf Null */
  hints.ai_flags = AI_PASSIVE; /* passives ÷ffnen */
  hints.ai_family = AF_UNSPEC; /* IPv4 oder IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* TCP-Socket */

  /* Adreﬂstruktur(en) f¸r passiven Socket ermitteln */
  if( ( status = getaddrinfo( nodename, servname, &hints,
      &ai ) ) == 0 )
  {
    for( aptr = ai; aptr != NULL; aptr = aptr->ai_next )
    {
      if( ( sd = socket( aptr->ai_family,
          aptr->ai_socktype, aptr->ai_protocol ) ) < 0 )
        continue; /* Im Fehlerfall: n‰chste Adreﬂstruktur */

      /* "address already in use" soweit mˆglich umgehen */
      reuseaddr = 1;
      setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
        sizeof( int ) );

      /* Socket an Socket-Adresse binden und ... */
      if( bind( sd, aptr->ai_addr,
          aptr->ai_addrlen ) == 0 )
        /* aktiven Socket in passiven Socket umwandeln */
        if( listen( sd, backlog ) >= 0 )
          /* Wenn alles geklappt hat: Schleife beenden */
          break;

      /* Im Fehlerfall: Socket schlieﬂen ... */
      close( sd );
    }

    /* Ergebnisliste wieder freigeben */
    freeaddrinfo( ai );

    /*
     * Wurde die Liste der Adreﬂstrukturen erfolglos
     * verarbeitet, gilt aptr == NULL und errno zeigt den
     * Fehler des letzten Aufrufs von socket(), bind() oder
     * listen() an.
     */
    
    if( aptr == NULL )
    {
      fprintf( stderr, "Can't listen on port %s: %s\n",
        servname, strerror( errno ) );
      return( -1 );
    }
  }
  else
  {
    fprintf( stderr, "getaddrinfo() failed: %s\n",
      gai_strerror( status ) );
    return( -1 );
  }

  return( sd );
}
