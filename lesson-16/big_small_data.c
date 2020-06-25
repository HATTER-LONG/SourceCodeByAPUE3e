/*************************************************************************
	> File Name: big_small_data.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Mon 14 Nov 2016 08:58:28 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void){
	uint32_t	i = 0x04030201;
	unsigned char	*cp = (unsigned char *)&i;

	if(*cp == 1)
		printf("little-endian\n");
	else if(*cp == 4)
		printf("big-endian\n");

	return 0;
}
