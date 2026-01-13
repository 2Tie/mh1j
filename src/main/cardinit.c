#include "common.h"
#include "structs.h"
#pragma cats off

extern CARD_WORK card_w0x531880;
CARD_WORK card_w20x390880;

extern SYSTEM_WORK system_w0x3f3690;

void Card_task0x100e20(void) {
    return;
}

void init_card_w0x100e30(void) {
    memset0x19dd28(&card_w0x531880, 0, 0x84);
    memset0x19dd28(&card_w20x390880, 0, 0x84);
    system_w0x3f3690.mc_access = 0;
}

s32 save_file_req0x100e80(void) {
    return 1;
}
