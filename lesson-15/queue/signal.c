#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
void myfun(int signum)
{
    int i = 0;
    while (i < 5)
    {
        printf("receive signum %d,i = %d\n", signum, i);
        sleep(1);
        i++;
    }
}

void myfun1(int signum)
{
    printf("receive signum %d", signum);
    wait(NULL);
}
int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid > 0)
    {

        int i = 0;
        signal(10, myfun);
        signal(17, myfun1);
        while (1)
        {
            printf("parents process things , i = %d\n", i);
            sleep(1);
            i++;
        }


        wait(NULL);
    }
    if (pid == 0)
    {
        sleep(10);
        kill(getppid(), 10);
        sleep(10);
        exit(0);
    }
    /*	printf("raise before!!\n");
     *		raise(9);
     *			printf("raise after\n");
     *			*/
    return 0;
}
