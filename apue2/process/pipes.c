#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * simulate the `ls -l | wc -l` pipe
 */
int main()
{
    int pfds[2];
    if (pipe(pfds) == 0) {
        if (fork() == 0) {
            printf("child start: %d\n", getpid());
            //close(1); neednot do this, dup2 will close it
            dup2(pfds[1], 1); //redirect pfds[1] to stdout
            close(pfds[0]);  // input end
            printf("this will not show, but it'will add the wc output by 1\n");
            //execlp("ls", "ls", "-l", NULL);
            system("ls -l");
            sleep(5 * 60);
        } else {
            printf("parent started: %d\n", getpid());
            //close(0);
            dup2(pfds[0], 0);
            close(pfds[1]);
            //execlp("wc", "wc", "-l", NULL);    
            system("wc -l");
            sleep(5 * 60);
        }    
    }

    return 0;
}
