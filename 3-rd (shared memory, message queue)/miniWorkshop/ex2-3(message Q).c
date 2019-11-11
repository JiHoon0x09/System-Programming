#include "mq.h"
int mq;
void FunChild(int num){
	int mtype = num*2 +1;
	int i;
	struct mbuf msg;
	printf("C %d type waiting\n",mtype);
	msgrcv(mq, &msg, sizeof(struct mbuf)-4, mtype, 0);
	printf("%dth C : %d type msg receive\n\n",num,mtype);
	for(i=msg.first; i<=msg.second; i++)
		msg.result+=i;
	msg.mtype = num*2 + 2;

	msgsnd(mq,(void*)&msg, sizeof(struct mbuf)-4, 0);
}
int main(int argc, char *argv[]){
	int i;
	int fir, sec, total =0;
	size_t sz;
	int mtype;
	struct mbuf msg;
	pid_t pid;
	key_t key;

	key = ftok("exam",0);
	mq = msgget(key, IPC_CREAT);

	for(i=0; i<4; i++){
		if(!(pid = fork())){
			printf("%d-th C create\n");
			FunChild(i);
			exit(1);
		}
	}

	for(i=0; i<4; i++){
		msg.mtype = i*2 +1;
		msg.first = rand()%20;
		msg.second = msg.first + rand()%10;
		msg.result = 0;
		printf("P : %d type msg send\n",msg.mtype);
		msgsnd(mq,(void*)&msg, sizeof(struct mbuf)-4,0);
	}

	for(i=0; i<4; i++){
		mtype = i*2 +2;
		msgrcv(mq, &msg, sizeof(struct mbuf)-4, mtype, 0);
		printf("%d type msg receive\n",mtype);
		total += msg.result;
		printf("P: total = %d\n",total);
	}


}
