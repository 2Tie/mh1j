#include "common.h"

//protos
f32 cpAng2Rad0x120240(s32 ang);
void cpAng2Rad_all0x120270(s32 angs[], float rads[]);
f32* cpRotMatrix0x1202c0(s32 angs[], f32 mat[]);
f32* cpRotMatrixYXZ20x120310(s32 angs[], f32 mat[]);

void RotateX0x120d40(f32*, f32);
void RotateY0x120d90(f32*, f32);
void RotateZ0x120de0(f32*, f32);

extern void flmatInit0x171ce0(f32[]);
extern void flmatSetXYZ330x172140(f32[], f32, f32, f32);
extern void flvecApplyMat330x172e00(f32[], f32[], f32[]);
extern void flvecApplyMat0x172ee0(f32[], f32[], f32[]);
extern f32 flvecCalcLength0x1730f0(f32[]);
extern f32 flvecNormalize0x1731b0(f32[]);
extern f32 flvecInnerProduct0x173220(f32[], f32[]);
extern f32 flvecOuterProduct0x173280(f32[], f32[], f32[]);
extern void flvecCopy0x173300(f32[], f32[]);
extern f32 flAbs0x173540(f32);
extern f32 flArcTan20x1735e0(f32, f32);


//implement
f32 cpAng2Rad0x120240(s32 ang) {
    return (ang & 0xFFFF) * DEG2RAD;
}

void cpAng2Rad_all0x120270(s32 angs[], float rads[]) {
    rads[0] = cpAng2Rad0x120240(angs[0]);
    rads[1] = cpAng2Rad0x120240(angs[1]);
    rads[2] = cpAng2Rad0x120240(angs[2]);
}

f32* cpRotMatrix0x1202c0(s32 angs[], f32 mat[]) {
    f32 rads[3];

    cpAng2Rad_all0x120270(angs, rads);
    flmatInit0x171ce0(mat);
    flmatSetXYZ330x172140(mat, rads[0], rads[1], rads[2]);
    return mat;
}

f32* cpRotMatrixYXZ20x120310(s32 angs[], f32 mat[]) {
    f32 rads[3];

    cpAng2Rad_all0x120270(angs, rads);
    flmatInit0x171ce0(mat);

    RotateY0x120d90(mat, rads[1]);
    RotateX0x120d40(mat, rads[0]);
    RotateZ0x120de0(mat, rads[2]);
    return mat;
}

f32* cpApplyMatrix0x120370(f32 vec[], f32 scalar[], f32 mat[]) {
    flvecApplyMat330x172e00(mat, scalar, vec);
    return mat;
}

s32 calc_vec_ang0x1203a0(f32 v1x, f32 v1y, f32 v2x, f32 v2y) {
    f32 angle;
    f32 vector[3];

    vector[0] = v1x - v2x;
    vector[1] = 0;
    vector[2] = v1y - v2y;
    flvecNormalize0x1731b0(vector);
    angle = flArcTan20x1735e0(-vector[2], vector[0]);
    return (s32) (0.5f + ((65536.0f * angle) / 6.2831855f)) & 0xFFFF;
}

s32 calc_vec_ang20x120430(f32 vec1[], f32 vec2[]) {
    f32 angle;
    f32 vector[3];

    vector[0] = vec1[0] - vec2[0];
    vector[1] = 0;
    vector[2] = vec1[2] - vec2[2];
    flvecNormalize0x1731b0(vector);
    angle = flArcTan20x1735e0(-vector[2], vector[0]);
    return  (s32) (0.5f + ((65536.0f * angle) / 6.2831855f)) & 0xFFFF;
}

s32 calc_mat_angY0x1204d0(f32 inmat[]) {
    f32 angle;
    f32 scale[4];
    f32 outmat[4];

    scale[2] = 1.0;
    scale[3] = 1.0;
    scale[0] = 0.0;
    scale[1] = 0.0;

    flvecApplyMat0x172ee0(outmat, scale, inmat);
    angle = flArcTan20x1735e0(-(outmat[2] - inmat[14]), outmat[0] - inmat[12]);
    return (s32) (0.5f + ((65536.0f * angle) / 6.2831855f)) & 0xFFFF;
}

void RotMatVec0x120570(f32 inmat[], f32 outmat[], u8 axis) {
    f32 axisvec[4];
    f32 xmat[4];
    f32 ymat[4];
    f32 zmat[4];

    flvecNormalize0x1731b0(inmat);
    switch (axis) {
    case 0:
        axisvec[0] = 0;
        axisvec[1] = 0;
        axisvec[2] = 1;
        flvecOuterProduct0x173280(ymat, axisvec, inmat); //a0 is output, a1 and a2 input?
        if (flvecInnerProduct0x173220(ymat, ymat) < 0.001f) {
            axisvec[2] = 0;
            axisvec[0] = 1;
            flvecOuterProduct0x173280(ymat, axisvec, inmat);
        }
        flvecNormalize0x1731b0(ymat);
        flvecCopy0x173300(xmat, inmat);
        flvecOuterProduct0x173280(zmat, xmat, ymat);
        break;
    case 1:
        axisvec[0] = 0;
        axisvec[1] = 0;
        axisvec[2] = 1;
        flvecOuterProduct0x173280(xmat, inmat, axisvec);
        if (flvecInnerProduct0x173220(xmat, xmat) < 0.001f) {
            axisvec[2] = 0;
            axisvec[1] = 1;
            flvecOuterProduct0x173280(xmat, axisvec, inmat);
        }
        flvecNormalize0x1731b0(xmat);
        flvecCopy0x173300(ymat, inmat);
        flvecOuterProduct0x173280(zmat, xmat, ymat);
        break;
    case 2:
        axisvec[0] = 0;
        axisvec[1] = 1;
        axisvec[2] = 0;
        flvecOuterProduct0x173280(xmat, axisvec, inmat);
        if (flvecInnerProduct0x173220(xmat, xmat) < 0.001f) {
            axisvec[2]= 1;
            axisvec[1] = 0;
            flvecOuterProduct0x173280(xmat, inmat, axisvec);
        }
        flvecNormalize0x1731b0(xmat);
        flvecCopy0x173300(zmat, inmat);
        flvecOuterProduct0x173280(ymat, zmat, xmat);
        break;
    }
    flmatInit0x171ce0(outmat);
    flvecCopy0x173300(outmat, xmat);
    flvecCopy0x173300(&outmat[4], ymat);
    flvecCopy0x173300(&outmat[8], zmat);
}

void SetVector0x1207d0(f32 vec[], f32 mag1, f32 mag2, f32 mag3) {
    vec[0] = mag1;
    vec[1] = mag2;
    vec[2] = mag3;
}

void PointToPoint0x1207e0(f32 diff[], f32 point1[], f32 point2[]) {
    diff[0] = point1[0] - point2[0];
    diff[1] = point1[1] - point2[1];
    diff[2] = point1[2] - point2[2];
}

void AddVector0x120820(f32 sum[], f32 vec1[], f32 vec2[]) {
    sum[0] = vec1[0] - vec2[0];
    sum[1] = vec1[1] - vec2[1];
    sum[2] = vec1[2] - vec2[2];
}

void SubVector0x120860(f32 diff[], f32 vec1[], f32 vec2[]) {
    diff[0] = vec1[0] - vec2[0];
    diff[1] = vec1[1] - vec2[1];
    diff[2] = vec1[2] - vec2[2];
}

void ScaleVector0x1208a0(f32 scale, f32 out[], f32 in[]) {
    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
}

s32 UnitNormalVectorCCW0x1208d0(f32 point1[], f32 point2[], f32 point3[], f32 result[]) {
    f32 vector1[3];
    f32 vector2[3];

    PointToPoint0x1207e0(vector1, point1, point2);
    PointToPoint0x1207e0(vector2, point3, point2);
    flvecOuterProduct0x173280(result, vector2, vector1);
    flvecNormalize0x1731b0(result);
    if (flvecCalcLength0x1730f0(result) == 0.0f) {
        return 0;
    }
    return 1;
}

f32 NormalClipF30x120960(f32 vert1[], f32 vert2[], f32 vert3[]) {
    u32 v[2];
    f32 vec[2];

    vec[0] = (vert2[0] - vert1[0]) * (vert3[1] - vert1[1]);
    vec[1] = (vert3[0] - vert1[0]) * (vert2[1] - vert1[1]);

    v[0] = *(s32*)&vec[0];
    v[1] = *(s32*)&vec[1];

    if (v[0] == (v[1] + 1)) {
        vec[0] = vec[1];
    }
    if (v[0] == (v[1] - 1)) {
        vec[0] = vec[1];
    }
    return vec[0] - vec[1];
}

INCLUDE_ASM("asm/main/nonmatchings/math", NormalClipCheckF30x120a00);

INCLUDE_ASM("asm/main/nonmatchings/math", PointHitCheckF30x120ba0);

void NvecFloatAdjust0x120c80(f32 out[], f32 in[]) {
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    if (flAbs0x173540(in[0]) < 0.001f) {
        out[0] = 0;
    }
    if (flAbs0x173540(in[1]) < 0.001f) {
        out[1] = 0;
    }
    if (flAbs0x173540(in[2]) < 0.001f) {
        out[2] = 0;
    }
}

INCLUDE_ASM("asm/main/nonmatchings/math", RotateX0x120d40);

INCLUDE_ASM("asm/main/nonmatchings/math", RotateY0x120d90);

INCLUDE_ASM("asm/main/nonmatchings/math", RotateZ0x120de0);

INCLUDE_ASM("asm/main/nonmatchings/math", cpInterVector0x120e30);

INCLUDE_ASM("asm/main/nonmatchings/math", AarcTan20x120e80);

INCLUDE_ASM("asm/main/nonmatchings/math", nlCalcPoint0x120ec0);

INCLUDE_ASM("asm/main/nonmatchings/math", CalcDistanceXZ0x120f20);
