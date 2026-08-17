#include "common.h"
#include "main/scheduler.h"

extern void* memset0x19dd28(void*, u8, u32);

//bss
TASK tcb_w0x3963b0[0x10];

void* SchedulerInit0x125060(void) {
    return memset0x19dd28(&tcb_w0x3963b0, 0, 0x200);
}

INCLUDE_ASM("asm/main/nonmatchings/scheduler", Scheduler0x125080);

void Tsk_Execute0x125200(void* task_func, s32 which) {
    TASK* task;

    task = &tcb_w0x3963b0[(s16)which];
    memset0x19dd28(task, 0, 0x20);
    task->flags = 0xC;
    task->task = task_func;
}

INCLUDE_ASM("asm/main/nonmatchings/scheduler", Select_Tsk_Execute0x125260);

void Tsk_Exit0x1252b0(TASK* task) {
    task->flags = TASK_KILL;
}

void Tsk_Sleep0x1252c0(s32 arg0) {
    tcb_w0x3963b0[(s16)arg0].flags = TASK_SLEEP;
}

void Tsk_Signal0x1252f0(s32 arg0) {
    tcb_w0x3963b0[(s16)arg0].flags = TASK_SIGNAL;
}

void Tsk_Kill0x125320(s32 which) {
    tcb_w0x3963b0[(s16)which].flags = TASK_KILL;
}
