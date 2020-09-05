#include "apue.h"
#include <pthread.h>
#include <stdio.h>

void* thread_func(void* arg)
{
    pthread_t pid;
    pthread_attr_t attr;
    int i;
    size_t v;
    void* stkaddr;
    pid = pthread_self();
    pthread_getattr_np(pthread_self(), &attr);
    pthread_attr_getdetachstate(&attr, &i);

    printf("Detachstate\t=");
    if (i == PTHREAD_CREATE_DETACHED)
        printf("PTHREAD_CREATE_DETACHED\n");
    else if (i == PTHREAD_CREATE_JOINABLE)
        printf("PTHREAD_CREATE_JOINABLE\n");

    pthread_attr_getguardsize(&attr, &v);

    printf("Guard size\t= %d bytes\n", (int)v);
    pthread_attr_getstack(&attr, &stkaddr, &v);
    printf("Stack address\t= %p\n", stkaddr);
    printf("Stack size\t= 0x%x bytes\n", (int)v);

    return ((void*)0);
}

int main(void)
{
    pthread_t pid;
    pthread_attr_t attr;
    int err;

    err = pthread_attr_init(&attr);
    if (err != 0)
    {
        printf("pthread_attr_init() error\n");
        exit(-1);
    }

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&pid, &attr, thread_func, NULL);

    sleep(2);
    return 0;
}
