#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_usr(int);

int main(void) {
    setbuf(stdout, NULL);
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        fprintf(stderr, "can't catch SIGUSR1");
	exit(-1);
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        fprintf(stderr, "can't catch SIGUSR2");
	exit(-1);
    }

    printf("waiting for signals...\n");
    for (;;)
        pause();
}

static void sig_usr(int signo) {
    printf("received signal: %d\n", signo);
    if (signo == SIGUSR1) 
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else 
        printf("received unknown signal: %d\n", signo);
}
