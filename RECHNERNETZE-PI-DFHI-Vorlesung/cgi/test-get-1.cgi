#!/bin/ksh
#
# Skript test-get-1.cgi zum Testen der GET-Methode
#


echo "Content-Type: text/html"
echo ""
echo "<HTML><HEAD>"
echo "<br>"
echo "<h2> Ausgabe von QUERY_STRING </h2>"
echo "$QUERY_STRING"
echo "<br><br>"
echo "und nun auseinandergepfriemelt : "
echo "<br><br>"
NACHNAME=`/web-tools/wpy-addons/cgi-tools/cgiparse -value nachname`
echo "----> Nachname 	= $NACHNAME"
echo "<br>"
VORNAME=`/web-tools/wpy-addons/cgi-tools/cgiparse -value vorname`
echo "----> Vorname 	= $VORNAME"
echo "<br>"
eval `/web-tools/wpy-addons/cgi-tools/cgiparse -form`
echo "----> Kennung = $FORM_kennung"
echo "</HTML>"
