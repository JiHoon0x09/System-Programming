#include <stdio.h>
#include <stdlib.h>

void func(void);

main(int argc, char *argv[])
{
    atexit(func);
    /* atoi는 정수 형태의 문자열을 정수로 변환하는 함수로 argv[1]이 "1"이면 1로 변환.
      argv[1]이 "0"이 되어야 if 조건이 참이 됨 */
    if(!atoi(argv[1]))
      /* 비정상적으로 프로세스를 종료하는데 atexit에 의해 등록된 함수는 실행되지 않음 */
       abort();
    exit(0); /* 정상적으로 프로세스를 종료하는데 atexit에 의해 등록된 함수가 실행 됨 */
}

void func(void)
{
    printf("run function\n");
}