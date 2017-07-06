/*
 *
 * DatagramSocketServer.java ---> kleines Bsp-Prg zur Kommunikation 
 *                        ueber Sockets
 *
 *
 *
 */
import java.net.*;
import java.io.*;

public class DatagramSocketServer 
{
     private static final int    DEFAULT_PORT_NUMMER = 5193;
     private static final int    DEFAULT_PUFFER_GROESSE = 65507;
     private static final String DEFAULT_SERVERANTWORT = 
                                 "Ich bin ein einfacher UDP-Server :-))) !!!";

     private int    portNummer;
     private int    anzahl;

     private InetAddress inetAdresseVonClient;
     private int    clientPortNummer;

     private byte [] datenPuffer;

     private DatagramPacket clientFrage, serverAntwort;
     private DatagramSocket serverSocket;

     private String clientFrageString, serverAntwortString;



  public DatagramSocketServer( int portNummer )
         throws IOException
  {
    this.portNummer = portNummer;
    anzahl = 0;
    
    serverSocket = new DatagramSocket( portNummer );

    while( true )
      {
       datenPuffer = new byte[ DEFAULT_PUFFER_GROESSE ];
       clientFrage = new DatagramPacket( datenPuffer, datenPuffer.length ); 
       serverSocket.receive( clientFrage );
       System.out.println( "\n\tHier die Merkmale des erzeugten Socket's : " +
                           "\n\t- die lokale Server - Internet-Adresse       ---> " +
                            serverSocket.getLocalAddress() +
                           "\n\t- die lokale Server - UDP - Portnummer       ---> " +
                            serverSocket.getLocalPort() +
                           "\n\n"
                      );
       System.out.println( "\n\tHier die Merkmale des empfangenen UDP-Packetes : " +
                           "\n\t- die entfernte Client - Internet-Adresse    ---> " +
                            clientFrage.getAddress() +
                           "\n\t- die entfernte Client - UDP - Portnummer    ---> " +
                            clientFrage.getPort() +
                           "\n\n"
                      );
       clientFrageString = new String( datenPuffer );
       System.out.println( "\n\tDie Client-Anfrage ---> " + clientFrageString +
                           "\n"
                         );
   
       inetAdresseVonClient = clientFrage.getAddress();
       clientPortNummer     = clientFrage.getPort();
       anzahl++;
       serverAntwortString = new String( DEFAULT_SERVERANTWORT + 
                                         "\n\tUnd wurde das schon " + anzahl +
                                         "'mal gefragt ?? :-(("
                                       );
       datenPuffer = serverAntwortString.getBytes();
       serverAntwort = new DatagramPacket( datenPuffer, datenPuffer.length,
                                           inetAdresseVonClient, clientPortNummer
                                         ); 
       serverSocket.send( serverAntwort );
   
      }
  }


  public static void main( String[] args ) 
  {
       DatagramSocketServer server;

       int    portNummer = DEFAULT_PORT_NUMMER;

       final int MIN_PARAMERTER_ANZAHL = 0;
       final int MAX_PARAMERTER_ANZAHL = 1;

       boolean parameterOk = (args.length <= MAX_PARAMERTER_ANZAHL);

     switch ( args.length )
       {
        case MAX_PARAMERTER_ANZAHL :
             try
               {
                portNummer = Integer.parseInt( args[MAX_PARAMERTER_ANZAHL - 1 ] );
               }
             catch ( NumberFormatException nex )
               {
                System.err.println("\nDie angegebene Port-Nummer laesst sich " +
                                   "\nNICHT in eine Zahl umwandeln !!!!\n"
                                  );
               }
       }


      
     if ( parameterOk )
       {
        try
          {
           server = new DatagramSocketServer( portNummer );
          }
        catch ( IOException ioe)
          {
           System.err.println( "\n\nFehler beim Schliessen des Server-Sockets !!!\n" +
                               "\nDie Exception : \n" + ioe  +
                               "\n\nDer Stacktrace : \n"
                             );
           ioe.printStackTrace();
           System.err.println( "\n\n" );
          }

        System.exit(0);
       }
     else
       {
        System.err.println("\nDas Programm ist wie folgt zu starten : " +
                           "\n\tjava DatagramSocketServer [portnummer]\n\n"
                          );
        System.exit(1);
       }
  }

}
