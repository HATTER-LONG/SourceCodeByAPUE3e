/*************************************************************************
	> File Name: csize.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Sun 20 Nov 2016 04:35:45 PM CST
 ************************************************************************/

#include <stdio.h>
#include <apue.h>

int main(void)
{
	struct termios term;

	if(tcgetattr(STDIN_FILENO, &term))
		err_sys("tcgetattr error");

	switch (term.c_cflag & CSIZE){
		case CS5:
			printf("5 bits/byte\n");
		case CS6:
			printf("6 bits/byte\n");
		case CS7:
			printf("7 bits/byte\n");
		case CS8:
			printf("8 bite/byte\n");
		default:
			printf("unknow bits/byte\n");
	}

	term.c_cflag &= ~CSIZE;
	term.c_cflag |= CS8;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		err_sys("tcsetattr error");

	exit(0);
}
