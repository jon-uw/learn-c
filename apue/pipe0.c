#include "../common.h"
#define MAX_LINE 1024

int main(void) {
    int n;
    int fd[2];
    pid_t pid;
    char line[MAX_LINE];

    if (pipe(fd) < 0) {
        err_sys("pipe error");
    }

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid > 0) { // parent
        printf("parent fd: %d, %d\n", fd[0], fd[1]);
        close(fd[0]);
	    write(fd[1], "so that's it\n", 13);
    } else {
        printf("child fd: %d, %d\n", fd[0], fd[1]);
        close(fd[1]);
	    n = read(fd[0], line, MAX_LINE);
	    printf("read %d bytes\n", n);
	    write(STDOUT_FILENO, line, n);
    } 

    exit(0);
}
