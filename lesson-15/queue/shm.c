#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(void){
	int shmid;
	int key;
	char *p;

	key = ftok("./shm.c",'b');
	if(key < 0){
		printf("create key failure!!\n");
		return -2;
	}

	printf("create key success  key = %X\n", key);

	shmid = shmget(IPC_PRIVATE, 128, 0777);
	if(shmid < 0){
		printf("creat share memory failure\n");
		return -1;
	}
	printf("create  share memory success shmid = %d\n", shmid);
	
	system("ipcs -m");
	
	p = (char *)shmat(shmid, NULL, 0);
	if(p == NULL){
		printf("shmat function failure\n");
	}
	fgets(p ,128 ,stdin);
	printf("share memory data:%s\n",p);
	printf("second read share memory data:%s\n",p);
	
	shmdt(p);
	memcpy(p,"abcd",4);
	return 0;
}








