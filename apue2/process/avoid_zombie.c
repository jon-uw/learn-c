#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * from APUE2e 8.5
 * In UNIX System terminology, a process that has terminated,
 *  but whose parent has not yet waited for it, is called a zombie.
 */
int main(void)
{
   pid_t pid;
   if ((pid = fork()) == 0) { //first child
       if (pid = fork() > 0) {
           printf("first child(%d) exited..\n", getpid());
           exit(0); // parent from the second fork == first child
        }

        sleep(2); // wait for the first child to exit
        printf("second child, pid = %d, ppid = %d\n", getpid(), getppid());
        exit(0);
    } 

    if (waitpid(pid, NULL, 0) != pid)
        printf("can't wait for the first child");

    printf("parent exits, child is: %d.\n", pid);
    return 0;
}
