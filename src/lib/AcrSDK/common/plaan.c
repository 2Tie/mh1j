#include "common.h"
#include "lib/AcrSDK/common/plaan.h"

extern f32 plGetFcurveTime0x192fa0(MOTION_HOLDER*);
extern f32 plGetFcurveStartTime0x192ec0(MOTION_HOLDER*);
extern u8* base_addr0x38a300;

static u32 plAANGetModelNum0x190080(AAN*);
s32 plGetMotionSizeFromAAN0x18f260(AAN_CONTAINER*);

static AAN* GetFileHeadAAN0x18f0b0(AAN* ptr){
	return ptr;
}

AAN_CONTAINER* GetModelHeadAAN0x18f0c0(AAN* arg1, s32 which) {
    AAN* addr;
    AAN_CONTAINER* scratch;
    s32 i;

    addr = GetFileHeadAAN0x18f0b0(arg1);
    scratch = addr->tags;
    addr += 1;
    i = 0;
    if (0 < which) {
        if (8 < which) {
            do{
                i += 8;
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + addr->head.cont.size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                addr = (AAN*)scratch;
            } while (i < (which - 8));
        }
        if (i < which) {
            do {
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + addr->head.cont.size);
                addr = (AAN*)scratch;
                i += 1;
            } while (i < which);
        }
    }
    return &addr->head.cont;
}

bool plGetLoopInfoAan0x18f180(AAN* arg0, f32* pt) {
    AAN* head;
    bool ret;

    head = GetFileHeadAAN0x18f0b0(arg0);
    if (head->head.animtype != 0) {
        ret = true;
        *pt = head->head.loop;
    } else {
        ret = false;
        *pt = 0;
    }
    return ret;
}

s32 plGetMotionSetSizeFromAAN0x18f1d0(AAN* arg0) {
    s32 i;
    AAN_CONTAINER* head;
    s32 children;
    s32 size;

    children = plAANGetModelNum0x190080(arg0);
    size = (children * 4) + sizeof(MOTION_SET); //size of MOTION_SET, plus a pointer per children it reserves
    for(i = 0; i < children; i += 1) {
        head = GetModelHeadAAN0x18f0c0(arg0, i); //seek to child
        size += sizeof(MOTION_REFERENCE);
        size += head->children * sizeof(MOTION_HOLDER);
        size += plGetMotionSizeFromAAN0x18f260(head);
    }
    return size;
}

s32 plGetMotionSizeFromAAN0x18f260(AAN_CONTAINER* arg0) {
    AAN_CONTAINER* container;
    s32 children;
    s32 size;
    s32 i;
    
    children = arg0->children;
    container = arg0 + 1;
    size = 0;
    for(i = 0; i < children; i++) {
        switch ((container->type & 0xFF0000) >> 0x10) {
        case FCV_LINEAR:
            size += container->children * 8;
            break;
        case FCV_HERMITE:
            size += container->children * 0x10;
            break;
        case FCV_COMPLEX:
            size += container->children * 0x14;
            break;
        case FCV_LINEAR_SHORT:
            size += container->children * 4;
            break;
        case FCV_HERMITE_SHORT:
            size += container->children * 8;
            break;
        case FCV_COMPLEX_SHORT:
            size += container->children * 0xC;
            break;
        }
        container = (AAN_CONTAINER*)((int)container + container->size);
    }
    
    return size;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateMotionSetFromAAN0x18f370);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateMotionFromAAN0x18f6b0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateMotionFromAANSub_SRT0x18f790);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN0x18f9f0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN_Linear0x18fac0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN_Hermite0x18fb70);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN_Complex0x18fc30);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN_LinearShort0x18fd00);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN_HermiteShort0x18fdb0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plCreateFcurveDataAAN_ComplexShort0x18fe70);

f32 plAANGetMotionEndTime0x18ff40(MOTION_REFERENCE* arg0) { //passed is pointer to (unpacked) motion data
    f32 candidate;
    f32 latest;
    s32 i;

    latest = 0.0f;
    
    for (i = 0; i < arg0->entries; i += 1) {
        candidate = plGetFcurveTime0x192fa0(&((MOTION_HOLDER*)((u32)arg0->mot_off + (u32)base_addr0x38a300))[i]);
        if (candidate > latest)
            latest = candidate;
    }
    return latest;
}

f32 plAANGetMotionStartTime0x18ffe0(MOTION_REFERENCE* arg0) {
    f32 candidate;
    f32 earliest;
    s32 i;

    earliest = 1e10f;
    
    for (i = 0; i < arg0->entries; i++){
        candidate = plGetFcurveStartTime0x192ec0(&((MOTION_HOLDER*)((s32)arg0->mot_off + (s32)base_addr0x38a300))[i]);
        if (candidate < earliest) 
            earliest = candidate;
    }
    return earliest;
}

u32 plAANGetModelNum0x190080(AAN* arg) {
    return GetFileHeadAAN0x18f0b0(arg)->head.cont.children;
}
