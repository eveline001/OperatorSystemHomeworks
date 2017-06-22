#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{ 
	int x;
	while((x = fork()) == -1);
	if(x == 0){
		printf("a");
		return 0;
	}
	wait(0);
	while((x = fork()) == -1);
	if(x == 0){
		printf("b");
		return 0;
	}
	wait(0);
	printf("c");
}