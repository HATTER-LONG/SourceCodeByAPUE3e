#include "apue.h"
#include <errno.h>
#include <sys/wait.h>
void pr_exit(int status)
{

    if (WIFEXITED(status))
        printf("normal termination , exut status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))

        printf("normal termination , exut status = %d\n", WTERMSIG(status)
#ifdef WCOREDUMP
                                                              ,
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
        );
#endif

    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int m_system(const char* cmdstring) /* version without signal handling */
{
    pid_t pid;
    int status;

    if (cmdstring == NULL)
        return (1); /* always a command processor with UNIX */

    if ((pid = fork()) < 0)
    {
        status = -1; /* probably out of processes */
    }
    else if (pid == 0)
    { /* child */
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
        _exit(127); /* execl error */
    }
    else
    { /* parent */
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1; /* error other than EINTR from waitpid() */
                break;
            }
        }
    }

    return (status);
}


int main(void)
{
    int status;

    if ((status = m_system("date")) < 0)
        err_sys("system() error");

    pr_exit(status);

    if ((status = m_system("nosuchcommand")) < 0)
        err_sys("system() error");

    pr_exit(status);

    if ((status = m_system("who; exit 44")) < 0)
        err_sys("system() error");

    pr_exit(status);

    exit(0);
}
