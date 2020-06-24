#include "apue.h"

int main(void)
{
    printf("uid = %ld , gid = %ld\n", (long)getuid(), (long)getpid());
    exit(0);
}
