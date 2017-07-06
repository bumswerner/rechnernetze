/*
 *
 * WpyEchoServerImpl.java ---> kleines Bsp-Prg zur Kommunikation 
 *                             ueber Sockets
 *
 *
 *
 */
import java.rmi.*;
import java.rmi.server.*;
import java.net.*;
import java.io.*;

public class WpyEchoServerImpl 
       extends UnicastRemoteObject
       implements WpyEchoServer
{
     private int wieoftGefragt;

  /*
   *
   */
  public WpyEchoServerImpl()
         throws RemoteException
  {
   wieoftGefragt = 0;
  }

  /*
   *
   */
  public String stelleFrage() 
         throws RemoteException
  {
   wieoftGefragt++;
   return new String( "\tIch, der WpyEchoServer wurde bis jetzt --> " + 
                      wieoftGefragt +
                      " <-- gefragt !!!!"
                    );
  }

  /*
   *
   */
  public int wieoftFrageGestellt() 
         throws RemoteException
  {
   return wieoftGefragt;
  }


  public static void main( String[] args ) 
  {
    try
      {
       WpyEchoServerImpl server = new WpyEchoServerImpl();

       Naming.rebind( WpyEchoServer.NAME_WPYECHO, server );
       System.out.println("\n\n\t WpyEchoServerImpl erfolgreich gestartet !!!!! \n\n");
      }
    catch ( UnmarshalException ue)
      {
       System.err.println( "\n\nUnmarshal-Exception im WpyEchoServerImpl !!!\n" +
                           "\nDie Exception : \n" + ue  +
                           "\n\nDer Stacktrace : \n"
                         );
       ue.printStackTrace();
       System.err.println( "\n\n" );
      }
    catch ( RemoteException re)
      {
       System.err.println( "\n\nRemote-Exception im WpyEchoServerImpl !!!\n" +
                           "\nDie Exception : \n" + re  +
                           "\n\nDer Stacktrace : \n"
                         );
       re.printStackTrace();
       System.err.println( "\n\n" );
      }
    catch ( MalformedURLException ulre)
      {
       System.err.println( "\n\nMalformedURL-Exception im WpyEchoServerImpl !!!\n" +
                           "\nDie Exception : \n" + ulre  +
                           "\n\nDer Stacktrace : \n"
                         );
       ulre.printStackTrace();
       System.err.println( "\n\n" );
      }
  }

}
