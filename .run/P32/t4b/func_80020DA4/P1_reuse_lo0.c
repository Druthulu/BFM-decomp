/* func_80020DA4 (0x80020DA4): builds a 3x3 Q12 rotation matrix from three angle-table lookups.
 * decl_prior (src/800.c): void func_80020DA4(s32 a0, s32 a1) -- callers cast pointers to s32.
 * a0 -> u16[3] angle indices (a0[0],a0[1],a0[2], each &0xFFF); a1 -> MTX_80020248-shaped s16[9]
 * output (m[0][0..2],m[1][0..2],m[2][0..2], offsets 0x0-0x10). D_800636D4 is a GLOBAL POINTER
 * (loaded via lw, not lui/addiu) to a table of packed {lo:s16, hi:s16} Q12 entries, 4B each.
 * Semantics hand-verified against every mult/mflo/sra/store in the target .s (identical Euler
 * composition to the banked twin ov_SC02_011/func_8018B76C, just Q12 not Q15 and a packed-word
 * table instead of two lookup calls).
 *
 * MATCH STATUS: NEAR, closeness 2 (masked), nins 100/100 exact. This is a THIRD-generation draft
 * on top of two prior sessions' documented walls (closeness 51->20->14->8, see
 * .run/S76y/sonnet/func_80020DA4.c and .run/S77w/sonnet/func_80020DA4.c for their full lever
 * histories, both reproduced byte-identically as a baseline this session). This draft keeps every
 * lever those sessions found load-bearing --
 *   1. `register s32 e0 __asm__("$6")` pin on the idxA table word (51 -> 20).
 *   2. Address computation as plain integer arithmetic `(idx << 2) + tbl` (tbl a plain `s32`, NOT
 *      `s32 *`) instead of `&tbl[idx]` pointer-index sugar (20 -> 14).
 *   3. Do not give a once-read shifted product (m7) its own named temp; inline it at its single use
 *      (14 -> 8).
 * -- and adds ONE new lever that closes the imm:6 frame-size residual those two sessions both
 * flagged as apparently irreducible:
 *   4. **`s32 frame_pad[3]; (void)&frame_pad;`** -- an address-taken-but-never-stored-through local
 *      array. Both prior sessions' notes independently concluded the persistent 16-byte (0x18 vs
 *      0x8) frame gap "is not a real spill of any value I can identify" and tried to reach it via
 *      statement reordering / register pins (all inert). It is neither: it is docs/matching-
 *      cookbook.md's documented INDUCE direction ("induce a phantom (unused, no-spill) stack frame
 *      the target has but your codegen omits -> an address-taken local array...Size N x 4 picks the
 *      frame: 1-2 words -> 8, 3-4 -> 0x10", evidence func_801758FC). N=3 words reserves exactly the
 *      missing 0x10, and `(void)&frame_pad` escapes the address with zero emitted code at -O2 (no
 *      store, no load, no register touched) -- confirmed byte-for-byte: EVERY other instruction in
 *      the function is unchanged, only the two `addiu $sp` immediates and the two `sw`/`lw $sN`
 *      displacements move to match the target exactly. This single addition dropped closeness
 *      8 -> 2, collapsing all 6 `imm` residual rows to zero in one compile.
 *
 * RESIDUAL (closeness 2, `REGALLOC-PERM $t0>$a2`, confirmed insensitive this session to: moving
 * m13's declaration next to lo0/hi2's, moving it to the very first declaration in the function,
 * moving the `m13 = lo0 * hi2;` statement to its earliest legal point (right after `lo0` is born),
 * swapping the multiply's operand order (`hi2 * lo0`, which regresses to closeness 3 via a
 * DIFFERENT REGALLOC-LOCAL class -- worse, reverted), and inlining m13 at its single use in
 * `dst[5]` (byte-identical to naming it, matches the prior session's finding)):
 *   - `mult $a2,$t2` (this draft's `m13 = lo0 * hi2`) is byte-identical to target including BOTH
 *     operand registers -- lo0 correctly persists in $a2, unpinned, through all 4 of its uses
 *     (m3, m7, m10, m13's mult; zero residual on any of them). Target's `mflo` REUSES the
 *     now-dying $a2 for the result (gcc-2.7.2's local-alloc.c `qty_phys_sugg` dying-hard-reg
 *     suggestion, recorded unconditionally at death per docs/matching-cookbook.md's §167-11/12
 *     region); mine allocates a fresh $t0 instead even though $a2 is free across m13's entire
 *     live range (born and dies within 2 statements, at the lowest register pressure point in the
 *     function). This is the allocation SUGGESTION not firing for reasons no source-level
 *     perturbation tried this session (or the prior two sessions, independently) moves -- a pure
 *     REGALLOC-PERM class per match_one's own classifier, i.e. cookbook law #3's "stop, submit
 *     NEAR with the class" signature. A same-register PIN on m13 (`register s32 m13
 *     __asm__("$6")`) was tried and is actively counterproductive (regresses to closeness 79):
 *     gcc-2.7.2 appears to treat an explicit `register __asm__` declaration as reserving that hard
 *     register for the WHOLE function, not just the pinned variable's live range, so co-pinning
 *     m13 to the same $6 as e0 (whose own live range ends long before m13's is born) creates a
 *     real conflict rather than a coincidental coloring match.
 *
 * NEW COOKBOOK CANDIDATE: the induced-phantom-frame lever (docs/matching-cookbook.md, the
 * "induce a phantom stack frame" bullet near func_801758FC) generalizes cleanly to a STRAIGHT-LINE,
 * branch-free, call-free function with heavy register pressure from many short-lived `mult`/`mflo`
 * results -- not just the leaf-with-a-stack-local case the existing note's evidence covers. Two
 * independent prior sessions on this exact function misdiagnosed the resulting 16-byte gap as an
 * un-reachable "whole-function CSE quantity budget" (their words) because pins and reordering
 * (the tools they reached for) cannot touch `get_frame_size()`; the lever needed is an inert
 * address-taken array, not a register-allocation change at all.
 */
extern s32 *D_800636D4;

void func_80020DA4(s32 a0, s32 a1) {
    u16 *src = (u16 *)a0;
    s16 *dst = (s16 *)a1;
    s32 tbl = (s32)D_800636D4;

    s32 p0, p1, p2;
    register s32 e0 __asm__("$6");
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
    dst[6] = -e1;
    dst[0] = m4 >> 12;
    dst[3] = m8 >> 12;
    dst[7] = m10 >> 12;
    lo0 = lo0 * hi2;
    dst[8] = m11 >> 12;
    dst[1] = (m5 >> 12) - p1v;
    dst[2] = (m6 >> 12) + (m7 >> 12);
    dst[4] = (m9 >> 12) + p_ac;
    dst[5] = (m12 >> 12) - (lo0 >> 12);
}
