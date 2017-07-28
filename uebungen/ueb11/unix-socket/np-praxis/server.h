#ifndef SERVER_EXAMPLE_H
#define SERVER_EXAMPLE_H

#include <stdlib.h>

/* Allgemeine Definitionen */

#define SRVPORT "12345" /* Port, auf dem der Server h�rt */
#define BACKLOG 32 /* L�nge der Listen-Queue */
#define MAXLINE 512 /* Maximale Zeilenl�nge */
#define PIDFILE "/var/run/testsrv.pid"

#define NUM_PROCS 8 /* Anzahl Prozesse f�r Preforking */
#define NUM_THREADS 8 /* Anzahl Threads f�r Prethreading */

#define HELLO "Sir Quickly sagt Servus!\n"

/* Deklaration der externen Funktionen */

void daemon_init( const char *program, const char *pid_file,
  int facility );

int tcp_connect( const char *nodename,
  const char *servname );
int tcp_listen( const char *nodename,
  const char *servname, int backlog );

ssize_t readline( int fildes, void *buf, size_t nbyte,
  void **help );
ssize_t readn( int fildes, void *buf, size_t nbyte );
ssize_t writen( int fildes, const void *buf, size_t nbyte );

void handle_client( int client );
void init_srv_stats( void );
void print_srv_stats( void );

#endif
