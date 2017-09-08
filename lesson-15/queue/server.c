#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
struct mybuf
{
	long type;
	char voltage[124];
	char ID[4];
};

int main()
{	
	int err,err2;

   	int msgid;
	int readret;
	int key;
        int pid;
	struct mybuf sendbuf;
	struct mybuf recvbuf;
	key = ftok("./b.c",'a');
	if(key < 0){
		printf("creat key failure\n");
		return -2;
	}
	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0777);
	if(msgid < 0){
		msgid = msgget(key,0777);
		if(msgid < 0){
			printf("creat share memory failure\n");
			return -1;
		}
	}
	printf("creat message queue  success msgid = %d\n",msgid);

	system("ipcs -q");
	sendbuf.type = 200;
	sendbuf.voltage[0] = 0;
	err2 = msgsnd(msgid ,(void *)&sendbuf,124,0);	
	if(err2 < 0){
		printf("error:%d\n",err2);
	}

	pid = fork();
	if(pid >0){//parent process  write 100

		sendbuf.type = 100;
		//init sendbuf
 		while(1){
			memset(sendbuf.voltage,0,124);
			printf("please input message\n");
			fgets(sendbuf.voltage,124,stdin);
			
		//start write message to message queue
			err2 = msgsnd(msgid ,(void *)&sendbuf,124,0);	
			if(err2 < 0){
				printf("error:%d\n",err2);
		    }
			printf("%d\n",strlen(sendbuf.voltage));
			if(*sendbuf.voltage == 'q'&& strlen(sendbuf.voltage)== 2) break;
		}
		waitpid(pid,0);
		wait(NULL);
	}	
	if(pid == 0){//child process read 200
		recvbuf.type = 200;
		while(1){
		  memset(recvbuf.voltage,0,1024);
		  err = msgrcv(msgid,(void *)&recvbuf,124,200,MSG_NOERROR);
		  if(err == -1){
				printf("error:%d\n",errno);
		  }
		  printf("serives receive from message queue : %s\n",recvbuf.voltage);
		  if(*recvbuf.voltage == 'q'&& strlen(recvbuf.voltage)== 2) break;
		  
		}
		exit(0);
	}
	//delete message queue
	msgctl(msgid,IPC_RMID,0);
	system("ipcs -q");
	
	

	exit(0);
}
