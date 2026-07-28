/* func_80176734 (371 ins, ov_SC01_077_jr_801734BC, reach-138 core) — wave23 pass
 *
 * SCORE (match_one, asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801734BC):
 *   wave22 seed .run/wave22/func_80176734.c   : 366 ins, closeness 217 (LENGTH-DRIFT -5)
 *   Phase-27 fable seed .run/giants/*.fable.c : 370 ins, closeness 111 (LENGTH-DRIFT -1)
 *   THIS FILE                                 : 371 ins, closeness  13, 13 real (masked, aligned)
 *   sibling .run/near6/wave23/x2.c            : 371 ins, closeness  14, 11 real  <- fewest REAL diffs
 * Length now EXACT (371/371); all callee-saved assignments, the frame (0x40), region 1,
 * regions 4/5/6, the switch, the whole D_80126CE0 / adjust / tail regions are byte-exact.
 *
 * FOUR LEVERS APPLIED THIS PASS (each byte-measured, all pin-free / generic-constraint):
 *
 * 1. NEW IDIOM — "the LOG_LINK next-use-only combine block" (the missing instruction).
 *    gcc-2.7.2 always expands `x = (a != b)` as `xor t; sne temp; move x,temp`
 *    (expmed.c:3978 `preserve_subexpressions_p()` is TRUE at -O2, so emit_store_flag always
 *    writes a fresh subtarget then copies).  combine then merges the sne+copy whenever the
 *    temp dies at the copy — which is why every draft was 1 insn SHORT here.
 *    flow.c:2085-2091 builds a LOG_LINK only from a SET to the *NEXT FOLLOWING USE* of that
 *    reg, and only inside the same basic block.  So one extra USE of the temp placed BETWEEN
 *    the sne and the copy moves the link off the copy: combine never sees the pair, both
 *    instructions survive, and NOTHING is emitted:
 *        tA = (st1->unk47 != b);
 *        __asm__("" :: "r"(tA));      <-- steals the LOG_LINK
 *        flag = tA;
 *    Crucially the anchor must go BEFORE the copy: placed after it (the Phase-27 fable v22
 *    attempt) it also blocks reorg from stealing the copy into the `j` delay slot (+1 nop,
 *    net 0).  Measured: closeness 111 -> 26.  A basic-block split (`goto`/label between the
 *    two) also defeats combine — proven at 372 ins — but costs the arm's extra `j`.
 *
 * 2. cse qty-head steering (`make_regs_eqv`, cse.c:826) for the `unk47 == 0x80` re-test.
 *    After `bne tB,w` falls through, record_jump_equiv merges the two regs; the class head
 *    (and hence the register the NEXT test reads) becomes `w` iff w's regno_last_uid is later.
 *    Routing the load through the function-wide scratch tB AND giving tB a later last mention
 *    (`tB = w; st1->unk47 = tB;` in the last adjust arm) keeps tB the head: 26 -> 23.
 *
 * 3. Head-init placement.  `st1` MUST stay a decl-initializer: moved into the body it loses
 *    the update_equiv_regs live-length doubling (local-alloc.c:1064), its allocno priority
 *    (global.c:594) explodes and the whole callee-saved bank rotates (frame 0x40 -> 0x48,
 *    +1 insn — measured on 12 permutations).  Moving only `st2`/`ext` into the body, after the
 *    index chain and the `self = arg0` copy, reproduces the target's save/init interleave:
 *    23 -> 15.
 *
 * 4. RC-15 density anchor on an explicit region-2 base pointer
 *    (`s32 base = (((s32)self<<16)>>14) + (s32)g; __asm__("" :: "r"(base));`) — the extra ref
 *    lifts the base allocno over the store temp, landing it in $a0 and making both
 *    `lw $a1,0x28($a0)` reloads exact: 15 -> 13 (real 13 -> 11 in the x2 spelling).
 *
 * RESIDUAL (13 positions here / 11 in x2.c), three clusters, all allocation/schedule ties:
 *   a) entry: `sw s1 / addiu s1,s3,0x48` scheduled one slot group off (sched2 LUID tie that
 *      is COUPLED to lever 3 — st1's LUID is pinned by the priority constraint).  4 positions.
 *   b) region 2: `d` (= st2->unk48, a cross-block => GLOBAL allocno) and the store temp swap
 *      $v1<->$a1.  local-alloc gives the block-local store temp $v1 before global.c ever sees
 *      `d`; this is the named "local-vs-global allocation tie" (regalloc.md §H).  5 positions.
 *   c) region 3: `e` in $a0 vs $a1 (same tie).  2 positions.
 *   In p3 (this file) the region-1 `q` also takes $a2 instead of $a0 — that one is fixed in
 *   x2.c (put `self = arg0` before `q`), at the cost of the entry order; the two are coupled
 *   through when the `move s6,a0` frees $a0 at sched1 time.
 *
 * PIN-FREE / x138-safe: three generic-constraint identity/anchor asms (tB re-opaque for the
 * cse.c:7511 fall-through delete, the tA LOG_LINK steal, the base density anchor) and the
 * fable-era `fl` tail anchor.  No `register __asm__("$N")` pins anywhere.
 *
 * What it does: per-track BGM/SFX state tick. g=&D_8011F7A8 (sound globals), st1/st2 = two
 * SndSt state blocks inside it (+0x48/+0xE0), ext=&D_80078E78 (the engine-side SndSt).
 * Region 1: master volume fade write to trk[arg0] (+4/+0x40). Region 2/3: unk48 state machine
 * (fade-step table D_8018A2D8, program change via func_800183E0). Region 4: unk2E pan/tempo
 * mirror + unk49 table. Region 5: unk1E 0x8000 flag toggle. Region 6: D_800B9A13 mode-change
 * detect (changed). Switch: ext->unk48 in {3,4,5,6} -> fade checks -> flag = 0xFF/0xBA. Then
 * volume ramp toward w (D_80126CE0 override or ext->unk47) with -3/-8 decay steps, and the
 * func_801775E0(trk+0x64, ...) tail.
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
    SndSt *st2;
    SndSt *ext;
    s32 flag;      /* s0 */
    s32 changed;   /* s5 */
    s32 tA;        /* v0 scratch, reused */
    s32 tB;        /* v1 scratch, reused */
    s32 w;         /* a1 */
    u8 h;
    s16 self;
    s8 pad[4];

    {
        Trk *e;
        Trk *q;
        self = arg0;                 /* K8/RC-4 lifetime shaping: arg0's LAST use moved ABOVE q's
                                        birth, so $a0 is dead when q is born and K3 first-fit gives
                                        q $a0 instead of $a2 (target idx24 `addiu $a0,$a1,0x3C`). */
        e = g->trk[arg0];
        q = (Trk *)((u8 *)e + 0x3C);
        st2 = &g->st2;
        ext = &D_80078E78;
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
        s32 base = (((s32)self << 16) >> 14) + (s32)g;
        __asm__("" :: "r"(base));
        (*(Trk **)(base + 0x28))->unkD = D_8018A2D8[st2->unk48];
        if (st2->unk48 >= 4) {
            u8 c = st1->unk48;
            Trk *e = *(Trk **)(base + 0x28);
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
            __asm__("" :: "r"(tA));
            flag = tA;
        } else {
            w = ext->unk47;
            flag = 0;
            tB = st1->unk47;
            if (tB != w || tB == 0x80) {
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
        tB = st1->unk47;
        if (tB < (s16)w) {
            st1->unk47 = w;
        } else {
            if ((s16)w != 0) {
                tA = tB - 3;
                st1->unk47 = tA;
            } else {
                tA = tB - 8;
                st1->unk47 = tA;
            }
            if (st1->unk47 == 0 || st1->unk47 >= 0x81) {
                st1->unk47 = 0;
                st1->unk4B = 0;
            } else if ((s32)st1->unk47 < (s16)w) {
                tB = w;
                st1->unk47 = tB;
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
