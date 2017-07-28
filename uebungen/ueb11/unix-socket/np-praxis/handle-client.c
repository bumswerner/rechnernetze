#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#include "server.h"

void eratosthenes( int num )
{
  int i, j;
  char *np;

  /* Hilfsfeld anlegen und mit 0 initialisieren */
  if( ( np = calloc( num + 1, sizeof( char ) ) ) == NULL )
  {
    syslog( LOG_ERR, "calloc() failed: %s",
      strerror( errno ) );
    return;
  }

  /* Alle Zahlen streichen, die keine Primzahlen sind */
  for( i = 2; i <= num / 2; i++ )
    for( j = 2; j <= num / i; j++ )
      np[i*j] = 1; /* gestrichen, d.h. keine Primzahl */

  /* Berechnung war nur Zeitvertreib, Ergebnis verwerfen */
  free( np );
  return;
}

void handle_client( int client )
{
  int br, bs, num_work, num_bytes;
  void *rl = NULL;
  char req[MAXLINE], *st, *data;

  /* Begrüßung an den Client schicken */
  num_bytes = strlen( HELLO );
  if( writen( client, HELLO, num_bytes ) != num_bytes )
  {
    syslog( LOG_ERR, "writen() failed: %s",
      strerror( errno ) );
    return;
  }
  
  for(;;)
  {
    /* Anfrage des Clients einlesen */
    if( ( br = readline( client, req, MAXLINE, &rl ) ) < 1 )
    {
      /* Bei EOF oder Fehler: Clientbehandlung beenden */
      break;
    }

    num_work = num_bytes = 0;
    if( ( data = strtok_r( req, " ", &st ) ) != NULL )
      num_work = atoi( data );
    if( ( data = strtok_r( NULL, " \r\n", &st ) ) != NULL )
      num_bytes = atoi( data );

    if( ( num_work <= 0 ) || ( num_bytes <= 0 ) )
    {
      syslog( LOG_ERR, "Ungültige oder falsche Parameter" );
      break; /* Bei Parameterfehler: Ende */
    }

    /* Speicherplatz für das Ergebnis anfordern */
    if( ( data = malloc( num_bytes ) ) == NULL )
    {
      syslog( LOG_ERR, "malloc() failed: %s",
        strerror( errno ) );
      break; /* Bei Speichermangel: Ende */
    }

    /* Arbeit ausführen */
    eratosthenes( num_work );

    /* Daten an Client schicken ... */
    bs = writen( client, data, num_bytes );

    /* ... und Speicherplatz wieder freigeben */
    free( data );

    /* Nachgezogene Behandlung von writen()-Fehlern */
    if( bs != num_bytes )
    {
      syslog( LOG_ERR, "writen() failed: %s",
        strerror( errno ) );
      break;
    }
  }

  free( rl );
  return;
}
