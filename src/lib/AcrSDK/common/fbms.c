#include "common.h"
#include "structs.h"

s32 fmsInitialize0x16abb0(FL_FMS* fms, u8* base_addr, s32 size, s32 alignment) {
    size = ~(alignment - 1) & (size + alignment - 1);
    fms->memoryblock = base_addr;
    fms->align = alignment;
    fms->baseandcap[0] = (u8*) (~(fms->align - 1) & (((s32)fms->memoryblock + fms->align) - 1));
    fms->baseandcap[1] = (u8*) (~(fms->align - 1) & ((fms->align + ((s32)(fms->memoryblock) + size)) - 1));
    fms->frame[0] = fms->baseandcap[0];
    fms->frame[1] = fms->baseandcap[1];
    return 1;
}

void* fmsAllocMemory0x16ac30(FL_FMS* lp, s32 bytes, s32 heapnum) {
    void* pMem;
    bytes = ~(lp->align - 1) & ((u32)bytes + lp->align - 1);

    if (lp->frame[0] + bytes > lp->frame[1]) {
        return NULL;
    }
    
    if (heapnum != 0) {
        lp->frame[1] -= bytes;
        pMem = lp->frame[1];
    } else {
        pMem = lp->frame[0];
        lp->frame[0] += bytes;
    }

    return pMem;
}

s32 fmsGetFrame0x16ac90(FL_FMS* fms, s32 heap, FMS_FRAME* frame) {
    frame->pFrame = fms->frame[heap];
    frame->heapnum = heap;
    return 1;
}

void fmsReleaseFrame0x16acb0(FL_FMS* fms, FMS_FRAME* frame) {
    fms->frame[frame->heapnum] = frame->pFrame;
}
