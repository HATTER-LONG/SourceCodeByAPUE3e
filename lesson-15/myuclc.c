/*************************************************************************
	> File Name: myuclc.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Mon 31 Oct 2016 08:34:31 PM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>
#include <ctype.h>

int main(void){
	int		c;

	while ((c = getchar()) != EOF){
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF)
			err_sys("output error");
		if(c == '\n')
			fflush(stdout);
	}

	exit(0);
}
