#include "apue.h"
#include <stdio.h>
#include <sys/wait.h>

#define DEF_PAGER "/bin/more"

int main(int argc, char* argv[])
{
    int n;
    int fd[2];
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE* fp;

    if (argc < 2 || argc > 3)
        err_quit("usage: a.out <pager>|<pathname>");

    if ((fp = fopen(argv[2], "r")) == NULL)
        err_sys("can't open %s", argv[2]);
    if (pipe(fd) < 0)
        err_sys("pipe error");
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0)
    {
        close(fd[0]);
        while (fgets(line, MAXLINE, fp) != NULL)
        {
            n = strlen(line);
            if (write(fd[1], line, n) != n)
                err_sys("write error to pipe");
        }
        if (ferror(fp))
            err_sys("fgets error");

        close(fd[1]);

        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
        exit(0);
    }
    else
    {
        close(fd[1]);
        if (fd[0] != STDIN_FILENO)
        {
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
                err_sys("dup2 error to stdin");
            close(fd[0]);
        }

        if (argc == 2 && (pager = getenv("PAGER")) == NULL)
            pager = (char*)DEF_PAGER;
        else if (argc == 3)
            pager = argv[1];

        if ((argv0 = strrchr(pager, '/')) != NULL)
        {
            argv0++;
            printf("\n%s\n", argv0);
        }
        else
            argv0 = pager;

        char buf[80];
        getcwd(buf, sizeof(buf));
        printf("\n%s\n", buf);
        if (execl(pager, argv0, (char*)0) < 0)
            err_sys("execl error for %s", pager);
    }
    exit(0);
}
