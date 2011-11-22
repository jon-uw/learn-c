#include "../common.h"

int main() {
	printf("info about you, user id: %d, group id: %d\n",
	    (int)getuid(), (int)getgid());
	exit(0);
}
