#include <stdio.h>

int 
main(void)
{
	int a = 010;
	char buf[10]= {"asdd"};
	char *buff[1] ;
	buff[0] = buf;
	char *p = "abc";
	printf("p[]=%c\n",p[1]);
	printf("=====%s======%s\n",__FILE__,buff[0]);
	exit (0);
}
