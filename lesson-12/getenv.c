#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
static char envbuf[1024];  //值存放到一个静态缓冲区中，线程共享
extern char **environ;
char *mygetenv(const char *name)
{
    int i,len;
    len = strlen(name);
    for(i=0;environ[i] != NULL;i++)
    {
        if((strncmp(name,environ[i],len) == 0) &&
           (environ[i][len] == '='))
           {
               strcpy(envbuf,&environ[i][len+1]);
               return envbuf;
           }
    }
    return NULL;
}
void * thread_func1(void *arg)
{
    char *pvalue;
    printf("thread 1 start.\n");
    pvalue = mygetenv("HOME");
    printf("HOME=%s\n",pvalue);
    printf("thread 1 exit.\n");
    pthread_exit((void*)1);
}
void * thread_func2(void *arg)
{
    char *pvalue;
    printf("thread 2 start.\n");
    pvalue = mygetenv("SHELL");
    printf("SHELL=%s\n",pvalue);
    printf("thread 2 exit.\n");
    pthread_exit((void*)2);
}
int main()
{
    pthread_t pid1,pid2;
    int err;
    void *pret;
    pthread_create(&pid1,NULL,thread_func1,NULL);
    pthread_create(&pid2,NULL,thread_func2,NULL);
    pthread_join(pid1,&pret);
    printf("thread 1 exit code is: %d\n",(int)pret);
    pthread_join(pid2,&pret);
    printf("thread 2 exit code is: %d\n",(int)pret);
    exit(0);
}