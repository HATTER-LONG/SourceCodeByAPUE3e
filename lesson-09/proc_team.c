#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t id = fork();

    if (id < 0)
    {
        printf("fork error!!");
        return -1;
    }
    else if (id == 0)
    {
        printf("child id is :%d\n", getpid());
        while (1)
        {
            printf("child\n");
            sleep(2);
        }
    }
    else
    {
        printf("father id is :%d\n", getpid());
        while (1)
        {
            printf("father!\n");
            sleep(2);
        }
    }
    return 0;
}
