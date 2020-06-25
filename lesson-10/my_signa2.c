/*************************************************************************
	> File Name: my_signa2.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sun 16 Oct 2016 04:10:39 PM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>

Sigfunc * signal_intr(int signo, Sigfunc *func){
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
#ifdef	SA_INTERRUPT
	act.sa_flags |= SA_INTERRUPT;
#endif

	if(sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}
