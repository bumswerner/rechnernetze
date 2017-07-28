#include <pthread.h>
#include <errno.h>

#include "barrier.h"

int barrier_init( barrier_t *barrier, unsigned count )
{
  int status;

  barrier->threshold = barrier->counter = count;
  barrier->cycle = 0;

  status = pthread_mutex_init( &barrier->mutex, NULL );
  if( status != 0 )
    return( status );

  status = pthread_cond_init( &barrier->cv, NULL );
  if( status != 0 )
  {
    /* Im Fehlerfall auch den Mutex wieder verwerfen */
    pthread_mutex_destroy( &barrier->mutex );
    return( status );
  }

  return( 0 );
}

int barrier_destroy( barrier_t *barrier )
{
  int status, status2;

  status = pthread_mutex_lock( &barrier->mutex );
  if( status != 0 )
    return( status );

  /* Ist die Barriere gerade aktiv? */
  if( barrier->counter != barrier->threshold )
  {
    pthread_mutex_unlock( &barrier->mutex );
    /* Falls ja, melden wir "BUSY" zurück */
    return( EBUSY );
  }

  status = pthread_mutex_unlock( &barrier->mutex );
  if( status != 0 )
    return( status );

  /* Mutex und Bedingungsvariable verwerfen */
  status = pthread_mutex_destroy( &barrier->mutex );
  status2 = pthread_cond_destroy( &barrier->cv );

  return( status != 0 ? status : status2 );
}

int barrier_wait( barrier_t *barrier )
{
  int status, cycle;

  status = pthread_mutex_lock( &barrier->mutex );
  if( status != 0 )
    return( status );

  cycle = barrier->cycle;

  /* Sind schon genügend Threads eingetroffen? */
  if( --barrier->counter == 0 )
  {
    /* Falls ja, neuer Barrierendurchlauf */
    barrier->cycle++;
    barrier->counter = barrier->threshold;

    status = pthread_cond_broadcast( &barrier->cv );
    if( status == 0 )
      status = BARRIER_SERIAL_THREAD;
  }
  else
  {
    /* Falls nein, auf weitere Threads warten */
    while( cycle == barrier->cycle )
    {
      status = pthread_cond_wait( &barrier->cv,
        &barrier->mutex );
      if( status != 0 )
        break;
    }
  }

  pthread_mutex_unlock( &barrier->mutex );
  return( status );
}
