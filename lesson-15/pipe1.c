/*************************************************************************
	> File Name: pipe1.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sun 30 Oct 2016 12:56:06 PM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>

int main(void){
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if(pipe(fd) < 0)
		err_sys("pipe error");
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid > 0){
		close(fd[0]);
		write(fd[1], "Hello World\n", 12);
	}else{
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	exit(0);
}
