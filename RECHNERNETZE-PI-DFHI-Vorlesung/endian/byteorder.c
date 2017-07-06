#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/systeminfo.h>

int main(int argc, char **argv)
{
    union {
           short  s;
           char   c[sizeof(short)];
    } un;

    struct utsname hostDetails;
    char instructionsets[20];

    if ( uname(&hostDetails) < 0 )
      {
       printf("\n\tRechner-Name, -Betriebssystem und - HW-Tpy nicht feststellbar !!!!\n");
       if ( sysinfo( SI_ARCHITECTURE_NATIVE, &instructionsets, sizeof(instructionsets) ) > -1 )
         {
          printf("\n\tCPU-Typ\t\t\t-> %s",instructionsets );
         }
       else
         {
          printf("\n\tCPU-Typ nicht feststellbar !!!!" );
         }
      }
    else
      {
       printf("\n\tAuf diesem Rechner\t-> %s \n\tlaeuft \t\t\t-> %s-%s.%s \n\tauf folgender Hardware\t-> %s", 
              hostDetails.nodename, hostDetails.sysname, hostDetails.release, 
              hostDetails.version, hostDetails.machine
             );
       if ( sysinfo( SI_ARCHITECTURE_NATIVE, &instructionsets, sizeof(instructionsets) ) > -1 )
         {
          printf("\n\tCPU-Typ\t\t\t-> %s",instructionsets );
         }
       else
         {
          printf("\n\tCPU-Typ nicht feststellbar !!!!" );
         }
      }

    un.s = 0x0102;
    if (sizeof(short) == 2) 
      {
       if (un.c[0] == 1 && un.c[1] == 2)
         {
          printf("\n\tdiese CPU benutzt die \t-> b i g - e n d i a n -Darstellung fuer Zahlen !!\n\n");
         } 
       else
         {
          if (un.c[0] == 2 && un.c[1] == 1)
            {
             printf("\n\tdiese CPU benutzt die l i t t l e - e n d i a n -Darstellung fuer Zahlen !!\n\n");
            }
          else
            {
             printf("unknown\n");
            }
         } 
      }
    else
      {
       printf("sizeof(short) = %d\n", sizeof(short));
      }

    exit(0);
}
