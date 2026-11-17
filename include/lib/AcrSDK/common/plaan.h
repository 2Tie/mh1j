#ifndef PLAAN_H
#define PLAAN_H

#include "types.h"
#include "common.h"

#define FCV_LINEAR_SHORT  0x11
#define FCV_HERMITE_SHORT 0x12
#define FCV_COMPLEX_SHORT 0x13
#define FCV_LINEAR        0x21
#define FCV_HERMITE       0x22
#define FCV_COMPLEX       0x23

#define ANIM_TARGET_SCALE_X     0
#define ANIM_TARGET_SCALE_Y     1
#define ANIM_TARGET_SCALE_Z     2
#define ANIM_TARGET_ROTATE_X    3
#define ANIM_TARGET_ROTATE_Y    4
#define ANIM_TARGET_ROTATE_Z    5
#define ANIM_TARGET_TRANSLATE_X 6
#define ANIM_TARGET_TRANSLATE_Y 7
#define ANIM_TARGET_TRANSLATE_Z 8

#define ANIM_FLAG_SCALE_X     1<<ANIM_TARGET_SCALE_X
#define ANIM_FLAG_SCALE_Y     1<<ANIM_TARGET_SCALE_Y
#define ANIM_FLAG_SCALE_Z     1<<ANIM_TARGET_SCALE_Z
#define ANIM_FLAG_ROTATE_X    1<<ANIM_TARGET_ROTATE_X
#define ANIM_FLAG_ROTATE_Y    1<<ANIM_TARGET_ROTATE_Y
#define ANIM_FLAG_ROTATE_Z    1<<ANIM_TARGET_ROTATE_Z
#define ANIM_FLAG_TRANSLATE_X 1<<ANIM_TARGET_TRANSLATE_X
#define ANIM_FLAG_TRANSLATE_Y 1<<ANIM_TARGET_TRANSLATE_Y
#define ANIM_FLAG_TRANSLATE_Z 1<<ANIM_TARGET_TRANSLATE_Z


typedef struct{
    f32 time;
    f32 value;
} FCV_DATA_LINEAR;

typedef struct{
    f32 time;
    f32 value;
    f32 handle_l;
    f32 handle_r;
} FCV_DATA_HERMITE;

typedef struct{
    s32 type; //linear or hermite
    f32 time;
    f32 value;
    f32 handle_l;
    f32 handle_r;
} FCV_DATA_COMPLEX;

typedef struct{
    u16 time;
    u16 value;
} FCV_DATA_LINEAR_SHORT;

typedef struct{
    u16 time;
    u16 value;
    u16 handle_l;
    u16 handle_r;
} FCV_DATA_HERMITE_SHORT;

typedef struct{
    s32 type;
    u16 time;
    u16 value;
    u16 handle_l;
    u16 handle_r;
} FCV_DATA_COMPLEX_SHORT;

typedef struct{
	u8 fcv_format; //see FCV_ defines
	u8 anim_target; //see ANIM_TARGET_ defines
	u16 point_count;
	void* fcv_data; //the raw anim data copied over, final pointer is then adjusted to offset from base_addr
} MOTION_HOLDER; //size: 0x08

typedef struct{
	u16 type;
	s16 entries;
	MOTION_HOLDER* mot_off;
} MOTION_REFERENCE; // size: 0x08

typedef struct{
	u16 flags; //set to 0
	s16 model_count;
	f32 earliest_start;
	f32 latest_end;
	f32 loop_point;
	MOTION_REFERENCE** models_ptrs; //array of pointers
	u8* base_addr;
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
