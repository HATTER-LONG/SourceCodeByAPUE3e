/*************************************************************************
	> File Name: sleep1.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sat 15 Oct 2016 07:52:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include <apue.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo){
	longjmp(env_alrm, 1);	
}

unsigned int sleep2(unsigned int seconds){
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		return (seconds);
	if(setjmp(env_alrm) == 0){
		alarm(seconds);
		pause();
	}
	return (alarm(0));

}

static void sig_int(int);

int main(void){
	unsigned int unslept;

	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal (SIGINT) error");
	unslept = sleep2(5);
	printf("sleep2 returned: %u\n", unslept);
	_exit(0);
}

static void sig_int(int signo){
	int i,j;
	volatile int k = 0;


	printf("\nsig_int starting\n");
	for(i = 0; i < 3000; i++)
		for(j = 0; j < 4000; j++)
			k+= i * j;
	printf("sig_int finished\n");
}
