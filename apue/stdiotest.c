#include "apue.h"

int main(void)
{
    int c;
    while ((c = getc(stdin)) != EOF)
        putc(c, stdout);

    exit(0);	
}
