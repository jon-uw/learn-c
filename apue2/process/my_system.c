#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int my_system(const char *cmdstr) //without signal handling
{
    pid_t pid;
    int status;
    
    if (cmdstr == NULL)
        return 1; // always a command processor with UNIX
    
    if ((pid = fork()) < 0) {
        status = -1;    
    } else if (pid == 0) {
        printf("execl pid is: %d. and cmdstr is'%s'\n", getpid(), cmdstr);
        execl("/bin/sh", "sh", "-c", cmdstr, NULL);
        _exit(127); //execl error
    } else {
        while (waitpid(pid, &status, 0) < 0) {
            printf("wait for pid: %d\n", pid);
            if (errno != EINTR) {
                status = -1; // error other than EINTR from waitpid()
                break;
            }    
        }   
    }

    return status;
}

int main(int argc, char *argv[]) {
    int status = my_system(argv[1]); //first argment as cmdstr    
    printf("\n\n'%s' => %d\n", argv[1], status);
    return 0;
}
