#ifndef COMMON_H
#define COMMON_H


#include "types.h"

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#define NULL 0

#define PI 3.1415927f
#define TAU 6.2831855f //2pi
#define USHORT_MAX_FLOAT 65536.0f
#define DEG2RAD  0.0000958738f //2pi / USHRT_MAX

#define SCREEN_RATIO 1.4285715 //640/448, used in projections

#define DEG_10_RAD 0.17453294f // 10º (PI/18)
#define DEG_45_RAD 0.78539820f // 45º (PI/4)
#define DEG_60_RAD 1.04719760f // 60º (PI/3)

#define PCH_ANGLE_STEP  0.022340214f // ~1.28° per frame

typedef f32 MATRIX[4][4];

#endif
