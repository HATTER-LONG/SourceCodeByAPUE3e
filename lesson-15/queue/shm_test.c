#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

void myfun(int signum){
	printf("signal recive\n");
	return;
}

int main(void) {
	pid_t pid;
	int shmid;
	char *p;

	shmid = shmget(IPC_PRIVATE, 128, 0777);
	if(shmid < 0){
		printf("create share memory failure\n");
		return -1;
	}
	printf("create share memory success shmid = %d\n", shmid);

	pid = fork();
	if(pid > 0){
		signal(SIGUSR2, myfun);
		p = (char *)shmat (shmid , NULL, 0);

		if(p == NULL){
		
			printf("parent process : shmat function failure\n");
			return -3;
		}	
		while(1){
			fgets(p ,128 ,stdin);
			printf("parents process : share memory data:%s\n",p);
			kill(pid , SIGUSR1);
			pause();
			
		}		
			
		
	}

	if(pid == 0){
		signal(SIGUSR1,myfun);
		p = (char *)shmat(shmid , NULL ,0);	
		if(p == NULL){
			printf("child process shmat failure\n");
			return -3;
		}
	while(1){

		pause();
		printf("start read");
		printf("share memorydata :%s\n",p);
			kill(getppid(),SIGUSR2);
		}

	}

	system("ipcs -m");
	shmctl(shmid , IPC_RMID ,NULL); 
	system("ipcs -m");
	return 0;
}
