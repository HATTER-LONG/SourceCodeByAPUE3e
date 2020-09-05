#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


extern char** environ;
pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT; //一次性初始化，保证只运行一次
//初始化互斥量类型
static void thread_init(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    //设置为递归锁
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}
int mygetenv(const char* name, char* buf, int buflen)
{
    int i, len, olen;
    pthread_once(&init_done, thread_init); //初始化互斥量
    len = strlen(name);
    //加锁防止name被修改
    pthread_mutex_lock(&env_mutex);
    for (i = 0; environ[i] != NULL; i++)
    {
        if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '='))
        {
            olen = strlen(&environ[i][len]);
            if (olen >= buflen)
            {
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strcpy(buf, &environ[i][len + 1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}

void* thread_func1(void* arg)
{
    char buf[100];
    printf("thread 1 start.\n");
    mygetenv("HOME", buf, 100);
    printf("HOME=%s\n", buf);
    printf("thread 1 exit.\n");
    pthread_exit((void*)1);
}
void* thread_func2(void* arg)
{
    char buf[100];
    printf("thread 2 start.\n");
    mygetenv("SHELL", buf, 100);
    printf("SHELL=%s\n", buf);
    printf("thread 2 exit.\n");
    pthread_exit((void*)2);
}
int main()
{
    pthread_t pid1, pid2;
    int err;
    void* pret;
    pthread_create(&pid1, NULL, thread_func1, NULL);
    pthread_create(&pid2, NULL, thread_func2, NULL);
    pthread_join(pid1, &pret);
    printf("thread 1 exit code is: %d\n", (int)pret);
    pthread_join(pid2, &pret);
    printf("thread 2 exit code is: %d\n", (int)pret);
    exit(0);
}
