#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>

typedef struct barrier
{
  /* Zugriff auf Barriere via Mutex serialisieren */
  pthread_mutex_t mutex;
  /* Zustandsänderungen über Bedingungsvariable anzeigen */
  pthread_cond_t cv;
  /* Schwellwert für wartende Threads (Soll-Stand) */
  int threshold;
  /* Anzahl aktuell wartender Threads (Ist-Stand) */
  int counter;
  /* Die eigentliche Wartebedingung */
  unsigned long cycle;
} barrier_t;

#define BARRIER_SERIAL_THREAD -2

int barrier_init( barrier_t *barrier, unsigned count );
int barrier_destroy( barrier_t *barrier );
int barrier_wait( barrier_t *barrier );

#endif
