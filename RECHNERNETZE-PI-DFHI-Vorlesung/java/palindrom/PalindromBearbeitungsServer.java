/*
 *
 * PalindromBearbeitungsServer.java ---> kleines Bsp-Prg zur Kommunikation 
 *                        ueber Sockets
 *
 *
 *
 */
import java.net.*;
import java.io.*;

public class PalindromBearbeitungsServer 
       extends Thread
{
     private static final String ENDE                = "ende";
     private static final String SERVER_ANTWORT_ENDE = "";

     private Socket         bearbeitungsSocket;
     private PrintStream    socketOutputStream;
     private BufferedReader socketInputStream;
     
  /*
   *
   *
   *
   *
   */
  public PalindromBearbeitungsServer( Socket initSocket )
         throws IOException
  {
    bearbeitungsSocket = initSocket;

    try
       {
        socketInputStream = new BufferedReader ( new InputStreamReader(
                                                        bearbeitungsSocket.getInputStream()
                                                     )
                                               );

        socketOutputStream = new PrintStream( bearbeitungsSocket.getOutputStream() );

       }
    catch ( IOException ioe )
       {
        meldung( "\n\nAusnahme waehrend des Verbindungsaufbaues !!!\n",
                 ioe
               );
       }
  }


  /*
   *
   *
   *
   *
   */
  public void run()
  {
           String testString, frageString, ergebnis;
     
    statusMeldung(" NEUE Verbindung " );
    
    try
       {
        frageString = anfrage( socketInputStream );
        while ( frageString != null )
          {
           ergebnis = ueberpruefe( frageString );
           antwort( socketOutputStream, ergebnis ); 
           frageString = anfrage( socketInputStream );
          }
       }
    catch ( IOException ioe )
       {
        meldung( "\n\nDas Schreiben/Lesen auf/von den/dem Socket zum Client " + 
                 " erzeugte einen Fehler !!!! \n",
                 ioe
               );
       }

    try
       {
        socketInputStream.close();
        socketOutputStream.close();
        bearbeitungsSocket.close();
        statusMeldung(" Verbindung BEENDET " );
       }
    catch ( IOException ioe )
       {
        meldung( "\n\nBeim Verbindungs-Abbau ist eine Exception aufgetreten !!! ",
                 ioe
               );
       }

  }


  /*
   *
   *
   *
   *
   */
  private String anfrage( BufferedReader socketInputStream )
          throws IOException
  {
    String clientFrage = socketInputStream.readLine();

    if ( !clientFrage.equalsIgnoreCase( ENDE ) )
      {
       return clientFrage;
      }
    else
      {
       return null;
      }
  }


  /*
   *
   *
   *
   *
   */
  private String ueberpruefe( String frageString )
  {
    String reverse = new String( new StringBuffer( frageString ).reverse() );
    String ergebnis;

    if ( frageString.equalsIgnoreCase( reverse ) )
      {
       ergebnis =  new String( "\n\tDer zu ueberpruefende String -->" + frageString +
                               "<--" +
                               "\n\tist ein P A L I N D R O M denn " +
                               "\n\tder resultierende gedrehte String -->" + reverse +
                               "<--" +
                               "\n\tist mit ihm bis auf die Gross- Kleinschreibung identisch !!!" +
                               "\n"
                             );
      }
    else
      {
       ergebnis =  new String( "\n\tDer zu ueberpruefende String -->" + frageString +
                               "<--" +
                               "\n\tist ein KEIN P A L I N D R O M denn " +
                               "\n\tder resultierende gedrehte String -->" + reverse +
                               "<--" +
                               "\n\tist mit ihm NICHT identisch !!!" +
                               "\n"
                             );
      }
    return ergebnis;
  }


  /*
   *
   *
   *
   *
   */
  private void antwort( PrintStream socketOutputStream, String ergebnis )
          throws IOException
  {
   socketOutputStream.println( ergebnis );
   socketOutputStream.println( SERVER_ANTWORT_ENDE );
  }


  /*
   *
   *
   *
   *
   */
  private void meldung( String meldung, Exception ex )
  {
   System.err.println( "[ " + bearbeitungsSocket.getInetAddress() +
                       ":" +  bearbeitungsSocket.getPort() + " ] --> " +
                       meldung + 
                       "\nDie Exception : \n" + ex  +
                       "\n\nDer Stacktrace : \n"
                     );
   ex.printStackTrace();
   System.err.println( "\n\n" );
  }


  /*
   *
   *
   *
   *
   */
  private void statusMeldung( String meldung )
  {
   System.err.println( "[ " + bearbeitungsSocket.getInetAddress() +
                       ":" +  bearbeitungsSocket.getPort() + " ] --> " +
                       meldung 
                     );
  }

}
