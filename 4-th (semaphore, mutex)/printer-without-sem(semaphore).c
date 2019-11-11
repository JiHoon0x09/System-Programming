#include <stdio.h>       
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>     
#include <semaphore.h>     

#define PROCESS_NUM 2

static void *processThread(void *arg1)
{
  int id = *(int *)arg1;
  int i;
  
  for (i=0;i<1000; i++) {
    putchar(id+'a');
    usleep(10);
  }
}

int main(int argc, char **argv)
{
  pthread_t process[PROCESS_NUM];
  int processId[PROCESS_NUM];
  int i;
  
  for (i=0;i<PROCESS_NUM;i++) {
    processId[i] = i;
    pthread_create(&process[i], NULL, processThread, &processId[i]);
  }
  pthread_exit(0);
}
