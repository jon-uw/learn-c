#include <stdio.h>
#include <unistd.h>

int main() 
{
    //DON'T use $LOGNAME, `cas environment variables can be modified 
    printf("current user is: %s\n", getlogin());
    return 0;
}
