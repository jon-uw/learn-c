#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// print out all the parameters
void print_str(char *first, ...)
{
    va_list ap;
    char *p;

    if (first == NULL)
        printf("No argument!\n");

    va_start(ap, first);
    while ((p = va_arg(ap, char *)) != NULL) 
        printf("argument: %s\n", p);

    va_end(ap);	
}
 
int main(void) 
{
    print_str("abc", "ddd", "hah", (char *) NULL);
    return 0;
}
