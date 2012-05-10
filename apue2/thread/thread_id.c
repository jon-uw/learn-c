#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s) 
{
  pid_t pid;
  pthread_t tid;
  
  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (ox%x)\n", s, (unsigned int)pid,
	 (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg)
{
  printids("new thread:\t");
  return NULL;
}

int main(void)
{
  int err;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0)
      printf("error create thread\n");

  printids("main thread:\t");
  sleep(1);
  exit(0);
}
