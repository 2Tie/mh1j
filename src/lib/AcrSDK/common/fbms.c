#include "common.h"
#include "structs.h"

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/fbms", fmsInitialize0x16abb0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/fbms", fmsAllocMemory0x16ac30);

s32 fmsGetFrame0x16ac90(FL_FMS* fms, s32 heap, FMS_FRAME* frame) {
    frame->pFrame = fms->frame[heap];
    frame->heapnum = heap;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/fbms", fmsReleaseFrame0x16acb0);
