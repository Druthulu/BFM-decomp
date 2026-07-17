// @class: regalloc-order
// @stuck: close=116/260 (ins count 260/260 + frame 0x50 vars=16/args=24/regs=10 + every prologue
// offset EXACT). Residual: gcc LICM hoists the INNER-loop constants 8 and 0xFFFFFF all the way to
// the OUTER preheader into callee regs ($s7/$s4) -- combine_movables merges the `8` with the outer
// `func_80140D68(...,8,...)` arg -- stealing the two callee regs the target gives to const-3 ($fp)
// and &D_801879BE ($s6). Knock-on: 3 is rematerialized inline (`li $t4,3` x2) so CSE learns k==3 and
// constant-folds k*2/k*4 to `li 6`/`li 12` instead of the target's `sll $t3,$v1,2`/`sll $v0,$a3,1`.
// Not C-steerable from here: the py->$s6 pin backfires (S27 caveat: 262 ins/228), explicit masks
// (171), k4 inline (222), k as s32 (182), every store-order permutation (118-175) are all WORSE.
// -> permuter fuel (regalloc/LICM placement space).

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

typedef struct { u32 addr : 24; u32 len : 8; } P_TAG;

#define getaddr(p)      ((u32)(((P_TAG *)(p))->addr))
#define setaddr(p, a)   (((P_TAG *)(p))->addr = (u32)(a))
#define addPrim(ot, p)  (setaddr(p, getaddr(ot)), setaddr(ot, p))

typedef struct {
    u32 tag;
    u32 rgbc;
    s16 x0, y0;
    u8  u0, v0;
    u16 clut;
    s16 w, h;
} Sprt;

extern u16 D_80115110[];
#define D_80115112  (D_80115110[1])
#define D_80115116  (D_80115110[3])
#define D_8011511A  (D_80115110[5])
#define D_80115128  (((s16 *)D_80115110)[12])
#define D_8011512E  (((s16 *)D_80115110)[15])
extern u8  D_80115140[];
extern u8  D_80115143;
extern u8  D_8011514E;
extern u8  D_80115158[];
extern u8  D_8011516A[];
extern void *D_80187A80[];
extern s16 D_80187E9C[];
extern s16 D_80187EAC[];
extern u8  D_8018793C[];
extern u8  D_8018798C[];
extern u16 D_801879BC;
extern u16 D_801879BE;
extern u16 D_800B9A02;
extern u8  D_800AE7BC[];

extern s32 func_8014168C(s32 a0);
extern u32 *func_80140D68(u32 *a0, void *a1, s32 a2, s32 a3, s32 a4);

u32 *func_80140958(u32 *ot, short idx, short n) {
    if (idx < n) {
        u16 *py = &D_801879BE;
        do {
            if (D_80115110[0] == 0 && D_80115112 != 3 && D_80115112 < 6) {
                if (idx == D_8011511A) {
                    ot = func_80140D68(ot, &D_8018793C[idx * 4], idx,
                                       D_80187E9C[D_80115116 & 7], 0);
                }
            } else {
                void *pk = D_80187A80[idx];
                if (pk != 0 && idx == D_8011511A && idx != 6) {
                    s32 v;
                    if (idx == 2 && D_80115128 != 0) {
                        pk = D_8018798C;
                    }
                    if (idx == 3) {
                        v = (D_8011514E - D_80115143) * 2;
                    } else {
                        v = func_8014168C(idx) * 2;
                    }
                    ot = func_80140D68(ot, pk, idx, D_80187EAC[D_80115116 & 7], (s16)v);
                    if (idx == 2 && D_80115128 == 1 && D_8011512E != 0) {
                        ot = func_80140D68(ot, pk, 2, 8, (D_8011512E & 0xF) * 2);
                    }
                }
            }
            if (idx == 3) {
                u16 k = D_8011511A;
                if (k == 3 && (D_80115116 & 8) != 0) {
                    short i;
                    u16 *pn = &D_800B9A02;
                    s32 k2 = k * 2;
                    s32 k4 = k * 4;
                    for (i = 0; i < 2; i++) {
                        Sprt *p = (Sprt *)ot;
                        s32 nn;
                        u32 *q;
                        if (i == 0) {
                            if (D_80115140[k] == 0) continue;
                            p->v0 = 0x30;
                            p->y0 = *py - 4;
                        } else {
                            if ((s8)D_80115158[k2] - (s8)D_80115140[k] < 2) continue;
                            p->v0 = 0x38;
                            p->y0 = *py + 3;
                        }
                        p->tag = 0x4000000;
                        p->rgbc = 0x64808080;
                        p->u0 = 0x78;
                        p->clut = 0x4056;
                        p->x0 = D_801879BC + *(u16 *)&D_8011516A[k4] + 0x4A;
                        p->h = 8;
                        p->w = 8;
                        nn = (u32)*pn * 0x14;
                        q = (u32 *)(*(s32 *)&D_800AE7BC[nn] + 8);
                        setaddr(ot, getaddr(q));
                        nn = (u32)*pn * 0x14;
                        q = (u32 *)(*(s32 *)&D_800AE7BC[nn] + 8);
                        setaddr(q, ot);
                        ot += 5;
                    }
                }
            }
            idx++;
        } while (idx < n);
    }
    return ot;
}
