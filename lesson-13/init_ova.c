#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <syslog.h>
#include <unistd.h>


void daemonize(const char* cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit r1;
    struct sigaction sa;
    umask(0);
    //获取文件描述符最大值
    getrlimit(RLIMIT_NOFILE, &r1);
    //创建子进程
    if ((pid = fork()) < 0)
    {
        perror("fork() error");
        exit(0);
    }
    else if (pid > 0) //使父进程退出
        exit(0);
    setsid(); //创建会话
              //创建子进程避免获取终端
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGHUP, &sa, NULL);
    if ((pid = fork()) < 0)
    {
        perror("fork() error");
        exit(0);
    }
    else if (pid > 0)
        exit(0);
    //修改目录
    chdir("/");
    //关闭不需要的文件描述符
    if (r1.rlim_max == RLIM_INFINITY)
        r1.rlim_max = 1024;
    for (i = 0; i < r1.rlim_max; ++i)
        close(i);
    //打开文件描述符
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

int main()
{
    daemonize("ls");
    sleep(30); //主进程休眠，以便查看守护进程状态
    exit(0);
}