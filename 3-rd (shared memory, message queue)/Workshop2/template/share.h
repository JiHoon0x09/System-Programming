#define SHMSZ 256
#define RETRY 100000000

#define SHM_KEY  "."
#define MQ_KEY  "/bin/login"

struct shmmsg {
	long mtype;
	int msg;
	int size;
};
#define MSIZE (sizeof(struct shmmsg)-sizeof(long)) 
#define MAX_MSG 10

#define MTYPE_C2S	1
#define MTYPE_S2C	2

#define MSG_REQ_FILE	1
#define MSG_ACK_FILE	2
#define MSG_NAK_FILE	3
#define MSG_SND_DATA	4
#define MSG_ACK_DATA	5
#define MSG_REQ_END	6
#define MSG_ACK_END	7

#define MAX_FILE_NAME 64

