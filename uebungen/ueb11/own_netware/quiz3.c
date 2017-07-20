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
    char antwort[] = "Himbeerjoghurt";
    char eingabe[20];
    struct sigaction action;
    struct sigaction old_action;
    int i;
    
    setvbuf(stdin, NULL, _IOLBF, 0);
    setvbuf(stdout, NULL, _IOLBF, 0);
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    
    
}