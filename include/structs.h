#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"
#include "common.h"

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3; // Size: 0x0C

typedef struct {
    /* 0x00 */ u16 current_state;
    /* 0x02 */ u16 previous_state;
    /* 0x04 */ u16 just_pressed;
    /* 0x06 */ u16 just_released;
    /* 0x08 */ u16 current_sticks;
    /* 0x0A */ u16 last_sticks;
    /* 0x0C */ u16 just_pressed_dir;
    /* 0x0E */ u16 just_released_dir;
    /* 0x10 */ u16 left_stick_angle;
    /* 0x12 */ u16 right_stick_angle;
    /* 0x14 */ u16 left_stick_power;
    /* 0x16 */ u16 right_stick_power;
    /* 0x18 */ u16 held_state;
    /* 0x1A */ u16 held_length;
    /* 0x1C */ u16 connected;
    /* 0x1E */ u16 prior_connected;
    /* 0x20 */ u16 unk;
} PSW; // Size: 0x22

typedef struct {
    /* 0x00 */ u8* memoryblock;
    /* 0x04 */ u8* baseandcap[2];
    /* 0x0C */ u8* frame[2];
    /* 0x14 */ s32 align;
} FL_FMS; // Size: 0x18

typedef struct {
    /* 0x00 */ u8* pFrame;
    /* 0x04 */ s32 heapnum;
} FMS_FRAME; // Size: 0x8

typedef struct {
    /* 0x00 */ u8 areaID;
    /* 0x01 */ u8 flag;
    /* 0x02 */ u8 demoID;
    /* 0x03 */ u8 targetSpecies;
    /* 0x04 */ u8 bgm;
    /* 0x05 */ u8 sfx;
    /* 0x06 */ u8 tutFlag1;
    /* 0x07 */ u8 tutFlag2;
    /* 0x08 */ s32 (*check)(void* demo);
    /* 0x0C */ s32 (*event)(void* demo);
} EVENT_DEMO_DATA; // Size: 0x10

typedef struct {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 state;
    /* 0x02 */ s16 timer;
    /* 0x04 */ s32 (*check)(void* demo);
    /* 0x08 */ s32 (*event)(void* demo);
    /* 0x0C */ EVENT_DEMO_DATA* demo_data;
} ACTIVE_EVENT_DEMO; // Size: 0x10

typedef struct {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 which;
    /* 0x02 */ u8 pad1;
    /* 0x03 */ u8 pad2;
    /* 0x04 */ ACTIVE_EVENT_DEMO demos[2];
} EVENT_DEMO; // Size: 0x24

typedef struct {
    bool is_stereo;
    u8 BGM_vol;
    u8 SFX_vol;
    bool vibrate;
    u8 targeting_type;
    u8 screen_xoff;
    u8 screen_yoff;
    u8 unk_7;
    u8 unk_8;
    u8 unk_9;
    u8 unk_A;
    u8 unk_B;
    u8 unk_C;
    u8 unk_D;
    u8 unk_E;
    u8 unk_F;
} OPTIONS_WORK;

typedef struct {
    f32 pos[3];
    f32 target[3];
    f32 pitch;
    f32 yaw;
    f32 roll;
    f32 proj_near;
    f32 proj_far;
    f32 view_angle;
    f32 view_angle_OLD;
    f32 view_roll;
    u32 unk_38;
    u32 unk_3C;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    f32 unk_4C;
} VIEW_WORK;

typedef struct {
    /* 0x00 */ f32 diff_r;
    /* 0x04 */ f32 diff_g;
    /* 0x08 */ f32 diff_b;
} RGB; // Size:0x0C

typedef struct {
    s32 v1;
    f32 v2;
    f32 v3;
    f32 v4;
    f32 v5;
    void (*trans)();
    s32 v7;
    s32 v8;
} prim;

typedef struct {
    u8 state; // offset 0x0, size 0x1
    u8 unk01;
    u8 unk02;
    u8 unk03;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0a;
    u32 unk0c;
} FADE_WORK;

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ u8 b1;
    /* 0x09 */ u8 b2;
    /* 0x0A */ u8 b3;
    /* 0x0B */ u8 b4;
} STAGE_FOG; // Size: 0x0C

typedef struct {
    /* 0x00 */ u16 item;
    /* 0x02 */ u16 quantity;
} ITEM_SLOT; // Size:0x04

typedef enum {
    INIT,
    VIOLENCE,
    CRI,
    ACCESS,
    CAPCOM,
    OPENING,
    TITLE
} DEMO_SCREEN;

typedef struct {
    // total size: 0x44
    DEMO_SCREEN screen; // offset 0x0
    u8 state;           // offset 0x1
    u8 playing;         // offset 0x2
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u16 timer; // offset 0xa
    u8 unk_0c;
    u8 unk_0d;
    u8 unk_0e;
    u8 unk_0f;
    u8 initting; // offset 0x10
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1a;
    u8 unk_1b;
    u8 unk_1c;
    u8 unk_1d;
    u8 unk_1e;
    u8 unk_1f;
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
    u8 unk_28;
    u8 unk_29;
    u8 unk_2a;
    u8 unk_2b;
    u8 unk_2c;
    u8 unk_2d;
    u8 unk_2e;
    u8 unk_2f;
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u8 unk_35;
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 unk_39;
    u8 unk_3a;
    u8 unk_3b;
    u8 unk_3c;
    u8 unk_3d;
    u8 unk_3e;
    u8 unk_3f;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
} DEMO_WORK;

typedef struct {
    /* 0x00 */ u8 unk_0[0x40];
    /* 0x40 */ MATRIX matrix;
} PART_WORK; // size: 0x80

typedef struct {
    /* 0x000 */ u8 unk_0[0x2];
    /* 0x002 */ u8 unk_2;
    /* 0x003 */ u8 unk_3[0x9];
    /* 0x00C */ u16 player_num;
    /* 0x00E */ u8 unk_E[0x6];
    /* 0x014 */ u8 unk_14;
    /* 0x015 */ u8 unk_15;
    /* 0x016 */ u8 unk_16[0x4A];
    /* 0x060 */ MATRIX matrix;
    /* 0x0A0 */ u8 unk_A0[0x4];
    /* 0x0A4 */ s32 angle;
    /* 0x0A8 */ u8 unk_A8[0x4];
    /* 0x0AC */ f32 pos[3];
    /* 0x0B8 */ u8 unk_B8[0x58];
    /* 0x110 */ PART_WORK* part_ptrs[32];
    /* 0x190 */ u8 unk_190[0x14C];
    /* 0x2DC */ u16 unk_2DC;
    /* 0x2DE */ u8 unk_2DE[0x485];
    /* 0x763 */ u8 sight_timer;
    /* 0x764 */ u8 unk_764;
    /* 0x765 */ u8 unk_765[0x113];
    /* 0x878 */ void* unk_878_ptr;
    /* 0x87C */ u8 unk_87C[0x4A];
    /* 0x8C6 */ u8 ojiisan_timer;
    /* 0x8C7 */ u8 unk_8C7[0x27];
    /* 0x8EE */ s16 unk_8EE;
    /* 0x8F0 */ u8 unk_8F0[0x110];
} PLAYER_WORK; // size: 0xA00

typedef struct {
    /* 0x000 */ u8 exists;
    /* 0x001 */ u8 unk_1;
    /* 0x002 */ u8 species;
    /* 0x003 */ u8 unk_3[0x5D];
    /* 0x060 */ MATRIX matrix;
    /* 0x0A0 */ u8 unk_a0[0xC];
    /* 0x0AC */ f32 pos[3];
    /* 0x0B8 */ u8 unk_0B8[0x2D0];
    /* 0x388 */ u8 unk_388; // read in F_DragonEscapeCamera
    /* 0x389 */ u8 unk_389[0x687];
} MONSTER_WORK; // size: 0xa10?

typedef struct {
    // total size:0x224
    u8 top_state;      // offset 0x0
    u8 sub_state;      // offset 0x1
    u8 game_top_state; // offset 0x2
    u8 game_sub_state; // offset 0x3
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u16 unk_0a;
    u8 unk_0c;
    u8 unk_0d;
    u8 unk_0e;
    u8 unk_0f;
    u8 BGM_flags; // offset 0x10
    u8 BGM;       // offset 0x11
    u8 unk_12;
    u8 unk_13;
    u8 current_area_id; // offset 0x14
    u8 area_model;      // offset 0x15
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1a;
    u8 unk_1b;
    u8 unk_1c;
    u8 unk_1d;
    u16 tick_count; // offset 0x1e
    u8 pad_0_ack;   // offset 0x20
    u8 pad_1_ack;   // offset 0x21
    u8 unk_22;
    u8 unk_23;
    u8 unk_24;
    u8 current_music;      // offset 0x25
    s16 music_timer;       // offset 0x26
    u8 load_monsters[4];   // offset 0x28
    u16 selected_quest_id; // offset 0x2c
    u8 fight_music_index;  // offset 0x2e
    u8 camp_area_id;       // offset 0x2f
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u8 unk_35;
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 unk_39;
    u8 unk_3a;
    u8 unk_3b;
    u8 unk_3c;
    u8 unk_3d;
    u8 unk_3e;
    u8 unk_3f;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 unk_48;
    u8 unk_49;
    u8 unk_4a;
    u8 unk_4b;
    u8 unk_4c;
    u8 unk_4d;
    u8 unk_4e;
    u8 unk_4f;
    u8 unk_50;
    u8 unk_51;
    u8 unk_52;
    u8 unk_53;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u8 unk_58;
    u8 unk_59;
    u8 unk_5a;
    u8 unk_5b;
    u8 unk_5c;
    u8 unk_5d;
    u8 unk_5e;
    u8 unk_5f;
    u8 unk_60;
    u8 unk_61;
    u8 unk_62;
    u8 unk_63;
    u8 unk_64;
    u8 unk_65;
    u8 unk_66;
    u8 unk_67;
    u8 unk_68;
    u8 unk_69;
    u8 unk_6a;
    u8 unk_6b;
    u8 unk_6c;
    u8 unk_6d;
    u8 unk_6e;
    u8 unk_6f;
    u8 unk_70;
    u8 unk_71;
    u8 unk_72;
    u8 unk_73;
    u8 unk_74;
    u8 unk_75;
    u8 unk_76;
    u8 unk_77;
    u8 unk_78;
    u8 unk_79;
    u8 unk_7a;
    u8 unk_7b;
    u8 unk_7c;
    u8 unk_7d;
    u8 unk_7e;
    u8 unk_7f;
    u8 player_items[4]; // offset 0x80
    u8 unk_84;
    u8 unk_85;
    u8 unk_86;
    u8 unk_87;
    u32 mdl_ptrs[4];       // offset 0x88
    u16 mdl_status[4];     // offset 0x98
    u16 mdl_starts[4];     // offset 0xa0
    u32 sub_mdl_ptrs[4];   // offset 0xa8
    u16 sub_mdl_status[4]; // offset 0xb8
    u16 sub_mdl_starts[4]; // offset 0xc0
    u8 unk_c8;
    u8 unk_c9;
    u8 unk_ca;
    u8 unk_cb;
    u16 stolen_item_id;       // offset 0xcc
    u16 stolen_item_quantity; // offset 0xce
    u8 stolen_item_flag;      // offset 0xd0
    u8 my_player_number;      // offset 0xd1
    u8 address_id;            // offset 0xd2
    u8 number_of_players;     // offset 0xd3
    u8 hit_id;                // offset 0xd4
    u8 mission_state;         // offset 0xd5
    u8 unk_d6;
    u8 unk_d7;
    u8 unk_d8;
    u8 unk_d9;
    u8 unk_da;
    u8 unk_db;
    u8 unk_dc;
    u8 unk_dd;
    u8 unk_de;
    u8 unk_df;
    u8 unk_e0;
    u8 unk_e1;
    u8 unk_e2;
    u8 unk_e3;
    u8 unk_e4;
    u8 unk_e5;
    u8 unk_e6;
    u8 unk_e7;
    u8 unk_e8;
    u8 unk_e9;
    u8 unk_ea;
    u8 unk_eb;
    u8 unk_ec;
    u8 unk_ed;
    u8 unk_ee;
    u8 unk_ef;
    u8 unk_f0;
    u8 unk_f1;
    u8 unk_f2;
    u8 unk_f3;
    u8 unk_f4;
    u8 unk_f5;
    u8 unk_f6;
    u8 unk_f7;
    u8 unk_f8;
    u8 unk_f9;
    u8 unk_fa;
    u8 unk_fb;
    u8 unk_fc;
    u8 unk_fd;
    u8 unk_fe;
    u8 unk_ff;
    u8 unk_100;
    u8 unk_101;
    u8 unk_102;
    u8 unk_103;
    u8 unk_104;
    u8 unk_105;
    u8 unk_106;
    u8 unk_107;
    u8 unk_108;
    u8 unk_109;
    u8 unk_10a;
    u8 unk_10b;
    u8 unk_10c;
    u8 unk_10d;
    u8 unk_10e;
    u8 unk_10f;
    u8 unk_110;
    u8 unk_111;
    u8 unk_112;
    u8 unk_113;
    u8 unk_114;
    u8 unk_115;
    u8 unk_116;
    u8 unk_117;
    u8 unk_118;
    u8 unk_119;
    u8 unk_11a;
    u8 unk_11b;
    u8 unk_11c;
    u8 unk_11d;
    u8 unk_11e;
    u8 unk_11f;
    u8 unk_120;
    u8 unk_121;
    u8 unk_122;
    u8 unk_123;
    u8 unk_124;
    u8 unk_125;
    u8 unk_126;
    u8 unk_127;
    ITEM_SLOT quest_item_box[32];      // offset 0x128
    u32 quest_item_box_taken_flags[2]; // offset 0x1a8
    u8 unk_1b0;
    u8 unk_1b1;
    u8 unk_1b2;
    u8 unk_1b3;
    u8 unk_1b4;
    u8 unk_1b5;
    u8 unk_1b6;
    u8 unk_1b7;
    u8 unk_1b8;
    u8 unk_1b9;
    u8 unk_1ba;
    u8 unk_1bb;
    u8 unk_1bc;
    u8 unk_1bd;
    u8 unk_1be;
    u8 unk_1bf;
    u8 unk_1c0;
    u8 unk_1c1;
    u8 unk_1c2;
    u8 unk_1c3;
    u8 unk_1c4;
    u8 unk_1c5;
    u8 unk_1c6;
    u8 unk_1c7;
    u8 unk_1c8;
    u8 unk_1c9;
    u8 unk_1ca;
    u8 unk_1cb;
    u8 unk_1cc;
    u8 unk_1cd;
    u8 unk_1ce;
    u8 unk_1cf;
    u8 unk_1d0;
    u8 unk_1d1;
    u8 unk_1d2;
    u8 unk_1d3;
    u8 unk_1d4;
    u8 unk_1d5;
    u8 unk_1d6;
    u8 unk_1d7;
    u8 unk_1d8;
    u8 unk_1d9;
    u8 unk_1da;
    u8 unk_1db;
    u8 unk_1dc;
    u8 unk_1dd;
    u8 unk_1de;
    u8 unk_1df;
    u16 current_sound_effect; // offset 0x1e0
    u8 unk_1e2;
    u8 unk_1e3;
    u8 unk_1e4;
    u8 unk_1e5;
    u8 unk_1e6;
    u8 in_tutorial;      // offset 0x1e7
    char user_id_1[8];   // offset 0x1e8
    char user_id_2[8];   // offset 0x1f0
    char user_id_3[8];   // offset 0x1f8
    char user_id_4[8];   // offset 0x200
    u8 hunter_1_present; // offset 0x208
    u8 hunter_2_present; // offset 0x209
    u8 hunter_3_present; // offset 0x20a
    u8 hunter_4_present; // offset 0x20b
    u8 unk_20c;
    u8 unk_20d;
    u8 unk_20e;
    u8 unk_20f;
    u8 number_bombs_placed; // offset 0x210
    u8 number_meats_placed; // offset 0x211
    u8 number_traps_placed; // offset 0x212
    u8 unk_213;
    u8 unk_214;
    u8 unk_215;
    u8 unk_216;
    u8 unk_217;
    u16 fatalis_health; // offset 0x218
    u8 unk_21a;
    u8 unk_21b;
    u8 unk_21c;
    u8 fort_damage; // offset 0x21d
    u8 unk_21e;
    bool demo_playing;
    u8 unk_220;
    u8 unk_221;
    u8 unk_222;
    u8 unk_223;
} GAME_WORK;

typedef struct {
    // total size: 0x64
    u8 unk_00;          // offset 0x0, size 0x1
    u8 unk_01;          // offset 0x1, size 0x1
    u8 current_area_id; // offset 0x2, size 0x1
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    Vec3 origin;
    Vec3 unk_1C;
    Vec3 offset;
    u16 unk_34;
    u8 unk_36;
    u8 unk_37;
    u16 modelwork_index;
    u8 unk_3A;
    u8 unk_3B;
    u8* modelwork_pointer;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8* area_origins;
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 unk_50;
    u8 unk_51;
    u8 unk_52;
    u8 unk_53;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u8 unk_58;
    u8 unk_59;
    u8 unk_5A;
    u8 unk_5B;
    u8 unk_5C;
    u8 unk_5D;
    u8 unk_5E;
    u8 unk_5F;
    u8 unk_60;
    u8 unk_61;
    u8 unk_62;
    u8 unk_63;
    u8 unk_64;
} STAGE_WORK;

typedef struct {
    // total size: 0x80
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0a;
    u8 unk_0b;
    u8 unk_0c;
    u8 unk_0d;
    u8 unk_0e;
    u8 unk_0f;
    u8 online; // offset 0x10, size 0x1
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 is_stereo; // offset 0x17, size 0x1
    u8 unk_18;
    u8 unk_19;
    u8 game_region; // offset 0x1a, size 0x1
    u8 unk_1b;
    u8 unk_1c;
    u8 unk_1d;
    u8 unk_1e;
    u8 unk_1f;
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
    u8 unk_28;
    u8 unk_29;
    u8 unk_2a;
    u8 unk_2b;
    u8 unk_2c;
    u8 unk_2d;
    u8 filter_mode;     // offset 0x2e, size 0x1
    u8 view_projection; // offset 0x2f, size 0x1
    u8 ope_mode;        // offset 0x30, size 0x1
    u8 aspect_ratio;    // offset 0x31, size 0x1
    u8 unk_32;
    u8 unk_33;
    u8 in_aq_session; // offset 0x34, size 0x1
    u8 busy_loading;  // offset 0x35, size 0x1
    u8 bgm_volume;    // offset 0x36, size 0x1
    u8 se_volume;     // offset 0x37, size 0x1
    u8 unk_38;
    u8 unk_39;
    u8 unk_3a;
    u8 unk_3b;
    u8 mc_access; // offset 0x3c, size 0x1
    u8 unk_3d;
    u8 unk_3e;
    u8 unk_3f;
    s16 aq_load_timeout; // offset 0x40, size 0x2
    u8 unk_42;
    u8 unk_43;
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 unk_48;
    u8 unk_49;
    u8 unk_4a;
    u8 unk_4b;
    u8 unk_4c;
    u8 unk_4d;
    u8 unk_4e;
    u8 unk_4f;
    u8 unk_50;
    u8 unk_51;
    u8 unk_52;
    u8 unk_53;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u8 unk_58;
    u8 unk_59;
    u8 unk_5a;
    u8 unk_5b;
    u8 unk_5c;
    u8 unk_5d;
    u8 unk_5e;
    u8 unk_5f;
    u8 unk_60;
    u8 unk_61;
    u8 unk_62;
    u8 unk_63;
    u8 unk_64;
    u8 unk_65;
    u8 unk_66;
    u8 unk_67;
    u8 unk_68;
    u8 unk_69;
    u8 unk_6a;
    u8 unk_6b;
    u8 unk_6c;
    u8 unk_6d;
    u8 unk_6e;
    u8 unk_6f;
    u8 unk_70;
    u8 unk_71;
    u8 unk_72;
    u8 unk_73;
    u8 unk_74;
    u8 unk_75;
    u8 unk_76;
    u8 unk_77;
    u8 unk_78;
    u8 unk_79;
    u8 unk_7a;
    u8 unk_7b;
    u8 unk_7c;
    u8 unk_7d;
    u8 unk_7e;
    u8 unk_7f;
} SYSTEM_WORK;

typedef struct {
    // total size: 0x84
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0a;
    u8 unk_0b;
    u8 unk_0c;
    u8 unk_0d;
    u8 unk_0e;
    u8 unk_0f;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1a;
    u8 unk_1b;
    u8 unk_1c;
    u8 unk_1d;
    u8 unk_1e;
    u8 unk_1f;
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23;
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
    u8 unk_28;
    u8 unk_29;
    u8 unk_2a;
    u8 unk_2b;
    s32 unk_2c;
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    s32 unk_34;
    s32 unk_38;
    u16 unk_3c;
    u16 unk_3e;
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 unk_48;
    u8 unk_49;
    u8 unk_4a;
    u8 unk_4b;
    u8 unk_4c;
    u8 unk_4d;
    u8 unk_4e;
    u8 unk_4f;
    u8 unk_50;
    u8 unk_51;
    u8 unk_52;
    u8 unk_53;
    u8 unk_54;
    u8 unk_55;
    u8 unk_56;
    u8 unk_57;
    u8 unk_58;
    u8 unk_59;
    u8 unk_5a;
    u8 unk_5b;
    u8 unk_5c;
    u8 unk_5d;
    u8 unk_5e;
    u8 unk_5f;
    u8 unk_60;
    u8 unk_61;
    u8 unk_62;
    u8 unk_63;
    u8 unk_64;
    u8 unk_65;
    u8 unk_66;
    u8 unk_67;
    u8 unk_68;
    u8 unk_69;
    u8 unk_6a;
    u8 unk_6b;
    u8 unk_6c;
    u8 unk_6d;
    u8 unk_6e;
    u8 unk_6f;
    u8 unk_70;
    u8 unk_71;
    u8 unk_72;
    u8 unk_73;
    u8 unk_74;
    u8 unk_75;
    u8 unk_76;
    u8 unk_77;
    u8 unk_78;
    u8 unk_79;
    u8 unk_7a;
    u8 unk_7b;
    u8 unk_7c;
    u8 unk_7d;
    u8 unk_7e;
    u8 unk_7f;
    u8 unk_80;
    u8 unk_81;
    u8 unk_82;
    u8 unk_83;
} CARD_WORK;

typedef struct {
    /* 0x00 */ u32 attack_bonus;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 speed_variance;
    /* 0x0C */ f32 horizontal_deviation;
    /* 0x10 */ f32 vertical_deviation;
    /* 0x14 */ f32 pellet_scale;
} GUN_GROW_UP; // size: 0x18

typedef struct {
    /* 0x00 */ u8 model;
    /* 0x01 */ u8 rarity;
    /* 0x02 */ u8 level;
    /* 0x03 */ u8 reload_delay;
    /* 0x04 */ u32 price;
    /* 0x08 */ u16 attack;
    /* 0x0A */ u8 defense;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ char* name;
    /* 0x10 */ u32 ammo_types;
} GUN_DATA; // size: 0x14

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 can_use;
    /* 0x02 */ u8 rarity;
    /* 0x03 */ u8 max_stack;
    /* 0x04 */ u8 flags;
    /* 0x05 */ u8 icon_index;
    /* 0x06 */ u8 color_index;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u16 ammo_type;
    /* 0x0A */ u16 sound_effect;
    /* 0x0C */ u16 buy_price;
    /* 0x0E */ u16 sell_sprice;
} ITEM_DATA; // size: 0x10

typedef struct {
    /* 0x00 */ s16 parent_bone;
    /* 0x02 */ s16 is_capsule;
    /* 0x04 */ s16 meat_zone;
    /* 0x06 */ s16 body_group;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 radius;
    /* 0x10 */ f32 point1[3];
    /* 0x1C */ f32 point2[3];
} HITCAPSULE_DATA; // size: 0x28

typedef struct {
    /* 0x00 */ u8 model;
    /* 0x01 */ u8 rarity;
    /* 0x02 */ u8 sharp_curve;
    /* 0x03 */ u8 sharp_max;
    /* 0x04 */ u32 price;
    /* 0x08 */ u16 raw_attack;
    /* 0x0A */ u8 defense;
    /* 0x0B */ u8 fire;
    /* 0x0C */ u8 water;
    /* 0x0D */ u8 thunder;
    /* 0x0E */ u8 dragon;
    /* 0x0F */ u8 poison;
    /* 0x10 */ u8 paralysis;
    /* 0x11 */ u8 sleep;
    /* 0x12 */ u16 sort_order;
    /* 0x14 */ char* name;
} KEN_DATA; // size: 0x18

typedef struct {
    /* 0x00 */ s16 initial_tolerance;
    /* 0x02 */ s16 recover_time;
    /* 0x04 */ s16 recover_amount;
    /* 0x06 */ s16 damage_amount;
    /* 0x08 */ s16 duration;
    /* 0x0A */ s16 damage_time;
    /* 0x0C */ s16 tolerance_increase;
} POISON_EFFICACY; // Size:0x0E

#endif
