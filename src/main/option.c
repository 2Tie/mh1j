#include "common.h"
#include "structs.h"
#include "main/scheduler.h"
#include "main/option.h"

/* bss */
extern OPTION_WORK option_w0x3f20e0;

/* sdata */
extern char* menu_audio0x387700[2];
// char* menu_audio0x387700[2] = {
//     "ＭＯＮＡＵＲＡＬ",
//     "ＳＴＥＲＥＯ",
// };
extern char* menu_vib0x387708[2];
// char* menu_vib0x387708[2] = {
//     "ＯＦＦ",
//     "ＯＮ",
// };
extern s8 option_max_kind0x387710[8];
// s8 option_max_kind0x387710[8] = {
//     2, 8, 8, 2, 3, 0, 0, 0,
// };

/* data */
extern char* option_menu_msg0x2ef7c0[8];
// char* option_menu_msg0x2ef7c0[8] = {
//     "ＳＯＵＮＤ",
//     "ＢＧＭ　ＬＥＶＥＬ",
//     "ＳＥ　ＬＥＶＥＬ",
//     "ＶＩＢＲＡＴＩＯＮ",
//     "ＴＡＲＧＥＴＩＮＧ",
//     "ＳＣＲＥＥＮ　ＡＤＪＵＳＴ",
//     "ＤＥＦＡＵＬＴ　ＳＥＴＴＩＮＧＳ",
//     "ＥＸＩＴ",
// };
extern char* menu_bgm0x2ef7e0[8];
// char* menu_bgm0x2ef7e0[8] = {
//     "ＭＩＮ□□□□□□□ＭＡＸ", "ＭＩＮ■□□□□□□ＭＡＸ", "ＭＩＮ■■□□□□□ＭＡＸ",
//     "ＭＩＮ■■■□□□□ＭＡＸ", "ＭＩＮ■■■■□□□ＭＡＸ", "ＭＩＮ■■■■■□□ＭＡＸ",
//     "ＭＩＮ■■■■■■□ＭＡＸ", "ＭＩＮ■■■■■■■ＭＡＸ",
// };
extern char* menu_gun0x2ef800[4];
// char* menu_gun0x2ef800[4] = {
//     "ＮＯＲＭＡＬ",
//     "ＲＥＶＥＲＳＥ１",
//     "ＲＥＶＥＲＳＥ２",
//     NULL,
// };
extern char** sub_str_tbl0x2ef810[8];
// char** sub_str_tbl0x2ef810[8] = {
//     menu_audio0x387700,
//     menu_bgm0x2ef7e0,
//     menu_bgm0x2ef7e0,
//     menu_vib0x387708,
//     menu_gun0x2ef800,
//     NULL,
//     NULL,
//     NULL,
// };
extern OPTION_CFG cfg_default0x2ef830;
// OPTION_CFG cfg_default0x2ef830 = {
//     1, 7, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// };
extern ARROW_ENTRY arrow_tbl0x2ef840[4];
// ARROW_ENTRY arrow_tbl0x2ef840[4] = {
//     {296, 96, 8192, 2, 0},
//     {232, 160, 2048, 0, 0},
//     {296, 224, 4096, 3, 0},
//     {360, 160, 1024, 1, 0},
// };

/* extern */
extern PSW Psw0x3f3710[2];

extern void memcpy0x19db70(void*, void*, u32);
extern void system_w_set0x11f8a0(void);
extern void str_master_vol0x100b40(s32);
extern void SetTrnslMode0x161480(s32, s32);
extern void trans0x163bc0(void);
extern u8 Fade_busy_ck0x10ed70(void);
extern void str_play0x100980(s32, s32);
extern void setBGcolor0x11f9e0(s32);
extern void fade_set0x10ef80(s32);
extern void decide_se0x162d20(void);
extern void vib_set0x1698d0(s32, s32);
extern void cancel_se0x162d40(void);
extern void cursor_se0x162d30(void);
extern void flAdjustScreen0x179db0(s32, s32);
extern void McOperationSet0x2821d0(u8);
extern void str_stop_all0x100b10(void);
extern u8 McCardOperation0x2860d0(void);
extern void vib_stop_all0x1699a0(void);
extern s32 save_file_req0x100e80(void);
extern void Tsk_Exit0x1252b0(TASK*);
extern void Load_overlay0x23e510(s32, s32);
extern void Select_Tsk_Execute0x125260(void);
extern s32 strlen0x1a13b8(char*);
extern void flfntLocate0x2168b0(s16, s16);
extern void font_print0x161970(char*, char*);
extern void Sel_back_disp0x23af30(s32);
extern void Sel_menu_disp0x23afc0(s32);
extern void flfntSetSize0x216890(u8, u8);
extern void font_set_palette0x1626a0(s16);
extern void font_print_ex0x161b80(s32, s32, s32, ...);
extern void Disp_button0x163420(s32, s32, s32, s32, f32);
extern void reload_tex0x11f170(s32, s32);
extern void SetTextureStage0x161550(s32);
extern void Put_sprite_rotate0x15b300(SPRITE*, s8);
extern void SetFilterMode0x161500(s32);

void option_default_set0x1267c0(void) {
    memcpy0x19db70(&option_w0x3f20e0.cfg, &cfg_default0x2ef830, sizeof(OPTION_CFG));
    system_w_set0x11f8a0();
    str_master_vol0x100b40(1);
}

void Option_task0x126800(OPTION_TASK* task) {
    u16 input = Psw0x3f3710->just_pressed | Psw0x3f3710->held_state;

    SetTrnslMode0x161480(4, 5);

    switch (task->state) {
        case OPT_TSK_INIT:
            option_init0x1268f0(task);
            break;

        case OPT_TSK_MAIN_MENU:
            option_main_menu0x126960(task, input);
            break;

        case OPT_TSK_SUB_MENU:
            option_sub_menu0x126cc0(task, input);
            break;

        case OPT_TSK_NONE:
            break;

        case OPT_TSK_EXIT:
            option_exit0x126e90(task, input);
            break;
    }

    trans0x163bc0();
}

void option_init0x1268f0(OPTION_TASK* task) {
    if (Fade_busy_ck0x10ed70() != true) {
        task->cursor = OPT_SOUND;
        task->state += 1;

        str_play0x100980(0, 78);
        setBGcolor0x11f9e0(0);
        fade_set0x10ef80(2);
        disp_option_menu0x127040(task);
    }
}

void option_main_menu0x126960(OPTION_TASK* task, u16 input) {
    if (Psw0x3f3710->just_pressed & SW_CIRCLE) {
        if (task->cursor == OPT_SCREEN_ADJUST) {
            task->state = OPT_TSK_SUB_MENU;
            decide_se0x162d20();
        } else {
            if (task->cursor == OPT_DEFAULT_SETTINGS) {
                decide_se0x162d20();

                if (option_w0x3f20e0.cfg.vibration == false) {
                    option_w0x3f20e0.cfg.vibration = true;
                    vib_set0x1698d0(0, 1);
                    vib_set0x1698d0(1, 1);
                }

                option_default_set0x1267c0();
            }

            if (task->cursor == OPT_EXIT) {
                task->state = OPT_TSK_EXIT;
                task->exit_state = OPT_EXIT_INIT;
                cancel_se0x162d40();
            }
        }
    } else if (Psw0x3f3710->just_pressed & SW_CROSS) {
        if (task->cursor != OPT_EXIT) {
            task->cursor = OPT_EXIT;
            cancel_se0x162d40();
        }
    } else {
        if (input & SW_D_UP) {
            if (task->cursor == OPT_SOUND) {
                task->cursor = OPT_EXIT;
            } else {
                task->cursor -= 1;
            }
            cursor_se0x162d30();
        }

        if (input & SW_D_DOWN) {
            if (task->cursor == OPT_EXIT) {
                task->cursor = OPT_SOUND;
            } else {
                task->cursor += 1;
            }
            cursor_se0x162d30();
        }

        if (task->cursor == OPT_VIBRATION) {
            input = Psw0x3f3710->just_pressed;
        }

        if (input & SW_D_RIGHT) {
            param_change0x126b30(task, 1);
        }

        if (input & SW_D_LEFT) {
            param_change0x126b30(task, -1);
        }
    }

    disp_option_menu0x127040(task);
}

void param_change0x126b30(OPTION_TASK* task, s32 direction) {
    s8* option;
    u8 max_value;
    OPTION_TSK_STATE cursor = task->cursor;

    switch (cursor) {
        case OPT_SCREEN_ADJUST:
        case OPT_DEFAULT_SETTINGS:
        case OPT_EXIT:
            break;

        default:
            if (direction < 0 && ((s8*) &option_w0x3f20e0.cfg)[cursor] == 0) {
                option = &((s8*) &option_w0x3f20e0.cfg)[cursor];
                max_value = option_max_kind0x387710[cursor];

                *option = max_value - 1;
            } else {
                option = &((s8*) &option_w0x3f20e0.cfg)[cursor];
                max_value = option_max_kind0x387710[cursor];

                *option = (*option + (s8) (direction)) % max_value;
            }

            system_w_set0x11f8a0();

            switch (task->cursor) {
                case OPT_VIBRATION:
                    if (option_w0x3f20e0.cfg.vibration != false) {
                        vib_set0x1698d0(0, 1);
                        vib_set0x1698d0(1, 1);
                    }
                    break;

                case OPT_BGM_LEVEL:
                    str_master_vol0x100b40(1);
                    break;
            }

            cursor_se0x162d30();
            break;
    }
}

s32 cfg_change_ck0x126c60(void) {
    s16 i;
    s8* options;
    s8* default_options;

    options = (s8*) &option_w0x3f20e0;
    default_options = (s8*) &cfg_default0x2ef830;

    for (i = 0; i < 16; i++) {
        if (*options != *default_options) {
            return true;
        }
        options++;
        default_options++;
    }

    return false;
}

void option_sub_menu0x126cc0(OPTION_TASK* task, u16 input) {
    s16 pos_changed = false;
    OPTION_CFG* cfg = &option_w0x3f20e0.cfg;
    u16 input_changed = SW_NONE;

    if (Psw0x3f3710->just_pressed & SW_CROSS) {
        task->state = OPT_TSK_MAIN_MENU;
        task->unk15 = 0;
        cancel_se0x162d40();
        system_w_set0x11f8a0();
    } else {
        if (input & SW_D_UP) {
            if (cfg->screen_pos_y > -16) {
                pos_changed = true;
                cfg->screen_pos_y--;
                input_changed |= SW_D_UP;
                cursor_se0x162d30();
            } else {
                cfg->screen_pos_y = -16;
            }
        }

        if (input & SW_D_DOWN) {
            if (cfg->screen_pos_y < 16) {
                pos_changed = true;
                cfg->screen_pos_y++;
                input_changed |= SW_D_DOWN;
                cursor_se0x162d30();
            } else {
                cfg->screen_pos_y = 16;
            }
        }

        if (input & SW_D_LEFT) {
            if (cfg->screen_pos_x > -16) {
                pos_changed = true;
                cfg->screen_pos_x--;
                input_changed |= SW_D_LEFT;
                cursor_se0x162d30();
            } else {
                cfg->screen_pos_x = -16;
            }
        }

        if (input & SW_D_RIGHT) {
            if (cfg->screen_pos_x < 16) {
                pos_changed = true;
                cfg->screen_pos_x++;
                input_changed |= SW_D_RIGHT;
                cursor_se0x162d30();
            } else {
                cfg->screen_pos_x = 16;
            }
        }

        if (pos_changed != false) {
            flAdjustScreen0x179db0(cfg->screen_pos_x, cfg->screen_pos_y);
        }
    }

    disp_option_sub_menu0x127250(task, input_changed);
}

void option_exit0x126e90(OPTION_TASK* task, u16 input) {
    switch (task->exit_state) {
        case OPT_EXIT_INIT:
            task->exit_state += 1;
            task->exit_timer = 0;
            McOperationSet0x2821d0(1);
            disp_option_menu0x127040(task);
            str_stop_all0x100b10();
            break;

        case OPT_EXIT_MC:
            if (McCardOperation0x2860d0() != false) {
                task->exit_state += 1;
                fade_set0x10ef80(1);
            }
            disp_option_menu0x127040(task);
            break;

        case OPT_EXIT_FADE:
            if (Fade_busy_ck0x10ed70() != true) {
                task->exit_state += 1;
                system_w_set0x11f8a0();
                str_stop_all0x100b10();
                vib_stop_all0x1699a0();
                save_file_req0x100e80();
            }
            disp_option_menu0x127040(task);
            break;

        case OPT_EXIT_FINALIZE:
            if (++task->exit_timer >= 10) {
                Tsk_Exit0x1252b0((TASK*) task);
                Load_overlay0x23e510(1, 1);
                Select_Tsk_Execute0x125260();
                fade_set0x10ef80(2);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/option", opt_sub_disp0x126fd0);
// void opt_sub_disp0x126fd0(s16 pos_y, char* str) {
//     u32 str_length = strlen0x1a13b8(str);
//     s16 pos_x = 440 - (str_length * 9) / 2;

//     flfntLocate0x2168b0(pos_x, pos_y);
//     font_print0x161970("%s", str);
// }

INCLUDE_ASM("asm/nonmatchings/main/option", disp_option_menu0x127040);
// void disp_option_menu0x127040(OPTION_TASK* task) {
//     s32 pos_y;
//     s32 menu_item;
//     s32 palette;
//     s8* str;

//     Sel_back_disp0x23af30(255);
//     Sel_menu_disp0x23afc0(2);

//     pos_y = 100;

//     flfntSetSize0x216890(18, 18);

//     for (menu_item = 0; menu_item < 8; menu_item++) {
//         if (menu_item == task->cursor) {
//             palette = 11; // orange - cursor highlight
//         } else if (menu_item == OPT_DEFAULT_SETTINGS && cfg_change_ck0x126c60()) {
//             palette = 3; // green - default settings highlight
//         } else {
//             palette = 0; // white
//         }

//         if (menu_item == OPT_EXIT) {
//             pos_y += 12;
//         }

//         flfntLocate0x2168b0(44, pos_y);
//         font_set_palette0x1626a0(palette);
//         font_print0x161970("%s", option_menu_msg0x2ef7c0[menu_item]);

//         switch (menu_item) {
//             case OPT_SOUND:
//                 str = sub_str_tbl0x2ef810[menu_item][((s8*) &option_w0x3f20e0.cfg)[menu_item]];
//                 opt_sub_disp0x126fd0(pos_y, str);
//                 break;

//             case OPT_VIBRATION:
//                 str = sub_str_tbl0x2ef810[menu_item][((s8*) &option_w0x3f20e0.cfg)[menu_item]];
//                 opt_sub_disp0x126fd0(pos_y, str);
//                 break;

//             case OPT_TARGETING:
//                 str = sub_str_tbl0x2ef810[menu_item][((s8*) &option_w0x3f20e0.cfg)[menu_item]];
//                 opt_sub_disp0x126fd0(pos_y, str);
//                 break;

//             case OPT_BGM_LEVEL:
//             case OPT_SE_LEVEL:
//                 str = sub_str_tbl0x2ef810[menu_item][((s8*) &option_w0x3f20e0.cfg)[menu_item]];
//                 opt_sub_disp0x126fd0(pos_y, str);
//                 break;
//         }

//         pos_y += 40;
//     }
// }

INCLUDE_RODATA("asm/nonmatchings/main/option", @550x3584d8); // "ＳＯＵＮＤ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @560x3584f0); // "ＢＧＭ　ＬＥＶＥＬ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @570x358510); // "ＳＥ　ＬＥＶＥＬ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @580x358530); // "ＶＩＢＲＡＴＩＯＮ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @590x358550); // "ＴＡＲＧＥＴＩＮＧ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @600x358570); // "ＳＣＲＥＥＮ　ＡＤＪＵＳＴ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @610x358590); // "ＤＥＦＡＵＬＴ　ＳＥＴＴＩＮＧＳ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @620x3585b8); // "ＥＸＩＴ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @670x3585d0); // "ＭＯＮＡＵＲＡＬ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @680x3585e8); // "ＳＴＥＲＥＯ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @690x358600); // "ＭＩＮ□□□□□□□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @700x358620); // "ＭＩＮ■□□□□□□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @710x358640); // "ＭＩＮ■■□□□□□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @720x358660); // "ＭＩＮ■■■□□□□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @730x358680); // "ＭＩＮ■■■■□□□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @740x3586a0); // "ＭＩＮ■■■■■□□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @750x3586c0); // "ＭＩＮ■■■■■■□ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @760x3586e0); // "ＭＩＮ■■■■■■■ＭＡＸ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @770x358700); // "ＯＦＦ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @780x358708); // "ＯＮ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @790x358710); // "ＮＯＲＭＡＬ"

INCLUDE_RODATA("asm/nonmatchings/main/option", @800x358720); // "ＲＥＶＥＲＳＥ１"

INCLUDE_RODATA("asm/nonmatchings/main/option", @810x358740); // "ＲＥＶＥＲＳＥ２"

INCLUDE_RODATA("asm/nonmatchings/main/option", @2950x358758); // "%s"

// splat not generating those ?

// INCLUDE_RODATA("asm/nonmatchings/main/option", @3890x358760); // "Ｘ　ＰＯＳＩＴＩＯＮ"

// INCLUDE_RODATA("asm/nonmatchings/main/option", @3900x358780); // "Ｙ　ＰＯＳＩＴＩＯＮ"

// INCLUDE_RODATA("asm/nonmatchings/main/option", @3910x358798); // "：ＥＸＩＴ"

// INCLUDE_RODATA("asm/nonmatchings/main/option", @3920x3587a8); // "%d"

INCLUDE_ASM("asm/nonmatchings/main/option", disp_option_sub_menu0x127250);
// void disp_option_sub_menu0x127250(OPTION_TASK* task, u16 input) {
//     ARROW_ENTRY* arrow;
//     SPRITE sprite;
//     s16 i;

//     switch (task->cursor) {
//         case OPT_SCREEN_ADJUST:
//             Sel_back_disp0x23af30(255);
//             Sel_menu_disp0x23afc0(3);

//             flfntSetSize0x216890(18, 18);
//             font_print_ex0x161b80(184, 304, 0, "Ｘ　ＰＯＳＩＴＩＯＮ");
//             font_print_ex0x161b80(184, 340, 0, "Ｙ　ＰＯＳＩＴＩＯＮ");
//             font_print_ex0x161b80(292, 392, 0, "：ＥＸＩＴ");

//             flfntSetSize0x216890(36, 18);
//             font_print_ex0x161b80(418, 304, 0, "%d", option_w0x3f20e0.cfg.screen_pos_x);
//             font_print_ex0x161b80(418, 340, 0, "%d", option_w0x3f20e0.cfg.screen_pos_y);

//             Disp_button0x163420(1, 271, 389, 8, 1.0f);

//             reload_tex0x11f170(1, 8);
//             SetTextureStage0x161550(8);

//             sprite.w = 64;
//             sprite.h = 64;
//             sprite.u0 = 0;
//             sprite.v0 = 160;
//             sprite.u1 = sprite.u0 + 64;
//             sprite.v1 = sprite.v0 + 64;

//             for (i = 0; i < 4; i++) {
//                 arrow = &arrow_tbl0x2ef840[i];

//                 sprite.x = arrow->x;
//                 sprite.y = arrow->y;

//                 if (input & arrow->direction) {
//                     sprite.color = 0xFF00FFFF; // cyan
//                 } else {
//                     sprite.color = 0xFFFFFFFF; // white
//                 }

//                 Put_sprite_rotate0x15b300(&sprite, arrow->rotation);
//             }
//     }

//     SetFilterMode0x161500(1);
// }
