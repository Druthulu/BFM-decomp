---
ts: 2026-11-07T00:45:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FaowHbDggnORjS1rHvbu
---
Same as w1. So sched1 puts the load after the stores regardless of source order.

Time: 17:44, item 2 started 17:36 → 8 min. OK, I have time.

Let me think about what makes the reverse scheduler place the load before the stores.

In the reverse schedule, we go from the block end backwards. The final order in the target: ..., call, load, li, store,store,store, store(p), sw v1, addiu, sw.

Hmm, let me look at the target's trace (with the asm) more carefully to see the decision points, and compare with mine. The target trace at T-2: ready list 58 61 64 67 72 77 → picks 77. T-3: 72 67 64 61 58 75 → picks 75. T-4: 72 67 64 61 58 → picks 72. T-5: 67 64 61 58 70 → picks 70? ...

The numbers in parens are priorities (hex?). "75 (7f000001)" = priority 0x7f000001 — that's a "queued" marker? Actually `queue_insn` sets `INSN_PRIORITY(insn) = QUEUE_PRIORITY`? Let me check: in sched.c, `#define QUEUE_PRIORITY 0x7f000001`? Something like that. So 7f000001 = the insn is queued (blocked).

OK, so the trace shows which insns are queued and when.

For the target: 75 (addiu) is queued at T-3; 70 queued at T-5...

I think a better approach: understand what *hazard* blocks insn 53 in my version and not in the target's. Since the asm insn 55 in the target is scheduled between, and it has deps on everything...

Honestly, maybe a simpler empirical route: what if I introduce a real dependency that mimics the asm: make the stores' *values* depend on `val` in a way that folds to 0? That's a launder (identity) — banned.

What about making `*p = 0;` come from a variable? no.

Hmm, what about the order of the *source statements* being: the load first, then the stores — but with the load's result used by an insn *before* the stores? The addiu `val+1` is at the end.

Wait — actually, what if the source writes the three stores BEFORE the load in the source but the RTL order... we tried.

Let me look at the *reverse* schedule logic: the block is scheduled from the end. The last insns are the jump and the final store. Since the final store depends on the addiu which depends on the load, the load is pulled in early in the reverse schedule (it must be scheduled before the addiu in the final order). Hmm, but the final order has the load BEFORE the addiu. Yes: load, ..., addiu, sw. Good.

In mine: stores, load, li, sw v1, addiu, sw. So the load is also before the addiu. Both satisfy the dependency.

The difference: the target's load is before the *three stores*; mine after.

Since the reverse scheduler places insns from the end backwards, the three stores (which are independent) get placed... hmm, in reverse, "blocking" means a hazard with respect to the *next* (later) insn.

OK let me try yet another empirical family: change the *statement* that produces the three stores. E.g., use a loop? No.

What if the three stores are written as one statement each but in a different ORDER (e.g., 0x50, 0x4C, 0x48)? Then in the target the order would differ... no, the target's order is 48,4C,50.

What if the three stores are written as a struct/array? E.g., `((s32 *)&D_801B7948)[0] = 0; ...` — that's what they are.

Hmm, what if the three stores are written as `D_801B7948 = D_801B794C = D_801B7950 = 0;` (a chained assignment)? That creates a different RTL (a copy chain) — the values are all constants, so it folds to three independent stores. Might change the order/deps!

Similarly, `*p = 0; D_801B7988 = 1;`.

Another idea: use a struct assignment or a union to make the stores' RTL different.

Another idea: `D_801B7948 = 0, D_801B794C = 0, D_801B7950 = 0;` (comma operator) — same RTL.

Hmm.

What about the LOAD: `val = D_801B7A84;` — in the target's RTL (with the pin), insn 53 is a load into a hard reg. Without the pin, it's a pseudo. The sched1 priority is 1 either way; the hazard is the same. But the ORDER differs between the target and mine. Yet w3 (barrier kept, pin dropped) has the right order! So the barrier alone fixes the order.

So in the target, is the order due to the barrier or the pin? w3 shows: barrier alone → correct order. So the barrier is the order lever. And the pin is the register lever.

So I need:
(a) a real-C replacement for the barrier's effect on the schedule order (load before the stores),
(b) a real-C replacement for the pin (val in v0, the constant 1 in v1).

For (b): the register assignment. In w3 (barrier only), mine gives val→v1, const→v0; target val→v0, const→v1. This is local-alloc's qty ordering. The `li` pseudo (reg 78) and val (reg 76). local-alloc assigns v0 first to whichever has higher priority (refs/length).

local-alloc's qty_compare_1: let me look at it — maybe decl order or scope changes it.

For (a): maybe I can avoid the issue by making the *load* not be blocked: the blocking depends on the hazard between the load and the previously scheduled (in reverse: later) insn. 

Hmm, what if the li (const 1) is *between* the load and the stores in the target — yes: load, li, store... So in the target the li is also hoisted. In mine: load, li, ... but they're together after the stores.

Wait, in mine (w1): stores, then load, li, then sw v1... So the load+li group is after the stores in mine, before in the target.

What if I change the source order so that the li statement (`D_801B7988 = 1;`) comes BEFORE the load? Then maybe the group... no.

Let me try a broad batch of statement-order permutations and RTL-shape variants, and see if any flips the order. Batch for item 2 (second round):
- w21: chained assignment for the three stores
- w22: `D_801B7948 = 0; D_801B794C = 0; D_801B7950 = 0;` written as `D_801B7948 = D_801B794C = D_801B7950 = 0;`
- w23: val load placed between the three stores and *p=0 with the three stores as one chain
- w24: `D_801B7988 = 1;` moved right after the load
- w25: load's statement written as `val = (s32)D_801B7A84;`
- w26: `s32 val;` declared at function scope (outside the case)
- w27: `val` assigned via a temp pointer: `p2 = &D_801B7A84; val = *p2;` — extra insns, skip
- w28: the stores written through a pointer `q = &D_801B7948; q[0]=0; q[1]=0; q[2]=0;` — different addressing (base+offset) but the target uses lui at; sw zero,0(at) — a base pointer would give different code. Skip.
- w29: `*p = 0;` moved before the three stores (target has it after — no)
- w30: swap the order of `p = &D_801B7930;` and the call

Hmm, none of these obviously targets the scheduling.

Let me reconsider: maybe the ordering difference is due to the *number of insns* in the block before sched1 or the presence of the `REG_EQUIV` note. In mine, insn 53 has REG_EQUIV (mem D_801B7A84) and insn 73 has REG_EQUIV too (from the .lreg dump). With the barrier, cse can't propagate the load's value to the addiu.

AH WAIT. Look at the .lreg dump for w1: insn 73 (addiu) has `(expr_list:REG_EQUIV (mem:SI (symbol_ref:SI ("D_801B7A84")))`. That means combine merged `val + 1` into `D_801B7A84 + 1`? No... REG_EQUIV on the addiu says the addiu's result equals the memory. Hmm.

More importantly: maybe with the barrier, the load is not merged/deleted, while without it, cse deletes the load and replaces its use with the memory operand... no, the load is still there in mine.

Hmm, what about `cse`'s effect: in mine, the load insn 53 has REG_EQUIV — meaning cse replaced a later use with... 

Let me compare the .cse2 dumps: does the target's cse2 keep insn 53? Both have it.

OK, let me try the most promising real-C idea for order: **make the load's address chain longer or add a dependence from the stores to the load via the *stack pointer* or something**... no.

NEW IDEA: What if `val` is declared as `u16`/`s16`? No — the value is s32.

NEW IDEA: What if the load is written as `D_801B7A84 + 0`? no.

Hmm, let me look at the problem from the "what did the original source look like" angle. The original (real game) C likely had:

```
s32 *p = &D_801B7930;   /* or a different structure */
...
```
The pin/barrier were added by the decomp author to force a match; the ORIGINAL compiler produced the target from the original C. Since the barrier is a fake, the original C must have had something that produced the same schedule. But the original C is unknown; the decomp author used levers because plain C didn't reproduce it. So this item may genuinely be a wall — the prior attempt found best 2 with 13 tries + 1440 permutations.

Hmm, best 2 in T10 means they got within 2 insns. My best is 6 (ORDER). 

Let me try a couple more families and then consider the wall (needs 30 tries; I have 4 + 11 + a few).

Actually, let me try the do-while trick around the load and around the stores *together* — C0535 says the do-while splits the EBB, which would put the load in its own block → then the order within each block is fixed and the concatenation is source order! That's promising: if the load is in its own EBB before the stores' EBB, sched1 schedules them separately and the order is load-then-stores.

w16/w17 (do-while around the stores) gave 8 COUNT (71 ins) — let me check w16's diff; maybe the order is right but something else broke.

Let me check w16.
