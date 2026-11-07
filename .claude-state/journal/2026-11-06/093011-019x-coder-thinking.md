---
ts: 2026-11-06T16:30:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uww3v2cOh856uLCFt8zl
---
Still merged. The `goto docall` was optimized away — GCC's jump optimization redirected the branch: since docall is right after the else, then-arm's goto docall becomes a branch to docall, and then cross-jump merged.

Wait, mine's layout now: bnez v0,2ba0 (else arm), then slti 81, beqz v0,2bb8 (skip), then jal. So the then arm's `goto docall` became fallthrough to the call (the call got moved before the else arm? no). Actually the merged tail is `beqz v0,skip; nop` shared. The else arm's `bnez v0,2ba0` jumps to 2ba0 which is shared.

Hmm the structure became: if unk70 !=0 branch to shared beqz; then compare. Same as before.

The cross-jump merge happens at jump2 (after cse?) and is hard to stop without RTL difference.

What real-C RTL difference can we introduce? The merge matches `beqz v0,Lskip` and `nop` at ends. To break, one arm's tail must differ. Options:

1. Make the branch in one arm a different insn form, e.g. `if (d < 0x51) { ... }` with the body being the call — that puts the call inside the arm. Then arms differ but call duplicated (cross-jump may still merge the call+return tails). Hmm, actually if we write:

```
if (unk70 == 0) {
    if (d < 0x51) { call; return; }
} else {
    if (d < 0x201) { call; return; }
}
goto skip;
```
Both arms contain call+return, cross-jump merges them into shared block — that yields mine's layout probably.

2. Use different comparison shape in then arm: e.g. `if (0x51 <= d) goto skip;` — RTL `slti` vs maybe `sltiu`? same.

Maybe use unsigned comparison in one arm that still compiles to same slti? d is s32. `if (d - 0x51 >= 0)` → sub + sge? Not same.

3. Use a variable for the constant: `s32 lim2 = 0x51; if (d >= lim2)`. That yields lw or li + slt instead of slti → different insns, fails.

4. The key: target's then arm ends with `j docall`. That arises when the then arm's fall-through path is NOT the call. Which C puts the call only in the else arm's fallthrough? If we write:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    call; return;      // then arm has the call
} else {
    if (d >= 0x201) goto skip;
    call; return;      // else arm also has the call
}
```
cross-jump merges the two call+return tails → shared block placed after both arms; then arm ends with j? No — cross-jump redirects both branch-to-skip and merges the call block; then arm falls into... Hmm.

Target's layout literally: then arm code, j to call; else arm code; call. That's what you'd get if the call is in the ELSE arm only and the then arm jumps to it:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
    docall: call; return;
}
```
That's what I wrote and it got optimized. Why? Because GCC's jump pass (jump_optimize) may have threaded it. Hmm, but the asm prevented the merge by making RTL differ — meaning the merge is cross-jump at jump2 (second jump pass) operating on the same RTL shape we have.

Let me understand what target's RTL must have been. Maybe the original source was:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else {
    if (d >= 0x201) goto skip;
}
goto docall;    /* ??? */
docall: call;
```
No.

Actually maybe the target's then-arm `j 2bb8` is not from source goto but from the fact that in the target's RTL, the two arms are not identical because the then arm's tail had one extra instruction the else arm lacked — which the asm provided! And the final layout was produced by cross-jump being refused, so the arms stay in source order with a jump.

So we need any *real-C* difference in the two arms' RTL tails that (a) doesn't add net instructions and (b) keeps the emitted code identical. The merge compares patterns of the insns backward: last insns `nop` (delay slot of the branch? or separate insn). Hmm wait the nop after beqz is the delay slot insn (separate insn in RTL). Matching backward: nop vs nop; then beqz vs beqz — rtx_renumbered_equal_p compares patterns. The branch's pattern on MIPS: `(set (pc) (if_then_else (eq (reg) (const_int 0)) (label_ref L1) (pc)))`. Labels L1 differ between arms (skip label shared? both branch to skip so same label). rtx_renumbered_equal_p probably treats label refs equal by number? In this case both target skip so identical. Then continue: slti v0,v1,81 vs slti v0,v1,513 — the constants differ → break; but minimum already ≤0 after matching nop and branch? minimum starts 2, decremented for each matched insn: nop → 1, beqz → 0, then slti mismatch break with minimum 0 → merge [nop,beqz] only. That's the merge that occurred.

To prevent: make the last two insns differ in RTL between arms. E.g., in one arm, branch on a differently-constructed but code-identical condition. The branch insn pattern would then differ (e.g., bne vs beq with swapped targets, or the delay slot filled differently). Real C:

- Write the then arm as `if (d < 0x51) { } else goto skip;` → `bgez`? no.
- Use `if (d >= 0x51) goto skip; else goto docall;` same.

Alternative: invert one test: then arm `if (!(d >= 0x51)) goto docall;` → that's `d < 0x51` → slti;bnez docall. Emitted: `slti v0,v1,81; bnez v0,docall` instead of `beqz v0,skip; j docall`. That changes insns (beqz+branch instead of beqz+j), which may match target? Target then arm is `beqz v0,2bc8; nop; j 2bb8; nop`. So no.

Hmm, what about making the *delay slot* differ: in one arm, the instruction in the delay slot of the branch. GCC fills delay slots at dbr (after jump2), so cross-jump sees RTL before delay fill: the nop isn't there. So matching is on `beqz` and preceding slti. Then minimum 2 requires two matched insns: beqz matches beqz (min→1), slti vs slti differ (min stays 1) → break, minimum=1>0 → no merge. But merge happened! So maybe the branch patterns differ in a way, or the preceding matched insns are different. Let me reconsider: maybe the match is on `move a0,s3` / `jal` tails — the two arms both end with jump to the call block... hmm.

Actually maybe the merge happened at jump2's "jump to next instruction" / jump-around-jump optimizations rather than cross-jump. Target has `j 2bb8` then at 2bb8 the call — this is the unmerged natural layout.

Let's inspect the dumps. Use tools/cc1_dumps.sh on the win body (self-contained? need common.h include). Let's do it: cc1_dumps.sh needs a self-contained draft; it prepends common.h. Our body uses Unkstruct_800B5CB8, CAST_WIDTH macros, D_ symbols — those come from common.h/other headers. cc1_dumps.sh only includes common.h; maybe enough. But simpler: tools/cc1_dumps_tu.sh dumps the TU. Let's check it.
