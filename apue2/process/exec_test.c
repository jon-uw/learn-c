#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("in exec_test..\nusing execlp now==>\n\n");
    if (fork() == 0) {
        execlp("./a.out", "list cwd files", "-l", NULL);

        // process is replaced by `execlp`, so the following will not executed
        printf("\n\nthis won't show..\n");
    }

    //parent pause
    while (1)
        pause();

    return -1;
}
