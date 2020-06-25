#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

char buf[100000];
//将描述符设置为阻塞状态
void set_fl(int fd,int flags)
{
    int val;
    val = fcntl(fd,F_GETFL,0);  //获取描述符
    val |= flags;   //添加状态
    fcntl(fd,F_SETFL,val);  //设置描述符
}
void clr_fl(int fd,int flags)
{
    int val;
    val = fcntl(fd,F_GETFL,0);
    val &= ~flags;   // 取消状态
    fcntl(fd,F_SETFL,val);
}
int main()
{
    int ntowrite,nwrite;
    char *ptr;
    ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
    fprintf(stderr,"read %d bytes\n",ntowrite);
    set_fl(STDOUT_FILENO,O_NONBLOCK); //设置为阻塞状态
    ptr = buf;
    while(ntowrite > 0)
    {
        errno = 0;
        nwrite = write(STDOUT_FILENO,ptr,ntowrite);
        fprintf(stderr,"nwrite = %d,errno =%d\n",nwrite,errno);
        if(nwrite > 0)
        {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }
    clr_fl(STDOUT_FILENO,O_NONBLOCK); //设置为非阻塞状态
    exit(0);
}