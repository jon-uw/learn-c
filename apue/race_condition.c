#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void charatatime(char *);

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        printf("error fork a child process, got: %d\n", pid);
	return -1;
    } else if (pid == 0) {
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
    }

    exit(0);
}

static void charatatime(char *str) {
    char *ptr;
    int c;
    setbuf(stdout, NULL); /*set unbuffered*/

    for (ptr = str; (c = *ptr++)!=0;)
        putc(c, stdout);
}
