#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/poll.h>

int main()
{
    fd_set rfds;
	struct pollfd *rfd;
    int retval;
    char buf[1024];
	rfd = (struct pollfd *)malloc(sizeof(struct pollfd));
	
	rfd->fd = STDIN_FILENO;
	rfd->events = POLLRDNORM;
	for(;;)
    {
        retval = poll(rfd, 1, 2000);
        /* Don't rely on the value of tv now! */
        if (retval)
        {
            printf("Data is available now.\n");
            if(FD_ISSET(STDIN_FILENO, &rfds))
            {
            
				read(STDIN_FILENO,buf,1024);
                printf("Read buf is: %s\n",buf);
            }
        }
        else
            printf("No data within 200 useconds.\n");
    }
    exit(0);
}
