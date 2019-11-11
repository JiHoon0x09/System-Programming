#include <stdio.h>
#include <unistd.h>

main()
{
    printf("Running ls with execl\n");
    /* 첫 번째 인수가 경로 이름이고 명령라인 인수들을 나열.
      (char *)0은 인수가 더 이상 없음을 의미 */
    execl("/bin/ls", "ls", (char *)0);
    /* 이후 문장은 실행되지 않음 */
    printf("execl failed to run ls\n");
    exit(0);
}