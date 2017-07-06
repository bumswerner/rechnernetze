/* rls_server.c: entfernte "readdir" Implementation */

 #include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <dirent.h>
 #include "rls.h" /* wird von rpcgen generiert */ 

 readdir_res * readdir_1(nametype * dirname, struct svc_req *req) {
   DIR *dirp;
   struct dirent *d;
   namelist nl;
   namelist *nlp;
   static readdir_res res; /* muss statisch sein! */
   dirp = opendir(*dirname); /* Verzeichnis oeffnen */ 


   printf("So, ich arbeite was ......\n");


   if (dirp != (DIR *)NULL) {
     /* voriges Ergebnis freigegeben (sonst: memory leaks) */ 
     xdr_free(xdr_readdir_res, &res);
     nlp = &res.readdir_res_u.list;
     res.errno = 0;
     while (d = readdir(dirp)) {
       nl = *nlp = (namenode *) malloc(sizeof(namenode)); 
       if (nl == (namenode *) NULL) {
         res.errno = EAGAIN;
         break;
       }
       nl->name = strdup(d->d_name);
       nlp = &nl->next;
     }
     *nlp = (namelist)NULL;
     closedir(dirp);
   } else
     res.errno = errno;

   return (&res);
 }