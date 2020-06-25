#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	pid_t pid;
	pid = fork();
	if(pid > 0){
		sleep(8);
		if(waitpid(pid, NULL, 0) == 0)
			kill(pid , 9);
	}
	
	if(pid == 0){
		printf("raise function before\n");
		raise(SIGTSTP);
		printf("raise function after\n");
		exit(0);
	}
	return 0;
}
