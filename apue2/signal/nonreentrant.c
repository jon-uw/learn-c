#include "../common.h"
#include <pwd.h>
static sigcount = 0;
static void send_usr1()
{
    sleep(1);
    kill(getpid(), SIGUSR1);
}

static void my_alarm(int signo)
{
    struct passwd *rootptr;
    printf("in signal handler: %d\n", sigcount++);
    if ((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root)");
    send_usr1();
}

int main()
{
    struct passwd *ptr;
    printf("process id is: %d\n", getpid());
    signal(SIGUSR1, my_alarm);
    send_usr1();
    for(; ;) {
        if ((ptr = getpwnam("gosudream")) == NULL)
            err_sys("getpwnam(gosudream)");
        if (strcmp(ptr->pw_name, "gosudream") != 0)
            printf("return value corrupted! pw_name = %s\n", ptr->pw_name);
    }

    return 0;
}
