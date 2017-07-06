/* rls_server.c: entfernte "readdir" Implementation */

 #include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <dirent.h>
 #include "rls.h" /* wird von rpcgen generiert */ 

 readdir_res * readdir_1_svc(nametype * dirname, struct svc_req *req) {
   DIR *dirp;
   struct dirent *d;
   namelist nl;
   namelist *nlp;
   static readdir_res res; /* muss statisch sein! */
   dirp = opendir(*dirname); /* Verzeichnis oeffnen */ 

   if (dirp != (DIR *)NULL) {
     /* voriges Ergebnis freigegeben (sonst: memory leaks) */ 
     xdr_free(xdr_readdir_res, &res);
     /* vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
     nlp = &res.readdir_res_u.list;
     vvvvvvvvvvvvvvvvvv von wpy ersetzt durch */
     nlp = &res.list;
     /* vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
       res.errno = 0;
     */
     while (d = readdir(dirp)) {
       nl = *nlp = (namenode *) malloc(sizeof(namenode)); 
       if (nl == (namenode *) NULL) {
         /* vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
           res.errno = EAGAIN;
         */
         break;
       }
       nl->name = strdup(d->d_name);
       nlp = &nl->next;
     }
     *nlp = (namelist)NULL;
     closedir(dirp);
   } /* else vvvvvvvvvvvvvvvvvv von wpy ausgeixt !!!!
      res.errno = errno;
     */

   return (&res);
 }
