#include "common.h"
#include "structs.h"
#include "lib/AcrSDK/common/plaan.h"

extern f32 plGetFcurveTime0x192fa0(MOTION_HOLDER*);
extern f32 plGetFcurveStartTime0x192ec0(MOTION_HOLDER*);
extern void* fmsAllocMemory0x16ac30(FL_FMS*, s32, s32);
extern s32 fmsInitialize0x16abb0(FL_FMS*, u8*, s32, s32);

u8* base_addr0x38a300;

extern FL_FMS fms0x454950;


//protos
static s32 plAANGetModelNum0x190080(AAN*);
s32 plGetMotionSizeFromAAN0x18f260(AAN_CONTAINER*);
f32 plAANGetMotionEndTime0x18ff40(MOTION_REFERENCE*);
f32 plAANGetMotionStartTime0x18ffe0(MOTION_REFERENCE*);
void plCreateMotionFromAAN0x18f6b0(MOTION_REFERENCE*, AAN*, s32);
void plCreateMotionFromAANSub_SRT0x18f790(AAN*, MOTION_REFERENCE*, AAN_CONTAINER*, s32);
void plCreateFcurveDataAAN0x18f9f0(AAN_CONTAINER*, MOTION_HOLDER*);
void plCreateFcurveDataAAN_Linear0x18fac0(AAN_CONTAINER*, MOTION_HOLDER*);
void plCreateFcurveDataAAN_Hermite0x18fb70(AAN_CONTAINER*, MOTION_HOLDER*);
void plCreateFcurveDataAAN_Complex0x18fc30(AAN_CONTAINER*, MOTION_HOLDER*);
void plCreateFcurveDataAAN_LinearShort0x18fd00(AAN_CONTAINER*, MOTION_HOLDER*);
void plCreateFcurveDataAAN_HermiteShort0x18fdb0(AAN_CONTAINER*, MOTION_HOLDER*);
void plCreateFcurveDataAAN_ComplexShort0x18fe70(AAN_CONTAINER*, MOTION_HOLDER*);

static AAN* GetFileHeadAAN0x18f0b0(AAN* ptr){
	return ptr;
}

AAN_CONTAINER* GetModelHeadAAN0x18f0c0(AAN* arg1, s32 which) {
    AAN* addr;
    AAN_CONTAINER* scratch;
    s32 i;

    addr = GetFileHeadAAN0x18f0b0(arg1);
    scratch = addr->tags;
    addr += 1;
    i = 0;
    if (0 < which) {
        if (8 < which) {
            do{
                i += 8;
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + addr->head.cont.size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + scratch->size);
                addr = (AAN*)scratch;
            } while (i < (which - 8));
        }
        if (i < which) {
            do {
                scratch = (AAN_CONTAINER*)((u8*)(scratch) + addr->head.cont.size);
                addr = (AAN*)scratch;
                i += 1;
            } while (i < which);
        }
    }
    return &addr->head.cont;
}

bool plGetLoopInfoAan0x18f180(AAN* arg0, f32* pt) {
    AAN* head;
    bool ret;

    head = GetFileHeadAAN0x18f0b0(arg0);
    if (head->head.animtype != 0) {
        ret = true;
        *pt = head->head.loop;
    } else {
        ret = false;
        *pt = 0;
    }
    return ret;
}

s32 plGetMotionSetSizeFromAAN0x18f1d0(AAN* arg0) {
    s32 i;
    AAN_CONTAINER* head;
    s32 children;
    s32 size;

    children = plAANGetModelNum0x190080(arg0);
    size = (children * 4) + sizeof(MOTION_SET); //size of MOTION_SET, plus a pointer per children it reserves
    for(i = 0; i < children; i += 1) {
        head = GetModelHeadAAN0x18f0c0(arg0, i); //seek to child
        size += sizeof(MOTION_REFERENCE);
        size += head->children * sizeof(MOTION_HOLDER);
        size += plGetMotionSizeFromAAN0x18f260(head);
    }
    return size;
}

s32 plGetMotionSizeFromAAN0x18f260(AAN_CONTAINER* arg0) {
    AAN_CONTAINER* container;
    s32 children;
    s32 size;
    s32 i;
    
    children = arg0->children;
    container = arg0 + 1;
    size = 0;
    for(i = 0; i < children; i++) {
        switch ((container->type & 0xFF0000) >> 0x10) {
        case FCV_LINEAR:
            size += container->children * sizeof(FCV_DATA_LINEAR);
            break;
        case FCV_HERMITE:
            size += container->children * sizeof(FCV_DATA_HERMITE);
            break;
        case FCV_COMPLEX:
            size += container->children * sizeof(FCV_DATA_COMPLEX);
            break;
        case FCV_LINEAR_SHORT:
            size += container->children * sizeof(FCV_DATA_LINEAR_SHORT);
            break;
        case FCV_HERMITE_SHORT:
            size += container->children * sizeof(FCV_DATA_HERMITE_SHORT);
            break;
        case FCV_COMPLEX_SHORT:
            size += container->children * sizeof(FCV_DATA_COMPLEX_SHORT);
            break;
        }
        container = (AAN_CONTAINER*)((int)container + container->size);
    }
    
    return size;
}

s32 plCreateMotionSetFromAAN0x18f370(MOTION_SET* set, u8* base, AAN* aan) {
    f32 loop;
    f32 candidate;
    f32 earliest_start;
    f32 latest_end;
    s32 i;
    s32 motion_set_size;
    s32 models_num;
    MOTION_SET* temp_set;
    MOTION_REFERENCE** mot_ref;

    motion_set_size = plGetMotionSetSizeFromAAN0x18f1d0(aan);
    base_addr0x38a300 = base;
    plFCVSetBaseAddress0x192e30(base);
    fmsInitialize0x16abb0(&fms0x454950, base, motion_set_size, 1);
    temp_set = fmsAllocMemory0x16ac30(&fms0x454950, 0x20, 0);
    models_num = plAANGetModelNum0x190080(aan);
    temp_set->flags = 0U;
    temp_set->model_count = models_num;
    temp_set->models_ptrs = fmsAllocMemory0x16ac30(&fms0x454950, models_num * 4, 0);
    temp_set->base_addr = 0;
    temp_set->total_size = motion_set_size;
    mot_ref = temp_set->models_ptrs;
    earliest_start = 1e10f;
    latest_end = 0.0f;
	
    for (i=0; i < models_num; i++,mot_ref += 1) {
        *mot_ref = fmsAllocMemory0x16ac30(&fms0x454950, 8, 0);
        plCreateMotionFromAAN0x18f6b0(*mot_ref, aan, i);
        candidate = plAANGetMotionEndTime0x18ff40(*mot_ref);
        if (!(candidate <= latest_end)) {
            latest_end = candidate;
        }
        candidate = plAANGetMotionStartTime0x18ffe0(*mot_ref);
        if (candidate < earliest_start) {
            earliest_start = candidate;
        }
    }
    temp_set->earliest_start = earliest_start;
    temp_set->latest_end = latest_end;
	
    if (plGetLoopInfoAan0x18f180(aan, &loop)) {
        temp_set->flags |= 0x8000;
        temp_set->loop_point = loop;
    } else {
        temp_set->flags &= 0x7FFF;
        temp_set->loop_point = 0;
    }
    
    for (i = 0;i < models_num;i++) {
        ((s32*)temp_set->models_ptrs)[i] -= (s32)base_addr0x38a300;
    }
	
    (u8*)temp_set->models_ptrs -= (s32)base_addr0x38a300;
	
    *set = *temp_set;
    set->base_addr = base;
    return 1;
}

void plCreateMotionFromAAN0x18f6b0(MOTION_REFERENCE* mot, AAN* aan, s32 child) {
    AAN* aan_head;
    AAN_CONTAINER* model_head;

    if (plAANGetModelNum0x190080(aan) < child)
        return;
    
    if((model_head = GetModelHeadAAN0x18f0c0(aan, child)) == 0)
        return;
    
    aan_head = GetFileHeadAAN0x18f0b0(aan);
    if(aan_head == NULL) 
        return;
    
    switch ((u8)aan_head->head.cont.type) {
        case 1:
            mot->type = 0x1000;
            break;
        case 2:
            mot->type = 0x2000;
            break;
    }
    switch(mot->type & 0xF000){
        case 0x1000:
        case 0x2000:
            plCreateMotionFromAANSub_SRT0x18f790(aan, mot, model_head, 0);
        break;
    }
}

void plCreateMotionFromAANSub_SRT0x18f790(AAN* arg0, MOTION_REFERENCE* mot, AAN_CONTAINER* container, s32 arg3) {
    MOTION_HOLDER* mot_iter;
    AAN_CONTAINER* cont_iter;
    s32 children;
    s32 i;
    s32 container_ID;

    children = container->children;
    mot->entries = children;
    mot_iter = fmsAllocMemory0x16ac30(&fms0x454950, children * 8, 0);
    
    mot->mot_off = mot_iter;
    for (i = 0; i < children; i++) {
        mot_iter[i].fcv_format = 0x20;
        mot_iter[i].point_count = 0;
    }
    
    cont_iter = container + 1;
    
    for(i = 0; i < children; i ++) {
        container_ID = cont_iter->type;
        if (container_ID & 0x80000000) {
            plCreateFcurveDataAAN0x18f9f0(cont_iter, mot_iter);
            switch (container_ID & 0x1FF) {
            case ANIM_FLAG_SCALE_X:
                mot_iter->anim_target = ANIM_TARGET_SCALE_X;
                break;
            case ANIM_FLAG_SCALE_Y:
                mot_iter->anim_target = ANIM_TARGET_SCALE_Y;
                break;
            case ANIM_FLAG_SCALE_Z:
                mot_iter->anim_target = ANIM_TARGET_SCALE_Z;
                break;
            case ANIM_FLAG_ROTATE_X:
                mot_iter->anim_target = ANIM_TARGET_ROTATE_X;
                break;
            case ANIM_FLAG_ROTATE_Y:
                mot_iter->anim_target = ANIM_TARGET_ROTATE_Y;
                break;
            case ANIM_FLAG_ROTATE_Z:
                mot_iter->anim_target = ANIM_TARGET_ROTATE_Z;
                break;
            case ANIM_FLAG_TRANSLATE_X:
                mot_iter->anim_target = ANIM_TARGET_TRANSLATE_X;
                break;
            case ANIM_FLAG_TRANSLATE_Y:
                mot_iter->anim_target = ANIM_TARGET_TRANSLATE_Y;
                break;
            case ANIM_FLAG_TRANSLATE_Z:
                mot_iter->anim_target = ANIM_TARGET_TRANSLATE_Z;
                break;
            }
        }
        mot_iter += 1;
        cont_iter = (AAN_CONTAINER*)((s32)cont_iter + cont_iter->size);
    }
    mot->mot_off = (MOTION_HOLDER*)((s32)mot->mot_off - (s32)base_addr0x38a300);
}

void plCreateFcurveDataAAN0x18f9f0(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    u32 type;

    type = (aan->type & 0xFF0000) >> 0x10;
    switch (type) {
    case FCV_LINEAR:
        plCreateFcurveDataAAN_Linear0x18fac0(aan, mot);
        return;
    case FCV_HERMITE:
        plCreateFcurveDataAAN_Hermite0x18fb70(aan, mot);
        return;
    case FCV_COMPLEX:
        plCreateFcurveDataAAN_Complex0x18fc30(aan, mot);
        return;
    case FCV_LINEAR_SHORT:
        plCreateFcurveDataAAN_LinearShort0x18fd00(aan, mot);
        return;
    case FCV_HERMITE_SHORT:
        plCreateFcurveDataAAN_HermiteShort0x18fdb0(aan, mot);
        return;
    case FCV_COMPLEX_SHORT:
        plCreateFcurveDataAAN_ComplexShort0x18fe70(aan, mot);
        
    }
}

void plCreateFcurveDataAAN_Linear0x18fac0(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    FCV_DATA_LINEAR* mot_fcv;
    FCV_DATA_LINEAR* file_fcv;
    s32 i;

    mot->fcv_format = FCV_LINEAR;
    file_fcv = (FCV_DATA_LINEAR*)(aan + 1);
    mot->anim_target = 0;
    mot->point_count = aan->children;
    mot_fcv = fmsAllocMemory0x16ac30(&fms0x454950, mot->point_count * sizeof(FCV_DATA_LINEAR), 0);
    mot->fcv_data = mot_fcv;
    for (i = 0; i < mot->point_count; i++) {
        mot_fcv->time = file_fcv->time;
        mot_fcv->value = file_fcv->value;
        file_fcv += 1;
        mot_fcv += 1;
    }
    mot->fcv_data = (FCV_DATA_LINEAR*)((s32)mot->fcv_data - (s32)base_addr0x38a300);
}

void plCreateFcurveDataAAN_Hermite0x18fb70(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    FCV_DATA_HERMITE* mot_fcv;
    FCV_DATA_HERMITE* file_fcv;
    s32 i;

    mot->fcv_format = FCV_HERMITE;
    file_fcv = (FCV_DATA_HERMITE*)(aan + 1);
    mot->anim_target = 0;
    mot->point_count = aan->children;
    mot_fcv = fmsAllocMemory0x16ac30(&fms0x454950, mot->point_count * sizeof(FCV_DATA_HERMITE), 0);
    mot->fcv_data = mot_fcv;
    for(i = 0; i < mot->point_count; i++){
            mot_fcv->time = file_fcv->time;
            mot_fcv->value = file_fcv->value;
            mot_fcv->handle_l = file_fcv->handle_l;
            mot_fcv->handle_r = file_fcv->handle_r;
            file_fcv++;
            mot_fcv++;
    }
    mot->fcv_data = (FCV_DATA_HERMITE*)((s32)mot->fcv_data - (s32)base_addr0x38a300);
}

void plCreateFcurveDataAAN_Complex0x18fc30(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    FCV_DATA_COMPLEX* mot_fcv;
    FCV_DATA_COMPLEX* file_fcv;
    s32 i;

    mot->fcv_format = FCV_COMPLEX;
    file_fcv = (FCV_DATA_COMPLEX*)(aan + 1);
    mot->anim_target = 0;
    mot->point_count = aan->children;
    mot_fcv = fmsAllocMemory0x16ac30(&fms0x454950, mot->point_count * sizeof(FCV_DATA_COMPLEX), 0);
    mot->fcv_data = mot_fcv;
    
    for(i = 0; i < mot->point_count; i++) {
        mot_fcv->type = file_fcv->type;
        mot_fcv->time = file_fcv->time;
        mot_fcv->value = file_fcv->value;
        mot_fcv->handle_l = file_fcv->handle_l;
        mot_fcv->handle_r = file_fcv->handle_r;
        file_fcv++;
        mot_fcv++;
    }
    mot->fcv_data = (FCV_DATA_COMPLEX*)((s32)mot->fcv_data - (s32)base_addr0x38a300);
}

void plCreateFcurveDataAAN_LinearShort0x18fd00(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    FCV_DATA_LINEAR_SHORT* mot_fcv;
    FCV_DATA_LINEAR_SHORT* file_fcv;
    s32 i;

    mot->fcv_format = FCV_LINEAR_SHORT;
    file_fcv = (FCV_DATA_LINEAR_SHORT*)(aan + 1);
    mot->anim_target = 0;
    mot->point_count = aan->children;
    mot_fcv = fmsAllocMemory0x16ac30(&fms0x454950, mot->point_count * sizeof(FCV_DATA_LINEAR_SHORT), 0);
    mot->fcv_data = mot_fcv;
    
    for (i = 0; i < mot->point_count; i++) {
            mot_fcv->time = file_fcv->time;
            mot_fcv->value = file_fcv->value;
            file_fcv++;
            mot_fcv++;
    }
    mot->fcv_data = (FCV_DATA_LINEAR_SHORT*)((s32)mot->fcv_data - (s32)base_addr0x38a300);
}

void plCreateFcurveDataAAN_HermiteShort0x18fdb0(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    FCV_DATA_HERMITE_SHORT* mot_fcv;
    FCV_DATA_HERMITE_SHORT* file_fcv;
    s32 i;

    mot->fcv_format = FCV_HERMITE_SHORT;
    file_fcv = (FCV_DATA_HERMITE_SHORT*)(aan + 1);
    mot->anim_target = 0;
    mot->point_count = aan->children;
    mot_fcv = fmsAllocMemory0x16ac30(&fms0x454950, mot->point_count * sizeof(FCV_DATA_HERMITE_SHORT), 0);
    mot->fcv_data = mot_fcv;
    
    for(i = 0; i < mot->point_count; i++) {
        mot_fcv->time = file_fcv->time;
        mot_fcv->value = file_fcv->value;
        mot_fcv->handle_l = file_fcv->handle_l;
        mot_fcv->handle_r = file_fcv->handle_r;
        file_fcv++;
        mot_fcv++;
    }
    mot->fcv_data = (FCV_DATA_HERMITE_SHORT*)((s32)mot->fcv_data - (s32)base_addr0x38a300);
}

void plCreateFcurveDataAAN_ComplexShort0x18fe70(AAN_CONTAINER* aan, MOTION_HOLDER* mot) {
    FCV_DATA_COMPLEX_SHORT* mot_fcv;
    FCV_DATA_COMPLEX_SHORT* file_fcv;
    s32 i;

    mot->fcv_format = FCV_COMPLEX_SHORT;
    file_fcv = (FCV_DATA_COMPLEX_SHORT*)(aan + 1);
    mot->anim_target = 0;
    mot->point_count = aan->children;
    mot_fcv = fmsAllocMemory0x16ac30(&fms0x454950, mot->point_count * sizeof(FCV_DATA_COMPLEX_SHORT), 0);
    mot->fcv_data = mot_fcv;
    
    for(i = 0; i < mot->point_count; i += 1) {
        mot_fcv->type = file_fcv->type;
        mot_fcv->time = file_fcv->time;
        mot_fcv->value = file_fcv->value;
        mot_fcv->handle_l = file_fcv->handle_l;
        mot_fcv->handle_r = file_fcv->handle_r;
        file_fcv += 1;
        mot_fcv += 1;
    }
    mot->fcv_data = (FCV_DATA_COMPLEX_SHORT*)((s32)mot->fcv_data - (s32)base_addr0x38a300);
}

f32 plAANGetMotionEndTime0x18ff40(MOTION_REFERENCE* arg0) { //passed is pointer to (unpacked) motion data
    f32 candidate;
    f32 latest;
    s32 i;

    latest = 0.0f;
    
    for (i = 0; i < arg0->entries; i += 1) {
        candidate = plGetFcurveTime0x192fa0(&((MOTION_HOLDER*)((u32)arg0->mot_off + (u32)base_addr0x38a300))[i]);
        if (candidate > latest)
            latest = candidate;
    }
    return latest;
}

f32 plAANGetMotionStartTime0x18ffe0(MOTION_REFERENCE* arg0) {
    f32 candidate;
    f32 earliest;
    s32 i;

    earliest = 1e10f;
    
    for (i = 0; i < arg0->entries; i++){
        candidate = plGetFcurveStartTime0x192ec0(&((MOTION_HOLDER*)((s32)arg0->mot_off + (s32)base_addr0x38a300))[i]);
        if (candidate < earliest) 
            earliest = candidate;
    }
    return earliest;
}

s32 plAANGetModelNum0x190080(AAN* arg) {
    return GetFileHeadAAN0x18f0b0(arg)->head.cont.children;
}
