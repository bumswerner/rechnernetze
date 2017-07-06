/*
 *
 * PalindromClient.java ---> zweites kleines Bsp-Prg zur Kommunikation 
 *                           ueber Sockets
 *                           Der Client sendet einen vom Benutzer eingegebenen
 *                           String an den Palindrom-Server, der schickt, wenn
 *                           es sich bei dem String um ein Palindrom handelt, diesen
 *                           gedreht zurueck ( Klein- == Gross- Buchstaben ) 
 *                           mit der Meldung ist Palindrom, ansonsten
 *                           wird nur eine Meldung geschickt, dass kein Palindrom
 *                           empfangen wurde.
 */
import java.net.*;
import java.io.*;
import java.util.Scanner;


public class PalindromClient 
{
     private static final int    DEFAULT_PORT_NUMMER = 18767;
     private static final String DEFAULT_SERVER_NAME = "localhost";
     private static final String SERVER_ANTWORT_ENDE = "";
     private static final String ENDE                = "ende";


     private String serverName;
     private int    portNummer;
  /*
   *
   *
   *
   *
   */
  public PalindromClient( String serverName, int portNummer )
         throws UnknownHostException, IOException
  {
      //--------- Eingabe Kanal --------------------------------
      Scanner in = new Scanner( System.in );

          String testString;
          Socket         clientSocket;
          BufferedReader socketInputStream;
          PrintStream    socketOutputStream;

    this.serverName = serverName;
    this.portNummer = portNummer;
    
    clientSocket = new Socket( serverName, portNummer );

    System.out.println( "\n\tHier die Merkmale des erzeugten Socket's : " +
                        "\n\t- die lokale Client - Internet-Adresse       ---> " +
                         clientSocket.getLocalAddress() +
                        "\n\t- die lokale Client - TCP - Portnummer       ---> " +
                         clientSocket.getLocalPort() +
                        "\n\t- die lokale Client - Empfangs-Puffer-Groesse  ---> " +
                         clientSocket.getReceiveBufferSize() +
                        "\n\t- die lokale Client - Sende-Puffer-Groesse     ---> " +
                         clientSocket.getSendBufferSize() +
                        "\n\t- die entfernte Server - Internet-Adresse    ---> " +
                         clientSocket.getInetAddress() +
                        "\n\t- die entfernte Server - TCP - Portnummer    ---> " +
                         clientSocket.getPort() +
                        "\n\n"
                      );

    socketInputStream = new BufferedReader ( new InputStreamReader(
                                                     clientSocket.getInputStream()
                                                 )
                                             );

    socketOutputStream = new PrintStream( clientSocket.getOutputStream() );


    testString = new String( "noch leer" );
    while ( !testString.equalsIgnoreCase( ENDE ) )
      {
       testString = MyInputFunctions.readlnString(in,
                                        "Gebe den zu ueberpruefenden String " +
                                        "ein oder (ende): "
                                      );

       socketOutputStream.println( testString );

       if ( !testString.equalsIgnoreCase( ENDE ) )
         {
          antwort( socketInputStream );
         }
      }

    socketInputStream.close();
    socketOutputStream.close();
    clientSocket.close();
  }



  /*
   *
   *
   *
   *
   */
  private void antwort( BufferedReader socketInputStream )
          throws IOException
  {
    StringBuffer antwortPuffer = new StringBuffer();
    String serverAntwort;

    serverAntwort = socketInputStream.readLine();
    while ( serverAntwort.compareTo( SERVER_ANTWORT_ENDE ) != 0  )
      {
       antwortPuffer.append( "\n" + serverAntwort );
       serverAntwort = socketInputStream.readLine();
      }

    if ( antwortPuffer.length() > 0 )
      {
       System.out.println( "\n\tDie Antwort des Servers : " +
                           "\n\n\t" + antwortPuffer + "\n\n"
                         );
      }
    else
      {
       System.out.println( "\n\tDie Antwort des Servers : " +
                           "\n\n\tes gibt K E I N E !!!!!\n\n"
                         );
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
       PalindromClient client;

       String serverName   = DEFAULT_SERVER_NAME;
       int    portNummer   = DEFAULT_PORT_NUMMER;

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
                System.err.println("\nDie angegebene Port-Nummer laesst sich " +
                                   "\nNICHT in eine Zahl umwandeln !!!!\n"
                                  );
               }
        case MAX_PARAMERTER_ANZAHL - 1 :
             serverName = args[MIN_PARAMERTER_ANZAHL];
       }


      
     if ( parameterOk )
       {
        try
           {
            client = new PalindromClient( serverName, portNummer );
           }
        catch ( UnknownHostException uhe ) 
           {
            System.err.println( "\n\nDer HOST mit dem Namen ---> " + serverName +
                                " <--- existiert nicht !!!! \n" +
                                "\nDie Exception : \n" + uhe  +
                                "\n\nDer Stacktrace : \n"
                              );
            uhe.printStackTrace();
            System.err.println( "\n\n" );
           }
        catch ( IOException ioe ) 
           {
            System.err.println( "\n\nDas Lesen aus dem Socket zum Host ---> " + serverName +
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
        System.err.println("\nDas Programm ist wie folgt zu starten : " +
                           "\n\tjava PalindromClient [servername [portnummer]]\n\n"
                          );
        System.exit(1);
       }
  }

}
