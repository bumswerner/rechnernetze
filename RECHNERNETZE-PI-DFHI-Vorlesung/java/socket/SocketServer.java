/*
 *
 * SocketServer.java ---> kleines Bsp-Prg zur Kommunikation 
 *                        ueber Sockets
 *
 *
 *
 */
import java.net.*;
import java.io.*;

public class SocketServer 
{
     private static final int    DEFAULT_PORT_NUMMER = 5193;


     private int    portNummer;
     private int    anzahl;


  public SocketServer( int portNummer )
         throws IOException
  {
    this.portNummer = portNummer;
    anzahl = 0;
    
    ServerSocket serverSocket = new ServerSocket( portNummer );
    Socket       eineSocketVerbindung;
    PrintStream  derMeldungsAusgabeStrom;

    while( true )
      {
       try
         {
          eineSocketVerbindung = serverSocket.accept();

          System.out.println( "\n\tHier die Merkmale des erzeugten Socket's : " +
                              "\n\t- die lokale Server - Internet-Adresse       ---> " +
                               eineSocketVerbindung.getLocalAddress() +
                              "\n\t- die lokale Server - TCP - Portnummer       ---> " +
                               eineSocketVerbindung.getLocalPort() +
                              "\n\t- die lokale Server - Empfangs-Puffer-Groesse  ---> " +
                               eineSocketVerbindung.getReceiveBufferSize() +
                              "\n\t- die lokale Server - Sende-Puffer-Groesse     ---> " +
                               eineSocketVerbindung.getSendBufferSize() +
                              "\n\t- die entfernte Client - Internet-Adresse    ---> " +
                               eineSocketVerbindung.getInetAddress() +
                              "\n\t- die entfernte Client - TCP - Portnummer    ---> " +
                               eineSocketVerbindung.getPort() +
                              "\n\n"
                            );
         
          derMeldungsAusgabeStrom = new PrintStream( 
                                        eineSocketVerbindung.getOutputStream()
                                        );
   
          anzahl++;
          derMeldungsAusgabeStrom.println( "Dies ist der " + anzahl + 
                                           "'te Verbindungswunsch !!!\n" 
                                         );
          derMeldungsAusgabeStrom.close();
          eineSocketVerbindung.close();
         }
       catch ( IOException ioe )
         {
          System.err.println( "\n\nDas Schreiben auf den Socket zum Client " + 
                              " erzeugte einen Fehler !!!! \n" +
                              "\nDie Exception : \n" + ioe  +
                              "\n\nDer Stacktrace : \n"
                            );
          ioe.printStackTrace();
          System.err.println( "\n\n" );
          serverSocket.close();
          System.exit( -1 );
         }
      }
  }


  public static void main( String[] args ) 
  {
       SocketServer server;

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
           server = new SocketServer( portNummer );
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
                           "\n\tjava SocketServer [portnummer]\n\n"
                          );
        System.exit(1);
       }
  }

}
