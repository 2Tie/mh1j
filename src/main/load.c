#include "common.h"

extern s32 arc_ptr0x38a23c;
extern s32 load_bin0x1003b0(s32, s32);

s32 load_file_mdl0x11ed20(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        return -1;
    }
    if (load_bin0x1003b0(arg1 | 0x20000, arc_ptr0x38a23c) == 1) {
        Meltw0x11f230(arc_ptr0x38a23c, arg0);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/load", load_pl_motion0x11ed90);

INCLUDE_ASM("asm/main/nonmatchings/load", load_plcom_motion0x11edb0);

INCLUDE_ASM("asm/main/nonmatchings/load", load_em_motion0x11edd0);

INCLUDE_ASM("asm/main/nonmatchings/load", load_stage_model0x11edf0);

INCLUDE_ASM("asm/main/nonmatchings/load", load_eft_model0x11ee50);

INCLUDE_ASM("asm/main/nonmatchings/load", load_weapon_model0x11eeb0);

INCLUDE_ASM("asm/main/nonmatchings/load", load_armor_model0x11ef10);

INCLUDE_ASM("asm/main/nonmatchings/load", load_enemy_model0x11ef90);

INCLUDE_ASM("asm/main/nonmatchings/load", load_enemy_sub_model0x11eff0);

INCLUDE_ASM("asm/main/nonmatchings/load", load_npc_model0x11f050);

INCLUDE_ASM("asm/main/nonmatchings/load", load_set_model0x11f0b0);

INCLUDE_ASM("asm/main/nonmatchings/load", load_edit_model0x11f110);

void debug_model_load0x11f160(void) {
    return;
}

INCLUDE_ASM("asm/main/nonmatchings/load", reload_tex0x11f170);

INCLUDE_ASM("asm/main/nonmatchings/load", LoadCameraData0x11f1e0);

INCLUDE_ASM("asm/main/nonmatchings/load", Meltw0x11f230);

INCLUDE_ASM("asm/main/nonmatchings/load", GetLinkFileNum0x11f310);

INCLUDE_ASM("asm/main/nonmatchings/load", GetLinkFileAddress0x11f320);

INCLUDE_ASM("asm/main/nonmatchings/load", GetLinkFileSize0x11f340);

INCLUDE_ASM("asm/main/nonmatchings/load", amo_ahi_expand0x11f350);
