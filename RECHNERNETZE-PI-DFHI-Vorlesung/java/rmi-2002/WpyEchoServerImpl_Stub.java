// Stub class generated by rmic, do not edit.
// Contents subject to change without notice.

public final class WpyEchoServerImpl_Stub
    extends java.rmi.server.RemoteStub
    implements WpyEchoServer, java.rmi.Remote
{
    private static final long serialVersionUID = 2;
    
    private static java.lang.reflect.Method $method_stelleFrage_0;
    private static java.lang.reflect.Method $method_wieoftFrageGestellt_1;
    
    static {
	try {
	    $method_stelleFrage_0 = WpyEchoServer.class.getMethod("stelleFrage", new java.lang.Class[] {});
	    $method_wieoftFrageGestellt_1 = WpyEchoServer.class.getMethod("wieoftFrageGestellt", new java.lang.Class[] {});
	} catch (java.lang.NoSuchMethodException e) {
	    throw new java.lang.NoSuchMethodError(
		"stub class initialization failed");
	}
    }
    
    // constructors
    public WpyEchoServerImpl_Stub(java.rmi.server.RemoteRef ref) {
	super(ref);
    }
    
    // methods from remote interfaces
    
    // implementation of stelleFrage()
    public java.lang.String stelleFrage()
	throws java.rmi.RemoteException
    {
	try {
	    Object $result = ref.invoke(this, $method_stelleFrage_0, null, 8064765137374034843L);
	    return ((java.lang.String) $result);
	} catch (java.lang.RuntimeException e) {
	    throw e;
	} catch (java.rmi.RemoteException e) {
	    throw e;
	} catch (java.lang.Exception e) {
	    throw new java.rmi.UnexpectedException("undeclared checked exception", e);
	}
    }
    
    // implementation of wieoftFrageGestellt()
    public int wieoftFrageGestellt()
	throws java.rmi.RemoteException
    {
	try {
	    Object $result = ref.invoke(this, $method_wieoftFrageGestellt_1, null, -6114806542334990559L);
	    return ((java.lang.Integer) $result).intValue();
	} catch (java.lang.RuntimeException e) {
	    throw e;
	} catch (java.rmi.RemoteException e) {
	    throw e;
	} catch (java.lang.Exception e) {
	    throw new java.rmi.UnexpectedException("undeclared checked exception", e);
	}
    }
}
