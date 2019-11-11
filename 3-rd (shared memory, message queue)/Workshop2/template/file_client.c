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

	char file_name[64];
	FILE *fp;

	int shmid;
	key_t key;
	char *shm;

	int myqid;
	key_t myqkey;
	struct shmmsg wmsg;
	struct shmmsg rmsg;
	
	char *fname;
	long sline;
	long nline;

	if(argc != 4) {
		printf("C: wrong argument\n");
		exit(-1);
	}

	fname = argv[1];
	sline = atoi(argv[2]);
	nline = atoi(argv[3]);
	printf("C: fname=%s, sline=%ld, nline=%ld\n", fname, sline, nline);
	
    /* TODO: add code here */

	return 0;
}

