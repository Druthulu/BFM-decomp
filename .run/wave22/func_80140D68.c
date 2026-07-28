/* func_80140D68 — SPRT (0x14) primitive builder + PsyQ addPrim() into OT_800D29F8[2].
 *
 * @class: schedule
 * @status: NEAR 9/65 — 65/65 instructions, every instruction byte-correct, ONE positional drift.
 * @stuck: the 0xFFFFFF mask register ($t1) builds ATOMICALLY here (lui idx2 / ori idx3); the target
 *   SPLITS the pair (lui idx2 ... ori idx13, between `sra $a2,$a2,14` and `addiu $a3,$a3,-0xD`).
 *   Everything from idx15 on is byte-identical; idx3..13 is a pure shift-by-one caused solely by
 *   that one `ori`. gcc-2.7.2 splits the large constant BEFORE sched2 (verified with
 *   -fno-schedule-insns2: cc1 emits `li $9,0x00ff0000` + `ori $9,$9,0xffff` as two insns), so the
 *   position is decided by the pre-sched2 RTL LUID of the `ori`, which is NOT reachable from the
 *   source in this shape. Explored and byte-measured (~200 compiles):
 *     - 126 header-statement orderings (q/dx/x/y/w/h permutations)  -> all 9, ori pinned at idx3
 *     - PTag bitfield layouts (u32:24+u32:8 / u32:24+u8 / u32:24)   -> all 9
 *     - plain-local and `register __asm__("$9")` mask + redundant `& mlo`, swept over 12 source
 *       positions                                                   -> 9 or 12, never 13
 *     - `volatile short` decl instead of a cast at use               -> 40+
 *   The ONE family that moves the `ori` is: pointer-cast header (no Sprt struct) + a SHARED
 *   `u32 *ot` local + LITERAL masks — there the constant sinks in RTL to just after the volatile
 *   lhu and schedules at idx14 (one slot late). Best of that family is kept at
 *   .run/wave22/_a80140D68/x_pin2.c (closeness 12: idx13/14 ori<->addiu swap + a clean $v0/$v1
 *   swap in the second addPrim half, because a single shared `ot` pseudo cannot take two registers
 *   while splitting it into two pseudos moves the `ori` back to idx23). Permuter-shaped.
 *
 * Signature (read off the asm): a0 = SPRT out, a1 = s16 *src, a2 = s16 idx (in-callee
 * sll16/sra14 => K&R narrow param, cookbook §99), a3 = s32 dx, 0x10($sp) = s16 ofs (K&R narrow;
 * ANSI `s16 ofs` yields `lh`+`sll 1` = 2 ins instead of the target's lw+sll16+sra15).
 *
 * Draft-local shims: these two typedefs already exist VERBATIM in src/shared/engine_types.h
 * (Hw4 @833, Env_800D29F8). The guard makes the draft self-contained for match_one (which only
 * prepends common.h) while collapsing to nothing once banked into a TU that includes the header. */
#ifndef BFM_ENGINE_TYPES_H
typedef struct { s16 x; s16 y; } Hw4;
typedef struct {
    u32 *ot;            /* 0x00 */
    u32 pad[4];         /* 0x04..0x13 */
} Env_800D29F8;         /* 0x14 stride */
#endif

extern Hw4 D_8011516A[];
extern short D_800B9A02;
extern Env_800D29F8 D_800AE7BC[];

#define OT8_80140D68 (*(u32 *)(D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot + 2))

u32 *func_80140D68(out, src, idx, dx, ofs)
    u32 *out;
    s16 *src;
    s16  idx;
    s32  dx;
    s16  ofs;
{
    typedef struct {
        u32 tag;        /* 0x00 */
        u32 code;       /* 0x04 */
        s16 x, y;       /* 0x08 */
        u8  u, v;       /* 0x0C */
        u16 clut;       /* 0x0E */
        s16 w, h;       /* 0x10 */
    } Sprt_80140D68;    /* 0x14 */
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_80140D68;

    register u32 mhi __asm__("$8");
    Sprt_80140D68 *p;
    s16 *q;

    p = (Sprt_80140D68 *)out;
    p->tag = 0x04000000;
    p->u = 0x70;
    p->v = 0x10;
    mhi = 0x64808080;
    p->code = mhi;
    p->clut = 0x4056;

    dx -= 0xD;
    q = (s16 *)(ofs * 2 + (s32)src);
    p->x = q[0] + D_8011516A[idx].x + dx;
    p->y = q[1] - 4;
    p->h = 0x10;
    p->w = 0x10;

    ((PTag_80140D68 *)p)->addr = ((PTag_80140D68 *)&OT8_80140D68)->addr;
    ((PTag_80140D68 *)&OT8_80140D68)->addr = (u32)p;

    return out + 5;
}
