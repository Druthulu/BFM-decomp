extern s32 D_800A469C;
extern s16 D_800A46A0;
extern s16 D_800A46A2;
extern u8  D_800A46B0;
extern s32 D_800652F0[];

extern void func_8002ED90(void);
extern void func_800415A8(s32);
extern s16  func_80041A80(s32, s32, s32);
extern s16  func_800419B0(s32);

/* func_8002FDE8 -- start resource `idx` playing out of the buffer `data`.
 *
 * Byte-shape notes (each measured against asm/nonmatchings/800_b_2/func_8002FDE8.s):
 *   - `extern s16 D_800A46D2;` at BLOCK SCOPE, exactly as func_8002FF0C and func_800301C8 do
 *     below: this TU declares the symbol `extern s16 D_800A46D2[]` further down, and the ARRAY
 *     spelling makes cse cache the address in a callee-saved register across the func_800419B0
 *     call; the target keeps two independent %hi/%lo accesses (the `sh` at 0x2066C and the `lh`
 *     at 0x206C8), which only the scalar spelling emits.  This was the residual that held the
 *     function at closeness 35 for four prior attempts.
 *   - the FIRST zero-byte fence (cookbook S194-A, AFTER placement) keeps `idx | 0x4000` at the
 *     head of the join block, which is what lets reorg steal it into the `bltz` delay slot and
 *     eager-duplicate it on the taken path (0x20618 / 0x20630).  Without it the function is
 *     2 instructions short.
 *   - `one` is a real local, and the fence sits BETWEEN its assignment and the first store:
 *     the `li` must be the block's first insn while the `sb` sinks below the index computation.
 *     Writing the literal 1 at all three sites instead costs 10 mismatched.
 *   - `i4 = idx * 4;` is a separate statement.  The `sb D_800A46B0` and the `lw D_800652F0`
 *     carry a memory dependence, so sched1 orders them by LUID; splitting the index out gives
 *     the `sll` a lower LUID than the `sb` and reproduces `sll / addu $a0 / sb / lw`.
 *   - the SECOND fence is the S47 live-length slider.  `data` (2 refs / 15 insns, pri 1333) and
 *     the `1` constant (4 refs / 58 insns, pri 1379) are adjacent in global.c's allocno_compare,
 *     so the constant allocated first and took $s1.  One extra static insn where the constant is
 *     live and `data` is dead lengthens it to 59 (pri 1355 -> ties/loses) and hands $s1 back to
 *     `data`, $s2 to the constant, exactly as the target.
 *   - the third `return 1` is spelled inside the `== -1` arm, not as a trailing fallthrough:
 *     the other spelling inverts the final `beq` into a `bne` and swaps the two tail blocks.
 */
s32 func_8002FDE8(s32 idx, s32 data) {
    /* block scope -- see the note above */
    extern s16 D_800A46D2;
    s16 r;
    s32 one;
    s32 i4;

    func_8002ED90();
    if (D_800A46A2 >= 0) {
        func_800415A8(D_800A46A2);
        D_800A46A2 = -1;
    }
    D_800A46A0 = idx | 0x4000;
    one = 1;
    __asm__ __volatile__("");
    D_800A46B0 = one;
    i4 = idx * 4;
    D_800A469C = *(s32 *)((u8 *)D_800652F0 + i4);
    r = func_80041A80(data, -1, D_800A469C);
    D_800A46D2 = r;
    D_800A46A2 = r;
    __asm__ __volatile__("");
    if (r == -1) {
        D_800A46B0 = one;
        return 1;
    }
    if (func_800419B0(r) == -1) {
        func_800415A8(D_800A46D2);
        D_800A46A2 = -1;
        D_800A46B0 = one;
        return 1;
    }
    D_800A46B0 = 0;
    return 1;
}
