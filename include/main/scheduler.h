#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "types.h"
#include "common.h"

typedef enum {
    TASK_KILL = 0,
    TASK_SLEEP = 1 << 0,
    TASK_SIGNAL = 1 << 1,
    TASK_TRIGGERED = 1 << 2,
    TASK_RUNNING = 1 << 3,
    TASK_TIMER = 1 << 4,
    DUMMY_16BIT = 0xFFFF //s16 size
} TASK_FLAG;

typedef struct {
    /* 0x00 */ TASK_FLAG flags;
    /* 0x02 */ s16 timer;
    /* 0x04 */ void (*task)(struct TASK *);
    /* 0x08 */ u8 unk_8; // state
    /* 0x09 */ u8 unk_9; // state sub
    /* 0x0A */ u8 unk_a;
    /* 0x0B */ u8 unk_b;
    /* 0x0C */ s16 unk_c;
    /* 0x0E */ s16 unk_e;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk_12[2];
    /* 0x14 */ u8 unk_14; // cursor
    /* 0x15 */ u8 unk_15; // cursor sub
    /* 0x16 */ u8 unk_16[0xA];
} TASK; // size: 0x20 (32)

#endif
