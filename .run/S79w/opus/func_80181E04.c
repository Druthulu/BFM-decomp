#include "common.h"

/* func_80181E04 (ov_SC01_001, 269 ins) - MATCH.
 *
 * splat labels this "handwritten" only because of the `cfc2` in gte_stflg; the
 * prologue/epilogue and the whole body are ordinary gcc-2.7.2 -O2 output (no $s
 * register is touched because both `jal`s precede the loop, so every loop value
 * lives happily in a call-clobbered temp).
 *
 * Four levers, in the order they were needed:
 *
 * 1. §246-2 PARALLEL GLOBALS SHARE ONE giv. The target reaches sixteen distinct
 *    D_801EDA?? symbols as `lui $at,%hi(sym); addu $at,$at,$a2; lw/sw %lo(sym)($at)`
 *    off ONE 0x50-stride byte-offset giv ($a2). Declaring every one of them as an
 *    array of a common 0x50-byte record type (field at +0) makes giv-combine fuse all
 *    of them onto that single IV -- and unlike the plain `s32 sym[]` + `sym[i*20]`
 *    spelling it folds for the STORES too. §200 aliases (`__asm__("D_801EDA4C")`)
 *    keep the TU's own `extern s32 D_801EDA4C[]` decls untouched.
 *    The six `lhu` reads are the SAME record type with a u16 at +0, aliased onto the
 *    +2 half-word symbols the linker script already exports (D_801EDA4E/52/56/72/76/7A).
 *
 * 2. THE COUNTED LOOP, NOT THE POINTER WALK. `i < 0x100` lets loop.c eliminate the
 *    biv in favour of the &D_801EDA44[i] address giv, and it emits the derived bound
 *    INSIDE the loop (`lui/addiu` are re-materialised every iteration at .L80182208
 *    because biv elimination runs after invariant motion). The reloc becomes
 *    D_801EDA44+0x5000, which links to the identical 0x801F2A44 bytes as the target's
 *    %hi/%lo(D_801F2A44). Spelling the bound as `&D_801F2A44` instead costs +12.
 *
 * 3. THE ROUNDING IS SOURCE-LEVEL, THE SHIFT IS NOT. The target's `bgez/addiu 7` sits
 *    BEFORE the packet stores and its `sra` AFTER them. A single `z / 8` cannot split
 *    like that (the whole div sequence is emitted at one point); `if (z < 0) z += 7;`
 *    then `(z >> 3) * 4 + (s32)ot` at the use site reproduces both halves, and the
 *    `lui 0xE100` falls into the bgez delay slot for free. Writing `(u32 *)ot + z/8`
 *    instead reverses the final `addu` operands.
 *
 * 4. THE OT INSERT IS A 24-BIT BITFIELD STORE, NOT A HAND-MASKED WORD. This is what
 *    the last 18 instructions turned on. Hand-written as
 *      `*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (*otp & 0xFFFFFF);`
 *    gcc evaluates the destination mask first, so 0xFF000000 hoists BEFORE 0xFFFFFF
 *    and the $a0/$v1/$a1 roles come out permuted (18 mismatched, all regalloc).
 *    Spelled as PsyQ's P_TAG `addr:24` bitfield, store_bit_field masks the VALUE first
 *    and then `expand_binop(ior, temp, value)` -- which fixes, in one edit, (a) the
 *    0xFFFFFF-before-0xFF000000 movable hoist order, (b) both `or` operand orders, and
 *    (c) the whole $a1/$v1/$a0 allocation. A local `register ... __asm__("$3")` pin on
 *    the OT pointer is INERT here (gcc-2.7.2 only honours a local reg var at an asm
 *    that references it) -- the bitfield spelling is the real lever.
 *
 * The packet is a 0x18-byte custom prim: tag, an inline GP0(E1) draw-mode word, then a
 * semi-transparent gouraud LINE_G2 body (code 0x52) whose two vertices come straight
 * from gte_stsxy01 into +0xC / +0x14.
 */

/* ---- GTE inline-asm macros (same spelling as the matched ov_SC03_099 TU) ---- */
#define gte_ldv3_80181E04(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt_80181E04() __asm__ volatile ("nop;nop;rtpt")

#define gte_stflg_80181E04(r0) __asm__ volatile (\
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stsxy01_80181E04(r0, r1) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 )                       \
    : "memory" )

#define gte_stsz3_80181E04(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

/* §246-2: every parallel global spelled as an array of one 0x50-byte record type so
 * gcc fuses all their address computations onto ONE scaled-offset giv. §200 aliases
 * keep the TU's own `extern s32 D_801EDA4C[]` spellings untouched. */
typedef struct { u32 addr:24; u32 len:8; } PTag_80181E04;
typedef struct { s32 v; u8 pad[0x4C]; } W50_80181E04;
typedef struct { u16 h; u8 pad[0x4E]; } H50_80181E04;

extern W50_80181E04 wD801EDA44[] __asm__("D_801EDA44");
extern W50_80181E04 wD801EDA48[] __asm__("D_801EDA48");
extern W50_80181E04 wD801EDA4C[] __asm__("D_801EDA4C");
extern W50_80181E04 wD801EDA50[] __asm__("D_801EDA50");
extern W50_80181E04 wD801EDA54[] __asm__("D_801EDA54");
extern W50_80181E04 wD801EDA58[] __asm__("D_801EDA58");
extern W50_80181E04 wD801EDA70[] __asm__("D_801EDA70");
extern W50_80181E04 wD801EDA74[] __asm__("D_801EDA74");
extern W50_80181E04 wD801EDA78[] __asm__("D_801EDA78");
extern W50_80181E04 wD801EDA7C[] __asm__("D_801EDA7C");
extern W50_80181E04 wD801EDA80[] __asm__("D_801EDA80");
extern W50_80181E04 wD801EDA84[] __asm__("D_801EDA84");
extern W50_80181E04 wD801EDA88[] __asm__("D_801EDA88");
extern W50_80181E04 wD801EDA8C[] __asm__("D_801EDA8C");
extern W50_80181E04 wD801EDA90[] __asm__("D_801EDA90");
extern H50_80181E04 hD801EDA4E[] __asm__("D_801EDA4E");
extern H50_80181E04 hD801EDA52[] __asm__("D_801EDA52");
extern H50_80181E04 hD801EDA56[] __asm__("D_801EDA56");
extern H50_80181E04 hD801EDA72[] __asm__("D_801EDA72");
extern H50_80181E04 hD801EDA76[] __asm__("D_801EDA76");
extern H50_80181E04 hD801EDA7A[] __asm__("D_801EDA7A");

extern void func_800547D8(s32, MATRIX2 *);
extern void func_80052E38(MATRIX2 *);
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern s16 D_801F3168;

void func_80181E04(void)
{
    MATRIX2 mtx;                                /* sp+0x10 */
    SVECTOR2 va;                                /* sp+0x30 */
    SVECTOR2 vb;                                /* sp+0x38 */
    struct { s32 flag, sz0, sz1, sz2; } g;      /* sp+0x40 */
    u8 *pkt;
    u8 *ot;
    u32 *otp;
    s32 i;
    s32 z;

    func_800547D8((s32)&D_801F3168, &mtx);
    func_80052E38(&mtx);

    ot = &D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    pkt = D_800A5E60;

    for (i = 0; i < 0x100; i++) {
        if (wD801EDA44[i].v != 0) {
            va.vx = hD801EDA4E[i].h;
            va.vy = hD801EDA52[i].h;
            va.vz = hD801EDA56[i].h;
            vb.vx = hD801EDA72[i].h;
            vb.vy = hD801EDA76[i].h;
            vb.vz = hD801EDA7A[i].h;

            wD801EDA4C[i].v += wD801EDA7C[i].v;
            wD801EDA50[i].v += wD801EDA80[i].v;
            wD801EDA54[i].v += wD801EDA84[i].v;
            if (wD801EDA48[i].v == 0) {
                wD801EDA70[i].v += wD801EDA7C[i].v;
                wD801EDA74[i].v += wD801EDA80[i].v;
                wD801EDA78[i].v += wD801EDA84[i].v;
            } else {
                wD801EDA48[i].v = wD801EDA48[i].v - 1;
            }
            wD801EDA7C[i].v += wD801EDA88[i].v;
            wD801EDA80[i].v += wD801EDA8C[i].v;
            wD801EDA84[i].v += wD801EDA90[i].v;

            if (wD801EDA7C[i].v > 0) {
                if (wD801EDA4C[i].v > wD801EDA58[i].v) {
                    wD801EDA44[i].v = 0;
                }
            } else {
                if (wD801EDA4C[i].v < wD801EDA58[i].v) {
                    wD801EDA44[i].v = 0;
                }
            }

            if (wD801EDA44[i].v != 0) {
                gte_ldv3_80181E04(&va, &vb, &vb);
                gte_rtpt_80181E04();
                gte_stflg_80181E04(&g.flag);
                if ((g.flag & 0x7F85E000) == 0) {
                    gte_stsxy01_80181E04(pkt + 0xC, pkt + 0x14);
                    gte_stsz3_80181E04(&g.sz0, &g.sz1, &g.sz2);
                    z = g.sz0 + g.sz1;
                    if (z < 0) {
                        z += 7;
                    }
                    pkt[3] = 5;
                    pkt[0xB] = 0x52;
                    pkt[9] = 0xE0;
                    pkt[0xA] = 0x88;
                    pkt[0x10] = 0x40;
                    pkt[0x11] = 0x60;
                    *(u32 *)(pkt + 4) = 0xE1000020;
                    pkt[8] = 0;
                    pkt[0x12] = 0x10;
                    otp = (u32 *)((z >> 3) * 4 + (s32)ot);
                    ((PTag_80181E04 *)pkt)->addr = ((PTag_80181E04 *)otp)->addr;
                    ((PTag_80181E04 *)otp)->addr = (u32)pkt;
                    pkt += 0x18;
                }
            }
        }
    }
    D_800A5E60 = pkt;
}
