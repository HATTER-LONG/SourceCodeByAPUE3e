/*************************************************************************
	> File Name: select.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Wed 26 Oct 2016 08:30:46 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>

int main(void){
	fd_set	rfds;
	struct timeval	tv;
	int retval;
	char buf[1024];

	for(;;){
		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		retval = select(1, &rfds, NULL, NULL, &tv);

		if(retval){
			printf("Data is available now.\n");
			if(FD_ISSET(STDIN_FILENO, &rfds)){
				read(STDIN_FILENO, buf, 1024);
				printf ("Read buf is: %s\n",buf);
			}
		}else{
			printf("No data within five second.\n");
		}
	}

	exit(0);
}
