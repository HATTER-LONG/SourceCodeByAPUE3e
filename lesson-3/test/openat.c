#include <stdio.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <unistd.h>  
  
  
int main()  
{  
    
	char *dir_path = "./..";
	char *relative_path = "stderr.out";
	char buf[20] = {"0"};
	int dir_fd;  
    int fd;  
    int flags;  
	int fd1;
	mode_t mode;  
  
    dir_fd = open(dir_path, O_RDONLY);  
    if (dir_fd < 0)   
    {  
        perror("open");  
        exit(EXIT_FAILURE);  
    }  
  
    flags = O_CREAT | O_RDWR;  
    mode = 0777;  
    fd = openat(dir_fd, relative_path, flags, mode);  
    if (fd < 0)   
    {  
        perror("openat");  
        exit(EXIT_FAILURE);  
    }  
  
    if(write(fd, "HELLO", 5) != 5)
		printf("write error!!\n");
//    close(fd);
	fd1 = openat(dir_fd, relative_path, O_RDWR, mode);  
	lseek(fd, 0, SEEK_SET);	
	
	printf("fd=%d\tfd1=%d\n",fd,fd1);
	if(read(fd , buf, sizeof(buf)) != 5)
		printf("read error!!\n");
	printf("%s\n",buf);
    close(fd);  
    close(dir_fd);  
    return 0;  
}  
