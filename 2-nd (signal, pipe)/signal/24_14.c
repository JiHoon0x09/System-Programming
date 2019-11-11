#include <stdio.h>
#include <signal.h>
#include <unistd.h>

main() 
{ 
    int count=0;

    while(1) {
       printf("Hello World\n");
       count++;
       if(count == 3) {   /* count가 3이 되면 */
          /* 자기 자신에게 SIGINT 시그널 보냄 */
          raise(SIGINT);
       }
       sleep(2);   /* 2초 동안 정지 */
    }
}