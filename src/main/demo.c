#include "common.h"
#include "structs.h"

//externs
extern void str_pause0x100ad0(s32, u8);
extern void adx_se_set0x21da90(void*, u16);
extern void demo_bgm_set0x21df30(u8);
extern void stage_bgm_set0x21df80(u8);
extern void DemoCameraCancel0x221ba0(void);
extern s32 DemoCameraCheck0x221bd0();
extern s32 Event_flag_set0x272ec0(s32);
extern void Event_flag_clear0x272f00(s32);
extern s32 Event_flag_ck0x272f50(s32);
extern bool Tutorial_flag_set0x63afa0(u8);

extern EVENT_DEMO_DATA evdemo_030x355460;
extern EVENT_DEMO_DATA evdemo_040x355470;
extern EVENT_DEMO_DATA evdemo_050x355480;
extern EVENT_DEMO_DATA evdemo_060x355490;
extern EVENT_DEMO_DATA evdemo_080x3554a0;
extern EVENT_DEMO_DATA evdemo_100x3554b0;
extern EVENT_DEMO_DATA evdemo_110x3554c0;
extern EVENT_DEMO_DATA evdemo_140x3554d0;
extern EVENT_DEMO_DATA evdemo_170x3554e0;
extern EVENT_DEMO_DATA evdemo_200x3554f0;
extern EVENT_DEMO_DATA evdemo_230x355500;
extern EVENT_DEMO_DATA evdemo_240x355510;
extern EVENT_DEMO event_demo0x531910;
extern u8 player_work0x3e4bf0[];
extern GAME_WORK game_w0x3f33f0;

//variables

//protos
s32 evdemo_init_sub0x286510(ACTIVE_EVENT_DEMO* arg0, EVENT_DEMO_DATA* arg1);
void evdemo_camera_request0x286920(u8, u8);

void EvDemoInitialize0x2862f0(void) {
    u16 quest;
    EVENT_DEMO* event = &event_demo0x531910;
    
    game_w0x3f33f0.demo_playing = 0;
    event_demo0x531910.active = 0;
    *(s32*)&event_demo0x531910.demos[1].active = 0;
    *(s32*)&event_demo0x531910.demos[0].active = 0;
    quest = game_w0x3f33f0.selected_quest_id;

    switch (quest) {
    case 0x88:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_030x355460);
        return;
    case 0x89:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_040x355470);
        return;
    case 0x8A:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_050x355480);
        evdemo_init_sub0x286510(&event->demos[1], &evdemo_240x355510);
        return;
    case 0x8B:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_060x355490);
        return;
    case 0x87:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_080x3554a0);
        return;
    case 0x94:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_100x3554b0);
        return;
    case 0x9A:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_110x3554c0);
        return;
    case 0xAB:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_140x3554d0);
        return;
    case 0x65:
    case 0x6B:
    case 0xCE:
        Event_flag_clear0x272f00(0x18);
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_170x3554e0);
        return;
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6A:
    case 0xCF:
        Event_flag_clear0x272f00(0x1B);
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_200x3554f0);
        return;
    case 0x83:
        evdemo_init_sub0x286510(&event->demos[0], &evdemo_230x355500);
    }
}

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

s32 event0000x2866c0(ACTIVE_EVENT_DEMO* demo) {
    switch (demo->state) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        game_w0x3f33f0.demo_playing = true;
        evdemo_camera_request0x286920(demo->demo_data->demoID, demo->demo_data->targetSpecies);
        if(demo->demo_data->bgm != 0)
            switch (demo->demo_data->bgm) {                        /* switch 2 */
            case 3:                                     /* switch 2 */
                demo->timer = 0x10E;
                str_pause0x100ad0(0, 1);
                break;
            case 2:                                     /* switch 2 */
                demo->timer = 0x15E;
            /* fallthrough */
            case 1:                                     /* switch 2 */
                str_pause0x100ad0(0, 1);
                break;
            }
        if (demo->demo_data->sfx != 0) {
            adx_se_set0x21da90(player_work0x3e4bf0 + (game_w0x3f33f0.my_player_number * 0xA00), demo->demo_data->sfx); //TODO once player_work is done
        }
        demo->state = demo->state + 1;
        break;
    case 1:                                         /* switch 1 */
        if (demo->timer != 0) {
            demo->timer = (s16) (demo->timer - 1);
            if (demo->timer == 0) {
                switch (demo->demo_data->bgm) {                /* switch 3 */
                case 2:                             /* switch 3 */
                    demo_bgm_set0x21df30(0x4E);
                    break;
                case 3:                             /* switch 3 */
                    demo_bgm_set0x21df30(0x54);
                    break;
                }
            }
        }
        if (DemoCameraCheck0x221bd0() <= 0) {
            demo->state = (u8) (demo->state + 1);
            game_w0x3f33f0.demo_playing = 0;
            Event_flag_set0x272ec0(demo->demo_data->flag);
            if (demo->demo_data->tutFlag1 != 0) {
                Tutorial_flag_set0x63afa0(demo->demo_data->tutFlag1);
                //Tutorial_flag_set0x63afa0();
                if (demo->demo_data->tutFlag2 != 0) {
                    Tutorial_flag_set0x63afa0(demo->demo_data->tutFlag2);
                }
            }
            
            switch (demo->demo_data->bgm) {                    /* switch 4 */
            case 1:                                 /* switch 4 */
                stage_bgm_set0x21df80(game_w0x3f33f0.current_area_id);
            case 0:                                 /* switch 4 */
                break;
            case 2:                                 /* switch 4 */
            case 3:                                 /* switch 4 */
                game_w0x3f33f0.BGM = 4;
                game_w0x3f33f0.music_timer = 0x96;
                break;
            }
        }
        break;
    case 2:                                         /* switch 1 */
        DemoCameraCancel0x221ba0();
        *(s32*)&demo->active = 0;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/demo", evdemo_camera_request0x286920);
