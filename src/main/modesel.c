#include "common.h"
#include "main/modesel.h"

char* main_menu_msg0x349210[8] = {
    "ＮＥＷ　ＧＡＭＥ",
    "ＣＯＮＴＩＮＵＥ",
    "ＧＡＬＬＥＲＹ",
    "ＯＰＴＩＯＮＳ",
    "ＤＥＢＵＧ",
    NULL,
    NULL,
    NULL,
};
char* game_menu_msg0x387a70[2] = {
    "街へ行く",
    "村へ行く",
};
char* game_menu_msg20x349230[4] = {
    "街にいる他のハンターたちと狩りに挑みます。",
    "（ＮＥＴＷＯＲＫ ＭＯＤＥ）",
    "村から１人で狩りに出かけます。",
    "（ＳＩＮＧＬＥ ＭＯＤＥ）",
};
s16 menu_str_000x349240[16] = {
    4, 0, 9, 3, 255, 9, 3, 10, 16, -1, 0, 0, 0, 0, 0, 0,
};
s16 menu_str_010x349260[16] = {
    9, 11, 2, 3, 255, 14, 3, 8, 3, 1, 15, -1, 0, 0, 0, 0,
};
s16 menu_str_020x349280[8] = {
    11, 12, 15, 6, 11, 10, 14, -1,
};
s16 menu_str_030x349290[16] = {
    14, 1, 13, 3, 3, 10, 254, 0, 2, 7, 16, 14, 15, -1, 0, 0,
};
s16 menu_str_040x3492b0[24] = {
    1, 5, 0, 13, 0, 1, 15, 3, 13, 252, 1, 13, 3, 0, 15, 6, 11, 10, -1, 0, 0, 0, 0, 0,
};
s16 menu_str_050x3492e0[24] = {
    1, 5, 0, 13, 0, 1, 15, 3, 13, 252, 14, 3, 8, 3, 1, 15, -1, 0, 0, 0, 0, 0, 0, 0,
};
s16 menu_str_060x349310[8] = {
    4, 0, 8, 8, 3, 13, 18, -1,
};
s16 menu_str_num0x349320[8] = {
    9, 11, 7, 13, 18, 16, 7, 0,
};
s16* menu_str0x349330[8] = {
    menu_str_000x349240, menu_str_010x349260, menu_str_020x349280, menu_str_030x349290,
    menu_str_040x3492b0, menu_str_050x3492e0, menu_str_060x349310, NULL,
};
s16 help_mess0x349350[8] = {
    50, 342, 5140, 1051, 0, 4, 8208, -16320,
};
char* omake_str0x349360[12] = {
    "Ｅ３公開映像",
    "オープニング",
    "ハンターの集う街",
    "グラビモスの生態",
    "ガノトトスの生態",
    "フルフルの生態",
    "ディアブロスの生態",
    "リオレイアの生態",
    "英雄の証",
    "-------",
    NULL,
    NULL,
};
u16 check_bit_no0x349390[16] = {
    0xFFFF, 0xFFFF, 5, 6, 2, 7, 4, 3, 8, 0, 0, 0, 0, 0, 0, 0,
};
s16 movie_no0x3493b0[12] = {
    8, 0, 4, 6, 1, 7, 3, 2, 5, 0, 0, 0,
};

INCLUDE_RODATA("asm/nonmatchings/main/modesel", @4080x36d190); // "%s"

INCLUDE_ASM("asm/nonmatchings/main/modesel", Select_task0x23a0f0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", csub000x23a230);

INCLUDE_ASM("asm/nonmatchings/main/modesel", ck_start_sw0x23a350);

INCLUDE_ASM("asm/nonmatchings/main/modesel", init_mode_sel0x23a370);

INCLUDE_ASM("asm/nonmatchings/main/modesel", sel_sel_sub0x23a3e0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", mode_sel0x23a4b0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", mode_sel_end0x23a7f0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", mode_sel_exit0x23a9c0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", key_rept_du0x23aa60);

INCLUDE_ASM("asm/nonmatchings/main/modesel", disp_mode_menu0x23ab50);

INCLUDE_ASM("asm/nonmatchings/main/modesel", Sel_back_disp0x23af30);

INCLUDE_ASM("asm/nonmatchings/main/modesel", Sel_menu_disp0x23afc0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", Sel_csr_disp0x23b2e0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_check0x23b4b0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", disp_omake_menu0x23b500);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_init0x23b790);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_main0x23b810);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_play0x23ba80);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_exit0x23bc90);

INCLUDE_ASM("asm/nonmatchings/main/modesel", Omake_task0x23bd00);
