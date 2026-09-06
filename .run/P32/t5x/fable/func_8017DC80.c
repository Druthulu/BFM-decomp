/* func_8017DC80 — the D_8019B7B8 record table's POLY_G4 / LINE_G2 emitter.
 * ov_SC07_002, TU ov_SC07_002_jr_8017C8D0.  346 instructions.  MATCH (P32 T5x, fable).
 *
 * WHAT IT IS.  Ordinary gcc-2.7.2 -O2 C over the PsyQ inline_c.h GTE macros (the
 * splat "Handwritten function" banner is wrong).  It walks the 0xC0-entry
 * 0x38-stride table at D_8019B7B8; for every record whose low byte is >= 2 it
 *   - RTPTs v3(rec+4, rec+0xC, rec+0x14) + RTPS(rec+0x1C) into a POLY_G4 (0x24),
 *     or RTPTs v3(rec+4, rec+0x14, rec+0x14) into a LINE_G2 (0x14) when the s16
 *     at rec+0x0A (v0.pad, "mode") has bit 0x1000 set,
 *   - biases the OTZ by mode&0xFFF (0xC000 = subtract with clamp-to-0, else add),
 *   - drops it when flag&~0x1000 or otz >= 0x1000,
 *   - fills xy from the stack sxy words and rgb from rec[0x25], rec[0x27],
 *     rec[0x29] (or, when rec+0x34 links a record, that record's colours),
 *   - addPrim()s it into OT bucket D_800A6610[D_800B9A02 << 14] + otz*4 and
 *     chains a DR_TPAGE ((n<<5)&0x9FF)|0xE1000000 in front of it when n < 4.
 *
 * LEVERS INHERITED FROM THE T3 OPUS DRAFT (closeness 84 -> 46, see §500-C/D2):
 *  1. The GTE macros must be REAL macros (this TU's house block, suffixed _2).
 *  2. §30 /s lattice: plain-scalar sxy frame words, COMPONENT_REF packet stores.
 *  3. The derived pointers c/va/vb exist as pinned variables (plain r+k makes
 *     loop.c synthesise a fifth induction variable).
 *  4. The zero-byte `__asm__("" : "=r"(n), "=r"(otz) : "0"(n), "1"(otz))` launder
 *     retires cse1's cross-call unification of the OT index / n<4 test; its two
 *     copies carry identical `#line 900 "p.c"` so jump.c can cross-jump the
 *     POLY/LINE tails (ASM_OPERANDS rtx_equal_p compares file+line) — LOAD-BEARING.
 *
 * THE THREE MECHANISMS THAT CLOSED THE LAST 46 ROWS (each read from the -dS/-dR/
 * .combine/.greg dumps and the compiler source, not guessed):
 *
 *  A. FRAME 0x70 = TWO combine USE-ORPHANS (§172 producer 2), NOT reload pressure
 *     of a live value.  The record's mode halfword is an s16 READ FROM MEMORY at
 *     each use (`*(s16 *)(c - 0x1F) & 0xC000`, and `... & 0xFFF` in each clamp
 *     arm) — there is no `mode` variable.  mips.md:2340 extendhisi2 force_not_mem's
 *     the HImode load and promotes through `temp = m<<16; p = temp>>16`; the arm's
 *     `& 0xFFF` is C-shortened to an HImode AND `(and (subreg:SI m) 4095)`, so m has
 *     a second use; combine's 3-way merge makes the `lh` (added_sets_1,
 *     combine.c:1664 keeps m alive) and the ashift `temp` loses its setter —
 *     distribute_notes (combine.c ~10835) walks back to the `bnez flag` jump and
 *     emits `(insn (use (reg temp)))`; reload's alter_reg gives that never-referenced
 *     pseudo an 8-byte slot (align -1) — one per clamp block = +16 bytes at
 *     sp+0x38/0x40 that no instruction touches.  The same spelling re-materialises
 *     the HI value as the target's `addu $v1,$v0,$zero` copy instead of an `lhu`.
 *     (An `s16 mode` VARIABLE gives the frame but an `lhu` re-load: 34; an `s32 mode`
 *     variable gives frame 0x60 and no orphan: 46/54.)
 *
 *  B. THE DR_TPAGE BLOCK: ONE SCRATCH VARIABLE carries BOTH the len byte (1) and
 *     the tpage word.  sched.c's backward list scheduler prefers a ready memory
 *     insn at equal priority (schedule_select/potential_hazard), so a `sb` whose
 *     only successor is the tag load is picked right after it — the target instead
 *     places the whole tpage chain first.  With `tp = 1; q[3] = tp; ... tp = (n<<5
 *     & 0x9FF) | 0xE1000000; *(u32*)(q+4) = tp;` the `sb` reads the pseudo the
 *     `or` later sets: an ANTI-dependence keeps the `sb` unready until the chain
 *     is placed, `tp` is 2-set (no birthing boost, sched.c adjust_priority), and
 *     both values trivially share `$v1`.  `n` must be UNPINNED here: a hard-register
 *     `n` dying at `sll n,5` hands `$s0` to the tpage temp through local-alloc's
 *     dying-input suggestion (combine_regs); an unpinned `n` is a global allocno
 *     that local-alloc never ties, and global.c gives it `$s0` by itself.
 *     (Same idiom, banked: src/800.c:3826-3832.)
 *
 *  C. `la $a0, D_800AF648` FIRST IN THE PROLOGUE: sched2 is a backward list
 *     scheduler (sched.c schedule_block: each pick is linked BEFORE the previous
 *     one; rank_for_schedule ties -> the highest LUID is picked first), so the body
 *     insn with the LOWEST LUID lands first.  The address must therefore be
 *     materialised by the FIRST statement (`arg = &D_800AF648;`) — but combine
 *     substitutes cse's REG_EQUAL constant into the call-site copy and deletes the
 *     first set (measured: identical bytes to the plain call).  The zero-byte
 *     `__asm__("" : "=r"(arg) : "0"(arg))` blocks that substitution; the call's
 *     argument copy becomes a no-op and is deleted.
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
    u8 *arg;
    register u8 *c  __asm__("$18");
    register u8 *va __asm__("$21");
    register u8 *vb __asm__("$22");
    u32 ot;
    s32 n;
    register u32 otz __asm__("$17");
    register u32 mlo __asm__("$19");   /* 0x00FFFFFF — P_TAG addr mask  */
    register u32 mhi __asm__("$23");

    u32 *otp;
    PRIM_8017DC80 *poly;
    register u8 *q __asm__("$2");
    register u32 qt __asm__("$5");
    register u32 ov __asm__("$2");
    u32 tp;
    register u32 w __asm__("$3");
    s32 lo;

    s32 adj;
    s32 t;
    u32 cc;

    arg = &D_800AF648;
    __asm__("" : "=r"(arg) : "0"(arg));
    r  = (u8 *)&D_8019B7B8;
    mlo = 0xFFFFFF;
    mhi = 0xFF000000;
    c  = r + 0x29;
    va = r + 0x14;
    vb = r + 4;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_80052E38(arg);

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
                    otz = otzr;
                    adj = *(s16 *)(c - 0x1F) & 0xC000;
                    if (adj != 0) {
                        if (adj == 0xC000) {
                            otz -= *(s16 *)(c - 0x1F) & 0xFFF;
                            if ((s32)otz < 0) {
                                otz = 0;
                            }
                        } else {
                            otz += *(s16 *)(c - 0x1F) & 0xFFF;
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
                            tp = 1;
                            q[3] = tp;
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
                    otz = otzr;
                    adj = *(s16 *)(c - 0x1F) & 0xC000;
                    if (adj != 0) {
                        if (adj == 0xC000) {
                            otz -= *(s16 *)(c - 0x1F) & 0xFFF;
                            if ((s32)otz < 0) {
                                otz = 0;
                            }
                        } else {
                            otz += *(s16 *)(c - 0x1F) & 0xFFF;
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
                            tp = 1;
                            q[3] = tp;
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
