---
ts: 2026-11-06T21:19:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1U6nWqsMgdSdCVQq0rc6
---
Confirmed: flow.c's insn_dead_p deletes the set (line 1479). The mechanism is flow. So the tag `flow-unused-result` is accurate. But the root cause is the void signature. Hmm.

Let me check line 1479 context to see the condition (maybe a `set` with REG_UNUSED). Actually, the dump showed flow deleted it. Good enough.

Now, the wall tag: walls.txt has both `flow-unused-result` and `expand-void-return`. The evidence: expand drops the return value (stmt.c:2622), flow deletes the dead set (flow.c:1479). The target's value is a "result computed but never used". `flow-unused-result` fits the observed deletion. `expand-void-return` fits the root. I'll pick `flow-unused-result` because the dump proves flow deleted it, and the walls.txt definition matches ("flow deletes results the target computes but never uses"). Actually, expand-void-return is specifically "void-return expansion drops a value the target keeps live" — also exact.

Given moves.md uses `expand-void-return` for the void-return family (func_800D2A24, func_801F0C4C, etc.), and our case is precisely "void fn, target keeps the exit value in v0", I'll use `expand-void-return`. Hmm, but our value isn't a return value in the C (it's `rv = (s32)a0`). The original C faked a return value. The target's move is the would-be return. So `expand-void-return` is apt.

Let me decide: `flow-unused-result` is the pass that actually removes it (verified by dump). The brief says "evidence = gcc pass + mechanism". So the tag should name the pass that causes the wall: flow. I'll use `flow-unused-result`.

Hmm, but the tag names in walls.txt: `flow-unused-result flow flow deletes results the target computes but never uses`. Exactly. Use it.

Now, time: 14:19ish. Need until 14:28. Let me continue with a couple more genuinely different attempts, then record.

Let me try one more class: making the value live via a *callee-saved* register by using it in the epilogue indirectly. E.g., the function has a local variable that's live-out? No.

What if we add a `return;` in the middle and the code after is unreachable but not deleted because of a label? E.g.:
```
rv = sp20; *a0 = rv; rv = (s32)a0;
if (0) goto skip;   // constant-folded
skip:
```
No.

What if we use a `switch` with a case that falls through and uses rv? Emits a branch.

What if we make the function recursive? No.

I think it's done. Let me spend the remaining time writing the notes.md and the log skeleton (useful work), then record at 14:28.

Actually, I can also start item 3 while "waiting"? No — one item at a time; the wall must be recorded at ≥20 min. But I could interleave: the time budget is wall-clock per item; if I work on item 3 now and come back to record item 2 later, the elapsed wall time for item 2 would include item 3's time, which is dishonest. Better to stay on item 2.

Let me do more analysis: examine whether the target's move could be produced by a *different* source function shape. Let me look at the 10-family siblings: maybe one of them has the same tail and is matched lever-free in the src, which would give a template. The comment says "Family of 10 / 430 templatable ins". Let me search the TU for functions ending with `*a0 = ...; rv = (s32)a0;` or similar. Actually, let me search the whole src for "move v0,s0" comments or for functions with a `$2` pin pattern.

Let me grep src for `__asm__("$2")` in this TU and nearby functions to see the family.

Actually, the comment at 3780 says "Family of 10". The family is probably functions with the same prologue/structure in this TU. Let me look for functions in this TU that have the pattern `func_8012B77C(...); ... *a0 = ...;` and a trailing v0. Let me grep for "$2" pins in the TU.
