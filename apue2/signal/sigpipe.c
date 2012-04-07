#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void sig_pipe(int signo);
static void sig_usr1(int signo);
static FILE *fp = NULL;
/**
 * if we don't trap SIGPIPE
 * while using pipe such as 'ps -ef | head -n 1',
 * then after the rear cmd executed, 
 * the process before it will get SIGPIPE if it still send output to stdout,
 * thus all the processes on the pipe exit
 * http://weibo.com/1822142792/ydf8RrQDZ?type=repost
 */
int main(void)
{
    int count = 0;
    fp = fopen("tmp.out", "w");
    if (signal(SIGPIPE, sig_pipe) == SIG_ERR) {
        printf("can't catch SIGPIPE\n");    
    }
    signal(SIGUSR1, sig_usr1);


    fprintf(fp, "start to test sigpipe...%d\n", getpid());
    fflush(fp);
    while (1)
    {
   //     fprintf(stdout, "useless -> %d\n", count++);
       // fflush(fp);
       pause();
    }

    return 0;
}


static void sig_pipe(int signo)
{
    fprintf(fp, "got SIGPIPE now, and sig_no is %d\n", signo); 
    fflush(fp);   
//    exit(0);
}

static void sig_usr1(int signo)
{
    fprintf(fp, "got SIGUSR1, try to print, wait for SIGPIPE\n");    
    fflush(fp);

    printf("got SIGUSR1, try to print\n");    
    fflush(stdout);
}
