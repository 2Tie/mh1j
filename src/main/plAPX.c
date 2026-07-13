#include "types.h"
#include "main/plAPX.h"

s32 plAPXGetMipmapTextureNum0x217e50(void* buf);
s32 plGetAPXPalleteNum0x217e70(void* buf);
s32 plAPXSetContextFromImage0x217e90(ApxContext* ctx_arr, void * buf);
s32 plAPXSetPaletteContextFromImage0x218130(ApxContext* ctx_arr, void* buf);
u8* plAPXGetPixelAddressFromImage0x218330(void *buf, s32 mip_index);
u8* plAPXGetPaletteAddressFromImage0x218340(void *buf, s32 mip_index);
static ApxHeader * GetAPXFileHeader0x218350(void* buf);
static u8 * GetAPXPixelMipmapAdrs0x218360(void* buf, s32 index);
static u8 * GetAPXPaletteAdrs0x2184a0(void* buf, s32 index);

s32 plAPXGetMipmapTextureNum0x217e50(void* buf) {
    return (s32)GetAPXFileHeader0x218350(buf)->mip_count;
}

s32 plAPXGetPaletteNum0x217e70(void* buf) {
    return (s32)GetAPXFileHeader0x218350(buf)->palette_num;
}

//INCLUDE_ASM("asm/main/nonmatchings/plAPX", plAPXSetContextFromImage0x217e90);
s32 plAPXSetContextFromImage0x217e90(ApxContext *ctx_arr,void *buf) {
    ApxHeader *apx;
	s32 width;
    s32 height;
	s32 i;
	s32 num;
    bool val;

	num = plAPXGetMipmapTextureNum0x217e50(buf);
	apx = GetAPXFileHeader0x218350(buf);

    width = apx->width;
    height = apx->height;
    i = 0;
	if (0 < num) {
		do {
            ctx_arr->flags = 0;
            ctx_arr->width = width;
        	ctx_arr->height = height;
            switch (apx->bpp) {
                case 4:
    				ctx_arr->flags = ctx_arr->flags | 0x14;
    				ctx_arr->pixel_format = 0;
    				ctx_arr->byte_per_row =  ctx_arr->width >> 1;
    				ctx_arr->red_offset = 0;
    				ctx_arr->red_bits = 0;
    				ctx_arr->red_mask = 0;
    				ctx_arr->green_offset = 0;
    				ctx_arr->green_bits = 0;
    				ctx_arr->green_mask = 0;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_bits = 0;
    				ctx_arr->blue_mask = 0;
    				ctx_arr->alpha_offset = 0;
    				ctx_arr->alpha_bits = 0;
    				ctx_arr->alpha_mask = 0;
                    break;
                case 8:
    				ctx_arr->flags = ctx_arr->flags | 4;
    				ctx_arr->pixel_format = 1;
    				ctx_arr->byte_per_row = ctx_arr->pixel_format * ctx_arr->width;
    				ctx_arr->red_offset = 0;
    				ctx_arr->red_bits = 0;
    				ctx_arr->red_mask = 0;
    				ctx_arr->green_offset = 0;
    				ctx_arr->green_bits = 0;
    				ctx_arr->green_mask = 0;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_bits = 0;
    				ctx_arr->blue_mask = 0;
    				ctx_arr->alpha_offset = 0;
    				ctx_arr->alpha_bits = 0;
    				ctx_arr->alpha_mask = 0;
                    break;
                case 0x10:
    				ctx_arr->pixel_format = 2;
    				ctx_arr->byte_per_row = ctx_arr->pixel_format * ctx_arr->width;
    				ctx_arr->red_bits = 5;
    				ctx_arr->red_offset = 10;
    				ctx_arr->red_mask = 0x1f;
    				ctx_arr->green_bits = 5;
    				ctx_arr->green_offset = 5;
    				ctx_arr->green_mask = 0x1f;
    				ctx_arr->blue_bits = 5;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_mask = 0x1f;
    				ctx_arr->alpha_bits = 1;
    				ctx_arr->alpha_offset = 0xf;
    				ctx_arr->alpha_mask = 1;
    				ctx_arr->red_offset = 0;
    				ctx_arr->blue_offset = 10;
                    break;
                case 0x18:
    				ctx_arr->pixel_format = 3;
    				ctx_arr->byte_per_row = ctx_arr->pixel_format * ctx_arr->width;
    				ctx_arr->red_bits = 8;
    				ctx_arr->red_offset = 0x10;
    				ctx_arr->red_mask = 0xff;
    				ctx_arr->green_bits = 8;
    				ctx_arr->green_offset = 8;
    				ctx_arr->green_mask = 0xff;
    				ctx_arr->blue_bits = 8;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_mask = 0xff;
    				ctx_arr->alpha_bits = 0;
    				ctx_arr->alpha_offset = 0;
    				ctx_arr->alpha_mask = 0;
    				ctx_arr->red_offset = 0;
    				ctx_arr->blue_offset = 0x10;
                    break;
                case 0x20:
    				ctx_arr->pixel_format = 4;
    				ctx_arr->byte_per_row = ctx_arr->pixel_format * ctx_arr->width;
    				ctx_arr->red_bits = 8;
    				ctx_arr->red_offset = 0x10;
    				ctx_arr->red_mask = 0xff;
    				ctx_arr->green_bits = 8;
    				ctx_arr->green_offset = 8;
    				ctx_arr->green_mask = 0xff;
    				ctx_arr->blue_bits = 8;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_mask = 0xff;
    				ctx_arr->alpha_bits = 8;
    				ctx_arr->alpha_offset = 0x18;
    				ctx_arr->alpha_mask = 0xff;
    				ctx_arr->red_offset = 0;
    				ctx_arr->blue_offset = 0x10;
                    break;
            }

			i++;
			ctx_arr += 1;
            width = width >> 1;
			height = height >> 1;
		} while (i < num);
	}
	return 1;
}


//INCLUDE_ASM("asm/main/nonmatchings/plAPX", plAPXSetPaletteContextFromImage0x218130);
s32 plAPXSetPaletteContextFromImage0x218130(ApxContext *ctx_arr, void *buf) {
	ApxHeader *apx;
	s32 num;
	s32 i;

	num = plAPXGetPaletteNum0x217e70(buf);
	apx = GetAPXFileHeader0x218350(buf);
	
	if (0 < num) {
        i = 0;
		do {
            ctx_arr->flags = 0;
            switch (apx->palette_bpp) {
                case 0x10:
    				ctx_arr->pixel_format = 2;
    				ctx_arr->red_bits = 5;
    				ctx_arr->red_offset = 10;
    				ctx_arr->red_mask = 0x1f;
    				ctx_arr->green_bits = 5;
    				ctx_arr->green_offset = 5;
    				ctx_arr->green_mask = 0x1f;
    				ctx_arr->blue_bits = 5;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_mask = 0x1f;
    				ctx_arr->alpha_bits = 1;
    				ctx_arr->alpha_offset = 0xf;
    				ctx_arr->alpha_mask = 1;
    				ctx_arr->red_offset = 0;
    				ctx_arr->blue_offset = 10;
                    break;
                case 0x18:
    				ctx_arr->pixel_format = 3;
    				ctx_arr->red_bits = 8;
    				ctx_arr->red_offset = 0x10;
    				ctx_arr->red_mask = 0xff;
    				ctx_arr->green_bits = 8;
    				ctx_arr->green_offset = 8;
    				ctx_arr->green_mask = 0xff;
    				ctx_arr->blue_bits = 8;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_mask = 0xff;
    				ctx_arr->alpha_bits = 0;
    				ctx_arr->alpha_offset = 0;
    				ctx_arr->alpha_mask = 0;
    				ctx_arr->red_offset = 0;
    				ctx_arr->blue_offset = 0x10;
                    break;
                case 0x20:
    				ctx_arr->pixel_format = 4;
    				ctx_arr->red_bits = 8;
    				ctx_arr->red_offset = 0x10;
    				ctx_arr->red_mask = 0xff;
    				ctx_arr->green_bits = 8;
    				ctx_arr->green_offset = 8;
    				ctx_arr->green_mask = 0xff;
    				ctx_arr->blue_bits = 8;
    				ctx_arr->blue_offset = 0;
    				ctx_arr->blue_mask = 0xff;
    				ctx_arr->alpha_bits = 8;
    				ctx_arr->alpha_offset = 0x18;
    				ctx_arr->alpha_mask = 0xff;
    				ctx_arr->red_offset = 0;
    				ctx_arr->blue_offset = 0x10;
                    break;
                default:
                    return 0;
            }

            switch (apx->bpp) {
                case 4:
                    ctx_arr->width = 0x10;
                    ctx_arr->height = 1;
                    break;
                case 8:
                    ctx_arr->width = 0x100;
                    ctx_arr->height = 1;
                    break;
                default:
                    return 0;
            }


			i++;
			ctx_arr->byte_per_row = ctx_arr->pixel_format * ctx_arr->width;
			ctx_arr += 1;
		} while (i < num);
	}
	return 1;
}

u8* plAPXGetPixelAddressFromImage0x218330(void *buf, s32 mip_index){
	return GetAPXPixelMipmapAdrs0x218360(buf, mip_index);
}

u8* plAPXGetPaletteAddressFromImage0x218340(void *buf, s32 mip_index){
	return GetAPXPaletteAdrs0x2184a0(buf, mip_index);
}


ApxHeader* GetAPXFileHeader0x218350(void *buf){
	return (ApxHeader*)buf;
}

//INCLUDE_ASM("asm/main/nonmatchings/plAPX", GetAPXPixelMipmapAdrs0x218360);
u8 * GetAPXPixelMipmapAdrs0x218360(void *buf, s32 mip_index) {
	ApxHeader *header;
    s32 i;
	s32 width;
    s32 height;
    u8 *data;
    s32 bpp;
    s32 total_pixels;

	if (plAPXGetMipmapTextureNum0x217e50(buf) <= mip_index) {
        return 0x0;
	}
    header = GetAPXFileHeader0x218350(buf);
    width = header->width;
    height = header->height;
    data = header->data;
    i = 0;
    if (0 < mip_index) {
        bpp = header->bpp;
        do {
            switch (bpp) {
                case 0x4:
                    data = data + width * height / 2;
                    break;
                case 8:
                    data = data + width * height;
                    break;
                case 0x10:
                    data = data + width * height * 2;
                    break;
                case 0x18:
                    data = data + width * height * 3;
                    break;
                case 0x20:
                    data = data + width * height * 4;
                    break;
            }
            i++;
            width = width >> 1;
            height = height >> 1;
        } while (i < mip_index);
    }  

    return data;
}


//INCLUDE_ASM("asm/main/nonmatchings/plAPX", GetAPXPaletteAdrs0x2184a0);
u8* GetAPXPaletteAdrs0x2184a0(void *buf, s32 index) {
	ApxHeader *apx;
    u8 *pixel_address;
	s32 i;
    s32 num_colors;

	apx = GetAPXFileHeader0x218350(buf); //wtf
    // idk, this has two args, but ig not here, its also (buf, 0)
	pixel_address = GetAPXPixelMipmapAdrs0x218360(buf, 0) + apx->palette_offset; 
    
    switch (apx->bpp) {
        case 4:
            num_colors = 0x10;
            break;
        case 8:
            num_colors = 0x100;
            break;
    }
    
    i = 0;
	if (0 < index) {
		do {            
            switch (apx->palette_bpp) {
                case 0x10:
                    pixel_address += num_colors * 2;
                    break;
                case 0x18:
                    pixel_address += num_colors * 3;
                    break;
                case 0x20:
                    pixel_address += num_colors * 4;
                    break;
            }
			i++;
		} while (i < index);
	}
	return pixel_address;
}

