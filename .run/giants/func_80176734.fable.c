/* func_80176734 (371 ins, ov_SC01_077_jr_801734BC, reach-134 core) — Fable5 pin-free draft
 *
 * Closeness: mine=370 vs target=371 ins; match_one positional 111 (cascade-inflated by the
 * 1 missing insn); REAL aligned diff ~81 lines, of which the true instruction deltas are
 * ~30 positions in 5 LOCAL clusters (see func_80176734.fable.md):
 *   entry-schedule order, region-1/2/3 caller-saved shuffles (e/q/base a0-a1-v0-v1),
 *   region-8 [sltu][copy] combine-merge (the 1 missing insn) + h/const v0-v1 swap.
 * ALL callee-saved assignments byte-exact (flag=s0 st1=s1 st2=s2 g=s3 ext=s4 changed=s5 arg0=s6),
 * frame size exact (0x40), whole LBF0/adjust/tail regions byte-exact.
 *
 * PIN-FREE / x134-safe: ONE generic-constraint identity asm on tB (cse.c:7511 fall-through
 * jump-equiv would otherwise delete the target's provably-dead `beqz v1` branch); everything
 * else is pure C. No register __asm__("$N") pins anywhere.
 *
 * What it does: per-track BGM/SFX state tick. g=&D_8011F7A8 (sound globals), st1/st2 = two
 * SndSt state blocks inside it (+0x48/+0xE0), ext=&D_80078E78 (the engine-side SndSt).
 * Region 1: master volume fade write to trk[arg0] (+4/+0x40). Region 2/3: unk48 state machine
 * (fade-step table D_8018A2D8, program change via func_800183E0). Region 4: unk2E pan/tempo
 * mirror + unk49 table. Region 5: unk1E 0x8000 flag toggle (two one-shot commands). Region 6:
 * D_800B9A13 mode-change detect (changed). Switch: ext->unk48 in {3,4,5,6} -> fade checks
 * (func_801619D0/A00/A30/A60) -> flag = 0xFF/0xBA. Then volume ramp toward w (D_80126CE0
 * override or ext->unk47) with -3/-8 decay steps, and the func_801775E0(trk+0x64, ...) tail.
 */
#include "common.h"

typedef struct Trk {
    u8   pad00[4];
    u8   unk4;           /* 0x04 */
    u8   pad05[8];
    u8   unkD;           /* 0x0D */
    u8   pad0E[0x12];
    u16  unk20;          /* 0x20 */
    u8   pad22[0x10];
    s16  unk32;          /* 0x32 */
    u8   pad34[0xC];
    u8   unk40;          /* 0x40 */
    u8   pad41[8];
    u8   unk49;          /* 0x49 */
    u8   pad4A[0x1A];
    u8   unk64;          /* 0x64 */
} Trk;

typedef struct SndSt {
    u8   pad00[0x1E];
    s16  unk1E;          /* 0x1E */
    u8   pad20[0xE];
    s16  unk2E;          /* 0x2E */
    u8   pad30[0x17];
    u8   unk47;          /* 0x47 */
    u8   unk48;          /* 0x48 */
    u8   pad49[2];
    u8   unk4B;          /* 0x4B */
    u8   pad4C[0x4C];    /* size 0x98 */
} SndSt;

typedef struct SndGlob {
    u8    pad00[7];
    u8    unk7;          /* 0x07 */
    u8    unk8;          /* 0x08 */
    u8    pad09[9];
    u16   unk12;         /* 0x12 */
    u8    pad14[0x14];
    Trk  *trk[8];        /* 0x28 */
    SndSt st1;           /* 0x48 */
    SndSt st2;           /* 0xE0 */
} SndGlob;

extern SndGlob D_8011F7A8;
extern SndSt   D_80078E78;

extern s16 D_801152BA;
extern u8  D_8011F7B0;
extern u8  D_80115214;
extern u8  D_800B9A13;
extern u16 D_8018A238;
extern u8  D_8018A2D8[];
extern u16 D_8018A22A[];
extern void *D_8018A2E4[];
extern u8  D_8018A2CC[];
extern s16 D_80126D20;
extern s16 D_80126CE0;
extern s32 D_80126B58;
extern u8  D_800D45D4[];
extern u8  D_800D43D4[];
extern u8  D_800D4414[];

extern void func_800183E0(void *);
extern s32 func_801619D0(void *);
extern s32 func_80161A00(void *);
extern s32 func_80161A30(void *);
extern s32 func_80161A60(void *);
extern void func_801775E0(u8 *, s16);

void func_80176734(arg0)
s16 arg0;
{
    SndGlob *g = &D_8011F7A8;
    SndSt *st1 = &g->st1;
    SndSt *st2 = &g->st2;
    SndSt *ext = &D_80078E78;
    s32 flag;      /* s0 */
    s32 changed;   /* s5 */
    s32 tA;        /* v0 scratch, reused */
    s32 tB;        /* v1 scratch, reused */
    s32 w;         /* a1 */
    u8 h;
    s16 self;
    s8 pad[4];

    {
        Trk *e = g->trk[arg0];
        Trk *q = (Trk *)((u8 *)e + 0x3C);
        self = arg0;
        if (D_801152BA != 0) {
            u8 b = D_8011F7B0;
            u8 v;
            if (b < 0x80U) {
                v = b - 0x80;
            } else {
                v = ~b - 0x80;
            }
            q->unk4 = v;
            e->unk4 = v;
            g->unk8 = g->unk8 + D_80115214;
        } else {
            e->unk40 = 0x80;
            e->unk4 = 0x80;
        }
    }

    if (st2->unk48 != 0) {
        g->trk[self]->unkD = D_8018A2D8[st2->unk48];
        if (st2->unk48 >= 4) {
            u8 c = st1->unk48;
            Trk *e = g->trk[self];
            if (c & 0x80) {
                e->unk20 = D_8018A238;
                func_800183E0(D_800D45D4);
            } else if (c != 0) {
                e->unk20 = D_8018A22A[c];
                func_800183E0(D_8018A2E4[st1->unk48]);
            }
            {
                u8 d = st2->unk48;
                if (d == 5) {
                    if (st1->unk48 == 0) {
                        st2->unk48 = 0;
                    } else {
                        st2->unk48 = d + 1;
                    }
                } else if (d == 0xA) {
                    st2->unk48 = 0;
                } else {
                    st2->unk48 = d + 1;
                }
            }
        } else {
            st2->unk48++;
        }
    } else {
        if (st1->unk48 != ext->unk48) {
            if (st1->unk48 == 0 && ext->unk48 != 0) {
                st2->unk48 = 5;
            } else {
                st2->unk48 = 0;
            }
            st1->unk48 = ext->unk48;
            {
                Trk *e = g->trk[self];
                u8 t = st2->unk48;
                st2->unk48 = t + 1;
                e->unkD = D_8018A2D8[t];
            }
        }
    }

    if (st1->unk2E == ext->unk2E) {
        if (st2->unk2E != 0) {
            st2->unk2E = 0;
            goto upd49;
        }
    } else {
        st1->unk2E = ext->unk2E;
        st2->unk2E = 1;
upd49:
        tB = (u16)st1->unk2E;
        tB = tB << 16;
        {
            Trk *e = g->trk[self];
            if (tB != 0) {
                e->unk49 = D_8018A2CC[tB >> 20];
            } else {
                e->unk49 = 0xA0;
            }
        }
    }

    {
        s32 f1 = st1->unk1E & 0x8000;
        if (f1 != (ext->unk1E & 0x8000)) {
            if (f1 != 0) {
                st1->unk1E = 0;
                func_800183E0(D_800D43D4);
            } else {
                st1->unk1E = -0x8000;
                func_800183E0(D_800D4414);
            }
        }
    }

    {
        u8 m = D_800B9A13;
        if (m != 3) {
            tA = (g->unk7 != m);
            changed = tA;
            if (tA != 0) {
                g->unk7 = m;
            }
        } else {
            changed = 0;
        }
    }

    flag = 0;
    switch (ext->unk48) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) flag = 0xFF;
        break;
    case 4:
        if (func_80161A00(&D_80126B58) != 0) flag = 0xFF;
        break;
    case 5:
        if (func_80161A30(&D_80126B58) != 0) flag = 0xFF;
        break;
    case 6:
        if (func_80161A60(&D_80126B58) != 0) flag = 0xBA;
        break;
    }

    tA = flag;
    if (tA != 0) {
        st2->unk47 = 1;
        st1->unk4B = ext->unk48 | 0xF0;
        st1->unk47 = (D_80126D20 << 7) / tA;
    } else {
        if (st1->unk4B >= 0xF0) {
            st1->unk4B = 0;
        }
        w = *(u16 *)&D_80126CE0;
        if (D_80126CE0 != 0) {
            u8 b = w;
            st1->unk4B = b;
            tA = (st1->unk47 != b);
            flag = tA;
        } else {
            w = ext->unk47;
            flag = 0;
            if (st1->unk47 != w || st1->unk47 == 0x80) {
                flag = 1;
            }
            if (ext->unk47 != 0 && st1->unk4B != 0) {
                st1->unk4B = 0;
                st1->unk47 = ext->unk47;
            }
        }

        tB = changed;
        if (flag != 0) goto adjust;
        if (tB != 0) goto adjust;
        if (st2->unk47 == 0) goto posttail;
        __asm__("" : "=r"(tB) : "0"(tB));
        if (tB == 0) goto clear;
adjust:
        h = st1->unk47;
        if ((s32)h < (s16)w) {
            st1->unk47 = w;
        } else {
            if ((s16)w != 0) {
                tA = h - 3;
                st1->unk47 = tA;
            } else {
                tA = h - 8;
                st1->unk47 = tA;
            }
            if (st1->unk47 == 0 || st1->unk47 >= 0x81) {
                st1->unk47 = 0;
                st1->unk4B = 0;
            } else if ((s32)st1->unk47 < (s16)w) {
                st1->unk47 = w;
            }
        }
        st2->unk47 = 1;
        goto posttail;
clear:
        st2->unk47 = 0;
posttail:;
    }

    {
        s32 fl = (g->unk7 != 0) << 8;
        s32 k = fl + 5;
        __asm__("" :: "r"(fl));
        g->trk[self]->unk32 = g->unk12 + k;
        fl += 9;
        func_801775E0(&g->trk[self]->unk64, g->unk12 + fl);
    }
}
