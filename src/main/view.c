#include "common.h"
#include "structs.h"

extern VIEW_WORK* lpView0x38a110;
extern VIEW_WORK view_work0x39da70;

void View_initialize0x1699e0(void) {
    lpView0x38a110 = &view_work0x39da70;
    lpView0x38a110->unk_38 = 0;
    lpView0x38a110->unk_3C = 0;
    lpView0x38a110->unk_40 = 0x200;
    lpView0x38a110->unk_44 = 0x1C0;
    lpView0x38a110->unk_48 = 0;
    lpView0x38a110->unk_4C = 1.0;
    View_init0x169a50();
}

INCLUDE_ASM("asm/main/nonmatchings/view", view_reset0x169a30);

INCLUDE_ASM("asm/main/nonmatchings/view", View_init0x169a50);

INCLUDE_ASM("asm/main/nonmatchings/view", View_move0x169a80);

INCLUDE_ASM("asm/main/nonmatchings/view", set_viewproj0x169c20);

INCLUDE_ASM("asm/main/nonmatchings/view", Create_FOV0x169cf0);

INCLUDE_ASM("asm/main/nonmatchings/view", set_aov0x169d20);

INCLUDE_ASM("asm/main/nonmatchings/view", RollView0x169da0);

INCLUDE_ASM("asm/main/nonmatchings/view", SetAngleOfView0x169db0);

INCLUDE_ASM("asm/main/nonmatchings/view", Get_dist_to_view0x169dc0);

INCLUDE_ASM("asm/main/nonmatchings/view", Get_view_dir0x169dd0);
