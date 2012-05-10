#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("pid=%d, ppid=%d, pgrpid=%d, sessionid=%d\n",
        getpid(), getppid(), getpgrp(), getsid(0));
    daemon(1, 1); //chdir("/"), redirect 0, 1 and 2 to /dev/null
    printf("become daemon now!\n");
    printf("pid=%d, ppid=%d, pgrpid=%d, sessionid=%d\n",
        getpid(), getppid(), getpgrp(), getsid(0));
    while (1);
}
