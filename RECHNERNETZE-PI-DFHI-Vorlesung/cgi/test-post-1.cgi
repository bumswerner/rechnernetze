#!/bin/ksh
#
# Skript : test-post-1.cgi zum Testen der POST-Methode
#


echo "Content-Type: text/html"
echo ""
echo "<HTML><HEAD>"
INHALT=`/web-tools/wpy-addons/cgi-tools/cgiparse -read`
echo "<br>"
echo "<h2> Ausgabe von stdin </h2>"
echo "$INHALT"
echo "<br>"
echo "<h2> Ausgabe von QUERY_STRING </h2>"
echo "$QUERY_STRING"
echo "</HTML>"
