/*************************************************************************
	> File Name: sum.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Thu 03 Nov 2016 11:47:30 AM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>
#include <stdlib.h>

int main(void){
	char buf[128];
	fgets(buf,128,stdin);
	printf("you input : %s\n ",buf);
	return 0;
}
