#ifndef COMMON_H
#define COMMON_H

#include "types.h"

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#define NULL 0

#define PI 3.1415927f
#define TAU 6.2831855f //2pi
#define USHORT_MAX_FLOAT 65536.0f
#define DEG2RAD  (2*PI/USHORT_MAX_FLOAT) // 0.0000958738f
#define RAD2DEG (USHORT_MAX_FLOAT/(2*PI)) // 10430.378f 0x4622f983

#define ONETHIRD (1.0f/3.0f)

#define ERROREPSILON (1.0e-6) // cardano uses this

#define SCREEN_RATIO 1.4285715 // 640/448, used in projections

#define DEG_10_RAD 0.17453294f // 10º 0x3E32B8C3
#define DEG_30_RAD (PI/6) // 30º 0x3F060A92 0.52359879f
#define DEG_45_RAD (PI/4) // 45º 0x3F490FDB 0.78539820f
#define DEG_50_RAD 0.87266463f // 50º 0x3F5F66F3
#define DEG_55_RAD 0.95993110f // 55º 0x3F75BE0B
#define DEG_60_RAD (PI/3) // 60º 0x3F860A92 1.04719760f

#define DEG_67_5_RAD (3*PI/8) //67.5º 1.17809725

#define PCH_ANGLE_STEP  0.022340214f // ~1.28° per frame

typedef f32 MATRIX[4][4];
typedef f32 VEC4[4]; 
typedef f32 VEC3[3];

#endif
