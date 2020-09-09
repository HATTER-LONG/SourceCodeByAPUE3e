#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int msgid;
    msgid = msgget(IPC_PRIVATE, 0777);
    if (msgid < 0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat message queue  success msgid = %d\n", msgid);

    system("ipcs -q");

    // delete message queue
    msgctl(msgid, IPC_RMID, NULL);
    system("ipcs -q");



    return 0;
}
