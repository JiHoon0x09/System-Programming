#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "share.h"

#define MAX_PASSENGER 100
#define MAX_PASSENGER_IN_TRAIN 5
#define MAX_TICKET 20
#define MAX_TRAIN_THREAD 5
#define MIN_START_TRAIN 10
#define MAX_TICKET_THREAD 2

void *ticket_thread(int *);
void *train_thread(int *);

pthread_mutex_t gTicketMutex;
int gTicket[MAX_TICKET];
int gTicketIn;
int gTicketOut;

sem_t gStartTrainSem;
sem_t gInAvailableSem;
sem_t gOutAvailableSem;

pthread_t gTicketThread[MAX_TICKET_THREAD];
pthread_t gTrainThread[MAX_TRAIN_THREAD];
int gTicketThreadID[MAX_TICKET_THREAD];
int gTrainThreadID[MAX_TRAIN_THREAD];

key_t myqkey;
int myqid;

/* TODO: add variables here if you need */

int main(void)
{
	int i;


	/* create message queue */
	myqkey = ftok(MQ_KEY, 1);
	myqid = msgget(myqkey, IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
	printf("CT: message queue created (myqid=0x%x, key=%d)\n", myqid, myqkey);
	
    /* TODO: initialize mutex */

	/* TODO: initialize semaphore */

	/* TODO: create threads */

	pthread_exit(0);
}

void *ticket_thread(int *arg)
{
    /* TODO: add code here */
}

void *train_thread(int *arg)
{
    /* TODO: add code here */
}



