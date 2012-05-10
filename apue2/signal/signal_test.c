#include <unistd.h>
#include <stdio.h>
#include <signal.h>

static void signal_handler(int signo)
{
    printf("USR1 received, signo is: %d.\n", signo);
}

int main()
{
    signal(SIGUSR1, signal_handler);
    printf("signal test, pid is: %d.\n", getpid());

    while (1)
        pause();

    return 0;
}
