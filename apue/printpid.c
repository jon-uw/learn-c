#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Greeting from process ID %d\n", getpid());
    exit(0);
}
