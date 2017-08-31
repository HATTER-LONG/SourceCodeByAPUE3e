#include <stdio.h>
#include <apue.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void){
	int oldfd;
	oldfd = open("app_log",O_RDWR | O_CREAT,0644);
	dup2(oldfd,1);
	close(oldfd);
	printf("111");	

	return 0;	

}
