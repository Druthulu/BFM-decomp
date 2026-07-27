#include "common.h"

/* SVECTOR-shaped keyframe element: 3 x s16 + pad, stride 8. */
typedef struct { s16 vx, vy, vz, pad; } SVECTOR2;

/* The morph target header the interpolated vertices are written into.
 * mode == 1  => `dst` at +0xC is a POINTER to the vertex block;
 * otherwise  => the vertex block is INLINE, `dst` at +0xC is a word count and
 *               the data starts at ((u32 *)&h->dst)[h->dst >> 2].
 * `n` at +0x10 is the vertex count in both cases. */
typedef struct {
    s32 unk0;      /* 0x00 */
    s32 mode;      /* 0x04 */
    s32 unk8;      /* 0x08 */
    u32 dst;       /* 0x0C */
    s32 n;         /* 0x10 */
} MorphObj;

/* ---- per-overlay globals (ov_SC07_006) ---------------------------------- */
extern MorphObj *D_801BF4F4;
extern MorphObj *D_801BF4F8;
extern MorphObj *D_801BF4FC;
extern MorphObj *D_801BF500;
extern MorphObj *D_801BF504;
extern MorphObj *D_801BF508;
extern MorphObj *D_801BF50C;
extern MorphObj *D_801BF510;
extern MorphObj *D_801BF514;
extern MorphObj *D_801BF518;
extern MorphObj *D_801BF51C;
extern MorphObj *D_801BF520;
extern MorphObj *D_801BF524;
extern MorphObj *D_801BF528;
extern MorphObj *D_801BF52C;
extern MorphObj *D_801BF530;
extern MorphObj *D_801BF534;
extern MorphObj *D_801BF538;
extern MorphObj *D_801BF650;
extern MorphObj *D_801BF65C;
extern MorphObj *D_801BF660;
extern MorphObj *D_801BF684;
extern MorphObj *D_801BF6A4;
extern MorphObj *D_801BF6A8;
extern MorphObj *D_801BF6AC;

extern SVECTOR2 *D_801C1E14;
extern SVECTOR2 *D_801C1E18;
extern SVECTOR2 *D_801C1E1C;
extern SVECTOR2 *D_801C1E20;
extern SVECTOR2 *D_801C1E24;
extern SVECTOR2 *D_801C1E28;
extern SVECTOR2 *D_801C1E2C;
extern SVECTOR2 *D_801C1E30;
extern SVECTOR2 *D_801C1E34;
extern SVECTOR2 *D_801C1E38;
extern SVECTOR2 *D_801C1E3C;
extern SVECTOR2 *D_801C1E40;
extern SVECTOR2 *D_801C1E44;
extern SVECTOR2 *D_801C1E48;
extern SVECTOR2 *D_801C1E4C;
extern SVECTOR2 *D_801C1E50;
extern SVECTOR2 *D_801C1E54;
extern SVECTOR2 *D_801C1E58;
extern SVECTOR2 *D_801C1E60;
extern SVECTOR2 *D_801C1E64;
extern SVECTOR2 *D_801C1E68;
extern SVECTOR2 *D_801C1E6C;
extern SVECTOR2 *D_801C1E70;
extern SVECTOR2 *D_801C1E74;
extern SVECTOR2 *D_801C1E78;
extern SVECTOR2 *D_801C1E7C;
extern SVECTOR2 *D_801C1E80;
extern SVECTOR2 *D_801C1E84;
extern SVECTOR2 *D_801C1E88;
extern SVECTOR2 *D_801C1E8C;
extern SVECTOR2 *D_801C1E90;
extern SVECTOR2 *D_801C1E94;
extern SVECTOR2 *D_801C1E98;
extern SVECTOR2 *D_801C1E9C;
extern SVECTOR2 *D_801C1EA0;
extern SVECTOR2 *D_801C1EA4;
extern SVECTOR2 *D_801C1EA8;
extern SVECTOR2 *D_801C1EAC;
extern SVECTOR2 *D_801C1EB0;


/* Interpolate `o`'s vertex block from keyframe `b` toward keyframe `a` by the
 * 1.12 fixed-point factor `t`.  MUST be `inline`: 25 expansions is what makes
 * this function 1518 instructions with zero `jal` and a 25 * 24 = 0x258 frame. */
static inline void morph_lerp(MorphObj *o, SVECTOR2 *b, SVECTOR2 *a, s32 t)
{
    SVECTOR2 *d;
    SVECTOR2 *pa;
    SVECTOR2 *pb;
    s32 i;

    if (o->mode == 1) {
        d = (SVECTOR2 *)o->dst;
    } else {
        d = (SVECTOR2 *)((u32 *)&o->dst + (o->dst >> 2));
    }
    i = o->n;
    pb = b;
    pa = a;
    for (; i != 0; i--) {
        d->vx = pb->vx + (((pa->vx - pb->vx) * t) >> 12);
        d->vy = pb->vy + (((pa->vy - pb->vy) * t) >> 12);
        d->vz = pb->vz + (((pa->vz - pb->vz) * t) >> 12);
        d++;
        pb++;
        pa++;
    }
}

void func_8017DC1C(s32 t)
{
    morph_lerp(D_801BF4F4, D_801C1E14, D_801C1E18, t);
    morph_lerp(D_801BF4F8, D_801C1E1C, D_801C1E1C, t);
    morph_lerp(D_801BF4FC, D_801C1E20, D_801C1E20, t);
    morph_lerp(D_801BF500, D_801C1E24, D_801C1E24, t);
    morph_lerp(D_801BF504, D_801C1E28, D_801C1E28, t);
    morph_lerp(D_801BF508, D_801C1E40, D_801C1E50, t);
    morph_lerp(D_801BF50C, D_801C1E44, D_801C1E54, t);
    morph_lerp(D_801BF510, D_801C1E48, D_801C1E58, t);
    morph_lerp(D_801BF514, D_801C1E4C, D_801C1E4C, t);
    morph_lerp(D_801BF518, D_801C1E60, D_801C1E60, t);
    morph_lerp(D_801BF51C, D_801C1E64, D_801C1E64, t);
    morph_lerp(D_801BF520, D_801C1E68, D_801C1E68, t);
    morph_lerp(D_801BF524, D_801C1E80, D_801C1E90, t);
    morph_lerp(D_801BF528, D_801C1E84, D_801C1E94, t);
    morph_lerp(D_801BF52C, D_801C1E88, D_801C1E98, t);
    morph_lerp(D_801BF530, D_801C1E8C, D_801C1E8C, t);
    morph_lerp(D_801BF534, D_801C1E9C, D_801C1E9C, t);
    morph_lerp(D_801BF538, D_801C1EA0, D_801C1EA4, t);
    morph_lerp(D_801BF650, D_801C1EA4, D_801C1EA8, t);
    morph_lerp(D_801BF65C, D_801C1E2C, D_801C1E38, t);
    morph_lerp(D_801BF660, D_801C1E30, D_801C1E3C, t);
    morph_lerp(D_801BF684, D_801C1EAC, D_801C1E34, t);
    morph_lerp(D_801BF6A4, D_801C1E6C, D_801C1E78, t);
    morph_lerp(D_801BF6A8, D_801C1E70, D_801C1E7C, t);
    morph_lerp(D_801BF6AC, D_801C1E74, D_801C1EB0, t);
}
