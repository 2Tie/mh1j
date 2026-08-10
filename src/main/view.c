#include "common.h"
#include "structs.h"
#include "junk.h"

extern VIEW_WORK* lpView0x38a110;
extern VIEW_WORK view_work0x39da70;
extern view_work_old view_w0x39d970;
extern f32 fov0x3f1fd0[];
extern MATRIX rview_mat0x3f2060;
extern MATRIX rview_matY0x3f2020;
extern MATRIX view_mat0x3f20a0;
extern f32 proj_tbl0x301a10[12];
extern SYSTEM_WORK system_w;
extern u8 D_003F36BF[]; // system_w.view_projection

extern void plSetupFOVClipPlanes0x193350(f32, f32, f32, f32, f32*);
extern void flmatrMakeProjection0x1715e0(u8, f32, f32, f32, f32);
extern void flSetRenderState0x177720(u8, u32);
extern f32 flArcTan20x1735e0(f32, f32);
extern f32 flvecCalcDistance0x173140(f32*, f32*);
extern void flQuatCnv0x1736b0(f32*, MATRIX);
extern void flQuatSetRot20x173890(f32*, f32*, f32);
extern void flmatInit0x171ce0(MATRIX);
extern void flmatInvert0x172be0(MATRIX, MATRIX);
extern void flmatMakeLookAt0x172810(MATRIX, f32*, f32*, f32*);
extern void flmatSetXYZ330x172140(MATRIX, f32, f32, f32);
extern void flmatrLoad0x173490(MATRIX, u32);
extern void flvecApplyMat330x172e00(f32*, f32*, MATRIX);
extern u16 calc_mat_angY0x1204d0(MATRIX);
extern void set_aov0x169d20(void);

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
    lpView0x38a110->view_angle = 0.87266465; // TODO constant
    lpView0x38a110->view_angle_OLD = -999.0;
    lpView0x38a110->view_roll = 0.0;
}

void View_move0x169a80(void) {
    f32 lookVector[4];
    MATRIX lookMatrix;
    f32 lookQuaternion[4];
    f32 view_y;
    s32 update_aov;

    update_aov = 0;
    if (lpView0x38a110->view_angle_OLD != lpView0x38a110->view_angle) {
        lpView0x38a110->view_angle_OLD = lpView0x38a110->view_angle;
        update_aov += 1;
    }

    if (update_aov != 0) {
        set_aov0x169d20();
    }

    lookVector[0] = lpView0x38a110->target[0] - lpView0x38a110->pos[0];
    lookVector[1] = lpView0x38a110->target[1] - lpView0x38a110->pos[1];
    lookVector[2] = lpView0x38a110->target[2] - lpView0x38a110->pos[2];

    flQuatSetRot20x173890(lookVector, lookQuaternion, lpView0x38a110->view_roll);
    flQuatCnv0x1736b0(lookQuaternion, lookMatrix);

    lookVector[0] = 0.0f;
    lookVector[1] = 1.0f;
    lookVector[2] = 0.0f;

    flvecApplyMat330x172e00(&lpView0x38a110->pitch, lookVector, lookMatrix);
    flmatMakeLookAt0x172810(lookMatrix, lpView0x38a110->pos, lpView0x38a110->target, &lpView0x38a110->pitch);
    flSetRenderState0x177720(0x16, (u32) lookMatrix);
    flmatrLoad0x173490(view_mat0x3f20a0, 0x21);
    flmatInvert0x172be0(rview_mat0x3f2060, view_mat0x3f20a0);

    view_y = (calc_mat_angY0x1204d0(rview_mat0x3f2060) + 0x4000) & 0xFFFF;
    view_y = 360.0f * view_y / 65536.0f / 360.0f * 3.1415927f * 2.0f;

    flmatInit0x171ce0(rview_matY0x3f2020);
    flmatSetXYZ330x172140(rview_matY0x3f2020, 0.0f, view_y, 0.0f);
}

void set_viewproj0x169c20(u32 which) {
    f32 tbl[4];
    s32 i;

    if (which == 0xFF) {
        set_aov0x169d20();
        return;
    }
    if (*D_003F36BF != which) {
        *D_003F36BF = which;

        for (i = 0; i < 4; i++) {
            tbl[i] = proj_tbl0x301a10[which * 4 + i];
        }

        lpView0x38a110->proj_far = tbl[0];
        lpView0x38a110->proj_near = tbl[1];
        lpView0x38a110->view_angle = tbl[2];
        lpView0x38a110->view_roll = 0.0f;

        set_aov0x169d20();
    }
}

void Create_FOV0x169cf0(f32 length) {
    plSetupFOVClipPlanes0x193350(lpView0x38a110->view_angle, SCREEN_RATIO, lpView0x38a110->proj_near, length, fov0x3f1fd0);
}

void set_aov0x169d20(void) {
    flmatrMakeProjection0x1715e0(0x20, lpView0x38a110->proj_far, lpView0x38a110->proj_near, lpView0x38a110->view_angle, SCREEN_RATIO);
    flSetRenderState0x177720(0x18, (u32) (&lpView0x38a110->unk_38));
    plSetupFOVClipPlanes0x193350(lpView0x38a110->view_angle, SCREEN_RATIO, lpView0x38a110->proj_near, 3000.0, fov0x3f1fd0);
}

void RollView0x169da0(f32 angle) {
    lpView0x38a110->view_roll = angle;
}

void SetAngleOfView0x169db0(f32 angle) {
    lpView0x38a110->view_angle = angle;
}

void Get_dist_to_view0x169dc0(f32* vec) {
    flvecCalcDistance0x173140(vec, lpView0x38a110->pos);
}

s32 Get_view_dir0x169dd0(void) {
    return (s32) (0.5f + ((USHORT_MAX_FLOAT * flArcTan20x1735e0(-(lpView0x38a110->target[2] - lpView0x38a110->pos[2]), lpView0x38a110->target[0] - lpView0x38a110->pos[0])) / TAU)) & 0xFFFF;
}
