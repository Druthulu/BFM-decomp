---
ts: 2026-11-07T00:45:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dF16fxqNvnkrKGga2Vkm
---
qty priority = floor_log2(refs) * refs * size / (death - birth). Shorter-lived, more-refs → higher priority. Tie → lower qty number (i.e., earlier-born qty) first.

In w16: val (reg 76) has refs 2 (def+use), life from the load to the addiu. The const 1 (reg 78) has refs 1 (def only, used in the store... refs counts occurrences: def + use = 2?). Both small.

Which qty number is lower? The const pseudo (78) is created later (higher regno) but qty numbers are assigned per block in insn order: reg 76 born at insn 53, reg 78 born at insn 68. So val's qty is lower → val wins the tie → val should get v0 (the first free reg).

But mine gives val v1 and const v0. Hmm, so the const won. That means the const's priority was higher (shorter life). The const's life: born at 68, dies at 70 — length ~2. val's life: born at 53, dies at 73 — length ~20. So the const has a much shorter life → higher priority → gets v0.

In the target, val gets v0 despite the longer life. Because of the pin ($2 forced).

So I need to make val's qty priority higher than the const's, or make the const not need v0.

val's life is long (from the load at 53 to the addiu at 73). Its priority = log2(2)*2*4/(death-birth) = 2*4/20 = 0.4. The const: log2(2)*2*4/2 = 8. So the const wins clearly.

To make val win, val's life must be shorter or its refs more. Since the RTL positions are fixed by the target's insn order... hmm, but the *order* is what we're choosing. If val's use (addiu) came right after the load, val's life would be short and it'd get v0. But the target's addiu is at the end.

Hmm, but local-alloc computes the life over the block: birth = the load's index, death = the last use. In the target (pin), val is $2 hard reg, so local-alloc doesn't matter.

So without the pin, local-alloc gives v0 to the const. To get val into v0 lever-free, I need val to have a higher local-alloc priority: shorter life or more refs.

Idea: **split val's life**: use val twice, e.g., `D_801B7A84 = val + 1;` and something else. More refs → higher prio. But any extra use changes the code.

Hmm — unless the extra use is *free*: e.g., `val` used in the *store* `*p = 0`? no.

Idea: make the const 1's pseudo die earlier or have a longer life... 

Hmm, what if the constant 1 is materialized differently: e.g., `D_801B7988 = val - val + 1`? laundering, no.

What if `D_801B7988 = 1;` is written as `D_801B7988 = D_801B7A84 == val;`? That's a computed compare — changes code.

What about making the *store* `D_801B7988 = 1` use a different mechanism so the constant doesn't need a register: e.g., if the source stores a variable that holds 1. E.g., `s32 one = 1; ... D_801B7988 = one;` — the local `one` would be a constant-folded pseudo; same li.

Hmm. What if the store order changes so the const's life is longer? E.g., if `D_801B7988 = 1;` came *before* the three stores, its li would be born earlier... its life would still be short (li → sw adjacent). Actually if the li is born early and the store later, the life is longer → lower priority → val could win!

But the target's li is at 8410 and the store at 8434 — a long life! In the target, `li v1,1` at 8410 and `sw v1,0(at)` at 8434: the const's life spans many insns. Hmm, but that's the *scheduled* order; local-alloc works on the pre-sched order (RTL order), where the li is born at insn 68 and used at 70 (adjacent).

So in the RTL, the const's life is short regardless.

Therefore lever-free, the const always beats val for v0 in local-alloc. Unless val's qty gets a higher priority...

val: refs=2 (the load's def and the addiu's use), size=4, life = death-birth. What are birth/death? The load at index 53, the use at 73 → ~20 insn indices? local-alloc's birth/death are insn indices (LUID-like). Priority = log2(2)*2*4/20 = 0.4.
const: 2*4/2 = 4 (using life 2).

To beat 4, val needs life ≤ 2 (impossible; its use is far) or refs higher: refs=4 → log2(4)*4*4/20 = 2*4*4/20 = 1.6 — still less than 4. refs=8: 3*8*4/20=4.8 > 4! So val needs ~8 refs — impossible.

So lever-free, val will NOT get v0 in this shape... unless the const's life is longer. If the const's li were born much earlier and its store much later, its priority would drop.

How to make the const's pseudo live longer in the RTL? If `D_801B7988 = 1;` is written such that the li is emitted early (e.g., the value 1 is computed at the top) and the store at the end. E.g.:

```
s32 one = 1;
...
D_801B7988 = one;
```
The `one` pseudo is born at its declaration point (the top of the block) and used at the store. Life = long → low priority → val (life 20) vs one (life ~25): val's priority 0.4 vs one's 0.32 → val wins v0!

But does `s32 one = 1;` emit an insn? `one = 1` would be a `li` at the declaration point — an extra insn (the target has only one li). Hmm, but if `one` is only used once, combine/cse might rematerialize... Actually a constant assignment `one = 1` may be deleted and the constant rematerialized at the use (REG_EQUIV), giving the same li at the store. Then the pseudo's life is still short.

Hmm.

Alternative: make the const 1's store use the *same* register as something else... 

Let me step back: maybe the target's register assignment comes not from local-alloc but from the pin's absence in a different shape. Since the target has val→v0 and const→v1, and local-alloc prefers the const, the target's RTL must have had val with a higher priority or the const with a longer life.

In the target's RTL (with the pin), val is a HARD register $2 — local-alloc doesn't allocate it. Then the const gets v0 (the first free)... but the target has the const in v1! Because v0 is taken by the pinned val. Right.

So lever-free, we need val to be allocated v0 by local-alloc — the const has priority. OR the const to be allocated v1 for another reason.

Hmm, what if the const's *preferred class* or its copy preference makes it v1? For example, if the const 1 is the result of a comparison or a copy from another register... 

What if `D_801B7988 = 1;` is written with the constant loaded from memory? No.

What if we make the const 1 share a register with another value that's already in v1? E.g., if some other value is in v1 and the constant is copied from it... In the target, what's in v1 before? `li v1,1` is the first use of v1 in that block.

Hmm, alternatively: make the *store* of 1 use a pseudo that is *tied* to the store's operand... no.

OK, what about making val's death closer? If the addiu `val + 1` were scheduled right after the load... The addiu's position is determined by sched1. In the target, the addiu is at 8438 (after the D_801B7988 store). In mine, the addiu is at 42 right after the li.

Wait — mine has the addiu BEFORE the sw (D_801B7988). The target has the addiu AFTER. So there's a scheduling difference too.

Let me reconsider: maybe a different source shape (e.g., the do-while placement) can fix both. In w16, the order of the load is right. The remaining: register + addiu position.

What if I wrap the *load* in a do-while too, or wrap `*p = 0; D_801B7988 = 1;`?

Let me try several do-while placements:
- A: do-while around the three stores (w16) → order right, reg wrong.
- B: do-while around the three stores AND around `*p = 0;`
- C: do-while around the whole tail (three stores + *p + D_801B7988)
- D: do-while around the load only
- E: do-while around the load and the three stores

Each do-while is a block split; the order within blocks is fixed. Maybe a split after the load makes the addiu land later.

Hmm, but the do-while(0) splits the EBB in cse1 and also affects sched1's basic blocks? The basic blocks for sched1 come from the CFG; a do-while(0) creates a loop note but after jump_optimize the CFG is flat (no branches), so sched1 sees one block unless there are labels.

Hmm, but w16's order changed — so the do-while DID affect sched1. Interesting: maybe the do-while(0) leaves a CODE_LABEL or a NOTE that splits sched1's block.

Let me try more do-while placements empirically. Also try `if (1) { ... }` — no, constant-folded.

Let me write a batch with do-while variants around different statements.

Also, for the register: what if the const 1's store is placed *inside* a do-while too?

Let me generate:
- w30: do-while around the three stores (same as w16)
- w31: do-while around the three stores + *p = 0
- w32: do-while around *p = 0 + D_801B7988 = 1
- w33: do-while around the three stores, and *p=0 and D_801B7988 in a second do-while
- w34: do-while around the load
- w35: do-while around the load and the three stores
- w36: do-while around everything after the load
- w37: do-while around the three stores, with the load placed after them in source
- w38: do-while around the three stores with `s32 val = ...` init at decl

Let me build a generator with a flexible template. Simpler: write the variants as separate small edits from w16. Let me write a new gen2.py that takes w16 as the base and applies rewrites.
