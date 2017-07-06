#
#
#
#   Makefile ---> zur Erzeugung von einer RPC-basierten 
#                 Client-Server Anwendung
#
#
#

CC=gcc
INCLUDES = rls.h

SERVER_OBJECTS = rls_xdr.o rls_svc.o rls_server.o
CLIENT_OBJECTS = rls_xdr.o rls_clnt.o rls.o

#wpy ---> mittels sun-compiler    :LIBS = -lnsl -socket
LIBS = -lnsl

rls_server  : $(SERVER_OBJECTS) 
	$(CC) $(SERVER_OBJECTS) $(LIBS) -o rls_server

rls         : $(CLIENT_OBJECTS) 
	$(CC) $(CLIENT_OBJECTS) $(LIBS) -o rls

rls_server.o: rls_server.c $(INCLUDES)
rls.o       : rls.c $(INCLUDES)

rls_xdr.o   : rls_xdr.c $(INCLUDES)
rls_svc.o   : rls_svc.c $(INCLUDES)
rls_clnt.o  : rls_clnt.c $(INCLUDES)

stubs:
	rpcgen rls.x
clean:
	rm rls_server rls *.o rls_xdr.c rls_svc.c rls_clnt.c rls.h
