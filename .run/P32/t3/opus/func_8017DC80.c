/* func_8017DC80 — the D_8019B7B8 record table's POLY_G4 / LINE_G2 emitter.
 * ov_SC07_002, TU ov_SC07_002_jr_8017C8D0.  346 instructions.
 *
 * WHAT IT IS.  The splat banner "Handwritten function" is WRONG (as the prior
 * §265 VERBATIM-ASM bank in this TU already suspected): this is ordinary
 * gcc-2.7.2 -O2 C over the PsyQ inline_c.h GTE macros.  It walks the 0xC0-entry
 * 0x38-stride table at D_8019B7B8; for every record whose low byte is >= 2 it
 *   - RTPTs v3(rec+4, rec+0xC, rec+0x14) + RTPS(rec+0x1C) into a POLY_G4 (0x24),
 *     or RTPTs v3(rec+4, rec+0x14, rec+0x14) into a LINE_G2 (0x14) when the mode
 *     halfword at rec+0x0A has bit 0x1000 set,
 *   - biases the OTZ by mode&0xFFF (0xC000 = subtract with clamp-to-0, else add),
 *   - drops it when flag&~0x1000 or otz >= 0x1000,
 *   - fills the packet's xy from the stack sxy words and its rgb from rec[0x25],
 *     rec[0x27], rec[0x29] — or, when rec+0x34 holds a linked record, the second
 *     colour pair from that record's +0x25/+0x27/+0x29,
 *   - addPrim()s it into OT bucket D_800A6610[D_800B9A02 << 14] + n*4 and chains
 *     a DR_TPAGE ((n<<5)&0x9FF)|0xE1000000 in front of it when n < 4.
 *
 * THE FOUR LEVERS THAT TOOK THIS FROM "-33 LENGTH DRIFT" TO EXACT LENGTH
 * (the TU's ~20 earlier drafts plateaued because of #1, and the pack's own body
 *  still carries that defect):
 *
 *  1. THE GTE MACROS MUST BE REAL MACROS.  Undefined gte_*() compile to implicit
 *     `jal`s — that alone is the historic length wall.  These are this TU's own
 *     house spelling (the file-scope block at L2701-2818 and the `_1` block at
 *     L7010), with a `_2` suffix so they collide with neither.  gte_stsxy0/
 *     gte_stsxy1 (a single `swc2 $12`/`$13`) and gte_avsz4 are the two this TU
 *     had not needed before; gte_stszotz (mfc2 $19 + sra 2) already existed.
 *
 *  2. §30's `/s`-DEPENDENCE LATTICE decides the sxy schedule.  The frame words
 *     must be PLAIN SCALARS (no `/s`, fixed address) and the packet stores must
 *     be COMPONENT_REFs through a struct pointer (`/s`, varying address); only
 *     then does sched.c's drop clause let each `lw 0xNN($sp)` rise past the
 *     previous group's `sh`.  Spell the sxy locals inside a struct, or spell the
 *     packet stores as `*(s16 *)(poly + 8)`, and every load-delay slot fills with
 *     a `nop` instead (measured: 344->346 ins and the whole block reorders).
 *
 *  3. ONE POINTER, NOT FOUR "REAL" ONES — but PINNED.  `c`/`va`/`vb` must exist
 *     as C variables pinned to $s2/$s5/$s6 ... plain `r + k` expressions make
 *     loop.c synthesise a FIFTH induction variable at r+0x27 and `ot` then spills.
 *
 *  4. THE OT INDEX AND THE `n < 4` TEST ARE COMPUTED TWICE.  cse1 unifies them
 *     across the `func_80010A08(8)` call (a call invalidates memory and hard
 *     registers, never pseudos — cse.c:7241/invalidate_for_call), and the value
 *     then wants a tenth callee-saved register.  The zero-byte
 *     `__asm__ ("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz))` retires both pseudos
 *     so the second copy is re-emitted.  The `#line` pairs are LOAD-BEARING: the
 *     POLY and LINE tails are cross-jumped into one block (the target's two
 *     `j .L8017E0E0`), and jump.c compares ASM_OPERANDS with rtx_equal_p, which
 *     includes the source FILE and LINE — without the directives the two launders
 *     differ, the merge is lost and the function grows by 13 instructions.
 *
 * RESIDUAL (46 of 346, exact length, all register-allocation / prologue-schedule):
 *   - frame 0x60 vs 0x70.  vars = 40 vs 56: same 28 bytes of declared scalars and
 *     the same 8-byte `i` spill at sp+0x30, but the target carries TWO MORE
 *     8-byte reload slots (sp+0x38, sp+0x40) that its own code never touches.
 *     Not reachable from C: a dead local always takes sp+0x10 (aggregates get
 *     their slot at expand_decl, before any `&`-driven scalar slot — measured),
 *     so the delta is reload pressure, not a declaration.  Costs the 10 prologue
 *     `sw` / 10 epilogue `lw` displacements and the two `addiu $sp`.
 *   - `la $a0, D_800AF648` is scheduled first in the target and 14th here; every
 *     other prologue insn is already in the target's order.
 *   - `t` lands in $v1 (mm's register, which dies at the `andi`) where the target
 *     reuses $v0, and the DR_TPAGE temp reuses $s0 for the same reason — two
 *     local-alloc dest-ties-dying-source decisions.  Pinning `t` to $2 drags the
 *     `andi` back above the `ori` (+2 ins); pinning the DR_TPAGE word to $3 costs
 *     12.  Both measured INERT/worse — [permuter] class.
 *
 * (The same tie on `w` IS breakable: `register u32 w __asm__("$3")` stops `w`
 *  from being coalesced into `n`'s pinned $s0 and restores lhu/andi/srl $v1.)
 *
 * DECLARATIONS: every symbol is spelled from this target's own relocation lines
 * and matches the TU (D_8019B7B8 file-scope at L3176, D_800B9A02 at L2468); the
 * block-scoped externs copy func_80185434's/func_80183FE0's spellings in this
 * same file, so nothing leaks into the rest of the TU.
 */

#define gte_ldv0_2(r0) __asm__ volatile (        \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_ldv3_2(r0, r1, r2) __asm__ volatile (\
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps_2()  __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt_2()  __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4_2() __asm__ volatile ("nop;nop;avsz4")

#define gte_stsxy_2(r0) __asm__ volatile (       \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy0_2(r0) __asm__ volatile (      \
    "swc2 $12, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy1_2(r0) __asm__ volatile (      \
    "swc2 $13, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stsxy3_2(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stotz_2(r0) __asm__ volatile (       \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stszotz_2(r0) __asm__ volatile (     \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg_2(r0) __asm__ volatile (       \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

extern s32 D_8019B7B8;

/* The primitive laid out as a real struct: the COMPONENT_REF stores carry
 * MEM_IN_STRUCT_P (`/s`) at a VARYING address, the sxy/flag frame slots are plain
 * non-`/s` scalars at a FIXED address, and sched.c's `/s` drop clause (§30 lattice)
 * therefore lets each `lw` rise past the previous group's `sh`.  LINE_G2 is the
 * first 0x14 bytes of the same layout. */
typedef struct {
    u8  t0, t1, t2, len;   /* 0x00  P_TAG      */
    u8  r0, g0, b0, code;  /* 0x04             */
    s16 x0, y0;            /* 0x08             */
    u8  r1, g1, b1, p1;    /* 0x0C             */
    s16 x1, y1;            /* 0x10             */
    u8  r2, g2, b2, p2;    /* 0x14             */
    s16 x2, y2;            /* 0x18             */
    u8  r3, g3, b3, p3;    /* 0x1C             */
    s16 x3, y3;            /* 0x20 -> 0x24     */
} PRIM_8017DC80;

void func_8017DC80(void)
{
    extern void func_80052E38(void *);
    extern void *func_80010A08(s32);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern short D_800B9A02;

    long flag;      /* sp+0x10 */
    long sxy0;      /* sp+0x14 */
    long sxy1;      /* sp+0x18 */
    long sxy2;      /* sp+0x1C */
    long flag2;     /* sp+0x20 */
    long sxy3;      /* sp+0x24 */
    long otzr;      /* sp+0x28 */
    s32 i;

    register u8 *r  __asm__("$20");
    register u8 *c  __asm__("$18");
    register u8 *va __asm__("$21");
    register u8 *vb __asm__("$22");
    u32 ot;
    register s32 n __asm__("$16");
    register u32 otz __asm__("$17");
    register u32 mlo __asm__("$19");   /* 0x00FFFFFF — P_TAG addr mask  */
    register u32 mhi __asm__("$23");
    register s32 zr  __asm__("$0");
    register s32 mm  __asm__("$3");   /* 0xFF000000 — P_TAG len/code   */
    u32 *otp;
    PRIM_8017DC80 *poly;
    register u8 *q __asm__("$2");
    register u32 qt __asm__("$5");
    register u32 ov __asm__("$2");
    u32 tp;
    register u32 w __asm__("$3");
    s32 lo;
    register s32 mode __asm__("$2");
    s32 adj;
    s32 t;
    u32 cc;

    r  = (u8 *)&D_8019B7B8;
    mlo = 0xFFFFFF;
    mhi = 0xFF000000;
    c  = r + 0x29;
    va = r + 0x14;
    vb = r + 4;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_80052E38(&D_800AF648);

    for (i = 0; i < 0xC0; i++) {
        w = *(u16 *)r;
        lo = w & 0xFF;
        if (lo >= 2) {
            n = w >> 8;
            if ((*(u16 *)(c - 0x1F) & 0x1000) == 0) {
                poly = (PRIM_8017DC80 *)func_80010A08(0x24);
                poly->len = 8;          /* setlen(poly, 8)   */
                poly->code = 0x38;      /* setcode POLY_G4   */
                gte_ldv3_2(vb, r + 0xC, va);
                gte_rtpt_2();
                gte_stflg_2(&flag);
                gte_stsxy3_2(&sxy0, &sxy1, &sxy2);
                gte_ldv0_2(r + 0x1C);
                gte_rtps_2();
                gte_stflg_2(&flag2);
                flag = flag | flag2;
                gte_stsxy_2(&sxy3);
                gte_avsz4_2();
                gte_stotz_2(&otzr);
                if ((flag & 0xFFFFEFFF) == 0) {
                    mode = *(s16 *)(c - 0x1F);
                    otz = otzr;
                    adj = mode & 0xC000;
                    if (adj != 0) {
                        mm = mode + zr;
                        t = mm & 0xFFF;
                        if (adj == 0xC000) {
                            otz -= t;
                            if ((s32)otz < 0) {
                                otz = 0;
                            }
                        } else {
                            otz += t;
                        }
                    }
                    if (otz < 0x1000) {
                        poly->x0 = sxy0;
                        poly->y0 = sxy0 >> 16;
                        poly->x1 = sxy1;
                        poly->y1 = sxy1 >> 16;
                        poly->x2 = sxy2;
                        poly->y2 = sxy2 >> 16;
                        poly->x3 = sxy3;
                        poly->y3 = sxy3 >> 16;
                        if (*(u32 *)(c + 0xB) != 0) {
                            cc = c[-4];
                            poly->r1 = cc;
                            poly->r0 = cc;
                            cc = c[-2];
                            poly->g1 = cc;
                            poly->g0 = cc;
                            cc = c[0];
                            poly->b1 = cc;
                            poly->b0 = cc;
                            cc = *(u8 *)(*(u32 *)(c + 0xB) + 0x25);
                            poly->r3 = cc;
                            poly->r2 = cc;
                            cc = *(u8 *)(*(u32 *)(c + 0xB) + 0x27);
                            poly->g3 = cc;
                            poly->g2 = cc;
                            cc = *(u8 *)(*(u32 *)(c + 0xB) + 0x29);
                            poly->b3 = cc;
                            poly->b2 = cc;
                        } else {
                            cc = c[-4];
                            poly->r3 = cc;
                            poly->r2 = cc;
                            poly->r1 = cc;
                            poly->r0 = cc;
                            cc = c[-2];
                            poly->g3 = cc;
                            poly->g2 = cc;
                            poly->g1 = cc;
                            poly->g0 = cc;
                            cc = c[0];
                            poly->b3 = cc;
                            poly->b2 = cc;
                            poly->b1 = cc;
                            poly->b0 = cc;
                        }
                        if (n < 4) {
                            poly->code |= 2;
                        }
                        otp = (u32 *)(otz << 2);
                        otp = (u32 *)((u32)otp + ot);
                        *(u32 *)poly = (*(u32 *)poly & mhi) | (*otp & mlo);
                        ov = *otp;
                        *otp = (ov & mhi) | ((u32)poly & mlo);
#line 900 "p.c"
                        __asm__ ("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz));
#line 901 "p.c"
                        if (n < 4) {
                            q = (u8 *)func_80010A08(8);
                            q[3] = 1;
                            qt = *(u32 *)q;
                            tp = ((n << 5) & 0x9FF) | 0xE1000000;
                            *(u32 *)(q + 4) = tp;
                            otp = (u32 *)(otz << 2);
                            otp = (u32 *)((u32)otp + ot);
                            *(u32 *)q = (qt & mhi) | (*otp & mlo);
                            *otp = (*otp & mhi) | ((u32)q & mlo);
                        }
                    }
                }
            } else {
                poly = (PRIM_8017DC80 *)func_80010A08(0x14);
                poly->len = 4;          /* setlen(poly, 4)   */
                poly->code = 0x50;      /* setcode LINE_G2   */
                gte_ldv3_2(vb, va, va);
                gte_rtpt_2();
                gte_stsxy0_2(&sxy0);
                gte_stsxy1_2(&sxy1);
                gte_stflg_2(&flag);
                gte_stszotz_2(&otzr);
                if ((flag & 0xFFFFEFFF) == 0) {
                    mode = *(s16 *)(c - 0x1F);
                    otz = otzr;
                    adj = mode & 0xC000;
                    if (adj != 0) {
                        mm = mode + zr;
                        t = mm & 0xFFF;
                        if (adj == 0xC000) {
                            otz -= t;
                            if ((s32)otz < 0) {
                                otz = 0;
                            }
                        } else {
                            otz += t;
                        }
                    }
                    if (otz < 0x1000) {
                        poly->x0 = sxy0;
                        poly->y0 = sxy0 >> 16;
                        poly->x1 = sxy1;
                        poly->y1 = sxy1 >> 16;
                        if (*(u32 *)(c + 0xB) != 0) {
                            poly->r0 = c[-4];
                            poly->g0 = c[-2];
                            poly->b0 = c[0];
                            poly->r1 = *(u8 *)(*(u32 *)(c + 0xB) + 0x25);
                            poly->g1 = *(u8 *)(*(u32 *)(c + 0xB) + 0x27);
                            poly->b1 = *(u8 *)(*(u32 *)(c + 0xB) + 0x29);
                        } else {
                            cc = c[-4];
                            poly->r1 = cc;
                            poly->r0 = cc;
                            cc = c[-2];
                            poly->g1 = cc;
                            poly->g0 = cc;
                            cc = c[0];
                            poly->b1 = cc;
                            poly->b0 = cc;
                        }
                        if (n < 4) {
                            poly->code |= 2;
                        }
                        otp = (u32 *)(otz << 2);
                        otp = (u32 *)((u32)otp + ot);
                        *(u32 *)poly = (*(u32 *)poly & mhi) | (*otp & mlo);
                        ov = *otp;
                        *otp = (ov & mhi) | ((u32)poly & mlo);
#line 900 "p.c"
                        __asm__ ("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz));
#line 901 "p.c"
                        if (n < 4) {
                            q = (u8 *)func_80010A08(8);
                            q[3] = 1;
                            qt = *(u32 *)q;
                            tp = ((n << 5) & 0x9FF) | 0xE1000000;
                            *(u32 *)(q + 4) = tp;
                            otp = (u32 *)(otz << 2);
                            otp = (u32 *)((u32)otp + ot);
                            *(u32 *)q = (qt & mhi) | (*otp & mlo);
                            *otp = (*otp & mhi) | ((u32)q & mlo);
                        }
                    }
                }
            }
        }
        c  += 0x38;
        va += 0x38;
        vb += 0x38;
        r  += 0x38;
    }
}
#line 3360 "src/ov_SC07_002/ov_SC07_002_jr_8017C8D0.c"
