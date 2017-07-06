
echo off

rem
rem  start_win_server.bat ---> startet den rmiserver : WpyEchoServerImpl
rem

echo "\n\n\n\t starten des Servers ...."

java -Djava.security.manager -Djava.security.policy=policy WpyEchoServerImpl

echo "\n\n\t ==========================================="
echo "\n\t der server laeuft  !!!"

