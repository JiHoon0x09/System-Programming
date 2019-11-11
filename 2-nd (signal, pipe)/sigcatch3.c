#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sigusr1Hdlr(int signo)
{
  printf("received SIGUSR1\n");
}

void sigusr2Hdlr(int signo)
{
  printf("received SIGUSR2\n");
}

int main(void)
{
	printf ("my pid = %d\n", getpid());
  if (signal(SIGUSR1, sigusr1Hdlr) == SIG_ERR) {
    printf("can't catch SIGUSR1\n");
  }
  if (signal(SIGUSR2, sigusr2Hdlr) == SIG_ERR) {
    printf("can't catch SIGUSR2\n");
  }
  while(1) { 
    sleep(1);
  }
  return 0;
}
