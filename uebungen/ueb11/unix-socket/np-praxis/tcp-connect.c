#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

int tcp_connect( const char *nodename,
  const char *servname )
{
  int sd, status;
  struct addrinfo hints, *ai, *aptr;

  /* Initialisierung der Hints-Adreßstruktur */
  memset( &hints, 0, sizeof( hints ) ); /* alles auf Null */
  hints.ai_family = AF_UNSPEC; /* IPv4 oder IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* TCP-Socket */

  /* Adreßstruktur(en) für aktiven Socket ermitteln */
  if( ( status = getaddrinfo( nodename, servname, &hints,
      &ai ) ) == 0 )
  {
    for( aptr = ai; aptr != NULL; aptr = aptr->ai_next )
    {
      if( ( sd = socket( aptr->ai_family,
          aptr->ai_socktype, aptr->ai_protocol ) ) < 0 )
        continue; /* Im Fehlerfall: nächste Adreßstruktur */

      /* Socket mit Socketadresse verbinden */
      if( connect( sd, aptr->ai_addr,
          aptr->ai_addrlen ) < 0 )
      {
        /* Im Fehlerfall: nächste Adreßstruktur */
        close( sd );
        continue;
      }

      /* Wenn alles geklappt hat: Schleife beenden */
      break;
    }

    /* Ergebnisliste wieder freigeben */
    freeaddrinfo( ai );

    /*
     * Wurde die Liste der Adreßstrukturen erfolglos
     * verarbeitet, gilt aptr == NULL und errno zeigt den
     * Fehler des letzten Aufrufs von socket() oder
     * connect() an.
     */
    
    if( aptr == NULL )
    {
      fprintf( stderr, "Can't connect to %s, port %s: %s\n",
        nodename, servname, strerror( errno ) );
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
