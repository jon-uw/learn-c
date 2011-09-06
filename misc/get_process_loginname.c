#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	char *login_name = getlogin();
	printf("Haha..we find it, Login name is: %s\n", login_name);
	exit(0);
}