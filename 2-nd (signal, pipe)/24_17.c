#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

main() 
{ 
    int status; 

    /* 부모 프로세스는 */
    if (fork()) { 
       /* 자식 프로세스가 종료되기를 기다림 */
       wait(&status); 
       printf("child process terminated with code %x\n", status); 
    /* 자식 프로세스는 */
    } else { 
       /* 3초 후에 SIGALRM 시그널을 자신에게 보냄 */
       alarm(3); 
       printf("looping forever...\n"); 
       while(1) 
          ; 
    } 
}