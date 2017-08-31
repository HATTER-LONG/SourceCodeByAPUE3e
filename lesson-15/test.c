/*************************************************************************
	> File Name: test.c
	> Author: Hatter
	> Mail: caolei67674@gmail.com 
	> Created Time: Wed 02 Nov 2016 03:57:59 PM CST
 ************************************************************************/

#include <stdio.h>

int main(void){
	int a = 0;
	int a1 = 1,a2,a3;
	int i = 0,j,k,l,g;
	for (i = 1; i < 9; i++){
		for(j = 1;j < 9; j++){
			for(k = 1; k < 9; k++){
				for(l = 1; l < 9; l++){				
					for(g= 1; g < 9; g++){
						if(i != j && i !=k && i != l &&i != g)
							if(j != k && j != l && j != g)
								if(k != l && k != g)
									if( l != g){

										a1 = i+j;
										a2 = i+k;
										
										if(a1 != j && a1 !=k && a1 != l &&a1 != g && a1 != i && a1 > 0 &&a1 < 9)
										if(a2 != j && a2 !=k && a2 != l &&a2 != g && a2 != i && a1 > 0 &&a2 < 9 )
										{
										a1 = a1 - l;
										a2 = a2 - g;
										
										if(a1 != j && a1 !=k && a1 != l &&a1 != g && a1 != i && a1 > 0)
										if(a2 != j && a2 !=k && a2 != l &&a2 != g && a2 != i && a2 > 0)
										{
											if(a1 == a2 && a1 != 0){
											printf("i = %d\tj = %d\tk = %d\tl = %d\tg = %d\t",i,j,k,l,g);
											printf("\n");
											a++;
											}
										}
									}
								
					}

				}
			}
		}
		}
	}
	printf("total = %d\n",a);
	return(0);	
}
