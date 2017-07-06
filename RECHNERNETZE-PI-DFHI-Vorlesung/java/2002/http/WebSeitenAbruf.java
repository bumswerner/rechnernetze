

package http;

import java.net.*;
import java.io.*;



 /**
 *    <H1> Die Klasse:  <B>WebSeitenAbruf.java</B></H1>
 *    Ruft eine Bestimmte HTML-Seite von einem zuvor spezifizierten
 *    Web-Server ab und gibt den HTML-Code auf dem Bildschirm aus
 *
 * @version     1.0 Beta 11.01.2002
 * @author      Wolfgang Pauly
 *
 */


public class WebSeitenAbruf
{

       // Klassen Attribute
       private static final  String URL_ANFANG = "http://";
       
       // Attribute
       URL            frageURL;
       BufferedReader antwortKanal;
       StringBuffer   antwort;


  /**
   *    <DL><DT>   Der STANDARD-Konstruktor   
   *    @param     <B>KEINE Parameter</B>
   *    </DL>
   */
   public WebSeitenAbruf()
   {
     System.out.println ("\n<!--\tEin WebSeitenAbruf-Objekt wurde konstruiert !\n\n");

     System.out.println ("\tDie Klasse WebSeitenAbruf\n"                     +
                         "\n\tRuft eine Bestimmte HTML-Seite von einem zuvor spezifizierten" +
                         "\n\tWeb-Server ab und gibt den HTML-Code auf dem Bildschirm aus" +
                         "\n-->"
                        );
     antwort = new StringBuffer();
   }


  /**
   *    <DL><DT>   Die start-Methode
   *    @param     <B>KEINE Parameter</B>
   *        <DD>   einhält die Steuerung  der Klasse-Logik
   *    </DL>
   */
   public void start( String serverName, String dokumentAdresse )
   {
         String antwortZeile;

     try
       {
        frageURL  = new URL( URL_ANFANG + serverName + "/" + dokumentAdresse );

        antwortKanal   = new BufferedReader( 
                             new InputStreamReader( frageURL.openStream() )
                             );

        while ( (antwortZeile = antwortKanal.readLine() ) != null )
          {
           antwort.append( antwortZeile ).append( "\n" );
          }

       }
     catch ( MalformedURLException urlEx )
       {
        System.out.println ("\n\n\t F E H L E R !!!!!!!!!!!" +
                            "\n\n\t Die folgende, im Programm konstruierte URL ist inkorrekt !!!" +
                            "\n\n\t" + URL_ANFANG + serverName + "/" + dokumentAdresse + "\n\n" +
                            "\n\n\t" + urlEx + "\n\n"
                           );
       }
     catch ( IOException ioEx )
       {
        System.out.println ("\n\n\t F E H L E R !!!!!!!!!!!" +
                            "\n\n\t Beim lesen der Server-Antwort trat ein IO-Fehler auf !!!" +
                            "\n\n\t" + ioEx + "\n\n"
                           );
       }
 
     System.out.println( antwort );
   }


  /**
   *    <DL><DT>   Das Test-Programm
   *               @param     <B>KEINE Parameter</B>
   *        <DD>
   *        <DD>   Erzeugt ein WebSeitenAbruf-Objekt
   *        <DD>   und
   *        <DD>   ruft seine Start-Methode auf
   *    </DL>
   */
   public static void main ( String[] args )
   {
     WebSeitenAbruf meineAnfrage = new WebSeitenAbruf();
    
     String serverName, dokumentAdresse;

     if ( args.length > 0 )
       {
        serverName = new String( args[0] );
        
        if ( args.length > 1 )
          { 
            dokumentAdresse = new String( args[1] );
          }
        else
          {
            dokumentAdresse = new String();
          }

        meineAnfrage.start( serverName, dokumentAdresse );
        System.exit( 0 );
       }
     else
       {
        System.out.println("\n\n\tUsage : java WebSeitenAbruf WWW-Servername Dokument-Adresse \n" );
        System.exit( 1 );
       }
   }
   
}
