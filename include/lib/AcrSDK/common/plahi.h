#ifndef PLAHI_H
#define PLAHI_H

typedef struct HIERARCHY_NODE HIERARCHY_NODE;

typedef struct HIERARCHY_NODE{
    s32 id;
    HIERARCHY_NODE* parent;
    HIERARCHY_NODE* child;
    HIERARCHY_NODE* sibling;
    f32 v1[4];
    f32 v2[4];
    f32 offset[4];
    s32 unk;
    s32 chain;
    s32 unk2[];
} HIERARCHY_NODE;

typedef struct{
    u32 tag;
    u32 children;
    u32 size;
} TAG_CONTAINER;

typedef struct{
    TAG_CONTAINER cont;
    HIERARCHY_NODE* roots[];
} AHI_DATA;

typedef struct{
    TAG_CONTAINER cont;
} AHI;

#endif
