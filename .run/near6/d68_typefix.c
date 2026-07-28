/* func_80140D68 — SPRT (0x14) primitive builder + PsyQ addPrim() into OT_800D29F8[2].
 *
 * @class: schedule
 * @status: MATCH 0/65 (match_one, asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077)
 *
 * ---------------------------------------------------------------------------
 * HOW THE "ori pinned at idx 3" WALL FELL — three sched1 levers, all byte-measured
 * against cc1 RTL dumps (-dS/-dR = .i.sched/.i.sched2).
 *
 * The 0xFFFFFF mask is ONE movsi that sched1's own `try_split` (sched.c:4830 ->
 * mips.md large_int split) turns into `lui`+`ori` BOTH SETTING THE SAME PSEUDO.
 * reg_n_sets becomes 2 (sched.c:4617 update_flow_info), so `birthing_insn_p`
 * (sched.c:2498, needs REG_N_SETS==1) never boosts either half.  sched1 schedules
 * BACKWARD, so an un-boosted priority-1 ALU insn only wins a tick when NOTHING
 * boosted and NOTHING on the memory unit is ready — otherwise it drifts to the
 * block head.  That is the whole residual: the `ori` floated to sched1 output
 * position 3, sched2 inherited that as its LUID, and it re-floated to idx 3.
 *
 * For the target, sched2 must sort  LUID(sra a2) < LUID(ori) < LUID(addiu a3),
 * i.e. sched1 must EMIT the ori between them.  Three things had to be true:
 *
 *  L1 — POINTER STORES, NOT A `Sprt *` STRUCT (fixes `lw $v1,0x10($sp)` @ idx 3).
 *       `p->tag = ...` through a struct pointer sets MEM_IN_STRUCT_P (`/s`) on the
 *       store, and `anti_dependence()` then says the `/s` store does NOT alias the
 *       plain `(mem (sp+16))` incoming-arg load — so the lw became ready 3 ticks
 *       early and sched1 placed it at pos 6 instead of pos 3.  Storing through
 *       `u32 *out` (no `/s`) restores the anti-dep and the lw lands at idx 3.
 *       (§30's store-vs-load `/s` flag, used in the *opposite* direction.)
 *
 *  L2 — BITFIELD addPrim, INLINE (keeps the ori off the "empty ready list" hole).
 *       With literal masks (`out[0] = (out[0] & 0xff000000) | (ot[2] & 0xffffff)`)
 *       sched1 hits a tick where the ori is the ONLY ready insn and freezes it at
 *       output pos 32 -> idx 14 (measured: 12 off — that is what every
 *       `.run/wave22/_a80140D68/*.c` 12-scorer was).  The `((PTag*)…)->addr`
 *       bitfield form (cookbook §31 "BITFIELD STORE = THE MASK-ORDER DECOUPLER")
 *       keeps that tick occupied so the ori keeps drifting.
 *
 *  L3 — KILL THE BIRTHING BOOST ON THE FIRST `addu` (the actual crack).
 *       sched1 queues each `lhu` 2 cycles behind its consumer (r3000 load latency,
 *       mips.md:157), which opens exactly ONE gap tick above them.  While
 *       `q[0]+D_8011516A[idx].x` was a fresh single-set pseudo it was boosted, took
 *       the tick above the loads, and `dx-0xD` (also boosted) took the gap — so the
 *       forced emission order was  sra, lhu, lhu, dx  with no ALU-only tick left
 *       for the ori anywhere between sra and dx.  Writing the sum into a variable
 *       that is assigned AGAIN (`a = q[0]+D…; a += dx;`) gives it REG_N_SETS==2,
 *       kills its boost, lets the boosted `dx-0xD` take the higher tick, and leaves
 *       the gap tick to the ori: sched1 now emits  sra, lhu, lhu, ori, dx  (ori at
 *       output pos 20) — exactly the LUID order sched2 needs.  11 -> 0.
 *
 * NEW IDIOM (for cookbook §S2/§49): an un-boosted 2-insn constant that floats to the
 * top of its block cannot be moved by its OWN source position (126 header orderings +
 * 150 body permutations measured: no effect at all).  It is moved by DELETING A BOOST
 * from whatever insn currently owns the load-latency gap above it —
 * `x = A + B; x += C;` instead of `x = A + B + C;` is a zero-byte boost-kill that
 * hands that gap tick to the floater.
 *
 * Measured dead ends kept for the record (every number from a real match_one run):
 *   register-pinned / plain mask locals over 12 positions -> 9 or 12, never 13
 *   126 header orderings / 150 body permutations          -> 12 (ori stuck at 14)
 *   two `u32 *ot` locals / inline OTP / `u32 ot` int form  -> 26 / 56 / 12
 *   `__asm__("":"=r"(v):"0"(v))` re-tie on the lhu temps   -> 32 / 64 (hoists the lhu)
 *   the same re-tie placed AFTER last use                 -> deleted as dead, 11
 *   reusing one s32 temp for both lhu (S12 fence)         -> 30 (loads float up)
 *   dropping the $8 pin on mhi                            -> 8 (REGALLOC-PERM $t0/$t1)
 *   dropping the (u16) casts on the two lhu               -> 2 (WIDTH lh != lhu)
 *
 * Signature (read off the asm): a0 = SPRT out, a1 = s16 *src, a2 = s16 idx (in-callee
 * sll16/sra14 => K&R narrow param, cookbook §99), a3 = s32 dx, 0x10($sp) = s16 ofs
 * (K&R narrow; ANSI `s16 ofs` yields `lh`+`sll 1` = 2 ins instead of lw+sll16+sra15).
 *
 * Draft-local shims: these two typedefs already exist VERBATIM in src/shared/engine_types.h
 * (Hw4 @833, Env_800D29F8). The guard makes the draft self-contained for match_one (which
 * only prepends common.h) while collapsing to nothing once banked into a TU that includes
 * the header. */
#ifndef BFM_ENGINE_TYPES_H
typedef struct { s16 x; s16 y; } Hw4;
#endif
/* §94 TYPE-CARRY FIX: Env_800D29F8 is NOT in engine_types.h (verified: 0 hits), so it must NOT sit
   behind the BFM_ENGINE_TYPES_H guard — in the real TU that guard is DEFINED, the typedef vanished,
   and the next line failed to parse. Hw4 stays guarded because it genuinely IS in the shared header
   (redefining it would conflict). Kept draft-local per cookbook §100, not lifted. */
typedef struct {
    u32 *ot;            /* 0x00 */
    u32 pad[4];         /* 0x04..0x13 */
} Env_800D29F8;         /* 0x14 stride */

extern Hw4 D_8011516A[];
extern short D_800B9A02;
extern Env_800D29F8 D_800AE7BC[];

#define OTP_80140D68 (D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot)

u32 *func_80140D68(out, src, idx, dx, ofs)
    u32 *out;
    s16 *src;
    s16  idx;
    s32  dx;
    s16  ofs;
{
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_80140D68;

    register u32 mhi __asm__("$8");
    s16 *q;
    s32  a;

    out[0] = 0x04000000;
    *((u8 *)out + 0xC) = 0x70;
    *((u8 *)out + 0xD) = 0x10;
    mhi = 0x64808080;
    out[1] = mhi;
    *(u16 *)((u8 *)out + 0xE) = 0x4056;

    dx -= 0xD;
    q = (s16 *)(ofs * 2 + (s32)src);
    a = (u16)q[0] + (u16)D_8011516A[idx].x;
    a += dx;
    *(s16 *)((u8 *)out + 0x8) = a;
    *(s16 *)((u8 *)out + 0xA) = q[1] - 4;
    *(s16 *)((u8 *)out + 0x12) = 0x10;
    *(s16 *)((u8 *)out + 0x10) = 0x10;

    ((PTag_80140D68 *)out)->addr = ((PTag_80140D68 *)(OTP_80140D68 + 2))->addr;
    ((PTag_80140D68 *)(OTP_80140D68 + 2))->addr = (u32)out;

    return out + 5;
}
