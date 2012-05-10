#include <unistd.h>
#include <stdio.h>

int main(void)
{
    FILE *file = fopen("pgid", "a+");
    fprintf(file, "pid is: %ld, process group id is: %ld\n", getpid(), getpgrp());
    fclose(file);
//    sleep(5 * 60);
    return 0;
}
