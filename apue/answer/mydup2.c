#include "common.h"
#include <fcntl.h>

/**
 * a ad-hoc solution to exercise 3.2
 * effeciency and system limit on open file numbers is the question
 */
int get_mydup2(int fd, int fd2) 
{
    int newfd;
    int result;
    if ((newfd = dup(fd)) < 0) {
        fprintf(stderr, "error getting a copy of file: %d\n", fd);
	perror("dup");
	return -1;
    }
    printf("in get mydup2, newfd is: %d\n", newfd);
    if (newfd == fd2) {
        printf("new fd is found now..\n");
        return newfd;
    }	
    sleep(5);
    result = get_mydup2(fd, fd2);	
    close(newfd);
    return result;
    
}

int mydup2(int fd, int fd2) {
    // need to assert if fd is opened
    // assert fd == fd2?
    if (fd < 0 || fd2 < 0) {
        fprintf(stderr, "file descriptors must be all non-negative");
	return -1;
    }
    close(fd2);  // lest fd2 is opened already
    return get_mydup2(fd, fd2);
}

int main(int argc, char *argv[]) {
    int fd2 = atoi(argv[1]);
    printf("start to run my dup2..: %d\n", fd2);

    // get fd2 from argument without error handling
    if (mydup2(STDIN_FILENO, fd2) > 0)
        printf("succeed in dup2 %d", STDIN_FILENO);

    //while (1) 
        //sleep(20);
}

