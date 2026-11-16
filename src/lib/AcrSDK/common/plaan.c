#include "common.h"
#include "lib/AcrSDK/common/plaan.h"

static u32 plAANGetModelNum0x190080(AAN*);

static AAN* GetFileHeadAAN0x18f0b0(AAN* ptr){
	return ptr;
}

AAN* GetModelHeadAAN0x18f0c0(AAN* arg1, s32 which) {
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
    return addr;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plGetLoopInfoAan0x18f180);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plGetMotionSetSizeFromAAN0x18f1d0);

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

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plAANGetMotionEndTime0x18ff40);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plaan", plAANGetMotionStartTime0x18ffe0);

u32 plAANGetModelNum0x190080(AAN* arg) {
    return GetFileHeadAAN0x18f0b0(arg)->head.cont.children;
}
