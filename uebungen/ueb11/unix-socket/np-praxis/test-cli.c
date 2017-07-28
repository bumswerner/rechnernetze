#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#include "server.h"
#include "barrier.h"

char *srv_host;
int num_reqs, num_work, num_bytes;
barrier_t barrier;

void *worker( void *arg )
{
  int srv, i, status, tid = (int)arg;
  char req[MAXLINE], hello[MAXLINE], *buffer;
  struct tms acct;
  clock_t *rtime, t;
  void *rl = NULL;

  /* Anfrage an den Server vorbereiten */
  snprintf( req, MAXLINE - 1, "%d %d\n", num_work,
    num_bytes );

  /* Speicherplatz für das Ergebnis anfordern */
  buffer = malloc( num_bytes );

  /* zusätzlicher Speicherplatz für Zeistempel */
  rtime = calloc( num_reqs, sizeof( clock_t ) );

  /* Bei Speichermangel: Programmende */
  if( ( buffer == NULL ) || ( rtime == NULL ) )
  {
      printf( "Thread %02d: malloc() failed.\n", tid );
      exit( EXIT_FAILURE );
  }

  /* Warten, bis alle Threads gestartet wurden */
  status = barrier_wait( &barrier );

  /* Die geforderte Anzahl Anfragen an den Server stellen */
  for( i = 0; i < num_reqs; i++ )
  {
    /* Startzeit für Verbindungsaufbau bestimmen */
    t = times( &acct );

    /* Neue TCP-Verbindung zum Server aufbauen */
    if( ( srv = tcp_connect( srv_host, SRVPORT ) ) < 0 )
    {
      /* Falls der Versuch fehlschlägt, nicht abbrechen */
      printf( "Thread %02d: tcp_connect() failed.\n", tid );
      exit( EXIT_FAILURE );
    }

    /* Begrüßungsformel des Servers einlesen */
    if( readline( srv, hello, MAXLINE, &rl ) < 1 )
    {
      /* Falls der Versuch fehlschlägt, nicht abbrechen */
      printf( "Thread %02d: No server greeting.\n", tid );
      exit( EXIT_FAILURE );
    }

    /* Gesamtzeit für Verbindungsaufbau berechnen */
    rtime[i] = times( &acct ) - t;
    
    /* Anfrage an den Server stellen und ... */
    if( writen( srv, req, strlen( req ) ) != strlen( req ) )
    {
      /* Falls die Kommunikation fehlschlägt, stur weiter */
      printf( "Thread %02d: writen() failed.\n", tid );
      exit( EXIT_FAILURE );
    }

    /* ... Antwort des Servers abwarten */
    if( readn( srv, buffer, num_bytes ) != num_bytes )
    {
      printf( "Thread %02d: readn() failed.\n", tid );
      exit( EXIT_FAILURE );
    }

    /* Readline-Puffer freigeben und Verbindung abbauen */
    free( rl );
    rl = NULL;
    close( srv );
  }

  /* Statistik ausgeben */
  for( i = 0; i < num_reqs;  i++ )
    printf( "Thread %02d: %d Clockticks\n", tid,
      (int)rtime[i] );

  /* Warten, bis alle Threads fertig sind */
  status = barrier_wait( &barrier );

  return( NULL );
}

int main( int argc, char *argv[] )
{
  int num_threads, i, status;
  pthread_t id;

  if( argc != 6 )
  {
    printf( "Usage: %s dest-host num-threads num-reqs "
      "num-work num-bytes\n", argv[0] );
    exit( EXIT_FAILURE );
  }

  srv_host = argv[1];

  if( ( num_threads = atoi( argv[2] ) ) <= 0 )
  {
    printf( "num-threads invalid: %s\n", argv[2] );
    exit( EXIT_FAILURE );
  }

  if( ( num_reqs = atoi( argv[3] ) ) <= 0 )
  {
    printf( "num-reqs invalid: %s\n", argv[3] );
    exit( EXIT_FAILURE );
  }

  if( ( num_work = atoi( argv[4] ) ) <= 0 )
  {
    printf( "num-work invalid: %s\n", argv[4] );
    exit( EXIT_FAILURE );
  }

  if( ( num_bytes = atoi( argv[5] ) ) <= 0 )
  {
    printf( "num-bytes invalid: %s\n", argv[5] );
    exit( EXIT_FAILURE );
  }

  /* Barrier für num_threads initialisieren */
  status = barrier_init( &barrier, num_threads );
  if( status != 0 )
  {
    printf( "barrier_init() failed: %s\n",
      strerror( status ) );
    exit( EXIT_FAILURE );
  }

  /* Threads starten: num_threads - 1 Stück */
  for( i = 1; i < num_threads; i++ )
  {
    status = pthread_create( &id, NULL, worker, (void *)i );
    if( status != 0 )
    {
      printf( "pthread_create() failed: %s\n",
        strerror( status ) );
      exit( EXIT_FAILURE );
    }
    pthread_detach( id );
  }

  /* Der Main-Thread arbeitet selbst mit */
  worker( (void *)0 );

  /* Die Barrier hat ihre Dienst geleistet, weg damit */
  barrier_destroy( &barrier );

  exit( EXIT_SUCCESS );
}
