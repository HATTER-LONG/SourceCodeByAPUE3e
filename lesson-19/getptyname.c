/*************************************************************************
	> File Name: getptyname.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Fri 25 Nov 2016 09:07:59 AM CST
 ************************************************************************/

#define _XOPEN_SOURCE
#include <stdio.h>
#include <apue.h>
#include <fcntl.h>

int main(void)
{
	int masterfd;
	char *salvedevice;

	if((masterfd = posix_openpt(O_RDWR|O_NOCTTY)) == -1){
		perror("posix_openpt() error");
		exit(0);
	}
	if(grantpt(masterfd) == -1){
		perror("grantpt() error");
		exit(0);
	}
	if(unlockpt(masterfd) == -1){
		perror("unlockpt() error");
		exit(0);
	}

	if((salvedevice = ptsname(masterfd)) == NULL){
		perror("ptsname() error");
		exit(0);
	}

	printf("salve device is: %s\n", salvedevice);
	exit(0);
}
