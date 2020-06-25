#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
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
	key = ftok("./a.c",'a');
	if(key < 0){
		printf("creat key failure\n");
		return -2;
	}
	msgid = msgget(key,IPC_CREAT|0777);
	if(msgid < 0){
		printf("creat share memory failure\n");
		return -1;
	}
	printf("creat message queue  success msgid = %d\n",msgid);

	system("ipcs -q");
	sendbuf.type = 100;
	//init sendbuf
	while(1){
		memset(sendbuf.voltage,0,124);
		printf("please input message\n");
		fgets(sendbuf.voltage,124,stdin);

	//start write message to message queue
		msgsnd(msgid ,(void *)&sendbuf,strlen(sendbuf.voltage),0);	
		printf("%d\n",strlen(sendbuf.voltage));
		if(*sendbuf.voltage == 'q'&& strlen(sendbuf.voltage)== 2) break;
	}	
	
	//delete message queue
	msgctl(msgid,IPC_RMID,NULL);
	system("ipcs -q");
	
	

	return 0;
}
