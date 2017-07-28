#include <syslog.h>
#include <sys/times.h>

struct tms start_acct;

void init_srv_stats( void )
{
  times( &start_acct ); /* Start-CPU-Zeiten festhalten */
  return;
}

void print_srv_stats( void )
{
  struct tms end_acct;

  times( &end_acct ); /* End-CPU-Zeiten ermitteln */

  /* Zeitdifferenzen berechnen und ausgeben */
  syslog( LOG_INFO, "CPU-Info: %d\n",
    /* CPU-Zeit im Anwendungsprozeß (User) */
    (int)( end_acct.tms_utime - start_acct.tms_utime ) +
    /* CPU-Zeit im Systemkern (System) */
    (int)( end_acct.tms_stime - start_acct.tms_stime ) +
    /* CPU-Zeit im Anwendungsprozeß (User) für die Kinder */
    (int)( end_acct.tms_cutime - start_acct.tms_cutime ) +
    /* CPU-Zeit im Systemkern (System) für die Kinder */
    (int)( end_acct.tms_cstime - start_acct.tms_cstime ) );
  return;
}
