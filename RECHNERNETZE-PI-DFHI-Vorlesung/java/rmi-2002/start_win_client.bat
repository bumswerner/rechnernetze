
echo off

rem
rem  start_win_client ---> Startet den RmiClient : WpyEchoClient
rem
rem
rem
rem

echo "\n\n\t das starten des clients ...."
echo "\n\t wird die Prozedur : $0 "
echo "\n\t ohne Paramenter gestartet, so muss "
echo "\n\t die rmiregistry und der server auf dem LOKALEN Rechner laufen !!"
echo "\n\n\t startet man die Prozedur mit einem Rechnernamen "
echo "\n\t als Parameter, so muss die rmiregistry und der server"
echo "\n\t auf demjenigen Rechner laufen !!!!"
echo "\n\n"
 

if "%1A"=="A" goto LOCAL
   java  -Djava.security.policy=policy WpyEchoClient %1
   goto ENDE
:LOCAL
   java  -Djava.security.policy=policy WpyEchoClient localhost 
:ENDE

echo "\n\n\t Client hat sich beendet !!!!"
