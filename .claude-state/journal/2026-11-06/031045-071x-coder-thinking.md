---
ts: 2026-11-06T10:10:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZK0mPi63pK5oguQjlqa0
---
b8 (tb reused for unk50) changed the structure — now only v1->v0 x1 plus reordering. b8: t=unk4C, tb=unk54 then tb=unk50. So t is local (v0?), tb global. Hmm.

Let me look at b8's full instruction stream. Actually the diff shows mine 53 lw v0,76 (t=v0!) then 54 sh v1,14 (tb=v1), 55 lw v1,80 (tb=unk50 v1). Target wants unk50 in v0. So unk50 in v1 is wrong.

Interesting: b8 got t=v0, tb=v1! That's the right allocation for t and tb. The only problem is the unk50 value is in tb (v1) instead of t (v0).

So b8 fixes t=v0/tb=v1 by making tb global (2 defs). Now I need unk50 to be in v0, i.e., use t for unk50, not tb. But if t is used for unk50, t has 2 defs → global, and tb (1 def) → local v0. That's the original problem.

Unless... both t and tb have 2 defs! Then both are global, and global-alloc orders t (pri higher) → v0, tb → v1. And t is used for unk4C and unk50, tb for unk54 and... something else.

So: give t 2 defs (unk4C, unk50) and tb 2 defs (unk54, X) where X is a harmless second def that doesn't emit code but survives. What X? 

If tb's second def is dead, flow removes it. But maybe if tb is set twice with the second set being a copy from another live variable? E.g. `tb = t;` — that emits a move. Bad.

Hmm, but wait: in b8, tb has 2 defs (unk54, unk50) and is global. t has 1 def → local. Local-alloc gives t v0, then global tb → v1. And unk50 in tb=v1 (wrong).

What if I use BOTH t (2 defs: unk4C, unk50) and tb (2 defs: unk54, unk50)? Can't, one value.

What if the second def of tb is a copy that gets coalesced away? `tb = t;` where t is dead after → move t→tb, but if it's at the end and unused, flow removes it (dead store).

Hmm. What if tb's second def is via a conditional that's constant-folded? Like `if (0) tb = 0;` — removed by flow.

What about `tb = tb + 0;`? combine/fold removes.

Alternatively: make t global by 2 defs and make tb global by making tb's single def cross blocks. If tb is used in a different basic block, reg_basic_block = -1 → global. Can I make tb used in another block without code? 

The function structure:
```
if (cnt < 0x20) {
    if ((cnt & 7) == 0) {
        ... tb ...
    }
    idx = ...
    ...
    return;
}
... call ...
```
If tb were used in the outer block (after the `if ((cnt&7)==0)`), it would be multi-block. But using tb there emits code.

Hmm.

What if I move the `tb = unk54; unkE = tb;` OUT of the inner if into the outer block? Then code order changes (the target has it inside the `(cnt&7)==0` guard). No.

OK here's another thought: b8 gives t=v0, tb=v1 with tb global. What if I use `t` for the unk50 store but keep tb global by giving tb a second def from the unk50 value in a way that produces the same code? Like:
```
tb = unk54;
unkE = tb;
t = unk50;
unkA = t - 8;
```
t has 2 defs → global. tb 1 def → local. Back to square one.

What if instead:
```
tb = unk54;
unkE = tb;
t = unk50;
tb = t;          // second def of tb (copy)
unkA = t - 8;
```
`tb = t` is a dead store (tb unused after) → removed by flow. Unless tb is used after... 

What if:
```
tb = unk54;
unkE = tb;
t = unk50;
tb = t;
unkA = tb - 8;
```
Then tb has 2 defs and the final store uses tb. Code: lw tb(unk54); sh tb; lw t(unk50); move tb,t; addiu tb-8; sh. The move adds an instruction. Bad.

Hmm.

What if the second def of tb is the SAME value as its first via copy propagation? `tb = unk54; unkE = tb;` then later `tb = unk54;` again (reload) — the second load would be a separate insn (extra code).

OK, different approach: use `t` for unk4C and unk50 (2 defs, global) and make tb global by... using tb across a call? If tb's value crosses a call, is it still local? The local-alloc condition doesn't consider calls; only reg_basic_block and n_deaths. A single-block pseudo crossing a call is still local (it would be in a callee-saved reg). Hmm.

Wait — actually, maybe there's a simpler lever: the ORDER of qtys in local-alloc. tb is the only local qty that wants v0 in its range. What if I introduce ANOTHER local qty that's born before tb and lives across tb's birth, taking v0? Then tb gets v1.

The `li a0,2274` is a constant. What if the call argument is a variable: `s32 arg = 0x8E2; func_80147324(arg);`? Then arg is a local qty living 56-60, overlapping tb (53-58) → arg gets v0 (born 56, but tb is born 53...). Priority: arg (1 ref, life ~4, pri 0.25) vs tb (2 refs, life 5, pri 0.4). tb higher → tb gets v0 first. Hmm.

What if the constant store `sw zero,48(s0)` is replaced with a variable? `s32 zero = 0; s0->unk30 = zero;` → zero is a local qty, born before tb? Order: it's after tb in source. Hmm.

Let me look at which local qty currently gets v0 in tb's range. Actually tb IS in v0. If I add a qty born before tb (e.g., at insn 52) that lives past 53, it takes v0 and tb gets v1.

What about the `t` load? t is global, not local.

What if I make the first store's value a local temp: e.g. `s32 x = s0->unk4C; s0->unk6 = x;` — that's exactly t but if t has 1 def it's local. If t is local and born at 52, living to 54, it takes v0; tb born 53 → v1. Then unk50 needs v0 separately.

So: t (unk4C, 1 def, local) → v0; tb (unk54, 1 def, local) → v1; u (unk50, 1 def, local) → v0 (born 55 after t dies). This is the v4/b12 setup! But b12 had the scheduling issue AND t=v1, tb=a1.

Hmm wait, b12 showed t=v1 and tb=a1. So the local-alloc didn't give t v0. Why? Because in b12, t is declared at function scope but still 1 def... let me check b12's alloc table. Maybe t got v1 because of the ordering.

Let me dump b12's allocation.

Actually, in v4/b12, the `u` variable is separate, so t has 1 def → local. But the lreg showed t (r74) in the global order in nopin (2 defs). With 1 def, t would be local and get v0. But b12's asm showed lw v1,76 (t=v1). So something else.

Let me get b12's alloc table. Splice b12, dump, alloc_table. This is worth it.
