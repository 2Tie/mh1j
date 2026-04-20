#include "common.h"

extern u16 CameraWork0x4767c0[0x2FC];

void CameraWorkInit0x21f3d0(void) {
    flMemset0x16f5f0(CameraWork0x4767c0, 0, sizeof(CameraWork0x4767c0));
}

INCLUDE_ASM("asm/main/nonmatchings/camera", Q_camera_init0x21f3f0);

INCLUDE_ASM("asm/main/nonmatchings/camera", CameraInit0x21f410);

INCLUDE_ASM("asm/main/nonmatchings/camera", SetCameraData0x21f470);

INCLUDE_ASM("asm/main/nonmatchings/camera", CameraMove0x21f590);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_std0x21f810);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_std0x21f9b0);

INCLUDE_ASM("asm/main/nonmatchings/camera", WyvernFindPlayer0x220420);

INCLUDE_ASM("asm/main/nonmatchings/camera", BBQcamera_set0x220450);

INCLUDE_ASM("asm/main/nonmatchings/camera", manual_cam_chk0x220490);

INCLUDE_ASM("asm/main/nonmatchings/camera", std_cam_sw_set_sub0x220570);

INCLUDE_ASM("asm/main/nonmatchings/camera", set_to_std_cam0x220650);

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

INCLUDE_ASM("asm/main/nonmatchings/camera", DemoCameraRequest0x221b80);

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

INCLUDE_ASM("asm/main/nonmatchings/camera", PachingerCamChk0x222930);

INCLUDE_ASM("asm/main/nonmatchings/camera", set_quake_sub0x222980);

INCLUDE_ASM("asm/main/nonmatchings/camera", set_quake_sub20x2229d0);

INCLUDE_ASM("asm/main/nonmatchings/camera", Pl_set_quake_sub0x222a10);

INCLUDE_ASM("asm/main/nonmatchings/camera", Em_set_quake_sub0x222aa0);

INCLUDE_ASM("asm/main/nonmatchings/camera", Pachinger_set_quake_sub0x222b30);

INCLUDE_ASM("asm/main/nonmatchings/camera", quake_sub0x222bc0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sw_set_sub0x222d80);

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

INCLUDE_ASM("asm/main/nonmatchings/camera", ZoomRateCalc0x224660);

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

INCLUDE_ASM("asm/main/nonmatchings/camera", PlayerDieCameraRequest0x225ed0);

INCLUDE_ASM("asm/main/nonmatchings/camera", PlComebackCameraRequest0x225ee0);

INCLUDE_ASM("asm/main/nonmatchings/camera", PilebunkerCameraRequest0x225ef0);

INCLUDE_ASM("asm/main/nonmatchings/camera", FishWyvernCameraRequest0x225f50);

INCLUDE_ASM("asm/main/nonmatchings/camera", LegendSwordCameraRequest0x225fb0);
