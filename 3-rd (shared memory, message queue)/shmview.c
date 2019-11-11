#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024		// 1 KB

int main(int argc, char **argv)
{
	key_t shmKey;
	int shmId;
	char *ptr1;
  char *ptr2;
	char cmd[80];
	
	shmKey = ftok("./shmview.c", 'R');
	shmId = shmget(shmKey, SHM_SIZE, 0644 | IPC_CREAT);
	if ((ptr1 = shmat(shmId, 0, 0)) == (void *)(-1)) {
		perror("shmat");
		exit(1);
	}
	sprintf(cmd, "pmap -x %d", getpid());
	system(cmd);

	if ((ptr2 = shmat(shmId, 0, 0)) == (void *)(-1)) {
		perror("shmat");
		exit(1);
	}
	sprintf(cmd, "pmap -x %d", getpid());
	system(cmd);
  
	shmdt(ptr1);
	shmdt(ptr2);  

	sprintf(cmd, "pmap -x %d", getpid());
	system(cmd);

	shmctl(shmKey, IPC_RMID, NULL);
	
	exit(0);
}
