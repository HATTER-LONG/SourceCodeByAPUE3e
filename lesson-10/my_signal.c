/*************************************************************************
	> File Name: my_signal.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sun 16 Oct 2016 03:56:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>

Sigfunc *signal(int signo, Sigfunc *func){
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if(signo == SIGALRM){
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}else{
		act.sa_flags |= SA_RESTART;
	}

	if(sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}
