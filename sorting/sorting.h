#pragma once
#include "../mylib.h"
#include <string.h>
#define declare_insertion_sort(type) void insertion_sort_##type (type *A,u32 size);
#define declare_merge_sorted_seg(type) void merge_sorted_seg_##type (type *A,u32 p,u32 q,u32 r);
#define declare_merge_sorted(type) type *merge_sorted_##type (type *A, type *B,u32 l1, u32 l2);
#define declare_merge_sort(type) void merge_sort_##type (type *A,u32 size);
#define declare_printarr(type) void printarr_##type (type *A,u32 size);
#define printarr(A,size) _Generic((A),generic_loop(printarr))(A,size)
#define insertion_sort(A,size) _Generic((A),generic_loop(insertion_sort))(A,size)
#define merge_sorted_seg(A,p,q,r) _Generic((A),generic_loop(merge_sorted_seg))(A,p,q,r)
#define merge_sorted(A,B,l1,l2) _Generic((A),generic_loop(merge_sorted))(A,B,l1,l2)
#define merge_sort(A,size) _Generic((A).generic_loop(merge_sort))(A,size)
loop_define(declare_insertion_sort);
loop_define(declare_merge_sorted_seg);
loop_define(declare_merge_sorted);
loop_define(declare_merge_sort);
loop_define(declare_printarr);
#define def_insertion_sort(type) \
void insertion_sort_##type(type *A, u32 size){ \
	for(i32 i=1;i<size;i++){ \
		type key=A[i]; \
		i32 j=i-1; \
		while((j>=0)&&(A[j]>key)){\
			A[j+1]=A[j]; \
			j--;\
		}\
		A[j+1]=key; \
	} \
}\

#define def_merge_sorted_seg(type) \
void merge_sorted_seg_##type(type *A, u32 p, u32 q, u32 r){ \
	u32 nl=q-p+1; \
	u32 nr=r-q; \
	type *L=malloc(nl*sizeof(type)); \
	type *R=malloc(nr*sizeof(type)); \
	for(u32 i=0;i<nl;i++)L[i]=A[p+i]; \
	for(u32 i=0;i<nr;i++)R[i]=A[q+i+1]; \
	u32 i=0,j=0,k=p; \
	while(i<nl&&j<nr){ \
		if(L[i]<=R[j])A[k++]=L[i++]; \
		else A[k++]=R[j++]; \
	} \
	while(i<nl)A[k++]=L[i++]; \
	while(j<nr)A[k++]=R[j++]; \
	free(L); \
	free(R); \
}\

#define def_merge_sorted(type) \
type *merge_sorted_##type(type *A, type *B, u32 l1, u32 l2){ \
	u32 l=l1+l2; \
	type *C=malloc(l*sizeof(type)); \
	u32 i=0,j=0,k=0; \
	while(i<l1&&j<l2){ \
		if(A[i]<=B[j])C[k++]=A[i++]; \
		else C[k++]=B[j++]; \
	} \
	while(i<l1)C[k++]=A[i++]; \
	while(i<l2)C[k++]=B[j++]; \
	return C; \
}\

#define def_merge_sort(type) \
void merge_sort_##type (type *A, u32 size){\
	if(size<2)return;\
	merge_sort_##type (A,size/2);\
	merge_sort_##type (A+size/2+1,size/2-1);\
	merge_sorted_seg_##type (A,0,size/2,size); \
}\

