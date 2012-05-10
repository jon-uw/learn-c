#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void alarm_handler(int signo)
{
    struct passwd *rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        perror("getpwnam(root) error");
        exit(EXIT_FAILURE);
    }
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;
//    signal(SIGUSR1, alarm_handler);
    signal(SIGALRM, alarm_handler);
    alarm(1);
    for (;;) {
        if ((ptr = getpwnam("demon")) == NULL) {
            perror("error getpwname(sar)");
            exit(EXIT_FAILURE);
        }
        if (strcmp(ptr->pw_name, "demon") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }

    exit(EXIT_SUCCESS);
}

