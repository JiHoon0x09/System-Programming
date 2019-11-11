#include "mq.h"

int main(int argc, char *argv[]){
	int i, j;
	pid_t pid;
	int mtype = 0;
	int status;
	key_t key =0;
	size_t sz;
	int mq;
	struct mbuf msg;
	int fir, sec, total = 0;

	key = ftok("exam",0);
	mq = msgget(key, IPC_CREAT);
	//parent
	for(i=0; i<4; i++)
	if(pid=fork()){
		printf("P: <To %d-th C> Enter two num :",i);
		scanf("%d%d",&fir,&sec);
		mtype = i*2 + 1;
		msg.mtype = mtype;
		msg.first = fir;
		msg.second = sec;
		msg.result = 0;
		printf("P(%d): msg type : %d\n",getpid(),(int)msg.mtype);
		printf("P(%d): msg first : %d\n",getpid(),msg.first);
		printf("P(%d): msg second : %d\n",getpid(),msg.second);
		printf("P(%d): msg result : %d\n",getpid(),msg.result);
		msgsnd(mq, (void *)&msg, sizeof(struct mbuf)-4, 0);
		pid = waitpid(pid, &status, 0);		
		printf("P:%d-th Child %d terminated (status=%x)\n",i,pid,status);
		
		mtype = i*2 +2;
		msgrcv(mq,&msg,sizeof(struct mbuf)-4,mtype,0);
		printf("P(%d): msg type : %d\n",getpid(),(int)msg.mtype);
		printf("P(%d): msg first : %d\n",getpid(),msg.first);
		printf("P(%d): msg second : %d\n",getpid(),msg.second);
		printf("P(%d): msg result : %d\n",getpid(),msg.result);
		total += msg.result;
		printf("P: total = %d\n",total);
	}
	else{
		mtype = i*2 + 1;
		msgrcv(mq,&msg,sizeof(struct mbuf)-4, mtype, 0);

		printf("C(%d): msg type : %d\n",getpid(),(int)msg.mtype);
		printf("C(%d): msg first : %d\n",getpid(),msg.first);
		printf("C(%d): msg second : %d\n\n",getpid(),msg.second);
		for(j=msg.first; j<=msg.second; j++){
			msg.result+=j;
		}
		msg.mtype = i*2 +2;
		printf("C(%d): msg type : %d\n",getpid(),(int)msg.mtype);
		printf("C(%d): msg first : %d\n",getpid(),msg.first);
		printf("C(%d): msg second : %d\n",getpid(),msg.second);

		printf("C: msg result : %d\n",msg.result);
		msgsnd(mq, (void *)&msg, sizeof(struct mbuf)-4, 0);
		exit(2);	
	}

}
