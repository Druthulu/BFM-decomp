typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef short          s16;
typedef int            s32;

/* func_8017B490 @ 0x8017B490 (0x184, 97 ins) -- ov_SC01_000 shared engine fn.
 *
 * Structure: func_8017BA3C(); then an if/else on ((u32)&D_801A5694 < 0xB).
 * The if-branch (table copy via func_8012F214 x2) is DEAD -- gcc cannot fold
 * the address relocation so it emits the compare (sltiu addr,0xB) + both arms.
 * The else-branch (unaligned 8-byte memcpy of two fixed defaults) is taken.
 * After the join, two more 8-byte unaligned copies land the buffers into the
 * D_801A56E4/EC region, then 6 sign-extended shorts are broadcast to the
 * resident D_80126984.. int slots.
 *
 * STATUS: NEAR (97/97 ins, 13 masked-mismatch). Reachable path + the DEAD
 * func_8012F214 branch (cracked: base-side "+8" reassociation so gcc keeps
 * x<<4 in $s0 and precomputes p+8 in the call delay slot) + the whole tail
 * ALL match. Sole residual: gcc's pre-regalloc scheduler hoists the lone
 * `sh D_801A5870,1` (li v0,1; sh) up into the copy->read window (it lands
 * before the 6 lh reads; target places it after them, between reads and the
 * 6 sw broadcasts). No source reorder moves it (position-independent); a
 * scheduling barrier / asm-anchor / reg-pin fixes the placement but each one
 * relabels the copy-region regs ($v0<->$v1) -> 16-20 mismatch, strictly worse.
 * This is an irreducible gcc-2.7.2 scheduler tie-break for this fn shape ->
 * ideal permuter seed (perm_ scheduling class). */

extern void *memcpy(void *, const void *, u32);

extern void func_8017BA3C(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

extern u8  D_801A5694[];   /* 8-byte default block A (also the dead-branch index/base) */
extern u8  D_801A569C[];   /* 8-byte default block B */
extern u8  D_80182548[];   /* dead-branch table (16-byte stride) */

extern s16 D_801A56E4;     /* dst block B base */
extern s16 D_801A56E6;
extern s16 D_801A56E8;
extern s16 D_801A56EC;     /* dst block A base */
extern s16 D_801A56EE;
extern s16 D_801A56F0;

extern s16 D_801A5870;
extern s16 D_801A5674;

extern s32 D_80126984;
extern s32 D_80126988;
extern s32 D_8012698C;
extern s32 D_80126990;
extern s32 D_80126994;
extern s32 D_80126998;

void func_8017B490(s32 arg0)
{
    u8 buf0[8];
    u8 buf1[8];

    func_8017BA3C();
    if ((u32)&D_801A5694 >= 0xB) {
        memcpy(buf0, (void *)&D_801A5694, 8);
        memcpy(buf1, (void *)&D_801A569C, 8);
    } else {
        s32 index = ((u32)&D_801A5694) << 4;
        s32 arg_a = (s32)D_80182548 + index;
        s32 arg_b = ((s32)D_80182548 + 8) + index;
        func_8012F214(arg0, arg_a, (s32)buf0);
        func_8012F214(arg0, arg_b, (s32)buf1);
    }
    {
        /* Explicit dest pointers so the copy-dest addresses stay live and are
         * reused for the base short-reads (target keeps &D_801A56EC in $v1 and
         * &D_801A56E4 in $a0 across the reads instead of reloading). */
        s16 *pA = &D_801A56EC;
        s16 *pB = &D_801A56E4;
        memcpy((void *)pA, buf0, 8);
        memcpy((void *)pB, buf1, 8);
        D_801A5870 = 1;
        D_801A5674 = 0x1E;
        D_80126990 = (s32)*pA;
        D_80126994 = (s32)D_801A56EE;
        D_80126998 = (s32)D_801A56F0;
        D_80126984 = (s32)*pB;
        D_80126988 = (s32)D_801A56E6;
        D_8012698C = (s32)D_801A56E8;
    }
}
