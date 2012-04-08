#include <stdio.h>

int main(int argc, char *argv[])
{
    while (*argv != NULL) {
        printf("arglist=> %s\n", *argv);
        argv++;
    }

    return 0;
}

