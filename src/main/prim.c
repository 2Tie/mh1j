#include "common.h"
#include "structs.h"

extern void flmatrLoad0x173490(f32[], s32);
extern void flvecApplyMat0x172ee0(f32[], f32[], f32[]);
extern void plplAdd0x194990(prim*, s32*);
extern prim* plplNext0x1949b0(prim* []);

extern prim prim0x3eddf0[0x200]; //migrate these when the file's done?
extern prim prim20x3ebdf0[0x100];
extern prim pit_prim0x3ebd70[4];

//sbss
u32 prim_free_top0x38a190;
u32 prim_free_top20x38a18c;

void plplAdd20x1691c0(prim* primlist, s32* order_table) {
    s32 table_floor;
    s32 table;

    while (1) {
        table = *order_table;

        if(table == 0 || !(table & 1))
        {
            *order_table = (s32)primlist | 1;
            primlist->v1 = table;
            break;
        }
        table_floor = table & ~1; //mask off bottom bit?
        if (((prim*)table_floor)->v2 <= primlist->v2) {
            *order_table = (s32)primlist | 1; //force bottom bit?
            primlist->v1 = table;
            break;
        }
        order_table = (s32*) table_floor;
    }
}

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
        if (ptr->trans == 0) {
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
        if (ptr->trans == 0)
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
    six = ptr->v7;
    seven = ptr->v8;
    memset0x19dd28(ptr, 0, sizeof(prim));
    ptr->v7 = six;
    ptr->v8 = seven;
    if (which < prim_free_top20x38a18c) {
        prim_free_top20x38a18c = which;
    }
}

u32 add_prim0x169530(s32* order_table, prim* primlist, u32 order_table_length, s32 first) {
    f32 polydat[4];
    f32 primitive[4];
    f32 mat[16]; //matrix
    u32 which;

    polydat[0] = primlist->v3;
    polydat[1] = primlist->v4;
    polydat[2] = primlist->v5;
    polydat[3] = 1;
    flmatrLoad0x173490(mat, 0x21); //prep a matrix
    flvecApplyMat0x172ee0(primitive, polydat, mat); //apply the transform matrix to primitive, save
    primitive[2] = primitive[2] * -1.0f;
    if (primitive[2] < 0.0f) {
        if (first != 0){ 
            primitive[2] = 0.0f;
        }
        else if(primitive[2] < -1600.0f) {
            return -1;
        }
        else
            primitive[2] = 0.0f;
    }
    primlist->v2 = primitive[2];
    which = (primitive[2] / 65000.0f) * order_table_length;
    if (which >= order_table_length)
        return -1U;
    if (order_table_length == 0x40) {
        plplAdd20x1691c0(primlist, &order_table[((order_table_length - 1) - which)]);
    } else {
        plplAdd0x194990(primlist, &order_table[((order_table_length - 1) - which)]);
    }
    return which;
}

//buflength should always be the number of elements in ot (ordering table), maybe use constants for this?
s32 add_prim20x169710(s32* ot, prim* primlist, s32 which, s32 buflength) {
    if (which >= buflength || which < 0)
        return -1;
    plplAdd0x194990(primlist, &ot[((buflength - 1) - which)]);
    return which;
}

void draw_prim0x169770(prim* primi) {
    while(1){
        primi = plplNext0x1949b0(&primi);
        if (primi == 0) 
            break;
        primi->trans(primi);
    }
}

INCLUDE_ASM("asm/main/nonmatchings/prim", SetDiffuseColor0x1697c0);
