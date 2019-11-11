#include "mq.h"
#define MAX_CHILD 4

struct cmdmsg {
  long mtype;
  int arg[2];
} gCmdBuf;

struct rspmsg {
  long mtype;
  int sum;
} gRspBuf;

int gMq;

void send_cmd(int, int, int);
void recv_cmd(int, int *, int *);
void send_resp(int, int);
int recv_resp(int);
void adder(int);

int main(int argc, char **argv)
{
	int i;
	int mtype = 0;
	key_t key = 0;
	int s, e;
	int childId[MAX_CHILD];
	int total = 0;
		
	key = ftok(argv[0], 0);		// create key value for message queue
	if ((gMq = msgget(key, IPC_CREAT)) == -1) {    // get message queue	
		perror("msgget");
		exit(-1);
	}

	for (i=0;i<MAX_CHILD;i++) {  // fork 4 childs
		if ((childId[i] = fork()) == 0) {  // code for child process
			adder(i);	
      exit(0);
		}
	}
	
	for (i=0;i<MAX_CHILD;i++) {	// send start & end values to each child
		s = rand()%1000;
		while ((e = rand() % 1000) <= s) ;
		send_cmd(i, s, e);		
	}  
	for (i=0;i<MAX_CHILD;i++) {	// receive sum from each child
		total += recv_resp(i);
	}	
  printf("Total sum = %d\n", total);
}

void send_cmd(int cid, int s, int e)
{
	gCmdBuf.mtype = (cid*2)+1;		// for parent -> child, use odd mtype (1,3,5...)
	gCmdBuf.arg[0] = s;
	gCmdBuf.arg[1] = e;
	
	if (msgsnd(gMq, (void *)&gCmdBuf, sizeof(struct cmdmsg)-4, 0) == -1) {
		perror("msgsnd");
		exit(-1);
	}	
}

void recv_cmd(int cid, int *s, int *e)
{
	int mtype;
  int sz;
	
	mtype = (cid*2)+1;		// for parent -> child, use odd mtype (1,3,5...)
	if ((sz = msgrcv(gMq, &gCmdBuf, sizeof(struct cmdmsg), mtype, 0)) == -1) {
		perror("msgrcv");
		exit(-1);
	}
  *s = gCmdBuf.arg[0];
  *e = gCmdBuf.arg[1];
}

void send_resp(int cid, int sum)
{
	gRspBuf.mtype = (cid*2)+2;		// for child -> parent, use even mtype (2, 4, 6, ...)
	gRspBuf.sum = sum;

	if (msgsnd(gMq, (void *)&gRspBuf, sizeof(struct rspmsg)-4, 0) == -1) {
		perror("msgsnd");
		exit(-1);
	}	
}

int recv_resp(int cid)
{
	int mtype;
  int sz;
	
	mtype = (cid*2)+2;		// for child -> parent, use even mtype (2, 4, 6, ...)
	if ((sz = msgrcv(gMq, &gRspBuf, sizeof(struct rspmsg), mtype, 0)) == -1) {
		perror("msgrcv");
		exit(-1);
	}
  return gRspBuf.sum;
}

void adder(int id)
{
  int start, end;
  int sum = 0;
  int i;
  
  recv_cmd(id, &start, &end);
  printf("child #%d: sum from %d to %d\n", id, start, end);
  for (i=start;i<end;i++) {
    sum += i;
  }
  send_resp(id, sum);
}
