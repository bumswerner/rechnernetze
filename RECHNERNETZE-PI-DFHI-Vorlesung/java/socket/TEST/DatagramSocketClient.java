/*
 *
 * DatagramSocketClient.java ---> kleines Bsp-Prg zur Kommunikation 
 *                                 ueber DatagramSockets
 *
 *
 *
 */
import java.net.*;
import java.io.*;

public class DatagramSocketClient 
{
     private static final int    DEFAULT_PORT_NUMMER = 4446;
     private static final String DEFAULT_HOST_NAME   = "localhost";
     private static final int    DEFAULT_PUFFER_GROESSE = 65507;
     private static final String DEFAULT_CLIENT_FRAGE   = "Hallo wer bist du ;-)))) ???";


     private String hostName;
     private int    portNummer;
  
     private InetAddress inetAdresseVonServer;
     private byte [] datenPuffer;
      
     private DatagramPacket clientFrage, serverAntwort;
     private DatagramSocket clientSocket;


  public DatagramSocketClient( String hostName, int portNummer )
         throws UnknownHostException, IOException
  {
    this.hostName = hostName;
    this.portNummer = portNummer;

    inetAdresseVonServer = InetAddress.getByName( hostName );

    clientSocket  = new DatagramSocket();

    datenPuffer = DEFAULT_CLIENT_FRAGE.getBytes();
    clientFrage = new DatagramPacket( datenPuffer, datenPuffer.length, 
                                      inetAdresseVonServer, portNummer 
                                    );
    System.out.println( "\n\tVor senden");
    clientSocket.send( clientFrage );
    System.out.println( "\n\tNach senden");
    

    datenPuffer   = new byte[ DEFAULT_PUFFER_GROESSE ];
    serverAntwort = new DatagramPacket( datenPuffer, datenPuffer.length );
    clientSocket.receive( serverAntwort );
    System.out.println( "\n\tHier die Merkmale des erzeugten Socket's : " +
                        "\n\t- die lokale Client - Internet-Adresse       ---> " +
                        clientSocket.getLocalAddress() +
                        "\n\t- die lokale Client - UDP - Portnummer       ---> " +
                        clientSocket.getLocalPort() +
                        "\n\n"
                      );
    System.out.println( "\n\tHier die Merkmale des empfangenen UDP-Packetes : " +
                        "\n\t- die entfernte Server - Internet-Adresse    ---> " +
                        serverAntwort.getAddress() +
                        "\n\t- die entfernte Server - UDP - Portnummer    ---> " +
                        serverAntwort.getPort() +
                        "\n\n"
                      );


    datenPuffer = serverAntwort.getData();

    
    String serverAntwortString = new String( datenPuffer );
    if ( serverAntwortString != null )
      {
       System.out.println( "\n\tDie Antwort des Servers : " +
                           "\n\n\t" + serverAntwortString + "\n\n"
                         );
      }
    else
      {
       System.out.println( "\n\tDie Antwort des Servers : " +
                           "\n\n\tes gibt K E I N E !!!!!\n\n"
                         );
      }
    
    clientSocket.close();
  }


  public static void main( String[] args ) 
  {
       DatagramSocketClient client;

       String hostName   = DEFAULT_HOST_NAME;
       int    portNummer = DEFAULT_PORT_NUMMER;

       final int MIN_PARAMERTER_ANZAHL = 0;
       final int MAX_PARAMERTER_ANZAHL = 2;

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
                System.err.println("\nDie angegebene Port-Nummer läßt sich " +
                                   "\nNICHT in eine Zahl umwandeln !!!!\n"
                                  );
               }
             hostName = args[MIN_PARAMERTER_ANZAHL];
        case MAX_PARAMERTER_ANZAHL - 1 :
             hostName = args[MIN_PARAMERTER_ANZAHL];
       }


      
     if ( parameterOk )
       {
        try
           {
            client = new DatagramSocketClient( hostName, portNummer );
           }
        catch ( UnknownHostException uhe ) 
           {
            System.err.println( "\n\nDer Host mit dem Namen ---> " + hostName +
                                " <--- existiert nicht !!!! \n" +
                                "\nDie Exception : \n" + uhe  +
                                "\n\nDer Stacktrace : \n"
                              );
            uhe.printStackTrace();
            System.err.println( "\n\n" );
           }
        catch ( IOException ioe ) 
           {
            System.err.println( "\n\nDas Lesen aus dem Socket zum Host ---> " + hostName +
                                " <--- erzeugte Fehler !!!! \n" +
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
        System.err.println("\nDas Program ist wie folgt zu starten : " +
                           "\n\tjava DatagramSocketClient [hostname [portnummer]]\n\n"
                          );
        System.exit(1);
       }
  }

}
