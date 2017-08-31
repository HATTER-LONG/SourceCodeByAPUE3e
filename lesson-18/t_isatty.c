/*************************************************************************
	> File Name: t_isatty.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Mon 21 Nov 2016 01:25:59 PM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>

int main(void)
{
	printf("fd 0: %s\n",isatty(0)?"tty":"not a tty");
	printf("fd 1: %s\n",isatty(1)?"tty":"not a tty");
	printf("fd 2: %s\n",isatty(2)?"tty":"not a tty");

	return 0;
}
