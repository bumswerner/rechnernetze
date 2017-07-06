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
     private int    antwortNummer;


  public SocketServer( int portNummer )
         throws IOException
  {
    this.portNummer = portNummer;
    antwortNummer = 0;
    
    ServerSocket serverSocket = new ServerSocket( portNummer );
    Socket       dasServerSocket = null;
    ObjectInputStream serverSocketObjectInputStream = null;
    ObjectOutputStream serverSocketObjectOutputStream = null;
    PrintStream  derMeldungsAusgabeStrom;

    while( true )
      {
       try
         {
          dasServerSocket = serverSocket.accept();

          System.out.println( "\n\tHier die Merkmale des erzeugten Socket's : " +
                              "\n\t- die lokale Server - Internet-Adresse       ---> " +
                               dasServerSocket.getLocalAddress() +
                              "\n\t- die lokale Server - TCP - Portnummer       ---> " +
                               dasServerSocket.getLocalPort() +
                              "\n\t- die lokale Server - Empfangs-Puffer-Groesse  ---> " +
                               dasServerSocket.getReceiveBufferSize() +
                              "\n\t- die lokale Server - Sende-Puffer-Groesse     ---> " +
                               dasServerSocket.getSendBufferSize() +
                              "\n\t- die entfernte Client - Internet-Adresse    ---> " +
                               dasServerSocket.getInetAddress() +
                              "\n\t- die entfernte Client - TCP - Portnummer    ---> " +
                               dasServerSocket.getPort() +
                              "\n\n"
                            );
         


          serverSocketObjectInputStream =
                            new ObjectInputStream (
                                                   dasServerSocket.getInputStream()
                                                  );
          System.out.println( "serverSocketObject I N P U T Stream erzeugt !!!!" );

      
          serverSocketObjectOutputStream =
                            new ObjectOutputStream (
                                                    dasServerSocket.getOutputStream()
                                                   );
          System.out.println( "serverSocketObject O U T  P U T Stream erzeugt !!!!" );
      
          String clientAnFrage;
          String antwortAnClient;
      
          try 
             {
              while (true)
                   {
                    antwortNummer++;
    
                    clientAnFrage = (String)serverSocketObjectInputStream.readObject();
                    System.out.println("CLIENT ::-> " + clientAnFrage );

                    antwortAnClient = new String(" Meine Antwort auf Deine Frage :: " +
                                                 clientAnFrage + ":: ist die Zahl :: "+
                                                 antwortNummer );

                    serverSocketObjectOutputStream.writeObject( antwortAnClient );
                   }

             }
          catch ( EOFException npex )
             {
              System.err.println( "Kommunikation zu  E N D E !!!");
             } 
         }
       catch ( Exception ioe )
         {
          System.err.println( "\n\nDie Kommunikation zum Client " + 
                              " erzeugte einen Fehler !!!! \n" +
                              "\nDie Exception : \n" + ioe  +
                              "\n\nDer Stacktrace : \n"
                            );
          ioe.printStackTrace();
          System.err.println( "\n\n" );
      
          serverSocketObjectInputStream.close();
          serverSocketObjectOutputStream.close();
          dasServerSocket.close();
      
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
           System.err.println( "\n\nFehler beim Schließen des Server-Sockets !!!\n" +
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
