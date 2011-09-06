#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    char **ptr;
    extern char **environ;

    printf("argment list:\n-------------------------\n");
    for (i = 0; i <  argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    printf("\n\nenviroment list:\n---------------------------\n");
    for (ptr = environ; *ptr != NULL; ptr++)
        printf("%s\n", *ptr);

    exit(0);
}
