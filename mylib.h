#pragma once
#ifndef typedef_check
	#include <stddef.h>
	#include <stdint.h>
	#define u8 uint8_t
	#define u16 uint16_t
	#define u32 uint32_t
	#define u64 uint64_t
	#define i8 int8_t
	#define i16 int16_t
	#define i32 int32_t
	#define i64 int64_t
#endif

#define loop_define(func)\
	func (u8)\
	func (u16)\
	func (u32)\
	func (u64)\
	func (i8);\
	func (i16)\
	func (i32)\
	func (i64)\
	func (float)\
	func (double)
#define generic_loop(type)\
	i8*:type##_i8,\
	i16*:type##_i16,\
	i32*:type##_i32,\
	i64*:type##_i64,\
	u8*:type##_u8,\
	u16*:type##_u16,\
	u32*:type##_u32,\
	u64*:type##_u64,\
	float*:type##_float,\
	double*:type##_double
#include "sorting/sorting.h"
