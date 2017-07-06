/*
 *
 * WpyEchoServer.java ---> kleines Bsp-Prg zur Kommunikation 
 *                         ueber RMI
 *
 *
 *
 */
import java.rmi.*;
import java.net.*;
import java.util.*;
import java.io.*;

public interface WpyEchoServer 
       extends   Remote
{

      public final static String NAME_WPYECHO = "Wpy-Echo-Server";

  public int wieoftFrageGestellt()    throws RemoteException;
  public String stelleFrage()         throws RemoteException;
}
