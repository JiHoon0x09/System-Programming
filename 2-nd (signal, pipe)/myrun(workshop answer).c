#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <string.h>

#define BUF_MAX 100
#define ARGC_MAX 10

pid_t ppid;
pid_t pid;

/* for pipe */
int pipefd[2];

int pipe_create(void)
{
	if(pipe(pipefd) == -1) {
		printf("pipe create pipe (errno = %d)\n", errno);
		return -1;
	}
	return 0;
}

int pipe_write(char *buf)
{
	if(write(pipefd[1], buf, strlen(buf)+1) == -1) {
		printf("can't write to pipe (errno = %d)\n", errno);
		return -1;
	}
	return 0;
}

int pipe_read(char *buf)
{
	if(read(pipefd[0], buf, BUF_MAX) == -1) {
		printf("can't read to pipe (errno = %d)\n", errno);
		return -1;
	}
	return 0;
}


/* for parent */
void sigusr1(int signo)
{
	printf("P: got SIGUSR1\n");

	/* send SIGUSR2 */
	kill(pid, SIGUSR2);
	printf("P: sent SIGUSR2\n");

	/* set alarm */
	alarm(5);
}

void sigalrm(int signo)
{
	printf("P: timeout\n");
	kill(pid, SIGKILL);
	printf("P: killed child (pid=%d)\n", pid);
}

/* for child */
void sigusr2(int signo)
{
	int ret;
	int i;
	int argc;
	char *p;

	/* for pipe */
	char buf[BUF_MAX];
	char *argv[ARGC_MAX];
	char *buf_p = buf;

	printf("C: got SIGUSR2\n");

	/* for pipe */
	if(pipe_read(buf) == -1) {
		exit(-1);
	}

	printf("C: read pipe [%s]\n", buf);
	for(i=0; i<ARGC_MAX; i++) {
		argv[i] = 0;
	}

	argc = 0;
	argv[argc] = buf_p;
	while(*buf_p) {
		if(*buf_p == ' ') {
			*buf_p = 0;
			argv[++argc] = ++buf_p;
		}
		else {
			buf_p++;
		}
	}

	printf("C: running \"");
	for(i=1; i<argc; i++) {
		printf("%s ", argv[i]);
	}
	printf("%s\"\n", argv[i]);
	fflush(stdout);

	ret = execvp(argv[1], argv+1);
	if(ret == -1) {
		printf("C: exec error (errno = %d)\n", errno);
		exit(-1);
	}
}

int main(int argc, char **argv)
{
	int i;

	/* for pipe */
	char buf[BUF_MAX];

	/* check arguments */
	if(argc < 2) {
		printf("too few arguments\n");
		exit(-1);
	}

	/* display command */
	strcpy(buf, argv[0]);
	for(i=1; i<argc; i++) {
		strcat(buf, " ");
		strcat(buf, argv[i]);
	}

	/* for pipe */
	if(pipe_create() == -1) {
		exit(-1);
	}

	/* for pipe */
	printf("P: write pipe [%s]\n", buf);
	if(pipe_write(buf) == -1) {
		exit(-1);
	}

	/* get pid */
	ppid = getpid();
	pid = fork();
	if(pid < 0) {
		printf("can't fork!\n");
	}
	else if(pid == 0) { /* child */
		printf("C: my pid is %d\n", getpid());
		printf("C: parent's pid is %d\n", ppid);

		/* set signal */
		signal(SIGUSR2, sigusr2);

		/* send SIGUSR1 to parent */
		kill(ppid, SIGUSR1);
		printf("C: sent SIGUSR1\n");

		pause();
	}
	else { /* parent */
		pid_t pid_temp;
		int status;

		printf("P: my pid is %d\n", ppid);
		printf("P: child's pid is %d\n", pid);

		/* set signal */
		signal(SIGUSR1, sigusr1);
		signal(SIGALRM, sigalrm);

		pause();

		pid_temp = wait(&status);
		printf("P: child (pid=%d) is terminated with status 0x%x\n", pid_temp, status);
	}

	return 0;
}

