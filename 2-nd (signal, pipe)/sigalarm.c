#include <time.h>
#include "sigheader.h"

time_t tm;

void alarmHdlr(int signo)
{
	time(&tm);
	printf("SIGALRM received at %s\n", ctime(&tm));
	alarm(5);
}

void sigQuitHdlr(int signo)
{
	time(&tm);
	printf("SIGQUIT received at %s\n", ctime(&tm));
	printf("   set SIGALRM to default\n");
	signal(SIGALRM, SIG_DFL);
}

int main(int argc, char *argv)
{
	time(&tm);
	printf("Process %d starts at %s\n", getpid(), ctime(&tm));
	
	signal(SIGALRM, alarmHdlr);
	signal(SIGQUIT, sigQuitHdlr);
	
	alarm(5);
	while (1) ;
}
