#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

struct foo
{
    int f_count;
    pthread_mutex_t f_mutex;
    pthread_cond_t f_cond;
};

struct foo* foo_alloc()
{
    struct foo* fp;
    fp = (struct foo*)malloc(sizeof(struct foo));
    if (fp != NULL)
    {
        fp->f_count = 0;
        pthread_mutex_init(&fp->f_mutex, NULL);
        pthread_cond_init(&fp->f_cond, NULL);
    }
    return fp;
}
void foo_increase(struct foo* fp)
{
    pthread_mutex_lock(&fp->f_mutex);
    if (fp->f_count == 0) //发送信号，通知可以做decrease操作
        pthread_cond_signal(&fp->f_cond);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_mutex);
}
void foo_decrease(struct foo* fp)
{
    pthread_mutex_lock(&fp->f_mutex);
    while (fp->f_count == 0)                          //判断是否可以做decrease操作
        pthread_cond_wait(&fp->f_cond, &fp->f_mutex); //等待信号
    fp->f_count--;
    pthread_mutex_unlock(&fp->f_mutex);
}
void* thread_func1(void* arg)
{
    struct foo* fp = (struct foo*)arg;
    printf("thread 1 start.\n");
    foo_increase(fp);
    printf("in thread 1 count = %d\n", fp->f_count);
    printf("thread 1 exit.\n");
    pthread_exit((void*)1);
}
void* thread_func2(void* arg)
{
    struct foo* fp = (struct foo*)arg;
    printf("thread 2 start.\n");
    foo_decrease(fp);
    printf("in thread 2  count = %d\n", fp->f_count);
    printf("thread 2 exit.\n");
    pthread_exit((void*)2);
}

int main()
{
    pthread_t pid1, pid2, pid3;
    int err;
    void* pret;
    struct foo* fobj;
    fobj = foo_alloc();
    pthread_create(&pid1, NULL, thread_func1, (void*)fobj);
    pthread_create(&pid2, NULL, thread_func2, (void*)fobj);
    pthread_join(pid1, &pret);
    printf("thread 1 exit code is: %d\n", (int)pret);
    pthread_join(pid2, &pret);
    printf("thread 2 exit code is: %d\n", (int)pret);
    exit(0);
}