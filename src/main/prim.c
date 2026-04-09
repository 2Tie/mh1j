#include "common.h"
#include "structs.h"

extern void flmatrLoad0x173490(f32[], s32);
extern void flvecApplyMat0x172ee0(f32[], f32[], f32[]);
extern void plplAdd0x194990(prim*, f32*);
extern void plplAdd20x1691c0(prim*, f32*);

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

prim* get_prim_ptr0x169300(s32 which) {
    prim* pointer = 0;
    if (which >= 0) {
        pointer = prim0x3eddf0 + which;
    }
    return pointer;
}

prim* get_prim_ptr20x169320(s32 which) {
    prim* pointer = 0;
    if (which >= 0) {
        pointer = prim20x3ebdf0 + which;
    }
    return pointer;
}

s16 get_prim0x169340(void) {
    prim *ptr;
    s32 top;
    s32 saved;

    saved = prim_free_top0x38a190;
    if (saved >= 0x200)
        return -1;
    ptr = get_prim_ptr0x169300(saved + 1);
    top = prim_free_top0x38a190 + 1;
    while(top < 0x200) {
        if (ptr[0][5] == 0) {
            break;
        }
        top += 1;
        ptr += 1;
    }
    prim_free_top0x38a190 = top;
    return saved;
}

s16 get_prim20x1693d0(void) {
    s32 saved;
    s32 top;
    prim* ptr;

    saved = prim_free_top20x38a18c;
    if (saved >= 0x100)
        return -1;
    ptr = get_prim_ptr20x169320(saved + 1);
    top = prim_free_top20x38a18c + 1;
    while(top < 0x100) {
        if (ptr[0][5] == 0)
            break;
        top += 1;
        ptr += 1;
    }
    prim_free_top20x38a18c = top;
    return saved;
}

void release_prim0x169460(s32 which) {
    memset0x19dd28(get_prim_ptr0x169300(which), 0, sizeof(prim));
    if (which < prim_free_top0x38a190) {
        prim_free_top0x38a190 = which;
    }
}

void release_prim20x1694b0(s32 which) {
    prim* ptr;
    s32 six;
    s32 seven;

    ptr = get_prim_ptr20x169320(which);
    six = (*ptr)[6];
    seven = (*ptr)[7];
    memset0x19dd28(ptr, 0, sizeof(prim));
    (*ptr)[6] = six;
    (*ptr)[7] = seven;
    if (which < prim_free_top20x38a18c) {
        prim_free_top20x38a18c = which;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/prim", add_prim0x169530);

INCLUDE_ASM("asm/main/nonmatchings/prim", add_prim20x169710);

INCLUDE_ASM("asm/main/nonmatchings/prim", draw_prim0x169770);
