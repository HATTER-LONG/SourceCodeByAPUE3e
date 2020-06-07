#include "apue.h"
#include <fcntl.h>

int main(void)
{
    int oldfd;
    oldfd = open("app_log", O_RDWR | O_CREAT, 0644);
    dup2(oldfd, STDOUT_FILENO);
    close(oldfd);
    printf("oldfd = %d\n", oldfd);
    return 0;
}
