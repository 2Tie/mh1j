#ifndef MODESEL_H
#define MODESEL_H

#include "types.h"

typedef struct TASK TASK; // size: 0x20 (32)

void Select_task0x23a0f0(TASK* task);
void csub000x23a230(TASK* task);
s32 ck_start_sw0x23a350(void);
void init_mode_sel0x23a370(TASK* task);
void sel_sel_sub0x23a3e0(u16 input_current, u16 input_pressed, u8* cursor, u8 max_items);
void mode_sel0x23a4b0(TASK* task, u16 input_current, u16 input_pressed);
void mode_sel_end0x23a7f0(TASK* task);
void mode_sel_exit0x23a9c0(TASK* task);
s32 key_rept_du0x23aa60(s32 arg0, u16 input_current, u16 input_pressed);
void disp_mode_menu0x23ab50(void);
void Sel_back_disp0x23af30(u32 arg0);
void Sel_menu_disp0x23afc0(s16 menu_id);
void Sel_csr_disp0x23b2e0(s16 pos_x, s16 pos_y, s16 width, s16 height, u32 color);
s32 omake_check0x23b4b0(s32 arg0);
void disp_omake_menu0x23b500(TASK* task);
void omake_init0x23b790(TASK* task);
void omake_main0x23b810(TASK* task);
void omake_play0x23ba80(TASK* task);
void omake_exit0x23bc90(TASK* task);
void Omake_task0x23bd00(TASK* task);

#endif