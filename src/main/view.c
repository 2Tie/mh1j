#include "common.h"
#include "structs.h"
#include "junk.h"

extern VIEW_WORK* lpView0x38a110;
extern VIEW_WORK view_work0x39da70;
extern view_work_old view_w0x39d970;
extern f32 fov0x3f1fd0[];

extern void plSetupFOVClipPlanes0x193350(f32, f32, f32, f32, f32*);
extern void flmatrMakeProjection0x1715e0(u8, f32, f32, f32, f32);
extern void flSetRenderState0x177720(u8, void*);
extern f32 flArcTan20x1735e0(f32, f32);
extern f32 flvecCalcDistance0x173140(f32*, f32*);

void View_init0x169a50(void);


void View_initialize0x1699e0(void) {
    lpView0x38a110 = &view_work0x39da70;
    lpView0x38a110->unk_38 = 0;
    lpView0x38a110->unk_3C = 0;
    lpView0x38a110->unk_40 = 0x200;
    lpView0x38a110->unk_44 = 0x1C0;
    lpView0x38a110->unk_48 = 0;
    lpView0x38a110->unk_4C = 1.0;
    View_init0x169a50();
}

void view_reset0x169a30(void) {
    view_w0x39d970.unk1 = 0;
    view_w0x39d970.unk2 = 1;
}

void View_init0x169a50(void) {
    lpView0x38a110->view_angle = 0.87266465; //TODO constant
    lpView0x38a110->view_angle_OLD = -999.0;
    lpView0x38a110->view_roll = 0.0;
}

INCLUDE_ASM("asm/main/nonmatchings/view", View_move0x169a80);

INCLUDE_ASM("asm/main/nonmatchings/view", set_viewproj0x169c20);

void Create_FOV0x169cf0(f32 length) {
    plSetupFOVClipPlanes0x193350(lpView0x38a110->view_angle, SCREEN_RATIO, lpView0x38a110->proj_near, length, fov0x3f1fd0);
}

void set_aov0x169d20(void) {
    flmatrMakeProjection0x1715e0(0x20, lpView0x38a110->proj_far, lpView0x38a110->proj_near, lpView0x38a110->view_angle, SCREEN_RATIO);
    flSetRenderState0x177720(0x18, &lpView0x38a110->unk_38);
    plSetupFOVClipPlanes0x193350(lpView0x38a110->view_angle, SCREEN_RATIO, lpView0x38a110->proj_near, 3000.0, fov0x3f1fd0);
}

void RollView0x169da0(f32 angle) {
    lpView0x38a110->view_roll = angle;
}

void SetAngleOfView0x169db0(f32 angle) {
    lpView0x38a110->view_angle = angle;
}

void Get_dist_to_view0x169dc0(f32* vec) {
    flvecCalcDistance0x173140(vec, &lpView0x38a110->pos_x);
}

s32 Get_view_dir0x169dd0(void) {
    return (s32) (0.5f + ((USHORT_MAX_FLOAT * flArcTan20x1735e0(-(lpView0x38a110->target_z - lpView0x38a110->pos_z), lpView0x38a110->target_x - lpView0x38a110->pos_x)) / TAU)) & 0xFFFF;
}
