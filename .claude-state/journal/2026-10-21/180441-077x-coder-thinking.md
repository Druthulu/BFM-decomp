---
ts: 2026-10-22T00:04:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_gLKup6W0p0rTEZgdpciP
---
Same. OK.

Let me think about the mechanism ONE more time, focused: the `addiu a1,s0,36` must be scheduled BEFORE the `li v0,51`/`sb`.

In the target, the order is: move a0,s1 (36); addiu a1,s0,36 (37); lui a2 (38); addiu a2 (39); li v0,51 (40); jal (41); sb (42).

So the arg setup (37-39) is contiguous and early, and the store's value load (40) is just before the call.

In mine: move a0,s1 (36); li v0,51 (37); sb (38); lui a2 (39); addiu a2 (40); jal (41); addiu a1 (42).

So mine's a1 setup is at the END (the delay slot).

Hmm! What if the a1 arg were set up in a way that's NOT delay-slot eligible? E.g. if the a1 value needed 2 insns. `p = (s32)((u8 *)ent + 0x24)` → `addiu a1,s0,36` (1 insn). If instead the value were computed as a 2-insn sequence (e.g. `ent + 0x20 + 4`), the whole pair would be ineligible for the delay slot, and the first insn would be scheduled early.

Hmm! `(s32)((u8 *)ent + 0x24)` → what if written as `(s32)((u8 *)ent + 0x20) + 4`? That's still one addiu (gcc folds 0x20+4=0x24). Hmm.

What about `(s32)((u8 *)ent + 0x24)` where ent is a `u8 *`? Hmm.

Hmm, the first branch has the same expression and it IS scheduled early (17) and the delay slot holds the `sw`. So the a1 setup CAN be scheduled early. In the if-arm it's early; in the else-arm mine it's late.

DIFFERENCE: in the if-arm, the arg setup (4 insns) is followed by 4 stores. In the else-arm, the arg setup is followed by 1 store.

Hmm, what if the else-arm's block is "too small" and the scheduler's "call setup hoisting" doesn't apply?

Hmm, hmm. What if I add a statement to the else-arm? E.g., what if the else-arm had the store AND something else? That would change the target's code. ✗

Hmm, what about the `hw = 0x1C;` placement: in the target, the `li v0,28` (hw = 0x1C) is at 43 — AFTER the call. In the source, `hw = 0x1C;` is after the call ✓ (both in mine and the target).

Hmm, so in the target's else-arm the order is: [call1 setup], [call2 setup], [store value], [call2], [store], [hw]. And in mine: [call1 setup], [store value], [store], [call2 a2 setup], [call2], [call2 a1 setup].

Hmm, the fundamental difference: mine scheduled the store BEFORE the a2 setup, and the target scheduled the a1 setup before the store.

So in mine, the store was scheduled EARLY (right after the a0 setup) — as if the store were the arm's FIRST statement. In the target, the store is the arm's LAST statement.

Since the source order is (q, p, e, store, call) in both, the LUIDs are the same. So the SCHEDULER made different choices. The scheduler's choice depends on priorities, which depend on the birth/death of values.

In the target, the store's value (v0 = 0x33) is born at the `li` (insn 40) and dies at the `sb` (42) — a very short range, right before the call. In mine, the `li` is at 37 and the `sb` at 38 — also short.

Hmm, the difference: in the target the store comes AFTER the arg setup, in mine BEFORE.

Hmm, what if it's about the a0 dependency? The store's base is a0 (q, $4). The `move a0,s1` (q = sub) is at 36 in both. Hmm.

What if the difference is the ORDER of the p/e assignments vs the q assignment? In the target, the order is a0 (36), a1 (37), a2 (38-39) — so q's assignment is FIRST, then p, then e ✓ (matching the source order q, p, e). In mine: a0 (36) first ✓, then the store, then a2.

So in mine, the p and e assignments were scheduled AFTER the store, even though their LUIDs are before the store's! Hmm, that's a scheduler inversion.

Hmm, hold on, is that right? In mine: 36 move a0,s1 (q = sub), 37 li v0,51, 38 sb, 39 lui a2, 40 addiu a2, 41 jal, 42 addiu a1 (delay).

So p's assignment (addiu a1) went to the delay slot and e's (lui/addiu a2) came after the store.

Hmm, so BOTH p and e were scheduled after the store, though their LUIDs are before. So the scheduler delayed them.

Why would the scheduler delay the p/e assignments? Because their values are needed only at the call, and gcc's scheduler (sched2) tries to minimize the live ranges → delays the setup to just before the call ✓ (that's the classic "call arg setup as late as possible" to avoid holding the arg regs).

And in the target, they were NOT delayed. Hmm! What prevents the delaying?

AH — maybe the LAUNDER! The asm consumes q, p, e (its inputs) → so the values must be in registers BEFORE the asm. And the asm is scheduled EARLY (priority 1) → so the arg setup is early ✓✓✓.

So the launder's effect = a scheduling anchor forcing the arg setup early. Without asm, gcc delays the arg setup.

To reproduce without asm: I need something that forces p and e to be in registers early. Hmm.

What if p and e are USED before the call (in a way that produces no code)? Hmm.

Hmm! What if p and e are used in the STORE? E.g., the store's value... no.

Hmm, what if the store is written to use p? No.

Hmm, what if I write the store as `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` but with q being `p`-related? Hmm.

Hmm, what if p is used to compute the store's address? The store's address is q + 0x27. Hmm, what if the store were `*(u8 *)((u8 *)q + 0x27) = 0x33;`? Same.

Hmm, what if I add a use of p and e that produces no instructions: e.g. `if (p == 0) {}`? gcc folds it (p's value is a known constant-ish?) hmm, p = ent+0x24 is not a constant → the comparison would generate code ✗.

Hmm, what about using p and e in a `sizeof`? no.

Hmm, what if the do-while(0) trick is used to force p and e to be "live" in a way that keeps them in regs? Hmm, the T10 example used `do { r = p + i; } while (0);` to add a REF to p (a loop-weighted ref) — changing the ref count/priority. Hmm! That's the "priority dial".

So: `do { r2 = p + 0; } while (0);` — hmm, that adds an insn (the add).

Hmm. What about `do { r2 = e; } while (0);` — a copy (an extra insn) ✗.

Hmm.

OK, I'm going to record this item as a WALL (best 4) with the mechanism: "the target's arg setup is scheduled EARLY (insns 36-39) and the store in the call's delay slot; without the launder gcc delays the call's arg setup to just before the call (sched2's late-arg-setup) and puts the a1 setup in the delay slot; the launder's asm acts as a scheduling anchor (pri(asm)=1, §373) forcing q/p/e into regs before the store."

Wall tag: "sched2-late-argsetup"? The existing tags: "sched1-argcopy-hoist: sched1/reload_cse: arg-copy hoisted/sunk across the call setup (T10 S01)" — hmm! That's close: "arg-copy hoisted/sunk across the call setup". Hmm, our case: the arg setup is hoisted (early) in the target vs sunk (late) in ours. The existing tag "sched1-argcopy-hoist" says "arg-copy hoisted/sunk across the call setup" ✓ — that fits!

Hmm, but the wall must be a lever-free body's best score. Our best lever-free score = 4. The wall tag: "sched1-argcopy-hoist" (existing) — the mechanism: the arg setup is sunk in ours vs hoisted in the target; the launder's asm is the anchor (pri(asm)=1 per §373).

Hmm, hold on. Before I settle, let me try ONE more thing: what if the arg setup is forced early by using p and e in the STORE? Hmm.

Hmm, actually — what about this: the store `((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;` — what if I write it as `*(u8 *)((u8 *)q + 0x27) = 0x33;`? Same code.

Hmm, what if the store's VALUE is derived from p or e? E.g. `unk27 = 0x33` — the value 0x33 is unrelated.

OK. Hmm, one more idea: what if the arg setup is sunk because gcc thinks a1/a2 are free until the call; but if I make the call take FOUR args (e.g. an extra arg), the setup would be bigger... The target's call has 3 args. Hmm, "a call passed at its REAL arity (the extra arg costs 0 bytes — jump2 deletes the no-op copy, jump.c:425-462) (R19)" — from the C0505 catalog! R19: "a call passed at its REAL arity (the extra arg costs 0 bytes)".

So passing an EXTRA argument to func_80128EA8 (if its real arity is 4?) would... hmm, the call's decl is `func_80128EA8(s32, s32, s32)`? Let me check the declaration. If the real arity is 4 (the callee takes 4 args), then our 3-arg call is wrong and the target's `move a3,zero` in the FIRST call (insn 13/35) suggests the first call func_8001CC3C takes 4 args (a0-a3) with a3 = 0.

Hmm! Look at the target's first call: 33 `move a2,zero`, 34 jal, 35 `move a3,zero` (delay slot). So func_8001CC3C(sub, X, 0, 0) — 4 args ✓ (as in the source).

And the second call func_80128EA8(q, p, e) — 3 args (a0, a1, a2) ✓.

Hmm, so no extra arg.

OK, let me try the R19 dial: hmm, it's about arity.

Let me try one more: what if the source passes the args in a way that requires the setup early: e.g., what if `p` and `e` are ALSO used in the first call? no.

FINAL IDEA for this item: what if the `q = sub;` assignment is moved to AFTER the p/e assignments (so a0's setup is later)? The target has a0 (36) first, so no.

What if the else-arm is restructured to have the store's value come from a variable assigned EARLIER (so the `li` has an early LUID and the store is late)? Hmm, in the target the `li v0,51` is at 40 (late) — so the value's LUID is late too.

Hmm, so in the target BOTH the `li` and the `sb` are late, and the arg setup is early. The LUID order in the target: arg setup (early) < li (40) < sb (42) = the call.

So the source order must be: [arg setup stuff] [the store] [the call]. And the arg setup must be generated by statements BEFORE the store.

The arg setup = the moves to a0/a1/a2. a0 = q ($4, pinned) → the `q = sub` assignment ✓ (a statement). a1 = p → the `p = ...` assignment (a statement) — but only if p is allocated to a1. a2 = e → the `e = ...` assignment (a statement) — only if e is allocated to a2.

So: if p is allocated to a1 and e to a2, the source order (q, p, e, store, call) gives the LUIDs: move a0,s1; addiu a1,s0,36; lui a2; addiu a2; li v0,51; sb; jal — EXACTLY the target's order!!!

So the whole problem is: **make gcc allocate p to a1 and e to a2** (instead of allocating them to temps and copying at the call).

That's local-alloc's "call argument register" allocation. Why didn't it happen in mine? Because... hmm! In gcc, a variable used only as a call argument IS allocated to the arg reg (this is `global.c`'s "hard reg" allocation for call args: the pseudo gets the arg reg if the reg is free at the call and the value isn't live across the call).

In mine, a1 and a2 were free at the call... hmm. But gcc's rule (global.c's `find_reg`): a pseudo that is a call argument can be allocated to the corresponding hard reg ONLY if the pseudo's live range doesn't extend beyond the call and the reg isn't otherwise used. Hmm, and the arg setup copy is emitted by expand as `a1 = p` — hmm, no: expand emits the arg setup by COPYING the value into the arg reg: `(set (reg a1) (reg p))`? Or does it emit the computation directly into a1?

Hmm! In gcc, for `f(x)` where x is a variable, expand emits the arg setup as a copy into the arg reg (a1 = x). Then local-alloc can coalesce the copy (assign x to a1) — but gcc's local-alloc does this coalescing only if beneficial. Hmm, in gcc 2.7.2, `local-alloc.c` has the "coalesce" logic? Hmm, actually gcc 2.7.2's local-alloc doesn't do copy coalescing per se; global.c's `global_alloc` has "hard reg" allocation for call args: `global.c`'s `allocate_hard_register`?

Hmm, there's a known gcc behavior: "a variable used as a call argument is allocated to the argument register" — this is done in global.c's `global_alloc` via the "call argument" preference? Hmm.

Whatever the mechanism, the question is: what makes gcc NOT do it in my else-arm but DO it in the target?

AH WAIT!!! Maybe in the target, p and e were NOT variables at all! What if the target's source was:

```
        func_8001CC3C(sub, (s32)D_801817A4, 0, 0);
        q = sub;
        func_80128EA8(q, (s32)((u8 *)ent + 0x24), (s32)D_801817B0);
        ((Unkstruct_800B5CB8 *)q)->unk27 = 0x33;
```
Then the arg setup (a1 = ent+36, a2 = &D_801817B0) is generated by expand AT THE CALL → its LUID is at the call (after the store's LUID if the store is before the call) ✗.

Hmm, but if the store is AFTER the call (v4), the arg setup's LUID < the store's LUID ✓✓✓ and the store would be scheduled last → into the delay slot ✓✓✓!!!

But v4 gave: mine 37 lui a2; 38 addiu a2; 39 jal; 40 addiu a1 (delay); 41 li v0,51; 42 sb. Hmm, so the store was NOT moved into the delay slot (the a1 setup took it).

Hmm! But in v4, the arg setup was NOT at the top: mine[36] = move a0,s1 (the q assignment), 37 lui a2, 38 addiu a2 — hmm, that IS early-ish. And the a1 setup went to the delay slot.

Argh, the a1 setup keeps going to the delay slot.

Hmm! In the target, the a1 setup is at 37. Hmm, what if the a1 arg's VALUE is what delays it? `addiu a1,s0,36` — hmm, a1 = s0 + 36. s0 = ent (the pinned $16). Hmm, in the if-arm the same expression is at 17 ✓ early.

OK, so in the if-arm, the a1 setup is early. In the else-arm, it's late. The difference must be in the block's structure.

**THE BLOCK STRUCTURE!** The if-arm's block: 4 statements + the call. The else-arm's block: 1 statement + the call. Hmm, and the else-arm ALSO has the first call before it.

Hmm, so the else-arm's block (after the first call) contains: q = sub, p = ..., e = ..., the store, the call. And the if-arm's block: the stores + the call.

Hmm! What if the difference is the number of quantities (the "3-qty sort bug")?! The if-arm's block has: sub, ent, hw, + temps = maybe 4+ quantities. The else-arm's block has: q, p, e, hw, sub, ent...

The 3-qty sort bug: "For a block with ≤3 local register quantities, the unrolled comparison switch ... 3-qty blocks allocate in qty-CREATION order, not density order."

Hmm! The else-arm's block might have exactly 3 quantities (q, p, e!) → the sort bug applies → the allocation order is by CREATION order (q, p, e) rather than density. Hmm, that might actually be what we want (q→a0, p→a1, e→a2)!

Hmm, but mine didn't do it.

OK, I need to stop. Let me record a WALL for this item (best 4) and move on to the remaining 2 items, then do the bookkeeping. Actually, let me check the remaining 2 items first — maybe they're easier (like item 2's dead-reset). If they're easy, I can come back.

Let me look at func_80184828 (src/ov_SC02_005) and func_8017D81C (src/ov_SC02_021).
