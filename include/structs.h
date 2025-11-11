#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

typedef struct {
    //total size: 0xC
    f32 x; //offset 0x0, size 0x4
    f32 y; //offset 0x4, size 0x4
    f32 z; //offset 0x8, size 0x4
} Vec3;

typedef struct {
    //total size: 0x64
    u8 unk_00; //offset 0x0, size 0x1
    u8 unk_01; //offset 0x1, size 0x1
    u8 current_area_id; //offset 0x2, size 0x1
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
} STAGE_WORK;

typedef struct {
    //total size: 0x18
    u32 attack_bonus; //offset 0x0, size 0x4
    f32 speed; //offset 0x4, size 0x4
    f32 speed_variance; //offset 0x8, size 0x4
    f32 horizontal_deviation; //offset 0xC, size 0x4
    f32 vertical_deviation;   //offset 0x10, size 0x4
    f32 pellet_scale;         //offset 0x14, size 0x4
} GUN_GROW_UP;

typedef struct {
    //total size: 0x14
    u8 model; //offset 0x0, size 0x1
    u8 rarity; //offset 0x1, size 0x1
    u8 level; //offset 0x2, size 0x1
    u8 reload_delay; //offset 0x3, size 0x1
    u32 price; //offset 0x4, size 0x4
    u16 attack; //offset 0x8, size 0x2
    u8 defense; //offset 0xA, size 0x1
    u8 unk1; //offset 0xB, size 0x1
    char* name; //offset 0xC, size 0x4
    u32 ammo_types; //offset 0x10, size 0x14
} GUN_DATA;

typedef struct {
    //total size: 0x10
    u8 type; //offset 0x0, size 0x1
    u8 can_use; //offset 0x1, size 0x1
    u8 rarity;  //offset 0x2, size 0x1
    u8 max_stack; //offset 0x3, size 0x1
    u8 flags;     //offset 0x4, size 0x1
    u8 icon_index; //offset 0x5, size 0x1
    u8 color_index;//offset 0x6, size 0x1
    u8 unk1; //offset 0x7, size 0x1
    u16 ammo_type; //offset 0x8, size 0x2
    u16 sound_effect; //offset 0xA, size 0x2
    u16 buy_price; //offset 0xC, size 0x2
    u16 sell_sprice; //offset 0xE, size 0x2
} ITEM_DATA;

typedef struct {
    //total size: 0x28
    s16 parent_bone; //offset 0x0, size 0x2
    s16 is_capsule;  //offset 0x2, size 0x2
    s16 meat_zone;   //offset 0x4, size 0x2
    s16 body_group;  //offset 0x6, size 0x2
    s32 unk;         //offset 0x8, size 0x4
    f32 radius;      //offset 0xC, size 0x4
    Vec3 point1;     //offset 0x10, size 0xC
    Vec3 point2;     //offset 0x1C, size 0xC
} HITCAPSULE_DATA;

typedef struct {
    //total size: 0x14
    u8 model; //offset 0x0, size 0x1
    u8 rarity; //offset 0x1, size 0x1
    u16 sharpness; //offset 0x2, size 0x2
    u32 price;     //offset 0x4, size 0x4
    u16 raw_attack;//offset 0x8, size 0x2
    u8 defense;    //offset 0xA, size 0x1
    u8 fire;       //offset 0xB, size 0x1
    u8 water;      //offset 0xC, size 0x1
    u8 thunder;    //offset 0xD, size 0x1
    u8 dragon;     //offset 0xE, size 0x1
    u8 poison;     //offset 0xF, size 0x1
    u8 paralysis;  //offset 0x10, size 0x1
    u8 sleep;      //offset 0x11, size 0x1
    u16 sort_order;//offset 0x12, size 0x2
    char* name;    //offset 0x14, size 0x4
} KEN_DATA;

typedef struct {
    //total size: 0xE
    s16 initial_tolerance; //offset 0x0, size 0x2
    s16 recover_time;      //offset 0x2, size 0x2
    s16 recover_amount;    //offset 0x4, size 0x2
    s16 damage_amount;     //offset 0x6, size 0x2
    s16 duration;          //offset 0x8, size 0x2
    s16 damage_time;       //offset 0xA, size 0x2
    s16 tolerance_increase;//offset 0xC, size 0x2
} POISON_EFFICACY;

#endif
