#ifndef FLPS2PS_H
#define FLPS2PS_H

#include "types.h"

typedef struct {
    // total size: 0x470
    u32 VideoMode;                    // offset 0x0, size 0x4
    u32 InterlaceMode;                // offset 0x4, size 0x4
    u32 DisplayMode;                  // offset 0x8, size 0x4
    s32 DispWidth;                    // offset 0xC, size 0x4
    s32 DispHeight;                   // offset 0x10, size 0x4
    u32 MAGH;                         // offset 0x14, size 0x4
    u32 FrameBitDepth;                // offset 0x18, size 0x4
    u32 FrameBuffForm;                // offset 0x1C, size 0x4
    u32 FrameBuffPageX;               // offset 0x20, size 0x4
    u32 FrameBuffPageY;               // offset 0x24, size 0x4
    u32 FrameBuffAdrs0;               // offset 0x28, size 0x4
    u32 FrameBuffAdrs1;               // offset 0x2C, size 0x4
    u32 ZBuffBitDepth;                // offset 0x30, size 0x4
    u32 ZBuffForm;                    // offset 0x34, size 0x4
    u32 ZBuffPageX;                   // offset 0x38, size 0x4
    u32 ZBuffPageY;                   // offset 0x3C, size 0x4
    u32 ZBuffAdrs;                    // offset 0x40, size 0x4
    f32 ZBuffMax;                     // offset 0x44, size 0x4
    u32 TextureStartAdrs;             // offset 0x48, size 0x4
    s32 Oddeven;                      // offset 0x4C, size 0x4
    s32 Dbi;                          // offset 0x50, size 0x4
    s32 FrameCount;                   // offset 0x54, size 0x4
    s32 FrameCountNext;               // offset 0x58, size 0x4
    s32 Irq_count;                    // offset 0x5C, size 0x4
    s32 Db_change_enable;             // offset 0x60, size 0x4
    s8 pad64[0xC];                    // offset 0x64, size 0xC
    u8 Db[0x330];                  // offset 0x70, size 0x330 //TODO sceGsDBuffDc
    u32 FrameClearColor;              // offset 0x3A0, size 0x4
    s32 D2dOffsetX;                   // offset 0x3A4, size 0x4
    s32 D2dOffsetY;                   // offset 0x3A8, size 0x4
    s32 ScreenOffsetX;                // offset 0x3AC, size 0x4
    s32 ScreenOffsetY;                // offset 0x3B0, size 0x4
    s32 ScreenDispX;                  // offset 0x3B4, size 0x4
    s32 ScreenDispY;                  // offset 0x3B8, size 0x4
    s32 ScreenAdjustX;                // offset 0x3BC, size 0x4
    s32 ScreenAdjustY;                // offset 0x3C0, size 0x4
    void* DmaChan[10];          // offset 0x3C4, size 0x28 //TODO sceDmaChan
    s32 NowVu1Code;                   // offset 0x3EC, size 0x4
    s32 NowVu1Size;                   // offset 0x3F0, size 0x4
    s32 DrawDisable;                  // offset 0x3F4, size 0x4
    uintptr_t system_memory_start;    // offset 0x3F8, size 0x4
    s32 system_memory_size;           // offset 0x3FC, size 0x4
    u32 SystemStatus;                 // offset 0x400, size 0x4
    s32 SystemIndex;                  // offset 0x404, size 0x4
    uintptr_t SystemTmpBuffStartAdrs; // offset 0x408, size 0x4
    uintptr_t SystemTmpBuffEndAdrs;   // offset 0x40C, size 0x4
    uintptr_t SystemTmpBuffNow;       // offset 0x410, size 0x4
    u32 SystemTmpBuffHandle[2];       // offset 0x414, size 0x8
    u64 RenderTESTStatus1;            // offset 0x420, size 0x4
    u64 RenderTESTStatus2;            // offset 0x428, size 0x4
    u64 RenderZBUFStatus1;            // offset 0x430, size 0x4
    u64 RenderZBUFStatus2;            // offset 0x438, size 0x4
    u64 RenderSCISSORStatus1;         // offset 0x440, size 0x4
    s32 RenderSCISSORValue1[4];       // offset 0x448, size 0x10
    u64 RenderSCISSORStatus2;         // offset 0x458, size 0x4
    s32 RenderSCISSORValue2[4];       // offset 0x460, size 0x10
} FLPS2State;

typedef struct {
    // total size: 0x3C
    u32 channel_id;             // offset 0x0, size 0x4
    u32 queue_size;             // offset 0x4, size 0x4
    s32 handleID;               // offset 0x8, size 0x4
    u32 dma_queue_handle[2];    // offset 0xC, size 0x8
    u32 queue_ctr[2];           // offset 0x14, size 0x8
    u32 queue_ptr0[2];          // offset 0x1C, size 0x8
    u32 queue_ptr1[2];          // offset 0x24, size 0x8
    u32 now_adrs;               // offset 0x2C, size 0x4
    u32 dma_normal_mode_status; // offset 0x30, size 0x4
    uintptr_t old_queue_data;   // offset 0x34, size 0x4
    uintptr_t old_endtag;       // offset 0x38, size 0x4
} FLPS2VIF1Control;

#endif
