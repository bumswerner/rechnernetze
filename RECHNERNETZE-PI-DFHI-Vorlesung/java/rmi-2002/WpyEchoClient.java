/*
 *
 * WpyEchoClient.java ---> kleines Bsp-Prg zur Kommunikation 
 *                        ueber RMI
 *
 *
 *
 */
import java.rmi.*;
import java.net.*;
import java.util.*;
import java.io.*;

public class WpyEchoClient 
{
     private static final String DEFAULT_HOST_NAME   = "//localhost/";

     private String         serverName;
     private WpyEchoServer  wpyEchoServer;

  /*
   *
   *
   *
   *
   */
  public WpyEchoClient( String server ) 
         throws NotBoundException, MalformedURLException, RemoteException
  {
        serverName = new String ( server);

    System.setSecurityManager( new RMISecurityManager() );

    wpyEchoServer = (WpyEchoServer) Naming.lookup( serverName  + WpyEchoServer.NAME_WPYECHO );
  }

  /*
   *
   *
   *
   *
   */
  public void start( int anzahlFragen, int anzahlWieOft ) 
         throws RemoteException
  {
      String serverAntwort;

   for ( int i = 0; i < anzahlFragen; i++ )
      {
       serverAntwort = wpyEchoServer.stelleFrage();
       System.out.println( "\nDer Server sagt : " + serverAntwort );
       if ( i % anzahlWieOft == 0 )
         {
          System.out.println( "\nDem Server wurde --> " + 
                              wpyEchoServer.wieoftFrageGestellt() +
                              " <-- mal die Frage gestellt !!!!"
                            );
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
        String hostName;
        WpyEchoClient wpyEchoClient;

    if ( args.length == 1 )
      {
       hostName = new String( "//" + args[0] + "/" );
      }
    else
      {
       hostName = new String(DEFAULT_HOST_NAME);
      }
    
    
   try
      {
       wpyEchoClient = new WpyEchoClient( hostName );
    
       System.out.println( "\n\n\tEs kommen 10 stelleFrage - Aufrufe \n\t und \n\t" +
                           "nach jeweils 2 ein wieoftFrageGestellt - Aufruf\n\n"
                         );
       wpyEchoClient.start( 10, 2 );
       System.out.println( "\n\n\tEs kommen 12 stelleFrage - Aufrufe \n\t und \n\t" +
                           "nach jeweils 3 ein wieoftFrageGestellt - Aufruf\n\n"
                         );
       wpyEchoClient.start( 12, 3 );
      }
   catch ( NotBoundException nbex ) 
      {
       System.err.println( "\n\nNotBoundException im WpyEchoClient  ---> " + 
                           "\nDie NotBoundException : \n" + nbex  +
                           "\n\nDer Stacktrace : \n"
                         );
       nbex.printStackTrace();
       System.err.println( "\n\n" );
      }
   catch ( MalformedURLException urlex ) 
      {
       System.err.println( "\n\nMalformedURLException im WpyEchoClient  ---> " + 
                           "\nDie MalformedURLException : \n" + urlex  +
                           "\n\nDer Stacktrace : \n"
                         );
       urlex.printStackTrace();
       System.err.println( "\n\n" );
      }
   catch ( RemoteException rex ) 
      {
       System.err.println( "\n\nRemoteException im WpyEchoClient  ---> " + 
                           "\nDie RemoteException : \n" + rex  +
                           "\n\nDer Stacktrace : \n"
                         );
       rex.printStackTrace();
       System.err.println( "\n\n" );
      }
   
    System.exit(0);
  }
   
}
