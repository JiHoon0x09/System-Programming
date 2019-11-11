#include "shmhdr.h"

#define MSIZE 4
int shmid;

void sighandler(int signo){
	char *data;
	char strdata[100];
	data = shmat(shmid, (void*)0, 0);
	if(data == (char*)(-1)){
		perror("parent shmat error\n"); exit(1);
	}
	strncpy(strdata, data, MSIZE);
	printf("reading segment: \"%s\"\n\n", strdata);
	if(shmdt(data)==-1){
		perror("parent shmdr error\n"); exit(1);
	}
}
int main(int argc, char *argv[]){
	pid_t pid;
	key_t key;
	char *data;
	char strdata[100]= {0};
	int num = 1;
	if((key = ftok("ex1.c",'R'))== -1) { 
		perror("ftok error\n"); exit(1);
	}

	if((shmid = shmget(key, MSIZE, 0644|IPC_CREAT))==-1){
			perror("shmget error\n"); exit(1);
	}
	

	data = shmat(shmid, (void*)0, 0);
	if(data == (char*)(-1)){
		perror("shmat error\n"); exit(1);
	}

	pid = fork();
	if(pid){
		signal(SIGUSR1,sighandler);
		while(1)
			pause();

	}
	else{
		while(1){
			data = shmat(shmid, (void*)0, 0);
			if(data == (char*)(-1)){
				perror("child shmat error\n"); exit(1);
			}
			sprintf(strdata,"%d",num);
			printf("writing to segment: \"%s\"\n", strdata);
			strncpy(data, strdata, MSIZE);
			if(shmdt(data)==-1){
				perror("child shmdr error\n"); exit(1);
			}
			kill(getppid(),SIGUSR1);
			
			num++;
			sleep(1);
		}
	}
	return 0;
}
