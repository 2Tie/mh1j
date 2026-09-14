#ifndef FLFNT_H
#define FLFNT_H

#include "types.h"
#include "common.h"

typedef struct {
  /* 0x0 */ u16 x;
  /* 0x2 */ u16 y;
  /* 0x4 */ f32 z;
  /* 0x8 */ u8  width;
  /* 0x9 */ u8  height;
  /* 0xa */ u16 pal;
  /* 0xc */ u8* strbuf;
} FLFONT_SUB; // size: 0x10

typedef struct {
  /* 0x00000 */ u32 font_tex_handle;
  /* 0x00004 */ u32 char_width;
  /* 0x00008 */ u32 char_height;
  /* 0x0000C */ void* font_file_ptr;
  /* 0x00010 */ u16 pos_x;
  /* 0x00012 */ u16 pos_y;
  /* 0x00014 */ f32 pos_z;
  /* 0x00018 */ u16 px_width;
  /* 0x0001A */ u16 px_height;
  /* 0x0001C */ u8 width;
  /* 0x0001D */ u8 height;
  /* 0x0001E */ u16 pal_num;
  /* 0x00020 */ void* pal_cache_ptr;
  /* 0x00024 */ u32 processed_lengths[5];
  /* 0x00038 */ FLFONT_SUB* processed_caches[5];
  /* 0x0004C */ s32 all_string_buffer_len;
  /* 0x00050 */ u8* all_string_buffer_ptr;
  /* 0x00054 */ u32 half_type;
  /* 0x00058 */ s32 unk_58;
  /* 0x0005C */ u32 chars_expanded_total;
  /* 0x00060 */ u32 unique_chars_total;
  /* 0x00064 */ u16 expanded_chars_list[363];
  /* 0x0033A */ u16 SJIS_cache_map[7809];
  /* 0x0403C */ u32 SJIS_cached_total;
  /* 0x04040 */ s32 tex_handles[3];
  /* 0x0404C */ s32 pal_handles[0x20];
  /* 0x040CC */ void* sysalloc_start;
  /* 0x040D0 */ void* sysalloc_end;
  /* 0x040D4 */ s32 term_len;
  /* 0x040D8 */ u32 last_tex_and_pal;
  /* 0x040DC */ u32 was_last_sheet_full;
  /* 0x040E0 */ u8  pad_40e0[0x20];
  /* 0x04100 */ u8 pal_cache[0x20][0x40];
  /* 0x04900 */ u8 font_bin[780800];
  /* 0xC3300 */ FLFONT_SUB process_cache_0[0x80];
  /* 0xC3B00 */ FLFONT_SUB process_cache_1[0x80];
  /* 0xC4300 */ FLFONT_SUB process_cache_2[0x80];
  /* 0xC4B00 */ FLFONT_SUB process_cache_3[0x80];
  /* 0xC5300 */ FLFONT_SUB process_cache_4[0x80];
  /* 0xC5B00 */ u8 all_strings_buffer[0x8000];
  /* 0xcdb00 */ u8 pad_end[0x2500];
} FLFONT; // size: 0xD0000

#endif
