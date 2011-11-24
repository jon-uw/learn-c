#include "../common.h"
#include <fcntl.h>

void set_fl(int fd, int flags) { // flags are file satus flags to turn on
	int val;

	// must store the original file status flags
	if ((val = fcntl(fd, F_GETFL, 0)) < 0) 
	    err_sys("fcntl F_GETFL error"); 
	val |= flags; // turn on flags
	if (fcntl(fd, F_SETFL, val) < 0)
	    err_sys("fcntl F_SETFL error");
}