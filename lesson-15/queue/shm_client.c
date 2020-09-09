#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
struct mybuf
{
    int pid;
    char buf[124];
};
void myfun(int signum)
{
    printf("signal recive\n");
    return;
}
int main()
{
    pid_t pid;
    int shmid;
    int key;
    struct mybuf* p;
    key = ftok("./shm_service.c", 'b');
    if (key < 0)
    {
        printf("creat key failure\n");
        return -2;
    }
    printf("creat key success key = %X\n", key);
    shmid = shmget(key, 128, IPC_CREAT | 0777);
    if (shmid < 0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat share memory success shmid = %d\n", shmid);

    signal(SIGUSR1, myfun);
    p = (struct mybuf*)shmat(shmid, NULL, 0);

    if (p == NULL)
    {

        printf("parent process : shmat function failure\n");
        return -3;
    }

    pid = p->pid;

    p->pid = getpid();
    printf("service pid = %d\n,mypid = %d\n", pid, p->pid);
    kill(pid, SIGUSR2);
    while (1)
    {
        pause();
        printf("client process recive data from share memory:%s\n", p->buf);
        kill(pid, SIGUSR2);
    }

    system("ipcs -m");
    shmctl(shmid, IPC_RMID, NULL);
    system("ipcs -m");
    return 0;
}
