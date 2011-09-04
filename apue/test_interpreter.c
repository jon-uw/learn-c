#include "common.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error");
	exit(-1);
    } else if (pid == 0) {
        execl("./testinterp", "testinterp", "myarg1", "MY args2", 
	(char *)0);
    }
    
    waitpid(pid, NULL, 0);
    exit(0);
}
