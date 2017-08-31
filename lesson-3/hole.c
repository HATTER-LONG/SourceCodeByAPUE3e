#include "apue.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
	int		fd;

	int 		byte;
	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");

	if ((byte = write(fd, buf1, 10)) && byte != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */

	printf("byte = %d\n",byte);
	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != 10)
		err_sys("buf2 write error");
	/* offset now = 16394 */
	
//	printf("buf1 = %s , buf2 = %s\n");
	exit(0);
}
