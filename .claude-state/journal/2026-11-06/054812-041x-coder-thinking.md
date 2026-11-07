---
ts: 2026-11-06T12:48:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_raBZKvt28h4VNiAEFMUB
---
Hmm all 10. The dbr delay-slot fill happens regardless.

Wait — is it dbr? The fill of `beqz`'s delay slot with the else move is dbr's `fill_slots_from_thread`? Actually dbr only fills with insns from the *target* block, not the fall-through. Here the move at ba84 is on the fall-through path (after the branch), and the target is the join at ba8c. Hmm, that means gcc restructured: the else block is EMPTY (ua=ub coalesced into a move before?), no...

Look again at mine:
```
ba7c andi v0,a1,0x10
ba80 beqz v0, ba8c       ; if !tc goto ba8c
ba84 move a0,v1          ; delay slot: else value
ba88 addiu a0,v1,-256    ; tc value
ba8c lbu v0,0(s2)        ; join
```
Hmm, that's odd: if tc==0, branch to ba8c, and the delay slot executes move a0,v1 → ua = ub. Correct. If tc!=0, fall through, delay slot does move a0,v1 (wasted), then addiu a0,v1,-256. Correct. So gcc computed the else value in the delay slot and the tc value after. This is dbr filling the delay slot with the else insn because it's cheap and the else block is the "thread" target? 

Actually this is dbr's `fill_slots_from_thread`: the branch target is the join; the else insn... hmm, the else block must be located at ba84 conceptually but was placed in the delay slot.

In the target:
```
beqz v0, ba8c
<delay slot>
j ba90
addiu a0,v1,-256
ba8c: move a0,v1
ba90: join
```
Target has an explicit j. So in the target, dbr did NOT thread the else block.

What makes dbr thread? It threads when the target block can be reached... The delay-slot fill with an insn from the *other* path is `fill_simple_delay_slots`/`fill_eager_delay_slots`. For a conditional branch, dbr can put an insn that is executed on both paths in the delay slot only if it's safe. The move a0,v1 is safe (a0 dead on the tc path).

Hmm, so with the barrier, dbr chose not to. The barrier insn in the else block would be an insn that can't go in a delay slot? No, an empty asm is fine.

But the barrier splits the else block into two blocks, making the else block have 2 insns (asm + move) → the move isn't the whole block, so dbr can't thread it as a single insn? Possibly.

Real-C to make the else block have 2 insns without adding code: hmm.

Alternatively, prevent the eager fill by making the branch a `bnez`? c3b gave 3 with the inverted branch and a different residual.

Let me look at c3b/e2 (score 3) again: mine has `bnez v0,ba8c` and target `beqz`. And a missing addiu at 273 vs extra at 274. Let me dump e2's object around there.

Actually, maybe I should accept the barrier-3 case as the wall if I can't crack it in budget. But let's try a couple more ideas.

Idea: make `ua` and `ub` such that the else move isn't a plain register move — e.g. `ua = ub;` where ub is u16 and ua s32 → a zero-extend (andi) → 2 insns? But target's else is a plain `move a0,v1`, so no.

Idea: reorder so the branch is on the *other* condition and the arms are laid out as target. Target = plain if/else (tc first). Mine (f1) also = plain if/else but dbr threaded. Difference: target's beqz delay slot is filled with something else and there's a j.

What if the else block's insn is not a move but the target's `move a0,v1` where v1 is ub... 

New idea: use a *different variable* for the else value, e.g.:
```
if (tc) {
    ua = ub - 0x100;
} else {
    ua = sy;
}
```
Semantically identical (ub == sy). Then the else is `move a0, <sy reg>`. Same shape.

Idea: make the join block start with something that makes threading unattractive, e.g. put `ub = ua + rec->h - 1;` inside both arms? Then the join has different content. Let's try:
```
if (tc) { ua = ub - 0x100; } else { ua = ub; }
```
→
```
if (tc) { ua = ub - 0x100; ub = ua + rec->h - 1; } else { ua = ub; ub = ua + rec->h - 1; }
```
That duplicates 2 insns — target doesn't.

Idea: compute `ub` before the branch:
```
ub = ua + rec->h - 1;
```
after. Hmm.

Idea: change the branch condition to `tc == 0` vs `!tc` — same.

Let me look at the actual e2 residual more carefully (score 3) — maybe that's closer to target in the sense that only 3 insns differ and the layout is nearly right. Let me dump e2's object.
