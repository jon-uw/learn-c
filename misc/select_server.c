#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * a tcp server using select 
 */

#define TCP_PORT 9600
#define MAX_CLIENT 5
#define BUF_SIZE 200

int fd[MAX_CLIENT];
int conn_amount;

void show_client() {
    printf("client amount: %d\n", conn_amount);
    for (int i = 0; i < MAX_CLIENT; i++) {
        printf("NO.%d  => %d\n", i , fd[i]);
    }
    printf("\n\n");
}

void print_err(char* err_msg) {
    fprintf(stderr, "%s", err_msg);
    exit(0);
}

int main(void) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t sin_size;
    int yes;
    char buf[BUF_SIZE];
    int ret;
    int i;

    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        print_err("can't build socket\n");

    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, 
        &yes, sizeof(int)) == -1)
	print_err("can't set sock address reuse...\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
    if (bind(server_sock, (struct sockaddr *)&server_addr, 
        sizeof(struct sockaddr)) == -1)
	    print_err("can't bind to the server address\n");
    if (listen(server_sock, MAX_CLIENT) == -1) 
        print_err("can't listen on the server endpoint\n");

    printf("server started @:%d\n", TCP_PORT);

    fd_set fds;
    int max_sock = server_sock;
    struct timeval tv;
    conn_amount = 0;
    sin_size = sizeof(client_addr);
    
    while (1) {
        // initialize fds
	FD_ZERO(&fds);
	FD_SET(server_sock, &fds);

	// timeout settting
	tv.tv_sec = 10;
	tv.tv_usec = 0;

	for (i = 0; i < MAX_CLIENT; i++) {
	    if (fd[i] != 0)
	        FD_SET(fd[i], &fds);
	}
    
        ret = select (max_sock + 1, &fds, NULL, NULL, &tv);
	if (ret < 0) {
	    fprintf(stderr, "select return %d\n, will exit\n", ret);
	    break;
	} else if (ret == 0) {
	    //printf("select time out\n");
	    continue;
	} 

	printf("select return: %d\n", ret);

	for (i = 0; i < conn_amount; i++) {
	    if (fd[i] != 0 && FD_ISSET(fd[i], &fds)) {
	        ret = recv(fd[i], buf, sizeof(buf), 0);
		if (ret <= 0) {
		    printf("client [%d] closed\n", fd[i]);
		    close(fd[i]);
		    FD_CLR(fd[i], &fds);
		    fd[i] = 0;
		    conn_amount--;
	    } else {
	        if (ret < BUF_SIZE)
	        memset(&buf[ret], '\0', 1);
	        printf("client[%d] send: %s\n", fd[i], buf);
	        send(fd[i], buf, strlen(buf) + 1, 0);
	    }
	}
	}

       if (FD_ISSET(server_sock, &fds)) {
           if ((client_sock = accept(server_sock, 
	       (struct sockaddr *)&client_addr, &sin_size)) <= 0) {
	       perror("error occured while accept new socket\n");
	       continue;
	   }

       printf("accept new connection: %d\n", client_sock);
	   if (conn_amount < MAX_CLIENT) {
	       for (int i = 0; i < MAX_CLIENT; i++) {
	       	  printf("fd[%d] is %d\n", i , fd[i]);
	          if (fd[i] == 0) {
		          fd[i] = client_sock;
		          //printf("fd[%d] set to %d\n", i , fd[i]);
		          break;
			   }
		   }
	       conn_amount++;
	       if (client_sock > max_sock) 
	           max_sock = client_sock;
	       printf("new connection: client[%d]<< %s:%d\n",
	           client_sock, inet_ntoa(client_addr.sin_addr), 
	           ntohs(client_addr.sin_port));
       } else {
           send(client_sock, "bye", 4, 0);
	       close(client_sock);

           printf("max client now..abort this socket: %d\n", client_sock);
           continue;
       }

       show_client();
    }
	}
    return 0;
}




