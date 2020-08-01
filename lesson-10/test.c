#include "apue.h"
#include <signal.h>
#include <unistd.h>

static int sig_int(int signo) { printf("\nSIGINT OK\n"); }

int main(void)
{
    if (signal(SIGALRM, sig_int) == SIG_ERR)
        err_sys("error");
    pause();

    err_quit("OK");
    return 0;
}
