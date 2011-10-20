#include <stdio.h>
#include <sys/socket.h>

int main(void) {
    printf("socket backlog upper limit: %d\n", SOMAXCONN);
    return 0;
}
