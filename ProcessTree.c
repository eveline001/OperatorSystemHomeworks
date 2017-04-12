#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>

const char ProcDir[7] = "/proc/";
int Total;

typedef struct ProcInfo{
    int  ItsPid;
    int  FatherPid;
    char ItsName[256];
} ProcInfo;

ProcInfo Proc[4096];
int vis[4096];

char Path[1024], buff[1024], temp[1024];

int GetPid(char* str){
    int res = 0;
    char* s;
    s = strstr(str, "Pid");
    if(s != NULL){
        for(; *s != '\0'; s++){
            if(*s > '9' || *s < '0') break;
            res = res * 10 + (*s - '0');
        }
    }
    return res;
}

int GetPPid(char* str){
    int res = 0;
    char* s;
    s = strstr(str, "PPid");
    if(s != NULL){
        for(; *s != '\0'; s++){
            if(*s > '9' || *s < '0') break;
            res = res * 10 + (*s - '0');
        }
    }
    return res;
}

void GetName(char* re, char* str){
    char* s;
    s = strstr(str, "Name");
    if(s != NULL) for(; *s != '\n' && *s != '\0'; *re = *s, s++, re++);
}

void PrintProcTree(int fa, int de){
    int i, j;
    for(i = 0; i < Total; i++){
        if(!vis[i] && Proc[i].FatherPid == fa){
            vis[i] = 1;
            for(j = 0; j < de; j++) printf("    ");
            printf("%s\n", Proc[i].ItsName);
            PrintProcTree(Proc[i].ItsPid, de + 1);
        }
    }
}

int main(){
    int i, top;
    struct dirent **NameList;
    FILE *fp;
    int ItsPid, FatherPid;

    Total = 0;
    top = scandir(ProcDir, &NameList, 0, alphasort);
    for(i = 0; i < top; i++){
        if(NameList[i]->d_name[0] > '9' || NameList[i]->d_name[i] < '0'){
            Total = i + 1;
            break;
        }
    }
    printf("Total: %d\n", Total);
    for(i = 0; i < Total; i++){
        memcpy(Path, ProcDir, sizeof(ProcDir));
        strcat(Path, NameList[i]->d_name);
        strcat(Path, "/status");
        fp = fopen(Path, "r");
        while(!feof(fp)){
            fgets(buff, 1023, fp);
            ItsPid = FatherPid = 0;
            temp[0] = '\0';
            if(!ItsPid) ItsPid = GetPid(buff);
            if(!FatherPid) FatherPid = GetPPid(buff);
            if(temp[0] == '\0') GetName(temp, buff);
            if(ItsPid && FatherPid && temp[0] != '\0') break;
        }
        Proc[i].ItsPid = ItsPid, Proc[i].FatherPid = FatherPid;
        strcpy(Proc[i].ItsName, temp);
        fclose(fp);
    }
    memset(vis, 0, sizeof(vis));
    PrintProcTree(0, 0);
    return 0;
}
