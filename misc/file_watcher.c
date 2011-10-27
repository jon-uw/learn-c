#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16)) //why add 16?

int main() {
	int length, i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];

	if ((fd = inotify_init()) < 0) {
		perror("inotify_init");
		exit(1);
	}
	wd = inotify_add_watch(fd, "/home/gosudream/tmp", 
	        IN_MODIFY | IN_CREATE | IN_DELETE);
	length = read(fd, buffer, BUF_LEN);
	if (length < 0)
	    perror("read change");

    printf("event size is: %d\n", EVENT_SIZE);
    printf("read length is: %d\n", length);
	while (i < length) {
		struct inotify_event *event = (struct inotify_event *)&buffer[i];
		printf("event length: %d\n", event->len);
		if (event->len) {
			if (event->mask & IN_CREATE) {
				if (event->mask & IN_ISDIR) {
					printf("Created directory: %s\n", event->name);
				} else {
					printf("file created: %s\n", event->name);
				}
			} else if (event->mask &IN_DELETE) {
			    printf("file(dir) is deleted: %s\n", event->name);
		    } else if (event->mask & IN_MODIFY) {
			    printf("file(dir) is modified: %s\n", event->name);
		    }
	    } else {
	    	fprintf(stderr, "bad watch event..\n");
	    }
	    i += EVENT_SIZE + event->len;
	    getchar();
	}

	inotify_rm_watch(fd, wd);
	close(fd);

	return 0;
}