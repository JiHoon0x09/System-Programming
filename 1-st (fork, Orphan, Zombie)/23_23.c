#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXARG 7

main()
{
    char buf[256];
    char *arg[MAXARG];
    char *s;
    char *save;
    int argv;
    /* 공백, 탭, 개행으로 이루어진 구분자 선언 */
    static const char delim[] = " \t\n";
    int pid, status;

    /* 무한 반복 */
    while(1) {
       /* 프롬프트 출력 */
       printf("myshell: ");
       gets(buf);
       argv = 0;
       /* 문자열에서 delim을 기준으로 단어를 잘라냄 */
       s = strtok_r(buf, delim, &save);
       while(s) {
          arg[argv++] = s;
          s = strtok_r(NULL, delim, &save);
       }
       /* 인수가 더 없음을 의미하는 문자 추가 */
       arg[argv] = (char *)0;

       /* 프롬프트로 입력 받은 첫 번째 단어가 ‘quit’이면 while 문 벗어남 */
       if (!strcmp(arg[0], "quit"))
           break;

       if ((pid=fork()) == -1)   /* fork 호출에 실패하면 */
          perror("fork failed");
       /* 부모 프로세스는 자식 프로세스가 종료되기를 기다림 */
       else if (pid != 0) {
          pid = wait(&status);
       /* 자식 프로세스는 execvp를 이용하여 arg[0] 실행 */
       } else {
          execvp(arg[0], arg);
       }
    }
    exit(0);
}