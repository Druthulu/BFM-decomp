---
ts: 2026-11-06T10:46:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_enwzV0NfII9Qr7o2T4uD
---
The key: `memrefs_conflict_p` decides if the two addresses could overlap. Let me look at memrefs_conflict_p: it's in alias.c? In gcc 2.7.2 it's in sched.c maybe. Let me grep.

If both addresses are `(plus (reg) (const))` with the same reg, memrefs_conflict_p returns 0 (provably distinct) — hence no dependence. To make them conflict, the base regs must differ, or one address must be a symbol.

So: use a *different* register for the load's base. How, in real C? A local pointer variable that gcc doesn't merge with a0.

What if the load's base is a variable loaded from memory? e.g., `Unkstruct_800B5CB8 *p = *(Unkstruct_800B5CB8 **)&someglobal;` no.

What about using the struct pointer that is stored at unk20? No, that's a different object.

Hmm, what about `t = ((Unkstruct_800B5CB8 *)a0)->unkC4;` vs stores `((Unkstruct_800B5CB8 *)a0)->...` — same base.

What if we use two different pointer variables: `p` for the earlier stores and `q` for the load, where p and q are both copies of a0? cse would merge them (make_regs_eqv) if they're equal. Unless one of them is derived from something else.

Hmm, what if the load's base is a pointer stored in a *local variable that also gets used as the base for the unk20 loads later*? The unk20 loads use `*(s32*)((s32)a0+0x20)` as a pointer.

Hmm.

Different approach: accept the sched1 hoisting but make the *register* assignment right and the store placement right by reordering the *whole tail* so that sched1's natural order matches. The hoisted load lands at the EBB start. So maybe move the unk2/unkC0/unkBC/unk5C stores into a different EBB (e.g., before the calls? no).

Wait — what if we split the EBB *before* the load using a construct that doesn't add instructions and doesn't disturb allocation: a `goto` label! A label creates an EBB boundary (cse1) but is free. E.g.:

```
unk5C = 0x8000;
goto L;
L:
t = unkC4;
```
A label with no jump to it would be removed. But `goto L; L:` is optimized away.

What about a label that is jumped to from an `if`? That adds a branch.

Hmm.

What about a `switch` with a single case? Might fold.

OK, alternative: maybe the target's schedule can be reproduced by making the load *not hoistable* via a dependence on a register computed from a previous store. Here's a thought: what if the load address uses the value stored at unk20? No, semantics.

Let me reconsider the do-while: d_S2S3S4 got score 2 with only the store position wrong. If I could get sched1 to put the store right after the address, we'd be done. In d_S2S3S4, block2 = [S3 addr, S3 store, S4 ori, S4 store, then the rest]. sched1 scheduled: lui, addiu, ori, sw, then (later) sw 88. Why did the store sink below the ori/sw? Because the store's dependence chain: sw 88 depends on addiu. The ori depends on the load (previous block, already complete) → ready immediately. sched1 picks the highest priority ready insn. The ori likely has higher priority because... its result feeds a store which feeds... hmm.

What if we make the store's address depend on a load from the previous block, so it's ready later? No.

What if we give the store a *higher* priority by making its value used later? Not possible.

Hmm, what if we reverse: compute the address of unk58 in the *previous* block (with the load), i.e., include the address computation in the do-while but not the store:

```
do { t = unkC4; a = (s32)&D_801907C4; } while (0);
unk58 = a;
unkC4 = t | 2;
```
Then block1: lw v0,196; lui v1; addiu v1. Block2: sw v1,88; ori v0; sw v0,196. In block2 the store is first in source; sched1 should keep it first (it's ready immediately). That gives exactly the target order! And t is in block1 (v0) and a in block1 (v1) — both in the same block, allocation by priority: t (2 refs: def in block1, use in block2 → global) vs a (def block1, use block2 → global). Hmm, both global; global-alloc assigns by priority: t has 2 refs, a has 2 refs; tie → order? t first → v0, a → v1. That matches the target!

Wait, but does the load get scheduled before the lui/addiu within block1? In block1: lw, lui, addiu — sched1 would emit the load first (it's first in source and independent). Good.

Let me test this: v_addr.

Actually, `a` as a local s32 variable = (s32)&D_801907C4. Then `unk58 = a;`. The emitted code: lui/addiu for the address, then sw. Same.

Let me try.
