#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
        err_sys("fcntl F_GETFL error");

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0)
        err_sys("fcntl F_SETFL error");
}

int main(void)
{
    const int BUFFSIZE = 8192;

    int n;
    char buf[BUFFSIZE];

    set_fl(STDOUT_FILENO, O_SYNC);

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
        {
            err_sys("write error");
        }
    }

    if (n < 0)
        err_sys("read error");

    exit(0);
}