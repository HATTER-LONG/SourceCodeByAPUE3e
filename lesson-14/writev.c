/*************************************************************************
	> File Name: wirtev.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Fri 28 Oct 2016 09:34:58 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	char * buf1 = (char *)malloc(10);
	char * buf2 = (char *)malloc(1024);
	struct iovec iov[2];

	memset(buf1, 0, 11);
	memset(buf2, 0, 1025);
	ssize_t nwritten;

	iov[0].iov_base = buf1;
	iov[0].iov_len = 10;
	iov[1].iov_base = buf2;
	iov[1].iov_len = 1024;

	readv(STDIN_FILENO, iov, 2);
	printf("call readv:\n");
	printf("buf1 is: %s\tlength is: %d\n", buf1, (int)strlen(buf1));
	printf("buf2 is: %s\tlength is: %d\n", buf2, (int)strlen(buf2));

	iov[0].iov_base = buf1;
	iov[0].iov_len = strlen(buf1);
	iov[1].iov_base = buf2;
	iov[1].iov_len = strlen(buf2);

	nwritten = writev(STDOUT_FILENO, iov, 2);
	
	free(buf1);
	free(buf2);

	exit(0);
}
