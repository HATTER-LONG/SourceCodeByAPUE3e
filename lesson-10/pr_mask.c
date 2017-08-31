/*************************************************************************
	> File Name: mask.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sun 16 Oct 2016 01:34:19 PM CST
 ************************************************************************/

#include<stdio.h>
#include <apue.h>
#include <errno.h>
void pr_mask(const char *str){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0, NULL, &sigset) < 0){
		err_ret("sigprocmask error");
	}else{
		printf("%s",str);
		if(sigismember(&sigset, SIGINT))
			printf(" SIGINT");
		if(sigismember(&sigset, SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&sigset, SIGUSR1))
			printf(" SIGUSR1");
		if(sigismember(&sigset, SIGALRM))
			printf(" SIGALRM");

		printf("\n");
	}

	errno = errno_save;		//retore errno
}

volatile static int k = 0;
void sig_int(int signo){
	printf("start");
int i = 0;
	for(i = 0;i <10000 ; i++ )
		for(k = 0;k < 10000; k++)
			k+=i;
	pr_mask("::");
	printf("\nOK,%d\n",i);
}

int main(void){
	sigset_t	newmask,oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	signal(SIGQUIT,sig_int);
	pr_mask(":");
	while(1)
		pause();
	return 0;
}
