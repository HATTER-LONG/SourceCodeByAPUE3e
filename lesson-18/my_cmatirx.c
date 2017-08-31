/*************************************************************************
	> File Name: my_cmatirx.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Tue 22 Nov 2016 09:50:23 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <apue.h>
#include <curses.h>

void finish(int sigage)
{

	curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}

int main(void){

	initscr();
	savetty();
	nonl();
	cbreak();
	noecho();
	timeout(0);
	signal(SIGINT, finish);
	if (has_colors()) {
			start_color();
	}
	if (use_default_colors() != 0){
		init_pair(COLOR_GREEN, COLOR_GREEN, -1);
	}

	printf("ok\n");
	printf("123");
	finish(0);
}
