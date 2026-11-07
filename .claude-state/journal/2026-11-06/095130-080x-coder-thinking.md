---
ts: 2026-11-06T16:51:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dGscS4RcLdkDieb3prx8
---
In the orig (with asm), D_8018E2DC is set in TWO separate places (389 and 587) — not merged. In our x1b, it was merged into one (389 only, with 7 occurrences).

So the asm prevented cse from merging pseudo 86 with the later pseudo 103. Because the asm clobbers m? The asm is `"=r"(m) : "0"(m)` — it takes m as input and output, forcing m to a register and clobbering its value. cse sees the asm as an insn that modifies m (a set of m), so m's constant value is invalidated → later constants are not merged with it.

So the real-C requirement: make the first pseudo not hold a constant across the calls. Since cse merges by constant equivalence, we need each site's constant to be "fresh".

What if we use a *loop* over the three sources? That would compute the address from an induction variable (not a constant). But target has constants.

What if we declare the addresses via a `register`? forbidden.

What if we make the source expressions *not* pure constants by involving a variable that folds to the same address? e.g. `(s32)D_8018E2DC + (k - k)` where k is a loop var → not constant.

Hmm.

Alternative: think about what the original C looked like such that cse produced two separate pseudos. In the orig-with-asm, the merge is prevented by the asm. In the original source (pre-lever), perhaps the calls were in *different basic blocks* separated by a branch, and cse's table was cleared at a branch? cse clears the table at basic block boundaries? No, cse's table persists across blocks within an EBB, and is flushed at labels that are jump targets or at calls? cse flushes at "LABEL" if the block has multiple predecessors? Actually cse's `cse_basic_block` processes one EBB at a time and the table is reset at each EBB boundary (`cse_end_of_basic_block`). So if the calls are in different EBBs, the constants won't merge!

In our source, the calls are all in one straight-line EBB (no branches). In the target, are they? The target's code from 7180 to 72e4 is straight-line (no branches). So one EBB. Hmm.

Unless the original source had the calls separated by something that ends an EBB (a label, a branch). The target has no branches there.

OK, let me look at cse.c to understand exactly why orig keeps them separate: the asm insn sets reg 86 (m) — the asm is `(set (reg 86) (asm_operands ...))` or similar, so qty_const[86] is invalidated. Then at the next site, `(set (reg 103) (symbol_ref))` — cse sees no register with that constant → keeps 103. So two separate pseudos, each live to its uses.

So to reproduce without asm, we need each site's pseudo to not be merged with a previous one. What if we assign to *different variables* with different scopes... no, cse is value-based.

Hmm, wait: what if the constant is loaded through a *pointer variable* that is re-assigned? No.

What if we prevent cse from recording the constant at all by making the value "unsafe"? cse records constants for any register. 

What if the first group's m is used in a way that makes cse's qty invalid: e.g. after the call, m is used again (so it stays live)? No, that keeps it valid.

Hmm. What if the address expressions are passed as `(void *)(s32)D_8018E2DC` where the cast through s32 creates a `const` rtx? Both sites identical.

Let me think about the structure differently: maybe the original source used an *array of structs* or a loop that got unrolled by... GCC 2.7.2 doesn't unroll.

Alternatively, maybe the original used a **macro** expanding to different expressions like `(s32)D_8018E2DC` vs `(s32)(D_8018E2DC + 0)`. Identity — forbidden.

Hmm, what about making the *first* use of each symbol in a different *mode*: e.g. `(void *)(s32)D_8018E2DC` vs `(void *)(u32)D_8018E2DC`. Same mode SI.

OK, let me look at the win.c (no asm) RTL more: the merged pseudo 86 is used for group A and group B. Global alloc then puts it in a callee-saved register, causing the spill differences. But note: target DOES keep the constant 1 in s3 across all calls. So one callee-saved reg for constants is fine; the problem is the 7 symbol addresses.

Wait, actually, maybe the fix isn't to prevent the merge but to make the merged pseudo's uses cheap: if the merged pseudo is a callee-saved register, the calls would use `move a1,sX` (1 insn) instead of lui+addiu (2 insns) — that's FEWER insns, not more! But mine has MORE insns (284 vs 270) because of the extra prologue/epilogue spills (s7, s6, s5, s4...). The register pressure from 7 addresses (each with long live ranges) forced spills.

So target keeps 7 addresses materialized per use (2 insns each, 14 insns) but no spills; mine keeps them in registers (1 insn per use) but spills others.

We need the target's exact allocation. The cleanest path: reproduce the RTL with separate pseudos per site.

Hmm, what if the variables m are declared in *separate blocks* AND assigned in a way that cse's qty is invalidated between? For example, if the block-scoped `m` is assigned from the symbol and then the block ends, cse might still keep the value.

Wait, here's an idea: what if the original passed the address as an argument of type `u8 *` directly (no cast to s32), e.g. `func_8017D8A4(..., D_8018E2DC, D_8018E2DC + 0x30, 0, 1);`? Then the address expression is a pointer; the rtx is the same symbol_ref. cse merges the same.

Let me test what actually happens with a simple direct form and check if cse merges. Actually, I realize the *asm* has "=r"(m) : "0"(m) which sets m. Any C construct that assigns m a *new* value between uses would invalidate. The real C original might have been:

```
u8 *m;
m = D_8018E2DC;  ... call(m, m+0x30);
m = D_8018E2E8;  ... call;
```
cse would still merge the constants since they're different values (E2DC vs E2E8), but the *same* value reused at group B would merge with group A's.

Hmm, unless the original had different *base variables* for group A and B, e.g.:
group A: m = (s32)D_8018E2DC
group B: m2 = (s32)D_8018E2DC
Two different variables with the same constant: cse merges them anyway.

So cse merging is value-based and unavoidable... unless the value is invalidated.

Hmm, let me look at the orig cse2 around line 389 and 587 to understand exactly which insn invalidated reg 86. Line 389: reg 86 = symbol (first site). Then at 587 another reg = symbol. The asm between them sets reg 86? Let me look at the asm insns.
