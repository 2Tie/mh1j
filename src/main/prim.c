#include "common.h"
#include "structs.h"

extern prim prim0x3eddf0[0x200]; //migrate these when the file's done
extern prim prim20x3ebdf0[0x100];
extern prim pit_prim0x3ebd70[4];
extern u32 prim_free_top0x38a190;
extern u32 prim_free_top20x38a18c;

void prim_init_sub0x169230(prim* primptr, s32 elements) {
    s32 i = 0;
    if (0 < elements) {
        do {
            memset0x19dd28(primptr, 0, sizeof(prim));
            i += 1;
            primptr += 1;
        } while (i < elements);
    }
}

void prim_init0x169290(void) {
    prim_init_sub0x169230(prim0x3eddf0, 0x200);
    prim_free_top0x38a190 = 0;
}

void prim_init20x1692c0(void) {
    prim_init_sub0x169230(prim20x3ebdf0, 0x100);
    prim_free_top20x38a18c = 0;
}

void pit_prim_init0x1692f0(void) {
    prim_init_sub0x169230(pit_prim0x3ebd70, 4);
}

INCLUDE_ASM("asm/main/nonmatchings/prim", get_prim_ptr0x169300);

INCLUDE_ASM("asm/main/nonmatchings/prim", get_prim_ptr20x169320);

INCLUDE_ASM("asm/main/nonmatchings/prim", get_prim0x169340);

INCLUDE_ASM("asm/main/nonmatchings/prim", get_prim20x1693d0);

INCLUDE_ASM("asm/main/nonmatchings/prim", release_prim0x169460);

INCLUDE_ASM("asm/main/nonmatchings/prim", release_prim20x1694b0);

INCLUDE_ASM("asm/main/nonmatchings/prim", add_prim0x169530);

INCLUDE_ASM("asm/main/nonmatchings/prim", add_prim20x169710);

INCLUDE_ASM("asm/main/nonmatchings/prim", draw_prim0x169770);
