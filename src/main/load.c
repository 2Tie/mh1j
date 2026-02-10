#include "common.h"

extern u8* arc_ptr0x38a23c;
extern s32 load_bin0x1003b0(s32, u8*);
extern int pl_motion_data0x2ebc50[];
extern int em_motion_data0x2ec830[];
extern int common_motion_data0x2ebc70[];
extern u8* data_load_ptr0x38a240;
extern u8* stage_model0x38a220;
extern u8* pl_area_top0x38a224;
extern int stage_model_data0x2ec950[];
extern int effect_model_data0x2ecee0[];
extern int weapon_model_data0x2ec5b0[];
extern int em_model_data0x2ec7a0[];
extern int em_sub_model_data0x2ec8c0[];
extern int npc_model_data0x2eced0[];
extern int set_model_data0x2ecd70[];
extern int edit_model_data0x386bd0[2]; //actually extern, the rest should be in rodata?

s32 load_file_mdl0x11ed20(u8* buff, s32 fileID) {
    if (fileID < 0) {
        return -1;
    }
    if (load_bin0x1003b0(fileID | 0x20000, arc_ptr0x38a23c) == 1) {
        Meltw0x11f230(arc_ptr0x38a23c, buff);
        return 1;
    }
    return 0;
}

int load_pl_motion0x11ed90(s32 arg1, s32 motion) {
    return load_file_mdl0x11ed20(pl_area_top0x38a224, pl_motion_data0x2ebc50[motion]);
}

int load_plcom_motion0x11edb0(s32 arg1, s32 motion) {
    return load_file_mdl0x11ed20(pl_area_top0x38a224, common_motion_data0x2ebc70[motion]);
}

int load_em_motion0x11edd0(s32 arg0, s32 em) {
    return load_file_mdl0x11ed20(pl_area_top0x38a224, em_motion_data0x2ec830[em]);
}

void load_stage_model0x11edf0(s32 stage) {
    u8* model_ptr;

    model_ptr = stage_model0x38a220;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, stage_model_data0x2ec950[stage]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

void load_eft_model0x11ee50(s32 eft) {
    u8* model_ptr;

    model_ptr = stage_model0x38a220;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, effect_model_data0x2ecee0[eft]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

void load_weapon_model0x11eeb0(s32 weap) {
    u8* model_ptr;

    model_ptr = pl_area_top0x38a224;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, weapon_model_data0x2ec5b0[weap]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

INCLUDE_ASM("asm/main/nonmatchings/load", load_armor_model0x11ef10);

void load_enemy_model0x11ef90(s32 enemy) {
    u8* model_ptr;

    model_ptr = pl_area_top0x38a224;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, em_model_data0x2ec7a0[enemy]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

void load_enemy_sub_model0x11eff0(s32 enemy) {
    u8* model_ptr;

    model_ptr = pl_area_top0x38a224;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, em_sub_model_data0x2ec8c0[enemy]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

void load_npc_model0x11f050(s32 npc) {
    u8* model_ptr;

    model_ptr = pl_area_top0x38a224;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, npc_model_data0x2eced0[npc]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

void load_set_model0x11f0b0(s32 stage) {
    u8* model_ptr;

    model_ptr = stage_model0x38a220;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, set_model_data0x2ecd70[stage]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}

void load_edit_model0x11f110(s32 edit) {
    u8* model_ptr;

    model_ptr = pl_area_top0x38a224;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, edit_model_data0x386bd0[edit]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, model_ptr, model_ptr + 0x128000); //TODO this constant?
}
//INCLUDE_ASM("asm/main/nonmatchings/load", load_edit_model0x11f110);

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
