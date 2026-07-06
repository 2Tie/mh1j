#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"
#include "common.h"

typedef enum {
  Y,
  XZ
} CAM_DATA_ENTRY_AXES;

typedef enum {
  NO_MOVE_TYPE,
  PAN,
  RAIL,
  PAN_WITH_PLAYER
}CAM_DATA_ENTRY_MOVE_TYPE;

typedef enum {
  NO_TARGET,
  PLAYER_UNK,
  PLAYER
}CAM_DATA_ENTRY_TARGET_TYPE;

typedef struct {
    /* 0x00 */ f32 a;
    /* 0x04 */ f32 b;
} COMPLEX; // size: 0x08

typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ u8 active;
    /* 0x0D */ u8 type;
    /* 0x0E */ s16 timer;
} QUAKE; // size: 0x10

typedef struct {
    /* 0x00 */ u8 vertices[0x20];
    /* 0x20 */ f32 origin[3];
    /* 0x2C */ u8 flags;
    /* 0x2D */ u8 padding[3];
    /* 0x30 */ f32 axis_normal[3];
    /* 0x3C */ f32 max_extent;
} CAM_GEOMETRY_ZONE; // size: 0x40

typedef struct{
    /* 0x00 */ u8 unk_0;
    /* 0x01 */ u8 index;
    /* 0x02 */ CAM_DATA_ENTRY_MOVE_TYPE move_type;
    /* 0x03 */ CAM_DATA_ENTRY_AXES axes;
    /* 0x04 */ CAM_DATA_ENTRY_TARGET_TYPE target_type;
    /* 0x05 */ u8 zone_count;
    /* 0x06 */ u8 attribute;
    /* 0x07 */ u8 unk_7;
    /* 0x08 */ f32 min_distance;
    /* 0x0C */ f32 max_distance;
    /* 0x10 */ f32 near_zoom;
    /* 0x14 */ f32 far_zoom;
    /* 0x18 */ union { u32 zones_offset; CAM_GEOMETRY_ZONE* zones_ptr;};
    /* 0x1C */ union { u32 bytepairs_offset; void* bytepairs_ptr;};
}CAM_DATA_ENTRY_HEADER; // size: 0x20

typedef struct {
    /* 0x00 */ s32 entry_count;
    /* 0x04 */ union {u32 entries_offset; CAM_DATA_ENTRY_HEADER** entries_ptr;};
} CAM_GRID_CELL; // size: 0x08

typedef struct{
    /* 0x00 */ u8 unk_0;
    /* 0x01 */ u8 unk_1;
    /* 0x02 */ u16 entry_count;
    /* 0x04 */ u16 x_count;
    /* 0x06 */ u16 y_count;
    /* 0x08 */ u16 area_width;
    /* 0x0A */ u16 area_length;
    /* 0x0C */ u32 base_offset_x;
    /* 0x10 */ u32 base_offset_y;
    /* 0x14 */ u32 area_width32;
    /* 0x18 */ u32 area_length32;
    /* 0x1C */ union { u32 cam_grid_offset; CAM_GRID_CELL* cam_grid_ptr;};
    /* 0x20 */ union { u32 entry_list_offset; CAM_DATA_ENTRY_HEADER** entry_list_ptr;};
    /* 0x24 */ void* eof;
    /* 0x28 */ union { u32 first_entry_offset; CAM_DATA_ENTRY_HEADER* first_entry_ptr;};
    /* 0x2C */ f32 unk_2c;
    /* 0x30 */ CAM_DATA_ENTRY_HEADER entries[];
}CAM_DATA_HEADER; // size: 0x30 plus entries

typedef struct {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ u8 unk_C[0x4];
    /* 0x10 */ f32 height;
    /* 0x14 */ u8 unk_14[0xC];
} CAM_HEIGHT_ENTRY; // size: 0x20

typedef struct {
    /* 0x00 */ f32 min_distance;
    /* 0x04 */ f32 max_distance;
    /* 0x08 */ u8 unk_8[0x18];
    /* 0x20 */ CAM_HEIGHT_ENTRY entries[];
} CAM_CNF; // size: 0x24 

typedef struct {
    /* 0x00 */ f32 cam_pos[3];
    /* 0x0C */ f32 target_pos[3];
    /* 0x18 */ f32 prev_cam_pos[3];
    /* 0x24 */ f32 ground_y;
    /* 0x28 */ s8 ground_hit;
    /* 0x29 */ u8 unk_29[0x07];
    /* 0x30 */ union { s16 rot_something[6]; f32 prev_target_a[3];};
    /* 0x3C */ f32 prev_target_b[3];
    /* 0x48 */ f32 min_dist_save;
    /* 0x4C */ union { s32 angle_min ; f32 min_dist_prev; s8 flags[4];};
    /* 0x50 */ union { s32 angle_max ; f32 max_dist_save;};
    /* 0x54 */ union { s32 angle_delta ; f32 max_dist_prev;};
    /* 0x58 */ union { f32 angle_cur; CAM_CNF* cfg_entry;};
    /* 0x5C */ union { f32 angle_something; CAM_HEIGHT_ENTRY* cfg_height;};
    /* 0x60 */ u8 unk_60[0x8];
    /* 0x68 */ s16 next_rot;
    /* 0x6A */ u8 unk_6A[0x4];
    /* 0x6E */ u8 unk_6E;
    /* 0x6F */ u8 hit_wall;
} CAM_VIEW_STATE; // size: 0x70

typedef struct {
    /* 0x00 */ u8 unk_0[0x4E];
    /* 0x4E */ u8 demo_id;
    /* 0x4F */ s8 demo_status;
    /* 0x50 */ void* target_ptr;
    /* 0x54 */ u8 unk_54[0x1C];
} CAM_VIEW_STATE_DEMO; // size: 0x70

typedef struct {
    /* 0x00 */ MATRIX matrix;
    /* 0x40 */ f32 pos[3];
    /* 0x4C */ f32 angle_min;
    /* 0x50 */ f32 angle_max;
    /* 0x54 */ f32 angle_delta;
    /* 0x58 */ f32 angle_cur;
    /* 0x5C */ f32 angle_pan;
    /* 0x60 */ s16 unk_60;
    /* 0x62 */ s8 pachi_type;
    /* 0x63 */ u8 unk_63;  
    /* 0x64 */ u8 unk_64;
    /* 0x65 */ u8 unk_65[0x3];
    /* 0x68 */ s16 next_rot;
    /* 0x6A */ u8 unk_6A[0x4];
    /* 0x6E */ u8 unk_6E;
    /* 0x6F */ u8 hit_wall;
} CAM_VIEW_STATE_PACHINGER; // size: 0x70

typedef struct {
    /* 0x00 */ s8 op;
    /* 0x01 */ s8 size;
    /* 0x02 */ union {s8 argb[2]; s16 args;};
} POINT_CAM_OP; // size: 0x04

typedef struct {
    /* 0x00 */ POINT_CAM_OP* logic_pos;
    /* 0x04 */ POINT_CAM_OP* logic_loop;
    /* 0x08 */ u8 simple;
    /* 0x09 */ u8 target_type;
    /* 0x0A */ u8 player_target_type;
    /* 0x0B */ u8 cam_part;
    /* 0x0C */ u8 target_part;
    /* 0x0D */ u8 follow_target;
    /* 0x0E */ u8 unk_e[2];
    /* 0x10 */ MONSTER_WORK* ent_ptr;
    /* 0x14 */ f32 cam_offset_target;
    /* 0x18 */ f32 cam_offset_start;
    /* 0x1C */ u8 halt_logic;
} POINT_CAM_POINT; //size: 0x30

typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 unk_c[3];
    /* 0x18 */ f32 tar[3];
    /* 0x24 */ f32 unk_24[3];
    /* 0x30 */ f32 yaw_end;
    /* 0x34 */ f32 yaw_start;
    /* 0x38 */ f32 pitch_end;
    /* 0x3C */ f32 pitch_start;
    /* 0x40 */ POINT_CAM_POINT point;
} POINT_CAM_STATE; //size: 0x70

typedef struct {
    /* 0x00 */ f32 cam_offset[3];
    /* 0x0C */ f32 target_offset[3];
    /* 0x18 */ u8 padding[0x8];
} FISH_CAM_OFFSET; // size: 0x20

typedef struct {
    /* 0x00 */ u8 unk_0[0x14];
    /* 0x14 */ u16 unk_14;
} FISHING_DATA;

typedef struct {
    /* 0x00 */ union {u8 active; s32 active_s32;}; // Had to use int to match cam_init_sub_playerEX
    /* 0x04 */ s32 is_fishing;
    /* 0x08 */ FISHING_DATA* data;
} CAM_FISHING_CONTROL; // size: 0xC

typedef struct {
    /* 0x00 */ u8 unk_0[0x2];
    /* 0x02 */ u8 unk_2;
    /* 0x03 */ u8 unk_6[0xA9];
    /* 0xAC */ f32 unk_AC[3];
} UNK_ZOOM_STRUCT; // size: unk

typedef struct {
    /* 0x00 */ union {u8 state; s32 state_s32;}; // Had to use int to match cam_init_sub_playerEX
    /* 0x04 */ UNK_ZOOM_STRUCT* unk_4;
    /* 0x08 */ f32 unk_8[3];
    /* 0x14 */ f32 unk_14[3];
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ s16 unk_22;
} CAM_ZOOM_CONTROL; // size: 0x24

typedef struct {
    /* 0x00 */ u8 unk_0[0x4];
    /* 0x04 */ CAM_FISHING_CONTROL fishing_control;
    /* 0x10 */ CAM_ZOOM_CONTROL zoom_control;
    /* 0x34 */ u8 unk_34[0x3C];
} CAM_VIEW_STATE_PLAYER; // size: 0x70

typedef struct {
    /* 0x00 */ f32 cam_pos[3];
    /* 0x0C */ f32 target_pos[3];
    /* 0x18 */ f32 prev_cam_pos[3];
    /* 0x24 */ u8  unk_24[0x3C];
    /* 0x60 */ f32 yaw;
    /* 0x64 */ f32 roll;
    /* 0x68 */ f32 pitch;
    /* 0x6C */ u8 unk_6C[0x4];
    /* 0x70 */ u8 which_sub;
    /* 0x71 */ u8 this_view_active;
    /* 0x72 */ u8 which_view;
    /* 0x73 */ u8  unk_73;
    /* 0x74 */ s16 move_cur;
    /* 0x76 */ s16 move_total;
    /* 0x78 */ union {s32 unk_78_s32; u8 unk_78_u8;};
    /* 0x7C */ union {s32 unk_7C; u8 cmd_status;};
    /* 0x80 */ s16 target_yaw;
    /* 0x82 */ s16 target_pitch;
    /* 0x84 */ s16 current_yaw;
    /* 0x86 */ s16 current_pitch;
    /* 0x88 */ s16 unk_88;
    /* 0x8A */ u8  unk_8A[0x6];
    /* 0x90 */ union { 
                    CAM_VIEW_STATE state;
                    CAM_VIEW_STATE_DEMO state_demo;
                    CAM_VIEW_STATE_PACHINGER state_pchngr;
                    CAM_VIEW_STATE_PLAYER state_player;
                    POINT_CAM_STATE state_point;
                };
} CAM_W_VIEW; // size: 0x100

typedef struct{
    /* 0x590 */ u16 map_area_count_x;
    /* 0x592 */ u16 map_area_count_z;
    /* 0x594 */ u16 map_area_width;
    /* 0x596 */ u16 map_area_length;
    /* 0x598 */ u32 map_area_offset_x;
    /* 0x59C */ u32 map_area_offset_z;
} CAM_AREA_XZ; //size: 0x10

typedef struct{
    /* 0x000 */ f32 pos[3];
    /* 0x00C */ f32 target[3];
    /* 0x018 */ u8 unk_18[0x48];//0x18 - 0x5f
    /* 0x060 */ f32 roll;
    /* 0x064 */ f32 yaw;
    /* 0x068 */ f32 pitch;
    /* 0x06C */ u8 unk_6C[0x14]; //0x6c - 0c7f
    /* 0x080 */ CAM_W_VIEW views[5];
    /* 0x580 */ u8 initialized;
                u8 padding[0x3];
    /* 0x584 */ PLAYER_WORK* player_ptr;
    /* 0x588 */ CAM_DATA_HEADER* CamDataBuffer;
    /* 0x58C */ CAM_DATA_ENTRY_HEADER* CamAreaPtr;
    /* 0x590 */ CAM_AREA_XZ area_xz;
    /* 0x5A0 */ u32 map_area_width_u32;
    /* 0x5A4 */ u32 map_area_length_u32;
    /* 0x5A8 */ u16 cam_grid_x;
    /* 0x5AA */ u16 cam_grid_y;
    /* 0x5AC */ f32 rail_scale;
    /* 0x5B0 */ f32 rail_zoom;
    /* 0x5B4 */ u8 rail_spline;
    /* 0x5B5 */ u8 unk_5B5[7];
    /* 0x5BC */ QUAKE sub_quake;
    /* 0x5CC */ QUAKE quake;
    /* 0x5DC */ u8 cam_grid_returnval;
    /* 0x5DD */ u8 cam_entry_index;
    /* 0x5DE */ u8 prev_cam_entry_index;
    /* 0x5DF */ u8 has_active_view;
    /* 0x5E0 */ u8 prev_has_active_view;
    /* 0x5E1 */ u8 active_view;
    /* 0x5E2 */ u16 pad_state;
    /* 0x5E4 */ u16 pad_new;
    /* 0x5E6 */ u16 pad_sticks;
    /* 0x5E8 */ u16 pad_right_stick_angle;
    /* 0x5EA */ u16 pad_right_stick_power;
    /* 0x5EC */ void* wyvern_target;
    /* 0x5F0 */ void* wyvern_ptr;
    /* 0x5F4 */ u8 demo_play;
    /* 0x5F5 */ u8 unk_5F5;
    /* 0x5F6 */ u8 player_cam_height_level;
    /* 0x5F7 */ u8 unk_5F7;
} CAMERA_WORK; // size: 0x5F8

#endif
