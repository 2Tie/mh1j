#include "common.h"

void amo_ahi_expand0x11f350(void * srcbuf, void * amobuf, void* ahibuf);

extern u8* arc_ptr0x38a23c;
extern s32 load_bin0x1003b0(s32, u8*);
extern void SetCameraData0x21f470(u8*);
extern void flReloadTexture0x189cd0(u32, void*);
extern void * memcpy0x19db70(void *, void *, size_t);

extern int pl_motion_data0x2ebc50[];
extern int em_motion_data0x2ec830[];
extern int common_motion_data0x2ebc70[];

extern u8* data_load_ptr0x38a240;
extern u8* stage_model0x38a220;
extern u8* pl_area_top0x38a224;
extern u8* cam_data_area0x38a204;

extern u8* mem_tex0x3f3990[];

extern int stage_model_data0x2ec950[];
extern int effect_model_data0x2ecee0[];
extern int camera_data_tbl0x2ecf00[];
extern int weapon_model_data0x2ec5b0[];
extern int em_model_data0x2ec7a0[];
extern int em_sub_model_data0x2ec8c0[];
extern int npc_model_data0x2eced0[];
extern int set_model_data0x2ecd70[];
extern int edit_model_data0x386bd0[2]; //actually extern, the rest should be in rodata?
extern int* armor_model_f0x2ec590[];
extern int* armor_model_m0x2ec0f0[];

extern s16 reload_tex_id0x38a1b0;
extern s16 reload_tex_num0x38a1ac;
extern s16 reload_tex_total0x38a1a8;

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

void load_armor_model0x11ef10(s32 armorID, s32 bodypart, s32 gender) {
    u8* buff;
    int* file;

    if (gender == 0) {
        file = armor_model_m0x2ec0f0[bodypart];
    } else {
        file = armor_model_f0x2ec590[bodypart];
    }
    buff = pl_area_top0x38a224;
    file += armorID;
    load_file_mdl0x11ed20(data_load_ptr0x38a240, file[0]);
    amo_ahi_expand0x11f350(data_load_ptr0x38a240, buff, buff + 0x128000);
}

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

void debug_model_load0x11f160(void) {
    return;
}

void reload_tex0x11f170(u32 count, u32 id) {
    if (count != 0) {
        flReloadTexture0x189cd0(count, &mem_tex0x3f3990[id]);
        reload_tex_id0x38a1b0 = id;
        reload_tex_num0x38a1ac = count;
        reload_tex_total0x38a1a8 += count;
    }
}

void LoadCameraData0x11f1e0(s32 map) {
    s32 file;
    u8* cam_data;

    file = camera_data_tbl0x2ecf00[map];
    cam_data = 0;
    if (file != 0) {
        load_file_mdl0x11ed20(cam_data_area0x38a204, file);
        cam_data = cam_data_area0x38a204;
    }
    SetCameraData0x21f470(cam_data);
}

INCLUDE_ASM("asm/main/nonmatchings/load", Meltw0x11f230);

s32 GetLinkFileNum0x11f310(u8* buff) {
    return *(s32*)buff; //first value is file count
}

u8* GetLinkFileAddress0x11f320(u8 *buf, s32 file) {
    u8 *addr;
    addr = buf + (file * sizeof(int)*2);//each file has a pos and size
    return buf + *(s32*)(addr + sizeof(int)); //advance past file count to file address, then add that offset to buffer ptr
}

s64 GetLinkFileSize0x11f340(u8 *buf, s32 file) {
    u8 *size;
    size = buf + (file * sizeof(int)*2);//each file has a pos and size
    return *(s32 *)(size + sizeof(int) + sizeof(int)); //advance past file count and file's address
}

void amo_ahi_expand0x11f350(void * srcbuf, void * amobuf, void* ahibuf) {
    memcpy0x19db70(amobuf, GetLinkFileAddress0x11f320(srcbuf, 0), GetLinkFileSize0x11f340(srcbuf, 0));
    memcpy0x19db70(ahibuf, GetLinkFileAddress0x11f320(srcbuf, 1), GetLinkFileSize0x11f340(srcbuf, 1));
}
