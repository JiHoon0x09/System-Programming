#include "mq.h"

int main(int argc, char **argv)
{
	size_t sz;
	int mtype = 0;
	int ftype, flag;
	key_t key = 0;
	int mq;
	struct mbuf msg;
	
	if (argc != 3) {
		printf("Usage: %s <msg type> <flag>\n", argv[0]);
		printf("       Flag: 0 - no flag, 1 - IPC_NOWAIT, 2 - MSG_NOERROR, 3 - MSG_EXCEPT\n");
		exit(0);
	}
	
	mtype = atoi(argv[1]);
	ftype = atoi(argv[2]);
	switch(ftype) {
		case 1:
			flag = IPC_NOWAIT;
			break;
		case 2:
			flag = MSG_NOERROR;
			break;
		case 3:
			flag = MSG_EXCEPT;
			break;
		default:
			flag = 0;
	}

	// get message queue
	key = ftok("./mqsend", 0);
	printf("key = 0x%08x\n", key);
	if ((mq = msgget(key, 0)) == -1) {	
		perror("msgget");
		exit(-1);
	}
	// get message from message queue
	if ((sz = msgrcv(mq, &msg, sizeof(struct mbuf)-4, mtype, flag)) == -1) {
		if ((flag == IPC_NOWAIT) && (errno == ENOMSG)) {
			printf("%s: no message in the mq\n", argv[0]);
			exit(0);
		} else {
			perror("msgrcv");
			exit(-1);
		}	
	}
	printf("msg type : %d\n", (int)msg.mtype);
	printf("msg body : %s\n", msg.mbody);
	printf("msg name : %s\n", msg.name);
	
	return 0;	
}
