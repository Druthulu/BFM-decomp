---
ts: 2026-11-06T05:03:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dC6EKT9MgidcNtDRcEn4
---
Interesting! l2 (replacing the HI store with a QI store) gives score 4 MIXED, 47 ins. That's not the target (it changed the sh to sb). But l1 shows the QI store breaks the cse forward (score 7, 51 ins — extra instructions).

So a QI store to the varying address invalidates. We need one that is removed later. Since l1 has 51 vs 47: 4 extra insns (sb + address computation?). Hmm.

Now, how to get a QI store that flow deletes? flow's last_mem_set: if the QI store is followed by another QI store to the same MEM, the first is deleted. So:
```
*(u8 *)(D_80127524 + 0x1A) = 0;
*(u8 *)(D_80127524 + 0x1A) = 0;
*(s16 *)(D_80127524 + 0x1A) = 1;
```
The first QI store is deleted (last_mem_set matches the second QI store). The second QI store survives → extra sb. Unless the second QI store is also deleted by a later equal store... the HI store isn't equal (mode differs).

What if we use TWO QI stores and then the HI store, where the last QI store is... no.

Alternatively, can flow delete a QI store whose MEM equals a *later QI store* that is itself deleted? The last one always survives.

Hmm, unless combine merges the surviving QI store with the HI store into one HI store? Combine works on adjacent insns with dependencies. A QI store and an HI store to overlapping addresses — combine's `try_combine` may not handle memory overlap.

What about making the surviving store land in a *branch delay slot* or elsewhere such that the count matches? Not target.

Alternative: make the QI store's MEM equal to a store that already exists in the target. Is there a QI store in the target? No.

Hmm, what about a QI store to a *dead stack slot* with a varying address that flow deletes? flow deletes only when last_mem_set matches. Two QI stores to the same varying address: first deleted. So we'd need the QI store to be the *first* of two identical stores where the second is... itself dead? No.

Wait, actually, maybe there's another deletion mechanism: `delete_dead_from_cse` deletes register sets only. `jump_optimize` (after cse2) might delete unreachable code. If the QI store is in an unreachable block, it would be deleted! But then cse wouldn't see it either (cse runs before jump_opt... wait, order: cse1, jump_opt, loop, jump_opt, cse2, jump_opt). Hmm, cse1 runs before the first jump_opt. If the dead store is in a block that jump_opt later deletes, cse1 sees it (good), and jump_opt removes it (good). But cse2 runs after and would not see it (fine, already invalidated the store entry? cse2 starts fresh: the forwarding could reappear in cse2!).

Wait, does the forwarding happen in cse1 or cse2? The a1.i.cse dump showed insn 64 already forwarded after cse1. So cse1 did it. If we block cse1 with a dead store, cse2 (running later, after the dead store is deleted by jump_opt?) could re-forward. Order: cse1 → jump_opt(1) → loop → jump_opt(2) → cse2 → jump_opt(3) → flow. So the dead store must survive until after cse2, then be deleted by flow (final) or combine.

flow_analysis (final pass) deletes dead stores with last_mem_set matching. So two identical QI stores: the first is deleted by flow; the second survives. Still one extra.

Unless the second store is deleted by combine because its value is overwritten... no.

Hmm, what if the second QI store's value is *not* needed and it's to a dead local, and flow's last_mem_set mechanism... no, the last store always stays.

OK, alternative: use an insn that cse treats as all=1 but which is not a store to memory at all and disappears: a CLOBBER of a MEM. What C generates a CLOBBER without code? A function call clobbers memory (CALL_INSN → invalidate everything), but calls can't be deleted. 

What about `__builtin_...`? no.

What about a variable-length array or alloca? no.

What about the `return` of a struct? no.

Hmm, what about a *volatile* MEM? The hash function sets do_not_record for volatile MEMs; note_mem_written for a volatile store: `if (GET_CODE(written)==MEM)` ... a volatile store's address may still be fixed. But a volatile store is a lever (not allowed).

Wait — is a volatile access actually a "lever of another kind"? The brief lists lever kinds: pin, launder, barrier, keepalive macro or asm. "no new lever of any kind" — volatile is a classic codegen lever. I should avoid it.

Let me reconsider the problem. Maybe I'm wrong that the reload is impossible. What if we make the stored value a *different pseudo* from the one cse records by using a store through a *union* or a *bitfield*... 

Actually, here's a thought: cse records the store dest as equivalent to the source. The lookup at insn 64 found reg 76. What if the stored value register is *killed* between the store and the load by a register write? cse's invalidate() removes entries whose expression mentions a register that's set. If the register 76 is modified between (e.g., by the sh store? no), the entry is removed. 

What if we reassign v0 between the store and the call? E.g.:
```
v0 = D_80127528;
D_80127528 = 0;
*p = v0;
if (v0 != 0) {
    sh = 1;
    v0 = 0;          // dead? changes the if? no, after the test
    call(*p);
}
```
If v0 is reassigned after the if test, cse invalidates the entry for reg 76 (the stored value). Then the load *p must be a real load! And if `v0 = 0` is dead, delete_dead_from_cse or flow deletes the assignment (a register set to a constant, not used → deleted). 

But careful: the entry for (mem symbol) is equivalent to reg 76; when reg 76 is set again, cse's invalidate removes entries mentioning reg 76 — including the memory entry. Yes! `invalidate(dest)` for a register dest removes table entries whose expression mentions that register.

So: add `v0 = 0;` (or any dead assignment to v0) after the if test and before the call. delete_dead_from_cse deletes register sets to unused regs. v0 is not used after → the set is deleted (if it has no side effects). 

But wait: the assignment `v0 = 0` is after the if test, inside the if block. Source:
```
if (v0 != 0) {
    *(s16 *)(D_80127524 + 0x1A) = 1;
    v0 = 0;
    func_80138C30(*p);
}
```
cse1 processes: the store *p = v0 (in the previous block) created the entry. Then in the if block: sh store; then `v0 = 0` invalidates reg 76 entries (removing the memory entry); then the load *p can't be forwarded → real load. Then delete_dead_from_cse (right after cse1) deletes the `v0 = 0` set because v0 is unused after (counts). 

This is a real C move ("dead reset" — the moves list mentions C0414 "dead-reset cse-breaker; cracked 3 launders in G16x"!). The brief even says MOVES+ C0414 dead-reset cse-breaker. That's exactly this. 

Let me test: `v0 = 0;` before the call. But is it semantically safe? v0 is a local; assigning 0 after the test and never using it is dead. Yes.

Let's test m1.
