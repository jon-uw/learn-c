// example from: 
// https://banu.com/blog/2/how-to-use-epoll-a-complete-example-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 64

static int make_socket_non_blocking(int sfd) {
	int flags, s;
	flags = fcntl(sfd, F_GETFL, 0);
	if (flags == -1) {
		perror("Fcntl");
		return -1;
	}
	flags |= O_NONBLOCK;
	s = fcntl(sfd, F_SETFL, flags);
	if (s == -1) {
		perror("fcntl");
		return -1;
	}
	return 0;
}

static int create_and_bind(char *port) {
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; // IPV4 or IPV6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	s = getaddrinfo(NULL, port, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
		    continue;
		s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0) 
		    break; // bind ok
		printf("can't bind...\n");
		close(sfd);
	}

	if (rp == NULL) {
		fprintf(stderr, "Could not bind\n");
		return -1;
	}
	freeaddrinfo(result);
	return sfd;
}

static int create_and_bind2(char *port) {
	struct sockaddr_in servaddr;
	int listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener == -1) {
		perror("can't create socket..\n");
		return -1;
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(port));
	if (bind(listener, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		perror("bind");
		return -1;
	}
	return listener;
}

int main(int argc, char *argv[]) {
	int sfd, s;
	int efd;
	struct epoll_event event;
	struct epoll_event *events;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s [PORT]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

    // listen to the specified address
	sfd = create_and_bind(argv[1]); // listener fd
	if (sfd == -1) 
	    abort();
    if (make_socket_non_blocking(sfd) == -1)
        abort();
    if (listen(sfd, SOMAXCONN) == -1) {
    	perror("listen");
    	abort();
    }

    // init epoll
    if ((efd = epoll_create1(0)) == -1) { // after 2.6.8, arg is useless
    	perror("epoll_create");
    	abort();
    }
    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event) == -1) {
    	perror("epoll_ctl");
    	abort();
    }

    // Buffer where events are returned
    events = calloc(MAX_EVENTS, sizeof(event));

    // event loop
    for (;;) {
    	int n, i;
    	n = epoll_wait(efd, events, MAX_EVENTS, -1);
    	for (i = 0; i < n; i++) {
    		if ((events[i].events & EPOLLERR) || 
    		    (events[i].events & EPOLLHUP) ||
    		    !(events[i].events & EPOLLIN)) {
    		    fprintf(stderr, "epoll error\n");
    		    close(events[i].data.fd); // epoll will remove closed fd     
    		    continue;
    		}

    		if (sfd == events[i].data.fd) {
    			// comes new connection
    			for (;;) {
    				struct sockaddr in_addr;
    				socklen_t in_len;
    				int infd;
    				char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

    				in_len = sizeof(in_addr);
    				infd = accept(sfd, &in_addr, &in_len);
    				if (infd == -1) {
    					if (errno == EAGAIN || errno == EWOULDBLOCK) {
    					    break;  // all incoming connections processed
    				    } else {
    					    perror("accept");
    					    break;
    					}
    				}
    				s = getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf),
    				    sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);
    				if (s == 0)
    				    printf("accept connection on descriptor: %d"
    				        "(host = %s, port = %s)\n", infd, hbuf, sbuf);
    				
    				if (make_socket_non_blocking(infd) == -1)
    				    abort();
    				event.data.fd = infd;
    				event.events = EPOLLIN | EPOLLET;
    				s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
    				if (s == -1) {
    					perror("epoll_ctl");
    					abort();
    				} 
    			}
    		} else {
    			// remember the pitfall of ET
    			int done = 0;
    			for (;;) {
    				ssize_t count;
    				char buf[512];
    				count = read(events[i].data.fd, buf, sizeof(buf));
    				if (count == -1) {
    					if (errno != EAGAIN) {
    						perror("socket read");
    						done = 1;
    					}
    					break;
    				} else if (count == 0) {
    					done = 1;
    					break;
    				}

    				s = write(1, buf, count);
    				if (s == -1) {
    					perror("write");
    					abort();
    				}
    			}
    			if (done) {
    				printf("Closing connection on descriptor: %d\n", events[i].data.fd);
    				close(events[i].data.fd);
    			}
    		}
    	}
    }

    free(events);
    close(sfd);
    close(efd);

    return 0;

}
