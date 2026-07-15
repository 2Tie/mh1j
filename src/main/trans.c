#include "common.h"
#include "structs.h"

extern PLAYER_WORK player_work0x3e4bf0[8];
extern GAME_WORK game_w0x3f33f0;
extern prim ot00x3f1ed0;
extern prim ot10x3f1e50;
extern prim ot20x3f1e10;
extern prim ot30x3f1df0;
extern short* ptmat_tbl0x3018f0[6];
// Unclear what type below should be
extern int ot40x38a1a4;
extern int ot50x38a1a0;
extern int ot60x38a19c;
extern int ot70x38a198;
extern int ot80x38a194;

extern void player_trans0x1678c0(PLAYER_WORK*, int);
extern void Lb_player_trans0x168100(PLAYER_WORK*, int);
extern void Ed_player_trans0x168700(PLAYER_WORK*, int);
extern void GameTrans0x163b60();
extern void InitRenderState0x161580(int);
extern void SetFilterMode0x161500(int);
extern void SetTrnslMode0x161480(int, int);
extern void draw_prim0x169770(prim*);
extern void font_draw_end0x1626f0();
extern void font_draw_stack_no0x161960(int);
extern void light_set0x11e4c0(int);
extern void stage_spr_disp0x160ab0(void);
extern void trans_eft0x1012b0();
extern void trans_eft_up0x101330();
extern void trans_set0x155470();
extern void trans_shell0x159280();
extern void trans_sprite0x15aed0();
extern void trans_stage0x15cd90();
extern void flSetRenderState0x177720(u8, MATRIX);
extern void flfntSetHalftype0x216910(int);
extern void flmatCopy0x172cb0(MATRIX, MATRIX);
extern void flmatInit0x171ce0(MATRIX);
extern void flmatMul0x172a30(MATRIX, MATRIX, MATRIX);
extern void flmatMul330x172b30(MATRIX, MATRIX, MATRIX);
extern void plmatCopy330x193100(MATRIX, MATRIX);

void (*trans_func0x39d870[64])(void);
s32 trans_num0x38a10c;
s32 trans_end0x38a108;

void TransReset0x163ab0(void) {
    int i;
    void (**fn_table)(void);

    trans_num0x38a10c = 0;
    i = 0;
    fn_table = trans_func0x39d870;
    while (i < 0x40) {
        i += 8;
        fn_table[0] = 0;
        fn_table[1] = 0;
        fn_table[2] = 0;
        fn_table[3] = 0;
        fn_table[4] = 0;
        fn_table[5] = 0;
        fn_table[6] = 0;
        fn_table[7] = 0;
        fn_table = fn_table + 8;
    }
}

void TransSet0x163b00(void* fn_entry) {
    if (trans_end0x38a108 != 0)
        TransReset0x163ab0();

    if (trans_num0x38a10c != 0x40) {
        (trans_func0x39d870)[trans_num0x38a10c] = fn_entry;
        trans_num0x38a10c += 1;
    }
}

void GameTrans0x163b60(void) {
    void (**fn_table)(void);
    int i;
    fn_table = trans_func0x39d870;
    for (i = trans_num0x38a10c; i != 0; i -= 1) {
        fn_table[0]();
        fn_table += 1;
    }
}

void trans0x163bc0(void) {
    SetFilterMode0x161500(0);
    SetTrnslMode0x161480(4, 5);
    flSetRenderState0x177720(0x60, (void*) 0); // Should be type MATRIX
    flSetRenderState0x177720(0x6C, (void*) 1); // Should be type MATRIX
    flfntSetHalftype0x216910(1);
    trans_stage0x15cd90();
    trans_eft_up0x101330();
    GameTrans0x163b60();
    light_set0x11e4c0(1);
    trans_shell0x159280();
    draw_prim0x169770(&ot10x3f1e50);
    draw_prim0x169770(&ot30x3f1df0);
    draw_prim0x169770(&ot00x3f1ed0);
    light_set0x11e4c0(1);
    trans_set0x155470();
    trans_eft0x1012b0();
    draw_prim0x169770((prim*) &ot40x38a1a4);

    if ((game_w0x3f33f0.top_state == 2 || game_w0x3f33f0.top_state == 3))
        stage_spr_disp0x160ab0();

    flSetRenderState0x177720(0x6D, (void*) 7); // Should be type MATRIX
    trans_sprite0x15aed0();
    flSetRenderState0x177720(0x6D, (void*) 3); // Should be type MATRIX
    draw_prim0x169770((prim*) &ot50x38a1a0);
    font_draw_stack_no0x161960(0);
    draw_prim0x169770((prim*) &ot60x38a19c);
    font_draw_stack_no0x161960(1);
    draw_prim0x169770((prim*) &ot70x38a198);
    font_draw_stack_no0x161960(2);
    draw_prim0x169770((prim*) &ot80x38a194);
    font_draw_stack_no0x161960(4);
    draw_prim0x169770((prim*) &ot20x3f1e10);
    font_draw_stack_no0x161960(3);
    font_draw_end0x1626f0();
    InitRenderState0x161580(1);
}

int trans_pl_sub0x163d20(int* arg0) {
    PLAYER_WORK* player_w;
    player_w = &player_work0x3e4bf0[*(arg0 + 6)];
    if (player_w->unk_0[0] == 0 || player_w->unk_0[1] == 0)
        return;
    player_trans0x1678c0(player_w, 0);
}

void Lb_trans_pl0x163d80(int* arg0) {
    PLAYER_WORK* player_w;
    player_w = &player_work0x3e4bf0[*(arg0 + 6)];
    if (player_w->unk_0[0] == 0 || player_w->unk_0[1] == 0)
        return;
    Lb_player_trans0x168100(&player_work0x3e4bf0[*(arg0 + 6)], 0);
}

void Ed_trans_pl0x163de0(int* arg0) {
    PLAYER_WORK* player_w;
    player_w = &player_work0x3e4bf0[*(arg0 + 6)];
    if (player_w->unk_0[0] == 0 || player_w->unk_0[1] == 0)
        return;
    Ed_player_trans0x168700(player_w, 0);
}

void SetPartsTrans0x163e40(PART_WORK* part_w, PLAYER_WORK* player_w, short body_part, short arg3) {
    short idx;
    MATRIX mat1;
    MATRIX mat2;

    idx = (ptmat_tbl0x3018f0[body_part])[part_w->unkC4];
    if (idx > 0) {
        if (idx < 0x40) {
            flmatCopy0x172cb0(mat2, player_w->part_ptrs[idx & 0x3F]->matrix);
        } else {
            flmatCopy0x172cb0(mat2, part_w->unk0);
            plmatCopy330x193100(mat2, player_w->part_ptrs[idx & 0x3Fu]->matrix);
            flmatMul330x172b30(mat2, part_w->matrix, player_w->part_ptrs[idx & 0x3Fu]->matrix);
        }
    } else {
        flmatInit0x171ce0(mat2);
        mat2[3][0] = part_w->unk0[3][0];
        mat2[3][1] = part_w->unk0[3][1];
        mat2[3][2] = part_w->unk0[3][2];
    }
    flmatMul0x172a30(mat1, part_w->unk80, mat2);
    flSetRenderState0x177720(part_w->unkC4 + 0x1AU, mat1);

    if (part_w->unkD0 != NULL)
        SetPartsTrans0x163e40(part_w->unkD0, player_w, body_part, arg3);

    if (part_w->unkCC != NULL)
        SetPartsTrans0x163e40(part_w->unkCC, player_w, body_part, arg3);
}

void SetPartsTrans20x163fb0(PART_WORK* part_w, PLAYER_WORK* player_w, short body_part, s32 arg3, MATRIX mat_param) {
    short idx;
    MATRIX mat1;
    MATRIX mat2;

    idx = (ptmat_tbl0x3018f0[body_part])[part_w->unkC4];
    if (idx > 0) {
        if (idx < 0x40) {
            flmatCopy0x172cb0(mat2, player_w->part_ptrs[idx & 0x3F]->matrix);
        } else {
            flmatMul0x172a30(mat2, part_w->matrix, mat_param);
        }
    } else {
        flmatInit0x171ce0(mat2);
        mat2[3][0] = part_w->unk0[3][0];
        mat2[3][1] = part_w->unk0[3][1];
        mat2[3][2] = part_w->unk0[3][2];
    }
    flmatMul0x172a30(mat1, part_w->unk80, mat2);
    flSetRenderState0x177720((part_w->unkC4 + 0x1A), mat1);

    if (part_w->unkD0 != NULL)
        SetPartsTrans20x163fb0(part_w->unkD0, player_w, body_part, arg3, mat2);

    if (part_w->unkCC != NULL)
        SetPartsTrans20x163fb0(part_w->unkCC, player_w, body_part, arg3, mat_param);
}
