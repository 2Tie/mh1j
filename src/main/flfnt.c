#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntCreate0x216490);

u32 flfntGetSystemMemorySize0x216570(void) {
    return 0xd0000;
};

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntStackReset0x216580);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntInit0x216610);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntCacheFlush0x216640);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetPalData0x2166e0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetSize0x216890);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntLocate0x2168b0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetZ0x2168d0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetPalette0x2168e0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetHalftype0x216910);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntPrintf0x216920);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDraw0x216ac0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDrawAll0x216bd0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntMakeHandle0x216cf0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntFontPuts0x216de0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntFontPutc0x216f90);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntPaletteTrans0x217480);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDrawStart0x217490);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDrawTerm0x217550);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSjis2Index0x217620);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSjis2Jis0x217680);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecReloadTexture0x217760);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecExpandFont0x217a60);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecCheckString0x217c10);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecCheckFont0x217d70);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecAscii2Sjis0x217de0);
