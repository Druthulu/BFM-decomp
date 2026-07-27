#include "common.h"
typedef struct { s16 vx, vy, vz, pad; } SVEC;
typedef struct { s32 f0; s32 mode; s32 f8; u32 ofs; s32 n; } Obj;

extern Obj *D_801BF4F4;
extern SVEC *D_801C1E14;
extern SVEC *D_801C1E18;

void func_8017DC1C(s32 t) {
    Obj *o; SVEC *d; SVEC *pa; SVEC *pb; s32 i;
    o = D_801BF4F4;
    if (o->mode == 1) d = (SVEC *)o->ofs;
    else d = (SVEC *)((u32 *)&o->ofs + (o->ofs >> 2));
    pb = D_801C1E14;
    pa = D_801C1E18;
    for (i = o->n; i != 0; i--) {
        d->vx = pb->vx + (((pa->vx - pb->vx) * t) >> 12);
        d->vy = pb->vy + (((pa->vy - pb->vy) * t) >> 12);
        d->vz = pb->vz + (((pa->vz - pb->vz) * t) >> 12);
        pa++; pb++; d++;
    }
}
