#include <stdio.h>       
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>     
#include <semaphore.h>     

#define SUMSIZE 100
#define BUFSIZE 8

int sum = 0;
sem_t items;
sem_t slots;

void putItem(int);
void getItem(int *);

static void *producer(void *arg1)
{
  int i;
  
  for (i=0;i<=SUMSIZE; i++) {
    sem_wait(&slots);
    putItem(i*i);
    sem_post(&items);
  }
  return NULL;
}

static void *consumer(void *arg1)
{
  int i, myitem;
  
  for (i=0; i<=SUMSIZE; i++) {
    sem_wait(&items);
    getItem(&myitem);
    sem_post(&slots);
    sum += myitem;
  }
  return NULL;
}

int main(int argc, char **argv)
{
  pthread_t producerThread;
  pthread_t consumerThread;
  int i, total;
  
  total = 0;
  for (i=1;i<=SUMSIZE;i++) {
    total += i*i;
  }
  printf("The checksum is %d\n", total);
  
  sem_init(&items, 0, 0);
  sem_init(&slots, 0, BUFSIZE);
  
  pthread_create(&producerThread, NULL, producer, NULL);
  pthread_create(&consumerThread, NULL, consumer, NULL);

  pthread_join(producerThread, NULL);
  pthread_join(consumerThread, NULL);
  printf("The threads produced the sum %d\n", sum);
}
