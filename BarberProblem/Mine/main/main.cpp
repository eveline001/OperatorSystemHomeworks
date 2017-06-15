#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstring>

const long SIZE_OF_BUFFER = 5;

int ConsumerID = 0;

bool Chair_Status[SIZE_OF_BUFFER];
int Chair_Record[SIZE_OF_BUFFER];
int Chair_Num = 5;
int CurChair;

HANDLE Mutex;
HANDLE BarberSemaphore;
HANDLE ConsumerSemaphore;
HANDLE CuttingSemaphore;

bool Cutting = false;

bool p_ccontinue = true;

void Cut(){
    printf("Consumer %d sit in chair %d is cutting hair\n", Chair_Record[CurChair], CurChair + 1);
    Sleep(3000);
    printf("Consumer %d finished\n", Chair_Record[CurChair]);
    Chair_Status[CurChair] = false;
    Chair_Num++;

    Sleep(3000);
}

DWORD WINAPI Barber(LPVOID lpPara){
    while(p_ccontinue){
        WaitForSingleObject(ConsumerSemaphore, INFINITE);
        WaitForSingleObject(CuttingSemaphore, INFINITE);
        WaitForSingleObject(Mutex, INFINITE);
        Cut();
        ReleaseMutex(Mutex);
        ReleaseSemaphore(BarberSemaphore, 1, NULL);
    }
    return 0;
}

DWORD WINAPI Consumer(LPVOID lpPara){
    while(p_ccontinue){
        WaitForSingleObject(Mutex, INFINITE);
        int itID = ++ConsumerID;
        ReleaseMutex(Mutex);

        for(int times = 1; times <= 3; times++){
            WaitForSingleObject(Mutex, INFINITE);
            if(Chair_Num){
                printf("Consumer %d in\n", itID);

                int itChair;
                for(int i = 0; i < SIZE_OF_BUFFER; i++){
                    if(!Chair_Status[i]){
                        itChair = i;
                        break;
                    }
                }

                printf("Sit in chair %d\n", itChair + 1);
                Chair_Status[itChair] = true;
                Chair_Record[itChair] = itID;
                Chair_Num--;

                ReleaseMutex(Mutex);
                ReleaseSemaphore(ConsumerSemaphore, 1, NULL);

                WaitForSingleObject(BarberSemaphore, INFINITE);
                WaitForSingleObject(Mutex, INFINITE);

                CurChair = itChair;
                Cutting = true;

                ReleaseMutex(Mutex);
                ReleaseSemaphore(CuttingSemaphore, 1, NULL);
            }else{
                printf("Consumer %d has left\n", itID);
                ReleaseMutex(Mutex);
                Sleep(2000);
            }
        }
        WaitForSingleObject(Mutex, INFINITE);
        printf("Consumer %d has left forever\n", itID);
        ReleaseMutex(Mutex);
        return 0;
    }
    return 0;
}

DWORD WINAPI Draw(LPVOID lpPara){
    while(p_ccontinue){
        WaitForSingleObject(Mutex, INFINITE);
        printf("\nCurrent Status\n");
        printf("========================================\n");
        printf("Chairs status:\n");
        for(int i = 0; i < SIZE_OF_BUFFER; i++) printf("%4d ", Chair_Status[i] ? 1 : 0);
        printf("\n");
        printf("Consumers in each chair:\n");
        for(int i = 0; i < SIZE_OF_BUFFER; i++) printf("%4d ", Chair_Status[i] ? Chair_Record[i] : 0);
        printf("\n");
        printf("========================================\n\n");
        ReleaseMutex(Mutex);

        Sleep(500);
    }
    return 0;
}

int main()
{
    Mutex = CreateMutex(NULL, FALSE, NULL);
    BarberSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
    ConsumerSemaphore = CreateSemaphore(NULL, 0, SIZE_OF_BUFFER, NULL);
    CuttingSemaphore = CreateSemaphore(NULL, 0, 1, NULL);

    const long CONSUMERS_NUM = 100;

    DWORD BarberPID;
    DWORD ConsumerPID[CONSUMERS_NUM];
    HANDLE hThreads
    CONSUMERS_NUM + 1];

    DWORD DrawPID;
    HANDLE DrawThread;

    memset(Chair_Status, false , sizeof(Chair_Status));

    printf("Pass Enter to exit.\n");

    try{
        if((hThreads[0] = CreateThread(NULL, 0, Barber, NULL, 0, &BarberPID)) == NULL) return -1;

        if((DrawThread = CreateThread(NULL, 0, Draw, NULL, 0, &DrawPID)) == NULL) return -1;

        for(int i = 1; i <= CONSUMERS_NUM; i++){
            if((hThreads[i] = CreateThread(NULL, 0, Consumer, NULL, 0, &ConsumerPID[i - 1])) == NULL) return -1;
        }
    }catch(...){
        exit(-1);
    }

    while(p_ccontinue){
        if(getchar()){
            p_ccontinue = false;
        }
    }
    return 0;
}
