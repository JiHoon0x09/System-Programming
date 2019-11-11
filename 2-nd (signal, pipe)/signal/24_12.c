#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

main(int argc, char *argv[]) 
{ 
    /* argv[1]번 프로세스에 SIGKILL 시그널 보냄 */
    kill(atoi(argv[1]), SIGKILL);   /* argv[1]은 문자열이므로 정수로 변환 */
}