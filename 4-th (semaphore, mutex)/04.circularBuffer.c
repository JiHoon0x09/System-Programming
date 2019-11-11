#include <pthread.h>

#define BUFSIZE 8

static int gBuf[BUFSIZE];
static int gBufin = 0;
static int gBufout = 0;
static pthread_mutex_t gBufLock = PTHREAD_MUTEX_INITIALIZER;

void getItem(int *item)
{
  pthread_mutex_lock(&gBufLock);
  *item = gBuf[gBufout];
  gBufout = (gBufout + 1) % BUFSIZE;
  pthread_mutex_unlock(&gBufLock);
}

void putItem(int item)
{
  pthread_mutex_lock(&gBufLock);
  gBuf[gBufin] = item;
  gBufin = (gBufin + 1) % BUFSIZE;
  pthread_mutex_unlock(&gBufLock);
}  
