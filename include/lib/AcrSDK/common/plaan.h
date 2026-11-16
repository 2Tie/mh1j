#ifndef PLAAN_H
#define PLAAN_H

#include "types.h"
#include "common.h"

#define FCV_LINEAR_SHORT 0x11
#define FCV_HERMITE_SHORT 0x12
#define FCV_COMPLEX_SHORT 0x13
#define FCV_LINEAR 0x21
#define FCV_HERMITE 0x22
#define FCV_COMPLEX 0x23

typedef struct{
	u8 fcv_type; //see constants above
	u8 unk_1[1];
	s16 point_count;
	void* fcv_data; //the raw anim data copied over, final pointer is then adjusted to offset from base_addr
} MOTION_HOLDER; //size: 0x08

typedef struct{
	s16 type;
	s16 entries;
	MOTION_HOLDER* mot_off;
} MOTION_REFERENCE; // size: 0x08

typedef struct{
	s16 unk; //set to 0
	s16 model_count;
	f32 earliest_start;
	f32 latest_end;
	f32 loop_point;
	void** models_ptrs; //array of pointers
	s32 base_addr;
	s32 total_size;
	s32 unk_1C;
} MOTION_SET; // size: 0x20

typedef struct{
    u32 type;
    u32 children;
    u32 size;
} AAN_CONTAINER;

typedef struct{
    AAN_CONTAINER cont;
    u32 animtype;
    f32 loop;
} AAN_HEADER;

typedef struct{
    AAN_HEADER head;
    AAN_CONTAINER tags[];
} AAN;

#endif
