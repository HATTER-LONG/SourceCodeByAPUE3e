#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
struct mybuf
{
    long type;
    char voltage[124];
    char ID[4];
};

int main()
{
    int msgid;
    int readret;
    struct mybuf sendbuf;
    struct mybuf recvbuf;
    msgid = msgget(IPC_PRIVATE, 0777);
    if (msgid < 0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat message queue  success msgid = %d\n", msgid);

    system("ipcs -q");
    // init sendbuf
    sendbuf.type = 100;
    printf("please input message\n");
    fgets(sendbuf.voltage, 124, stdin);

    // start write message to message queue
    msgsnd(msgid, (void*)&sendbuf, strlen(sendbuf.voltage), 0);

    // start read message queue
    memset(recvbuf.voltage, 0, 124);
    readret = msgrcv(msgid, (void*)&recvbuf, 124, 100, 0);
    printf("recv  = %s ,", recvbuf.voltage);
    printf("readret = %d\n", readret);

    // delete message queue
    msgctl(msgid, IPC_RMID, NULL);
    system("ipcs -q");

    return 0;
}
