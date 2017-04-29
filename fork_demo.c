#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{ 
	int x;
	while((x = fork()) == -1);
	if(x == 0) printf("a");
	else printf("b");
	printf("c");
}