#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int sig) {
    printf("Ihre Bedenkzeit ist abgelaufen.\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    char antwort[] = "Hase";
    char eingabe[20];
    struct sigaction action;
    struct sigaction old_action;
    int i;
    
    setvbuf(stdin, NULL, _IOLBF, 0);
    setvbuf(stdout, NULL, _IOLBF, 0);
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    
    if(sigaction(SIGALRM, &action, &old_action) < 0) {
        printf("Konnte Handler nicht installieren: %s. \n", strerror(errno));
        return (EXIT_FAILURE);
    }
    
    printf("Sie haben 20 Sekunden für die Antwort:\n");
    printf("Was isst Sir Quickly am Liebsten?\n");
    
    alarm(2);
    
    fgets(eingabe, sizeof(eingabe), stdin);
    
    /*
        Abschliessende Zeilentrenner \n und \r entfernen 
    */
    for(i = strlen(eingabe) - 1; i >= 0 && (eingabe[i] == '\n' || eingabe[i] == '\r'); i--) {
        eingabe[i] = '\0';
    }
    
    if(strcmp(eingabe, antwort) == 0) {
        printf("Die Anwort ist richtig. Gratulation.\n");
    } else {
        printf("Leider falsch, richtig ist %s\n", antwort);
    }
    
    exit(EXIT_SUCCESS);
    
}