#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#define BUFLEN	128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void
daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	/*
	 * Clear file creation mask.
	 */
	umask(0);

	/*
	 * Get maximum number of file descriptors.
	 */
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("%s: can't get file limit", cmd);

	/*
	 * Become a session leader to lose controlling TTY.
	 */
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid != 0) /* parent */
		exit(0);
	setsid();

	/*
	 * Ensure future opens won't allocate controlling TTYs.
	 */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't ignore SIGHUP", cmd);
	if ((pid = fork()) < 0)
		err_quit("%s: can't fork", cmd);
	else if (pid != 0) /* parent */
		exit(0);

	/*
	 * Change the current working directory to the root so
	 * we won't prevent file systems from being unmounted.
	 */
	if (chdir("/") < 0)
		err_quit("%s: can't change directory to /", cmd);

	/*
	 * Close all open file descriptors.
	 */
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/*
	 * Attach file descriptors 0, 1, and 2 to /dev/null.
	 */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	/*
	 * Initialize the log file.
	 */
	openlog(cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
		  fd0, fd1, fd2);
		exit(1);
	}
}
int
initserver(int type, const struct sockaddr *addr, socklen_t alen,
  int qlen)
{
	int fd;
	int err = 0;
	int reuse = 1;
	if ((fd = socket(addr->sa_family, type, 0)) < 0)
		return(-1);
	printf("socket ok\n");
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int) ) < 0)
		goto errout;
		if (bind(fd, addr, alen) < 0)
		goto errout;
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		if (listen(fd, qlen) < 0){
			printf("listen error\n");
			goto errout;
		}
	}
	printf("listen ok\n");
	return(fd);

errout:
	err = errno;
	close(fd);
	errno = err;
	return(-1);
}


int 
serve(int sockfd)
{
	int		clfd;
	FILE	*fp;
	char	buf[BUFLEN];

	
	set_cloexec(sockfd);
	for (;;) {
		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
		set_cloexec(clfd);
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL)
				send(clfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(clfd);
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n;
	char			*host;
	int 			sum_fd = 0;
	int 			retval = 0;
	fd_set 	rfds;
	struct  timeval tv;
	printf("ok?\n");
	if (argc != 1)
		err_quit("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
	if ((host = malloc(n)) == NULL)
		printf("malloc error\n");
	if (gethostname(host, n) < 0)
		printf("getname error\n");
//		err_sys("gethostname error");
//	 daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
		exit(1);
	}
	printf("test\n");	
	FD_ZERO(&rfds);
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
		  aip->ai_addrlen, QLEN)) >= 0) {
			printf("initserver ok\n"); 
			sum_fd++;
			printf("sum_fd = %d, sockfd = %d\n",sum_fd, sockfd);
			printf("1");
			FD_SET(sockfd, &rfds);
			printf("\n");
//			serve(sockfd);
//			exit(0);
		}
	}
	printf("ok\n");
	tv.tv_sec = 0;
    tv.tv_usec = 0;
	while(1){
		retval = select(sum_fd, &rfds, NULL, NULL, &tv);
		if(retval){
			if(serve(retval) == 0){
				printf("ok!\n");
			}
		}
	}
	
	
	exit(1);
}
