---
ts: 2026-11-06T10:11:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XYTqsm7IrRkD5oAXmJ7y
---
In b12: t = r74 (unk4C), tb = r76 (unk54), u = r75 (unk50). Dispositions: r74 in 3 (v1!), r75 in 2 (v0), r76 in 5 (a1).

So local-alloc gave:
- r74 (t) → v1
- r76 (tb) → a1
- r75 (u) → v0

Target needs t=v0, tb=v1, u=v0.

Why did t get v1 and tb get a1? The priority: all refs=2, live=12?? The "live 12" is weird. Let me check: r74 "used 2 times across 12 insns". Hmm, maybe the live count is from the global-alloc dump (different). But the priority tie-break should give r74 v0.

Unless the priority isn't 1666 for all — the table shows r74 v1 pri 1666, r75 v0 pri 1666, r76 a1 pri 1666. All tie. Lower allocno wins → r74 first. r74 should get the first free reg. Why v1 not v0?

In local-alloc's find_free_reg, it checks `regs_live_at` for the qty's birth..death. If v0 is live at insn 68 (birth of t), it can't use v0. What's in v0 at insn 68? From the RTL, insn 68 is the load of t. The preceding insn 65 is the store `sh ...,26(a2)`. Let me look at the RTL around 65.

Actually, the local-alloc "free reg" check uses `regs_live_at[insn]` which marks hard regs live at that insn. If v0 is live at 68 due to another pseudo's use, t can't take v0.

Hmm, in the nopin case, t was global and tb local. In b12, all three local. The local-alloc order/regs differ.

Let me look at the RTL around insns 60-70 to see what's live.

Actually, this is a rabbit hole. Let me consider: maybe I should accept that this item is a WALL with best 6, and move on. I've spent ~25 min. The requirement for WALL: ≥20 min and ≥30 scored tries. I've done about 6+25+16 = 47 tries. Good, the try count is satisfied. Time is ~25 min.

But let me give it one more shot with the b8 insight: b8 got t=v0, tb=v1 (correct!) with only 1 register pair off (v1->v0 x1) plus reordering. Let me look at b8's full dump and see if a small move fixes it.

b8: t=unk4C, tb=unk54, tb=unk50 (tb reused). Dump b8.

Actually b8's diff:
```
insert mine[52:52] target[52:53]
  52 -- | lw v0,76(s0)
replace mine[53:56] target[54:56]
  53 lw v0,76(s0) | sh v0,6(s0)
  54 sh v1,14(s0) | lw v0,80(s0)
  55 lw v1,80(s0) | --
replace mine[58:60] target[58:60]
  58 sh v0,6(s0) | sh v1,14(s0)
```
So mine b8 order: 53 lw v0,76; 54 sh v1,14; 55 lw v1,80; ... 58 sh v0,6. Target: 52 lw v0,76; 53 lw v1,84; 54 sh v0,6; 55 lw v0,80; ... 58 sh v1,14.

b8 has t=v0 (good), tb=v1 (good), but the schedule is different: the store sh v0,6 moved to 58. Hmm, and the tb load (lw v1,84) is at 52? Let me dump b8.

The b8 issue: unk50 loaded into tb (v1) but target wants v0. Actually b8's diff shows `55 lw v1,80` — unk50 in v1 (wrong, target v0). Wait the register pair count was v1->v0 x1. So one instruction has v1 where target v0. That's the unk50 load.

So b8: t=v0 ✓, tb=v1 ✓, unk50=tb=v1 ✗ (needs v0), plus scheduling.

If I use t for unk50 instead of tb: t would have 2 defs → global. But wait — in b8, t=v0 came from local-alloc because t has 1 def. If t has 2 defs, it becomes global and we're back to nopin.

Hmm, unless: in b8, tb is global (2 defs) and gets v1. What if t also has 2 defs but is ordered before tb? Both global: t (pri 10000, 4 refs) → v0; tb (pri ?) → v1. And unk50 uses t → v0. That's exactly the target!

So: t = unk4C, unk50 (2 defs, global); tb = unk54 + a second def (global). The second def of tb must not emit code. 

What if the second def of tb is `tb = tb;`? Flow removes dead stores... but maybe not if tb is used later? In b8, `tb = tb;` was a8 which gave 6 (same as base) — meaning tb=tb was removed (tb stayed local). So that doesn't work.

What if the second def of tb is a genuine second use that emits code identical to target? Hmm.

Alternatively — what if I make tb global by using it in TWO blocks, with the second use being in the `cnt >= 0x20` block that's already there? The else path has `((void(*)(s32))func_80146C3C)(arg0)` which uses arg0/s0, not tb. If I could use tb there... but tb isn't set on that path. Using an uninitialized tb would emit code.

Hmm.

OK here's another idea: make t global with 2 defs and make tb global via `volatile`? no.

What about: declare tb at function scope and assign it in the block, and ALSO assign it in the else branch (before the call), where its value is used as the call arg? No, that changes semantics/code.

Let me look at b8 more: maybe the schedule can be fixed to match target even with unk50 in v1? No, target clearly has v0.

Let me try: t 2 defs (unk4C, unk50), tb 2 defs (unk54, and reuse tb in the store of unk4C? no).

Alternatively, make tb global by giving it 2 defs where the second def is a copy of t used for a store: 
```
t = unk4C; unk6 = t;
tb = unk54; unkE = tb;
t = unk50; unkA = t - 8;
```
What if:
```
t = unk4C;
tb = unk54;
unk6 = t;
unkE = tb;
t = unk50;
unkA = t - 8;
```
still t global, tb local.

What if I introduce a second store via tb that's identical to an existing one and gets CSE'd? E.g. `unkE = tb;` twice → the second is dead (same store) → removed by cse.

Hmm.

Let me try a different tactic: make local-alloc give tb v1 by adding a preceding local qty that holds v0. In b8, tb is global. Let me instead try to make ALL THREE local and get the right assignment. In b12, t=v1, tb=a1, u=v0. The tie-break should give r74(t) v0. Why v1? Because v0 is live at t's birth. What's in v0 at insn 68 (t's birth)? Let me look at the b12 RTL around insn 60-68.
