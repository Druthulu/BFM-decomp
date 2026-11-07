---
ts: 2026-11-06T12:28:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y950tMMVtITuEghupxWg
---
rare_destination(insn) = 0 for the target label (CODE_LABEL). rare_fallthrough = rare_destination(NEXT_INSN(jump_insn)) = also a CODE_LABEL? NEXT_INSN of the jump is the insn after — no label, it's the insn itself → the loop starts at an INSN, continues to next insns until a CODE_LABEL → returns 0. So both 0 → difference 0 → fall through to condition switch: EQ → 0.

So we can't easily flip prediction without changing the condition.

New approach: change the C structure to eliminate the need. What if the loop body's increment is written so that the increment appears in the then-arm's end? Hmm.

Actually, wait. Let me reconsider: maybe there's a completely different pure-C structure giving the same insns. The essential target sequence:

```
2200 top:
  sll v0,s1,0x10 ; sra a2,v0,0x10 ; sll v0,a2,1 ; lui at ; addu at ; lh v0 ; nop
  beqz v0, L2238
  addiu v0,s1,1        ← delay
  move a0,s0
  jal
  move a1,s3
  move s0,v0
  addiu v0,s1,1
L2238: move s1,v0
  sll v0,v0,0x10 ; sra v0 ; slt v0,v0,s2 ; bnez v0, top ; addiu s3,s3,32
```

The `move s1,v0` at the join is a cross-jump merge: both paths compute i+1 in v0 then a single move to s1. That's cross-jumping (jump.c / cross-jump pass). gcc 2.7.2 has cross-jumping in jump.c? Yes, cross-jump in jump.c (jump_optimize) merges identical tails.

Hmm, what if instead the source computes `i = i + 1` in the then-arm and in the loop tail? No.

Alternatively, maybe the source form is:
```
do {
    if (x != 0) { ot = call(...); }
    i = i + 1;
    panel += 0x20;
} while (...);
```
which is what we have. The increment computed at 2234 (fall-through path) and 2230... Mine: 2230 addiu, 2234 move s1,v0. Target: the addiu appears in the beqz delay slot as a duplicate and at 2234.

So the entire difference is which insn went into the beqz delay slot: `move a0,s0` (mine) vs `addiu v0,s1,1` (target). In mine the `move a0,s0` sits in the delay slot instead of before the jal; target has it at 2224 (before jal). So the target's arm is 5 insns (move a0; jal; move a1; move s0,v0; addiu) vs mine 4 (jal; move a1; move s0,v0; addiu) + delay slot.

Total insns: target 175, mine 174.

Is there another C form where the fall-through head is ineligible? The `opposite_needed` set at the target label (2238): v0, s2, s3, sp, ra. If the call arm's first insn sets s3... 

Wait — what if `panel` (s3) is computed in the arm rather than read? E.g. if the arm passes `panel` but panel were incremented before the call? No.

Hmm, what about the argument `(s32)i`: if gcc emitted the arg setup for a2 first (as `sll/sra` writing v0 → then move a2,v0)... The target's a2 already holds i due to the loop's index computation. What if we write the call as `xf(ot, panel, (s32)i)` and gcc's arg order is a0,a1,a2 — first a0.

What if we reorder so the call's first argument is a value needing computation that writes v0? E.g., pass `(s32)i` as the first argument: `ot = xf((s32)i, panel, ot)`? Changes semantics — no, the call signature must stay: `xf8017E1D4(s32 *, s32, s32)` = (ot, panel, i). Can't reorder args.

Alternatively use a temp: `s32 k = (s32)i; ot = xf(ot, panel, k);` — where would k go? If k were assigned in the arm, the assignment `k = (s32)i` emits sll/sra to some reg (maybe v0? then move a2,v0) — the target has no such insns (a2 already holds). Since gcc's arg promotion would need it in a2. Actually if we compute `s32 k = (s32)i` inside the arm, gcc emits sll v0,s1,16; sra a2,v0,16 — writing v0 at the arm head! Then the fall-through head would be `sll v0,s1,0x10` which sets v0, live at the target → rejected → reorg takes the taken thread. But we'd add 2 insns (the sll/sra) that the target doesn't have. Unless gcc reuses the existing a2... no, it would recompute.

Hmm. So we'd get 176 insns. Unless combine/cse deletes the duplicate sll/sra? cse would see `sll v0,s1,16` already computed at the loop top (same value, no store between) → cse2? Actually cse1 runs before loop; within a loop iteration, the top's sll v0,s1,16 and the arm's are the same expression → cse1 would CSE them into one, making the arm's use the top's v0 — but v0 is overwritten by lh v0 at 2214! So no.

OK, another angle: use a `goto` to make a label that redirects. Hmm.

Alternative: maybe we should make the *increment* the fall-through head by restructuring: 

```
do {
    if (x != 0) {
        ot = xf(ot, panel, (s32)i);
        i = i + 1;
        panel = panel + 0x20;
        continue;   /* or goto */
    }
    i = i + 1;
    panel = panel + 0x20;
} while (...);
```
No, that duplicates code.

Let me step back. Maybe the item can be solved by keeping a *different* kind of lever that is allowed: the constraint says "levers of other kinds the def already had (pins under other causes) may stay, never added". The kinds here are barrier, keepalive, pin. The empty asm is a barrier. So no asm at all.

Hmm, what about C0535 (do{}while(0) splits cse1 EBB) — that's a real C move! A `do { } while (0)` around a statement splits the EBB in cse1, which changes scheduling/scheduling boundaries. Could a do-while(0) around the call make the fall-through head ineligible? The EBB split adds a NOTE_INSN_LOOP_BEG/END and a BARRIER? In cse1, `do{}while(0)` creates a loop note but not a real barrier at the RTL level... Actually C0535 says it splits cse1 EBB. Hmm, it might create a NOTE_INSN_LOOP_BEG which reorg's mostly_true_jump uses: "If this is the test of a loop, it is very likely true. We scan backwards from the target label. If we find NOTE_INSN_LOOP_BEG before the next real insn, we assume the branch is to the top of the loop" → returns 2!

So: if we place a `do { } while (0)` such that a NOTE_INSN_LOOP_BEG lands immediately before the branch target label (the increment path), mostly_true_jump returns 2 → prediction > 0 → reorg tries the target thread first → steals `addiu v0,s1,1` → target shape!

How to arrange: wrap the increment in a do-while(0):
```
do { i = i + 1; panel = panel + 0x20; } while (0);
```
Hmm, the loop notes: for `do { A } while(0)`, gcc emits NOTE_INSN_LOOP_BEG before A's code, then at the end a test `while(0)` — combine removes the test since 0 is constant → deletes the loop, but the notes? Typically gcc's loop notes for a do-while(0) get deleted when the loop is deleted... C0535 says it splits cse1 EBB — so something survives.

Alternatively wrap the call arm in a do-while(0)? The target label region is the increment. Hmm.

Wait, actually there's a subtlety: where does the label sit? The branch target label is at the increment. If the loop-begin note lands just before the increment's label, prediction = 2.

Let me try: wrap the increment statements in do{}while(0):
```
do {
    i = i + 1;
    panel = panel + 0x20;
} while (0);
```
Hmm, but if gcc's loop optimization deletes the do-while(0) entirely and removes notes, nothing changes.

Alternative: put the whole `if` inside a do-while(0):
```
do {
   if (x) { call; }
} while (0);
i = i + 1;
```
Then the NOTE_INSN_LOOP_BEG would be before the if, and the LOOP_END after → when the "loop" is deleted (constant test 0), the notes... 

Let me just try a few and observe. Cheap: each dt.sh run is a compile. Let me set up a batch of candidates and use sc.sh.

Also I still need to fix the tail store order (struct alias). Let's do both changes in candidates.

First, let me test the tail fix alone (struct alias) to see it works, then tackle the delay slot.

Actually, wait. Before elaborate experiments, consider that maybe the (s16) casts I used for cnt/lim already changed things vs. the zr pin. The score was 8 with 174 ins. Fine.

Let me create c2 = c1 + D_801151D0 struct alias.

For the alias: local struct type. In C, declaring a struct type inside a function is allowed. Then `extern struct S D_801151D0;` at block scope conflicts with the TU-level declaration if one exists. Let me check if D_801151D0 is declared elsewhere in the TU.
