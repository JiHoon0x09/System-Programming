#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

#define slot 8
///////////////////////////////////////////
sem_t SLOT;
sem_t ITEM;
///////////////////////////////////////////
char data[100] = "Data Reception\n";

void *Producer(void *arg){
	int i = 1;
	int r_slot;
	printf("P start\n");
	while(slot){
		sem_getvalue(&SLOT, &r_slot);
		if(r_slot == 0){
			printf("P: Don't have the slot, WAIT!\n");
		}
	sem_wait(&SLOT);
	printf("P : %d-th Make Product\n",i++);
	sem_post(&ITEM);
	if(i==30) return 0;
	}
}

void *Consumer(void *arg){
	printf("C start\n");
	int i = 1;
	int r_item; //remain item
	while(slot){
		///////////////////////////////////////////
		sem_getvalue(&ITEM, &r_item);
		///////////////////////////////////////////
		if(r_item == 0){
			printf("C: Don't have the item, WAIT!\n");
		}
		///////////////////////////////////////////
		sem_wait(&ITEM);
		///////////////////////////////////////////
		printf("%d-th %s\n",i++,data);
		sem_post(&SLOT);
	if(i==30) return 0;
	}
}

int main(void){
	pthread_t tid[2];
	int i;
	///////////////////////////////////////////
	sem_init(&SLOT, 0, 8);
	sem_init(&ITEM, 0, 0);
	///////////////////////////////////////////
	pthread_create(&tid[0], NULL, Producer, NULL);
	pthread_create(&tid[1], NULL, Consumer, NULL);
	pthread_exit(1);
	printf("\t Main Thread End\n");
}


