/* func_80020DA4 (0x80020DA4): builds a 3x3 Q12 rotation matrix from three angle-table lookups.
 * decl_prior (src/800.c:12196): extern void func_80020DA4(s32 a0, s32 a1); -- callers cast pointers to s32.
 * a0 -> u16[3] angle indices (a0[0],a0[1],a0[2], each &0xFFF); a1 -> MTX_80020248-shaped s16[9]
 * output (m[0][0..2],m[1][0..2],m[2][0..2], offsets 0x0-0x10). D_800636D4 is a GLOBAL POINTER
 * (loaded via lw, not lui/addiu) to a table of packed {lo:s16, hi:s16} Q12 entries, 4B each.
 * Semantics hand-verified against every mult/mflo/sra/store in the target .s (identical Euler
 * composition to the banked twin ov_SC02_011/func_8018B76C, just Q12 not Q15 and a packed-word
 * table instead of two lookup calls).
 *
 * MATCH STATUS: MATCH (match_one 100/100 AND rtu_match MATCH in the real TU src/800.c, P32 T5x,
 * 2026-09-05, Fable). Sixth-generation draft: 51 -> 20 -> 14 -> 8 -> 2 -> 0. The levers the earlier
 * sessions found load-bearing are all kept EXCEPT the very first one, which turned out to be the
 * cause of the final residual:
 *   1. (REMOVED) `register s32 e0 __asm__("$6")` pin on the idxA table word (51 -> 20 in S76). The pin
 *      put e0 in $a2 the way the target has it, but an explicit hard register is copied into
 *      reload1.c's `regs_explicitly_used` (reload1.c:486) -> `bad_spill_regs` (reload1.c:3651-3660)
 *      -> `forbidden_regs` (reload1.c:709), and that set is the `losers` argument of every
 *      `retry_global_alloc` (reload1.c:3497 -> global.c find_reg). The mult results here are GLOBAL
 *      allocnos (their preferred class is LO_REG, the `=l` output of mulsi3_internal, mips.md:848);
 *      global.c first parks m3/m8/m13 in LO itself, reload then spills LO ("Spilling reg 65") and
 *      RETRIES them -- and the retried m13 (pseudo 102) could not take the freshly-dead $a2 because
 *      $a2 was forbidden by the pin. That is the whole `mflo $t0` vs `mflo $a2` residual (idx 91/92).
 *      Unpinned, m13's retry lands in $a2 ("Register 102 now in 6" in the -dg dump) exactly as the
 *      target's does.
 *   2. Address computation as plain integer arithmetic `(idx << 2) + tbl` (tbl a plain `s32`, NOT
 *      `s32 *`) instead of `&tbl[idx]` pointer-index sugar (20 -> 14).
 *   3. Do not give a once-read shifted product (m7) its own named temp; inline it at its single use
 *      (14 -> 8).
 *   4. `s32 frame_pad[3]; (void)&frame_pad;` -- an address-taken-but-never-stored-through local
 *      array reproduces the target's 16-byte phantom frame (8 -> 2), zero emitted code.
 *   5. (NEW) Two zero-byte launders `__asm__("" : "=r"(x) : "0"(x))` that steer LOCAL-alloc's
 *      qty_compare priorities (local-alloc.c:1579) so that unpinned first-fit lands e0 in $a2:
 *      - `e1` laundered immediately before `dst[6] = -e1`. Unpinned, e0's tied quantity {e0, e0<<16,
 *        lo0} (10 refs / 38 insns, pri 7894) out-ranked e1's tied quantity {e1, -e1} (5 refs / 15,
 *        pri 6666), so e0 was allocated first and took the free $v1; the target needs e1's quantity
 *        allocated FIRST (it then holds $v1 across e0's range, and e0's first fit falls through
 *        $v0/$v1/$a0/$a1 to $a2). The launder adds two refs to e1's quantity (7 refs / 16 -> 8750)
 *        and sched1 places it at position 40, AFTER lo1's death (the m12 mult), which matters: placed
 *        right after e1's load (pos 27) it lengthens lo1 by one insn and flips the exact
 *        qty_compare tie lo1 (4/32) vs p_ab (3/12) = 2500 both, handing $a0 to p_ab (closeness 15).
 *      - `p1` laundered between its `& 0xFFF` and its `<< 2`. The e1 launder at pos 40 lengthens the
 *        global allocnos m6/m7/m12 (95/96/101: 23 -> 24 insns, allocno pri 869 -> 833) but not m1
 *        (90: 24 insns, 833), collapsing the order 95 96 101 90 into an allocno-number tie won by 90
 *        (closeness 6: the $t8/$t6/$t7 mflo rotation). A second zero-byte insn at sched1 pos 20 --
 *        inside m1's range [15,38], outside lo1's [23,39] and before m2's birth -- restores
 *        len(90) > len(95/96/101) while leaving every local qty_compare order unchanged (hand-checked
 *        for all 30 local quantities; equivalently, laundering `addr1` right after its addu also
 *        matches byte-for-byte).
 *   The order of allocations is exactly the target's now: global "92 97 99 100 102 91 93 94 95 96
 *   101 90 98"; local e1 {81,124} -> $v1 before e0 {80,120,85} -> $a2, tbl -> $a3, lo1 -> $a0, p_ab/p1v
 *   -> $a3, lo2/hi0/hi2 -> $t0/$t1/$t2, p_ac -> $t3; reload retries m3 -> $a3, m8 -> $s1, m13 -> $a2.
 *   Evidence and the full -dl/-dg readings: .run/P32/t5x/reports/func_80020DA4.md; cookbook §47/§500-G
 *   are the priority-slider precedents, §500-H the launder-of-a-pinned-value precedent.
 */
extern s32 *D_800636D4;

void func_80020DA4(s32 a0, s32 a1) {
    u16 *src = (u16 *)a0;
    s16 *dst = (s16 *)a1;
    s32 tbl = (s32)D_800636D4;

    s32 p0, p1, p2;
    s32 e0;
    s32 e1;
    s32 addr1, addr2;
    s32 hi0, lo0, hi1, lo1, hi2, lo2;
    s32 m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13;
    s32 p_ab, p_ac, p1v;
    s32 frame_pad[3]; (void)&frame_pad;

    p0 = src[0] & 0xFFF;
    e0 = *(s32 *)((p0 << 2) + tbl);
    p2 = src[2] & 0xFFF;
    addr2 = (p2 << 2) + tbl;
    hi0 = e0 >> 16;
    lo2 = *(s16 *)addr2;
    m1 = hi0 * lo2;
    hi2 = *(s16 *)(addr2 + 2);
    m2 = hi0 * hi2;
    p1 = src[1] & 0xFFF;
    __asm__("" : "=r"(p1) : "0"(p1));
    addr1 = (p1 << 2) + tbl;
    lo0 = (s16)e0;
    lo1 = *(s16 *)addr1;
    m3 = lo0 * lo1;
    e1 = *(s32 *)addr1;
    hi1 = e1 >> 16;
    m4 = hi2 * hi1;
    p_ab = m3 >> 12;
    m5 = p_ab * hi2;
    p_ac = m2 >> 12;
    m6 = p_ac * lo1;
    m7 = lo0 * lo2;
    m8 = lo2 * hi1;
    m9 = p_ab * lo2;
    m10 = hi1 * lo0;
    m11 = hi1 * hi0;
    p1v = m1 >> 12;
    m12 = p1v * lo1;
    __asm__("" : "=r"(e1) : "0"(e1));
    dst[6] = -e1;
    dst[0] = m4 >> 12;
    dst[3] = m8 >> 12;
    dst[7] = m10 >> 12;
    m13 = lo0 * hi2;
    dst[8] = m11 >> 12;
    dst[1] = (m5 >> 12) - p1v;
    dst[2] = (m6 >> 12) + (m7 >> 12);
    dst[4] = (m9 >> 12) + p_ac;
    dst[5] = (m12 >> 12) - (m13 >> 12);
}
