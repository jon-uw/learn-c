#include "common.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void) {
    pid_t pid;

    printf("process pid: %d\n", getpid());

    if ((pid = fork()) < 0) {
        printf("fork error\n");
	exit(-1);
    } else if (pid == 0) {
        printf("pid again: %d\n", getpid());
        execle("/home/gosudream/bin/path/echoall", "echoall",
	"arg2", (char *)0, env_init);
	exit(0);
    }

    if( waitpid(pid, NULL, 0) < 0) { // no error detect
        printf("wait error.\n");
        exit(-1);
    }
       

    printf("\n\nexeclp..\n");
    // ignore error and parent process
    if ((pid = fork()) == 0) {
        execlp("echoall", "bbyou_not_the_program name",
	"only a flag", (char *)0);
    }
    waitpid(pid, NULL, 0);
    exit(0);
}


