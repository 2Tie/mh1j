#include "common.h"

f32 cpAng2Rad0x120240(s32 ang) {
    //return 0.0000958738f * (f32) (arg0 & 0xFFFF);
    return (ang & 0xFFFF) * DEG2RAD;
}

void cpAng2Rad_all0x120270(s32 angs[], float rads[]) {
    rads[0] = cpAng2Rad0x120240(angs[0]);
    rads[1] = cpAng2Rad0x120240(angs[1]);
    rads[2] = cpAng2Rad0x120240(angs[2]);
}

INCLUDE_ASM("asm/main/nonmatchings/math", cpRotMatrix0x1202c0);

INCLUDE_ASM("asm/main/nonmatchings/math", cpRotMatrixYXZ20x120310);

INCLUDE_ASM("asm/main/nonmatchings/math", cpApplyMatrix0x120370);

INCLUDE_ASM("asm/main/nonmatchings/math", calc_vec_ang0x1203a0);

INCLUDE_ASM("asm/main/nonmatchings/math", calc_vec_ang20x120430);

INCLUDE_ASM("asm/main/nonmatchings/math", calc_mat_angY0x1204d0);

INCLUDE_ASM("asm/main/nonmatchings/math", RotMatVec0x120570);

INCLUDE_ASM("asm/main/nonmatchings/math", SetVector0x1207d0);

INCLUDE_ASM("asm/main/nonmatchings/math", PointToPoint0x1207e0);

INCLUDE_ASM("asm/main/nonmatchings/math", AddVector0x120820);

INCLUDE_ASM("asm/main/nonmatchings/math", SubVector0x120860);

INCLUDE_ASM("asm/main/nonmatchings/math", ScaleVector0x1208a0);

INCLUDE_ASM("asm/main/nonmatchings/math", UnitNormalVectorCCW0x1208d0);

INCLUDE_ASM("asm/main/nonmatchings/math", NormalClipF30x120960);

INCLUDE_ASM("asm/main/nonmatchings/math", NormalClipCheckF30x120a00);

INCLUDE_ASM("asm/main/nonmatchings/math", PointHitCheckF30x120ba0);

INCLUDE_ASM("asm/main/nonmatchings/math", NvecFloatAdjust0x120c80);

INCLUDE_ASM("asm/main/nonmatchings/math", RotateX0x120d40);

INCLUDE_ASM("asm/main/nonmatchings/math", RotateY0x120d90);

INCLUDE_ASM("asm/main/nonmatchings/math", RotateZ0x120de0);

INCLUDE_ASM("asm/main/nonmatchings/math", cpInterVector0x120e30);

INCLUDE_ASM("asm/main/nonmatchings/math", AarcTan20x120e80);

INCLUDE_ASM("asm/main/nonmatchings/math", nlCalcPoint0x120ec0);

INCLUDE_ASM("asm/main/nonmatchings/math", CalcDistanceXZ0x120f20);
