---
ts: 2026-11-06T15:46:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M9KepC0BGWyzztUa1qCK
---
Mine: `lui s0,0; addiu s0,s0,24` — s0 = &D_800AF630 + 24, then `move a0,s0` twice.

Target: `lui s0,0; addiu s0,s0,0` (base), then `addiu a0,s0,24` twice.

So I need the base in s0 and the +24 at each call. The C: `mb = (u8 *)&D_800AF630; func_8004914C(mb + 0x18); func_800491AC(mb + 0x18);`

With the launder, mb's value is opaque after the first call → the two `mb+0x18` are computed with addiu off mb. But the base `mb = &D_800AF630` — the launder makes mb a *new* value; the allocator keeps mb in s0 (base) and each use does addiu.

Wait, but the launder is between the calls, so the *first* call's `mb + 0x18` is before the launder: cse would fold it to the constant `&D_800AF630+24`... but the target's first call is also `addiu a0,s0,24`. So both calls use addiu. Hmm, so the first call's argument is also computed as an add.

So how does the first call get addiu? With the launder at the top? No — the launder is between the calls, after the first call. Let me re-read:

```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
__asm__("" : "=r"(mb) : "0"(mb));
func_800491AC(mb + 0x18);
```
The first call's `mb + 0x18`: mb is a register holding the constant; the RTL `(plus reg_mb 24)` — cse's fold_rtx might fold reg_mb's known constant value... The first use is `(plus (reg mb) 24)`; cse knows mb = &D_800AF630 (a symbol_ref). It could fold to a const address. But the target has addiu for the first too.

Hmm, so maybe the launder also affects the first call by making mb's *birth* later? No.

Let me look at the orig's asm to see where the launder sits relative to the first call. Actually the asm comes after the first call in source. But the first call's addiu... Let me look at the orig's machine code around there (orig = target, score 0).

Target at 7714: `lui s0; addiu s0,s0,0` then jal 771c with delay `addiu a0,s0,24`, jal 7724 with delay `addiu a0,s0,24`.

So both calls' args are `mb+24` computed as addiu. The first call's expression `mb + 0x18` where mb = &D_800AF630: gcc's expand would emit `lui/addiu` for the symbol then `addiu` for +24 → but the allocator/cse may combine into `lui s0; addiu s0,s0,24`. In mine it did exactly that. In the target, the +24 stayed separate for both.

Why? Because the launder's opaque set of mb means the *value* of mb is unknown, so `mb+24` can't be folded into the constant. But the first call is before the launder...

Unless the asm's presence makes mb's constant value unknown from the start? cse processes the block in order: `(set mb (symbol_ref))`, then `(plus mb 24)` for call 1. At that point mb's value is known (the symbol) → could fold. But the target shows addiu for call 1 too.

Hmm, maybe the fold is blocked because the symbol address needs a register anyway, and cse's fold of `(symbol+24)` vs `(plus (reg) 24)`... In mine (a1) it folded to s0 = symbol+24. So cse/combine DID fold.

Wait, in mine the first and second calls both use s0 = symbol+24. The launder-less code: `mb = &D_800AF630; call1(mb+24); call2(mb+24)` — cse unifies both `mb+24` into one expression and combine folds the symbol+24 into the address. With the launder, mb is redefined between, so call2's `mb+24` is a different expression. But call1's could still fold.

Let me look at the orig's RTL for the first call. Let me dump the orig cse. Hmm, time. Let me instead try the dead-reset approach and see:

b1:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
func_800491AC((u8 *)&D_800AF630 + 0x18);
```
The second call's arg is the constant expression → gcc would emit lui/addiu (2 insns) for the symbol then addiu +24, or fold into lui/addiu of symbol+24 (2 insns). Target has addiu off s0 (1 insn) + s0 already holding the base. So a constant expression would need its own lui/addiu — 2 insns. Not matching.

So the second call must use a register holding the base. With the dead-reset, mb = 0 kills the base. Hmm.

What if we use a second variable holding the base:
```
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = 0;
mb2 = (u8 *)&D_800AF630;
func_800491AC(mb2 + 0x18);
```
cse would know mb2 = symbol and fold `mb2+24`... unless the dead-reset of mb kills the class that both share (the constant class). The moves note says: "the §373 dead-reset `q = 0; q2 = &sp18;` before the last call — cse's &sp18 class breaks, addiu a2,sp,24 and addiu a0,sp,24 rematerialise, no s0 address reg".

Hmm, "cse's &sp18 class breaks" — so assigning q2 = &sp18 after q = 0 means the constant class was invalidated by q = 0, so q2's value isn't folded? That seems odd: `q2 = &sp18` is a fresh set with a known constant; cse would record it.

Hmm, maybe the mechanism is different: cse's table entry for the *address expression* `(plus &sp18 24)` is invalidated when q is set to 0? No...

Let me look at the actual crack bodies in the shard dirs of G16x for func_80149374 and func_8014964C to see the exact C.
