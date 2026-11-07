---
ts: 2026-11-06T10:07:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NGtfV9WNFhMCtQAvfEy1
---
Still nop with plain call. So the copy pseudo is created regardless.

The root: reg73 = a copy of s0 made for the call arg, coalesced to a0. To avoid, we need the call to use s0 directly. In the target, s0 is pinned so the copy can't coalesce to a0.

Idea: make the call argument an expression that isn't a simple variable, so no copy pseudo: e.g. `func_80146C3C((u8 *)(s0 + 0));` — hmm, `s0 + 0` may be folded. `func_80146C3C((u8 *)(s32)s0)` same.

Alternatively, use the ORIGINAL arg0 instead of s0: `func_80146C3C(arg0);` — but arg0's value at that point is clobbered? In C, arg0 is the parameter; its value is still valid (the variable), but the compiler may have reused its register. Using arg0 directly might create a different copy. But semantically the function should pass s0 (which equals arg0). The target passes s0. If I write `func_80146C3C((u8*)arg0)`, the compiler might keep arg0 in a0... but a0 was clobbered by the struct copy. It would reload from... arg0's home? If arg0 is only used here and at the start, it might be in a callee-saved reg.

Hmm, but semantically arg0 == s0 only if s0 wasn't modified; s0 = (s32)arg0 and never modified. So `func_80146C3C((u8*)arg0)` is equivalent. But codegen: arg0 would be a separate pseudo from s0? Actually the compiler might merge them.

Alternatively, make the call argument be `s0` but prevent the copy-coalescing by making s0 and a0 conflict. Since a0 is clobbered by the calls before, maybe if the call arg pseudo can't take a0...

Honestly, this is one instruction (the delay slot). And the register swap is 6 diffs. To get 0 I need both.

Let me reconsider the register swap solution via "make tb global". Actually, here's a cleaner idea: make tb's *death count* 2 by writing the source so tb is set twice, with the second set being a copy that the compiler keeps. For example:

```
tb = s0->unk54;
s0->unkE = tb;
```
→
```
tb = s0->unk54;
s0->unkE = tb;
...
```
What if I reuse `tb` for the unk50 computation but store the result from a different temp? No.

Alternatively, what if the store to unkE uses tb and then tb is used as the source for the addiu? i.e.:
```
tb = s0->unk54;
s0->unkE = tb;
t = s0->unk50;
s0->unkA = t - 8;
```
t is reused (2 defs, global v0), tb 1 def local v0. Conflict.

What if I add a *second* use of tb in the same block that doesn't emit code but survives? E.g., `if (tb) {}`? That's a branch.

Hmm, what about making tb `s32 tb = 0;` (init at decl at function top) — the init sets tb in block 0, and tb used in block 2 → multi-block → global. But the init at top emits `move tb,0` at the function start — extra instruction. Unless... the init is at the declaration inside the `if ((cnt&7)==0)` block:
```
if ((cnt & 7) == 0) {
    s32 tb = 0;
    ...
    tb = s0->unk54;
    s0->unkE = tb;
```
The `tb = 0` would be dead → eliminated. Hmm.

What if `s32 tb = s0->unk54;` at the declaration point (init at decl) and then use tb? That's still 1 def (the init) + 1 use = 1 death. Local.

OK, another angle: change t so it does NOT conflict v0 — i.e., make t's live range not overlap tb's. tb (v0) lives 53-58. t lives 52-59. If t's life were only 52-54 (first use) and the unk50 value were a separate pseudo, then t wouldn't conflict tb's range... but t also needs v0 for the unk50 part.

Wait, what if I split t: t1 for unk4C (lives 52-54) and t2 for unk50 (lives 55-59). Both local? t1 1 def 1 use → local. t2 1 def 1 use → local. tb local. Local-alloc priority order: t1 (pri 1, life 2), t2 (pri 0.5, life 4), tb (pri 0.4, life 5). Assign t1 → v0 (52-54), t2 born 55: v0 free → v0, tb born 53: v0 taken by t1 (live till 54) → tb → v1. Result: t1=v0, tb=v1, t2=v0. Matches target! And t2 (unk50) v0.

But the scheduling issue: without the anti-dependency (t reused), sched1 grouped the loads. In v4 (separate u), the stores moved to 58/59. Hmm. But wait — in v4, tb got a1, meaning the allocation was different. Let me check v4's exact schedule again: mine 52 lw v1,76; 53 lw a1,84; ... 58 sh v1,6; 59 sh a1,14. So the two stores moved after the unk50 load.

The scheduling is determined by sched1, which sees pseudos not registers. So whether t is reused or split affects dependencies and hence schedule.

To keep the target schedule with split t1/t2, I need a dependency forcing sh t1,6 before lw t2,80. Hmm.

What if t2 is initialized before... no.

Alternatively, maybe use `t` reused (keeping anti-dep) but ALSO split so the reuse creates 2 defs... no.

Hmm, what if the anti-dependency can be created by reusing the STORE's base? No.

Let me think about sched1's behavior: it schedules insns by priority. The store `sh v1,6(s0)` depends on `lw v1,76` (t1). It doesn't depend on `lw tb` or `lw t2`. sched1 chose to move the loads up. In the target (pinned), why did it keep sh at 54? Because with the pin, maybe the pseudo `t` was hard reg $? no, t wasn't pinned. Hmm.

Actually in the orig, tb is pinned to $3, and the `sh $3,14(s0)` uses hard $3. But the first store is `sh t,6` where t is a pseudo. The target order 52 lw v0,76; 53 lw v1,84; 54 sh v0,6; 55 lw v0,80. 

Why would sched1 keep sh at 54 in orig? Possibly because in orig, the RTL order after earlier passes differs. Hmm.

OK, I've spent a lot on this item. Let me check the clock and decide. The budget is 20-30 min per item. Let me record the time.
