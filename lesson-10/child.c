/*************************************************************************
	> File Name: child.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sat 15 Oct 2016 04:06:50 PM CST
 ************************************************************************/

#include<stdio.h>
#include<apue.h>
#include<sys/wait.h>

static void sig_cld(int);

int main(void){
	pid_t pid;

	if(signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if((pid = fork()) < 0){
		perror("fork error");
	}else if(pid == 0){
		sleep(2);
		_exit(0);
	}

	pause();
	exit(0);
}

static void sig_cld(int signo){
	pid_t pid;
	int status;

	printf("SIGCLD received\n");

	if(signal(SIGCLD, sig_cld) == SIG_ERR)
		perror("signal error");
	if((pid = wait(&status)) < 0)
		perror("wait error");

	printf("pid = %d\n",pid);
}
