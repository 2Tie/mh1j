#include "common.h"
#include "structs.h"
#include "main/modesel.h"
#include "main/scheduler.h"

char* main_menu_msg0x349210[8] = {
    "ＮＥＷ　ＧＡＭＥ",
    "ＣＯＮＴＩＮＵＥ",
    "ＧＡＬＬＥＲＹ",
    "ＯＰＴＩＯＮＳ",
    "ＤＥＢＵＧ",
    NULL,
    NULL,
    NULL,
};
char* game_menu_msg0x387a70[2] = {
    "街へ行く",
    "村へ行く",
};
char* game_menu_msg20x349230[4] = {
    "街にいる他のハンターたちと狩りに挑みます。",
    "（ＮＥＴＷＯＲＫ ＭＯＤＥ）",
    "村から１人で狩りに出かけます。",
    "（ＳＩＮＧＬＥ ＭＯＤＥ）",
};
s16 menu_str_000x349240[16] = {
    4, 0, 9, 3, 255, 9, 3, 10, 16, -1, 0, 0, 0, 0, 0, 0,
};
s16 menu_str_010x349260[16] = {
    9, 11, 2, 3, 255, 14, 3, 8, 3, 1, 15, -1, 0, 0, 0, 0,
};
s16 menu_str_020x349280[8] = {
    11, 12, 15, 6, 11, 10, 14, -1,
};
s16 menu_str_030x349290[16] = {
    14, 1, 13, 3, 3, 10, 254, 0, 2, 7, 16, 14, 15, -1, 0, 0,
};
s16 menu_str_040x3492b0[24] = {
    1, 5, 0, 13, 0, 1, 15, 3, 13, 252, 1, 13, 3, 0, 15, 6, 11, 10, -1, 0, 0, 0, 0, 0,
};
s16 menu_str_050x3492e0[24] = {
    1, 5, 0, 13, 0, 1, 15, 3, 13, 252, 14, 3, 8, 3, 1, 15, -1, 0, 0, 0, 0, 0, 0, 0,
};
s16 menu_str_060x349310[8] = {
    4, 0, 8, 8, 3, 13, 18, -1,
};
s16 menu_str_num0x349320[8] = {
    9, 11, 7, 13, 18, 16, 7, 0,
};
s16* menu_str0x349330[8] = {
    menu_str_000x349240, menu_str_010x349260, menu_str_020x349280, menu_str_030x349290,
    menu_str_040x3492b0, menu_str_050x3492e0, menu_str_060x349310, NULL,
};
s16 help_mess0x349350[8] = {
    50, 342, 5140, 1051, 0, 4, 8208, -16320,
};
char* omake_str0x349360[12] = {
    "Ｅ３公開映像",
    "オープニング",
    "ハンターの集う街",
    "グラビモスの生態",
    "ガノトトスの生態",
    "フルフルの生態",
    "ディアブロスの生態",
    "リオレイアの生態",
    "英雄の証",
    "-------",
    NULL,
    NULL,
};
u16 check_bit_no0x349390[16] = {
    0xFFFF, 0xFFFF, 5, 6, 2, 7, 4, 3, 8, 0, 0, 0, 0, 0, 0, 0,
};
s16 movie_no0x3493b0[12] = {
    8, 0, 4, 6, 1, 7, 3, 2, 5, 0, 0, 0,
};

/* --- extern --- */
extern PSW Psw0x3f3710[2];
extern DEMO_WORK demo_w0x3f3620;
extern SYSTEM_WORK system_w0x3f3690;
extern u32 PIT_TEX0x2ef290[3];
extern u32 mem_tex0x3f3990[345];
extern u8 User_data0x3c6fc0[0x480]; // define struct
extern u8 select_w0x3f3330[0xC0];   // define struct
extern s16 key_timer0x38a610[2][2];
extern s16 key_wait0x38a618[2];
extern TASK tcb_w0x3963b0[16];
extern u16 System_timer0x38a1f4;

extern void TransSet0x163b00(void*);
extern void trans0x163bc0(void);
extern u8 Fade_busy_ck0x10ed70(void);
extern void fade_set0x10ef80(s32);
extern void Tsk_Kill0x125320(s32);
extern void Init_rev_set0x21e270(void);
extern void all_reset0x162730(void);
extern void load_texlist0x11e9e0(s32, s32, s32);
extern void Menu_snd_load0x15a410(void);
extern void setBGcolor0x11f9e0(s32);
extern void cursor_se0x162d30(void);
extern void decide_se0x162d20(void);
extern void cancel_se0x162d40(void);
extern void Tsk_Exit0x1252b0(TASK*);
extern void Tsk_Execute0x125200(void*, s32);
extern void Edit_task0x5367f0(TASK*);
extern void Tsk_Sleep0x1252c0(s32);
extern void Cont_task0x5375f0(TASK*);
extern void Game_task0x10f050(TASK*);
extern void Option_task0x126800(TASK*);
extern void Demo_task0x533be0(TASK*);
extern void flfntSetSize0x216890(u8, u8);
extern void font_set_palette0x1626a0(s16);
extern void flfntLocate0x2168b0(u16, u16);
extern void DispFrameMessage0x276160(s16*, u8);
extern void font_print_ex0x161b80(s16, s16, s16, char*, ...);
extern void Disp_button0x163420(BUTTON_GLYPH, s16, s16, s32, f32);
extern u32 strlen0x1a13b8(char*);
extern void font_reset0x1626c0(void);
extern void SetFilterMode0x161500(s32);
extern void reload_tex0x11f170(u32, u32);
extern void SetTextureStage0x161550(s32);
extern void Put_2TF0x15b650(SPRITE*);
extern void flSetRenderState0x177720(u8, u32);
extern void SetTrnslMode0x161480(s32, s32);
extern f32 flSin0x173600(f32);
extern void flps00050x175750(void*);

void Select_task0x23a0f0(TASK* task) {
    u16 input_current = Psw0x3f3710->current_state;
    u16 input_pressed = Psw0x3f3710->just_pressed;

    switch (task->unk_8) {
        case 0:
            csub000x23a230(task);
            break;

        case 1:
            init_mode_sel0x23a370(task);
            Sel_back_disp0x23af30(255);
            TransSet0x163b00(disp_mode_menu0x23ab50);
            break;

        case 2:
            mode_sel0x23a4b0(task, input_current, input_pressed);
            Sel_back_disp0x23af30(255);
            TransSet0x163b00(disp_mode_menu0x23ab50);
            break;

        case 3:
            mode_sel_end0x23a7f0(task);
            Sel_back_disp0x23af30(255);
            TransSet0x163b00(disp_mode_menu0x23ab50);
            break;

        case 4:
            mode_sel_exit0x23a9c0(task);
            if (task->unk_b < 2) {
                Sel_back_disp0x23af30(255);
                TransSet0x163b00(disp_mode_menu0x23ab50);
            }
            break;
    }

    if (task->unk_8 != 0) {
        trans0x163bc0();
    }
}

void csub000x23a230(TASK* task) {
    switch (task->unk_a) {
        case 0:
            if (ck_start_sw0x23a350() != false && Fade_busy_ck0x10ed70() != true) {
                demo_w0x3f3620.initting = 1;
                system_w0x3f3690.unk_0 = 1;
                system_w0x3f3690.unk_1 = 1;
                task->unk_a += 1;
                fade_set0x10ef80(1);
            }
            break;

        case 1:
            if (Fade_busy_ck0x10ed70() != true) {
                task->unk_a += 1;
                Tsk_Kill0x125320(3);
                task->unk_c = 5;
            }
            break;

        case 2:
            if (--task->unk_c <= 0) {
                task->unk_8 += 1;
                task->unk_c = 0;
                task->unk_e = 0;
                Init_rev_set0x21e270();
                all_reset0x162730();
            }
            break;
    }
}

s32 ck_start_sw0x23a350(void) {
    s32 var_v0 = 0;

    if (Psw0x3f3710->just_pressed & SW_START) {
        var_v0 |= 1;
    }

    return var_v0;
}

void init_mode_sel0x23a370(TASK* task) {
    if (mem_tex0x3f3990[2] == 0) {
        load_texlist0x11e9e0(PIT_TEX0x2ef290[0], 2, 0);
    }

    Menu_snd_load0x15a410();
    setBGcolor0x11f9e0(0);

    task->unk_8 += 1;
    task->unk_9 = 0;
    task->unk_a = 0;
    task->unk_14 = 1;
    task->unk_b = 0;
}

void sel_sel_sub0x23a3e0(u16 input_current, u16 input_pressed, u8* cursor, u8 max_items) {
    u16 input_key = key_rept_du0x23aa60(0, input_current, input_pressed);

    switch (input_key) {
        case SW_D_UP:
            if (*cursor == 0) {
                *cursor = max_items - 1;
            } else {
                *cursor -= 1;
            }
            cursor_se0x162d30();
            break;

        case SW_D_DOWN:
            if (*cursor == max_items - 1) {
                *cursor = 0;
            } else {
                *cursor += 1;
            }
            cursor_se0x162d30();
            break;
    }
}

void mode_sel0x23a4b0(TASK* task, u16 input_current, u16 input_pressed) {
    switch (task->unk_9) {
        case 0:
            switch (input_pressed) {
                case SW_CIRCLE:
                case SW_START:
                    switch (task->unk_14) {
                        case MAIN_MENU_OPTIONS:
                        default:
                            task->unk_8 = 3;
                            decide_se0x162d20();
                            fade_set0x10ef80(1);
                            break;

                        case MAIN_MENU_NEW_GAME:
                            task->unk_9 += 1;
                            task->unk_15 = SEL_MODE_MENU_NETWORK;
                            decide_se0x162d20();
                            fade_set0x10ef80(1);
                            break;

                        case MAIN_MENU_CONTINUE:
                            task->unk_9 += 1;
                            task->unk_15 = SEL_MODE_MENU_NETWORK;
                            decide_se0x162d20();
                            fade_set0x10ef80(1);
                            break;
                    }
                    break;

                case SW_CROSS:
                    task->unk_8 = 4;
                    task->unk_b = 0;
                    cancel_se0x162d40();
                    break;

                default:
                    sel_sel_sub0x23a3e0(input_current, input_pressed, &task->unk_14, 4);
                    break;
            }
            break;

        case 1:
            switch (task->unk_14) {
                case MAIN_MENU_OPTIONS:
                default:
                    task->unk_9 += 1;
                    break;

                case MAIN_MENU_NEW_GAME:
                    if (Fade_busy_ck0x10ed70() != true) {
                        Tsk_Exit0x1252b0((TASK*) task);
                        Tsk_Execute0x125200(Edit_task0x5367f0, 4);
                    }
                    break;

                case MAIN_MENU_CONTINUE:
                    if (Fade_busy_ck0x10ed70() != true) {
                        task->unk_9 += 1;
                        select_w0x3f3330[0xB6] = 0;
                        Tsk_Sleep0x1252c0(1);
                        Tsk_Execute0x125200(Cont_task0x5375f0, 4);
                    }
                    break;
            }
            break;

        case 2:
            task->unk_9 += 1;
            if (task->unk_14 == MAIN_MENU_CONTINUE && User_data0x3c6fc0[0x3ED] != 0) {
                task->unk_15 = SEL_MODE_MENU_SINGLE;
            } else {
                task->unk_15 = SEL_MODE_MENU_NETWORK;
            }
            task->unk_10 = 20;
            /* fallthrough */

        case 3:
            if (task->unk_10 != 0) {
                task->unk_10 -= 1;
            }

            switch (input_pressed) {
                case SW_CIRCLE:
                case SW_START:
                    if (task->unk_10 == 0) {
                        task->unk_8 = 3;
                        decide_se0x162d20();
                        User_data0x3c6fc0[0x3ED] = task->unk_15;
                        switch (task->unk_14) {
                            case MAIN_MENU_NEW_GAME:
                                fade_set0x10ef80(1);
                                break;

                            case MAIN_MENU_CONTINUE:
                                fade_set0x10ef80(1);
                                break;
                        }
                    }
                    break;

                case SW_CROSS:
                    task->unk_9 = 0;
                    cancel_se0x162d40();
                    break;

                default:
                    switch (task->unk_14) {
                        case MAIN_MENU_OPTIONS:
                        default:
                            task->unk_9 = 0;
                            return;

                        case MAIN_MENU_NEW_GAME:
                        case MAIN_MENU_CONTINUE:
                            break;
                    }

                    sel_sel_sub0x23a3e0(input_current, input_pressed, &task->unk_15, 2);
                    break;
            }
            break;
    }
}

void mode_sel_end0x23a7f0(TASK* task) {
    switch (task->unk_14) {
        case MAIN_MENU_NEW_GAME:
            if (Fade_busy_ck0x10ed70() != true) {
                if (task->unk_15 == SEL_MODE_MENU_NETWORK) {
                    system_w0x3f3690.online = true;
                } else {
                    system_w0x3f3690.online = false;
                }
                system_w0x3f3690.unk_2 = 0;
                system_w0x3f3690.unk_3 = 1;
                system_w0x3f3690.unk_5 = 0;
                Tsk_Exit0x1252b0(task);
                Tsk_Execute0x125200(Game_task0x10f050, 5);
            }
            return;

        case MAIN_MENU_CONTINUE:
            if (Fade_busy_ck0x10ed70() != true) {
                if (task->unk_15 == SEL_MODE_MENU_NETWORK) {
                    system_w0x3f3690.online = true;
                } else {
                    system_w0x3f3690.online = false;
                }
                system_w0x3f3690.unk_2 = 0;
                system_w0x3f3690.unk_5 = 0;
                system_w0x3f3690.unk_3 = 1;
                Tsk_Execute0x125200(Game_task0x10f050, 5);
                Tsk_Exit0x1252b0(task);
            }
            return;

        case MAIN_MENU_OPTIONS:
            if (Fade_busy_ck0x10ed70() != true) {
                Tsk_Exit0x1252b0(task);
                Tsk_Execute0x125200(Option_task0x126800, 4);
            }
            return;

        case MAIN_MENU_GALLERY:
            if (Fade_busy_ck0x10ed70() != true) {
                Tsk_Exit0x1252b0(task);
                Tsk_Execute0x125200(Omake_task0x23bd00, 4);
            }
            return;

        default:
            Tsk_Exit0x1252b0(task);
            Tsk_Execute0x125200(Demo_task0x533be0, 3);
            return;
    }
}

void mode_sel_exit0x23a9c0(TASK* task) {
    switch (task->unk_b) {
        case 0:
            task->unk_b += 1;
            fade_set0x10ef80(1);
            break;

        case 1:
            if (Fade_busy_ck0x10ed70() != true) {
                task->unk_b += 1;
                all_reset0x162730();
                Tsk_Exit0x1252b0(task);
                Tsk_Execute0x125200(Demo_task0x533be0, 3);
            }
            break;

        case 2:
            break;
    }
}

s32 key_rept_du0x23aa60(s32 controller, u16 input_current, u16 input_pressed) {
    s32 result = input_pressed;

    if (input_pressed & (SW_D_UP | SW_D_DOWN)) {
        key_timer0x38a610[controller][0] = 0;
        key_timer0x38a610[controller][1] = 0;
        return result;
    }

    if (input_current & (SW_D_UP | SW_D_DOWN)) {
        result = 0;

        if (key_timer0x38a610[controller][0] != 0) {
            key_wait0x38a618[controller] = 4;
        } else {
            key_wait0x38a618[controller] = 10;
        }

        if (++key_timer0x38a610[controller][1] > key_wait0x38a618[controller]) {
            key_timer0x38a610[controller][1] = 0;
            key_timer0x38a610[controller][0] = 1;
            return input_current;
        }
    } else {
        key_timer0x38a610[controller][0] = 0;
        key_timer0x38a610[controller][1] = 0;
    }

    return result;
}

void disp_mode_menu0x23ab50(void) {
    s32 pos_x;
    s32 pos_y;
    s32 cursor;
    s32 y_step;
    s32 i;
    s32 palette_1;
    s32 palette_2;
    TASK* task;
    s32 qty_msg;
    char** menu_msg;

    task = &tcb_w0x3963b0[1];

    flfntSetSize0x216890(26, 26);
    font_set_palette0x1626a0(4);

    pos_y = 32;
    flfntLocate0x2168b0(177, 32);

    switch (task->unk_9) {
        case 0:
        case 1:
            cursor = task->unk_14;
            qty_msg = 4;
            menu_msg = main_menu_msg0x349210;
            Sel_menu_disp0x23afc0(0);
            y_step = 64;
            pos_y = 136;
            break;

        case 2:
        case 3:
            cursor = task->unk_15;

            switch (task->unk_14) {
                case MAIN_MENU_OPTIONS:
                    return;

                case MAIN_MENU_NEW_GAME:
                case MAIN_MENU_CONTINUE:
                    Sel_menu_disp0x23afc0(1);
                    DispFrameMessage0x276160(help_mess0x349350, 0);

                    pos_y = 350;
                    y_step = 24;

                    flfntSetSize0x216890(20, 20);

                    menu_msg = game_menu_msg20x349230;

                    if (task->unk_15 != SEL_MODE_MENU_NETWORK) {
                        pos_x = (640 - (strlen0x1a13b8(menu_msg[2]) * 10)) / 2;
                        font_print_ex0x161b80(pos_x, pos_y, 0, "%s", menu_msg[2]);

                        pos_y += y_step;
                        pos_x = (640 - (strlen0x1a13b8(menu_msg[3]) * 10)) / 2;
                        font_print_ex0x161b80(pos_x, pos_y, 0, "%s", menu_msg[3]);
                    } else {
                        pos_x = (640 - (strlen0x1a13b8(menu_msg[0]) * 10)) / 2;
                        font_print_ex0x161b80(pos_x, pos_y, 0, "%s", menu_msg[0]);

                        pos_y += y_step;
                        pos_x = (640 - (strlen0x1a13b8(menu_msg[1]) * 10)) / 2;
                        font_print_ex0x161b80(pos_x, pos_y, 0, "%s", menu_msg[1]);
                    }

                    font_print_ex0x161b80(230, (pos_y + y_step), 0, "決定　　　キャンセル");

                    Disp_button0x163420(BUTTON_CIRCLE, 206, (pos_y + 22), 8, 1.0f);
                    Disp_button0x163420(BUTTON_CROSS, 306, (pos_y + 22), 8, 1.0f);

                    qty_msg = 2;
                    y_step = 96;
                    pos_y = 150;
                    menu_msg = game_menu_msg0x387a70;
                    break;
            }
            break;

        default:
            return;
    }

    flfntSetSize0x216890(24, 24);

    for (i = 0; i < qty_msg; i++) {
        pos_x = (640 - (strlen0x1a13b8(menu_msg[i]) * 12)) / 2;

        if (i == cursor) {
            palette_1 = 0;
            palette_2 = 2;
            Sel_csr_disp0x23b2e0(320, (pos_y - 3), 280, 32, 0xFF20C0C0);
        } else {
            palette_1 = 12;
            palette_2 = 1;
        }

        font_print_ex0x161b80((pos_x + 2), (pos_y + 2), palette_2, "%s", menu_msg[i]);
        font_print_ex0x161b80(pos_x, pos_y, palette_1, "%s", menu_msg[i]);

        pos_y += y_step;
    }

    font_reset0x1626c0();
}

void Sel_back_disp0x23af30(u32 brightness) {
    SPRITE sprite;
    u32 shade;

    SetFilterMode0x161500(1);
    reload_tex0x11f170(1, 7);
    SetTextureStage0x161550(7);

    shade = brightness & 0xFF;

    sprite.x = 0;
    sprite.y = 0;
    sprite.w = 640;
    sprite.h = 448;
    sprite.color = 0xFF000000 | (shade << 16) | (shade << 8) | shade;
    sprite.v0 = 0;
    sprite.u0 = 0;
    sprite.u1 = 255;
    sprite.v1 = 255;

    Put_2TF0x15b650(&sprite);
}

void Sel_menu_disp0x23afc0(s16 menu_id) {
    SPRITE sprite;
    s16* glyphs;
    s16 glyph;
    s16 pos_x;

    glyphs = menu_str0x349330[menu_id];

    if (menu_id == 4 || menu_id == 5) {
        pos_x = (640 - (menu_str_num0x349320[menu_id] * 32)) / 2;
        sprite.w = 32;
        sprite.h = 32;
    } else {
        pos_x = (640 - (menu_str_num0x349320[menu_id] * 48)) / 2;
        sprite.w = 48;
        sprite.h = 48;
    }

    if (menu_id == 3) {
        pos_x += 14;
    }

    SetFilterMode0x161500(1);

    sprite.y = 32;
    sprite.color = 0xFFFFFFFF;

    glyph = *glyphs;
    while (glyph != -1) {
        glyphs++;

        switch (glyph) {
            case 255:
                pos_x += 48;
                break;

            case 254:
                pos_x += 20;
                break;

            case 252:
                pos_x += 32;
                break;

            default:
                reload_tex0x11f170(1, 8);
                SetTextureStage0x161550(8);

                sprite.x = pos_x;
                sprite.u0 = (glyph & 7) * 32;
                sprite.v0 = (glyph / 8 * 32) + 48;
                sprite.u1 = sprite.u0 + 31;
                sprite.v1 = sprite.v0 + 31;
                Put_2TF0x15b650(&sprite);

                pos_x += sprite.w;
                break;
        }
        glyph = *glyphs;
    }

    sprite.x = 0;

    if (menu_id == 4 || menu_id == 5) {
        sprite.y = 64;
    } else {
        sprite.y = 80;
    }

    sprite.w = 255;
    sprite.h = 8;
    sprite.color = 0xFFFFFFFF;
    sprite.u0 = 0;
    sprite.v0 = 144;
    sprite.u1 = sprite.u0 + 255;
    sprite.v1 = sprite.v0 + 16;
    Put_2TF0x15b650(&sprite);

    sprite.x += 256;
    Put_2TF0x15b650(&sprite);

    sprite.x += 256;
    Put_2TF0x15b650(&sprite);
}

void Sel_csr_disp0x23b2e0(s16 pos_x, s16 pos_y, s16 width, s16 height, u32 color) {
    CURSOR_RECT rect;
    u16 phase;
    f32 pulse;
    s32 half_w;

    flSetRenderState0x177720(96, 0);
    SetTrnslMode0x161480(4, 5);

    phase = (System_timer0x38a1f4 & 0x3F) * 1024;
    pulse = flSin0x173600(0.0000958738f * phase);

    pos_x = 0.8f * pos_x;
    width = 0.8f * width;

    half_w = width / 2;

    rect.x0 = pos_x - half_w;
    rect.y0 = pos_y;
    rect.x1 = pos_x;
    rect.y1 = rect.y0 + height;

    rect.colors[0] = color & 0x00FFFFFF;
    rect.colors[1] = rect.colors[0] | (((s8) (48.0f * pulse) + 160) * 0x01000000);
    rect.colors[2] = rect.colors[0];
    rect.colors[3] = rect.colors[1];

    flps00050x175750(&rect);

    rect.x0 = rect.x1 + half_w;
    flps00050x175750(&rect);

    flSetRenderState0x177720(96, 0);
}

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_check0x23b4b0);

INCLUDE_ASM("asm/nonmatchings/main/modesel", disp_omake_menu0x23b500);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_init0x23b790);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_main0x23b810);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_play0x23ba80);

INCLUDE_ASM("asm/nonmatchings/main/modesel", omake_exit0x23bc90);

INCLUDE_ASM("asm/nonmatchings/main/modesel", Omake_task0x23bd00);
