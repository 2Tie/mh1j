#include "common.h"
#include "structs.h"

extern OPTIONS_WORK option_w0x3f20e0;

extern void flPADShockSet0x196200(s32, s32, s32);


//funcs
bool vib_check0x1698b0(void) {
    return option_w0x3f20e0.vibrate == false;
}

INCLUDE_ASM("asm/main/nonmatchings/vib", vib_set0x1698d0);

INCLUDE_ASM("asm/main/nonmatchings/vib", vib_set_pl0x169920);

void vib_stop0x169990(s32 which) {
    flPADShockSet0x196200(which, 0, 0);
}

void vib_stop_all0x1699a0(void) {
    s32 pad = 0;
    do {
        vib_stop0x169990(pad);
        pad += 1;
    } while (pad < 2);
}
