


package einfach;
import java.net.*;
// import de.htw.saarland.stl.Stdin;



 /**
 *    <H1> Die Klasse:  <B>Host.java</B></H1>
 *    Gibt den DNS-Host-Name und die IP-Adresse des Rechners aus.
 *
 * @version     1.0 Beta 08.01.2002
 * @author      Wolfgang Pauly
 *
 */


public class Host
{

       // Attribute
       private InetAddress localeIP;
       private String      localeHostName;


  /**
   *    <DL><DT>   Der STANDARD-Konstruktor   
   *    @param     <B>KEINE Parameter</B>
   *    </DL>
   */
   public Host()
   {
     System.out.println ("\n\tEin Host-Objekt wurde konstruiert !\n\n");

     System.out.println ("\tDie Klasse Host\n"                     +
                         "\tgibt den DNS-Host-Namen und die IP-Adresse\n" +
                         "\tdes Rechners aus, auf dem sie gestartet wird.\n\n"
                        );
     localeIP       = null;
     localeHostName = null;
   }


  /**
   *    <DL><DT>   Die start-Methode
   *    @param     <B>KEINE Parameter</B>
   *        <DD>   einhält die Steuerung  der Klasse-Logik
   *    </DL>
   */
   public void start()
   {
     try
       {
        localeIP = InetAddress.getLocalHost();
        localeHostName = localeIP.getHostName();
       }
     catch ( UnknownHostException hostEx )
       {
        System.out.println ("\n\n\t F E H L E R !!!!!!!!!!!" +
                            "\n\n\t Kein TCP/IP-Protokoll verfuegbar !!!" +
                            "\n\n\t" + hostEx + "\n\n"
                           );
       }

     System.out.println("\n\n\tDer Rechner hat den Name : " + localeHostName +
                        "\n\tund\n\tdie IP-Adresse\t\t : " + localeIP +
                        "\n\n"
                       );
   }


  /**
   *    <DL><DT>   Das Test-Programm
   *               @param     <B>KEINE Parameter</B>
   *        <DD>
   *        <DD>   Erzeugt ein Host-Objekt
   *        <DD>   und
   *        <DD>   ruft seine Start-Methode auf
   *    </DL>
   */
   public static void main ( String[] args )
   {
     Host meinHost = new Host();
     meinHost.start();
     System.exit( 0 );
   }
   
}
