#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

struct mybuf
{
	int pid;
	char buf[124];
};

void myfun(int  signum){
	printf("signal revive\n");
	return ;
}

int main(void){
	pid_t pid;
   	int shmid;
	int key;
	struct mybuf *p;
	key = ftok("./shm_service.c",'b');
	if(key < 0 ){
		printf("creat key failure\n");
		return -2;
	}	
	printf("creat key success key = %X\n",key);
	shmid = shmget(key , 128 ,IPC_CREAT | 0777);	
	if(shmid < 0){
		printf("creat share memory failure\n");
		return -1;
	}
	printf("creat share memory success shmid = %d\n",shmid);
	
	signal(SIGUSR2,myfun);
	p = (struct mybuf *)shmat(shmid , NULL ,0);
	if(p == NULL){
		
		printf("parent process : shmat function failure\n");
		return -3;
	}	

	p->pid = getpid();
	printf("my pid = %d\n",p->pid);
	pause();

	pid = p->pid;
	printf("clint pid = %d\n",pid);
	while(1){
		fgets(p->buf ,128 ,stdin);
		printf("parents process : share memory data:%s\n",p->buf);
		kill(pid , SIGUSR1);
		pause();
			
	}
	
	system("ipcs -m");
	shmctl(shmid , IPC_RMID ,NULL); 
	system("ipcs -m");
	return 0;
}










