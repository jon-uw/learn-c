#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void daemonize(void)
{
    pid_t pid;

    // become a session leader to lose controlling TTY
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) {
        // parent exit, make sure child is not a process group leader
        // so it can call setsid(2) to become a session leader
        exit(0);
    }
    printf("sesssion id is: %d\n", getsid(0));
    setsid();
    printf("new session id is: %d, pid is: %d, pgid is: %d\n", 
         getsid(0), getpid(), getpgrp());

    // make sure this DON'T prevent other to create file 
    //with some permission bit
    umask(0);


    // change current work directory
    if (chdir("/") < 0) {
        perror("cwd:");
        exit(1);
    }

    // attach file descriptors 0, 1 and 2 to /dev/null
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

int main(void)
{
    daemonize();
    while(1) {
        pause();
    }
}
