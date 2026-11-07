---
ts: 2026-11-06T01:49:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xuSmk7lDYmHMD0Fu65Dk
---
So order: sched2 → jump2 (cross-jump) → dbr_schedule (reorg, fills delay slots). So jump2 is before reorg. My earlier reasoning holds.

So at jump2, dec's store is before the jump (not yet in the delay slot). Merge happens. Target says no merge. Therefore at jump2, in the target build, something differed.

What if the original C's dec block's store was NOT before the jump at jump2? E.g., if the dec block's store were a separate basic block or the jump were conditional? Target dec: lw; nop; addiu; j; sw. The store is in the delay slot — placed there by dbr_schedule from before the jump. So at jump2 it was before the jump.

Unless the target's dec block had the store *after* the jump already at jump2 — i.e., the store was placed in the delay slot by an earlier mechanism? No.

Hmm, what if in the original the dec block's `unk1C--` store and the jump were arranged so that jump2 didn't cross-jump because the jump was a *conditional* one? No, target shows j.

What if the original's zero block ended with a jump to the epilogue that was deleted at jump2 itself (not the first pass)? Then the merge would be prevented as I described. But the mini test showed the LAST return in a function is elided at expansion (fall-through), so no jump. BUT: maybe the elision only happens for `return;` as the last statement of the function body — and in the original, the zero block was not literally the last statement: e.g., the original had the zero block inside an `if (...) { ... }` at the end, or the function had a trailing `goto`/label. Hmm.

Actually, look at the mini test: `void f(int *p) { if (p[0]) { p[1]=2; return; } p[2]=3; return; }` → the final `return;` was elided (fall-through to $L1). But the first return emitted `j $L1`.

What if the last statement in the original was a `return;` inside an if-block, e.g.:
```
if (t == 0) { ...; return; }
```
as the last statement? Then the return is inside a conditional block. Does the expander elide it? The elision in the mini test: the last return was at top level. Inside an if-block, `return;` emits a jump (the compiler doesn't know it's last?). Let me test: `void f(int *p){ if(p[0]){p[1]=2;return;} p[2]=3; }` vs with the return inside.

Actually the C structure of our function: the zero block is reached by `goto zero` from the t==0 test, and the zero statements are at the end. The original might be:
```
if (t == 0) {
    ...zero...;
    return;
}
```
Hmm, but the target's zero block is reached by `beqz v0, 17d0` — a conditional branch to the zero block, and the zero block is at the end. If the source is `if (t==0) { zero...; return; }`, the compiler emits: test; beqz → zero_label; ... other code ...; zero_label: ...; return (elided as last?).

Wait, in the current src, the structure is `goto zero` with labels — a reconstruction. The ORIGINAL C likely had an if/else structure! The `goto`s were invented to match the layout. Maybe the original is:

```
t = unk1C;
if (t != 0) {
    if (t >= 0x1E) { unk1C--; return; }
    if (unkFE >= 3 && func_8012BD3C(...) == 1) {
        shared...; return;
    }
    if (func_8012BD3C(a0,0x2C0,0x31000) == 1) {
        if (func_80185D3C(a0,1) != 0) { shared...; return; }
        ...; return;
    }
    r = func_8012B8E4(a0,0x10);
    unk12 += r;
    unk1C--;
    return;
}
// zero block
...;
unk1C = 0x1D;
```

That's an if-block whose fall-through is the zero block. The zero block's last statement is the store, and there's no return at the end → falls off the function end. That's the same as our current structure (modulo gotos). So still no jump.

Hmm, so the merge should happen in the original too... unless the original's zero block ends with a return that the compiler keeps because it's inside the if-block? If the source were:

```
if (t == 0) {
    ...zero...;
    unk1C = 0x1D;
    return;    // inside the if-block, not the last statement of the function
}
```
then the function body ends with the if statement, and the `return;` inside the block is the last statement executed. Does expander elide it? The elision happens in `expand_null_return` when `use_goto`... Hmm, actually where is the elision? Let me find: in the mini test the final top-level return was elided. Where? Possibly in `expand_function_end`: if the last insn is a jump to the return label, it's deleted as "jump to next" by the first jump pass (not the expander). Let me verify with the mini test's -dj dump: check whether the jump existed at .rtl and was deleted at .jump.

If the elision is the first jump pass's jump-to-next deletion, then a return inside an if-block would also be deleted (same pass). Unless the return's jump target is not the next insn at that pass.

In the mini test, the final return's jump target $L1 is immediately after → deleted. Same for a return inside an if-block at the end.

So how can ANY C shape keep a jump to the return label until jump2? Only if the return label is not immediately after the jump at the early passes — i.e., there's other code between the zero block and the return label. But the target's layout has zero directly before the epilogue... 

UNLESS the epilogue label is NOT the target of the zero block's jump in the original! What if the zero block's trailing jump targets a *user* label, and that label is where the return label later lands... Hmm.

Alternatively, maybe the original's zero block is not immediately before the epilogue in RTL order at jump2, and the final layout (zero before epilogue) is achieved by dbr_schedule moving code? dbr can move insns into delay slots but not reorder whole blocks.

Hmm, hold on. Let me reconsider the actual merge condition. find_cross_jump(insn=dec's jump, JUMP_LABEL(insn), minimum=1). i2 = PREV_INSN(label), skipping NOTE/CODE_LABEL. What if between zero's store and the label there is a BARRIER? A barrier would stop it (i2 = barrier, i1 = store → differ). When is a barrier emitted? After a jump insn! If the zero block ended with a jump, there'd be a barrier after it: store, jump, barrier, label. But then i2 = barrier. Right — that's the vA case, and the merge was avoided at the first pass... but vA's jump was deleted at the first pass, leaving store, label.

So the question remains: why was vA's jump deleted at the first pass? Let me find the deletion. Let me test the mini case: compile with -dr and -dj and compare.
