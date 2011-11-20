#include "../common.h"

int main(void) {
	int n;
    if ((n = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1)
        printf("can not seek\n");
    else 
        printf("seek OK\n");

    printf("current file position is: %d\n", n);
    exit(0);
}
