#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_quit(int signo);

int main(void)
{
  sigset_t newmask, oldmask, pendmask;

  signal(SIGQUIT, sig_quit);

  // block SIGQUIT
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGQUIT);
  sigprocmask(SIG_BLOCK, &newmask, &oldmask);
  
  sleep(5);

  // SIGQUIT will remain pending
  sigpending(&pendmask);
  if (sigismember(&pendmask, SIGQUIT))
      printf("\nSIGQUIT pending\n");

  // reset sigmask which unblocks SIGQUIT
  sigprocmask(SIG_SETMASK, &oldmask, NULL);
  printf("SIGQUIT unblocked\n");

  sleep(5);
  exit(0);
}

static void sig_quit(int signo)
{
    printf("Caught SIGQUIT\n");
    signal(SIGQUIT, SIG_DFL);
}
