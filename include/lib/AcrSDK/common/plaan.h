#ifndef PLAAN_H
#define PLAAN_H

#include "types.h"
#include "common.h"

#define FCV_LINEAR_SHORT 0x11
#define FCV_HERMITE_SHORT 0x12
#define FCV_COMPLEX_SHORT 0x13
#define FCV_LINEAR 0x21
#define FCV_HERMITE 0x22
#define FCV_COMPLEX 0x23

typedef struct{
    u32 type;
    u32 children;
    u32 size;
} AAN_CONTAINER;

typedef struct{
    AAN_CONTAINER cont;
    u32 animtype;
    f32 loop;
} AAN_HEADER;

typedef struct{
    AAN_HEADER head;
    AAN_CONTAINER tags[];
} AAN;

#endif
