#include "types.h"

typedef struct {
    u32 unk0;
	u32 palette_offset;
	u32 unk1;
    u16 bpp;
	u16 width;
	u16 height;
	u16 mip_count;
	u16 palette_bpp;
	u16 palette_num;
	u8  pad[8];
	u8 data[1];
} ApxHeader;

typedef struct {
	u32 flags;
	s32 width;
	s32 height;
	u32 byte_per_row;
	u32 unk2;
	s32 pixel_format;
	u32 red_bits;
	u32 red_offset;
	u32 red_mask;
	u32 green_bits;
	u32 green_offset;
	u32 green_mask;
	u32 blue_bits;
	u32 blue_offset;
	u32 blue_mask;
	u32 alpha_bits;
	u32 alpha_offset;
	u32 alpha_mask;
} ApxContext; // size = 0x48

typedef struct {
	ApxContext contexts[];
} ApxCtxs;
