#include <stdio.h>
#include <pthread.h>

int num = 0;
pthread_mutex_t mutex;
pthread_t CrtTid;
pthread_t tid[3];

void Thread_0(){
    pthread_t SelfTid = pthread_self();
    int times, status;
    for(times = 0; times < 10;){
	status = pthread_mutex_lock(&mutex);
	while(status != 0) status = pthread_mutex_lock(&mutex);
        if(pthread_equal(SelfTid, CrtTid)){
	    printf("A %u\n", (unsigned int)SelfTid);
            times = times + 1;
	    num = num + 1;
            CrtTid = tid[1];
	}
	pthread_mutex_unlock(&mutex);
    }
}


void Thread_1(){
    pthread_t SelfTid = pthread_self();
    int times, status;
    for(times = 0; times < 10;){
	status = pthread_mutex_lock(&mutex);
	while(status != 0) status = pthread_mutex_lock(&mutex);
        if(pthread_equal(SelfTid, CrtTid)){
	    printf("B %u\n", (unsigned int)SelfTid);
            times = times + 1;
	    num = num + 1;
	    CrtTid = tid[2];
	}	
	pthread_mutex_unlock(&mutex);
    }
}


void Thread_2(){
    pthread_t SelfTid = pthread_self();
    int times, status;
    for(times = 0; times < 10;){
	status = pthread_mutex_lock(&mutex);
	while(status != 0) status = pthread_mutex_lock(&mutex);
        if(pthread_equal(SelfTid, CrtTid)){
	    printf("C %u\n", (unsigned int)SelfTid);
            times = times + 1;
            num = num + 1;
	    CrtTid = tid[0];
	}
	pthread_mutex_unlock(&mutex);
    }
}

int main(){
    int i;

    while(pthread_mutex_init(&mutex, NULL) != 0);
    while(pthread_create(&tid[0], NULL, (void *)Thread_0, NULL) != 0);
    CrtTid = tid[0];
    while(pthread_create(&tid[1], NULL, (void *)Thread_1, NULL) != 0);
    while(pthread_create(&tid[2], NULL, (void *)Thread_2, NULL) != 0);
    for(i = 0; i < 3; i++){
	pthread_join(tid[i], NULL);
        printf("%d finished\n", i);
    }
    printf("All clear.\n");
    return 0;
}
