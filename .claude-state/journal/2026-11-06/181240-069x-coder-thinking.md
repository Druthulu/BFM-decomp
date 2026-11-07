---
ts: 2026-11-07T01:12:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3S3YCnW7AKKTJ7gs8Mdx
---
The base changes from r72 (in .sched) to a0 (in .lreg). Between sched1 and lreg: local-alloc and global-alloc. So **local-alloc** (or global-alloc) rewrote the store's base from r72 to a0!

Ah, I see: at sched1 time, insn 46 (`a0 = r72`) precedes insn 43 (the store). The local-alloc pass has a "qty" mechanism: it can tie/merge pseudos... but here it rewrote a use of r72 to the hard reg a0? 

That's `local-alloc`'s behavior? Hmm, more likely it's the **flow** pass? No, flow is before sched.

Wait, between .sched (sched1 dump) and .lreg: after sched1 comes local-alloc, then global-alloc. The lreg dump is after local-alloc (before global). So local-alloc did the rewrite.

Local-alloc does "combine_regs" and also, at the end, it calls... hmm, local-alloc doesn't rewrite uses to hard regs. But it does *tie* pseudos: if a pseudo's live range doesn't cross a call and it's used only in one block, it's allocated locally. r72 crosses a call → not local. But the store's base r72 at insn 43 — r72 is live from insn 4 to insn 46; it crosses call 28. So r72 is global.

Hmm, so how did the base become a0?

OH WAIT. Maybe it's not a rewrite of r72 → a0; maybe insn 43's base was *always* a different pseudo that got $4, and I'm misreading. In .lreg, `(reg:SI 4 a0)` — regno 4 is a hard reg. In .sched it's `(reg/v:SI 72)`. So it IS a rewrite.

Local-alloc's `reg_renumber`? No.

Hmm, gcc 2.7.2's local-alloc has a final step: "for each pseudo that is tied to a hard reg, replace"? There's a function `local_alloc` that, after assigning, calls `reg_renumber` and also does "if a pseudo is assigned a hard reg and it's a copy..." Hmm.

Actually — I recall gcc 2.7.2's local-alloc does **not** rewrite; but `global_alloc`/`retry` doesn't either. However, there IS a pass `regmove`? Not in 2.7.2.

Wait, maybe the .lreg dump is taken AFTER global_alloc, and the pseudo r72 got hard reg 16 — but the dump shows hard regs for *some* pseudos (72 in 16). In the .lreg dump, insn 4 shows `(reg/v:SI 72)` (not 16), so pseudos are shown as pseudos. Yet insn 43 shows `(reg:SI 4 a0)` — a genuine hard reg 4.

So something replaced the *base* of that store with a0. In local-alloc, there's a mechanism: **local-alloc can substitute a hard reg for a pseudo when the pseudo is dead and the hard reg holds the same value** — that's `reg_renumber`? No...

Hmm, gcc 2.7.2 local-alloc.c has a function `update_equiv_regs`? That's in local-alloc? Actually `update_equiv_regs` is in local-alloc.c in later versions; in 2.7.2 it might be in local-alloc.c too! `update_equiv_regs` replaces registers with equivalent constants/regs based on REG_EQUIV/REG_EQUAL notes. Yes! In gcc 2.7.2, `update_equiv_regs` is in local-alloc.c (called at the end of local_alloc). It uses REG_EQUIV notes to replace pseudos with equivalent values — e.g., a pseudo with a REG_EQUIV of another reg.

So the store's base r72 was replaced by a0 because r72 had a REG_EQUIV note of a0? Hmm, insn 46 is `a0 = r72` — that gives r72 the equivalence to a0? No, it's the other direction.

Actually `update_equiv_regs` looks at insns that set a register to another register and creates equivalences... Let me check: it's the pass that "if a register is set only once to a constant/equivalent, replace uses".

The prior note called it "reload_cse". Whatever the name, the mechanism is: after sched1 moved the copy `a0 = r72` before the store, the equivalence pass replaced the store's base r72 with a0.

So the ROOT cause is **sched1 moving insn 46 (the call-arg copy) above the store**. If the copy stayed after the store, the store's base would stay r72 (→ $16) and we'd have a MATCH!

The prior note says exactly that: "sched1 hoists the arg copy `a0 = P(param)` above both stores". So the fix is to prevent sched1 from hoisting the copy, or to make the store's base not equivalent.

How to prevent sched1 from hoisting insn 46 above insn 43? sched1 (the first scheduler) can move insns within a basic block based on dependencies. The copy `a0 = r72` (for the call) and the store `mem[r72+516] = v0` — the store reads r72, the copy reads r72. They're independent (no data dep), so the scheduler may order them either way. It put the copy first (target puts the store first? No—the target's final code has `move $4,$16` then `jal`, and the store in the delay slot AFTER the jal; so in the target the copy is also before the store!).

Wait, in the target: 
```
li $2,0x100000
move $4,$16
jal func_80171990
sw $2,516($16)
```
The copy IS before the store (which is in the delay slot). But the store's base is still $16 because it's a hard reg (update_equiv_regs only replaces pseudos).

So the store-base replacement only happens for a pseudo. In the target, the base is hard $16 → immune.

Therefore lever-free, we need the store's base to be a pseudo that update_equiv_regs does NOT replace with a0. The equivalence arises because the copy `a0 = r72` makes r72 equivalent to a0 (via a REG_EQUIV/REG_EQUAL note? update_equiv_regs uses REG_EQUIV notes on insns that set a reg to a value).

Hmm: `update_equiv_regs` looks for REG_EQUIV notes (constants) and REG_EQUAL notes (expressions). For a copy `a0 = r72`, does it create an equivalence "r72 == a0"? There's a specific case: "If this insn is a simple register copy, record that the source and dest are equivalent." Then a later use of the source can be replaced by the dest if the dest isn't modified in between and the source isn't... 

So to break it: make the store's base a *different pseudo* from the one copied to a0. E.g., the store uses `new_var`, and the call arg is `s0`. If new_var and s0 are different pseudos (not cse-merged), then the copy `a0 = s0` doesn't make new_var equivalent to a0 → the store keeps new_var → allocated $16 → MATCH!

But cse1/cse2 would merge new_var and s0 (both are copies of the same value)... In the current body, `new_var = (char *) s0;` then the store uses new_var. cse folded new_var into r72 (s0's pseudo). So they're the same.

Can we keep them separate? If new_var's value differs in *mode*? Both are SImode pointers. cse's make_regs_eqv merges pseudos with the same mode.

What if the store's base is `s0` and the call arg is a *cast* of new_var? Both merge.

What if the store's base is computed as `(char *)s0 + 0x204` inline (no temp)? Then it's r72 + 516 → base r72. Same.

Hmm. What if the store's base is a *different variable* that holds a value the compiler can't prove equal, but which is numerically equal? That's an identity-spelling launder — explicitly disallowed.

So: is this a WALL? The prior note says sched1-argcopy-hoist, best 1, 25 tries.

BUT: maybe there's a way to keep the copy from being scheduled before the store — e.g., by making the store depend on the call? No.

Or make the store's base not equivalent: the equivalence is created by the copy insn 46 `a0 = r72`. If instead the call argument were a *different* value — e.g., `func_80171990((u8 *)(s0))` where the compiler sets a0 from a different pseudo (say r75 = (u8*)s0) — then r72 (the store base) isn't the source of the copy, so no equivalence with a0.

So: introduce a separate variable for the call argument:
```
  u8 *p = (u8 *)s0;
  ...
  func_80171990(p);
```
Then the call's arg copy is `a0 = p_pseudo`. If p_pseudo is a distinct pseudo from r72, the store base r72 stays. But cse would merge p with s0 (both are the same value). Unless the copy p = (u8*)s0 happens *after* the store... order matters:

```
  s0 = a0;
  call1(a0);
  new_var = (char *) s0;
  v0 = 8;
  *(s32*)((char*)s0 + 0x200) = v0;
  v0 = 0x100000;
  *(s32*)(new_var + 0x204) = v0;
  u8 *p = (u8 *)s0;      // copy AFTER the store
  func_80171990(p);
```
Then at cse time, p = s0's pseudo → cse merges p into r72 anyway (it's a copy; cse's canon_reg replaces p with r72). Then the call arg copy is `a0 = r72` → same equivalence. Hmm.

Unless the copy `a0 = r72` is scheduled after the store and update_equiv_regs doesn't see it before. But sched1 hoists it.

So the key question: can we make sched1 NOT hoist the call-arg copy above the store? sched1's ordering depends on dependencies and priorities. The copy has a dependency on the call (it feeds it). The store and the copy are independent.

What if the store is made dependent on something the copy writes? E.g., the store's value v0 is also the call's arg? No.

What if the store is placed BEFORE the copy in the source AND sched1 keeps it? sched1 might reorder.

Alternatively: make the copy's source not r72. E.g., pass the call arg as a *recomputed* value: `func_80171990((u8 *)((char *)s0))` — the compiler generates a copy from r72 anyway.

What if we pass `(u8 *)new_var` where new_var is a *volatile*? no.

Hmm, what about making the call arg a value with a different mode: e.g., the function takes `u8 *`; passing `(u8 *)s0` is a no-op cast.

What if the call is passed `(u8 *)(v0)`? No, wrong.

OK, what if we swap which variable is the store base vs the call arg, using two distinct live pseudos that are NOT copies of each other:
- store base: `new_var` = (char*)s0 (a copy)
- call arg: `(u8*)s0` (r72)
Both are the same pseudo after cse.

What if the store base is `s0` and the call arg is `new_var`? Same.

Fundamentally cse merges them.

What if we prevent cse from merging by making the copy have a different mode: e.g. `new_var` is a `char *` and `s0` is `void *` — both SImode, cse merges.

Use a *struct pointer*? Same mode.

Hmm, what about making the copy a *different size*: e.g., store through an `s16 *`? The store is a 32-bit store.

So the wall stands unless sched1's hoist can be prevented.

Idea: make the store's base depend on the call's result? No.

Idea: use `do { } while (0);` blocks to split the basic block so sched1 can't move the copy across! The body already has an empty `do { } while (0);` at the top (a block boundary). If we wrap the store in a `do { ... } while (0);` block, sched1 works within EBBs — the block boundary would prevent the copy from moving above the store (or the store from moving). C0535 in the moves catalog: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item".

That's promising! If the store is inside a `do{}while(0)` block, the copy (outside) can't be scheduled into the block.

But wait: the target has the store in the delay slot of the call, so it must be schedulable after the copy... Hmm, in the target, the store IS after the copy (delay slot). So the target's RTL order is: copy, store. The store is in the delay slot.

If we split the block, the store stays before the copy → the final code would differ (the store wouldn't be in the delay slot).

Hmm. The target's final code: `move $4,$16; jal func_80171990; sw $2,516($16)` — the store is in the delay slot. And the base is $16.

So the store must be scheduled after the copy (into the delay slot), yet the base stays $16. That's only possible with a hard-reg base.

Alternatively, if the store is NOT in the delay slot, the code differs (an extra nop or different order) → score > 0.

So the target requires: the store in the delay slot with base $16. Lever-free, once the copy is hoisted, the base becomes a0.

Unless... the substitution by update_equiv_regs requires the copy to be the *only* set of a0? Or it requires the source pseudo to be "dead" at that point? Look at insn 43's REG_DEAD: in .sched, insn 43 has REG_DEAD (reg/v:SI 72) — the store is r72's last use. In .lreg, insn 43's REG_DEAD is (reg/v:SI 74) and r72 dies at insn 46.

So update_equiv_regs replaced r72's use with a0 and moved the death to insn 46.

The equivalence: insn 46 `a0 = r72` gives a0 the value of r72. update_equiv_regs records "a0 is equivalent to r72" and then replaces uses of r72 with a0 when a0 is not modified... The store (after insn 46) uses r72 → replaced by a0.

To prevent: ensure a0 is *modified* between insn 46 and the store — impossible (the store is right after).

Or ensure the copy isn't seen as an equivalence: if the copy is `a0 = r72` where a0 is a hard reg... update_equiv_regs might skip hard-reg destinations? Apparently not.

What if the call argument is not a register copy but a *computed* address? E.g., `func_80171990((u8 *)((char *)s0 + 0))` — the compiler folds +0 → copy.

What if the call argument is `(u8 *)new_var` where new_var = (char*)s0 but computed with a cast that yields a different pseudo? cse merges.

Hmm, what if the call argument involves a *different* pseudo that is not cse-equivalent: e.g., `u8 *p = (u8 *)((char *)s0);` — a copy, merged.

What if the store's base is not a register at all but a *constant-relative* address? no.

What if we reverse: make the CALL argument the store base and the STORE use the other? They're the same.

OK: another angle — the store's base could be r72 and the call arg could be a *different* register that is set from r72 *inside* a place where update_equiv can't propagate: e.g., if the copy `a0 = r72` is in a different basic block from the store. The store is in block 0, the call setup too.

What if the store is inside the first `do { } while (0)` block (a separate EBB) and the call is after? Then the store's block has no a0 = r72 copy → no substitution. But the final code would have the store before the call, not in the delay slot. Target has it in the delay slot. Score > 0.

Hmm, unless the store in the delay slot is a dbr (reorg) decision made after reload: reorg can move the store into the delay slot. And update_equiv_regs runs at local-alloc (before reorg). So if the store is in a different EBB from the copy at local-alloc time, no substitution; then reorg could still fill the delay slot with it (moving it across the block boundary — reorg does move insns into delay slots from the fall-through path).

Wait, but if the store is in a different basic block, reorg's delay-slot filling can only move an insn from the same block (the delay slot must be filled from the instruction after the jump, which is in the same block).

Hmm.

Let me look at the target's block structure: the target's source has `do { } while (0);` right after the declarations — an empty block that splits EBBs at the top only.

OK, so what can we do? The prior agent tried 25 spellings and concluded sched1-argcopy-hoist. Our brief wants ≥30 tries and 20 min for a WALL. Maybe there IS a crack: what if we make the store's base *not* r72 but a pseudo that isn't the copy source, by having the store use a pointer that is computed from r72 by an add that the compiler keeps as a separate register? E.g., `char *r = (char *)s0 + 0x204;` computed BEFORE the call (so it's live across the call, in a callee-saved reg):

```
  s0 = a0;
  r = (char *)s0 + 0x204;   // live across call 1
  call1(a0);
  ...
  *(s32 *)r = v0;
  func_80171990((u8 *)s0);
```
Then the store's base is r (a pseudo), and the call arg copy is a0 = r72. r != r72 (different pseudos, and r is not a copy — it's an add). update_equiv_regs won't equate r with a0. The store stays base r → allocated a callee-saved reg (say $17). The target's store base is $16 (s0). If r gets $16 (because it's the only other global allocno and conflicts?), hmm: r would take a callee-saved reg; s0 (r72) also crosses the call → another callee-saved. The frame/regs would differ: target has only $16 saved; with r live across the call, we'd save 2 regs → different frame. Score worse.

What if r is computed AFTER the call (not live across): `r = (char*)s0 + 0x204;` after call1, before the stores. Then r = r72 + 516 (an add). The store uses r. update_equiv_regs might see r's value as r72+516 and fold the store back to 516(r72)... combine/cse might. If not folded, the store would be `sw $2,0(r)` with an extra `addiu r,$16,516` — extra instruction → mismatch.

So no.

Hmm, what about the *order* of the two stores? The target has store1 (0x200) then store2 (0x204). What if we swap them in the source? Then the first store's base... both use r72. The copy a0 = r72 hoisted above both. Same.

What if we put the second store BEFORE the first? Same.

OK — what about making the call-arg copy come from a pseudo that is *not* r72 by making the call arg `(u8 *)new_var` and the store base `s0`? cse merges new_var and s0.

Let me test whether cse actually merges them: in the current body, new_var = (char*)s0 and the store uses new_var; the .cse dump showed the store base as r72 (merged). Yes.

What if new_var is assigned AFTER the store and used only in the call? Then the call arg copy source might be a different pseudo... but cse would still merge.

Hmm, what if we make the call argument a value that is not provably equal to the store base, but which the target also produces? The target's call arg is s0. So the arg must be s0.

Therefore the copy `a0 = r72` is inevitable, and update_equiv_regs will replace the store's base r72 with a0 whenever the copy precedes the store.

Unless the store's base is a HARD REG. Lever-free impossible.

=> WALL. Tag: sched1-argcopy-hoist (existing tag, defined as "arg-copy hoisted/sunk across the call setup (T10 S01)" — exactly this function).

But wait: the brief says a WALL needs ≥30 tries and ≥20 min. Prior: 25 tries. I need to try ≥30 new moves. Let me generate a broad sweep:

1. Order of the two stores swapped.
2. new_var assigned at different points.
3. Call arg as a separate variable (several spellings).
4. do{}while(0) around the store / around the call.
5. The store before/after the call.
6. v0 as a temp (multiple temps vs one).
7. Address spellings: (char*)s0 + 0x204 vs ((char*)s0)+0x204 vs (s32*)((u8*)s0+0x204).
8. `int v0` vs `s32 v0`.
9. Splitting v0 into two variables (the target reuses $2 for both constants!).
10. `func_80171990((u8 *)new_var)`.
11. Moving `new_var = (char*)s0;` to after the first store.
12. Using `s0` directly for the second store (no new_var).
13. Different cast styles.
14. `void *p = s0;` etc.

Let me write a generator with ~35 variants, score them, and see if any hits 0.

Note: the empty `do { } while (0);` in the orig — keep it in the base (it's in the target's source). Actually, does it matter? Let me test both with and without.

Let me also reconsider: the current best is 1 with the pin removed. Maybe a variant that changes the store base's pseudo could reach 0 if the *scheduler* orders differently.

Actually — here's a thought: what if the second store uses `s0` (not new_var) and the call arg uses `new_var`? Then the call-arg copy is `a0 = new_var`, and if new_var is a distinct pseudo from r72 (not merged), the store's base r72 stays. But cse merges new_var and s0 (copies). Hmm, but does cse merge if new_var is used only once? It still merges (copy propagation).

Unless new_var is assigned from something else: e.g. `new_var = (char *)s0;` where the cast is to `char*` from `void*` — cse's make_regs_eqv requires the same mode; both SImode. Merged.

OK, let me just run the sweep.

Also worth trying: reordering the source so that the second store comes before the first (the target's order is 0x200 then 0x204 — matches the source).

Let me write the generator now. I'll produce ~30 variants.

One more idea: make the call arg `(u8 *)(s0)` be computed via a *union* or a cast through `s32`: `func_80171990((u8 *)(s32)s0)` — same.

Another: make the call arg a `char *` variable assigned *before* the stores (so it's live across the stores): e.g.
```
  u8 *p = (u8 *)s0;    // before the stores
  ...stores...
  func_80171990(p);
```
cse merges p with r72; the copy a0 = p becomes a0 = r72. Same.

Another: pass the call arg as `(u8 *)((char *)s0 + 0x200 - 0x200)` — an identity launder, disallowed.

Let me generate the sweep.
