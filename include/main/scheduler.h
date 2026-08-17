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
    /* 0x04 */ void* task;
    /* 0x08 */ u8 type;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ s32 data[5];
} TASK; // size: 0x20

#endif
