/*************************************************************************
	> File Name: read1.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sun 16 Oct 2016 10:02:09 AM CST
	> 读标准输入一行并输出到标准输出
 ************************************************************************/

#include<stdio.h>
#include <apue.h>

static void sig_alrm(int);

int main(void ){

	int n;
	char line[MAXLINE];
	
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal (SIGALRM) error");

	alarm(10);

	if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
		err_sys("read error");
	alarm(0);

	write(STDOUT_FILENO, line, n);

	exit(0);
}

static void sig_alrm(int signo){
	//Nothing to do!!
	
}
