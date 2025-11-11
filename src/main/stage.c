#include "common.h"
#include "structs.h"
#pragma cats off
extern void * memset0x19dd28(void *__s,int __c,size_t __n);
s16 flash_timer0x38a118;
s16 flash_flag0x38a114;

extern STAGE_WORK stage_work0x3d8230;

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_w_init0x15bab0);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_fog_set0x15bb60);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @550x35b810);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @560x35b818);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @570x35b820);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @580x35b828);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @590x35b838);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @600x35b840);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @610x35b848);

INCLUDE_RODATA("asm/main/nonmatchings/stage", @620x35b858);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_set_set0x15bbe0);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_mv_ck0x15c210);

void * clr_stg_work0x15c490(void) {
    return memset0x19dd28(&stage_work0x3d8230, 0, 100);
}

void clr_flash0x15c4b0(void) {
    flash_flag0x38a114 = 0;
    flash_timer0x38a118 = 0;
}

INCLUDE_ASM("asm/main/nonmatchings/stage", Stage_env_ck0x15c4c0);

INCLUDE_ASM("asm/main/nonmatchings/stage", Pile_on0x15c4e0);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_i0x15c520);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_se_move0x15c6b0);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_m0x15c940);

INCLUDE_ASM("asm/main/nonmatchings/stage", move_stage0x15cce0);

INCLUDE_ASM("asm/main/nonmatchings/stage", trans_stage_sub0x15cd40);

INCLUDE_ASM("asm/main/nonmatchings/stage", trans_stage0x15cd90);

INCLUDE_ASM("asm/main/nonmatchings/stage", spr_disp_sub0x1608c0);

INCLUDE_ASM("asm/main/nonmatchings/stage", stage_spr_disp0x160ab0);
