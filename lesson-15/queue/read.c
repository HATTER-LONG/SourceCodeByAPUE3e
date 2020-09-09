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
    int key;
    struct mybuf sendbuf;
    struct mybuf recvbuf;
    key = ftok("./a.c", 'a');
    if (key < 0)
    {
        printf("creat key failure\n");
        return -2;
    }
    msgid = msgget(key, IPC_CREAT | 0777);
    if (msgid < 0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat message queue  success msgid = %d\n", msgid);

    system("ipcs -q");
    // init sendbuf
    while (1)
    {
        memset(recvbuf.voltage, 0, 124);
        // start read message from message queue
        msgrcv(msgid, (void*)&recvbuf, 124, 100, 0);
        printf("receive data from message queue:%s\n", recvbuf.voltage);
        if (*recvbuf.voltage == 'q' && strlen(recvbuf.voltage) == 2)
            break;
    }

    // delete message queue
    msgctl(msgid, IPC_RMID, NULL);
    system("ipcs -q");



    return 0;
}
