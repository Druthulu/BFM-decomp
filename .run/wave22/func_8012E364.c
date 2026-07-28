/* func_8012E364 (ov_SC01_077_jr_8012ACE0) — NEAR: 67/67 ins, closeness 7 (reloc-masked).
 *
 * Structure is fully solved: identical instruction count, identical control flow, identical
 * delay-slot fills, identical %hi/%lo pairs. The residual 7 slots are pure gcc-2.7.2 register
 * allocation / list-scheduler tie-breaks (see "RESIDUAL" at the bottom).
 *
 * Symbols: sig_hints listed no callees and no data decls for this fn, so the three externs below
 * are derived from the asm's %hi/%lo pairs:
 *   D_80126CE0  -> `lh`  (0x8012E370)  => s16
 *   D_801D9498  -> `lw`/`sw`           => s32
 *   D_801D949C  -> `lw`/`sw`           => s32
 * D_80126CE0 is already declared `extern s16 D_80126CE0;` inside ov_SC03_099_jr_8016AB6C.c etc.,
 * so the s16 typing is consistent with the rest of the tree.
 *
 * LOAD-BEARING constructs (do not "simplify"):
 *  1. `spd` — a local holding 0x1000 that is SET BEFORE the if/else chain. This is what makes gcc
 *     materialise the constant in a pseudo whose live range crosses the branch, giving
 *     `addiu $a3,$zero,0x1000` in the `blez` delay slot at 0x8012E3DC and the `sw $a3` /
 *     `addu $v1,$v1,$a3` register forms at L8012E410. Writing the literal 0x1000 inline instead
 *     costs 2 instructions (a separate `li` + an unfilled delay slot).
 *  2. `a` — ONE variable reused for three roles (the D_80126CE0 value, the division result, and
 *     the entity pointer). That makes it a cross-block (global) allocno, so local-alloc's
 *     combine_regs cannot tie the division result to the `sra` temp — which is what puts the
 *     result in $a0 (`subu $a0,$v0,$v1`) instead of coalescing into $v0. Splitting `a` into
 *     x/t/ent regresses 2 slots.
 *  3. The three register pins ($6 param, $5 prev, $2 flags) reproduce the target's allocation of
 *     the tail block; without them the whole a/t register profile shifts down one slot (and the
 *     leading `move $a2,$a0` disappears entirely, costing an instruction).
 *
 * RESIDUAL (7 slots, both clusters are compiler tie-breaks, not C-expressible):
 *   idx 43-45  the two block-head loads are swapped: gcc schedules `lw $a0,0x20($a2)` before
 *              `lw $a1,D_801D949C`; the target has them the other way round. Priority-driven
 *              (the ent->lhu->ori->sh chain outranks prev->subu->addu->sw), NOT source order —
 *              every permutation of the 7 tail statements gives the identical schedule.
 *   idx 59-62  the target keeps a redundant copy `addu $v0,$v1,$zero` (in the bgez delay slot)
 *              before `negu $v0,$v0`; gcc here coalesces d with v and emits `nop`/`negu $v1,$v1`.
 *              Forcing the copy (pin `v` to $3, compare on `v`) makes it appear but lands `d` in
 *              $a1/$a0 rather than $v0 — same 4-slot cost either way.
 *   ~2500 source-shape/pin combinations swept, plus a 400 s decomp-permuter run at -j10
 *   (33 saved candidates, all score 7, never below). This is genuine regalloc hard tail.
 */
extern s16 D_80126CE0;
extern s32 D_801D9498;
extern s32 D_801D949C;

void func_8012E364(s32 arg0_)
{
    register s32 arg0 __asm__("$6");
    register s32 prev __asm__("$5");
    register u16 flags __asm__("$2");
    s32 a;
    s32 diff;
    s32 v;
    s32 d;
    s32 spd;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_801D9498 = 0x1000;
        D_801D949C = 0x1000;
    }
    a = ((0x90 - a) << 12) / 0x90;
    *(s32 *)(arg0 + 0x1C) += 1;
    spd = 0x1000;

    diff = D_801D9498 - a;
    if (diff > 0) {
        D_801D9498 -= diff >> 2;
    } else if (diff < 0) {
        D_801D9498 += (-diff) / 4;
    }

    prev = D_801D949C;
    a = *(s32 *)(arg0 + 0x20);
    v = D_801D9498 - prev + spd;
    D_801D949C = spd;
    flags = *(u16 *)(a + 0x2C);
    D_801D9498 = v;
    *(u16 *)(a + 0x2C) = flags | 0x10;

    a = *(s32 *)(arg0 + 0x20);
    d = v;
    if (d < 0) d = -d;
    *(s16 *)(a + 0x1C) = d;
    *(s16 *)(a + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x1000;
}
