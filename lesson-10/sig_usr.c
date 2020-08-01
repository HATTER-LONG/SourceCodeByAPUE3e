#include "apue.h"
#include <signal.h>
#include <stdio.h>


static void sig_usr(int);

int main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("can't catch  SIGUSR1");

    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("can't catch  SIGUSR");
    for (;;)
        pause();
}

static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
        printf("receivec SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("receivec SIGUSR2\n");
    else
        err_dump("receivec signal %d\n", signo);
}
