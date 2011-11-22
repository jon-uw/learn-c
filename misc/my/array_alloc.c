/**
 * simple array memory allocation from 'The C Programming Language'
 * section 5.4
 * limition: stack-based, must be freed as LIFO mode
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOCSIZE 10 * 1024 // size of availabe space

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) { // return pointer to n characers
	if (allocbuf + ALLOCSIZE >= allocp + n) {
		allocp += n;
		return allocp - n; // old allocp
	} else {
		return NULL; // not enough memory
	}
}

void afree(char *p) {
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
	    allocp = p;
}

int main() {
	char *test = alloc(9);
	strcpy(test, "hellowordddd"); //wrong now, 
	printf("test: %s\n", test);
	char *test2 = alloc(10);
	test2[0] = '\0';
    printf("test: %s\n", test);

	exit(0);
}

