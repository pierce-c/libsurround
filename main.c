#include <stdio.h>
#include "mylib.h"
void test(int8_t *A, int32_t size){ 
	for(int32_t i=1;i<size;i++){ 
		int8_t key=A[i]; 
		int32_t j=i-1; 
		while((j>=0)&&(A[j]>key)){
			A[j+1]=A[j];
			j--;
		}
		A[j+1]=key; 
	}
}

int main(){
	i8 array[9]={2,4,5,6,7,3,5,8,9};
	printf("original array:");printarr(array,9);
	insertion_sort_i8(array,9);
	printf("final array:");printarr_i8(array,9);
	return 0;
}
