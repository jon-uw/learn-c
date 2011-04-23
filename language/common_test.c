#include "common.h"

int main(void)
{
    const char *test = "abc";
    printf("length of [%s]: %d\n", test, strlen(test));
    printf("length of [%s]: %d\n", test, sizeof(test));
    errno = EACCES;
    err_sys("error occured: %s", "hhhh");
    return -1;

}
