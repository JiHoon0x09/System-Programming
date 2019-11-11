#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *func1(void *arg){
	int i;
	for(i=10; i<20;i++){
		printf("first Thread : %d\n",i);
		sleep(1);
	}

	printf("\t First Thread end\n");
}

void *func2(void *arg){
	int i;
	for(i=20; i<30;i++){
		printf("Second Thread : %d\n",i);
		sleep(1);
	}

	printf("\t Second Thread end\n");
}
void *func3(void *arg){
	int i;
	for(i=30; i<40;i++){
		printf("Thrid Thread : %d\n",i);
		sleep(1);
	}

	printf("\t Thrid Thread end\n");
}
void *func4(void *arg){
	int i;
	for(i=40; i<50;i++){
		printf("Forth Thread : %d\n",i);
		sleep(1);
	}

	printf("\t Forth Thread end\n");
}

int main(void){
	pthread_t tid[4];
	int status;
	int i;


	status = pthread_create(&tid[0],NULL,func1,NULL);
	status = pthread_create(&tid[1],NULL,func2,NULL);
	status = pthread_create(&tid[2],NULL,func3,NULL);
	status = pthread_create(&tid[3],NULL,func4,NULL);

	
	for(i=0; i<10; i++){
		printf("Main Thread : %d\n",i);
		sleep(1);
	}

	printf("\t Main Thread End");
}
