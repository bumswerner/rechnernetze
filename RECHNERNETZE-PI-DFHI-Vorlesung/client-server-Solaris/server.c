/* server.c - ein Serverprogramm, das TCP nutzt */

#define closesocket close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include <unistd.h>

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define PROTOPORT 5193 /* Protokoll-Portnummer (Standard) */ 
#define QLEN 6         /* Groesse der Anfragewarteschlange */
int visits = 0;       /* Zaehler fuer Clientbesuche */ 

/*
 * Programm: Server 
 * Zweck: Socket zuweisen und dann folgendes wiederholt ausfuehren:
 *        (1) Auf naechsten Verbindungswunsch eines Clients warten
 *        (2) Kurze Nachricht an Client senden 
 *        (3) Verbindung abbauen
 *        (4) Zurueck zu Schritt (1) 
 * Syntax: server [port ] 
 * Port - zu benutzende Protokoll-Portnummer 
 * Anmerkung: Das Portargument ist optional. Wird kein Port 
 * angegeben, benutzt der Server den durch PROTOPORT 
 * bestimmten Standard.
 *------------------------------------------------------------
*/ 

int main(int argc, char *argv[])
{

   struct protoent *ptrp ; /* Zeiger auf einen Eintrag in Protokolltabelle */
   struct sockaddr_in sad; /* Struktur fuer die Serveradresse */ 
   struct sockaddr_in cad; /* Struktur fuer die Clientadresse */ 
   int ss, bs;            /* ss = Server-Socket-Deskriptor */
                          /* bs = Bearbeitungs-Socket-Deskriptor */
   int port;               /* Protokoll-Portnummer */
   int alen;               /* Laenge der Adresse */
   char buf[1000];         /* Puffer fuer die vom Server gesendeten Daten */

memset((char *)&sad, 0, sizeof(sad)); /* sockaddr-Struktur leeren */
sad.sin_family = AF_INET;             /* Familie auf Internet setzen */
sad.sin_addr.s_addr = INADDR_ANY;     /* Lokale IP-Adressen setzen */
                                      /* INADDR_ANY == alle moeglichen IP-Adressen */

/* Befehlszeilenargument auf Protokollport pruefen und Portnummer 
 * entnehmen, sofern definiert. Andernfalls den von der Konstanten 
 * PROTOPORT vorgegebenen Standard benutzen 
*/

if (argc > 1)            /* Falls Argument angegeben wurde */
  {
   port = atoi(argv[1]); /* Kdo-Zeilenparameter in Integerwert umwandeln */
                         /* String -> Ganzzahl*/ 
  }
else
  {
   port = PROTOPORT;      /* Standard-Portnummer benutzen */
  }

if (port > 0)             /* Auf gueltigen Wert pruefen */ 
  {                                       /* Umwandeln von */
   sad.sin_port = htons((uint16_t)port);  /* host-byte-order -> network byte-order */
  }
else                      /* Fehlermeldung ausgeben und beenden */
  {
   fprintf(stderr, "bad port number %s\n", argv[1]); 
   exit(1);
  }

/* Name.von TCP-Transportprotokoll in Nummer umwandeln */ 

if ( ((int)(ptrp = getprotobyname("tcp"))) == 0)
  {
   fprintf(stderr, "cannot map \"tcp\" to protocol number"); 
   exit(2);
  }

/* Socket erzeugen */
ss = socket(PF_INET, SOCK_STREAM, ptrp->p_proto); 
if (ss < 0)
  {
   fprintf(stderr, "socket creation failed\n"); 
   exit(3);
  }

/* Lokale Adresse mit Socket binden */
if (bind(ss, (struct sockaddr *)&sad, sizeof(sad)) < 0)
  {
   fprintf(stderr, "bind failed\n");
   exit(4); 
  }

/* Groesse der Anfragewarteschlange bestimmen */ 
if (listen(ss, QLEN) < 0)
  {
   fprintf(stderr, "listen failed\n"); 
   exit(5);
  }

/* Hauptschleife des Servers - Anfragen annehmen und bedienen */ 
while(1) 
  {
   alen = sizeof(cad);
   if ( (bs=accept(ss, (struct sockaddr *)&cad, &alen)) < 0)
     {
      fprintf(stderr, "accept failed\n"); 
      exit(6);
     }
   /* hier wuerde man bei einem realen Server den WORKER als eigenen Prozess starten */
   /* z.b. mittels fork() */
   visits++; 
   sprintf(buf, "This server has been contacted %d time%s\n", 
           visits, visits==1?".":"s.");
   send(bs, buf, strlen(buf), 0);
   closesocket(bs);
  }
}
