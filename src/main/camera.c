#include "common.h"
#include "structs.h"
#include "main/camera.h"

// externs
extern PSW Psw0x3f3710[2];
extern GAME_WORK game_w0x3f33f0;
extern PLAYER_WORK player_work0x3e4bf0[8];
extern MONSTER_WORK em_work0x3d82a0[20];
extern VIEW_WORK* lpView0x38a110;

extern f32 flSqrt0x173680(f32);
extern f32 flPow0x173670(f32, f32);
extern f32 flCos0x173610(f32);
extern f32 flSin0x173600(f32);
extern f32 flArcTan20x1735e0(f32, f32);
extern f32 flAbs0x173540(f32);
extern f32 flvecInnerProduct0x173220(f32*, f32*);
extern f32 flvecCalcDistance0x173140(f32*, f32*);
extern void View_move0x169a80();
extern void RollView0x169da0(f32);
extern void SetAngleOfView0x169db0(f32);
extern s32 Game_clear_ck0x162db0(s32);
extern u32 Pl_stg_ck0x151ff0(PLAYER_WORK*);
extern s32 Em_stg_ck0x152010(MONSTER_WORK*);
extern void flmatInit0x171ce0(MATRIX);
extern void flmatCopy0x172cb0(MATRIX, MATRIX);
extern void flmatRotXYZ330x1724e0(MATRIX, f32, f32, f32);
extern void flmatGetTrans0x171ee0(f32*, MATRIX);
extern void nlCalcPoint0x120ec0(f32*, f32*, MATRIX);
extern void ScaleVector0x1208a0(f32*, f32*, f32);
extern void SubVector0x120860(f32*, f32*, f32*);
extern void AddVector0x120820(f32*, f32*, f32*);
extern void flvecApplyMat33_20x172e70(VEC3, MATRIX);
extern void flvecApplyMat330x172e00(f32*, f32*, MATRIX);
extern void flvecCopy0x173300(f32*, f32*);
extern void flvecRotY0x173070(f32*, f32);
extern void cpInterVector0x120e30(f32*, f32*, f32*, f32);
extern s32 Pl_scope_ck0x154d00(PLAYER_WORK*);
extern s16 act_ck0x14ef20(PLAYER_WORK*, s8, s8);
extern s32 pl_flag_ck0x14ef60(PLAYER_WORK*, u32);

// rodata
extern s16 quake_time_tbl0x338ed0[6];
extern void (*cam_init_sub_jmp0x3391f0[5])(CAMERA_WORK*, CAM_W_VIEW*);
extern void (*cam_sub_jmp0x339210[5])(CAMERA_WORK*, CAM_W_VIEW*);
extern f32 pch_pos0x339350[3][6];
extern f32 dka_j_tbl0x3393D0[];
/*f32 dka_j_tbl0x3393D0[6] = {
    0.0f,
    1.0f,
    0.5f,
    0.33333334f,
    0.25f,
    0.2f
};*/
extern f32 dka_init_tbl0x3393a0[5][2];
extern void* Demo_cam_tbl0x348d70[35];
extern FISH_CAM_OFFSET* fishcam_ofs_tbl0x339080[90];

extern CAM_DATA_HEADER* cam_data_area0x38a204;
extern CAM_HEIGHT_ENTRY* stage_camera_data_tbl0x2f58e0[4];

// bss
extern CAMERA_WORK CameraWork0x4767c0;

// protos
void cmd_set_pos0x221d30(f32*, POINT_CAM_STATE*, s32*);
void cmd_set_tar0x221e60(f32*, POINT_CAM_STATE*, s32*);
void cmd_copy0x221f90(f32*, s32);
void cmd_cam_move0x2220c0(CAMERA_WORK*, CAM_W_VIEW*, POINT_CAM_STATE*);
void cam2view0x2227a0(CAMERA_WORK*);
void cam_sw_set_sub0x222d80(CAMERA_WORK*);
static void default_area_data0x222e20(CAMERA_WORK*);
void StageCamInit0x223000(CAMERA_WORK*);
s32 SetAreaData0x223070(CAMERA_WORK*);
u8 Get_cam_grid_XZ0x223190(u16*, u16*, f32*, CAM_AREA_XZ*);
s32 CameraAreaCheck0x2232a0(CAM_AREA_DATA*, PLAYER_WORK*, u8);
s32 CamAreaAttribChk0x2233c0(CAM_AREA_DATA*, PLAYER_WORK*);
s32 Area_XZ_Check0x223410(CAM_GEOMETRY_ZONE*, f32*);
s8 PachiTypeCheck0x221460(PLAYER_WORK*);
s32 pch_lock_chk0x221400(PLAYER_WORK*);
u32 point_camera0x221be0(CAMERA_WORK*, CAM_W_VIEW*);
s32 point_cam_sub0x222410(CAMERA_WORK*, CAM_W_VIEW*, POINT_CAM_STATE*);
void DemoCameraRequest0x221b80(s32, void*);
void quake_sub0x222bc0(QUAKE*);
void CamRailPoint0x223f00(VEC4, VEC3*, f32);
s32 GetOrthogonalPoint0x223fe0(f32* , f32 [4][3], f32* , s32 );
void Spline0x2248c0(VEC3[][4], VEC4 *, s32);
void DKA50x224dd0(COMPLEX*, f32*);
s32 Cardano0x225050(f32*, f32*);
void cam_plEX_fishing0x221600(CAMERA_WORK*, CAM_W_VIEW*, CAM_FISHING_CONTROL*);
void cam_plEX_zoom0x221870(CAMERA_WORK*, CAM_W_VIEW*, CAM_ZOOM_CONTROL*);
s32 fish_cam_sub0x221700(CAMERA_WORK*, CAM_W_VIEW*, CAM_FISHING_CONTROL*);
s32 fishing_cam_chk0x2216e0(PLAYER_WORK*);


// funcs
void CameraWorkInit0x21f3d0(void) {
    flMemset0x16f5f0(CameraWork0x4767c0, 0, sizeof(CameraWork0x4767c0));
}

void Q_camera_init0x21f3f0(void) {
    CameraWork0x4767c0.demo_play = 0;
    CameraWork0x4767c0.wyvern_ptr = 0;
    CameraWork0x4767c0.player_cam_height_level = 2;
}

void CameraInit0x21f410(void) {
    *(u32*) &CameraWork0x4767c0.initialized = 0;
    CameraWork0x4767c0.quake.active = false;
    CameraWork0x4767c0.sub_quake.active = false;
    CameraWork0x4767c0.wyvern_target = 0;
    CameraWork0x4767c0.player_ptr = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
    StageCamInit0x223000(&CameraWork0x4767c0);
}

void SetCameraData0x21f470(CAM_DATA_HEADER* data) {
    CAM_AREA_DATA* entry;
    u8* next_offset;
    CAM_GRID_CELL* grid;
    CAM_DATA_ENTRY_HEADER** entry_ptrs;
    s32 count;
    s32 cell_count;
    s32 total_ptrs;

    CameraWork0x4767c0.CamDataBuffer = data;

    if (data != 0) {
        entry = data->entries;
        data->first_entry_ptr = entry;

        for (count = data->entry_count; count != 0; count--) {
            next_offset = (void*) entry;

            if (entry->header.bytepairs_ptr != 0) {
                entry->header.zones_ptr = (CAM_GEOMETRY_ZONE*) (next_offset + entry->header.zones_offset);
                entry->header.bytepairs_ptr = (u8*) next_offset + entry->header.bytepairs_offset;
                entry = (CAM_AREA_DATA*) ((u32) (entry + 1) + entry->header.zone_count * sizeof(CAM_GEOMETRY_ZONE) + sizeof(AREA_CONNECT)*AREA_CONNECT_COUNT); 
            } else {
                entry->header.zones_ptr = (CAM_GEOMETRY_ZONE*) (next_offset + entry->header.zones_offset);
               entry = (CAM_AREA_DATA*) ((u32) (entry + 1) + entry->header.zone_count * sizeof(CAM_GEOMETRY_ZONE));
            }
        }

        grid = (CAM_GRID_CELL*) ((u8*) data + data->cam_grid_offset);
        data->cam_grid_ptr = grid;

        entry_ptrs = (CAM_DATA_ENTRY_HEADER**) ((u8*) data + data->entry_list_offset);
        data->entry_list_ptr = entry_ptrs;

        cell_count = data->x_count * data->y_count;
        total_ptrs = 0;

        for (count = cell_count; count != 0; count--) {
            if (grid->entry_count != 0) {
                grid->entries_ptr = (CAM_AREA_DATA**) ((u8*) data + grid->entries_offset);
                total_ptrs += grid->entry_count;
            }
            grid++;
        }

        for (count = total_ptrs; count != 0; count--) {
            *entry_ptrs = (CAM_DATA_ENTRY_HEADER*) ((u8*) data + (u32) *entry_ptrs);
            entry_ptrs++;
        }
    }
}

void CameraMove0x21f590(void) {
    PLAYER_WORK* player;
    CAMERA_WORK* cam_work;
    CAM_W_VIEW* cam_view;
    u32 count;

    player = CameraWork0x4767c0.player_ptr;

    cam_work = &CameraWork0x4767c0;

    cam_sw_set_sub0x222d80(cam_work);

    cam_work->cam_grid_returnval = Get_cam_grid_XZ0x223190(
        &cam_work->cam_grid_x, &cam_work->cam_grid_y, player->pos, &cam_work->area_xz);

    cam_work->has_active_view = 0;

    if (cam_work->initialized == 0) {
        cam_work->initialized++;
        cam_work->CamAreaPtr = NULL;
        cam_work->prev_cam_entry_index = -1;
        cam_work->cam_entry_index = -1;

        if (SetAreaData0x223070(cam_work) >= 0) {
            cam_work->cam_entry_index = cam_work->CamAreaPtr->header.index;
        }

        cam_view = &cam_work->views[0];

        count = 0;
        while (count < 5) {
            cam_view->which_sub = count;
            cam_view->unk_78_s32 = 0;
            cam_init_sub_jmp0x3391f0[count](cam_work, cam_view);
            count++;
            cam_view++;
        }

        cam_work->active_view = 0;

        if (cam_work->CamAreaPtr != NULL) {
            if (cam_work->CamAreaPtr->header.move_type == NO_MOVE_TYPE) {
                cam_work->active_view = 0;
            } else {
                cam_work->active_view = 1;
            }
        }

        cam_work->prev_has_active_view = cam_work->active_view;
    }

    if (cam_work->cam_entry_index == 0) {
        if (SetAreaData0x223070(cam_work) > 0) {
            cam_work->prev_cam_entry_index = cam_work->cam_entry_index;
            cam_work->cam_entry_index = cam_work->CamAreaPtr->header.index;
            cam_work->has_active_view = 1;
        }
    } else if (CameraAreaCheck0x2232a0(cam_work->CamAreaPtr, player, 2) != 0) {
        cam_work->prev_cam_entry_index = cam_work->cam_entry_index;
        cam_work->has_active_view = 1;

        if (SetAreaData0x223070(cam_work) >= 0) {
            cam_work->cam_entry_index = cam_work->CamAreaPtr->header.index;
        }
    }

    cam_work->prev_has_active_view = cam_work->active_view;

    if (cam_work->CamAreaPtr != NULL) {
        switch (cam_work->CamAreaPtr->header.move_type) {
            case NO_MOVE_TYPE:
                cam_work->active_view = 0;
                break;
            case PAN:
            case RAIL:
            case PAN_WITH_PLAYER:
                cam_work->active_view = 1;
                break;
        }
    } else {
        cam_work->active_view = 0;
    }

    cam_view = &cam_work->views[0];
    for (count = 5; count != 0; count--) {
        cam_sub_jmp0x339210[cam_view->which_sub](cam_work, cam_view);
        cam_view++;
    }

    cam2view0x2227a0(cam_work);
    cam_work->wyvern_target = NULL;
    View_move0x169a80();
}

INCLUDE_ASM("asm/nonmatchings/main/camera", cam_init_sub_std0x21f810);

INCLUDE_ASM("asm/nonmatchings/main/camera", cam_sub_std0x21f9b0);

void WyvernFindPlayer0x220420(PLAYER_WORK* player) {
    CAMERA_WORK* camera_work = &CameraWork0x4767c0;

    if (player->player_num == game_w0x3f33f0.my_player_number) {
        camera_work->wyvern_target = player;
    }
}

void BBQcamera_set0x220450(PLAYER_WORK* player) {
    CAMERA_WORK* camera_work = &CameraWork0x4767c0;

    if (player->player_num == game_w0x3f33f0.my_player_number) {
        camera_work->views[0].state.hit_wall = 0;
        camera_work->views[0].state.next_rot = player->angle + 0x2000;
        camera_work->player_cam_height_level = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/camera", manual_cam_chk0x220490);

INCLUDE_ASM("asm/nonmatchings/main/camera", std_cam_sw_set_sub0x220570);

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

void cam_init_sub_stg0x220690(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    cam_view->yaw = 0;
    cam_view->pitch = DEG_55_RAD;
}

INCLUDE_ASM("asm/nonmatchings/main/camera", cam_sub_stg0x2206b0);

void cam_init_sub_pchngr0x220ee0(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    CAM_VIEW_STATE_PACHINGER* view_state;
    f32 loaded_unk_68;

    view_state = &cam_view->state_pchngr;

    cam_view->pitch = DEG_45_RAD;
    cam_view->yaw = 0;
    view_state->angle_min = DEG_10_RAD;
    view_state->angle_max = DEG_60_RAD;
    view_state->angle_delta = view_state->angle_max - view_state->angle_min;

    loaded_unk_68 = cam_view->pitch;

    view_state->angle_pan = loaded_unk_68;
    view_state->angle_cur = loaded_unk_68;
}

void cam_sub_pchngr0x220f30(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    f32 tmp_vec1[3];
    f32 tmp_vec2[3];
    f32 tmp_vec3[3];

    f32* tmp_angle;

    CAM_VIEW_STATE_PACHINGER* view_state;
    PLAYER_WORK* player;

    player = cam_work->player_ptr;
    cam_view->this_view_active = 0;

    if (player->unk_764 == 0) {
        cam_view->unk_78_s32 = 0;
        return;
    }

    view_state = &cam_view->state_pchngr;
    view_state->pachi_type = PachiTypeCheck0x221460(player);

    switch (view_state->pachi_type) {
        case 0:
            view_state->unk_63 = 1;

            if (Pl_scope_ck0x154d00(player) == 1) {
                view_state->unk_64 = 1;
                view_state->angle_min = DEG_10_RAD;
                view_state->angle_max = DEG_60_RAD;
                view_state->angle_delta = view_state->angle_max - view_state->angle_min;
            } else {
                view_state->unk_64 = 0;
            }
            break;

        case 1:
            view_state->unk_63 = 0;
            view_state->unk_64 = 1;
            view_state->angle_min = DEG_10_RAD;
            view_state->angle_max = DEG_60_RAD;
            view_state->angle_delta = view_state->angle_max - view_state->angle_min;
            break;

        case 2:
            view_state->unk_63 = 17;
            view_state->unk_64 = 0;
            break;

        default:
            break;
    }

    switch (cam_view->unk_78_u8) {
        case 0:
            switch (view_state->pachi_type) {
                case 0:
                    if (pch_lock_chk0x221400(player) == 1) {
                        return;
                    }

                case 1:
                    break;

                case 2:
                    cam_view->pitch = DEG_45_RAD;
                    break;

                default:
                    break;
            }

            cam_view->unk_78_u8++;

        case 1:
            if ((view_state->unk_64 != 0) && (cam_work->pad_right_stick_power > 0x60)) {
                tmp_angle = (view_state->pachi_type == 0) ? &view_state->angle_cur : &view_state->angle_pan;

                if (((cam_work->pad_right_stick_angle - 0x4000) & 0xFFFF) < 0x6001) {
                    *tmp_angle -= PCH_ANGLE_STEP;
                    if (*tmp_angle < view_state->angle_min) {
                        *tmp_angle = view_state->angle_min;
                    }
                }

                if ((((cam_work->pad_right_stick_angle - 0x8000) - 0x6000) & 0xFFFF) < 0x6001) {
                    *tmp_angle += PCH_ANGLE_STEP;
                    if (*tmp_angle > view_state->angle_max) {
                        *tmp_angle = view_state->angle_max;
                    }
                }
            }

            switch (view_state->pachi_type) {
                case 0:
                    cam_view->pitch = view_state->angle_cur;
                    break;

                case 1:
                    cam_view->pitch = view_state->angle_pan;
                    break;

                case 2:
                    break;

                default:
                    break;
            }

            switch (view_state->pachi_type) {
                case 0:
                    if (pch_lock_chk0x221400(player) == 0) {
                        flvecCopy0x173300(view_state->pos, player->pos);
                        flmatCopy0x172cb0(view_state->matrix, player->part_ptrs[14]->matrix);
                    } else {
                        SubVector0x120860(tmp_vec1, player->pos, view_state->pos);
                        flvecCopy0x173300(view_state->pos, player->pos);
                        AddVector0x120820(view_state->matrix[3], view_state->matrix[3], tmp_vec1);
                    }

                    cam_view->pitch = view_state->angle_cur;
                    break;

                case 1:
                    flmatInit0x171ce0(view_state->matrix);
                    flmatRotXYZ330x1724e0(
                        view_state->matrix,
                        DEG2RAD * player->unk_8EE,
                        DEG2RAD * ((player->angle + 0x8000) & 0xFFFF),
                        0.0f);
                    flvecCopy0x173300(view_state->matrix[3], player->pos);
                    cam_view->pitch = view_state->angle_pan;
                    break;

                case 2:
                    flmatInit0x171ce0(view_state->matrix);
                    flmatRotXYZ330x1724e0(
                        view_state->matrix,
                        0.0f,
                        DEG2RAD * ((player->angle + 0x8000) & 0xFFFF),
                        0.0f);
                    flvecCopy0x173300(view_state->matrix[3], player->pos);
                    break;

                default:
                    break;
            }

        default:
            flmatGetTrans0x171ee0(tmp_vec3, view_state->matrix);
            flvecApplyMat330x172e00(tmp_vec2, &pch_pos0x339350[view_state->pachi_type][0], view_state->matrix);
            AddVector0x120820(cam_view->cam_pos, tmp_vec3, tmp_vec2);
            flvecApplyMat330x172e00(tmp_vec2, &pch_pos0x339350[view_state->pachi_type][3], view_state->matrix);
            AddVector0x120820(cam_view->target_pos, tmp_vec3, tmp_vec2);

            cam_view->unk_88 = player->angle + 0x8000;
            view_state->unk_60 = player->angle + 0x8000;
            cam_view->this_view_active = 1;
    }
}

s32 pch_lock_chk0x221400(PLAYER_WORK* player) {
    switch (player->unk_2DC) {
        case 0x3EA:
        case 0x579:
        case 0x57C:
        case 0x583:
        case 0x57D:
        case 0x580:
            return 1;

        default:
            return 0;
    }
}

s8 PachiTypeCheck0x221460(PLAYER_WORK* player) {
    if (act_ck0x14ef20(player, 0, 0x65) != 0 || act_ck0x14ef20(player, 0, 0x66) != 0) {
        return 1;
    }

    if (act_ck0x14ef20(player, 0, 0x36) != 0 || act_ck0x14ef20(player, 0, 0x48) != 0) {
        return 2;
    }

    if (player->unk_2 == 1 || player->unk_2 == 5) {
        return 0;
    }

    return -1;
}

s8 GetPachingerInfo0x221530(void* arg0, u8* arg1, u8* arg2, f32* arg3) {
    CAM_W_VIEW* cam_view;
    CAM_VIEW_STATE_PACHINGER* view_state;

    cam_view = &CameraWork0x4767c0.views[2];
    view_state = &cam_view->state_pchngr;

    *arg1 = view_state->unk_63;
    *arg2 = view_state->unk_64;

    if (view_state->unk_64 != 0) {
        *arg3 = cam_view->pitch - view_state->angle_min;
        *arg3 /= view_state->angle_delta;
    }

    return view_state->pachi_type;
}

void cam_init_sub_playerEX0x221580(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    cam_view->pitch = DEG_55_RAD;
    cam_view->yaw = 0.0f;

    cam_view->state_player.fishing_control.active_s32 = 0;
    cam_view->state_player.zoom_control.state_s32 = 0;
    cam_view->state_player.zoom_control.unk_20 = 0;
}

void cam_sub_playerEX0x2215a0(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    CAM_VIEW_STATE_PLAYER* view_state;

    view_state = &cam_view->state_player;

    cam_plEX_fishing0x221600(cam_work, cam_view, &view_state->fishing_control);

    if (cam_view->this_view_active == false) {
        cam_plEX_zoom0x221870(cam_work, cam_view, &view_state->zoom_control);
    }
}

void cam_plEX_fishing0x221600(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view, CAM_FISHING_CONTROL* cam_fish) {
    PLAYER_WORK* player;
    s32 is_fishing_active;

    cam_view->this_view_active = false;
    player = cam_work->player_ptr;

    is_fishing_active = fishing_cam_chk0x2216e0(player);
    cam_fish->is_fishing = is_fishing_active;

    if (is_fishing_active == false) {
        cam_fish->active = 0;
        return;
    }

    if (cam_fish->active == false) {
        cam_fish->active += 1;
        cam_fish->data = player->unk_878_ptr;

        if (game_w0x3f33f0.current_area_id != 0x4B) {
            cam_view->pitch = DEG_55_RAD;
        } else {
            cam_view->pitch = DEG_50_RAD;
        }

        cam_view->yaw = 0.0f;
    }

    if (fish_cam_sub0x221700(cam_work, cam_view, cam_fish) >= 0) {
        cam_view->this_view_active = true;
    }
}

s32 fishing_cam_chk0x2216e0(PLAYER_WORK* player) {
    return pl_flag_ck0x14ef60(player, 0x80000) != 0;
}

s32 fish_cam_sub0x221700(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view, CAM_FISHING_CONTROL* cam_fish) {
    f32 tmp_vec[3];
    f32 angle_rad;

    PLAYER_WORK* player;
    FISHING_DATA* fish_data;
    FISH_CAM_OFFSET* fish_offsets;

    player = cam_work->player_ptr;

    fish_data = cam_fish->data;
    if (fish_data == NULL) {
        return -1;
    }

    fish_offsets = fishcam_ofs_tbl0x339080[game_w0x3f33f0.current_area_id];
    if (fish_offsets == NULL) {
        return -1;
    }

    angle_rad = DEG2RAD * fish_data->unk_14;

    flvecCopy0x173300(tmp_vec, fish_offsets->cam_offset);
    flvecRotY0x173070(tmp_vec, angle_rad);
    AddVector0x120820(cam_view->cam_pos, player->pos, tmp_vec);

    flvecCopy0x173300(tmp_vec, fish_offsets->target_offset);
    flvecRotY0x173070(tmp_vec, angle_rad);
    AddVector0x120820(cam_view->target_pos, player->pos, tmp_vec);

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/camera", NPCZoomInCameraRequest0x221820);

void NPCZoomInCameraCancel0x221850(void) {
    CameraWork0x4767c0.views[3].state.rot_something[0] = 0;
}

s32 NPCZoomInCameraCheck0x221860(void) {
    return (u16) CameraWork0x4767c0.views[3].state.rot_something[0] != 0;
}

void cam_plEX_zoom0x221870(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view, CAM_ZOOM_CONTROL* cam_zoom) {
    PLAYER_WORK* player;
    CAM_W_VIEW* active_view;
    UNK_ZOOM_STRUCT* unk;
    f32 tmp;

    cam_view->this_view_active = false;

    switch (cam_zoom->state) {
        case 0:
            if (cam_zoom->unk_20 != 0) {
                cam_zoom->unk_22 = 0;
                cam_zoom->state += 1;
            }
            return;

        case 1:
            if (cam_zoom->unk_22 < 15) {
                cam_zoom->unk_22 += 1;
            }
            if (cam_zoom->unk_20 == 0) {
                cam_zoom->state += 1;
            }
            break;

        case 2:
            if (cam_zoom->unk_22 > 0) {
                cam_zoom->unk_22 -= 1;
            }
            if (cam_zoom->unk_20 != 0) {
                cam_zoom->state = 1;
            } else if (cam_zoom->unk_22 == 0) {
                cam_zoom->state = 0;
                return;
            }
            break;

        default:
            break;
    }

    player = cam_work->player_ptr;
    active_view = &cam_work->views[cam_work->active_view];
    unk = cam_zoom->unk_4;

    if (unk->unk_2 == 3) {
        cpInterVector0x120e30(cam_zoom->unk_14, player->pos, unk->unk_AC, 0.5f);
        cam_zoom->unk_14[1] += 64.0f;
    } else {
        cpInterVector0x120e30(cam_zoom->unk_14, player->pos, cam_zoom->unk_8, 0.2f);
        cam_zoom->unk_14[1] += 150.0f;
    }

    tmp = 0.06666667f * cam_zoom->unk_22;

    cpInterVector0x120e30(cam_view->target_pos, cam_zoom->unk_14, active_view->target_pos, tmp);

    cam_view->pitch = (active_view->pitch * (1.0f - tmp)) + (DEG_30_RAD * tmp);

    flvecCopy0x173300(cam_view->cam_pos, active_view->cam_pos);

    cam_view->yaw = active_view->yaw;
    cam_view->this_view_active = true;
}

void cam_init_sub_demo0x221aa0(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    cam_view->yaw = 0;
    cam_view->pitch = DEG_55_RAD;

    cam_view->state_demo.demo_id = 0;
    cam_view->state_demo.demo_status = 0;
    cam_view->state_demo.target_ptr = NULL;
}

void cam_sub_demo0x221ac0(CAMERA_WORK* cam_work, CAM_W_VIEW* cam_view) {
    CAM_VIEW_STATE_DEMO* view_state;
    s32 result;

    view_state = &cam_view->state_demo;
    cam_view->this_view_active = 0;

    switch (cam_view->unk_78_u8) {
        case 0:
            if (cam_work->demo_play == 0) {
                break;
            }

            view_state->demo_id = cam_work->demo_play;
            view_state->target_ptr = cam_work->wyvern_ptr;
            cam_view->unk_78_u8 += 1;
            cam_view->unk_7C = 0;

        case 1:
            cam_work->demo_play = 0;
            result = point_camera0x221be0(cam_work, cam_view);

            if (result <= 0) {
                cam_view->this_view_active = 1;

                if (result == 0) {
                    view_state->demo_status = 1;
                } else {
                    view_state->demo_status = -1;
                }
                break;
            }

            cam_view->unk_78_u8 = 0;
            view_state->demo_id = 0;
            view_state->demo_status = 0;
            view_state->target_ptr = NULL;
            break;

        default:
            break;
    }
}

void DemoCameraRequest0x221b80(s32 demo, void* target_ptr) {
    CameraWork0x4767c0.demo_play = demo;
    CameraWork0x4767c0.wyvern_ptr = target_ptr;
}

void DemoCameraCancel0x221ba0(void) {
    CAM_W_VIEW* view = &CameraWork0x4767c0.views[4];

    view->unk_78_u8 = 0;

    view->state_demo.demo_id = 0;
    view->state_demo.demo_status = 0;
    view->state_demo.target_ptr = NULL;

    CameraWork0x4767c0.demo_play = 0;
}

s8 DemoCameraCheck0x221bd0(void) {
    return CameraWork0x4767c0.views[4].state_demo.demo_status;
}

u32 point_camera0x221be0(CAMERA_WORK* cam, CAM_W_VIEW* view) {
    f32 temp_f;
    u8 status;
    s32 ret;
    POINT_CAM_STATE* state;

    status = view->cmd_status;
    state = &view->state_point;
    switch (status) {
        case 0:
            view->cmd_status = status + 1;
            state->point.logic_pos = Demo_cam_tbl0x348d70[state->point.unk_e[0]];
            flvecCopy0x173300(view->cam_pos, cam->pos);
            flvecCopy0x173300(state->pos, cam->pos);
            flvecCopy0x173300(view->target_pos, cam->target);
            flvecCopy0x173300(state->tar, cam->target);
            temp_f = cam->roll;
            view->yaw = temp_f;
            state->yaw_end = temp_f;
            temp_f = cam->pitch;
            view->pitch = temp_f;
            state->pitch_end = temp_f;
            view->move_total = -1;
            view->move_cur = -1;
            /* fallthrough */
        case 1:
            ret = point_cam_sub0x222410(cam, view, state);
            if (ret > 0) {
                ret = view->cmd_status + 1;
                view->cmd_status = view->cmd_status + 1;
                case 2:
                    ret = 1;
                    return ret; //?
            }
    }
    return;
}

static MATRIX* get_em_local0x221cf0(POINT_CAM_STATE* ptcam) {
    MONSTER_WORK* mon;
    MATRIX* retval;

    mon = ptcam->point.ent_ptr;
    if ((mon != 0)) {
        if ((mon->exists != 0)) {
            retval = &mon->matrix;
            return retval;
        }
    }
    ptcam->point.halt_logic = true;
    retval = 0;
    return retval;
}

void cmd_set_pos0x221d30(f32* result, POINT_CAM_STATE* pcam, s32* opargs) {
    PLAYER_WORK* player;
    MATRIX* em_mat;

    player = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
    result[0] = 0.00024414062f * opargs[1]; // constant is 1/4096
    result[1] = 0.00024414062f * opargs[2];
    result[2] = 0.00024414062f * opargs[3];
    switch (pcam->point.target_type) {
        case 2:
            nlCalcPoint0x120ec0(result, result, player->part_ptrs[pcam->point.cam_part]->matrix);
            return;
        case 0:
            nlCalcPoint0x120ec0(result, result, player->matrix);
            return;
        case 1:
            AddVector0x120820(result, result, player->pos);
            return;
        case 3:
            em_mat = get_em_local0x221cf0(pcam);
            if (em_mat != NULL) {
                nlCalcPoint0x120ec0(result, result, *em_mat);
                return;
            }
        case 5: // this was needed to generate a jumptable
        default:
            break;
        case 4:
            AddVector0x120820(result, result, pcam->tar);
            break;
    }
    return;
}

void cmd_set_tar0x221e60(f32* result, POINT_CAM_STATE* pcam, s32* opargs) {
    PLAYER_WORK* player;
    MATRIX* em_mat;

    player = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
    result[0] = 0.00024414062f * opargs[1];
    result[1] = 0.00024414062f * opargs[2];
    result[2] = 0.00024414062f * opargs[3];
    switch (pcam->point.player_target_type) {
        case 2:
            nlCalcPoint0x120ec0(result, result, player->part_ptrs[pcam->point.target_part]->matrix);
            break;
        case 0:
            nlCalcPoint0x120ec0(result, result, player->matrix);
            break;
        case 1:
            AddVector0x120820(result, result, player->pos);
            break;
        case 3:
            em_mat = get_em_local0x221cf0(pcam);
            if (em_mat != NULL) {
                nlCalcPoint0x120ec0(result, result, *em_mat);
            }
            /* fallthrough */
        case 4:
            break;
    }
    return;
}

void cmd_copy0x221f90(f32* vals, s32 what) {
    switch (what) {
        case 0:
            flvecCopy0x173300(&vals[3], &vals[0]);
            break;
        case 1:
            flvecCopy0x173300(&vals[9], &vals[6]);
            break;
        case 2:
            vals[13] = vals[12];
            break;
        case 3:
            vals[15] = vals[14];
            break;
    }
}

void get_angle0x222020(s16* arg0, CAM_W_VIEW* arg1) {
    if (arg1->move_total > 0) {
        arg0[0] = arg1->target_yaw - arg1->current_yaw;
        arg0[0] = arg1->current_yaw + arg0[0] * arg1->move_cur / arg1->move_total;
        arg0[1] = arg1->target_pitch - arg1->current_pitch;
        arg0[1] = arg1->current_pitch + arg0[1] * arg1->move_cur / arg1->move_total;
    } else {
        arg0[0] = arg1->target_yaw;
        arg0[1] = arg1->target_pitch;
    }
}

// temp rodata padding to keep alignment, move/remove as needed?
const char __pad_cam_0x36B0E8[] = "\0\0\0\0"; // shunts cmd_cam_move jumptable to next 0x10

void cmd_cam_move0x2220c0(CAMERA_WORK* cam, CAM_W_VIEW* view, POINT_CAM_STATE* pcam) {
    f32 move_progress;
    f32 move_left;
    s16 angles[2];
    MATRIX mat;
    VEC3 point;
    MATRIX* em;
    u8 byt;
    PLAYER_WORK* pw;
    
    if(view->move_total > 0)
        move_progress = (f32)view->move_cur / (f32)view->move_total;
    else
        move_progress = 1.0f;
    move_left = 1.0f - move_progress;
    switch(pcam->point.simple){
        case 0:
            get_angle0x222020(angles, view);
            flmatInit0x171ce0(mat);
            flmatRotXYZ330x1724e0(mat, angles[0]*DEG2RAD, angles[1]*DEG2RAD, 0);
            point[0] = 0.0f;
            point[1] = 0.0f;
            point[2] = 500.0f;
            if(pcam->point.follow_target == 1)
            {
                cpInterVector0x120e30(view->cam_pos, pcam->pos, pcam->unk_c, move_progress);
                flvecApplyMat33_20x172e70(point, mat);
                pw = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
                switch(pcam->point.target_type){
                    case 2:
                        flvecApplyMat33_20x172e70(point, pw->part_ptrs[pcam->point.target_part]->matrix);
                        break;
                    case 0:
                        flvecApplyMat33_20x172e70(point, pw->matrix);
                        break;
                    case 3:
                        em = get_em_local0x221cf0(pcam);
                        if(em != 0)
                        {
                            flvecApplyMat33_20x172e70(point, *em);
                        }
                        break;
                    case 1:
                    case 4:
                    case 5:
                    default:
                        break;
                }
                AddVector0x120820(view->target_pos, view->cam_pos, point);
            }
            else
            {
                cpInterVector0x120e30(view->target_pos, pcam->tar, pcam->ground_hit, move_progress);
                point[2] = pcam->point.cam_offset_target * move_progress + pcam->point.cam_offset_start * move_left;
                flvecApplyMat33_20x172e70(point, mat);
                pw = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
                switch(pcam->point.player_target_type){
                    case 2:
                        flvecApplyMat33_20x172e70(point, pw->part_ptrs[pcam->point.cam_part]->matrix);
                        break;
                    case 0:
                        flvecApplyMat33_20x172e70(point, pw->matrix);
                        break;
                    case 3:
                        em = get_em_local0x221cf0(pcam);
                        if(em != 0)
                        {
                            flvecApplyMat33_20x172e70(point, *em);
                        }
                        break;
                    case 1:
                    case 4:
                    default:
                    break;
                }
                AddVector0x120820(view->cam_pos, view->target_pos, point);
            }
            break;
        case 1:
            cpInterVector0x120e30(view->target_pos, pcam->tar, pcam->ground_hit, move_progress);
            cpInterVector0x120e30(view->cam_pos, pcam->pos, pcam->unk_c, move_progress);
            break;
    }
    view->yaw = pcam->yaw_end * move_progress + pcam->yaw_start * move_left;
    view->pitch = pcam->pitch_end * move_progress + pcam->pitch_start * move_left;
}

s32 point_cam_hit0x222400(CAMERA_WORK* a1, CAM_W_VIEW* a2, POINT_CAM_STATE* a3, void* a4) {
    return 0;
}

s32 point_cam_sub0x222410(CAMERA_WORK* cam_w, CAM_W_VIEW* view, POINT_CAM_STATE* pcam) {
    s32 move_amt;
    POINT_CAM_OP* op_ptr; // next unprocessed op
    s32 running;          // looping
    s32 retval;
    POINT_CAM_OP* op;
    s32* opdata; // current op

    running = 1;
    pcam->point.halt_logic = 0U;
    op_ptr = pcam->point.logic_pos;

    while (true) {
        op = op_ptr;
        opdata = (s32*) op_ptr;
        op_ptr += op->size;
        switch (op->op) {
            case 0:
                pcam->point.simple = op->argb[0];
                break;
            case 1:
                pcam->point.target_type = op->argb[0];
                pcam->point.cam_part = op->argb[1];
                break;
            case 2:
                cmd_set_pos0x221d30(pcam->pos, pcam, opdata);
                break;
            case 3:
                cmd_set_pos0x221d30(pcam->unk_c, pcam, opdata);
                break;
            case 4:
                pcam->point.player_target_type = op->argb[0];
                pcam->point.target_part = op->argb[1];
                break;
            case 5:
                cmd_set_tar0x221e60(pcam->tar, pcam, opdata);
                break;
            case 6:
                cmd_set_tar0x221e60(pcam->ground_hit, pcam, opdata);
                break;
            case 7:
                pcam->point.follow_target = op->argb[0];
                break;
            case 8:
                view->target_yaw = op->args;
                break;
            case 9:
                view->current_yaw = op->args;
                break;
            case 10:
                view->target_pitch = op->args;
                break;
            case 11:
                view->current_pitch = op->args;
                break;
            case 12:
                pcam->point.cam_offset_target = 0.0625f * opdata[1]; // 1/16?
                break;
            case 13:
                pcam->point.cam_offset_start = 0.0625f * opdata[1];
                break;
            case 14:
                pcam->yaw_end = DEG2RAD * opdata[1];
                break;
            case 15:
                pcam->yaw_start = DEG2RAD * opdata[1];
                break;
            case 16:
                pcam->pitch_end = DEG2RAD * opdata[1];
                break;
            case 17:
                pcam->pitch_start = DEG2RAD * opdata[1];
                break;
            case 18:
                move_amt = opdata[1];
                view->move_total = move_amt;
                view->move_cur = move_amt;
                break;
            case 19:
                cmd_copy0x221f90(pcam->pos, op->argb[0]);
                break;
            case 20:
                pcam->point.logic_loop = op_ptr;
                break;
            case 21:
                view->move_cur = (s16) (view->move_cur - 1);
                if (view->move_total <= 0 || view->move_cur >= 0) {
                    op_ptr = pcam->point.logic_loop;
                    running = 0;
                    retval = 0;
                } else {
                    flvecCopy0x173300(pcam->pos, view->cam_pos);
                    flvecCopy0x173300(pcam->tar, view->target_pos);
                    view->target_yaw = view->current_yaw;
                    view->target_pitch = view->current_pitch;
                    pcam->yaw_end = view->yaw;
                    pcam->pitch_end = view->pitch;
                    view->move_cur = -1;
                    view->move_total = -1;
                }
                break;
            case 22:
                cmd_cam_move0x2220c0(cam_w, view, pcam);
                break;
            case 25:
                if (point_cam_hit0x222400(cam_w, view, pcam, opdata) != 0) {
                    default:
                        return 1;
                }
                break;
            case 24:
                running = 0;
                retval = -1;
                break;
        }

        if (pcam->point.halt_logic != 0) {
            return 1;
        }
        pcam->point.logic_pos = op_ptr;
        if (running == 0) {
            return retval;
        }

    } // while end
}

void cam2view0x2227a0(CAMERA_WORK* cam) {
    QUAKE* quake;
    s16 qtime;
    s32 active;
    s32 q;
    CAM_W_VIEW* view;

    quake = &cam->sub_quake;
    for (q = 2; q > 0; q -= 1) {
        if (quake->active != false) {
            qtime = quake->timer - 1;
            quake->timer = qtime;
            if (qtime <= 0) {
                quake->active = false;
            }
        }
        quake++;
    }
    view = &cam->views[cam->active_view];
    flvecCopy0x173300(cam->pos, view->cam_pos);
    flvecCopy0x173300(cam->target, view->target_pos);
    cam->roll = view->yaw;
    cam->pitch = view->pitch;
    active = -1;
    if (cam->views[4].this_view_active != 0) {
        active = 4;
    } else if (cam->views[2].this_view_active != 0) {
        active = 2;
    } else if (cam->views[3].this_view_active != 0) {
        active = 3;
    }
    if (active > 0) {
        view = &cam->views[active];
        flvecCopy0x173300(lpView0x38a110->pos, view->cam_pos);
        flvecCopy0x173300(lpView0x38a110->target, view->target_pos);
        if (active == 2) {
            quake_sub0x222bc0(&cam->quake);
        }
        RollView0x169da0(view->yaw);
        SetAngleOfView0x169db0(view->pitch);
    } else {
        flvecCopy0x173300(lpView0x38a110->pos, cam->pos);
        flvecCopy0x173300(lpView0x38a110->target, cam->target);
        quake_sub0x222bc0(&cam->sub_quake);
        RollView0x169da0(cam->roll);
        SetAngleOfView0x169db0(cam->pitch);
    }
    set_to_std_cam0x220650(active);
}

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
    quake->active = true;
    quake->type = which | 0x80;
    quake->timer = quake_time_tbl0x338ed0[which];
}

void Pl_set_quake_sub0x222a10(PLAYER_WORK* ply, u32 which) {
    QUAKE* quake = &CameraWork0x4767c0.sub_quake;
    if ((u8) Pl_stg_ck0x151ff0(ply)) {
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
    if ((u8) Em_stg_ck0x152010(mon)) {
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
    if ((u8) Pl_stg_ck0x151ff0(ply)) {
        quake->active = true;
        quake->type = which;
        quake->timer = quake_time_tbl0x338ed0[which];
        quake->pos[0] = ply->pos[0];
        quake->pos[1] = ply->pos[1];
        quake->pos[2] = ply->pos[2];
    }
}

void quake_sub0x222bc0(QUAKE* quake) {
    f32 shake_offset;
    f32 intensity;

    if (quake->active == 0) {
        return;
    }

    shake_offset = 90.0f * ((f32) quake->timer / quake_time_tbl0x338ed0[quake->type & 0x7F]); // timing

    if ((quake->type & 0x7F) < 2) {
        shake_offset = 10.0f * flSin0x173600(shake_offset / 360.0f * PI * 2.0f);
    } else {
        shake_offset = 12.0f * flSin0x173600(shake_offset / 360.0f * PI * 2.0f);
    }

    if (quake->type & 0x80) {
        intensity = 1.0f;
    } else {
        intensity = flvecCalcDistance0x173140(quake->pos, lpView0x38a110->pos);
        if (intensity > 2000.0f) {
            intensity = 0.0f;
        } else {
            intensity = 1.0f - (intensity / 2000.0f);
        }
    }

    shake_offset = shake_offset * intensity;
    if ((quake->timer >> 1) & 1) {
        shake_offset *= -1.0f;
    }
    lpView0x38a110->pos[1] += shake_offset;
    lpView0x38a110->target[1] += shake_offset;
}

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

void default_area_data0x222e20(CAMERA_WORK* cam_work) {
    CAM_DATA_HEADER* cam_data = cam_data_area0x38a204;
    CAM_AREA_DATA* entry;
    CAM_HEIGHT_ENTRY* stage_data;
    s32 i;

    // CAM_DATA_HEADER
    cam_data->unk_0 = 258;
    cam_data->entry_count = 0;
    cam_data->x_count = 1;
    cam_data->y_count = 1;
    cam_data->area_width = 20000;
    cam_data->area_length = 20000;
    cam_data->base_offset_x = 0;
    cam_data->base_offset_y = 0;
    cam_data->area_width32 = 20000;
    cam_data->area_length32 = 20000;
    cam_data->cam_grid_ptr = NULL;
    cam_data->entry_list_ptr = NULL;
    cam_data->eof = NULL;

    entry = &cam_data->entries[0];
    cam_data->first_entry_ptr = entry;

    // CAM_DATA_ENTRY(first entry in CAM_DATA_HEADER.entries)
    entry->header.unk_0 = 0;
    entry->header.index = 0;
    entry->header.move_type = NO_MOVE_TYPE;
    entry->header.axes = 2; // missing enum number
    entry->header.target_type = NO_TARGET;
    entry->header.zone_count = 0;
    entry->header.min_distance = 400.0f;
    entry->header.max_distance = 2400.0f;
    entry->header.near_zoom = 1.0f;
    entry->header.far_zoom = 0.75f;
    entry->header.zones_ptr = NULL;
    entry->header.bytepairs_ptr = NULL;

    for (i = 0; i < 4; i++) {
        stage_data = &stage_camera_data_tbl0x2f58e0[i][game_w0x3f33f0.current_area_id];
        entry->follow.entries[i + 1].data.unk_4 = stage_data->unk_4;
        entry->follow.entries[i + 1].data.unk_8 = stage_data->unk_8;
        entry->follow.entries[i + 1].data.height = stage_data->height;
        entry->follow.entries[i + 1].data.unk_18 = stage_data->unk_18;
    }

    entry->follow.entries[0].data.unk_4 = 300.0f;
    entry->follow.entries[0].data.unk_8 = 160.0f;
    entry->follow.entries[0].data.height = 184.0f;
    entry->follow.entries[0].data.unk_18 = 80.0f;

    entry->follow.fov = 0.87266463f;
    entry->follow.roll = 0;
    entry->follow.unk_8 = 0;
    entry->follow.unk_E = 0;
    entry->follow.unk_C = 0;
    
    cam_work->CamDataBuffer = cam_data;
}

// this match requires default_area_data match as static
INCLUDE_ASM("asm/nonmatchings/main/camera", StageCamInit0x223000);

// void StageCamInit0x223000(CAMERA_WORK* cam) {
//     CAM_DATA_HEADER* dataBuff;
//
//     if (cam->CamDataBuffer == 0) {
//         default_area_data0x222e20(cam);
//     }
//     dataBuff = cam->CamDataBuffer;
//     cam->area_xz.map_area_count_x = dataBuff->x_count;
//     cam->area_xz.map_area_count_z =  dataBuff->y_count;
//     cam->area_xz.map_area_width = dataBuff->area_width;
//     cam->area_xz.map_area_length = dataBuff->area_length;
//     cam->area_xz.map_area_offset_x = dataBuff->base_offset_x;
//     cam->area_xz.map_area_offset_z = dataBuff->base_offset_y;
//     cam->map_area_width_u32 = dataBuff->area_width32;
//     cam->map_area_length_u32 = dataBuff->area_length32;
// }

s32 SetAreaData0x223070(CAMERA_WORK* cam) {
    CAM_DATA_HEADER* data;
    PLAYER_WORK* player;
    CAM_GRID_CELL* grid;
    s32 grid_index;
    CAM_GRID_CELL* cell;
    CAM_AREA_DATA** cell_entries;
    s32 count;

    data = cam->CamDataBuffer;
    player = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];

    if (data == 0) {
        cam->CamAreaPtr = 0;
        return -1;
    }

    cam->CamAreaPtr = data->first_entry_ptr;

    if (cam->cam_grid_returnval != 0) {
        return 0;
    }

    grid = data->cam_grid_ptr;
    if (grid == 0) {
        return 0;
    }

    grid_index = cam->cam_grid_x + (cam->area_xz.map_area_count_x * cam->cam_grid_y);
    cell = &grid[grid_index];

    count = cell->entry_count;
    if (count == 0) {
        return 0;
    }

    cell_entries = cell->entries_ptr;
    for (; count != 0; count--) {
        if (CameraAreaCheck0x2232a0(*cell_entries, player, 1) == 0) {
            cam->CamAreaPtr = *cell_entries;
            return 1;
        }
        cell_entries++;
    }

    return 0;
}

u8 Get_cam_grid_XZ0x223190(u16* cam_x, u16* cam_z, f32* pos, CAM_AREA_XZ* area_count) {
    f32 offset;
    u32 z_norm;
    u32 x_norm;
    u8 boundsflag;
    u16 z_count;
    u16 x_count;

    offset = pos[0];
    boundsflag = 0;
    x_norm = offset;
    x_count = area_count->map_area_count_x;
    x_norm = (x_norm - area_count->map_area_offset_x) / area_count->map_area_width;
    if (x_norm >= x_count) {
        x_norm = x_count - 1;
        boundsflag |= 1;
    }
    *cam_x = x_norm;

    offset = pos[2];
    z_norm = offset;
    z_count = area_count->map_area_count_z;
    z_norm = (z_norm - area_count->map_area_offset_z) / area_count->map_area_length;
    if (z_norm >= z_count) {
        z_norm = z_count - 1;
        boundsflag = 0x10;
    }
    *cam_z = z_norm;

    return boundsflag;
}

s32 CameraAreaCheck0x2232a0(CAM_AREA_DATA* entry, PLAYER_WORK* player, u8 mask) {
    CAM_GEOMETRY_ZONE* zone;
    s32 zone_count;
    f32 player_dir[3];
    f32 proj;

    if (CamAreaAttribChk0x2233c0(entry, player) == 0) {
        return 2;
    }

    zone_count = entry->header.zone_count;
    zone = entry->header.zones_ptr;

    for (; zone_count != 0; zone_count--) {
        if (!(zone->flags & mask)) {
            player_dir[0] = player->pos[0] - zone->origin[0];
            player_dir[1] = player->pos[1] - zone->origin[1];
            player_dir[2] = player->pos[2] - zone->origin[2];

            proj = flvecInnerProduct0x173220(zone->axis_normal, player_dir);

            if ((proj >= 0.0f) &&
                (proj <= zone->max_extent) &&
                (Area_XZ_Check0x223410(zone, player->pos) == 0)) {
                return 0;
            }
        }
        zone++;
    }

    return 2;
}

s32 CamAreaAttribChk0x2233c0(CAM_AREA_DATA* entry, PLAYER_WORK* player) {
    if (entry->header.attribute & 0x80) {
        if (player->unk_14 || player->unk_15 < 0x27 || player->unk_15 > 0x2B) {
            return 0;
        }
    }

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/camera", Area_XZ_Check0x223410);

INCLUDE_ASM("asm/nonmatchings/main/camera", GetPanTarget0x223500);

void GetRailTarget0x2235e0(CAMERA_WORK* cam, VEC4 out, CAM_AREA_DATA* area, VEC4 in) {
    PLAYER_WORK *player = cam->player_ptr;

    switch (area->header.target_type) {
    case NO_MOVE_TYPE:                                    
        flvecCopy0x173300(out, in);
        break;
    case PAN:
        nlCalcPoint0x120ec0(out, area->rail.player_pan_target, player->matrix);
        break;
    case RAIL:
        AddVector0x120820(out, player->pos, area->rail.player_rail_target);
        break;
    }
    
    switch (area->header.axes) {
    case Y:   
        out[1] = in[1];
        break;
    case XZ:      
        out[0] = in[0];
        out[2] = in[2];
    }
}

void GetRailCamPos0x2236d0(VEC4 arg0, CAMERA_WORK* cam, CAM_AREA_DATA* area, SPLINE_RVALUE* res) {
    f32 distance;

    Spline0x2248c0(res->val, area->rail.pos, area->rail.point_num);
    distance = cam->rail_work.rail_percent * area->rail.pos[cam->rail_work.rail_spline][3];
    CamRailPoint0x223f00(arg0, res->val[cam->rail_work.rail_spline], distance);
}

s32 GetNearSection0x223760(CAM_CNF_RAIL* cnf, VEC4 pos) {
    f32 distances[SPLINE_POINT_MAX];
    f32 max_dist;
    VEC3* targets;
    f32* distances_ptr;
    s32 i;
    s32 point;

    targets = (VEC3*)&cnf->tar[0]; //??
    distances_ptr = &distances[0];
    max_dist = 1e7f; // 10000000.0f
    point = 0;
    for(i = 0; i < cnf->point_num; i++, targets++, distances_ptr ++) {
        *distances_ptr = flvecCalcDistance0x173140(pos, targets[0]);
        if (max_dist > *distances_ptr) {
            max_dist = *distances_ptr;
            point = i;
        }
        
    }
    if ((point != 0) && (point < (cnf->point_num - 1))) {
        if (distances[point-1] < distances[point+1]) {
            point -= 1;
        }
    } else if (point >= (cnf->point_num - 1)) {
        point = cnf->point_num - 2;
    }
    return point;
}

//returns -1 if last point has negative distance
//returns 0 if in range of a point
//returns 1 if last point has a positive distance
//ret_distance loaded with targeted point's distance
static s32 get_near_point_sub0x223870(f32* ret_distance, VEC3* arg1, f32* target, f32* distances, u32 points) {
    f32 closest_distance;
    s32 retval;

    if (*distances < 0.0f) { //if first float neg
        closest_distance = -(*distances); //set to its pos
        *ret_distance = 0.0f;
        retval = -1;
    }
    else if( *distances > target[3]){ //if > arg3's W
        closest_distance = *distances -  target[3]; //save the distance
        *ret_distance =  target[3]; //target the W?
        retval = 1;
    }
    else{
        *ret_distance = *distances; //in range, use this
        return 0;
    }
    
    if (points == 1) { //if only one point,
        return retval; //return with what we have
    }
    
    for (points--; points != 0; points--) {
        distances++; //check remaining floats
        if (*distances < 0.0f) {
            if (closest_distance > -*distances) {
                closest_distance = -*distances;
                *ret_distance = 0.0f;
                retval = -1;
            }
        }
        else if(*distances > target[3]){
            if ( closest_distance > *distances - target[3] ) { //if closer, update closest
                closest_distance = *distances - target[3];
                *ret_distance = target[3];
                retval = 1;
            }
        }
        else {
                *ret_distance = *distances;
                return 0;
            }
    }
    return retval;
}

//returns 0 if no near points
s32 GetNearPoint0x223980(RAIL_WORK* rail, SPLINE_RVALUE* spline, CAM_CNF_RAIL* arg2, f32* arg3) {
    f32 scratch[5];
    s32 nearest_status;
    s32 near_points;

    Spline0x2248c0(spline->val, arg2->tar, arg2->point_num);
    near_points = GetOrthogonalPoint0x223fe0(scratch, spline->val[rail->rail_spline], arg3, arg2->rail_type);
    if (near_points == 0) {
        rail->rail_progress = 0;
        return 0;
    }
    nearest_status = get_near_point_sub0x223870(&rail->rail_progress, spline->val[rail->rail_spline], arg2->tar[rail->rail_spline], scratch, near_points);
    if (nearest_status > 0) { //go to next point
        if (rail->rail_spline < arg2->point_num - 2) {
            near_points = GetOrthogonalPoint0x223fe0(scratch, spline->val[rail->rail_spline + 1], arg3, arg2->rail_type);
            if(near_points != 0) {
                rail->rail_spline++;
                get_near_point_sub0x223870(&rail->rail_progress, spline->val[rail->rail_spline], arg2->tar[rail->rail_spline], scratch, near_points);
            }
        }
    } else if (nearest_status < 0) { //go back a point
        if (rail->rail_spline > 0) {
            near_points = GetOrthogonalPoint0x223fe0(scratch, spline->val[rail->rail_spline - 1], arg3, arg2->rail_type);
            if(near_points != 0) {
                rail->rail_spline--;
                get_near_point_sub0x223870(&rail->rail_progress, spline->val[rail->rail_spline], arg2->tar[rail->rail_spline], scratch, near_points);
            }
        }
    }
    return 1;
}

void cam_rail_move_sub0x223b50(RAIL_WORK* rail, CAM_CNF_RAIL* cnf, s32 section, f32 point) {
    f32 spline_left;
    f32 progress;
    f32 railspeed;

    railspeed = RAIL_SPEED;
    if (rail->rail_spline < section) {
        do {
            progress = rail->rail_progress;
            spline_left = cnf->tar[rail->rail_spline][3] - progress; //how long to go
            if (spline_left <= railspeed) {
                railspeed -= spline_left;
                rail->rail_spline++;
                rail->rail_progress = 0.0f;
            } else {
                rail->rail_progress = progress + railspeed;
                return;
            } 
        } while (rail->rail_spline < section);
        progress = rail->rail_progress;
        if ((point - progress) <= railspeed) {
            rail->rail_progress = point;
        } else {
            rail->rail_progress = progress + railspeed;
        }
    } else {
        do {
            if (rail->rail_progress <= railspeed) {
                railspeed -= rail->rail_progress;
                rail->rail_spline--;
                rail->rail_progress = cnf->tar[section][3];
            } else {
                rail->rail_progress = rail->rail_progress - railspeed;
                return;
            }
        } while (rail->rail_spline > section);
        progress = rail->rail_progress;
        if ((progress - point) <= railspeed) {
            rail->rail_progress = point;
        } else {
            rail->rail_progress = progress - railspeed;
        }    
    }
}

s32 cam_rail_move0x223c90(RAIL_WORK* rail, CAM_CNF_RAIL* cnf, SPLINE_RVALUE* spline, VEC4 point) {
    RAIL_WORK temp_rail;

    temp_rail.rail_spline = GetNearSection0x223760(cnf, point);
    if (GetNearPoint0x223980(&temp_rail, spline, cnf, point)) {
        if (rail->rail_spline == temp_rail.rail_spline) {
            if (rail->rail_progress < temp_rail.rail_progress) {
                if ((temp_rail.rail_progress - rail->rail_progress) <= RAIL_SPEED) {
                    rail->rail_progress = temp_rail.rail_progress;
                } else {
                    rail->rail_progress += RAIL_SPEED;
                }
            } else if (rail->rail_progress > temp_rail.rail_progress) {
                if ((rail->rail_progress - temp_rail.rail_progress) <= RAIL_SPEED) {
                    rail->rail_progress = temp_rail.rail_progress;
                } else {
                    rail->rail_progress -= RAIL_SPEED;
                }
            }
        } else {
            cam_rail_move_sub0x223b50(rail, cnf, temp_rail.rail_spline, temp_rail.rail_progress);
        }
    } else {
        return -1;
    }
    rail->rail_percent = rail->rail_progress / cnf->tar[rail->rail_spline][3];
    return 0;
}

s32 cam_rail_move_00x223de0(RAIL_WORK* rail, CAM_CNF_RAIL* cnf, SPLINE_RVALUE* spline, VEC4 pos) {
    rail->rail_spline = GetNearSection0x223760(cnf, pos);
    if (GetNearPoint0x223980(rail, spline, cnf, pos) != 0) {
        rail->rail_percent = rail->rail_progress / (cnf->tar[rail->rail_spline][3]);
        return 0;
    }
    rail->rail_percent = 0.0f;
    rail->rail_progress = 0.0f;
    return -1;
}


s32 CamRailMove0x223e90(CAMERA_WORK* cam, SPLINE_RVALUE* spline, VEC4 point, s32 arg3) {
    CAM_AREA_DATA* area;

    area = cam->CamAreaPtr;
    if (area == 0) {
        return -1;
    }
    if (arg3 == 0) {
        return cam_rail_move_00x223de0(&cam->rail_work, &area->rail, spline, point);
    } else {
        return cam_rail_move0x223c90(&cam->rail_work, &area->rail, spline, point);
    }
}

void CamRailPoint0x223f00(VEC4 res, VEC3* vecs, f32 scale) {
    ScaleVector0x1208a0(res, vecs[0], scale);
    AddVector0x120820(res, res, vecs[1]);
    ScaleVector0x1208a0(res, res, scale);
    AddVector0x120820(res, res, vecs[2]);
    ScaleVector0x1208a0(res, res, scale);
    AddVector0x120820(res, res, vecs[3]);
}

static f32 vInnerProductXZ0x223f90(f32* arg0, f32* arg1) {
    f32 x = arg0[0] * arg1[0];
    f32 z = arg0[2] * arg1[2];

    return x + z;
}

static f32 vInnerProduct0x223fb0(f32* arg0, f32* arg1) {
    f32 x = arg0[0] * arg1[0];
    f32 y = arg0[1] * arg1[1];
    f32 z = arg0[2] * arg1[2];

    return x + y + z;
}

// arg1 is one chunk of a series populated by Spline()
// arg2 is an offset coord?
// arg3 is a bool passed from a struct.. offset 0x20 of CamAreaPtr
s32 GetOrthogonalPoint0x223fe0(f32* arg0, f32 arg1[4][3], f32* arg2, s32 arg3) {
    f32 spB0[3];
    f32 spA0[3];
    f32 sp80[6];
    COMPLEX sp50[5];
    s32 retval;
    s32 counter;

    flvecCopy0x173300(spA0, arg2);
    if (arg3 == 0) {
        spA0[1] = 0;
        SubVector0x120860(spB0, arg1[3], spA0);
        if (!((arg1[0][0] * arg1[0][0] + arg1[0][1] * arg1[0][1] + arg1[0][2] * arg1[0][2]) > 0.0000000001)) {
            if (!((arg1[1][0] * arg1[1][0] + arg1[1][1] * arg1[1][1] + arg1[1][2] * arg1[1][2]) > 0.0000000001)) {
                if (!((arg1[2][0] * arg1[2][0] + arg1[2][1] * arg1[2][1] + arg1[2][2] * arg1[2][2]) > 0.0000000001)) {
                    return 0;
                }
                *arg0 = -(vInnerProductXZ0x223f90(arg1[2], spB0) / vInnerProductXZ0x223f90(arg1[2], arg1[2]));
                return 1;
            }
            sp80[0] = 2.0f * vInnerProductXZ0x223f90(arg1[1], arg1[1]);
            sp80[1] = 3.0f * vInnerProductXZ0x223f90(arg1[1], arg1[2]);
            sp80[2] = 2.0f * vInnerProductXZ0x223f90(arg1[1], spB0) +
                      vInnerProductXZ0x223f90(arg1[2], arg1[2]);
            sp80[3] = vInnerProductXZ0x223f90(arg1[2], spB0);
            return Cardano0x225050(arg0, sp80);
        }
        sp80[0] = 3.0f * vInnerProductXZ0x223f90(arg1[0], arg1[0]);
        sp80[1] = 5.0f * vInnerProductXZ0x223f90(arg1[0], arg1[1]);
        sp80[2] = 4.0f * vInnerProductXZ0x223f90(arg1[0], arg1[2]) +
                  (2.0f * vInnerProductXZ0x223f90(arg1[1], arg1[1]));

        sp80[3] = 3.0f * (vInnerProductXZ0x223f90(arg1[0], spB0) + vInnerProductXZ0x223f90(arg1[1], arg1[2]));
        sp80[4] = 2.0f * vInnerProductXZ0x223f90(arg1[1], spB0) +
                  vInnerProductXZ0x223f90(arg1[2], arg1[2]);
        sp80[5] = vInnerProductXZ0x223f90(arg1[2], spB0);
        DKA50x224dd0(sp50, sp80);

        counter = retval = 0;
        for (; counter < 5U; counter++) {
            if (flAbs0x173540(sp50[counter].b) < 0.001f) {
                retval++;
                *arg0++ = sp50[counter].a;
            }
        }
    } else {
        SubVector0x120860(spB0, arg1[3], spA0);
        if (!((arg1[0][0] * arg1[0][0] + arg1[0][1] * arg1[0][1] + arg1[0][2] * arg1[0][2]) > 0.0000000001)) {
            if (!((arg1[1][0] * arg1[1][0] + arg1[1][1] * arg1[1][1] + arg1[1][2] * arg1[1][2]) > 0.0000000001)) {
                if (!((arg1[2][0] * arg1[2][0] + arg1[2][1] * arg1[2][1] + arg1[2][2] * arg1[2][2]) > 0.0000000001)) {
                    return 0;
                }
                *arg0 = -(vInnerProduct0x223fb0(arg1[2], spB0) /
                          vInnerProduct0x223fb0(arg1[2], arg1[2]));
                return 1;
            }
            sp80[0] = 2.0f * vInnerProduct0x223fb0(arg1[1], arg1[1]);
            sp80[1] = 3.0f * vInnerProduct0x223fb0(arg1[1], arg1[2]);
            sp80[2] = 2.0f * vInnerProduct0x223fb0(arg1[1], spB0) +
                      vInnerProduct0x223fb0(arg1[2], arg1[2]);
            sp80[3] = vInnerProduct0x223fb0(arg1[2], spB0);
            return Cardano0x225050(arg0, sp80);
        }
        sp80[0] = 3.0f * vInnerProduct0x223fb0(arg1[0], arg1[0]);
        sp80[1] = 5.0f * vInnerProduct0x223fb0(arg1[0], arg1[1]);
        sp80[2] = 4.0f * vInnerProduct0x223fb0(arg1[0], arg1[2]) +
                  (2.0f * vInnerProduct0x223fb0(arg1[1], arg1[1]));
        sp80[3] = 3.0f * (vInnerProduct0x223fb0(arg1[0], spB0) +
                          vInnerProduct0x223fb0(arg1[1], arg1[2]));
        sp80[4] = 2.0f * vInnerProduct0x223fb0(arg1[1], spB0) +
                  vInnerProduct0x223fb0(arg1[2], arg1[2]);
        sp80[5] = vInnerProduct0x223fb0(arg1[2], spB0);
        DKA50x224dd0(sp50, sp80);

        counter = retval = 0;
        for (; counter < 5u; counter++) {
            if (flAbs0x173540(sp50[counter].b) < 0.001f) {
                retval++;
                *arg0++ = sp50[counter].a;
            }
        }
    }
    return retval;
}

f32 ZoomRateCalc0x224660(f32 distance, CAM_DATA_ENTRY_HEADER* header) {
    f32 max;
    f32 min;
    f32 zoom;

    min = header->min_distance;
    if (distance <= min) {
        return header->near_zoom; // if too close, return minimum
    }
    max = header->max_distance;
    if (distance >= max) {
        return header->far_zoom; // if too far, return maximum
    }
    if (max == min) {
        return 0.5f * (header->near_zoom + header->far_zoom); // if no range defined, average the settings
    }
    zoom = (header->far_zoom - header->near_zoom) * (distance - min);
    zoom /= (max - min);
    zoom += header->near_zoom;
    return zoom; // otherwise linear scale between the two values
}

static f32 ZoomBaseAngleRail0x2246f0(CAM_CNF_RAIL* cnf, s32 which, f32 scale) {
    return cnf->a[which] * (1.0f - scale) + (cnf->a[which+1] * scale);
}

static f32 RollAngleRail0x224720(CAM_CNF_RAIL* cnf, s32 which, f32 scale) {
    s16 temp[2];
    
    *(s32*)&temp[0] = (s32)(cnf->rot[which+1] - cnf->rot[which]) * (s32)(65536.0f * scale);
    temp[1] += cnf->rot[which];
    return (f32)temp[1] * DEG2RAD;
}

static void tri_diag0x224790(f32* out, f32* subdiag, f32* diag, f32* superdiag, f32* in, s32 equations) {
    //Thomas Algorithm, aka tridiagonal matrix algorithm
    f32 scratch[64];
    f32 divisor; //b-a*scratch
    s32 idx;
    
    divisor = diag[0];
    
    if (divisor != 0.0f) {
        divisor = 1.0f / divisor;
    }
    out[0] = in[0] * divisor;

    for (idx = 1; idx < equations; idx++) {
        scratch[idx - 1] = divisor * superdiag[idx - 1];
        divisor = diag[idx] - (subdiag[idx] * scratch[idx - 1]);
        if (divisor != 0.0f) {
            divisor = 1.0f / divisor;
        }
        out[idx] = divisor * (in[idx] - (subdiag[idx] * out[idx + - 1]));
    }

    for (idx = equations - 2; idx >= 0; idx--) {
        out[idx] -= (scratch[idx] * out[idx + 1]);
    }
}

//first arg is result, second is passed points, third is number of points
void Spline0x2248c0(VEC3 res[][4], VEC4 *pts, s32 num) {
    SPLINE_WORK ram;
    SPLINE_WORK* spline = &ram;
    s32 i;
    VEC3* vp;

    f32 ba;
    f32 ab;

    f32 pow;
    f32 inv;
    f32 invsq;

    
    spline->subdiag[0] = 0.0f;
    spline->diag[0] = pts[0][3] + pts[0][3];
    spline->superdiag[0] = pts[0][3];
    spline->b[0][0] = 3.0f * (pts[1][0] - pts[0][0]);
    spline->b[1][0] = 3.0f * (pts[1][1] - pts[0][1]);
    spline->b[2][0] = 3.0f * (pts[1][2] - pts[0][2]);
    
    for(i = 1; i < num - 1; i++) {
            ba = pts[i][3]/pts[i-1][3];
            ab = pts[i-1][3]/pts[i][3];
            spline->subdiag[i] = pts[i][3];
            spline->diag[i] = 2.0f * (pts[i-1][3] + pts[i][3]);
            spline->superdiag[i] = pts[i-1][3];
            spline->b[0][i] = 3.0f * ((pts[i][0] - pts[i-1][0]) * ba + (pts[i+1][0] - pts[i][0]) * ab);
            spline->b[1][i] = 3.0f * ((pts[i][1] - pts[i-1][1]) * ba + (pts[i+1][1] - pts[i][1]) * ab);
            spline->b[2][i] = 3.0f * ((pts[i][2] - pts[i-1][2]) * ba + (pts[i+1][2] - pts[i][2]) * ab);
    }
    spline->subdiag[num-1] = pts[num-2][3];
    spline->diag[num-1] = pts[num-2][3] + pts[num-2][3];
    spline->superdiag[num-1] = 0.0f;
    spline->b[0][num-1] = 3.0f * (pts[num-1][0] - pts[num-2][0]);
    spline->b[1][num-1] = 3.0f * (pts[num-1][1] - pts[num-2][1]);
    spline->b[2][num-1] = 3.0f * (pts[num-1][2] - pts[num-2][2]);
    tri_diag0x224790(spline->xy[0], spline->subdiag, spline->diag, spline->superdiag, spline->b[0], num);
    tri_diag0x224790(spline->xy[1], spline->subdiag, spline->diag, spline->superdiag, spline->b[1], num);
    tri_diag0x224790(spline->xy[2], spline->subdiag, spline->diag, spline->superdiag, spline->b[2], num);
    vp = res[0];
    for(i = 0; i < (num - 1); i++, vp += 4) {
            inv = 1.0f / pts[i][3];
            invsq = inv*inv;
            pow = 1.0f / flPow0x173670(pts[i][3], 3.0f);
            //pow = 1.0f / pow;
            vp[0][0] = 2.0f * (pts[i][0] - pts[i + 1][0]) * pow + (spline->xy[0][i] + spline->xy[0][i+1]) * invsq;
            vp[1][0] = 3.0f * (pts[i + 1][0] - pts[i][0]) * invsq - (2.0f * spline->xy[0][i] + spline->xy[0][i+1]) * inv;
            vp[2][0] = spline->xy[0][i];
            vp[3][0] = pts[i][0];
            vp[0][1] = 2.0f * (pts[i][1] - pts[i + 1][1]) * pow + (spline->xy[1][i] + spline->xy[1][i+1]) * invsq;
            vp[1][1] = 3.0f * (pts[i+1][1] - pts[i][1]) * invsq - (spline->xy[1][i] * 2.0f + spline->xy[1][i+1]) * inv;
            vp[2][1] = spline->xy[1][i];
            vp[3][1] = pts[i][1];
            vp[0][2] = 2.0f * (pts[i][2] - pts[i + 1][2]) * pow + (spline->xy[2][i] + spline->xy[2][i+1]) * invsq;
            vp[1][2] = 3.0f * (pts[i + 1][2] - pts[i][2]) * invsq - (spline->xy[2][i] * 2.0f + spline->xy[2][i+1]) * inv;
            vp[2][2] = spline->xy[2][i];
            vp[3][2] = pts[i][2];
    }
}

static void dCnvComplex0x224cb0(COMPLEX* arg0, f32 fparg0, f32 fparg1) {
    arg0->a = fparg0;
    arg0->b = fparg1;
}

static void dSubComplex0x224cc0(COMPLEX* arg0, COMPLEX* arg1, COMPLEX* arg2) {
    arg0->a = arg1->a - arg2->a;
    arg0->b = arg1->b - arg2->b;
}

static void dMulComplex0x224cf0(COMPLEX* res, COMPLEX* arg1, COMPLEX* arg2) {
    COMPLEX tmp;
    f32 v3 = arg2->a;
    f32 v2 = arg1->b;
    f32 v4 = arg2->b;
    f32 v1 = arg1->a;

    tmp.a = v1 * v3 - v2 * v4;
    tmp.b = v1 * v4 + v2 * v3;
    *res = tmp;
}

static void dDivComplex0x224d40(COMPLEX* res, COMPLEX* arg1, COMPLEX* arg2) {
    f32 power;
    COMPLEX tmp;
    f32 v2;
    f32 v1;
    f32 v3 = arg2->b;
    f32 v4 = arg2->a;

    power = v4 * v4 + v3 * v3;
    if (power != 0.0f) {
        power = 1.0f / power;
        v1 = arg1->b;
        v2 = arg1->a;
        tmp.a = power * (v2 * v4 + v1 * v3);
        tmp.b = power * (v1 * v4 - v2 * v3);
        *res = tmp;
    } else {
        *res = *arg1;
    }
}

// arg0 is a 5-size array of COMPLEX
// arg1 has six floats? a scalar and then five vals?
void DKA50x224dd0(COMPLEX* out, f32* products) {
    COMPLEX diffprod, totalprod, tempout, ratio, difference;
    f32 scaledproducts[6];
    f32 scalar;
    f32 invscale;
    s32 innest;
    s32 i;
    s32 window_left;
    COMPLEX* out_window;
    f32* in_scale;
    COMPLEX* in_window;
    s32 inner;

    scalar = 0.0f;
    invscale = 1.0f / products[0];

    for (i = 1; i <= 5; i++) {
        scaledproducts[i] = invscale * products[i]; // scale vals
    }

    for (i = 2; i <= 5; i++) {
        invscale = flPow0x173670(flAbs0x173540(scaledproducts[i]), dka_j_tbl0x3393D0[i]); // raise values by powers
        if (invscale > scalar) {
            scalar = invscale; // save the largest
        }
    }

    scalar *= 5.0f; // multiply by five, new scalar

    for (i = 0; i < 5; i++) {
        out[i].a = scalar * dka_init_tbl0x3393a0[i][0]; // save the table vals to the complex array
        out[i].b = scalar * dka_init_tbl0x3393a0[i][1]; // scaled of course
    }

    for (window_left = 25; window_left >= 0; window_left--) {
        inner = 0;
        out_window = out;

        for (; inner < 5; inner++) {
            dCnvComplex0x224cb0(&diffprod, 1.0f, 0.0f);  // make a complex identity? (not imaginary mask!)
            dCnvComplex0x224cb0(&totalprod, 1.0f, 0.0f); // and another!

            tempout = *out_window;

            innest = 0;
            in_scale = &scaledproducts[0];
            in_window = out;

            for (; innest < 5; innest++) {
                dMulComplex0x224cf0(&totalprod, &totalprod, &tempout); // total kept in &90

                totalprod.a += in_scale[1];

                if (innest != inner) {
                    dSubComplex0x224cc0(&difference, &tempout, in_window);  // difference
                    dMulComplex0x224cf0(&diffprod, &diffprod, &difference); // keep it in &98
                }

                in_scale++;
                in_window++;
            }
            dDivComplex0x224d40(&ratio, &totalprod, &diffprod); // ratio of total product over difference product
            dSubComplex0x224cc0(out_window, &tempout, &ratio);  // subtract ratio from table, save it out

            out_window++;
        }
    }
}

//return val is number of unique real roots, first arg is the returned roots
s32 Cardano0x225050(f32* roots, f32* coeffs) {
    f32 c0, c1, c2, c3;
    f32 alpha, alpha2, discriminant;
    f32 P;
    f32 Psquared;
    f32 PoverU;
    f32 Q;
    f32 U;
    f32 Usquared;
    f32 Proot;
    f32 arctan_res;
    f32 cos_res;
    f32 sin_res;
    
    //remove coef from pow3 in c0x^3 + c1x^2 + c2x + c3
    c0 = 1.0f / coeffs[0]; //inverted pow3 coef
    c1 = coeffs[1] * c0; //new pow2 coef
    c2 = coeffs[2] * c0; //new pow1 coef
    c3 = coeffs[3] * c0; //new constant

    //depress the cubic, t^3 + Pt + Q
    alpha = c1 * ONETHIRD;
    alpha2 = alpha * alpha;
    P = (c2 * ONETHIRD) - alpha2; //P = c2 - (c1 * c1 / 3), bake an extra /3 in for simpler discriminant calc
    
    Q = ((alpha2 + alpha2 - c2) * alpha + c3) * 0.5f; 
    //Q = ((2(c1/3 * c1/3) - c2) * c1/3 + c3) / 2
    //Q = ((2*c1*c1*c1)/27 + c1*c2/3 + c3) / 2, baked an extra /2 in for simpler discriminant calc
    
    if ((flAbs0x173540(P) < ERROREPSILON) && 
        (flAbs0x173540(Q) < ERROREPSILON)) {
        //det of 0 means a triple root
        roots[0] = -alpha; //return -b/3a
        return 1;
    }
    Psquared = P * P;
    discriminant = Psquared * P + Q * Q; //note the sign
    if (discriminant > 0.0f) {
        //positive det means one real root
        if ((Q >= 0.0f)) {
            U = flPow0x173670(Q + flSqrt0x173680(discriminant), ONETHIRD);
        } else {
            U = -flPow0x173670(-Q + flSqrt0x173680(discriminant), ONETHIRD);
        }
        PoverU = P / U;
        if (P < 0.0f) {
            roots[0] = PoverU - U;
        } else {
            Usquared = U * U;
            roots[0] = -2.0f * Q * Usquared / ((Usquared + P) * Usquared + Psquared );
        }
        roots[0] = roots[0] - alpha;
        return 1;
    }
    //otherwise det is negative, which means up to three unique real roots
    if (Q < 0.0f) {
        Proot = flSqrt0x173680(-P);
    } else {
        Proot = -flSqrt0x173680(-P);
    }
    if (flAbs0x173540(discriminant) < ERROREPSILON) {
        roots[0] = Proot + Proot - alpha;
        roots[1] = -Proot - alpha;
        return 2;
    }
    arctan_res = flArcTan20x1735e0(flSqrt0x173680(-discriminant), -Q) * ONETHIRD;
    cos_res = Proot * flCos0x173610(arctan_res);
    sin_res = Proot * flSin0x173600(arctan_res) * 1.7320508f; //2*sin(PI/3)
    roots[0] = cos_res + cos_res - alpha;
    roots[1] = -cos_res - sin_res - alpha;
    roots[2] = -cos_res + sin_res - alpha;
    return 3;
}

INCLUDE_ASM("asm/nonmatchings/main/camera", k_HitWallCamera0x225370);

INCLUDE_ASM("asm/nonmatchings/main/camera", k_HitEmCamera0x225510);

INCLUDE_ASM("asm/nonmatchings/main/camera", QuestClearCameraRequest0x225d80);

void RedDragonEscapeCamera0x225e90(void* target_ptr) {
    DemoCameraRequest0x221b80(0x1C, target_ptr);
}

void F_DragonEscapeCamera0x225ea0(MONSTER_WORK* arg0) {
    s32 demo_id;

    if (arg0->unk_388 != 2) {
        demo_id = 0x1F;
    } else {
        demo_id = 0xA;
    }

    DemoCameraRequest0x221b80(demo_id, arg0);
}

void PlayerDieCameraRequest0x225ed0(void) {
    DemoCameraRequest0x221b80(0x1A, NULL);
}

void PlComebackCameraRequest0x225ee0(void) {
    DemoCameraRequest0x221b80(2, NULL);
}

void PilebunkerCameraRequest0x225ef0(void) {
    s32 demo_id;

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

    DemoCameraRequest0x221b80(demo_id, NULL);
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
    DemoCameraRequest0x221b80(0x19, NULL);
}
