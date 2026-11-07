---
ts: 2026-11-06T10:14:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qewAB304XgggNpjqL575
---
Baseline 0, 188 insns. Lever-free 186.

The 2 missing instructions: the `y = t + zr` and `y = t2 + zr` copies (addu). Also `r2 = r + zr` — that one might be folded into the later use.

To reproduce the copies lever-free, I need `y` to be a distinct pseudo from `t`, and `r2` distinct from `r`. Since `t` is live after `y = t`, the copy should survive unless cse merges them.

Idea: make `y` live in a way t isn't, forcing a copy. Actually cse's copy propagation: if `y = t` and no redefinition, it replaces y with t. To break equivalence, modify t after the copy: `y = t;` then `t = t;`? no.

Alternative: compute y via an expression that's a copy but cse can't prove: `y = (t & 0xFFFFFFFF);` folds. `y = (s32)(u32)t;` folds.

Hmm. What about using a second variable initialized: `s32 y = t;`? Same.

What if `y = t` appears inside a conditional? no.

Maybe the 2 instructions come from something else. Let me compare the lever-free stream with target fully to see where the 2 insns are. Let me dump nopin and diff carefully. I'll use dumpbody.py.

Actually, the diff showed mine[12] `nop` vs target[12] `addiu a0,v1,-296`; mine[14] `addiu s4,v1,-296` vs target[14] `move s4,a0`. So the scheduling differs around there, not necessarily count.

The 2-insn deficit could be anywhere. Let me dump both streams.

Given the time, let me just do the bulk variant approach. But first, let me think about whether a "copy" can be forced: 

In the target, the sequence for `y = t + zr`:
Let me look at the target's instructions near the start. From the diff: mine[8] sw s2,72 / target sw s3,76. mine[11] lh v0,44(s3) / target lh v0,44(s2). mine[12] nop / target addiu a0,v1,-296. mine[13] beqz / target beqz. mine[14] addiu s4,v1,-296 / target move s4,a0.

Hmm, target has `addiu a0,v1,-296` at 12 (in the delay slot?) and `move s4,a0` at 14. That's `t = D_80127190 - 0x128` computed into a0 then moved to s4? That's the zr copy: y = t + zr → `addu s4, a0, $0` = `move s4,a0`! And t itself is in a0. So y=s4, t=a0.

Mine[12] nop, mine[14] addiu s4,v1,-296 — so mine computes t directly into s4 and there's no separate y. So the copy is gone: t and y merged.

So to reproduce, y must be a separate pseudo. In target, t is in a0 and y in s4 (both callee-saved? a0 is caller-saved; hmm).

Lever-free, `y = t` merges. How to keep them separate with real C? 

Trick: make y's value not literally equal to t's expression. E.g., compute y = t + something that's zero but not constant-foldable... that's a launder (forbidden).

Real C move: use y before t is assigned? no.

Alternative: reorder so that `y = t` is needed: if t is reassigned after y=t, the copy is required. t isn't reassigned. But `t2 = y - (...)`, then `y = t2` — t2 and y could merge too.

Hmm, what if we write the code with different variables such that the copy is naturally required, e.g.:
```
t = D_80127190 - 0x128;
y = t;
if (...) { ... }
```
Since t is used later (`(s16)t`), y=t is a live copy — but cse merges because they hold the same value and neither is redefined. GCC's cse `make_regs_eqv` merges them. To prevent, one must be redefined.

What if y is redefined in the if-branch? It is: `y = b + (D_8012718C - t);` in the branch. But cse works per-path.

Hmm.

OK, maybe the 2 instructions aren't the copies. Let me just count and locate. Let me dump.

Time management: let me spend 5 min on analysis, then bulk variants, then record.

Let me dump nopin vs target.
