#include "shmhdr.h"

int main()
{
  int shmId;
  int childPid;

  int *calNum;
  char *shmPtr;

  if ((shmId = shmget((key_t)1234, sizeof(int), 0666|IPC_CREAT)) == -1) {
    perror("shmget");
    exit(0);
  }
  
  if ((childPid = fork()) == 0) {   // child
    if ((shmPtr = shmat(shmId, (void *)0, 0)) == (char *)-1) {
      perror("shmat failed : ");
      exit(0);
    }
    calNum = (int *)shmPtr;
    *calNum = 1;

    while(1) {
      *calNum = *calNum + 1;
      printf("child  : %d\n", *calNum); 
      sleep(1);
    }
  } 
  else if(childPid > 0) {   // parent
    if ((shmPtr = shmat(shmId, (void *)0, 0)) == (char *)-1) {
      perror("shmat failed : ");
      exit(0);
    }

    calNum = (int *)shmPtr;

    while(1) {
      sleep(1);
      printf("parent : %d\n", *calNum);
    }
  }
}
