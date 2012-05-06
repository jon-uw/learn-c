#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) 
{
    printf("pid: %d\n", getpid());
    printf("parent pid: %d\n", getppid());
    printf("real user id: %d\n", getuid());
    printf("effective user id: %d\n", geteuid());
    printf("group id: %d\n", getgid());
    
    return 0;
}
