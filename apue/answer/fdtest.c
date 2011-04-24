#include "../../language/common.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("test", O_RDWR| O_CREAT, 0755);
    while (1)
        sleep(1);
    
    return 0;
}
