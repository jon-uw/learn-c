#include <stdio.h>

int main()
{
    //should be: 
    //const char *p
    char *p = "abcd";
    *p = 'A'; // this will generate a segment fault

    return 0;
}
