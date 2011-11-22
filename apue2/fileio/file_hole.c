#include "../common.h"
#include <fcntl.h>

/*
 * Default file access permissions for new files.
 */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void) {
	int fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0) 
	//if ((fd = open("file.hole", O_RDWR)) < 0)
	    err_sys("can't create file");

	if (write(fd, buf1, 10) != 10)
	    err_sys("buf1 write error");
	// offset is now 10

	if (lseek(fd, 16384, SEEK_SET) == -1)
	    err_sys("lseek error");
	// offset is now 16384

	if (write(fd, buf2, 10) != 10)
	    err_sys("buf2 write error");
    // offset is now 16394

    exit(0);
}