/* func_80185810 (ov_SC03_105, sub ov_SC03_105_jr_80181C84) -- 489 ins.
 *
 * COMPILER-EMITTED gcc-2.7.2 -O2 C using PsyQ GTE inline-asm macros.  splat's
 * "Handwritten function" banner is WRONG: ordinary prologue/epilogue (frame 0x80,
 * $s0-$s4+$ra at 0x68..0x7C), if/else diamonds with `j` over the else arm,
 * jal + delay-slot calls, load-delay nops -- every COP2 op comes from a macro.
 *
 * Draws one billboard sprite for the actor at a0:
 *   - builds the rot/trans matrix (3 paths: no object -> identity at D_800AF630+0x18;
 *     flag 0x800000 set -> rotate the object's own 3x3 at +0x34 column by column;
 *     clear -> func_80185FB4 fills it, then rotate that),
 *   - RTPS the actor position, rejects it outside +-200 / +-160 screen units,
 *   - RTPT the two extent vectors through the D_801BC9B4 scale matrix,
 *   - fills a 0x28-byte packet off the D_800A5E60 bump allocator (tag/code/uv/clut/
 *     tpage/xy) and links it into the OT at &D_800A6610[state << 14].
 *
 * STATUS: exact length (489/489), every register allocation matches, 35 masked
 * mismatches remain -- all of them pure sched1/sched2 EMISSION ORDER inside four
 * windows of one 50-insn basic block (the packet fill).  See the trailing note.
 *
 * LEVERS THAT MATTERED (each measured; the count in parens is the mismatch total
 * after applying it, from 133 at exact length):
 *  1. `base = D_800AF630;` as a LOCAL (the house idiom, cf. func_80021D38 in
 *     src/800.c) -- gcc will not hoist a symbol address used in 3 different basic
 *     blocks into $s4 by itself.
 *  2. The `w` packet word is ONE expression at its store, not a `w |= ...` chain:
 *     a C variable with 5 sets is never `birthing_insn_p` (cookbook S49), so its
 *     defining insns are un-boosted and float to the FRONT of the block; single-set
 *     sub-expressions sink to the end, which is where the target has them. (93)
 *  3. `(tp + 0x100) << 6` must be a TWO-USE temp `tb`.  With one use, combine folds
 *     it to `(tp << 6) | 0x4010` (nonzero_bits knows the lbu is <= 0xFF) and the
 *     `addiu` disappears.  A second use blocks the fold.
 *  4. Statement-order brute force (cookbook index line 25) on the two independent
 *     store groups: 0x10/0x1A/0x12/0x18 and 0x14/0x15/0x1C/0x1D. (76 -> 67)
 *  5. `uu = (uu - ...) << (2 - mode)` as ONE statement fixes `mode`'s register;
 *     splitting it back into two AFTER the fence below fixes `uu`'s. (64, 39)
 *  6. A zero-byte scheduling fence `__asm__ volatile("")` after `p[7] |= ...`
 *     (S194-A family): it is the only lever found that puts the $a0-$a3 quartet
 *     (uu/mode/ot/cl) on the target's registers -- without it the whole packet
 *     block rotates one register up and drags $t0/$t1/$t2 with it. (67 -> 49)
 *  7. `ot16` (the D_800AF630[0xA3D2] read) split from `ob` (the &D_800A6610[..<<14]
 *     address) so the read stays before the fence and the address after. (49 -> 47)
 *  8. `cl &= 0xFFFF` IN PLACE rather than into a second variable: the separate
 *     pseudo took $t0 and pushed every later caller-saved allocno up one. (39 -> 35)
 *
 * MEASURED INERT (do not re-run): swapping the `ob + (otz<<2)` operand order or
 * spelling it `(otz<<2) + (s32)ob` / via an `oi` temp; all 6 orders of the
 * ot16/uu/cl load statements; all 9 placements of the D_801BA6B0 read across the
 * coordinate block; `u16`/`s32`/`(u16)` spellings of cl; a `shf = 2 - mode` temp at
 * 4 positions; `u32` vs `s32` for uu/mode/w; every other fence position (20 tried).
 */

#ifndef BFM_ENGINE_TYPES_H
typedef struct { short m[3][3]; long t[3]; } MATRIX_80188114;
#endif

extern u8 D_800AF630[];
extern MATRIX_80188114 D_801BC9B4;
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern u8 D_801BA6B0;
extern void func_80185FB4(s32 a0, s32 a1, s32 a2);
extern void func_8001F730(s32 a0, void *a1, void *a2);

#define gte_SetRotMatrix_85810(r0) __asm__ volatile (    \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix_85810(r0) __asm__ volatile (  \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldclmv_85810(r0) __asm__ volatile (          \
    "lhu $12, 0( %0 );"                                  \
    "lhu $13, 6( %0 );"                                  \
    "lhu $14, 12( %0 );"                                 \
    "mtc2 $12, $9;"                                      \
    "mtc2 $13, $10;"                                     \
    "mtc2 $14, $11"                                      \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_rtir_85810() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0")

#define gte_stclmv_85810(r0) __asm__ volatile (          \
    "mfc2 $12, $9;"                                      \
    "mfc2 $13, $10;"                                     \
    "mfc2 $14, $11;"                                     \
    "sh $12, 0( %0 );"                                   \
    "sh $13, 6( %0 );"                                   \
    "sh $14, 12( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14", "memory" )

#define gte_ldlvl_85810(r0) __asm__ volatile (           \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )

#define gte_rt_85810() __asm__ volatile ("nop;nop;mvmva 1, 0, 0, 0, 0")

#define gte_stlvnl_85810(r0) __asm__ volatile (          \
    "swc2 $25, 0( %0 );"                                 \
    "swc2 $26, 4( %0 );"                                 \
    "swc2 $27, 8( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_ldv0_85810(r0) __asm__ volatile (            \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 )"                                   \
    :                                                    \
    : "r"( r0 ) )

#define gte_rtps_85810() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy_85810(r0) __asm__ volatile (           \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stsz_85810(r0) __asm__ volatile (            \
    "swc2 $19, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_ldv3_85810(r0, r1, r2) __asm__ volatile (    \
    "lwc2 $0, 0( %0 );"                                  \
    "lwc2 $1, 4( %0 );"                                  \
    "lwc2 $2, 0( %1 );"                                  \
    "lwc2 $3, 4( %1 );"                                  \
    "lwc2 $4, 0( %2 );"                                  \
    "lwc2 $5, 4( %2 )"                                   \
    :                                                    \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt_85810() __asm__ volatile ("nop;nop;rtpt")

#define gte_stsxy0_85810(r0) __asm__ volatile (          \
    "swc2 $12, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stsxy1_85810(r0) __asm__ volatile (          \
    "swc2 $13, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

#define gte_stflg_85810(r0) __asm__ volatile (           \
    "cfc2 $12, $31;"                                     \
    "nop;"                                               \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

#define gte_stszotz_85810(r0) __asm__ volatile (         \
    "mfc2 $12, $19;"                                     \
    "nop;"                                               \
    "sra $12, $12, 2;"                                   \
    "sw $12, 0( %0 )"                                    \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "memory" )

void func_80185810(s32 a0)
{
    typedef struct { u16 vx, vy, vz, pad; } UV_85810;
    typedef struct { short m[3][3]; long t[3]; } MTX_85810;

    UV_85810  v[5];        /* sp+0x10 .. sp+0x37 */
    MTX_85810 m;           /* sp+0x38 */
    long sz;               /* sp+0x58 */
    long flag;             /* sp+0x5C */
    long otz;              /* sp+0x60 */
    u8 *base;
    u8 *p;
    u8 *ob;
    u32 ot16;
    s32 *q;
    u32 flags;
    s32 spr;
    s32 t0;
    s32 sx;
    s32 sy;
    u32 mode;
    u32 w;
    u32 uu;
    u32 cl;
    u32 tp;

    base  = D_800AF630;
    flags = *(u32 *)a0;
    spr   = *(s32 *)(a0 + 0x24);

    if (*(s32 *)(a0 + 0x20) != 0) {
        if (flags & 0x800000) {
            gte_SetRotMatrix_85810(base + 0x18);
            gte_ldclmv_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x34));
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][0]);
            gte_ldclmv_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x36));
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][1]);
            gte_ldclmv_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x38));
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][2]);
            gte_SetTransMatrix_85810(base + 0x18);
            gte_ldlvl_85810((u8 *)(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x48));
            gte_rt_85810();
            gte_stlvnl_85810(&m.t[0]);
        } else {
            func_80185FB4(*(s32 *)(*(s32 *)(a0 + 0x20) + 0x20), flags, (s32)&m);
            gte_SetRotMatrix_85810(base + 0x18);
            gte_ldclmv_85810(&m.m[0][0]);
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][0]);
            gte_ldclmv_85810(&m.m[0][1]);
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][1]);
            gte_ldclmv_85810(&m.m[0][2]);
            gte_rtir_85810();
            gte_stclmv_85810(&m.m[0][2]);
            gte_SetTransMatrix_85810(base + 0x18);
            gte_ldlvl_85810(&m.t[0]);
            gte_rt_85810();
            gte_stlvnl_85810(&m.t[0]);
        }
        gte_SetRotMatrix_85810(&m);
        gte_SetTransMatrix_85810(&m);
        t0 = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) + 0x10;
    } else {
        gte_SetRotMatrix_85810(base + 0x18);
        gte_SetTransMatrix_85810(base + 0x18);
        t0 = a0 + 4;
    }

    gte_ldv0_85810((u8 *)(a0 + 0x14));
    gte_rtps_85810();
    gte_stsxy_85810(&v[0]);
    gte_stsz_85810(&sz);

    sx = *(s16 *)&v[0].vx;
    if (sx < 0) sx = -sx;
    if (sx >= 0xC9) return;
    sy = *(s16 *)&v[0].vy;
    if (sy < 0) sy = -sy;
    if (sy >= 0xA1) return;

    *(u16 *)&D_801BC9B4 = *(u16 *)(a0 + 0xC);
    *(u16 *)((u8 *)&D_801BC9B4 + 8) = *(u16 *)(a0 + 0xE);
    gte_SetRotMatrix_85810(&D_801BC9B4);
    gte_SetTransMatrix_85810(&D_801BC9B4);

    v[3].vx = *(u16 *)(spr + 8) + *(u16 *)(a0 + 0x1C);
    v[3].vy = *(u16 *)(spr + 0xA) + *(u16 *)(a0 + 0x1E);
    v[3].vz = sz;
    v[4].vx = *(u8 *)(spr + 2);
    v[4].vy = *(u8 *)(spr + 3);
    v[4].vz = sz;

    gte_ldv3_85810(&v[3], &v[4], &v[4]);
    gte_rtpt_85810();
    gte_stsxy0_85810(&v[1]);
    gte_stsxy1_85810(&v[2]);
    gte_stflg_85810(&flag);
    gte_stszotz_85810(&otz);
    if (flag & ~0x1000) return;

    mode = (flags >> 24) & 3;
    p = D_800A5E60;
    D_800A5E60 = p + 0x28;
    w = mode << 7;
    p[3] = 9;
    p[7] = 0x2C;
    ot16 = *(u16 *)(base + 0xA3D2);
    uu = *(u16 *)(spr + 4);
    cl = *(u16 *)(spr + 6);
    p[7] = 0x2E;
    *(u16 *)(p + 0x16) = w | ((flags >> 23) & 0x60) | ((cl & 0x100) >> 4)
                           | ((uu & 0x3C0) >> 6) | ((cl & 0x200) << 2);
    p[7] |= (flags & 0x40) >> 6;
    __asm__ volatile("");
    ob = &D_800A6610[ot16 << 14];
    uu -= (*(u16 *)(p + 0x16) & 0xF) << 6;
    uu <<= 2 - mode;
    cl &= 0xFFFF;
    p[0xC] = uu;
    if (*(u16 *)(p + 0x16) & 0x10) cl -= 0x100;
    p[0xD] = cl;

    p[0x14] = p[0xC] + *(u8 *)(spr + 2) - 1;
    p[0x15] = p[0xD];
    p[0x1C] = p[0xC];
    p[0x1D] = p[0xD] + *(u8 *)(spr + 3) - 1;
    p[6] = 0x80;
    p[5] = 0x80;
    p[4] = 0x80;
    p[0x24] = p[0x14];
    p[0x25] = p[0x1D];

    *(u16 *)(p + 8)    = v[0].vx + v[1].vx;
    *(u16 *)(p + 0xA)  = v[0].vy + v[1].vy;
    *(u16 *)(p + 0x10) = *(u16 *)(p + 8) + v[2].vx;
    *(u16 *)(p + 0x1A) = *(u16 *)(p + 0xA) + v[2].vy;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0xA);
    *(u16 *)(p + 0x18) = *(u16 *)(p + 8);
    tp = D_801BA6B0;
    *(u16 *)(p + 0x20) = *(u16 *)(p + 0x10);
    *(u16 *)(p + 0x22) = *(u16 *)(p + 0x1A);

    if (tp == 0) {
        u32 t2 = *(u8 *)(spr + 1);
        u32 tb = (t2 + 0x100) << 6;
        if (t2 < 0xE0) *(u16 *)(p + 0xE) = tb | 0x16;
        else           *(u16 *)(p + 0xE) = tb | 0x10;
    } else {
        u32 tb = (tp + 0x100) << 6;
        { u32 vv; if (tp < 0xE0) vv = tb | 0x16; else vv = tb | 0x10; *(u16 *)(p + 0xE) = vv; }
    }

    if ((flags & 0x300000) == 0x200000) {
        func_8001F730(t0, &v[0], p);
    }

    q = (s32 *)(ob + (otz << 2));
    *(s32 *)p = (*(s32 *)p & 0xFF000000) | (q[1] & 0xFFFFFF);
    q[1] = (q[1] & 0xFF000000) | ((s32)p & 0xFFFFFF);
}

/* RESIDUAL (35 masked mismatches, [permuter] class -- pure emission order, all
 * registers and all 489 instructions otherwise identical):
 *   343-347  the three loads: mine emits lhu(spr+4), lhu(spr+6), lui/addu/lhu(A3D2);
 *            the target emits the A3D2 group first.  Same multiset, rotated.
 *   363-380  the fence boundary: the target interleaves `sll $a2,14` (ob) and
 *            `andi $a3,0xFFFF` (cl) INTO the `sh 0x16 / lbu 7 / or / sb 7` window
 *            and computes `2 - mode` there too; the fence that fixes the register
 *            allocation also forbids exactly that interleave.  Both halves of this
 *            trade were measured: no fence = right order, wrong registers (67).
 *   432-438  the D_801BA6B0 lui/lbu sits between the two 0x20/0x22 loads instead of
 *            after both.
 *   466-479  the OT link: otz/(*(s32*)p) occupy $a0/$v1 instead of $v1/$a0.
 * All four are rank_for_schedule / INSN_LUID ties (cookbook S49), not reachable
 * from any source form tried here.
 */
