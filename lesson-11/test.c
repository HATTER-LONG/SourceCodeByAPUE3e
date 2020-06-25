/*************************************************************************
	> File Name: test.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Wed 19 Oct 2016 07:50:40 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXlINE 4096
int main(void){
	char str[MAXlINE] = {0};
	int i,k;
	int Data=0;
	int Char=0;
	int Other=0;
	fgets(str,MAXlINE,stdin);
//	gets(str);
	k = strlen(str)-1;
	printf("strlen = %d\n",k);
	i = 0;
	while(1){
		i++;
		
		if(i == k+1)
			break;
		if(str[i-1]>= 48&&str[i-1]<=57){
			Data++;
			continue;
		}
		if(str[i-1]>= 65&&str[i-1]<=90){
			Char++;
			continue;
		}
		if(str[i-1]>= 97&&str[i-1]<=122){
			Char++;
			continue;
		}
		Other++;
	}
	printf("char = %d\tdata = %d\tother = %d\n",Char,Data,Other);
	
	return 0;
}
