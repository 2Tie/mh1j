#include "common.h"
#include "main/scheduler.h"
#include "structs.h"

extern void* memset0x19dd28(void*, u8, u32);
extern void Select_task0x23a0f0(struct TASK*);
extern void TransReset0x163ab0();
extern u32 ran_suu0x161230(s32);

extern SYSTEM_WORK system_w0x3f3690;
extern GAME_WORK game_w0x3f33f0;
extern u16 System_flag0x38a1fc;
extern u16 System_timer0x38a1f4;
extern s16 spr_list_no0x38a0f8;

//bss
TASK tcb_w0x3963b0[0x10];

void* SchedulerInit0x125060(void) {
    return memset0x19dd28(&tcb_w0x3963b0, 0, 0x200);
}

void Scheduler0x125080(void) {
    TASK* task;
    s16 flag;
    s32 tasknum;
    s32 reset;

    System_timer0x38a1f4 += 1;
    ran_suu0x161230(1);
    if ((System_flag0x38a1fc == 0) && ((system_w0x3f3690.unk_03 == 0) || (game_w0x3f33f0.unk_22[1] == 0))) {
        reset = 0;
    } else {
        reset = 1;
    }
    if (reset == 0) {
        TransReset0x163ab0();
        spr_list_no0x38a0f8 = 0;
    }

    for(tasknum = 0, task = tcb_w0x3963b0; tasknum < 0x10; tasknum++, task++) {
        if ((reset == 0) || (0xB < tasknum)) {
            flag = task->flags;
            switch(flag) {
                case TASK_KILL: break;
                case TASK_TRIGGERED:
                    task->flags = TASK_RUNNING;
                    break;
                case TASK_RUNNING | TASK_TRIGGERED:
                    task->flags = TASK_RUNNING;
                    break;
                case TASK_RUNNING:
                    task->task((struct TASK*)task);
                    break;
                case TASK_SLEEP: break;
                case TASK_SIGNAL:
                    task->timer = 0;
                    task->flags = TASK_TRIGGERED;
                    break;
                case TASK_TIMER:
                    task->timer -= 1;
                    if (task->timer < 0) {
                        task->timer = 0;
                    } else if (task->timer == 0) {
                        task->flags = TASK_TRIGGERED;
                    }
                    break;
            }
        }
    }
}

void Tsk_Execute0x125200(void* task_func, s32 which) {
    TASK* task;

    task = &tcb_w0x3963b0[(s16)which];
    memset0x19dd28(task, 0, 0x20);
    task->flags = 0xC;
    task->task = task_func;
}

void Select_Tsk_Execute0x125260(void) {
    TASK* task = &tcb_w0x3963b0[1];

    memset0x19dd28(task, 0, 0x20);
    task->flags = TASK_TRIGGERED | TASK_RUNNING;
    task->task = Select_task0x23a0f0;
    task->type = 1; // TODO constant?
}

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
