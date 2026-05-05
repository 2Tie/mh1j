#include "common.h"
#include "structs.h"

//externs
extern s32 Event_flag_ck0x272f50(s32);
extern GAME_WORK game_w0x3f33f0;

//variables

//protos
s32 evdemo_init_sub0x286510(ACTIVE_EVENT_DEMO* arg0, EVENT_DEMO_DATA* arg1)

INCLUDE_ASM("asm/main/nonmatchings/demo", EvDemoInitialize0x2862f0);

s32 evdemo_init_sub0x286510(ACTIVE_EVENT_DEMO* demo, EVENT_DEMO_DATA* data) {
    if (Event_flag_ck0x272f50(data->flag) == 0) {
        demo->active = 1;
        demo->check = data->check;
        demo->event = data->event;
        demo->demo_data = data;
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/main/nonmatchings/demo", EvDemoMove0x286580);

s32 check0000x286660(ACTIVE_EVENT_DEMO* demo) {
    if (Event_flag_ck0x272f50(demo->demo_data->flag) == 1) {
        *(s32*)&demo->active = 0; //wipe the whole set?
        return -1;
    }
    return game_w0x3f33f0.current_area_id == demo->demo_data->areaID;
}

INCLUDE_ASM("asm/main/nonmatchings/demo", event0000x2866c0);

INCLUDE_ASM("asm/main/nonmatchings/demo", evdemo_camera_request0x286920);
