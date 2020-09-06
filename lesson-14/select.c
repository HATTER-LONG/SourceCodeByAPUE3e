#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    char buf[1024];

    for (;;)
    {
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        retval = select(1, &rfds, NULL, NULL, &tv);

        if (retval)
        {
            printf("Data is available now.\n");
            if (FD_ISSET(STDIN_FILENO, &rfds))
            {
                read(STDIN_FILENO, buf, 1024);
                printf("Read buf is: %s\n", buf);
            }
        }
        else
        {
            printf("No data within five second.\n");
        }
    }

    exit(0);
}
