/*
 *
 * PalindromServer.java ---> kleines Bsp-Prg zur Kommunikation 
 *                           ueber Sockets
 *
 *
 *
 */
import java.net.*;
import java.io.*;

public class PalindromServer 
{
     private static final int    DEFAULT_PORT_NUMMER = 18767;

     private int    portNummer;


  /*
   *
   *
   *
   *
   */
  public PalindromServer( int portNummer )
         throws IOException
  {
       ServerSocket serverSocket;
       Socket       bearbeitungsSocket;

    this.portNummer = portNummer;
    
    serverSocket = new ServerSocket( portNummer );
    System.out.println( "\n\tHier die Merkmale des Server-Lausch-Socket's : " +
                        "\n\t- die lokale Server - Internet-Adresse    ---> " +
                        serverSocket.getInetAddress() +
                        "\n\t- die lokale Server - TCP - Portnummer       ---> " +
                        serverSocket.getLocalPort() +
                        "\n\n"
                       );

    while( true )
      {
       try
         {
          bearbeitungsSocket = serverSocket.accept();

          System.out.println( "\n\tHier die Merkmale des Bearbeitungs-Socket's : " +
                              "\n\t- die lokale Server - Internet-Adresse       ---> " +
                               bearbeitungsSocket.getLocalAddress() +
                              "\n\t- die lokale Server - TCP - Portnummer       ---> " +
                               bearbeitungsSocket.getLocalPort() +
                              "\n\t- die lokale Server - Empfangs-Puffer-Groesse  ---> " +
                               bearbeitungsSocket.getReceiveBufferSize() +
                              "\n\t- die lokale Server - Sende-Puffer-Groesse     ---> " +
                               bearbeitungsSocket.getSendBufferSize() +
                              "\n\t- die entfernte Client - Internet-Adresse    ---> " +
                               bearbeitungsSocket.getInetAddress() +
                              "\n\t- die entfernte Client - TCP - Portnummer    ---> " +
                               bearbeitungsSocket.getPort() +
                              "\n\n"
                            );
         
          new PalindromBearbeitungsServer( bearbeitungsSocket ).start();
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


  /*
   *
   *
   *
   *
   */
  public static void main( String[] args ) 
  {
       PalindromServer server;

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
           server = new PalindromServer( portNummer );
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
                           "\n\tjava PalindromServer [portnummer]\n\n"
                          );
        System.exit(1);
       }
  }

}
