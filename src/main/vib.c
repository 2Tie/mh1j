#include "common.h"
#include "structs.h"

extern OPTIONS_WORK option_w0x3f20e0;
extern s32 vib_tbl0x3019e0[5][2];

extern void flPADShockSet0x196200(s32, s32, s32);
extern s32 Pl_master_ck0x14fc20(void*);


//funcs
static s32 vib_check0x1698b0(void) {
    return option_w0x3f20e0.vibrate == false;
}

void vib_set0x1698d0(s32 controller, s32 which) {
    if (vib_check0x1698b0() == 0) {
        flPADShockSet0x196200(controller, vib_tbl0x3019e0[which][0], vib_tbl0x3019e0[which][1]);
    }
}

void vib_set_pl0x169920(void* player, s32 which) {
    if ((vib_check0x1698b0() == 0) && (Pl_master_ck0x14fc20(player) != 0)) {
        flPADShockSet0x196200(0, vib_tbl0x3019e0[which][0], vib_tbl0x3019e0[which][1]);
    }
}

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
