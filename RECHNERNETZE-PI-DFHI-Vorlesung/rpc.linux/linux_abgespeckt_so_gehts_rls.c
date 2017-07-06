
 /* rls.c: Remote directory listing client */

 #include <stdio.h>
 #include <errno.h>
 /* vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
    #include <netconfig.h>
 */
 #include "rls.h" /* wird von rpcgen generiert */ 

 main(int argc, char *argv[]) {

   CLIENT *clnt;
   char *server;
   char *dir;
   readdir_res *result;
   namelist nl;
   if (argc != 3) {
     fprintf(stderr, "usage: %s host directory\n",argv[0]); 
     exit(1);
   }

   server = argv[1];
   dir = argv[2];
   clnt = clnt_create(server, DIRPROG, DIRVERS, "tcp"); 
   if (clnt == (CLIENT *)NULL) {
     clnt_pcreateerror(server);
     exit(1);
   }

   result = readdir_1(&dir, clnt);
   if (result == (readdir_res *)NULL) {
     clnt_perror(clnt, server); /* RPC schlug fehl */
     exit(1);
   }

   /* vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
      if (result->errno != 0) {
        errno = result->errno; * Fehler beim Server * 
        perror(dir);
        exit(1);
      }
   */

   /* vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
   for (nl = result->readdir_res_u.list;nl != NULL; nl = nl->next) {
     printf("%s\n", nl->name);
   }
    ersezt durch vvvvvvvvvvvvvvvvvvvvvvv*/
   for (nl = result->list;nl != NULL; nl = nl->next) {
     printf("%s\n", nl->name);
   }

   xdr_free(xdr_readdir_res, result);
   clnt_destroy(clnt);
   exit(0);
 }
