#include "apue.h"

int main(int argc, char* argv[])
{
    int i;
    char** ptr;
    extern char** environ;

    for (i = 0; i < argc; i++)
    {
        printf("[%s][%d] argv[%d] : %s\n", __FILE__, __LINE__, i, argv[i]);
    }

    for (ptr = environ; *ptr != 0; ptr++)
    {
        printf("[%s]【%d] %s\n", __FILE__, __LINE__, *ptr);
    }

    exit(0);
}
