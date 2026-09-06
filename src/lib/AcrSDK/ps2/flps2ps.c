#include "common.h"
#include "lib/AcrSDK/ps2/flps2ps.h"

extern f32 flViewportCX0x38a280;
extern f32 flViewportCY0x38a27c;
extern f32 flViewportLX0x38a278;
extern f32 flViewportLY0x38a274;

extern FLPS2State flPs2State0x4241c0;



INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flPS2psAddQueue0x175120);

s32 flPS2CheckGSClip0x1751d0(f32 xcoord, f32 ycoord, f32 zcoord) {
    s32 inview;

    if ((flViewportCX0x38a280 + flViewportLX0x38a278) < xcoord) {
        return 0;
    }
    if (!((flViewportCX0x38a280 - flViewportLX0x38a278) <= xcoord)) {
        return 0;
    }
    if ((flViewportCY0x38a27c + flViewportLY0x38a274) < ycoord) {
        return 0;
    }
    if (!((flViewportCY0x38a27c - flViewportLY0x38a274) <= ycoord)) {
        return 0;
    }
    if (zcoord < 0.0f) {
        return 0;
    }
    inview = 1;
    if ((flPs2State0x4241c0.ZBuffMax >= zcoord)) {
        inview = 0;
    }
    return inview ^ 1;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps00020x175290);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps00040x175530);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps00050x175750);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps00080x175b80);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps00090x175e40);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps000C0x176100);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps0D000x176470);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps0F000x1766b0);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps13000x176a10);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps14000x176d00);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/ps2/flps2ps", flps16000x177040);
