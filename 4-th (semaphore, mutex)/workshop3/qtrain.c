#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MAX_PASSENGER 100
#define MAX_PASSENGER_IN_TRAIN 5
#define MAX_TICKET 20
#define MAX_TRAIN_THREAD 5
#define MIN_START_TRAIN 10

void *ticket_thread(int *);
void *train_thread(int *);

// person == ticket
pthread_mutex_t gTicketMutex;	// controls people in platform 
int gTicket[MAX_TICKET]; 		// total people in platform
int gTicketIn;					// total number of people which has got in platform
int gTicketOut;					// total number of people which has left platform

sem_t gStartTrainSem;			// train: waits until 10 people got in platform
sem_t gInAvailableSem;			// person enters platform while platform has less than 20 people
sem_t gOutAvailableSem;			// person leaves platform

pthread_t gTicketThread;
pthread_t gTrainThread[MAX_TRAIN_THREAD];
int gTicketThreadID;
int gTrainThreadID[MAX_TRAIN_THREAD];
int main(void)
{
	int i;

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



