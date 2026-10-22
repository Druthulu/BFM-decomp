---
ts: 2026-10-22T09:00:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_mOeehSKe1VSaAlnoPmMn
---
Excellent! Decisive result!

In d1 (the call argument is the constant 0, so NO copy into a0 for the ptr):
- The globals are 73 (q), 76 (val), 83 (switch value), 72 (arg) — 4 globals.
- r73 STILL has "preferences: 4" and STILL gets a0 (73 in 4)!
- And now r74 (the ptr, no longer global) → v0 (74 in 2).

So the a0 preference for r73 is INDEPENDENT of the call-arg copy! It comes from the q pseudo itself — the store's address copy.

So the copy into a0 for r73 is created by local_alloc (the address needs a hard reg) and the reg chosen is a0 (4).

Now, WHY a0? In local_alloc, when a global pseudo is used as a memory address, local_alloc must put it in a hard reg. The reg choice: local-alloc.c's `find_reg`/`allocate_available_regs` for the "hard reg copy" — it picks from the class in regno order (K3: v0, v1, a0...) — but v0 is used in the join block (the return value... hmm, the return value is at the END of the join block; the store is before it) and v1?

Hmm, in d1 the join block: the store's address, the call, the return value (v0). So v0 is used later in the block. Hmm, and v1 is not used in the join block at all.

But local_alloc's "hard reg copy" for an address: I recall in local-alloc.c there's `hard_reg_copy` handling: when an operand must be in a hard reg at a specific insn, local_alloc creates a copy and assigns a reg via `find_reg` with `regs_ever_live` considerations.

Hmm, per the doc: "Reload's version: order_regs_for_reload sorts spill candidates by total pseudo refs" and "hard_reg_use_compare :3822 ... by ascending use count".

So the choice is by ascending USE COUNT of the hard reg in the function:
- v0: used many times (call results ×2, consts 1/2 ×2, the return value ×1, the slt operands...) → high.
- v1: used... in the pre-allocation RTL, v1 is NOT used at all! (the const 36864 and the slt are pseudos). So v1's count = 0.
- a0: in d1, a0 is not used either (the call arg is a constant now)! Hmm, but a0 was still chosen. Hmm!! In d1, the call `func_8012BD14(0)` → the arg is `li a0,0` → a0 IS used (1 use). And v1 = 0 uses. So by ascending use count, v1 should win. But a0 won.

Hmm! So the choice isn't by use count either.

Hmm, what else? Let me think: maybe local_alloc's hard-reg copy for the address uses a reg that is *free in that block* and the "free" test is per-block: in the join block, at the store, the live hard regs are: sp, fp, v0 (the value r76 is a pseudo at this stage; the return value v0 comes later). Hmm, so v0 and v1 are both free at the store.

Hmm, but wait: maybe the choice is made by *reload* (after global alloc)! Hmm, but the preference exists at global_alloc time...

Hmm, hmm. OK, let me think about the *order* of the local_alloc hard-reg copy: local_alloc assigns hard regs to the local qtys. Maybe the address copy is NOT a local qty but rather local_alloc's "hard_reg_copy" mechanism (local-alloc.c has a section: "Now allocate the hard regs for the operands that must be in hard regs at specific insns" — the `hard_reg_copy` array). In local-alloc.c:

```c
  /* Now scan the insns of the function and find all the operands that need
     to be in hard regs... */
```
Hmm, this is the "local_operands" / "hard_reg_copy" mechanism: for each insn, for each operand that must be in a hard reg (like a memory address or a call arg), local_alloc creates a copy into a hard reg, choosing the reg with `find_reg (..., 0, ...)` — which uses the class's reg order and the "regs_ever_live" test.

Hmm, if the choice were by ascending regno (v0, v1, a0), v0 would be first (but v0 is live? the value r76 → hmm, r76 is a global; at local_alloc time it's a pseudo).

Hmm, the "hard reg copy" for the address of the store: local_alloc picks a reg. In local-alloc.c's `find_reg` for hard reg copies:

```c
	  /* Find a reg that is not live at this point ... */
```
and there's this important bit in local-alloc.c:

```c
      /* If this is a hard reg copy, and the reg is not used elsewhere... */
```

Honestly. Let me try the EXPERIMENTAL route instead: can I make the address copy land in v1 by changing the *hard reg usage* in the function? E.g., if v0 were busy at the store, the copy would take v1.

In the join block, v0 is used at the END (the return value). What if the return value came EARLIER in the join block? Hmm, the return value is the last thing.

Hmm! What about the *value* r76 (val): it's stored to memory, so it's not in a hard reg at the store.

What if the value were kept in a hard reg... no.

Hmm, what if the *call* in the join block were before the store? Then the call's v0 (the return value, unused) would... the target has the call after the first store.

Hmm, what if there were an extra use of v0 in the join block before the store? E.g. if the source computed something in v0 first. Hmm, that changes the code.

OK, alternatively: what if the address copy's reg choice is driven by the *hard reg copy's own* requirements: local_alloc might reuse the SAME reg as a previous hard reg copy in the function (e.g. the call-arg copy in the arms used a0 → the address copy reuses a0 to minimize the number of regs). In d1, the call arg is a constant → `li a0,0` — hmm, that's not a "copy" but a0 is still used.

Hmm! So maybe: local_alloc's hard-reg copy picks a reg that is *already used* by another hard-reg copy in the function (to avoid using more regs)? Or it picks the reg with the fewest *live* uses.

Hmm, in d1: a0 is used once (li a0,0), v0 used ~5 times, v1 used 0 times. If the rule were "fewest uses", v1 (0) would win. It didn't.

So maybe the rule is: the hard reg copy for an address prefers a reg that is *already used elsewhere in the function* (to keep the "hard regs used" set small)? In d1, a0 (1 use) vs v1 (0 uses) → a0 wins if the rule is "prefer a used reg". Hmm, that's the "regs_used_so_far" idea from K5 (pass 0: never allocate a register for the FIRST time in pass 0). YES! K5: "global.c:900 find_reg: pass 0 excludes regs not in regs_used_so_far ('never allocate a register for the FIRST time in pass 0', :945-948) and regs someone else prefers; pass 1 opens fresh regs."

So the analogous rule in local_alloc: the hard reg copy prefers a reg that's already in use (v1 is not used anywhere in the RTL at this stage → not eligible in pass 0) → a0 (used by the call args) ✓✓✓.

So: to make the address copy land in v1, v1 must be USED somewhere in the RTL at that stage! I.e., the RTL must have a hard-reg use of v1 before local_alloc.

Hmm! Interesting. In the target (pinned), the const 0x9000 and the slt are in v1 — but those are local pseudos at that stage... Hmm, but in the PINNED version, the q is hard $3 → the const 0x9000 in the arms is loaded into... hmm, the pinned version's RTL: the const 36864 is a pseudo (r78) → local_alloc gives it v1 ✓ (the local scan order: v0 is used by the call result, so v1 is next ✓).

So in the lever-free version, if I could make the *hard reg* v1 used somewhere in the RTL (pre-allocation), then the address copy would prefer v1.

How to get a hard-reg use of v1 in the RTL? Hmm! The switch dispatch: `beq v1,v0` — the switch value is in v1! In the .lreg RTL: `(insn 89 16 91 (set (reg:SI 83) (zero_extend:SI (reg/v:HI 75))))` — hmm, the switch value is a PSEUDO (r83) at that stage, not v1.

Hmm. So which hard regs appear in the pre-allocation RTL? From the .lreg dump: a0 (the call-arg copies), v0 (the call results, the consts 1/2, the return value). And... that's it? So the hard regs used = {2 (v0), 4 (a0), 29 (sp), 30 (fp), 31 (ra)}.

Hmm, so v1 is NOT used → the address copy prefers a0 (used) over v1 (unused) ✓ consistent!

Now: how do I get a hard-reg use of v1 in the RTL? The *call* to a function returning a value uses v0. The call args use a0-a3.

Hmm! What if the call had MORE arguments (using a1, a2, a3)? That doesn't give v1.

What if the function had a *second* call whose result is used? Still v0.

Hmm, what about the *return value* of the function: `(set (reg/i:SI 2 v0) (symbol_ref func_80172710))` — v0.

Hmm. What if the return value were computed as an *address* (lui/addiu)? In the target: `lui v0,0x0; addiu v0,v0,0` — v0.

Hmm, so v1 seems unreachable... unless: the *switch dispatch* could use v1! E.g., if the switch value were compared against a *constant in v1*... hmm, the target's dispatch: `li v0,1; beq v1,v0` — the switch value is in v1 (a local pseudo r83 → v1) and the constant 1 in v0.

Hmm! What if the *constant* in the dispatch were in v1 and the switch value in v0? That would swap... hmm, the target has `lhu v1,2(a0); li v0,1; beq v1,v0` — the switch value in v1, the const 1 in v0.

Hmm, so in the pre-allocation RTL, could the switch dispatch be expressed with hard regs? The switch value is a pseudo.

Hmm, what if the source's switch were on a *hard-reg* value? No.

Hmm, what about a `u16` comparison that requires a hard reg? no.

Hmm, what if the *call* returned a value used in a comparison... v0.

Hmm! What about the *slt*: `(set (reg/v:SI 79) (lt:SI (reg/v:SI 78) (reg:SI 2 v0)))` — the operands are pseudos and v0.

Hmm, what if the *store* of the value used a hard reg? `(set (mem/s:HI (plus:SI (reg/v:SI 73) 2)) (reg/v:HI 76))` — the value is a pseudo (HI mode). Hmm, what if the value were an SImode pseudo? Then the store would need a truncation → the value would be in a hard reg? Hmm! Interesting: if the stored value were SImode (s32), the store to a u16 field requires a truncation → the RTL would have `(set (reg/v:HI X) (reg/v:SI 76))` hmm, still pseudos.

Hmm.

OK, what about this: the *second* call `func_80178BF8()` — its result is unused → no v0 use... hmm, but the first call's result IS used (v0).

Hmm, so the hard regs used pre-allocation: v0, a0. To get v1 used, I need an insn that mentions v1 as a hard reg.

Hmm! IDEA: a *comparison against a constant* where gcc puts the constant in a hard reg? no, pseudos.

IDEA: the `sw s0,16(sp)` / `sw ra,20(sp)` — sp/fp.

IDEA: What if the function had a *second* return value? no.

Hmm, IDEA: what about a `switch` with a *jump table*? no.

Hmm. What about the *parameter copy*: `(insn 4 2 5 (set (reg/v:SI 72) (reg:SI 4 a0))` — a0. And `(set (reg:SI 16 s0) (reg:SI 4 a0))` — hmm, this is the *pseudo* s0 (a hard reg in the RTL? "reg:SI 16 s0" is hard). So s0 is used ✓ (in the hard regs used list: 16).

So the hard regs used: 2, 4, 16, 31 (+29, 30 for sp/fp).

Hmm, to get v1 (3) into the "used" set, I need an RTL insn with v1.

Hmm! What about the *call* to func_8012BD14 — the call's clobbers include v0, v1, a0-a3! Does gcc's RTL mark the clobbers? In the .lreg dump, the call_insn shows `(clobber (reg:SI 31 ra))` only (the other clobbers are implicit). Hmm, so the "hard regs used" computation might count the clobbered regs? The .greg "Hard regs used: 2 3 4 16 31" — includes 3 (v1)!! Hmm, in the lever-free version, "Hard regs used: 2 3 4 16 31" — v1 IS there! But that's the *final* list (after allocation).

Hmm, so at the pre-allocation stage, is v1 in "regs_used_so_far"? The .lreg dump's "Hard regs used" line? Let me check the .lreg dump for a "Hard regs used" line. Hmm, the .lreg dump I read didn't show one (it showed the register table and the blocks).

OK, so the key question: what made local_alloc pick a0 for the address copy? Options: (i) the reg order (v0, v1, a0) with v0 unavailable (live) and v1 unavailable (?), (ii) the "already used" rule.

Why would v1 be unavailable in the join block? Hmm! Because the *local* allocation in blocks 2 and 5 assigned the const/slt pseudos to v1 — and local_alloc's hard reg assignment happens FIRST (local_alloc runs before global_alloc) — and once v1 is assigned to a local qty in blocks 2/5, is v1 "occupied" globally? NO — local_alloc assigns per-qty; the same hard reg can be used by different qtys in different blocks. But local_alloc tracks "reg_occupied" per block.

Hmm, but the hard-reg *copy* for the address in block 9: local_alloc's find_reg would check the availability of v1 in block 9. Since v1 is used by locals in blocks 2/5 (not 9), v1 should be available in block 9.

Hmm, unless the availability check is function-wide: local_alloc's `find_reg` uses `regs_ever_live` — hmm.

OK, let me just do a targeted EXPERIMENT: I want to see whether v1 can ever be chosen for the address copy. Experiment: add a *use* of v1 in the RTL. Hmm, how?

IDEA: what if the *call* to func_8012BD14 took TWO arguments (a0 and a1)? Then a1 would be used — not v1.

IDEA: what if the *comparison* `> 0x9000` were spelled so that gcc uses v1 as a hard reg? Hmm: `(set (reg/v:SI 79) (lt:SI (reg/v:SI 78) (reg:SI 2 v0)))` — the const is a pseudo (r78) and the call result is v0 (hard).

Hmm! What if the comparison were `0x9000 < func_8012BD14(ptr)` → `(lt (reg/v:SI 78) (reg v0))` — hmm, the same.

What if the comparison used the *ptr* instead: `func_8012BD14(ptr) > ptr`? That changes the semantics ✗ (diagnostic only). Hmm, but as a diagnostic it'd tell me whether a v1 use in the RTL redirects the copy.

Actually, a cleaner diagnostic: what if the source had an extra statement that forces a hard reg v1? Hmm.

Hmm, what about this: the *return value* `(set (reg/i:SI 2 v0) (symbol_ref func_80172710))` — v0.

Hmm, what if the function returned a *constant* (e.g. `return 5;`)? Then the return would be `li v0,5` — still v0.

Hmm, v1 is the second return register — only used by functions returning a struct (in MIPS o32, a struct return uses v0/v1!). Hmm! Interesting: if the function returned a struct, the return value would be in v0 AND v1. But the signature is fixed (s32).

Hmm. What if the *callee* returns a struct? The call `func_8012BD14(ptr)` returns s32 (v0).

Hmm.

OK, alternative approach: make the *local* const 0x9000 NOT be in v1 in the arms. Then... hmm, that's the target's requirement (v1).

Hmm, hold on. Let me reconsider: in the target (pinned), the const 0x9000 is in v1 — that comes from local_alloc's scan (K3: regno order v0, v1, a0...): in blocks 2/5, v0 is occupied (the call result) → v1 ✓.

And in the lever-free version, the same ✓.

Now, the address copy in block 9: the scan (v0, v1, a0): is v0 occupied in block 9? The return value (v0) is at the END of block 9 — but for the *address copy* at the store, v0 is not yet live... hmm, but the local_alloc availability check might consider the whole block ("regs live at start/end" — the block's live set). In block 9, the live-at-start regs are 29, 30, 73, 76 (sp, fp, q, val) — no v0. Hmm, but v0 is used later in the block (the return value).

Hmm, hmm, so the scan would pick v0 for the address copy! But it picked a0. Hmm.

Unless the *value* r76 (val) — hmm, it's a pseudo (global).

OK, I need to stop the deep analysis. Let me do a couple of cheap DIAGNOSTIC experiments to find a lever, in parallel with a broader candidate sweep:

DIAGNOSIS IDEA: make v0 unavailable at the store in block 9 → then the address copy might take v1. How? The return value is at the end of the block. Hmm, what if the *value* (val) were in v0? It's a pseudo.

Hmm, what if the store's VALUE were a hard reg? E.g. if the value stored were a *constant* — no, it differs per arm.

Hmm! What if the value stored were an SImode pseudo? The truncation to HI would create a copy into a hard reg (the truncation `(set (reg/v:HI X) (reg/v:SI Y))`) — hmm, still pseudos.

OK, what about the *first* store's value: `(set (mem/s:HI ...) (reg/v:HI 76))` — the value is HI mode.

Hmm, what if the value were SImode (s32)? Then the store would need `(set (mem/s:HI ...) (reg:HI <trunc of val>)`. The truncation would be a pseudo (HI). Hmm, but truncating an SI pseudo to HI might require a hard reg? In MIPS, truncating SI to HI = `move`? no, it's just using the low half → no insn. Hmm.

Honestly, let me try the broad sweep: maybe some variant hits. Let me generate ~15 variants mechanically (different declaration orders, types, spellings) and score them all. Even without understanding, one might hit.

Let me write a generator with many variants:
1. val declared before q / after q / between.
2. q as s32/u32/s16/u16 (s16/u16 would truncate the pointer ✗).
3. val as u16/s16/u8/s32.
4. st as u16/u8.
5. the stores via `*(u16*)(q+2)`.
6. the stores via a struct-typed pointer.
7. `q` assigned via a temp.
8. the call arg inline vs ptr.
9. the value assignment before/after the q load.
10. the switch case order swapped.
11. `if/else` instead of switch.
12. `q` declared inside the switch's scope? no.

Let me generate and score them all, then look at the best.

Actually, time check: ~1h25m elapsed. Let me timebox item 1 to 20 more minutes, then move to items 2 and 3 (which are twins and might be easier or harder).

Let me write the sweep now.
