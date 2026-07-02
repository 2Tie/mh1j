#include "common.h"
#include "structs.h"
#include "main/camera.h"

//externs
extern PSW Psw0x3f3710[2];
extern GAME_WORK game_w0x3f33f0;
extern PLAYER_WORK player_work0x3e4bf0[8];
extern MONSTER_WORK em_work0x3d82a0[20];
extern VIEW_WORK* lpView0x38a110;

extern f32 flPow0x173670(f32, f32);
extern f32 flSin0x173600(f32);
extern f32 flAbs0x173540(f32);
extern f32 flvecInnerProduct0x173220(f32*, f32*);
extern f32 flvecCalcDistance0x173140(void*, void*);
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
extern void SubVector0x120860(f32*, f32*, f32*);
extern void AddVector0x120820(f32*, f32*, f32*);
extern void flvecApplyMat330x172e00(f32*, f32*, MATRIX);
extern void flvecCopy0x173300(f32*, f32*);
extern s32 Pl_scope_ck0x154d00(PLAYER_WORK*);
extern s16 act_ck0x14ef20(PLAYER_WORK*, s8, s8);

//rodata
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

//bss
extern CAMERA_WORK CameraWork0x4767c0;

//protos
void cmd_set_pos0x221d30(f32*, POINT_CAM_STATE*, s32*);
void cmd_set_tar0x221e60(f32*, POINT_CAM_STATE*, s32*);
void cmd_copy0x221f90(f32*, s8);
void cmd_cam_move0x2220c0(CAMERA_WORK*, CAM_W_VIEW*, void*);
void cam2view0x2227a0(CAMERA_WORK*);
void cam_sw_set_sub0x222d80(CAMERA_WORK*);
static void default_area_data0x222e20(CAMERA_WORK*);
void StageCamInit0x223000(CAMERA_WORK*);
s32 SetAreaData0x223070(CAMERA_WORK*);
u8 Get_cam_grid_XZ0x223190(u16*, u16*, f32*, CAM_AREA_XZ*);
s32 CameraAreaCheck0x2232a0(CAM_DATA_ENTRY_HEADER*, PLAYER_WORK*, u8);
s32 CamAreaAttribChk0x2233c0(CAM_DATA_ENTRY_HEADER*, PLAYER_WORK*);
s32 Area_XZ_Check0x223410(CAM_GEOMETRY_ZONE*, f32*);
s8 PachiTypeCheck0x221460(PLAYER_WORK*);
s32 pch_lock_chk0x221400(PLAYER_WORK*);
s32 point_camera0x221be0(CAMERA_WORK*, CAM_W_VIEW*);
void quake_sub0x222bc0(QUAKE*);

void CameraWorkInit0x21f3d0(void) {
    flMemset0x16f5f0(CameraWork0x4767c0, 0, sizeof(CameraWork0x4767c0));
}

void Q_camera_init0x21f3f0(void) {
    CameraWork0x4767c0.demo_play = 0;
    CameraWork0x4767c0.wyvern_ptr = 0;
    CameraWork0x4767c0.player_cam_height_level = 2;
}

void CameraInit0x21f410(void) {
    *(u32*)&CameraWork0x4767c0.initialized = 0;
    CameraWork0x4767c0.quake.active = false;
    CameraWork0x4767c0.sub_quake.active = false;
    CameraWork0x4767c0.wyvern_target = 0;
    CameraWork0x4767c0.player_ptr = &player_work0x3e4bf0[game_w0x3f33f0.my_player_number];
    StageCamInit0x223000(&CameraWork0x4767c0);
}

void SetCameraData0x21f470(CAM_DATA_HEADER* data) {
    CAM_DATA_ENTRY_HEADER* entry;
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

        for(count = data->entry_count; count != 0;count--) {
            next_offset = (void*) entry;

            if (entry->bytepairs_ptr != 0) {
                entry->zones_ptr = (CAM_GEOMETRY_ZONE*)(next_offset + entry->zones_offset);
                entry->bytepairs_ptr = (u8*)next_offset + entry->bytepairs_offset;
                entry = (CAM_DATA_ENTRY_HEADER*) ((u32) entry + 0x300 + entry->zone_count  * 0x40) + 1;
            } else {
                entry->zones_ptr = (CAM_GEOMETRY_ZONE*)(next_offset + entry->zones_offset);
                entry = (CAM_DATA_ENTRY_HEADER*) ((u32) entry + 0x300 + entry->zone_count * 0x40);
            }
        }        

        grid = (CAM_GRID_CELL*)((u8*) data + data->cam_grid_offset);
        data->cam_grid_ptr = grid;

        entry_ptrs = (CAM_DATA_ENTRY_HEADER**) ((u8*) data + data->entry_list_offset);
        data->entry_list_ptr = entry_ptrs;

        cell_count = data->x_count * data->y_count;
        total_ptrs = 0;

        for(count = cell_count;count != 0;count--) {
            if (grid->entry_count != 0) {
                grid->entries_ptr = (CAM_DATA_ENTRY_HEADER**)((u8*)data + grid->entries_offset);
                total_ptrs += grid->entry_count;
            }
            grid ++;
        }

        for(count = total_ptrs;count != 0;count--) {
            *entry_ptrs = (CAM_DATA_ENTRY_HEADER*)((u8*)data + (u32)*entry_ptrs);
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
        &cam_work->cam_grid_x, &cam_work->cam_grid_y, player->pos, &cam_work->area_xz
    );
    
    cam_work->has_active_view = 0;
    
    if (cam_work->initialized == 0) {
        cam_work->initialized++;
        cam_work->CamAreaPtr = NULL;
        cam_work->prev_cam_entry_index = -1;
        cam_work->cam_entry_index = -1;

        if (SetAreaData0x223070(cam_work) >= 0) {
            cam_work->cam_entry_index = cam_work->CamAreaPtr->index;
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
            if (cam_work->CamAreaPtr->move_type == NO_MOVE_TYPE) {
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
            cam_work->cam_entry_index = cam_work->CamAreaPtr->index;
            cam_work->has_active_view = 1;
        }
    } else if (CameraAreaCheck0x2232a0(cam_work->CamAreaPtr, player, 2) != 0) {
        cam_work->prev_cam_entry_index = cam_work->cam_entry_index;
        cam_work->has_active_view = 1;

        if (SetAreaData0x223070(cam_work) >= 0) {
            cam_work->cam_entry_index = cam_work->CamAreaPtr->index;
        }
    }
    
    cam_work->prev_has_active_view = cam_work->active_view;
    
    if (cam_work->CamAreaPtr != NULL) {
        switch (cam_work->CamAreaPtr->move_type) {
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
        camera_work->views[0].state.hit_wall = 0;
        camera_work->views[0].state.next_rot = player->angle + 0x2000;
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
                        0.0f
                    );
                    flvecCopy0x173300(view_state->matrix[3], player->pos);
                    cam_view->pitch = view_state->angle_pan;
                    break;
                
                case 2:
                    flmatInit0x171ce0(view_state->matrix);
                    flmatRotXYZ330x1724e0(
                        view_state->matrix,
                        0.0f,
                        DEG2RAD * ((player->angle + 0x8000) & 0xFFFF),
                        0.0f
                    );
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
            cam_view->this_view_active= 1;
    }
}

s32 pch_lock_chk0x221400(PLAYER_WORK* player) {
    switch(player->unk_2DC) {
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

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_init_sub_playerEX0x221580);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_sub_playerEX0x2215a0);

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_plEX_fishing0x221600);

INCLUDE_ASM("asm/main/nonmatchings/camera", fishing_cam_chk0x2216e0);

INCLUDE_ASM("asm/main/nonmatchings/camera", fish_cam_sub0x221700);

INCLUDE_ASM("asm/main/nonmatchings/camera", NPCZoomInCameraRequest0x221820);

void NPCZoomInCameraCancel0x221850(void) {
       *(s16*)((u8*)&CameraWork0x4767c0 + 0x440) = 0;
   }

s32 NPCZoomInCameraCheck0x221860(void) {
    return (u16) CameraWork0x4767c0.views[3].state.rot_something[0] != 0;
}

INCLUDE_ASM("asm/main/nonmatchings/camera", cam_plEX_zoom0x221870);

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

INCLUDE_ASM("asm/main/nonmatchings/camera", point_camera0x221be0);

static MATRIX* get_em_local0x221cf0(POINT_CAM_STATE* ptcam) {
    MONSTER_WORK* mon;
    MATRIX* retval;

    mon = ptcam->point.ent_ptr;
    if ((mon != 0)) {
        if((mon->exists != 0)){
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
    result[0] = 0.00024414062f * opargs[1]; //constant is 1/4096
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
    case 5: //this was needed to generate a jumptable
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

INCLUDE_ASM("asm/main/nonmatchings/camera", cmd_copy0x221f90);

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

//temp rodata padding to keep alignment, move/remove as needed?
const char __pad_cam_0x36B0E8[] = "\0\0\0\0"; //shunts cmd_cam_move jumptable to next 0x10

INCLUDE_ASM("asm/main/nonmatchings/camera", cmd_cam_move0x2220c0);

s32 point_cam_hit0x222400(CAMERA_WORK *a1, CAM_W_VIEW *a2, POINT_CAM_STATE *a3, void *a4) {
    return 0;
}

s32 point_cam_sub0x222410(CAMERA_WORK* cam_w, CAM_W_VIEW* view, POINT_CAM_STATE* arg2) {
    s32 move_amt;
    POINT_CAM_OP* op_ptr; //next unprocessed op
    s32 running; //looping
    s32 retval;
    POINT_CAM_OP* op;
    s32* opdata; //current op

    running = 1;
    arg2->point.halt_logic = 0U;
    op_ptr = arg2->point.logic_pos;
    
    while(true) {
    op = op_ptr;
    opdata = (s32*)op_ptr;
    op_ptr += op->size;
    switch (op->op) {
    case 0:
        arg2->point.simple = op->argb[0];
        break;
    case 1:
        arg2->point.target_type = op->argb[0];
        arg2->point.cam_part = op->argb[1];
        break;
    case 2:
        cmd_set_pos0x221d30(arg2->pos, arg2, opdata);
        break;
    case 3:
        cmd_set_pos0x221d30(arg2->unk_c, arg2, opdata);
        break;
    case 4:
        arg2->point.player_target_type = op->argb[0];
        arg2->point.target_part = op->argb[1];
        break;
    case 5:
        cmd_set_tar0x221e60(arg2->tar, arg2, opdata);
        break;
    case 6:
        cmd_set_tar0x221e60(arg2->unk_24, arg2, opdata);
        break;
    case 7:
        arg2->point.follow_target = op->argb[0];
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
        arg2->point.cam_offset_target = 0.0625f * opdata[1]; //1/16?
        break;
    case 13:
        arg2->point.cam_offset_start = 0.0625f * opdata[1];
        break;
    case 14:
        arg2->yaw_end = DEG2RAD * opdata[1];
        break;
    case 15:
        arg2->yaw_start = DEG2RAD * opdata[1];
        break;
    case 16:
        arg2->pitch_end = DEG2RAD * opdata[1];
        break;
    case 17:
        arg2->pitch_start = DEG2RAD * opdata[1];
        break;
    case 18:
        move_amt = opdata[1];
        view->move_total = move_amt;
        view->move_cur = move_amt;
        break;
    case 19:
        cmd_copy0x221f90(arg2->pos, op->args);
        break;
    case 20:
        arg2->point.logic_loop = op_ptr;
        break;
    case 21:
        view->move_cur = (s16) (view->move_cur - 1);
        if (view->move_total <= 0 || view->move_cur >= 0 ) {
            op_ptr = arg2->point.logic_loop;
            running = 0;
            retval = 0;
        } else {
            flvecCopy0x173300(arg2->pos, view->cam_pos);
            flvecCopy0x173300(arg2->tar, view->target_pos);
            view->target_yaw = view->current_yaw;
            view->target_pitch = view->current_pitch;
            arg2->yaw_end = view->yaw;
            arg2->pitch_end = view->pitch;
            view->move_cur = -1;
            view->move_total = -1;
        }
        break;
    case 22:
        cmd_cam_move0x2220c0(cam_w, view, arg2);
        break;
    case 25:
        if (point_cam_hit0x222400(cam_w, view, arg2, opdata) != 0) {
        default:
            return 1;
        }
        break;
    case 24:
        running = 0;
        retval = -1;
        break;
    }
    
    if (arg2->point.halt_logic != 0) {
        return 1;
    }
    arg2->point.logic_pos = op_ptr;
    if (running == 0) {
        return retval;
    }
        
    }//while end
}

void cam2view0x2227a0(CAMERA_WORK* cam) {
    QUAKE* quake;
    s16 qtime;
    s32 active;
    s32 q;
    CAM_W_VIEW* view;

    quake = &cam->sub_quake;
    for(q = 2; q > 0; q -= 1) {
        if (quake->active != false) {
            qtime = quake->timer - 1;
            quake->timer = qtime;
            if (qtime  <= 0) {
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

void quake_sub0x222bc0(QUAKE* quake) {
    f32 shake_offset;
    f32 intensity;
    
    if (quake->active == 0) {
        return;
    }
    
    shake_offset = 90.0f * ((f32)quake->timer / quake_time_tbl0x338ed0[quake->type & 0x7F]); //timing
    
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
    if (( quake->timer >> 1) & 1) {
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

INCLUDE_ASM("asm/main/nonmatchings/camera", default_area_data0x222e20);

//this match requires default_area_data match as static
INCLUDE_ASM("asm/main/nonmatchings/camera", StageCamInit0x223000);

//void StageCamInit0x223000(CAMERA_WORK* cam) {
//    CAM_DATA_HEADER* dataBuff;
//
//    if (cam->CamDataBuffer == 0) {
//        default_area_data0x222e20(cam);
//    }
//    dataBuff = cam->CamDataBuffer;
//    cam->area_xz.map_area_count_x = dataBuff->x_count;
//    cam->area_xz.map_area_count_z =  dataBuff->y_count;
//    cam->area_xz.map_area_width = dataBuff->area_width;
//    cam->area_xz.map_area_length = dataBuff->area_length;
//    cam->area_xz.map_area_offset_x = dataBuff->base_offset_x;
//    cam->area_xz.map_area_offset_z = dataBuff->base_offset_y;
//    cam->map_area_width_u32 = dataBuff->area_width32;
//    cam->map_area_length_u32 = dataBuff->area_length32;
//}

s32 SetAreaData0x223070(CAMERA_WORK* cam) {
    CAM_DATA_HEADER* data;
    PLAYER_WORK* player;
    CAM_GRID_CELL* grid;
    s32 grid_index;
    CAM_GRID_CELL* cell;
    CAM_DATA_ENTRY_HEADER** cell_entries;
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
    for(;count !=0; count--){
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

s32 CameraAreaCheck0x2232a0(CAM_DATA_ENTRY_HEADER* entry, PLAYER_WORK* player, u8 mask) {
    CAM_GEOMETRY_ZONE* zone;
    s32 zone_count;
    f32 player_dir[3];
    f32 proj;

    if (CamAreaAttribChk0x2233c0(entry, player) == 0) {
        return 2;
    }
    
    zone_count = entry->zone_count;
    zone =  entry->zones_ptr;

    for (;zone_count != 0;zone_count--) {
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

s32 CamAreaAttribChk0x2233c0(CAM_DATA_ENTRY_HEADER* entry, PLAYER_WORK* player) {
    if (entry->attribute & 0x80) {
        if (player->unk_14 || player->unk_15 < 0x27 || player->unk_15 > 0x2B) {
            return 0;
        }
    }
    
    return 1;
}

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

f32 vInnerProductXZ0x223f90(f32* arg0, f32* arg1) {
    f32 x = arg0[0] * arg1[0];
    f32 z = arg0[2] * arg1[2];

    return x + z;
}

f32 vInnerProduct0x223fb0(f32* arg0, f32* arg1) {
    f32 x = arg0[0] * arg1[0];
    f32 y = arg0[1] * arg1[1];
    f32 z = arg0[2] * arg1[2];

    return x + y + z; 
}

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

    power = v4*v4 + v3*v3;
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

//arg0 is a 5-size array of COMPLEX
//arg1 has six floats? a scalar and then five vals?
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

    for (i = 1;i <= 5;i++) {
        scaledproducts[i] = invscale * products[i]; //scale vals
    }
    
    for (i = 2;i <= 5;i++) {
        invscale = flPow0x173670(flAbs0x173540(scaledproducts[i]), dka_j_tbl0x3393D0[i]); //raise values by powers
        if (invscale > scalar) {
            scalar = invscale; //save the largest
        }
    }
    
    scalar *= 5.0f; //multiply by five, new scalar

    for (i = 0;i < 5;i++) {
        out[i].a = scalar * dka_init_tbl0x3393a0[i][0]; //save the table vals to the complex array
        out[i].b = scalar * dka_init_tbl0x3393a0[i][1]; //scaled of course
    }
    
    for (window_left = 25;window_left >= 0;window_left--) {
        inner = 0;
        out_window = out;
        
        for (; inner < 5; inner++) {
            dCnvComplex0x224cb0(&diffprod, 1.0f, 0.0f); //make a complex identity? (not imaginary mask!)
            dCnvComplex0x224cb0(&totalprod, 1.0f, 0.0f); //and another!
            
            tempout = *out_window;
            
            innest = 0;
            in_scale = &scaledproducts[0];
            in_window = out;
            
            for (;innest < 5;innest++) {
                dMulComplex0x224cf0(&totalprod, &totalprod, &tempout); //total kept in &90
                
                totalprod.a += in_scale[1];
                
                if (innest != inner) {
                    dSubComplex0x224cc0(&difference, &tempout, in_window); //difference
                    dMulComplex0x224cf0(&diffprod, &diffprod, &difference); //keep it in &98
                }
                
                in_scale++;
                in_window++;
            }
            dDivComplex0x224d40(&ratio, &totalprod, &diffprod); //ratio of total product over difference product
            dSubComplex0x224cc0(out_window, &tempout, &ratio); //subtract ratio from table, save it out
            
            out_window++;
        }
    }
}


INCLUDE_ASM("asm/main/nonmatchings/camera", Cardano0x225050);

INCLUDE_ASM("asm/main/nonmatchings/camera", k_HitWallCamera0x225370);

INCLUDE_ASM("asm/main/nonmatchings/camera", k_HitEmCamera0x225510);

INCLUDE_ASM("asm/main/nonmatchings/camera", QuestClearCameraRequest0x225d80);

void DemoCameraRequest0x221b80(s32 , void*);

void RedDragonEscapeCamera0x225e90(void* target_ptr) {
    DemoCameraRequest0x221b80(0x1C, target_ptr);
}


void DemoCameraRequest0x221b80(s32, void*);

typedef struct {
    /* 0x000 */ u8 unk_0[0x388];
    /* 0x388 */ u8 unk_388;
} UNK_STRUCT; // size: unk

void F_DragonEscapeCamera0x225ea0(UNK_STRUCT* arg0) {
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
