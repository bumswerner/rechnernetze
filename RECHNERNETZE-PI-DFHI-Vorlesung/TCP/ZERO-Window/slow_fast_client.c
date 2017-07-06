/* slow_client.c - ein Clientprogramm, das TCP nutzt 
                   aber nach dem lesen von maximal 100 Zeichen
                   eine 10 Sekunden dauernde pause einlegt
*/


#define closesocket close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <unistd.h>

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


#define PROTOPORT 5193 /* Protokoll-Portnummer (Standard) */

extern int errno;
char localhost[] = "localhost"; /* Hostname (Standard) */


/*
 * Programm: Client
 * Zweck: Socket zuweisen, Verbindung zu Server aufbauen, 
 * alle empfangenen Daten ausgeben
 * Syntax: client [ host Cport] ] 
 * Host - Name eines Computers, auf dem der Server laeuft 
 * Port - Protokoll-Portnummer, die der Server benutzt
 * Anmerkung: Beide Argumente sind optional. Wird kein Hostname 
 * angegeben, benutzt der Client "localhost". Wird kein Protokollport 
 * angegeben, benutzt der Client den durch PROTOPORT bestimmten Standard.
 *----------------------------------------------------------
*/ 

int main(int argc, char *argv[]) 
{

    struct hostent *ptrh;        /* Zeiger auf einen Eintrag in Hosttabelle */
    struct protoent *ptrp;       /* Zeiger auf einen Eintrag in Protokolltabelle */
    struct sockaddr_in sad;      /* Struktur fuer eine IP-Adresse */ 
    int cs;                      /* Client-Socket-Deskriptor */
    int port;                    /* Protokoll-Portnummer */ 
    char *host;                  /* Zeiger auf Hostname */
    int n;                       /* Anzahl der gelesenen Zeichen */ 
    char buf[1000];               /* Puffer fuer Daten vom Server */ 
    unsigned int warteZeit = 1; /* Wartezeit in Sekunden */
    int slowDurchlaufZaehlerMAX = 3;
    int fastDurchlaufZaehlerMAX = 35;
    int slowDurchlaufZaehler, fastDurchlaufZaehler;
    int slow;
 
memset((char *)&sad,0,sizeof(sad)); /* sockaddr-Struktur leeren */
sad.sin_family = AF_INET;           /* Familie auf Internet setzen */ 

/* Befehlszeilenargument auf Protokollport pruefen und Portnummer 
 * entnehmen, sofern definiert. Andernfalls von der Konstanten 
 * PROTOPORT vorgegebenen Standard benutzen 
*/
if (argc > 2)                       /* Falls Protokollport angegeben wurde */
  { 
   port = atoi(argv[2]);	    /* In Binaerwert umwandeln */ 
  }
else 
  {
   port = PROTOPORT;	            /* Standard-Portnummer benutzen */
  }


if (port > 0)                       /* Auf gueltigen Wert pruefen */
  {
   sad.sin_port = htons((uint16_t)port);
  }
else                                /* Fehlermeldung ausgeben und beenden */   
  {
   fprintf(stderr, "bad port number %s\n", argv[2]);
   exit(1);
  }


/* Hostargument pruefen und Hostname zuweisen */
if (argc > 1) 
  {
   host = argv[1];	            /* Falls Hostargument angegeben wurde */
  }
else  
  {
   host = localhost;
  }

/* Hostname in IP-Adresse konvertieren und nach sad kopieren */

ptrh = gethostbyname(host);
if ( ((char *)ptrh) == NULL )
  {
   fprintf(stderr, "invalid host: %s\n", host);
   exit(1);
  }

memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);

/* Name von TCP-Transportprotokoll in Nummer konvertieren */

if ( ((int) (ptrp = getprotobyname ("tcp"))) == 0) 
  {
    fprintf(stderr, "cannot map \"tcp\" to protocol number");
    exit(1);
  }
 
/* Socket erzeugen */

cs = socket(PF_INET, SOCK_STREAM, ptrp->p_proto); 
if (cs < 0)
  {
   fprintf(stderr, "socket creation failed\n");
   exit(1);
  }
 
/* Socket mit dem betreffenden Server verbinden */

if (connect(cs, (struct sockaddr *)&sad, sizeof(sad)) < 0)
  {
   fprintf(stderr, "connect failed\n");
   exit(1);
  }

/* Daten wiederholt vom Socket lesen und am Bildschirm ausgeben */

slow = 1;
slowDurchlaufZaehler = 0;
fastDurchlaufZaehler = 0;
n = recv(cs, buf, sizeof(buf), 0);
while (n > 0)
  {
   if ( slow == 1 )
     {
      sleep(warteZeit);
      slowDurchlaufZaehler++;
      printf("%d ", slowDurchlaufZaehler );
      /* printf("%d. Durchlauf (slow) -> Daten -> ", slowDurchlaufZaehler ); */
      if ( slowDurchlaufZaehler >= slowDurchlaufZaehlerMAX )
        {
         slow = 0;
         fastDurchlaufZaehler = 0;
         printf ("\nFAST : ");
        }
     }
   else
     {
      fastDurchlaufZaehler++;
      printf("%d ", fastDurchlaufZaehler );
      /* printf("%d. Durchlauf (fast) -> Daten -> ", fastDurchlaufZaehler ); */
      if ( fastDurchlaufZaehler >= fastDurchlaufZaehlerMAX )
        {
         slow = 1;
         slowDurchlaufZaehler = 0;
         printf ("\nSLOW : ");
        }
     }

   /*write(1,buf,n); */
   if ( slowDurchlaufZaehler == 2)
     {
      printf("\n%s", buf );
     }
   n = recv(cs, buf, sizeof(buf), 0);
  }

/* Socket schliessen */ 
closesocket(cs);

/* Clientprogramm elegant beenden */
exit(0);
}

