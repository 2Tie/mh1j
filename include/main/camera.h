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
    bool active;
    u8 type;
    u16 timer;
} QUAKE;

typedef struct{
  u8 unk_0;
  u8 unk_1;
  u16 entry_count;
  u16 x_count;
  u16 y_count;
  u16 unk_8;
  u16 unk_a;
  u32 unk_c;
  u32 unk_10;
  u32 unk_14;
  u32 unk_18;
  void* end_header;
  void* entry_ptr_list;
  void* eof;
  void* first_entry_ptr;
  f32 unk_2c;
  u32 first_entry_offset;
}CAM_DATA_HEADER;

typedef struct{
  u8 unk_0;
  u8 index;
  u8 move_type; //CAM_DATA_ENTRY_MOVE_TYPE
  u8 axes; //CAM_DATA_ENTRY_AXES
  u8 target_type; //CAM_DATA_ENTRY_TARGET_TYPE
  u8 float_chunk_count;
  u8 attribute;
  u8 unk_7;
  f32 min_distance;
  f32 max_distance;
  f32 near_zoom;
  f32 far_zoom;
  void* float_chunks_ptr;
  void* bytepairs_ptr;
}CAM_DATA_ENTRY_HEADER;

typedef struct{
    u8 todo[0x71];
    u8 this_view_active; //0x71
    u8 which_view; //0x72
    u8 todo2[0x85];
    u16 next_rot; //0xF8
    u8 todo3[0x5];
    u8 hit_wall; //0xFF
}CAM_W_VIEW;

typedef struct{
  f32 pos[3];
  f32 target[3];
  u8 unk1[0x48];//0x18 - 0x5f
  f32 roll;
  u8 unk2[0x4]; //0x64 - 0x67
  f32 unk3;
  u8 unk4[0x14]; //0x6c - 0c7f
  CAM_W_VIEW views[5];
  u32 initialized;
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
  u8 unk5[7];
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
