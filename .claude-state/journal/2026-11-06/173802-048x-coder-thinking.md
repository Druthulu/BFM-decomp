---
ts: 2026-11-07T00:38:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Bi57JUiJGuPyHZifKIy9
---
Lever-free: score 6, same insn count (71). The difference: `lui v0; lw v0; li v1,1` (the val load + li) is at position 39 in mine but at 32 in the target — i.e., the target births the val load EARLIER (right after the jal's delay slot at 8404, before the three constant stores at 8414+).

Target order: 8408 lui v0; 840c lw v0; 8410 li v1,1; then the stores. Mine: the stores first, then the val load.

This is the sched1-birth-boost wall: the value's load is scheduled later because its birth (the insn) is placed later in the source, and sched1's priority depends on the insn's LUID (birth order). The target has the val load earlier — before the D_801B7948/4C/50 stores.

In the source, `val = D_801B7A84;` comes AFTER the two calls and BEFORE the stores. The target emits it before the stores (natural source order!). Mine emits it AFTER the stores. So sched1 (or the RTL order) moved it down in my version.

Why? Because `val`'s load has a "birth boost" in sched1: an insn with a single set and a short life gets boosted... The prior note says "sched1-birth-boost best 2, 13 tries".

In the target (pinned val to $2), the load has a hard-reg destination → different priority.

Lever-free: the load's pseudo gets v0 anyway (mine shows lui v0; lw v0), but sched1 schedules it later.

Hmm. So the fix: make sched1 schedule the load earlier. Options:
- Give the load a higher priority: e.g., make it feed an insn with a longer dependency chain, or use the loaded value in more places.
- Change the source order? It's already before the stores.

Wait, mine has the load at 39 — after the stores. Let me see the full listing of mine to understand the actual order. The diff shows only 2 hunks; mine[39:42] = lui v0; lw v0; li v1,1 deleted, and target[32:35] inserted. So mine's order is: ... stores ... then the val load.

So sched1 sinks the load below the stores (they're independent). In the target, the load stays before.

Since both have the same insn count, only order differs. What real-C move makes sched1 birth the load earlier?

sched1's priority = insn's "birth" (LUID) and dependencies. The three constant stores (`sw zero,0(at)` with lui at) are independent of the load. sched1 picks ready insns by priority: higher priority first. The load's priority depends on the length of the dependency chain it feeds: `val` feeds `addiu v0,v0,1` → `sw v0,0(at)` (the final store). The stores feed nothing.

Hmm, in the target the load is first. In mine it's after. The difference in the pinned version: val in a hard reg (v0) with a REG_DEAD/priority difference.

Real-C moves to try:
1. Make `val` feed more: e.g., use val twice.
2. Change where `val = D_801B7A84;` sits relative to the stores (move it earlier in the source, e.g., right after the call). In my w1 it's already before the stores in source. But sched1 reordered it. Hmm — wait, is it? My source: val = D_801B7A84; then the stores. Yes.
3. Use the value of `*p` instead? 
4. Add a dependence: e.g., `D_801B7988 = 1;` could use val...
5. Change the switch structure.

Hmm, what does the barrier do? In orig, the barrier is between `val = D_801B7A84;` and the stores. An empty asm with no clobber — it acts as a scheduling barrier for sched1 (asm insns have priority 1 and can't be reordered?). Actually an empty asm without memory clobber has no data dependence, but sched1 treats asm insns specially (can't move across? insn_cost LINK_COST_FREE). It probably prevents the load from sinking below.

So the barrier's role: keep the val load above the stores. A real-C way to keep them in order: create a data dependence between the load and the stores!

E.g., if one of the stores' values depends on val, sched1 must keep the load before it. But the target's stores are `sw zero` — no dependence. Hmm, but the dependency could be through the *address* register: the stores use `at` (lui at; sw zero,0(at)). In the target, `li v1,1` is between the load and the stores.

What if the source computes the constant stores in an order that forces the load first? Not by data dependence.

Alternatively: make the val load's *destination* be needed by the first store — e.g., if the source wrote the stores as `D_801B7948 = val - val;`? That's a launder (identity statement) — banned.

Hmm. Let's think about what sched1 does: it schedules within a basic block. The block here: from after the second jal to the end of case 0. Insns: lui v0; lw v0 (val); li v1,1; lui at; sw zero (×3); sw zero,0(s0); lui at; sw v1; addiu v0; lui at; sw v0.

Actually wait: in the target, `li v1,1` is at 8410 (right after the load) — and `li v1,1` is the constant for D_801B7988 = 1. So the target's order: load val, li v1,1, then the three sw-zero stores, sw zero,0(s0), then lui at; sw v1,0(at), addiu v0,1, lui at, sw v0.

In mine: the stores first, then the load at 39-41, then presumably the rest.

Since sched1's priority ordering: the val load's chain feeds addiu → sw. The stores' chain is short.

Hmm, how did the pin produce the target order? With `register s32 val __asm__("$2")`, the load's dest is a hard reg v0; local-alloc/global-alloc can't change that. The sched1 priority of a load: `insn_priority` = 1 + (number of dependents...) Actually sched.c: priority = 1 + sum over dependents? A "birth" boost applies to insns whose result is used once? Let me look at sched.c's priority computation.

Actually, the prior note says the wall tag is "sched1-birth-boost". Let me read sched.c's priority function.
