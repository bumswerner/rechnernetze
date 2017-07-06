
 /* rls.x: Remote directory listing protocol (vereinfacht) */

 const MAXNAMELEN = 255; /* maximale Dateinamenlaenge */ 
 typedef string nametype<MAXNAMELEN>; /* ein Verzeichniseintrag*/ 
 typedef struct namenode *namelist; /* Zeiger einer verketteten Liste */

 /* Ein Eintrag im Verzeichnis */
 struct namenode {
   nametype name; /* Name des Eintrages */ 
   namelist next; /* naechster Eintrag */ 
 };


 struct readdir_res {
   namelist list;
 };

 /* Programm Definition */

 program DIRPROG {
   version DIRVERS {
       readdir_res READDIR(nametype) = 1;
   } = 1;
 } = 0x20000076;
