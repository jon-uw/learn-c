#include <stdio.h>
#include <sys/select.h>

int main(void) {
    printf("max fd set number in select call(): %d\n", FD_SETSIZE);
    return 0;
}
