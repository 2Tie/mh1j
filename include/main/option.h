#ifndef OPTION_H
#define OPTION_H

#include "types.h"

typedef enum {
    MONO,
    STEREO
} SOUND_MODE;

typedef enum {
    NORMAL,
    REVERSE_1,
    REVERSE_2
} GUN_TARGETING;

typedef enum {
    OPT_TSK_INIT,
    OPT_TSK_MAIN_MENU,
    OPT_TSK_SUB_MENU,
    OPT_TSK_NONE,
    OPT_TSK_EXIT
} OPTION_TSK_STATE;

typedef enum {
    OPT_EXIT_INIT,
    OPT_EXIT_MC,
    OPT_EXIT_FADE,
    OPT_EXIT_FINALIZE,
} OPTION_TSK_EXIT;

typedef enum {
    OPT_SOUND,
    OPT_BGM_LEVEL,
    OPT_SE_LEVEL,
    OPT_VIBRATION,
    OPT_TARGETING,
    OPT_SCREEN_ADJUST,
    OPT_DEFAULT_SETTINGS,
    OPT_EXIT
} OPTION_MENU_ITEM;

typedef struct {
    /* 0x00 */ SOUND_MODE sound;
    /* 0x01 */ s8 BGM_vol;
    /* 0x02 */ s8 SFX_vol;
    /* 0x03 */ bool vibration;
    /* 0x04 */ GUN_TARGETING targeting;
    /* 0x05 */ s8 screen_pos_x;
    /* 0x06 */ s8 screen_pos_y;
    /* 0x07 */ u8 pad[9];
} OPTION_CFG; // size: 0x10 (16)

typedef struct {
    u8 unk[0x480];
} USER_SAVE; // size: 0x480 (1152)

typedef struct {
    u8 unk[0x21C];
} REIBUN; // size: 0x21C (540)

typedef struct {
    /* 0x000 */ OPTION_CFG cfg;
    /* 0x010 */ USER_SAVE saves[3];
    /* 0xD90 */ u8 unk_D90[0x20];
    /* 0xDB0 */ REIBUN reibun;
    /* 0xFCC */ s16 unk_FCC;
    /* 0xFCE */ u8 unk_FCE;
    /* 0xFCF */ u8 unk_FCF[0x231];
} OPTION_WORK; // size: 0x1200 (4608)

// Same of TASK in scheduler, change to it
typedef struct {
    /* 0x00 */ u8 unk_0[8];
    /* 0x08 */ OPTION_TSK_STATE state;
    /* 0x09 */ OPTION_TSK_EXIT exit_state;
    /* 0x0A */ u8 exit_timer;
    /* 0x0B */ u8 unk_b[9];
    /* 0x14 */ OPTION_MENU_ITEM cursor;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16[0xA];
} OPTION_TASK; // size: 0x20 (32)

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 direction;
    /* 0x06 */ s8 rotation;
    /* 0x07 */ u8 pad;
} ARROW_ENTRY; // size: 0x8 (8)

void option_default_set0x1267c0(void);
void Option_task0x126800(OPTION_TASK* task);
void option_init0x1268f0(OPTION_TASK* task);
void option_main_menu0x126960(OPTION_TASK* task, u16 input);
void param_change0x126b30(OPTION_TASK* task, s32 direction);
s32 cfg_change_ck0x126c60(void);
void option_sub_menu0x126cc0(OPTION_TASK* task, u16 input);
void option_exit0x126e90(OPTION_TASK* task, u16 input);
void opt_sub_disp0x126fd0(s16 pos_y, char* str);
void disp_option_menu0x127040(OPTION_TASK* task);
void disp_option_sub_menu0x127250(OPTION_TASK* task, u16 input);

#endif