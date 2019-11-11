#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>

#include "share.h"

/* TODO: add variables here if you need */
/* TODO: add functions here if you need */

int main(int argc, char *argv[])
{
	int i;

	char fname[MAX_FILE_NAME];
	FILE *fp;
	long sline;
	long nline;
	char c;
	int count;
	int found;

	int shmid;
	key_t key;
	char *shm;
	int shm_pos;

	int myqid;
	key_t myqkey;
	struct shmmsg wmsg;
	struct shmmsg rmsg;

	int timeout;
	
	if(argc != 1) {
		printf("S: wrong argument\n");
		exit(-1);
	}

    /* TODO: add code here */

	return 0;
}

