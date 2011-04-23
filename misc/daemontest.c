#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>

int init_daemon(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)
        return (-1);
    else if (pid != 0)
        exit(0);   //parent exit

    printf("pid is %d\n", getpid());
    syslog(LOG_INFO, "current daemon pid is: %d\n", pid);
    setsid(); // become session leader
    chdir("/");
    umask(0);
    close(0);  //close the standard io stream
    close(1);
    close(2);

    return 0;
}

void sig_term(int signo)
{
    if (signo = SIGTERM)
        syslog(LOG_INFO, "Won't terminate when receiver TERMINATE signal!");
}

int main(void) {
    if (init_daemon() < 0) 
    {
        printf("can't for a child process\n");
	exit(1);
    }
    openlog("daemontest", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "daemon started...\n");
    signal(SIGTERM, sig_term);
    closelog();

    while (1)
       sleep(1);
    return 0;
}

