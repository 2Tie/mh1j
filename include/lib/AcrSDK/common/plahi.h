#ifndef PLAHI_H
#define PLAHI_H

typedef struct INIT_MOTION_SET INIT_MOTION_SET;

typedef struct{
    /* 0x00 */ s16 id;
    /* 0x02 */ s16 chain;
    /* 0x04 */ s16 parent; //unpopulated?
    /* 0x06 */ s16 child;
    /* 0x08 */ s16 sibling;
    /* 0x0A */ s16 unk_A;
    /* 0x0C */ u8 unk_C[4];
    /* 0x10 */ f32 scale[4];
    /* 0x20 */ f32 rotate[4];
    /* 0x30 */ f32 translate[4];
} INIT_MOT_BONE; // size: 0x40

typedef struct INIT_MOTION_SET{
    /* 0x00 */ s16 unk_0;
    /* 0x02 */ s16 bone_total;
    /* 0x04 */ s32 unk_4;
    /* 0x08 */ INIT_MOTION_SET* work;
    /* 0x0C */ s32 size;
    INIT_MOT_BONE bones[];
} INIT_MOTION_SET; // size: 0x10

typedef struct HIERARCHY_NODE HIERARCHY_NODE;

typedef struct HIERARCHY_NODE{
    /* 0x00 */ s32 id;
    /* 0x04 */ s32 parent;
    /* 0x08 */ s32 child;
    /* 0x0C */ s32 sibling;
    /* 0x10 */ f32 scale[4];
    /* 0x20 */ f32 rotate[4];
    /* 0x30 */ f32 translate[4];
    /* 0x40 */ s32 unk; //usually -1?
    /* 0x44 */ s32 chain;
    /* 0x48 */ s32 unk2[];
} HIERARCHY_NODE;

typedef struct{
    /* 0x0 */ u32 tag;
    /* 0x4 */ u32 children;
    /* 0x8 */ u32 size;
} TAG_CONTAINER; // size: 0xC

typedef struct{
    TAG_CONTAINER cont;
    s32 roots[];
} AHI_DATA;

typedef struct{
    TAG_CONTAINER cont;
} AHI;

#endif
