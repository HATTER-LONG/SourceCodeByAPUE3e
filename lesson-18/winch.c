#include "apue.h"
#include <termios.h>
#ifndef	TIOCGWINSZ
#include <sys/ioctl.h>
#endif

static void
pr_winsize(int fd)
{
	struct winsize	size;

	if (ioctl(fd, TIOCGWINSZ, (char *) &size) < 0)
		err_sys("TIOCGWINSZ error");
	printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
}

static void
sig_winch(int signo)
{
	if (signal(SIGWINCH, sig_winch) == SIG_ERR)
		err_sys("signal error");
	printf("SIGWINCH received\n");
	pr_winsize(STDIN_FILENO);
}

int
main(void)
{
	struct winsize size;
	size.ws_row = 100;
	size.ws_col = 100;
	if (isatty(STDIN_FILENO) == 0)
		exit(1);
	if (signal(SIGWINCH, sig_winch) == SIG_ERR)
		err_sys("signal error");
	
	if (ioctl(STDIN_FILENO, TIOCSWINSZ, (char *) &size) < 0)
		err_sys("TIOCGWINSZ error");
	printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
	pr_winsize(STDIN_FILENO);	/* print initial size */
	for ( ; ; )	{

		pause();
	}/* and sleep forever */

}
