#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int fd[2];
    int ret;

    char writebuf[] = "Hello World!!";
    char readbuf[128] = {0};
    char change[1] = {0};
    char message[1] = {1};
    char sendbuf[] = "fuck you man";
    printf("change = %d , message = %d\n", change[0], message[0]);

    ret = pipe(fd);
    if (ret < 0)
    {
        printf("creat pipe error !!");
        return -1;
    }

    pid = fork();

    if (pid == 0)
    {
        printf("this is child process pid = %d\n", pid);

        int i = 0;
        read(fd[0], change, 1);
        printf("child change = %d\n", change[0]);
        while (&change == 0)
            ;

        ret = read(fd[0], readbuf, 128);
        if (ret == 0)
        {
            printf("child raed error\n");
            return -1;
        }
        printf("child process OK!\nfather send string is %s\n", readbuf);
        ret = write(fd[1], sendbuf, 22);
        if (ret != 0)
            printf("child send ok");
        printf("child process close !!\n");
    }
    if (pid > 0)
    {
        printf("This is father process child pid = %d\n", pid);
        sleep(2);
        printf("send massage to child\n");
        write(fd[1], message, sizeof message);
        sleep(1);
        write(fd[1], writebuf, sizeof writebuf);
        waitpid(pid, NULL, 0);
        printf("close child process\n");
        read(fd[0], readbuf, 128);
        printf("father process OK!\nchild send string is %s\n", readbuf);
    }

    close(fd[0]);
    close(fd[1]);
    return 0;
}
