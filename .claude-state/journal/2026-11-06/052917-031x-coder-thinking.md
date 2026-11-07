---
ts: 2026-11-06T12:29:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k3J4MVUfhhvwCHzPFCA3
---
c3/c4 worse (39). c5 12. None fixed the delay slot.

Let me think differently. Maybe instead of the delay slot, restructure the loop so the increment is not duplicated but the `move a0,s0` moves before the jal.

Look at the target again:
```
2224: move a0,s0
2228: jal
222c: move a1,s3
2230: move s0,v0
2234: addiu v0,s1,1
2238: move s1,v0
```
Hmm wait: is the addiu at 2234 really a duplicate stolen from the taken thread? Or is the source such that the increment is computed inside... no, cross-jump merged both paths' increment into one at 2234, and reorg's delay-slot fill added the copy in the delay slot.

Since the increment insn is shared by both paths (at 2234) and reorg copies it into the delay slot when the fall-through is ineligible... 

What if the C has the increment written as a separate statement BEFORE the if? Like:

```
do {
    ...
    i = i + 1;      /* at loop top? */
```
No — the target's index load uses i before the increment.

Alternative: could we get `move a0,s0` before the jal and the delay slot filled with `addiu` via a *different* branch structure, e.g. an early-exit? Consider:

```
do {
    if (*(s16 *)(...) == 0) goto tail;
    ot = xf(ot, panel, (s32)i);
tail:
    i = i + 1;
    panel = panel + 0x20;
} while ((s32)i < lim);
```
Here the branch is `beqz v0, tail_label` — same beqz to the increment, same fill decision.

Hmm what if the taken thread starts with the increment in a way that makes `move a0,s0` ineligible? `insn_sets_resource_p(trial, &opposite_needed, 1)` — opposite_needed = live at the target (2238) = {v0, s2, s3, sp, ra}. The trial is `move a0,s0`. To make it ineligible, a0 must be live at the target... a0 isn't.

What if the call took its first argument in a register that's live at the target? Not controllable.

What about the "may_trap_p" part? no.

OK here's another thought: what if we make the increment NOT shareable (so cross-jump doesn't merge it) and instead write the source as:

```
do {
    if (x != 0) {
        ot = xf(ot, panel, (s32)i);
    }
    i = i + 1;
    panel += 0x20;
} while (...);
```
= current.

What if the loop is a `for` loop: `for (i = 0; i < lim; i++) { ... }`? The increment is in the for-update, still at the bottom. gcc would generate the same. But maybe the loop notes differ: `for` loop with the test at the top vs do-while at the bottom. Target's test is at the bottom (bnez back to top) — that's a do-while shape (or a for loop where the test is duplicated? no). Actually gcc turns a for loop with a constant trip... no.

Hmm, but what about the LOOP_BEG note idea: mostly_true_jump returns 2 if NOTE_INSN_LOOP_BEG is immediately before the target label. The target label is the increment path. In a do-while loop, NOTE_INSN_LOOP_BEG is at the loop top (2200), not at 2238.

BUT: `NOTE_INSN_LOOP_VTOP`! "If this is a jump to the test of a loop, it is likely true: scan forwards from the target label; if NOTE_INSN_LOOP_VTOP appears before the next real insn, return 1." For a `while` loop (test at top), LOOP_VTOP is before the test. Not our case.

Alternatively `rare_destination` difference: rare_fallthrough - rare_dest. rare_destination(insn at target) = 0 (CODE_LABEL). rare_destination(NEXT_INSN(jump)): scans forward from the insn after the jump: it's an INSN, next... until a CODE_LABEL → 0. Unless there's a BARRIER or RETURN or simplejump before a label. NEXT_INSN(jump) is `move a0,s0` (INSN) → next insns → the jal (CALL_INSN; not JUMP_INSN) → ... then the code label at 2238 → 0. Hmm, unless the arm ends with a simplejump (no).

Wait, what about `if (condition == const_true_rtx)`... no.

So prediction for this beqz is 0 and we can't change it via C.

What about making `own_fallthrough` 0? own_fallthrough = own_thread_p(NEXT_INSN(insn), NULL_RTX, 1) which returns 0 if there's a CODE_LABEL between NEXT_INSN(insn) and the first active insn after it. So if a CODE_LABEL sits immediately after the branch! How? A label right after the branch = a branch target at the arm's head. If some other branch jumps to the arm's head, there'd be a label there. Hmm — a label at the arm head would then... Let me think: if we write

```
do {
    if (x != 0) {
        ot = ...;
    }
```
The arm head has no label. But if the arm were a join target of an earlier branch (e.g. `if (a) goto arm;`)... we'd add code.

Hmm, what about `if (x == 0) goto inc; ...` with a label at the increment? That label is at the increment, not the arm.

Let me reconsider: maybe there's a completely different C shape that produces the target's insns with 175. What about the do-while(0) around the *whole* if including... no.

Alternatively — maybe use a helper temp so that the call's first arg setup is not `move a0,s0` but something ineligible. `insn_sets_resource_p(trial, &set, 1)` where set = resources set by earlier insns in the thread scan... The scan starts at the arm head with empty set.

The condition `! insn_sets_resource_p (trial, &opposite_needed, 1)` is the key gate. opposite_needed = live at target. What if `panel` (s3) is live at the target label but our arm head set s3? Consider writing the loop so panel is incremented at the arm's start? No.

Wait wait. What about the ORDER of the increment and panel update vs. the arm? What if the source is:

```
do {
    s32 nx;
    if (x != 0) { ot = xf(ot, panel, (s32)i); }
    i = i + 1;
    panel += 0x20;
} while (...)
```
Same.

Different idea: use the fact that `addiu v0,s1,1` writes v0 and v0 is live at the target. If the *increment* were the fall-through head... i.e., if the branch were inverted: `if (x == 0) goto inc;` — no, the branch condition to the increment would be bnez.

Hmm, actually, what about the source `if (!(x != 0)) ...`? Same EQ.

Let me reconsider the problem from the other side: maybe the source should compute i+1 into a variable *inside the arm*, i.e. the increment is inside the if in the C:

Target's structure could come from:
```
do {
    if (x != 0) {
        ot = xf(ot, panel, (s32)i);
        i = i + 1;
        panel += 0x20;
        continue;     /* -> the loop's increment */
    }
    i = i + 1;
    panel += 0x20;
} while ((s32)i < lim);
```
No, that duplicates.

Or maybe the target source is:
```
do {
    if (x != 0) {
        ot = xf(ot, panel, (s32)i);
    }
    i = i + 1;
    panel = panel + 0x20;
} while ((s32)i < lim);
```
with the difference being that `i` is s16 → `i = i + 1` needs the truncation... Both mine and target do `move s1,v0` + sll/sra at the loop test.

Hmm hold on. Let me reconsider: in target, is the beqz's delay-slot insn really a *copy* of 2234? What if the source instead has TWO increment computations: e.g.

```
if (x != 0) { ot = xf(ot, panel, (s32)i); }
i = i + 1;
```
where the loop's `i = i + 1` at the end gets... no.

Alternatively, maybe the source is a `for` loop:
```
for (i = 0; i < lim; i++) { if (x) call; panel += 0x20; }
```
gcc's for loop: the increment `i++` is at the bottom, and the loop test at the bottom too (gcc duplicates the test? For a for loop with the test at the top, gcc emits the test at the top AND at the bottom? No — gcc's for loops emit the test at the top and a jump back; the bottom has the increment then a jump to the test. That gives a different shape (extra jump).

Actually target has: test at bottom (bnez back to top). And i's increment at the bottom. This is a do-while or a for-loop rotated by loop.c (loop.c can invert loops to put the test at the bottom — "loop inversion"). In 2.7.2, loop.c has a loop rotation pass (the `loop.c` `maybe_never` ...). If a for loop gets rotated, the test is duplicated: once at the top (before the loop, as the initial guard `if (cnt != 0)` — YES! Our code has `if (cnt != 0) {` guard which is exactly the rotated-loop guard!). 

Look: the source has `if (cnt != 0) { lim = ...; do {...} while (i < lim); }` — the do-while shape.

Hmm, so where does the target's `move v0,v1` at 21f0 come from — `cnt = n` copy to v0 for the beqz guard, and `move s2,v0` for the loop bound.

OK let me try a slightly different tack: use a `for` loop instead of do-while, with the guard:
```
for (i = 0; (s32)i < cnt; i++) { ... }
```
and see what happens.

Actually, let me look at the earlier G28x MATCH for a similar barrier (moves.md 318): "param-direct a0 (s0 pin gone); do-while around the unkC4 load + empty do-while after the unk58 store: sched1 keeps sw 88 before the RMW". Not our case.

Line 335: "WALL sched1-birth-order — s8 two + do-while two=2 fixes the v1/v0 swap; do-while around the 0x10 store fixes the store sink; residual is sched putting lui v0,0x20 (unk14) before li a0,2432 (call arg) — target reverses them, only a memory barrier holds it".

Let me look at whether there's an existing moves.md entry for a delay-slot fill problem — "dbr"/"reorg"/"delay" in moves.md.
