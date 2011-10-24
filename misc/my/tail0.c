#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFUALT_N 10
#define MAX_LEN 50

int parse_arg(int argc, char* argv[], int *n, char* filename) {
	int is_f = 0;
	int i = 0;
	while (++i < argc) {
		if (strcmp(argv[i], "-f") == 0) {
			is_f = 1;
		} else if(strcmp(argv[i], "-n") == 0) {
			*n = atoi(argv[++i]);
		} else{
			strcpy(filename, argv[i]);
			printf("filename: %s\n", filename);
		}
	}
	return is_f;
}

int main(int argc, char* argv[]) {
	int n = DEFUALT_N;
	int is_f = 0;
	char filename[MAX_LEN] = {'\0'}; 

   
	is_f = parse_arg(argc, argv, &n, filename);
	if (*filename == '\0') {
		fprintf(stderr, "missing filename\n");
		exit(1);
	}
	printf("follow mode: %d, n is: %d, filename is: %s\n",
	    is_f, n, filename);


// using a savageman's method 
	// read the last n lines of a file
	/*
	 * 1. malloc a array of n strings
	 * 2. read a buffer that may contain n line of string from the end of the file
	 * 3. fill the array with n strings from tail to head
	   4. print out the array and free the space 
	*/

	// if (is_f)
	// for (;;) {
	/**
     * sleep in a short time
     * check whether the file is written 
     * print the added chars
	/	
	

	return 0;
} 