#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
    /* fork 호출하기 전이므로 현재(부모) 프로세스에서만 한번 실행 */
    printf("one\n");
    /* fork 호출에 의해 자식 프로세스 생성 */
    if (fork() == -1)  /* fork에 실패하면 */
       perror("fork failed");
    else  /* fork에 성공하면 */
       printf("two\n");   /* 부모 프로세스와 자식 프로세스 각각이 실행 */
}