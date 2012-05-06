#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("pid is: %d\n", getpid());
    printf("process group is[getpgrp()]:%d.\n", getpgrp());
    printf("process group is[getpgid()]:%d.\n", getpgid(0));

    return 0;
}
