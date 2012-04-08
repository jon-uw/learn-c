#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    if ((pid = fork()) == 0)
        exit(0); // zombie: it's not waited by its parent

    while (1) {
        printf("paused now.\n");
        pause(); //pause to 'ps -ef' in order to see zombie child
    }
    return 0;
}


