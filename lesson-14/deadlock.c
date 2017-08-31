#include <stdio.h>   
#include <stdlib.h>   
#include <unistd.h>   
#include <fcntl.h>   
#include <errno.h>   
#include <signal.h>   
#include <sys/stat.h>    
  
#define read_lock(fd, offset, whence, len) \   
    lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))  
#define readw_lock(fd, offset, whence, len) \   
    lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))  
#define write_lock(fd, offset, whence, len) \   
    lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))  
#define writew_lock(fd, offset, whence, len) \   
    lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))  
#define un_lock(fd, offset, whence, len) \   
    lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))  
  
#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)   
  
sig_atomic_t sigflag; /* set nonzero by sig handler */  
sigset_t newmask, oldmask, zeromask;  
  
//输出错误信息并退出      
void error_quit(const char *str)      
{      
    fprintf(stderr, "%s\n", str);      
    exit(1);      
}  
  
static void sig_usr(int signo)  /* one signal handler for SIGUSR1 and SIGUSR2 */  
{  
    sigflag = 1;  
}  
  
void TELL_WAIT(void)  
{  
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)  
        error_quit("signal(SIGUSR1) error");  
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)  
        error_quit("signal(SIGUSR2) error");  
    sigemptyset(&zeromask);  
    sigemptyset(&newmask);  
    sigaddset(&newmask, SIGUSR1);  
    sigaddset(&newmask, SIGUSR2);  
  
    /*  
    * Block SIGUSR1 and SIGUSR2, and save current signal mask.  
    */  
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)  
        error_quit("SIG_BLOCK error");  
}  
  
void TELL_PARENT(pid_t pid)  
{  
    kill(pid, SIGUSR2);     /* tell parent we're done */  
}  
  
void WAIT_PARENT(void)  
{  
    while (sigflag == 0)  
        sigsuspend(&zeromask);  /* and wait for parent */  
    sigflag = 0;  
  
    /*  
    * Reset signal mask to original value.  
    */  
    int temp = sigprocmask(SIG_SETMASK, &oldmask, NULL);  
    if (temp < 0)  
        error_quit("SIG_SETMASK error");  
}  
  
void TELL_CHILD(pid_t pid)  
{  
    kill(pid, SIGUSR1);         /* tell child we're done */  
}  
  
void WAIT_CHILD(void)  
{  
    while (sigflag == 0)  
        sigsuspend(&zeromask);  /* and wait for child */  
    sigflag = 0;  
  
    /*  
    * Reset signal mask to original value.  
    */  
    int temp = sigprocmask(SIG_SETMASK, &oldmask, NULL);  
    if (temp < 0)  
        error_quit("SIG_SETMASK error");  
}  
  
//加锁或解锁某个文件区域   
int lock_reg(int fd, int cmd, int type, off_t offset,  
             int whence, off_t len)  
{  
    struct flock lock;  
    lock.l_type = type;  
    lock.l_start = offset;  
    lock.l_whence = whence;  
    lock.l_len = len;  
    return fcntl(fd, cmd, &lock);  
}  
  
//锁住文件中的一个字节   
void lockabyte(const char *name, int fd, off_t offset)  
{  
    //在我的系统上（Ubuntu10.04），发生死锁时writew_lock并不会返回-1   
    if( writew_lock(fd, offset, SEEK_SET, 1) < 0 )  
        error_quit("writew_lock error");  
    printf("%s: got the lock, byte %ld\n", name, offset);  
}  
  
int main(void)  
{  
    int fd;  
    pid_t pid;  
  
    fd = creat("templock", FILE_MODE);  
    if( fd < 0 )  
        error_quit("create error");  
    if( write(fd, "ab", 2) != 2 )  
        error_quit("write error");  
  
    TELL_WAIT();  
    pid = fork();  
    if( pid < 0 )  
        error_quit("fork error");  
    else if( pid == 0 )  
    {  
        lockabyte("child", fd, 0);  
        TELL_PARENT( getpid() );  
        WAIT_PARENT();  
        lockabyte("child", fd, 1);  
    }  
    else  
    {  
        lockabyte("parent", fd, 1);  
        TELL_CHILD(pid);  
        WAIT_CHILD();  
        lockabyte("parent", fd, 0);  
    }  
    return 0;  
} 