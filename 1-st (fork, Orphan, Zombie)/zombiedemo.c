#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	pid_t childPid;
	int status;
	
	childPid = fork();
	if (childPid < 0) {		// fork() error
		printf("fork() error.\n");
		exit(-1);
	} else if (childPid == 0) {	// child process
		printf("Child(pid=%d): exit\n",getpid());
		exit(0); 
	} else {	// parent process
		printf("Parent(pid=%d): do nothing for 20 sec.\n", getpid());
		sleep(20);
		wait(&status);
		printf("Parent(pid=%d): child(pid=%d) exit code = %d\n", getpid(), childPid, (status & 0xff00)>>8);
		sleep(20);
	}
}
