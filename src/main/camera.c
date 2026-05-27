#include "common.h"
#include "structs.h"
#include "main/camera.h"

//externs
extern PSW Psw0x3f3710[2];
extern GAME_WORK game_w0x3f33f0;
extern PLAYER_WORK player_work0x3e4bf0[8];
extern MONSTER_WORK em_work0x3d82a0[20];
extern s32 Game_clear_ck0x162db0(s32);
extern u32 Pl_stg_ck0x151ff0(PLAYER_WORK*);
extern s32 Em_stg_ck0x152010(MONSTER_WORK*);

//rodata
extern s16 quake_time_tbl0x338ed0[6];

//bss
extern CAMERA_WORK CameraWork0x4767c0;

//protos
void StageCamInit0x223000(CAMERA_WORK*);


void CameraWorkInit0x21f3d0(void) {
    flMemset0x16f5f0(CameraWork0x4767c0, 0, sizeof(CameraWork0x4767c0));
}

void Q_camera_init0x21f3f0(void) {
    CameraWork0x4767c0.demo_play = 0;
    CameraWork0x4767c0.wyvern_ptr = 0;
    CameraWork0x4767c0.player_cam_height_level = 2;
}

void CameraInit0x21f410(void) {
    CameraWork0x4767c0.initialized = 0;
    CameraWork0x4767c0.quake.active = false;
    CameraWork0x4767c0.sub_quake.active = false;
    CameraWork0x4767c0.wyvern_target = 0;
    CameraWork0x4767c0.player_ptr = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
    StageCamInit0x223000(&CameraWork0x4767c0);
}

INCLUDE_ASM("asm/main/nonmatchings/camera", SetCameraData0x21f470);

INCLUDE_ASM("asm/main/nonmatchings/camera", CameraMove0x21f590);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_std0x21f810);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_std0x21f9b0);

void WyvernFindPlayer0x220420(PLAYER_WORK* player) {
    CAMERA_WORK* camera_work = &CameraWork0x4767c0;
    
    if (player->player_num == game_w0x3f33f0.my_player_number) {
        camera_work->wyvern_target = player;
    }
}

void BBQcamera_set0x220450(PLAYER_WORK* player) {
    CAMERA_WORK* camera_work = &CameraWork0x4767c0;

    if (player->player_num == game_w0x3f33f0.my_player_number) {
        camera_work->views[0].hit_wall = 0;
        camera_work->views[0].next_rot = (s16) (player->angle + 0x2000);
        camera_work->player_cam_height_level = 2;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/camera", manual_cam_chk0x220490);

INCLUDE_ASM("asm/main/nonmatchings/camera", std_cam_sw_set_sub0x220570);

void set_to_std_cam0x220650(s32 view) {
    CAM_W_VIEW* cam_w_view = &CameraWork0x4767c0.views[0];
    s32 tmp = view;

    if (tmp == 4) {
        tmp = -1;
    }
    if (tmp >= 0) {
        cam_w_view->which_view = tmp;
        return;
    }
    cam_w_view->which_view = -1;
}

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_stg0x220690);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_stg0x2206b0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_pchngr0x220ee0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_pchngr0x220f30);

INCLUDE_ASM("asm/main/nonmatchings/camera", pch_lock_chk0x221400);

INCLUDE_ASM("asm/main/nonmatchings/camera", PachiTypeCheck0x221460);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetPachingerInfo0x221530);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_playerEX0x221580);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_playerEX0x2215a0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_plEX_fishing0x221600);

INCLUDE_ASM("asm/main/nonmatchings/camera", fishing_cam_chk0x2216e0);

INCLUDE_ASM("asm/main/nonmatchings/camera", fish_cam_sub0x221700);

INCLUDE_ASM("asm/main/nonmatchings/camera", NPCZoomInCameraRequest0x221820);

INCLUDE_ASM("asm/main/nonmatchings/camera", NPCZoomInCameraCancel0x221850);

INCLUDE_ASM("asm/main/nonmatchings/camera", NPCZoomInCameraCheck0x221860);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_plEX_zoom0x221870);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_demo0x221aa0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_demo0x221ac0);

void DemoCameraRequest0x221b80(s8 demo, void* ptr) {
    CameraWork0x4767c0.demo_play = demo;
    CameraWork0x4767c0.wyvern_ptr = ptr;
}

INCLUDE_ASM("asm/main/nonmatchings/camera", DemoCameraCancel0x221ba0);

INCLUDE_ASM("asm/main/nonmatchings/camera", DemoCameraCheck0x221bd0);

INCLUDE_ASM("asm/main/nonmatchings/camera", point_camera0x221be0);

INCLUDE_ASM("asm/main/nonmatchings/camera", get_em_local0x221cf0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cmd_set_pos0x221d30);

INCLUDE_ASM("asm/main/nonmatchings/camera", cmd_set_tar0x221e60);

INCLUDE_ASM("asm/main/nonmatchings/camera", cmd_copy0x221f90);

INCLUDE_ASM("asm/main/nonmatchings/camera", get_angle0x222020);

INCLUDE_ASM("asm/main/nonmatchings/camera", cmd_cam_move0x2220c0);

INCLUDE_ASM("asm/main/nonmatchings/camera", point_cam_hit0x222400);

INCLUDE_ASM("asm/main/nonmatchings/camera", point_cam_sub0x222410);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam2view0x2227a0);

s32 PachingerCamChk0x222930(PLAYER_WORK* ply) {
    CAMERA_WORK* cam = &CameraWork0x4767c0;
    if (cam->views[4].this_view_active != 0) {
        return 0;
    }
    if (ply->sight_timer != 0) {
        return 1;
    } else {
        return cam->views[2].this_view_active != 0;
    }
}

void set_quake_sub0x222980(u32 which, float* pos) {
    QUAKE* quake = &CameraWork0x4767c0.sub_quake;
    quake->active = 1;
    quake->type = which;
    quake->timer = quake_time_tbl0x338ed0[which];
    quake->pos[0] = pos[0];
    quake->pos[1] = pos[1];
    quake->pos[2] = pos[2];
}

void set_quake_sub20x2229d0(u32 which) {
    QUAKE* quake = &CameraWork0x4767c0.sub_quake;
    quake -> active = true;
    quake->type = which | 0x80;
    quake->timer = quake_time_tbl0x338ed0[which];
}

void Pl_set_quake_sub0x222a10(PLAYER_WORK* ply, u32 which) {
    QUAKE* quake = &CameraWork0x4767c0.sub_quake;
    if ((u8)Pl_stg_ck0x151ff0(ply)) {
        quake->active = true;
        quake->type = which;
        quake->timer = quake_time_tbl0x338ed0[which];
        quake->pos[0] = ply->pos[0];
        quake->pos[1] = ply->pos[1];
        quake->pos[2] = ply->pos[2];
    }
}

void Em_set_quake_sub0x222aa0(MONSTER_WORK* mon, u32 which) {
    QUAKE* quake = &CameraWork0x4767c0.sub_quake;
    if ((u8)Em_stg_ck0x152010(mon)) {
        quake->active = true;
        quake->type = which;
        quake->timer = quake_time_tbl0x338ed0[which];
        quake->pos[0] = mon->pos[0];
        quake->pos[1] = mon->pos[1];
        quake->pos[2] = mon->pos[2];
    }
}

void Pachinger_set_quake_sub0x222b30(PLAYER_WORK* ply, u32 which) {
    QUAKE* quake = &CameraWork0x4767c0.quake;
    if ((u8)Pl_stg_ck0x151ff0(ply)) {
        quake->active = true;
        quake->type = which;
        quake->timer = quake_time_tbl0x338ed0[which];
        quake->pos[0] = ply->pos[0];
        quake->pos[1] = ply->pos[1];
        quake->pos[2] = ply->pos[2];
    }
}

INCLUDE_ASM("asm/main/nonmatchings/camera", quake_sub0x222bc0);

void cam_sw_set_sub0x222d80(CAMERA_WORK* cam) {
    if (Game_clear_ck0x162db0(1) == 1 || cam->player_ptr->ojiisan_timer != 0) {
        cam->pad_sticks = 0U;
        cam->pad_new = 0U;
        cam->pad_state = 0U;
        cam->pad_right_stick_power = 0U;
        cam->pad_right_stick_angle = 0U;
    } else {
        cam->pad_state = Psw0x3f3710[0].current_state;
        cam->pad_new = Psw0x3f3710[0].just_pressed;
        cam->pad_sticks = Psw0x3f3710[0].current_sticks;
        cam->pad_right_stick_angle = Psw0x3f3710[0].right_stick_angle;
        cam->pad_right_stick_power = Psw0x3f3710[0].right_stick_power;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/camera", default_area_data0x222e20);

INCLUDE_ASM("asm/main/nonmatchings/camera", StageCamInit0x223000);

INCLUDE_ASM("asm/main/nonmatchings/camera", SetAreaData0x223070);

INCLUDE_ASM("asm/main/nonmatchings/camera", Get_cam_grid_XZ0x223190);

INCLUDE_ASM("asm/main/nonmatchings/camera", CameraAreaCheck0x2232a0);

INCLUDE_ASM("asm/main/nonmatchings/camera", CamAreaAttribChk0x2233c0);

INCLUDE_ASM("asm/main/nonmatchings/camera", Area_XZ_Check0x223410);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetPanTarget0x223500);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetRailTarget0x2235e0);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetRailCamPos0x2236d0);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetNearSection0x223760);

INCLUDE_ASM("asm/main/nonmatchings/camera", get_near_point_sub0x223870);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetNearPoint0x223980);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_rail_move_sub0x223b50);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_rail_move0x223c90);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_rail_move_00x223de0);

INCLUDE_ASM("asm/main/nonmatchings/camera", CamRailMove0x223e90);

INCLUDE_ASM("asm/main/nonmatchings/camera", CamRailPoint0x223f00);

INCLUDE_ASM("asm/main/nonmatchings/camera", vInnerProductXZ0x223f90);

INCLUDE_ASM("asm/main/nonmatchings/camera", vInnerProduct0x223fb0);

INCLUDE_ASM("asm/main/nonmatchings/camera", GetOrthogonalPoint0x223fe0);

f32 ZoomRateCalc0x224660(f32 distance, CAM_DATA_ENTRY_HEADER* header) {
    f32 max;
    f32 min;
    f32 zoom;

    min = header->min_distance;
    if (distance <= min) {
        return header->near_zoom; //if too close, return minimum
    }
    max = header->max_distance;
    if (distance >= max) {
        return header->far_zoom; //if too far, return maximum
    }
    if (max == min) {
        return 0.5f * (header->near_zoom + header->far_zoom); //if no range defined, average the settings
    }
    zoom = (header->far_zoom - header->near_zoom) * (distance - min);
    zoom /= (max - min);
    zoom += header->near_zoom;
    return zoom; //otherwise linear scale between the two values
}

INCLUDE_ASM("asm/main/nonmatchings/camera", ZoomBaseAngleRail0x2246f0);

INCLUDE_ASM("asm/main/nonmatchings/camera", RollAngleRail0x224720);

INCLUDE_ASM("asm/main/nonmatchings/camera", tri_diag0x224790);

INCLUDE_ASM("asm/main/nonmatchings/camera", Spline0x2248c0);

INCLUDE_ASM("asm/main/nonmatchings/camera", dCnvComplex0x224cb0);

INCLUDE_ASM("asm/main/nonmatchings/camera", dSubComplex0x224cc0);

INCLUDE_ASM("asm/main/nonmatchings/camera", dMulComplex0x224cf0);

INCLUDE_ASM("asm/main/nonmatchings/camera", dDivComplex0x224d40);

INCLUDE_ASM("asm/main/nonmatchings/camera", DKA50x224dd0);

INCLUDE_ASM("asm/main/nonmatchings/camera", Cardano0x225050);

INCLUDE_ASM("asm/main/nonmatchings/camera", k_HitWallCamera0x225370);

INCLUDE_ASM("asm/main/nonmatchings/camera", k_HitEmCamera0x225510);

INCLUDE_ASM("asm/main/nonmatchings/camera", QuestClearCameraRequest0x225d80);

INCLUDE_ASM("asm/main/nonmatchings/camera", RedDragonEscapeCamera0x225e90);

INCLUDE_ASM("asm/main/nonmatchings/camera", F_DragonEscapeCamera0x225ea0);

void PlayerDieCameraRequest0x225ed0(void) {
    DemoCameraRequest0x221b80(0x1A, 0);
}

void PlComebackCameraRequest0x225ee0(void) {
    DemoCameraRequest0x221b80(2, 0);
}

void PilebunkerCameraRequest0x225ef0(void) {
    s8 demo_id;

    switch (game_w0x3f33f0.current_area_id) {
        case 12:
            demo_id = 3;
            break;
        case 25:
            demo_id = 4;
            break;
        default:
            return;
    }

    DemoCameraRequest0x221b80(demo_id, 0);
}

void FishWyvernCameraRequest0x225f50(void) {
    MONSTER_WORK* em = &em_work0x3d82a0[0];
    s32 count;

    for (count = 20; count != 0; count--) {
        if (em->exists != 0 && em->species == 0x15) {
            DemoCameraRequest0x221b80(0x11, em);
            return;
        }
        em++; 
    }
}

void LegendSwordCameraRequest0x225fb0(void) {
    DemoCameraRequest0x221b80(0x19, 0);
}
