#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int oc; // option character
	//char *b_opt_arg;
	//opterr = 0;

	while ((oc = getopt(argc, argv, ":ab:")) != -1) {
		switch (oc) {
			case 'a':
			    printf("there is an A\n");
			    break;
			case 'b':
			    printf("b option is: %s\n", optarg);
			    break;
			case '?':
			    printf("got an ?: invalid opt:%c\n", optopt);
			    break;
			case ':':
			    printf("got a :, missing option argument: %c\n", optopt);
			    break;
			default:
			    printf("error\n");
		}
	}

	printf("optind is %d\n", optind);

	exit(0);
}