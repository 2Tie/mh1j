#ifndef PLAHI_H
#define PLAHI_H

typedef struct{
    u32 tag;
    u32 children;
    u32 size;
} TAG_CONTAINER;

typedef struct{
    TAG_CONTAINER cont;
} AHI;

#endif
