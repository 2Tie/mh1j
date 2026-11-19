#include "common.h"
#include "lib/AcrSDK/common/plahi.h"

extern s32 tree_model_num0x38a304;

//protos
static TAG_CONTAINER* GetFileHeadAHI0x190230(TAG_CONTAINER*);
AHI_DATA* GetDataHeadAHI0x190240(TAG_CONTAINER*, s32);
s32 plAHIGetTreeModelNum20x1901a0(AHI*, HIERARCHY_NODE*);
HIERARCHY_NODE* GetModelDataAHI0x190340(AHI*, HIERARCHY_NODE*);
s32 plAHIGetTreeModelNum0x190170(AHI*, u32);
void GetTreeModelNum0x1901c0(AHI*, HIERARCHY_NODE*);

//implementations
s32 plAHIGetModelNum0x1900a0(AHI* arg0) {
    s32 models;
    TAG_CONTAINER* cont;

    cont = GetFileHeadAHI0x190230(&arg0->cont);
    models = cont->children;
    if (cont->tag & 0x80000000) {
        models -= 1;
    }
    return models;
}

s32 plAHIGetTreeNum0x1900e0(AHI* ahi) {
    AHI_DATA* cont;

    cont = GetDataHeadAHI0x190240(&ahi->cont, 0);
    if (cont != NULL) {
        return cont->cont.children;
    }
    return 0;
}

HIERARCHY_NODE* plAHIGetTreeRootModel0x190110(AHI* ahi, u32 root) {
    AHI_DATA* cont;

    cont = GetDataHeadAHI0x190240(&ahi->cont, 0);
    if ((cont != NULL) && (root < cont->cont.children)) {
        return cont->roots[root];
    }
    return (HIERARCHY_NODE*)-1;
}

s32 plAHIGetTreeModelNum0x190170(AHI* ahi, u32 root) {
    return plAHIGetTreeModelNum20x1901a0(ahi, plAHIGetTreeRootModel0x190110(ahi, root));
}

s32 plAHIGetTreeModelNum20x1901a0(AHI* ahi, HIERARCHY_NODE* cont) {
    tree_model_num0x38a304 = 0;
    GetTreeModelNum0x1901c0(ahi, cont);
    return tree_model_num0x38a304;
}

void GetTreeModelNum0x1901c0(AHI* ahi, HIERARCHY_NODE* cont) {
    HIERARCHY_NODE* next;
    HIERARCHY_NODE* data;

    tree_model_num0x38a304 += 1;
    data = GetModelDataAHI0x190340(ahi, cont);
    next = data->child;
    if ((s32)next != -1) {
        GetTreeModelNum0x1901c0(ahi, next);
    }
    next = data->sibling;
    if ((s32)next != -1) {
        GetTreeModelNum0x1901c0(ahi, next);
    }
}

static TAG_CONTAINER* GetFileHeadAHI0x190230(TAG_CONTAINER* ptr) {
    return ptr;
}

AHI_DATA* GetDataHeadAHI0x190240(TAG_CONTAINER* cont, s32 tag) {
    TAG_CONTAINER* head;
    u32 i;

    head = GetFileHeadAHI0x190230(cont);
    cont = (TAG_CONTAINER*)(cont+1);
    
    for(i = 0; head->children > i ; i++){
        if ((u8)cont->tag == tag) {
            return (AHI_DATA*)cont;
        }
        cont = (TAG_CONTAINER*)((s32)cont + cont->size);
    }
    return NULL;
}

TAG_CONTAINER* GetModelDataHeadAHI0x1902b0(TAG_CONTAINER* ptr, s32 which_child) {
    s32 cur_child;
    u32 i;
    u32 children;

    cur_child = 0;
    children = GetFileHeadAHI0x190230(ptr)->children;
    if (which_child < children) {
        ptr = ptr + 1;
        
        for (i = 0;children > i; i += 1) {
            if ((u8)ptr->tag != 0) {
                if (cur_child == which_child) {
                    return ptr;
                }
                cur_child += 1;
            }
            ptr = (TAG_CONTAINER*)((s32)ptr + ptr->size);
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", GetModelDataAHI0x190340);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plGetInitMotionSetSizeFromAHI0x190370);

INCLUDE_ASM("asm/nonmatchings/lib/AcrSDK/common/plahi", plCreateInitMotionSetFromAHI0x1903d0);
