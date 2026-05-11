#ifndef CAMERA_H
#define CAMERA_H

#include "types.h"

typedef enum {
  Y,
  XZ
} CAM_DATA_ENTRY_AXES;

typedef enum {
  NONE,
  PAN,
  RAIL,
  PAN_WITH_PLAYER
}CAM_DATA_ENTRY_MOVE_TYPE;

typedef enum {
  NONE,
  PLAYER_UNK,
  PLAYER
}CAM_DATA_ENTRY_TARGET_TYPE;

typedef struct{
  u8 unk_0;
  u8 unk_1;
  u8 entry_count;
  u8 unk_3;
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
  CAM_DATA_ENTRY_MOVE_TYPE* move_type;
  CAM_DATA_ENTRY_AXES* axes;
  CAM_DATA_ENTRY_TARGET_TYPE* target_type;
  u8 float_chunk_count;
  u8 attribute;
  u8 unk_7;
  f32 unk_8;
  f32 unk_c;
  f32 unk_10;
  f32 unk_14;
  void* float_chunks_ptr;
  void* bytepairs_ptr;
}CAM_DATA_ENTRY_HEADER;

typedef struct{
  f32 pos[3];
  f32 target[3];
  u8 unk1[0x48];//0x18 - 0x5f
  f32 roll;
  u8 unk2[0x4]; //0x64 - 0x67
  f32 unk3;
  u8 unk4[0x14]; //0x6c - 0c7f
  u8 views[5][0x100];
  u32 initialized;
  void* player_ptr; //TODO PLAYER_WORK*
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
  f32 sub_quake_x;
  f32 sub_quake_y;
  f32 sub_quake_z;
  u8 quakingsub;
  u8 sub_quake_type;
  u16 sub_quake_timer;
  f32 quake_x;
  f32 quake_y;
  f32 quake_z;
  u8 quaking;
  u8 quake_type;
  u16 quake_timer;
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
