#include <stdio.h>
#include <unistd.h>

/**
 * see how the kernel execute interpreter file
 */
int main()
{
    //the args will shifted according to interpreter file argumeents count
    execlp("./pa.sh", "print args", "arg1", "Arg2", NULL);    
    return 0;
}
