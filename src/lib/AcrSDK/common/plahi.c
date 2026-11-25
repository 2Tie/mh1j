#include "common.h"
#include "lib/AcrSDK/common/plahi.h"

extern s32 tree_model_num0x38a304;

//protos
static TAG_CONTAINER* GetFileHeadAHI0x190230(TAG_CONTAINER*);
AHI_DATA* GetDataHeadAHI0x190240(TAG_CONTAINER*, s32);
s32 plAHIGetTreeModelNum20x1901a0(AHI*, s32);
HIERARCHY_NODE* GetModelDataAHI0x190340(TAG_CONTAINER*, s32);
s32 plAHIGetTreeModelNum0x190170(AHI*, u32);
void GetTreeModelNum0x1901c0(AHI*, s32);

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

s32 plAHIGetTreeRootModel0x190110(AHI* ahi, u32 root) {
    AHI_DATA* cont;

    cont = GetDataHeadAHI0x190240(&ahi->cont, 0);
    if ((cont != NULL) && (root < cont->cont.children)) {
        return cont->roots[root];
    }
    return -1;
}

s32 plAHIGetTreeModelNum0x190170(AHI* ahi, u32 root) {
    return plAHIGetTreeModelNum20x1901a0(ahi, plAHIGetTreeRootModel0x190110(ahi, root));
}

s32 plAHIGetTreeModelNum20x1901a0(AHI* ahi, s32 rootidx) {
    tree_model_num0x38a304 = 0;
    GetTreeModelNum0x1901c0(ahi, rootidx);
    return tree_model_num0x38a304;
}

void GetTreeModelNum0x1901c0(AHI* ahi, s32 rootidx) {
    s32 next;
    HIERARCHY_NODE* data;

    tree_model_num0x38a304 += 1;
    data = GetModelDataAHI0x190340(&ahi->cont, rootidx);
    next = data->child;
    if (next != -1) {
        GetTreeModelNum0x1901c0(ahi, next);
    }
    next = data->sibling;
    if (next != -1) {
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

HIERARCHY_NODE* GetModelDataAHI0x190340(TAG_CONTAINER* ptr, s32 which_child) {
    TAG_CONTAINER* temp_v0;

    temp_v0 = GetModelDataHeadAHI0x1902b0(ptr, which_child);
    if (temp_v0 != NULL) {
        return (HIERARCHY_NODE*)((s32)temp_v0 + sizeof(TAG_CONTAINER));
    }
    return NULL;
}

s32 plGetInitMotionSetSizeFromAHI0x190370(AHI* ahi, s32 root) {
    s32 num;
    
    if (root >= plAHIGetTreeNum0x1900e0(ahi)) {
        return 0;
    }
    num = plAHIGetTreeModelNum0x190170(ahi, root);
    return (num * sizeof(INIT_MOT_BONE)) + sizeof(INIT_MOTION_SET);
}

s32 plCreateInitMotionSetFromAHI0x1903d0(INIT_MOTION_SET* out, INIT_MOTION_SET* work, AHI* ahi, s32 root) {
    s32 bone_total;
    s32 cur_bone;
    s32 root_model;
    HIERARCHY_NODE* ahi_bone;
    INIT_MOT_BONE* bones;
    INIT_MOT_BONE* bone;
    s32 el;

    if (root >= plAHIGetTreeNum0x1900e0(ahi)) {
        return 0;
    }
    work->size = plGetInitMotionSetSizeFromAHI0x190370(ahi, root);
    bone_total = plAHIGetTreeModelNum0x190170(ahi, root);
    work->bone_total = bone_total;
    work->unk_4 = 0x10;
    bones = work->bones;
    
    work->work = NULL;
    for (cur_bone = 0; cur_bone < bone_total; cur_bone += 1) {
        bone = &bones[cur_bone];
        for(el = 0; el < 4; el++)
        {
            bone->scale[el] = 0;
            bone->rotate[el] = 0;
            bone->translate[el] = 0;
        }
    }
    root_model = plAHIGetTreeRootModel0x190110(ahi, root);
    
    for (cur_bone = 0; cur_bone < bone_total; cur_bone += 1) {
        ahi_bone = GetModelDataAHI0x190340(&ahi->cont, cur_bone + root_model);
        bones->id = ahi_bone->id;
        bones->chain = ahi_bone->chain;
        bones->child = ahi_bone->child;
        bones->sibling = ahi_bone->sibling;
        if (bones->child != -1) 
            bones->child -= root_model; //initmot idx are relative to root, ahi idx are global
        if (bones->sibling != -1)
            bones->sibling -= root_model;
            
        bones->unk_A = ahi_bone->unk;

        for(el = 0; el < 4; el++){
            bones->scale[el] = ahi_bone->scale[el];
            bones->rotate[el] = ahi_bone->rotate[el];
            bones->translate[el] = ahi_bone->translate[el];
        }
        bones ++;
    }
    *out = *work;
    out->work = work;
    return 1;
}
