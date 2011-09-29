#include <stdio.h>

int main() {
    if ((char)0xff == -1) { 
        printf("little endian\n");
    } else {
        printf("big endian.\n");
    }

    return 0;
}
