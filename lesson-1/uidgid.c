#include <apue.h>

int 
main(void)
{
	printf("uid = %d , gid = %d\n",(long )getuid(),(long)getpid());
	exit(0);
}
