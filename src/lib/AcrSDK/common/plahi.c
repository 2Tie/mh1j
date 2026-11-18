#include "common.h"
#include "lib/AcrSDK/common/plahi.h"

AHI* GetFileHeadAHI0x190230(AHI*);

s32 plAHIGetModelNum0x1900a0(AHI* arg0) {
    s32 models;
    TAG_CONTAINER* cont;

    cont = &GetFileHeadAHI0x190230(arg0)->cont;
    models = cont->children;
    if (cont->tag & 0x80000000) {
        models -= 1;
    }
    return models;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plAHIGetTreeNum0x1900e0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plAHIGetTreeRootModel0x190110);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plAHIGetTreeModelNum0x190170);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plAHIGetTreeModelNum20x1901a0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", GetTreeModelNum0x1901c0);

AHI* GetFileHeadAHI0x190230(AHI* ptr) {
    return ptr;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", GetDataHeadAHI0x190240);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", GetModelDataHeadAHI0x1902b0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", GetModelDataAHI0x190340);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plGetInitMotionSetSizeFromAHI0x190370);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plCreateInitMotionSetFromAHI0x1903d0);
