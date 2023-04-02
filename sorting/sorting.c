#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
void printarr_i8(i8* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%d ",A[i]);
	}
	printf("]\n");
}
void printarr_i16(i16* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%hi ",A[i]);
	}
	printf("]\n");
}
void printarr_i32(i32* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%d ",A[i]);
	}
	printf("]\n");
}
void printarr_i64(i64* A,u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%li ",A[i]);
	}
	printf("]\n");
}
void printarr_u8(u8* A,u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%u ",A[i]);
	}
	printf("]\n");
}
void printarr_u16(u16* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%hu ",A[i]);
	}
	printf("]\n");
}
void printarr_u32(u32* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%d ",A[i]);
	}
	printf("]\n");
}
void printarr_u64(u64* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%lu ",A[i]);
	}
	printf("]\n");
}
void printarr_float(float* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%f ",A[i]);
	}
	printf("]\n");
}
void printarr_double(double* A, u32 size){
	putchar('[');
	for(u32 i=0;i<size;i++){
		printf("%lf ",A[i]);
	}
	printf("]\n");
}



loop_define(def_insertion_sort);
loop_define(def_merge_sorted_seg);
loop_define(def_merge_sorted);
loop_define(def_merge_sort);
