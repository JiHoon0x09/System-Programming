#include "mq.h"

int main(int argc, char **argv)
{
	int i;
	int mtype = 0;
	key_t key = 0;
	int mq;
	struct mbuf msg;
	
	if (argc != 4) {
		printf("Usage: %s <msg type> <msg> <sender name>\n", argv[0]);
		exit(0);
	}
	
	if ((mtype = atoi(argv[1])) <= 0) {   // mtype must be positive integer
		printf("%s: Can not use '%d' for message type.\n", argv[0], mtype);
		exit(-1);
	}
	// get message queue	
	key = ftok("./mqsend", 0);
	printf("key = 0x%08x\n", key);

	if ((mq = msgget(key, IPC_CREAT)) == -1) {	
		perror("msgget");
		exit(-1);
	}
	// prepare message to send
	msg.mtype = mtype;
	strncpy(msg.mbody, argv[2], 31);
	msg.mbody[31] = '\0';
	strncpy(msg.name, argv[3], 15);
	msg.name[15] = '\0';	
	// send message to message queue
	if (msgsnd(mq, (void *)&msg, sizeof(struct mbuf)-4, 0) == -1) {
		perror("msgsnd");
		exit(-1);		
	}
	printf("msg type : %d\n", (int)msg.mtype);
	printf("msg body : %s\n", msg.mbody);
	printf("msg name : %s\n", msg.name);
}
