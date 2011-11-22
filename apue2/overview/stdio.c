#include "../common.h"

int main() {
	fprintf(stderr, "EOF is %d\n", EOF);

	// copy start
	int c;
	while ((c = getc(stdin)) != EOF) 
	    if (putc(c, stdout) == EOF)
	        err_sys("output error");
	
	if (ferror(stdin))
	    err_sys("input error");

	exit(0);
}
