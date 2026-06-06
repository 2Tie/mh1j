#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

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
    f32 pos[3];
    u8 active;
    u8 type;
    s16 timer;
} QUAKE;

typedef struct {
    /* 0x00 */ u8 vertices[0x20];
    /* 0x20 */ f32 origin[3];
    /* 0x2C */ u8 flags;
    /* 0x2D */ u8 padding[3];
    /* 0x30 */ f32 axis_normal[3];
    /* 0x3C */ f32 max_extent;
} CAM_GEOMETRY_ZONE; // size: 0x40

typedef struct{
  u8 unk_0;
  u8 index;
  u8 move_type; //CAM_DATA_ENTRY_MOVE_TYPE
  u8 axes; //CAM_DATA_ENTRY_AXES
  u8 target_type; //CAM_DATA_ENTRY_TARGET_TYPE
  u8 zone_count;
  u8 attribute;
  u8 unk_7;
  f32 min_distance;
  f32 max_distance;
  f32 near_zoom;
  f32 far_zoom;
  union { u32 zones_offset; CAM_GEOMETRY_ZONE* zones_ptr;};
  union { u32 bytepairs_offset; void* bytepairs_ptr;};
}CAM_DATA_ENTRY_HEADER;

typedef struct {
    /* 0x00 */ s32 entry_count;
    /* 0x04 */  union {u32 entries_offset; CAM_DATA_ENTRY_HEADER** entries_ptr;};
} CAM_GRID_CELL; // Size: 0x08

typedef struct{
  u8 unk_0;
  u8 unk_1;
  u16 entry_count;
  u16 x_count;
  u16 y_count;
  u16 area_width;
  u16 area_length;
  u32 unk_c;
  u32 unk_10;
  u32 area_width32;
  u32 area_length32;
  union { u32 cam_grid_offset; CAM_GRID_CELL* cam_grid_ptr;};
  union { u32 entry_list_offset; CAM_DATA_ENTRY_HEADER** entry_list_ptr;};
  void* eof;
  union { u32 first_entry_offset; CAM_DATA_ENTRY_HEADER* first_entry_ptr;};
  f32 unk_2c;
  CAM_DATA_ENTRY_HEADER entries[];
}CAM_DATA_HEADER;

typedef struct{
    /* 0x00 */ u8 unk_0[0x70];
    /* 0x70 */ u8 which_sub;
    /* 0x71 */ u8 this_view_active;
    /* 0x72 */ u8 which_view;
    /* 0x73 */ u8 unk_73[0x5];
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ u8 unk_7C[0x64];
    /* 0xE0 */ s32 unk_E0;         // used in function DemoCameraCancel
    /* 0xE4 */ u8 unk_E4[0x14];
    /* 0xF8 */ u16 next_rot;
    /* 0xFA */ u8 unk_FA[0x5];
    /* 0xFF */ u8 hit_wall;
}CAM_W_VIEW;

typedef struct{
  f32 pos[3];
  f32 target[3];
  u8 unk_18[0x48];//0x18 - 0x5f
  f32 roll;
  u8 unk_64[0x4]; //0x64 - 0x67
  f32 unk_68;
  u8 unk_6C[0x14]; //0x6c - 0c7f
  CAM_W_VIEW views[5];
  u8 initialized;
  u8 padding[0x3];
  PLAYER_WORK* player_ptr;
  CAM_DATA_HEADER* CamDataBuffer;
  CAM_DATA_ENTRY_HEADER* CamAreaPtr;
  u16 map_area_count_x;
  u16 map_area_count_y;
  u16 map_area_width;
  u16 map_area_length;
  u32 unk_header_1;
  u32 unk_header_2;
  u32 map_area_width_u32;
  u32 map_area_length_u32;
  u16 cam_grid_x;
  u16 cam_grid_y;
  f32 rail_scale;
  f32 rail_zoom;
  u8 rail_spline;
  u8 unk_5B5[7];
  QUAKE sub_quake;
  QUAKE quake;
  u8 cam_grid_returnval;
  u8 cam_entry_index;
  u8 prev_cam_entry_index;
  u8 has_active_view;
  u8 prev_has_active_view;
  u8 active_view;
  u16 pad_state;
  u16 pad_new;
  u16 pad_sticks;
  u16 pad_right_stick_angle;
  u16 pad_right_stick_power;
  void* wyvern_target;
  void* wyvern_ptr;
  u8 demo_play;
  u8 unk_5F5;
  u8 player_cam_height_level;
  u8 unk_5F7;
} CAMERA_WORK;

#endif
