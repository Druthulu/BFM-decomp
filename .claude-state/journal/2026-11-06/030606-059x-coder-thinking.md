---
ts: 2026-11-06T10:06:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UoYdMbn1JbAZD0ZK5Ryr
---
Same as v1: loads grouped, stores later, and registers t=v1, tb=a1?! Now tb is a1 (r78?) because the split changed allocation.

Hmm, the scheduling (loads grouped) is the issue. Why did nopin keep the store at 54 but v4 moves it? Because in nopin, t is reused for unk50, so the store `sh t,6` must happen before `t` is overwritten at 55 — a dependency! In v4, u is separate, so `sh t,6` has no dependency on the unk50 load, allowing sched1 to group loads.

So reusing t creates the anti-dependency that keeps the store at 54. But reusing t makes t global (2 defs), and tb local → conflict.

Hmm. So we need t reused (for scheduling) but somehow tb global.

Idea: make tb also have 2 defs so it's global. If tb is global, global-alloc allocates t first (pri 10000) → v0, tb → v1. And t stays reused for unk50 (anti-dep keeps scheduling).

How to give tb 2 defs while keeping the code identical? E.g.:
```
tb = s0->unk54;
s0->unkE = tb;
```
one def. Add a second def that's live, e.g., reuse tb for another store? There's no other natural use.

Alternatively, make tb 2 refs but with an extra def via a compound? Hmm.

Or: make tb's def in a different block (then it's global). E.g., hoist `tb = s0->unk54;` before the if? That changes code.

Or: use tb in an expression that forces a second set: `s0->unkE = (tb = s0->unk54);` still one set.

What about making tb a `s32` and doing `tb = s0->unk54; tb = tb;`? Dead.

Hmm.

Alternative: make t block-local by keeping the reuse but in a way that local-alloc handles 2 defs? Local-alloc can handle multiple defs? The table said t "in block 2; dies in 2 places" and it WAS in the global order line. So no.

Let me reconsider the v4 scheduling. In v4, mine: 52 lw v1,76; 53 lw a1,84; 58 sh v1,6; 59 sh a1,14; and presumably 55 lw v1,80? Let me dump v4 to see full. But the main issue is the store ordering. Could I add a dependency to force `sh t,6` before the unk50 load without reusing t? E.g., write the store before the unk50 load in source (it already is). sched1 reorders because no dep.

Hmm, what if I keep the reuse of t for unk50 but ALSO make tb global? Can't easily.

What if instead I make t NOT global by giving it 1 def but keep the anti-dependency via a different mechanism: e.g., use the same variable for the unk50 load but declare it as a different... no, same variable = same pseudo = 2 defs.

Wait — actually, does 2 defs really make it global? Let me verify: in orig (matching), t=r74 is in the global order too (order "74 76 77"). Yes, t is global in orig. And tb pinned. So t is global regardless.

So the goal: tb must be global (not local). Then global-alloc order: t (pri 10000) first → gets v0 (no conflict, since tb global won't occupy v0 yet), then tb (pri 2500) → v1 (v0 taken by t). And the local v0 occupancy is gone.

How to make tb global? Give it 2 sets, or make it live across blocks. 

Idea: initialize tb at declaration with a constant that ISN'T eliminated. E.g. `s32 tb = 0;` then `tb = s0->unk54;` — the first def is dead → eliminated. But if `tb` is used before reassignment? No.

Idea: use `tb` for the store AND keep it live: e.g.
```
tb = s0->unk54;
s0->unkE = tb;
```
then later use tb again? There's no later use in this block; using it after the call would make it live across the call → global for sure, but adds a ref and changes code.

Hmm, what about declaring tb `volatile`? Not allowed (new lever kind).

What about making tb's definition conditional? e.g.
```
if (cnt >= 0) tb = s0->unk54; else tb = 0;
```
adds code.

Alternatively, exploit a different mechanism: make local-alloc assign tb to v1 instead of v0. Local-alloc's qty priority: tb (r75) is the only local qty in block 2? The dispositions listed r75 in 2 (v0). If there were another local qty that also wants v0 with higher priority, tb might get v1. But then that other qty would be in v0 — could be fine if it's short-lived and dies before t's use.

Hmm, but t (global) needs v0 free during its life. If a local qty holds v0 during part of t's life, t still conflicts.

OK here's another angle: maybe make t's live range shorter so it doesn't overlap the local v0 occupant. t's range is 52-59. tb (v0) occupies 53-58. They overlap. If tb were assigned v1 by local-alloc (e.g., v0 occupied by another qty at tb's birth), then t could get v0.

What local qty is in v0 at tb's birth? r79, r80, etc. Hmm.

This is getting long. Let me try the direct approach: give tb a second def that survives. What if I write:

```
tb = s0->unk54;
s0->unkE = tb;
```
→ replace with:
```
tb = s0->unk54;
((Unkstruct_800CD314 *)s0)->unkE = tb;
```
same.

What if I make tb used as both s32 and the store, e.g. assign the store value through tb twice:
```
tb = s0->unk54;
tb = tb;  // dead
```
no.

Alternatively, restructure so tb is defined in a nested block that closes? Block scoping doesn't change pseudo count.

Hmm, let me check: maybe a simpler route is to accept the register difference but fix the delay slot, or vice versa. Score 7 is the best so far.

Actually — wait. Let me reconsider the "local" vs "global" classification. r75 (tb) was local. Why? Local-alloc handles pseudos whose reg_qty != -1. A pseudo is local if it's set and used within one basic block AND... "if it were used in more than one block, reg_qty == -1". t is used in one block too but got -1 because... maybe because t is set twice? Let me read local-alloc.c's scan. Search for "reg_qty\[i\] = -1".
