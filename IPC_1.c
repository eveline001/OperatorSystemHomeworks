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

	shm = shmat(shmid, 0, 0);
	data = (int*) shm;
	cnt = 9;
	while(1){
		if(*data == -1){
			printf("(client) sent \n");
			*data = cnt;
			cnt--;
		}
		if(cnt == 0) break;
	}
	shmdt(shm);
	exit(0);
}

void SERVER(){
	void* shm = NULL;
	int* data;

	shmid = shmget(SHMKEY, sizeof(int), 0666 | IPC_CREAT);
	shm = shmat(shmid, 0, 0);
	data = (int*) shm;
	*data = -1;
	do{
		if(*data != -1){
			printf("(Server) recieved\n");
			*data = -1;
		}
	}while(*data == 0);
	shmdt(shm);
	shmctl(shmid, IPC_RMID, 0);
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
 