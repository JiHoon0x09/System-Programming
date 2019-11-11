#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int gCnt = 10;

int main(int argc, char **argv)
{
	pid_t childPid;
	
	childPid = fork();
	if (childPid < 0) {		// fork() error
		printf("fork() error.\n");
		exit(-1);
	} else if (childPid == 0) {	// child process
		gCnt++;
		printf("Hello. I'm child (pid=%d) of process %d.\n", getpid(), getppid());
		printf("Global Count(pid=%d) = %d\n", getpid(), gCnt); 
	} else {	// parent process
		gCnt--;
		printf("Hi. I'm parent (pid=%d).\n", getpid());
		printf("Global Count(pid=%d) = %d\n", getpid(), gCnt); 
		wait();
	}
}
