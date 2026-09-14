#include "common.h"
#include "main/flfnt.h"

extern void * memset0x19dd28(void *, int, size_t);

s32 flfntMakeHandle0x216cf0(void);
void flfntCacheFlush0x216640(void);

extern FLFONT* np0x38a340;

void flfntCreate0x216490(FLFONT* arg0) {
    np0x38a340 = arg0;
    memset0x19dd28(arg0, 0, sizeof(FLFONT));
    np0x38a340->pal_cache_ptr = arg0->pal_cache[0];
    np0x38a340->font_file_ptr = arg0->font_bin;
    np0x38a340->processed_caches[0] = arg0->process_cache_0;
    np0x38a340->processed_caches[1] = arg0->process_cache_1;
    np0x38a340->processed_caches[2] = arg0->process_cache_2;
    np0x38a340->processed_caches[3] = arg0->process_cache_3;
    np0x38a340->processed_caches[4] = arg0->process_cache_4;
    np0x38a340->all_string_buffer_ptr = arg0->all_strings_buffer;
    np0x38a340->char_width = 0x16;
    np0x38a340->char_height = 0x16;
    np0x38a340->font_tex_handle = flfntMakeHandle0x216cf0();
}

u32 flfntGetSystemMemorySize0x216570(void) {
    return sizeof(FLFONT);
};

void flfntStackReset0x216580(void) {
    np0x38a340->processed_lengths[0] = 0;
    np0x38a340->processed_lengths[1] = 0;
    np0x38a340->processed_lengths[2] = 0;
    np0x38a340->processed_lengths[3] = 0;
    np0x38a340->processed_lengths[4] = 0;
    np0x38a340->pos_x = 0;
    np0x38a340->pos_y = 0;
    np0x38a340->pos_z = 10.0f;
    np0x38a340->width = (u8) np0x38a340->char_width;
    np0x38a340->height = (u8) np0x38a340->char_height;
    np0x38a340->pal_num = 0;
    np0x38a340->all_string_buffer_len = 0;
    np0x38a340->half_type = 1;
    np0x38a340->unique_chars_total = np0x38a340->chars_expanded_total;
}

void flfntInit0x216610(void) {
    flfntStackReset0x216580();
    flfntCacheFlush0x216640();
}

void flfntCacheFlush0x216640(void) {
    s32 i;
    
    for(i = 0; i < 0x1E80; i += 8){
        np0x38a340->SJIS_cache_map[i] = 0xFF;
        np0x38a340->SJIS_cache_map[i+1] = 0xFF;
        np0x38a340->SJIS_cache_map[i+2] = 0xFF;
        np0x38a340->SJIS_cache_map[i+3] = 0xFF;
        np0x38a340->SJIS_cache_map[i+4] = 0xFF;
        np0x38a340->SJIS_cache_map[i+5] = 0xFF;
        np0x38a340->SJIS_cache_map[i+6] = 0xFF;
        np0x38a340->SJIS_cache_map[i+7] = 0xFF;
    }
    np0x38a340->SJIS_cached_total = 0;
    np0x38a340->chars_expanded_total = 0;
    np0x38a340->unique_chars_total = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetPalData0x2166e0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetSize0x216890);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntLocate0x2168b0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetZ0x2168d0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetPalette0x2168e0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSetHalftype0x216910);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntPrintf0x216920);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDraw0x216ac0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDrawAll0x216bd0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntMakeHandle0x216cf0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntFontPuts0x216de0);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntFontPutc0x216f90);

void flfntPaletteTrans0x217480(void) {
    return;
}

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDrawStart0x217490);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntDrawTerm0x217550);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSjis2Index0x217620);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flfntSjis2Jis0x217680);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecReloadTexture0x217760);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecExpandFont0x217a60);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecCheckString0x217c10);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecCheckFont0x217d70);

INCLUDE_ASM("asm/nonmatchings/main/flfnt", flnecAscii2Sjis0x217de0);
