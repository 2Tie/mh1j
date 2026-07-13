#include "types.h"

// https://github.com/GReinoso96/XXModding/wiki/Texture-Formats-(PS2)

// Header of texture in apx format, these are within texlist files (*_tex.bin)
typedef struct {
    u32 file_size; // 0x0
	u32 palette_offset; // 0x4
	u32 total_colors_x4; // 0x8 // according to yuzu, havent seen it used
    u16 bpp; // 0xc // 32 (rgba), 24 (rgb), 16 (rgba5551), 8(indexed8), 4(indexed4)
	u16 width; // 0xe
	u16 height; // 0x10
	u16 mip_count; // 0x12
	u16 palette_bpp; // 0x14
	u16 palette_num; // 0x16
	u8  pad[8]; // 0x18
	u8  data[]; // 0x20 // first pixel data, then palette data
} ApxHeader; // size = 0x20

// The context set from the palettes and images
typedef struct {
	u32 flags; // 0x0
	s32 width; // 0x4
	s32 height; // 0x8
	u32 byte_per_row; // 0xc
	u32 unk2; // 0x10
	s32 pixel_format; // 0x14
	u32 red_bits; // 0x18
	u32 red_offset; // 0x1c
	u32 red_mask; // 0x20
	u32 green_bits; // 0x24
	u32 green_offset; // 0x28
	u32 green_mask; // 0x2c
	u32 blue_bits; // 0x30
	u32 blue_offset; // 0x34
	u32 blue_mask; // 0x38
	u32 alpha_bits; // 0x3c
	u32 alpha_offset; // 0x40
	u32 alpha_mask; // 0x44
} ApxContext; // size = 0x48
