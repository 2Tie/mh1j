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

typedef struct OPTION_CFG {
    /* 0x00 */ SOUND_MODE sound;
    /* 0x01 */ s8 BGM_vol;
    /* 0x02 */ s8 SFX_vol;
    /* 0x03 */ bool vibration;
    /* 0x04 */ GUN_TARGETING targeting;
    /* 0x05 */ s8 screen_pos_x;
    /* 0x06 */ s8 screen_pos_y;
    /* 0x07 */ u8 pad[9];
} OPTION_CFG; // size: 0x10 (16)

typedef struct USER_SAVE {
    u8 unk[0x480];
} USER_SAVE; // size: 0x480 (1152)

typedef struct REIBUN {
    u8 unk[0x21C];
} REIBUN; // size: 0x21C (540)

typedef struct OPTION_WORK {
    /* 0x000 */ OPTION_CFG cfg;
    /* 0x010 */ USER_SAVE saves[3];
    /* 0xD90 */ u8 unk_D90[0x20];
    /* 0xDB0 */ REIBUN reibun;
    /* 0xFCC */ s16 unk_FCC;
    /* 0xFCE */ u8 unk_FCE;
    /* 0xFCF */ u8 unk_FCF[0x231];
} OPTION_WORK; // size: 0x1200 (4608)

#endif