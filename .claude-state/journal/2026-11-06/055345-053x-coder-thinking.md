---
ts: 2026-11-06T12:53:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rSJ2dNhcTNzoiI18hACG
---
b3 (volatile pointer local) = 11, same as a5.

Let me examine a5/b3's diff in full to understand what's needed. The residual:
```
mine 58 lbu v0,0(v0); 59 nop; 60 andi v1,v0,0xff
target 58 lbu v1,0(v0)
```
Hmm, mine has an extra nop and andi. The nop is a load-delay nop. Target has none because it's `lbu v1,0(v0)` and the next insn doesn't use v1 immediately.

Also target's case-3 `lhu v0,0(s0)` reload vs mine folding.

Two problems. Hmm.

Wait, actually maybe the target's `lbu v1,0(v0)` (into v1) vs mine `lbu v0,0(v0)` — the target loads into v1 and compares `beq v1,v0`... 

Let me look at the diff again: mine[58] lbu v0,0(v0), target[58] lbu v1,0(v0). Then mine has nop+andi, target nothing. So target's dispatch load is `lbu v1,0(v0)` with v0 = address and v1 = value, and the andi is absent because gcc knows lbu zero-extends (dsp is s32, u8 load). Mine's volatile load gives an extra andi because... the volatile load in QImode then extended with andi? That's gcc's `load` + `zero_extend` for volatile (can't use the lbu's implicit extension because the mem is volatile? no...).

Let me try `dsp = *(volatile u32 *)...`? No, wrong semantics.

Alternative: what if the volatile access is a *store* to a scratch location? Adds a store insn.

What if I use a volatile read of a *different* variable that's already loaded? Hmm.

Idea: use `__asm__`? no.

Idea: the barrier is needed to invalidate cse memory. What if instead I use a real C construct that changes the memory state between the dispatch load and case 3: e.g. the `p[0x4E] -= 1;` store? That's before.

The dispatch block: after `dsp = sv[idx]`, the switch. Case 3 reads `tbl[p->unkA]` and `p[0x50] = 0`. The target reloads p->unkA (lhu 0(s0)) in case 3.

Mine (barrier-free) folds the dispatch-loaded idx into case 3's call arg (reusing a0).

To force a reload without the barrier: the `p[0x50] = 0` store would invalidate memory for a *following* load — but the load comes before the store in target (mask = tbl[...]; p[0x50]=0; call). Hmm, target: `lhu v0,0(s0)` (reload of p->unkA) then `sll` then table access, then sb.

So the reload happens at case 3 entry, before any store in the case. What invalidates cse there? The barrier in the dispatch block.

Real C: could I put the barrier's effect in the dispatch via a *volatile read of p->unkA*? That's a4 = 13/344 (one extra insn: probably the lhu is fine but the reload...).

Hmm, a4 was `idx = *(volatile u16 *)(p + 0xA);` = 344 ins, score 13. One extra insn. Let me look at a4's diff — maybe it's closer.

Actually, let me think about the structure differently: maybe I can get the reload by making the case-3 index read a *separate expression* that cse can't fold because the dispatch `idx` variable is not the same pseudo. E.g.:

```
idx = p->unkA;      // dispatch
dsp = sv[idx];
switch (dsp) {
case 3:
    mask = tbl[((Unkstruct_80030CA4 *)p)->unkA];   // reads p->unkA again
```
Here case 3 reads p->unkA directly (not idx). cse would still know p->unkA is unchanged (no memory clobber) and reuse idx's value... but does cse forward a *load* across the switch? cse's memory table should still hold p->unkA = idx. So it folds.

To break that, we need something that kills the memory table. Real options: a volatile access, a call, or a store to memory.

The `sv[idx]` load itself doesn't invalidate.

What if `sv` is a `u8 *volatile`? That's a volatile pointer variable (the pointer's storage volatile), not the pointee.

What if I make the dispatch read of `p->unkA` a volatile read (a4)? Then cse's memory table is invalidated by the volatile load, so case 3's plain `p->unkA` read must reload. That's exactly what a4 does (13, 344 ins). The extra insn: probably the andi or a nop.

Let me look at a4's diff.
