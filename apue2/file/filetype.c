#include "../common.h"
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	int i;
	struct stat buf;
	char *filetype;

	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			err_ret("lstat error");
			continue;
		}

		if (S_ISREG(buf.st_mode))
		    filetype = "regular";
		else if (S_ISDIR(buf.st_mode))
		    filetype = "directory";
		else if (S_ISCHR(buf.st_mode))
		    filetype = "character special";
		else if (S_ISBLK(buf.st_mode))
		    filetype = "block special";
		else if (S_ISFIFO(buf.st_mode))
		    filetype = "fifo";
		else if (S_ISLNK(buf.st_mode))
		    filetype = "symbolic link";
		else if (S_ISSOCK(buf.st_mode))
		    filetype = "socket";
		else 
		    filetype = "** unknown mode **";
		printf("%s\n", filetype);
	}

	exit(0);
}