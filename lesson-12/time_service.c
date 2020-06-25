#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MAXLINE 100

void daemon_init(const char* pname,int facility)
{
    int                 i;
    pid_t               pid;
    struct  rlimit      rl;
    struct  sigaction   sa;
    /* 清除文件模式创建掩码,使新文件的权限位不受原先文件模式创建掩码的权限位的影响*/
    umask(0);
    if(getrlimit(RLIMIT_NOFILE,&rl) < 0)
    {
        perror("getrlimit() error");
        exit(-1);
    }
    if((pid = fork()) < 0)
    {
        perror("fork() error");
        exit(-1);
    }
    else if(pid > 0)   /*父进程终止 */
        exit(0);
    setsid();         /* 子进程成为会话首进程*/
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP,&sa,NULL) < 0)
    {
        perror("sigaction() error");
        exit(-1);
    }
    if((pid = fork()) < 0)
    {
        perror("fork() error");
        exit(-1);
    }
    else if(pid > 0)
        exit(0);        /* 第一个子程进终止,保证后面操作不会分配终端 */
    if(chdir("/")<0)    /* 改变工作目录 */
    {
        perror("chdir() error");
        exit(-1);
    }
    if(rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i=0;i<rl.rlim_max;++i)  /*关闭所有打开的文件描述字*/
        close(i);
    openlog(pname, LOG_PID, facility);  /*用syslogd处理错误*/
}

int main(int argc,char *argv[])
{
    int                 listenfd, connfd;
    socklen_t           addrlen, len;
    struct sockaddr     cliaddr;
    struct sockaddr_in  server;
    char                buff[MAXLINE];
    time_t              ticks;
    int                 n;
    bzero(&server, sizeof(server));
    bzero(&cliaddr,sizeof(cliaddr));
    server.sin_family = AF_INET;
    server.sin_port = htons(5050);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    daemon_init(argv[0], 0);
    if((listenfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        syslog(LOG_NOTICE|LOG_LOCAL0,"socket error");
        exit(-1);
    }
    if (bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1)
    {
        syslog(LOG_NOTICE|LOG_LOCAL0,"socket error");
        exit(-1);
    }
    if(listen(listenfd,5)==-1)
    {
        syslog(LOG_NOTICE|LOG_LOCAL0,"listen error");
        exit(-1);
    }
    for ( ; ; )
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd,&cliaddr, &len);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if((n= write(connfd, buff, strlen(buff)))==-1)
           syslog(LOG_NOTICE|LOG_LOCAL0,"write error");
        close(connfd);
    }
}