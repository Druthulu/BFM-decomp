---
ts: 2026-10-22T21:43:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1iStRfy74XaURu1ARme1
---
All ≥2. The `li` vs `sw ra` order.

Time: ~15:50. Item 3 started 15:41. ~10 min, 13 tries.

New idea: in item 2 the crack worked because the stores became the *initializer*, which is emitted before other insns. Here I could make the two s16 stores part of a declaration initializer of a *separate* local: e.g.

```
s16 a0v[2] = {0, -0x40};
*(s32 *)&loc.a.raw[0] = *(s32 *)a0v;   // no, changes asm
```
No.

Alternative: maybe I can move the `li` later by making the -0x40 value a *parameter-derived* expression that's computed late... but the asm has `li v0,-64` right after sw ra.

Hmm — actually, in the target the order is: sw ra; li v0,-64; sh zero,16; sh v0,18. So the li is right after sw ra. In mine: li; sw ra; sh zero; sh v0.

So only the sw ra/li pair is swapped. Both are independent. sched2 picks li first in mine.

Why? At the time sched2 makes the choice, both are ready; the tie-break (rank_for_schedule) decided. In the target, the barrier made sw ra... hmm, actually with the barrier, sw ra would be *before* the barrier insn in program order and the barrier blocks reordering — sched2 might not even consider moving sw ra past it.

What could make sw ra "not movable" in plain C? If a memory-clobbering insn followed it. A CALL would do that, but there's no call at the top.

What about a memory *store* whose address might alias the stack? A store through a pointer variable whose value is unknown (e.g. a global pointer): 
```
extern s32 *D_ptr;
*D_ptr = 0;   // memory op with unknown address before the li
```
That adds insns. No.

What about `loc.a.raw[0] = 0;` — a store to the stack, which is a memory op. It's insn 83? Hmm.

Since the stores are already memory ops with a stack address (constant), sched2's alias analysis says they don't conflict with sw ra (different offsets).

Idea: make the zero store's address *variable*: `*(s16 *)((u8 *)&loc + i) = 0;` with i = 0 (variable, not folded?) — if i is a variable the compiler can't fold, giving `addu` + `sh` → extra insn. No.

Hmm, what about `loc.a.raw[0] = 0;` written via a pointer: `s16 *p = (s16 *)&loc; *p = 0;` → p folds to sp+16 constant. Same.

I think this is another sched2 wall. But before giving up, let me reconsider: maybe I can make the li be born later — i.e., the -0x40 constant is materialized closer to its use. In mine, sched2 hoisted the li above sw ra. sched2 schedules bottom-up: it chose li at T-11 and sw ra at T-10 (later in program order = earlier in time?). Confusing.

Empirical: what if I put the *zero* store before... it already is.

What if the -0x40 store is the FIRST statement (c1) → score 3 (worse).

What if there are 3 stores... no.

Let me try: make `loc.a.raw[2] = -0x40` be `loc.a.raw[2] = 0xC0;`? Different value (u8 field) — but it's `*(s16 *)&loc.a.raw[2] = -0x40` → the bits 0xFFC0. Writing 0xFFC0 as an s16 constant = -0x40. Same.

Let me try a couple more: 
c8: `*(s16 *)&loc.a.raw[2] = -0x40;` where loc is declared as `S16_SC02_005_8017F7CC loc;` but the first statement is the b-copy (c4 = 11, worse).

c9: change the decl order: put `s32 iVar2;` after `loc`? No effect.

c10: make `iVar2` the first statement computed before the stores.

Let me test c10: move `iVar2 = ...unk204 - 1;` before the stores.

Actually, in the target, is the `subu` before or after the stores? Let me look at the target's full disassembly to see where the unk204 computation happens. If it's after the lwl/lwr copy, then moving it earlier changes asm.

Let me look at the target more fully.
