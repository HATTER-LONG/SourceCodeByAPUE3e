#include <apue.h>

int 
main(void)
{
	off_t currpos;

	if ((currpos = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1)
		printf("CANNOT SEEK\n");
	else
		printf("seek ok!!,seek = %d\n",currpos);
	exit(0);
	
}
