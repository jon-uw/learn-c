#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int err = 0;
    uid_t uid = 501;
    if ((err = setuid(uid)) < 0) {
        printf("setuid(%d) returns a error: %d, errno is: %d.\n", uid, err, errno);
        perror("unable to setuid");    
    }

    return 0;
}
