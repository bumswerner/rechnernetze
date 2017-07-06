#   Makefile ---> persoenliches JAVA Makefile
#
#
#


# Voreinstellungen fuer den java-compiler
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

CJC=/opt/j2sdk/j2sdk1.4.2/bin/javac
CJC_FLAGS= -target 1.4 -deprecation -g


SJC=/opt/j2sdk/j2sdk1.4.2/bin/rmic
SJC_FLAGS= -keep -v1.2


# Make-Regeln
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

client:
	$(CJC) $(CJC_FLAGS) WpyEchoClient.java

server:
	$(SJC) $(SJC_FLAGS) WpyEchoServerImpl

clean:
	rm *.class *Stub*.java
