/*************************************************************************
	> File Name: sleep1.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sat 15 Oct 2016 07:52:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include <apue.h>
#include <unistd.h>

static void sig_alrm(int signo){
	
}

unsigned int sleep1(unsigned int seconds){
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		return (seconds);
	alarm(seconds);
	pause();
	return (alarm(0));

}
