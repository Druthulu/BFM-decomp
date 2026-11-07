---
ts: 2026-11-06T08:53:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BPkI5otlF7mGy4IyfZju
---
Very relevant: line 134: "target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold, so cse keeps the copy; a C-level zero is a constant -> combine folds -> cse propagates (best 2)". So in that case the move was `plus v,$0` (an add of the zero register) — because the source added a hard-reg zero? That's a pin-ish lever though.

And line 47: "combine folds then-block copy v1=v0 into v0=v1-1; pre-test copy: cse canonical v1 rewrites the test".

Our target's move is a plain `move v1,s1` (addu v1,s1,zero). So combine merged.

Hmm. So maybe this item is a genuine wall: combine-copy-merge. But wait — the target code is achievable with the asm; the question is whether real C can. Given the many walls of this class, maybe this one is a WALL too.

But let me not give up yet. Let me reconsider the source: maybe the original C had the negation *before* the copy in a way that forces... 

Actually, let's reconsider the whole structure. What if the original source was:

```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```

The asm was inserted by the decompiler *because* combine merges. The original programmer's code must have been different. What if the original was:

```c
if (rand() & 1) {
    val = nudge;
} else {
    val = -nudge;
}
```
→ mine exactly (negu v1,s1). Not target.

What if the original was:
```c
s32 t;
...
if (rand() & 1) {
    t = nudge;
} else {
    t = nudge;
    t = -t;
}
val = t;
```
Same.

Hmm, what if the original else was:
```c
} else {
    val = nudge;
    val = -val;
}
```
where `val` was **u32** and nudge **s32**? The neg of u32 → negu; the copy s32→u32 might produce a SUBREG? On 32-bit, no.

What if `val` was declared as `s32 val` but the copy was `val = (s32)nudge;` where nudge is `u32`? combine still merges.

What if the original code used a **pointer** to val? no.

What if the original used a *macro* like `#define NEG(x) (0-(x))`? same RTL.

Hmm. What if the target's `move v1,s1` came from a *different* source statement: maybe the original had `val = nudge;` *outside* the if (before the branch) and the compiler's sched1 moved it into the delay slot... but the branch is after a call, so it can't move before the call. c5 shows the global register shift when the copy is before the call.

Unless the copy is placed after the call but before the branch: impossible in C unless the call is evaluated separately:
```c
s32 c = rand();
val = nudge;
if (!(c & 1)) val = -val;
```
Here `rand()` is called into c, then `val = nudge` after the call, then the test. The branch tests c&1. Target: jal rand; andi v0,v0,1; bnez v0; move v1,s1; negu. Hmm, with `s32 c = rand(); val = nudge; if (!(c & 1)) val = -val;`:
- jal rand
- move c, v0 (or andi)
- val = nudge (move v1,s1) — before the branch!
- andi v0,c,1 / bnez
- negu in the then.
The move would be before the andi/bnez, not in the delay slot. The target has the andi and bnez BEFORE the move. So no.

Unless sched1 moves the move down into the delay slot: reorg can move the insn before the branch into the delay slot only if adjacent. Order: move v1,s1; andi; bnez → the insn before bnez is andi, not the move. sched1 might reorder andi/bnez... hmm, the move is independent; sched1 could schedule: andi; bnez... no, bnez must follow andi (dependency). The move could be scheduled after the andi, right before the bnez? sched1 schedules the block [after the call] containing: move c,v0; move val,nudge; andi; beqz. It could put the copy last (just before the branch) → reorg fills the delay slot with it. That's exactly the target!

Wait, but in the target the copy is in the *delay slot* of the bnez, and the negu follows. If the source had the copy *after* the call and before the test, sched1 could schedule it into the delay slot. In c5, the copy was before the call (source order), so it stayed before. If instead the copy is after the call, it works.

But the target's bnez tests rand()&1 and the copy is in its delay slot — consistent with either structure.

So candidate:
```c
s32 c = rand() & 1;
val = nudge;
if (!c) {
    val = -val;
}
```
Hmm, but `c = rand() & 1` adds an `andi` and a move? The target has `andi v0,v0,1` then `bnez v0`. With `s32 c = rand() & 1; if (!c)`, the code: jal rand; andi v0,v0,1; (maybe move c,v0); then val=nudge; then beqz v0. Extra move for c.

Better: `if (!(rand() & 1))` — the call is in the condition, so the copy before it. No.

What about computing the call first but keeping the condition inline? C doesn't allow `if` after a call without a variable unless we use a comma in the condition:
```c
if ((c = rand() & 1) , !c) ...
```
ugly.

What about:
```c
s32 c = rand();
val = nudge;
if (!(c & 1)) val = -val;
```
Code: jal rand; move c,v0 (a move to a new pseudo — maybe coalesced); val=nudge; andi; beqz. The `move c,v0` might coalesce into v0 itself (c = v0). Then: andi v0,v0,1 after the val copy? Order: jal; (c=v0 coalesced); move v1,s1; andi v0,v0,1; beqz v0; negu. Hmm, target: jal; andi; bnez; move; negu. The andi is before the copy in target.

sched1 order: after the call, the block contains [copy val=nudge; andi; beqz]. sched1 might schedule andi first (it feeds the branch) and the copy into the delay slot. That matches the target! And the negu in the then-block. But the then-block here is `val = -val` (no copy) → `negu v1,v1`? val is in v1 (set by the copy before the branch), so negu v1,v1! That could be exactly the target!

Wait, but with `if (!(c & 1)) val = -val;` the branch is beqz v0 (if c&1 == 0 → negate). The target's bnez v0 jumps over the negu when rand&1 is nonzero. With `if (!c)` where c = rand&1: beqz → negate; bnez → skip. Target: bnez v0, L (skip negu). So `if (c)` → then-block negate, else skip: bnez to skip? Let's see: `if (c) { negu }` — gcc emits `beqz v0, skip` (if c==0 skip). Target has `bnez v0, skip` — meaning the negate happens when c==0. So the source is `if (!(rand() & 1))` / `if (c == 0)`.

But the call must be before the copy in source order. So:
```c
s32 c = rand();
val = nudge;
if (!(c & 1)) {
    val = -val;
}
```
Hmm, but `c = rand()` then `c & 1` — the andi is computed at the test, after the copy in source order. sched1 could still order the andi before the copy (it's a dependency for the branch). The copy is independent → scheduled into the delay slot. Plausible!

But wait: does the original code even look like that? The original source is from the game; the decompiled version has `if (rand() & 1) { val = nudge; } else { val = nudge; val = -val; }`. The original might well be:

```c
val = nudge;
if (!(rand() & 1)) ...
```
but the call order issue. Hmm, in the original binary, the call to rand happens before the copy — so the original source had the rand() call before the copy. If the original were `if (!(rand() & 1)) { val = nudge; val = -val; } else { val = nudge; }`, the copy is inside the branch after the call → the copy is in the then block, and the target's delay-slot move would be the then-block's copy... 

Let me test c14: 
```c
s32 c = rand();
val = nudge;
if (!(c & 1)) {
    val = -val;
}
```
and c15:
```c
s32 c = rand();
if (!(c & 1)) {
    val = nudge;
    val = -val;
} else {
    val = nudge;
}
```
Hmm, c15 keeps the if/else with copies inside — combine would merge the then-block copy+neg again (same block). No.

c14 has the copy outside the if (before the test) → combine can't merge (different blocks). The copy is after the call. Let me test c14.

Also c16:
```c
s32 c = rand();
val = nudge;
if (c & 1) {
} else {
    val = -val;
}
```
equivalent.

Let me test c14 first. Need to add `s32 c;` declaration — but that adds a variable; the target's registers: v0 is used for rand's result and the andi. If c is a new pseudo it may get v0 (coalesced). Let's see.
