#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define SHMKEY 75

int shmid, i;

void CLIENT(){
	void* shm = NULL;
	int* data;
	int cnt;

	printf("1\n");
	shm = shmat(shmid, 0, 0);
	printf("1\n");
	data = (int*) shm;
	printf("1\n");
	cnt = 9;
	while(1){
		if(*data == -1){
			printf("(client) sent \n");
			*data = cnt;
			cnt--;
		}
		if(cnt == 0) break;
	}
	printf("1\n");
	shmdt(shm);
	printf("1\n");
	exit(0);
}

void SERVER(){
	void* shm = NULL;
	int* data;

	printf("0\n");
	shmid = shmget(SHMKEY, sizeof(int), 0666 | IPC_CREAT);
	printf("0\n");
	shm = shmat(shmid, 0, 0);
	printf("0\n");
	data = (int*) shm;
	printf("0\n");
	*data = -1;
	do{
		if(*data != -1){
			printf("(Server) recieved\n");
			*data = -1;
		}
	}while(*data == 0);
	printf("0\n");
	shmdt(shm);
	printf("0\n");
	shmctl(shmid, IPC_RMID, 0);
	printf("0\n");
	exit(0);
}

void main(){
	while ((i = fork()) == -1);
	if (!i) SERVER();
	while ((i = fork()) == -1);
	if (!i) CLIENT();
	wait(0);
	wait(0);
}
 