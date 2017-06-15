#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char op[256];
char arg[256];
char str[1024];

int main()
{
    pid_t CurSon;

    while(1){
        scanf("%s", op);
        if(strcmp(op, "quit") == 0 || strcmp(op, "exit") == 0 || strcmp(op, "bye") == 0){
            printf("\nQuiting...Bye~");
            return 0;
        }
        if(strcmp(op, "help") == 0){
            printf("It's a fake shell~\n");
        }
        if(strcmp(op, "cd") == 0){
            scanf("%s", arg);
            sprintf(str, "cd %s", arg);
            system(str);
        }
        if(strcmp(op, "environ") == 0){
            system("env");
        }
        if(strcmp(op, "echo") == 0){
            scanf("%s", arg);
            sprintf(str, "echo %s", arg);
            system(str);
        }
        if(strcmp(op, "jobs") == 0){
            system("ps");
        }
        gets(arg);
        sprintf(str, "%s %s", op, arg);
        while((CurSon = fork()) < 0);
        if(CurSon == 0){
            system(str);
        }else{
            wait(NULL);
            printf("%s\n", str);
            printf("Complete...\n");
        }
    }
    return 0;
}
