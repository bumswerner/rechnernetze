/*
 *
 * SocketClient.java ---> kleines Bsp-Prg zur Kommunikation 
 *                        ueber Sockets
 *
 *
 *
 */
import java.net.*;
import java.io.*;

public class SocketClient 
{
     private static final int    DEFAULT_PORT_NUMMER = 5193;
     private static final String DEFAULT_HOST_NAME   = "localhost";


     private String hostName;
     private int    portNummer;


  public SocketClient( String hostName, int portNummer )
         throws UnknownHostException, IOException
  {
    this.hostName = hostName;
    this.portNummer = portNummer;
    
    Socket         clientSocket = new Socket( hostName, portNummer );

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

    BufferedReader clientSocketInputStream = new BufferedReader (
                                                 new InputStreamReader(
                                                     clientSocket.getInputStream()
                                                 )
                                             );

    String serverAntwort = clientSocketInputStream.readLine();
    if ( serverAntwort != null )
      {
       System.out.println( "\n\tDie Antwort des Servers : " +
                           "\n\n\t" + serverAntwort + "\n\n"
                         );
      }
    else
      {
       System.out.println( "\n\tDie Antwort des Servers : " +
                           "\n\n\tes gibt K E I N E !!!!!\n\n"
                         );
      }
    
    clientSocketInputStream.close();
    clientSocket.close();
  }


  public static void main( String[] args ) 
  {
       SocketClient client;

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
                System.err.println("\nDie angegebene Port-Nummer laesst sich " +
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
            client = new SocketClient( hostName, portNummer );
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
        System.err.println("\nDas Programm ist wie folgt zu starten : " +
                           "\n\tjava SocketClient [hostname [portnummer]]\n\n"
                          );
        System.exit(1);
       }
  }

}
