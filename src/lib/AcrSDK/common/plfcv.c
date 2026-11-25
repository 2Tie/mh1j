#include "common.h"

void* base_addr0x38a308;

void plFCVSetBaseAddress0x192e30(void* ptr)
{
	base_addr0x38a308 = ptr;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plfcv", plFCVFcurveInterpolateHermite0x192e40);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plfcv", plGetFcurveStartTime0x192ec0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plfcv", plGetFcurveTime0x192fa0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plfcv", plGetFcurveEndTime0x192fb0);
