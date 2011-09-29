#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char * abc  = "abc";
    char out[strlen(abc) + 2];
    sprintf(out, "%sx", abc);
    printf("out is: [%s], length: %d\n", out, strlen(out));
    return 0;
}
