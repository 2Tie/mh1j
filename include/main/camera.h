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
    /* 0x0C */ u32 unk_c;
    /* 0x10 */ u32 unk_10;
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
    /* 0x00 */ u8 unk_0[0x68];
    /* 0x68 */ s16 next_rot;
    /* 0x6A */ u8 unk_6A[0x5];
    /* 0x6F */ u8 hit_wall;
} CAM_VIEW_STATE; // size: 0x70

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
    /* 0x65 */ u8 unk_65[0x9];
    /* 0x6E */ u8 unk_6E;
    /* 0x6F */ u8 unk_6F;
} CAM_VIEW_STATE_PACHINGER; // size: 0x70

typedef struct {
    /* 0x00 */ f32 cam_pos[3];
    /* 0x0C */ f32 target_pos[3];
    /* 0x18 */ f32 prev_cam_pos[3];
    /* 0x24 */ u8  unk_24[0x3C];
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ u8 unk_64[0x4];
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ u8 unk_6C[0x4];
    /* 0x70 */ u8 which_sub;
    /* 0x71 */ u8 this_view_active;
    /* 0x72 */ u8 which_view;
    /* 0x73 */ u8  unk_73[0x5];
    /* 0x78 */ union {s32 unk_78_s32; u8 unk_78_u8;};
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ u8 unk_80[0x8];
    /* 0x88 */ s16 unk_88;
    /* 0x8A */ u8  unk_8A[0x6];
    /* 0x90 */ union { CAM_VIEW_STATE state; CAM_VIEW_STATE_PACHINGER state_pchngr; };
} CAM_W_VIEW; // size: 0x100

typedef struct{
    /* 0x000 */ f32 pos[3];
    /* 0x00C */ f32 target[3];
    /* 0x018 */ u8 unk_18[0x48];//0x18 - 0x5f
    /* 0x060 */ f32 roll;
    /* 0x064 */ u8 unk_64[0x4]; //0x64 - 0x67
    /* 0x068 */ f32 unk_68;
    /* 0x06C */ u8 unk_6C[0x14]; //0x6c - 0c7f
    /* 0x080 */ CAM_W_VIEW views[5];
    /* 0x580 */ u8 initialized;
                u8 padding[0x3];
    /* 0x584 */ PLAYER_WORK* player_ptr;
    /* 0x588 */ CAM_DATA_HEADER* CamDataBuffer;
    /* 0x58C */ CAM_DATA_ENTRY_HEADER* CamAreaPtr;
    /* 0x590 */ u16 map_area_count_x;
    /* 0x592 */ u16 map_area_count_y;
    /* 0x594 */ u16 map_area_width;
    /* 0x596 */ u16 map_area_length;
    /* 0x598 */ u32 unk_header_1;
    /* 0x59C */ u32 unk_header_2;
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
