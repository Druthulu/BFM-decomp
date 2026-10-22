---
ts: 2026-10-21T23:43:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9CzhcczTnoHVsLIN3PEz
---
"loop.c treats a pseudo with n_times_set > 1 as non-invariant, so it declines BOTH the invariant hoist and the address-giv formation, and the address is recomputed exactly where the target recomputes it."

So the mechanism is: a pseudo (a base POINTER variable) with n_times_set > 1 is not treated as an address GIV → the address is recomputed at each use.

In our case: the base pointer is the address of sp10. In C, the address of a local array is a "constant" (symbol_ref), not a pseudo... but if we introduce a pointer VARIABLE `u16 *base = sp10;` and assign it TWICE, then base has n_times_set=2 → not an address GIV → the address gets recomputed at each use → `addiu a1,sp,24` and `addiu a0,sp,24`!

But careful: "assign it AGAIN at the END of the loop body" — the re-assignment needs to be at a point where it invalidates. And in our case, the two uses are in the same straight-line block, separated by a call.

Hmm, in §349 the base pointer was used in a LOOP. Here, we need the base to be re-assigned between the two uses.

But a second assignment of the SAME value is an "identity". Hmm, but if the base is re-assigned to a *different* value... no, the address must be the same.

Hmm, but wait: in §349 the base pointer was re-assigned to the NEXT iteration's value (a genuine change). Here we need the same value.

Hmm. But what if the base pointer's value changes and changes BACK? E.g.:
```
u16 *base = sp10;        // set 1
... call1(base, base+4, 1) ...
base = sp10;             // set 2 — identity
... call2(base + 4) ...
```
Still an identity assignment, but it's a "re-assignment to make n_times_set > 1" — a legitimate structural move per §349? The brief bans "identity-statement launders". Hmm. `base = sp10;` twice is literally an identity statement.

BUT: here's a legitimate variant! What if the base pointer is assigned from a DIFFERENT source that yields the same address:
```
u16 *base = sp10;        // set 1
func_800D20C0(base, base + 4, 1);
base = &sp10[0];         // set 2 (same address, different spelling)
func_800D23D0(base + 4);
```
Hmm, "identity address spellings" — banned.

Hmm hmm. OK, what if the re-assignment is a genuine pointer bump that ends at the same place? Like:
```
u16 *base = sp10 + 2;   // sp+20
...
base -= 2;               // back to sp+18?? no
```

Hmm.

WAIT. Actually, maybe I'm overанализing the ban. Let me re-read the brief's exact words: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." and "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack".

I think the intent: you can't replace an asm launder with a C statement that *pretends* to do the same thing (i.e., an identity that exists only to steer the compiler). The example `w = (w>>16<<16)|x` is a value launder. "identity address spellings" = writing the same address in two ways to fake a launder.

So `base = sp10; ... base = &sp10[0];` — the second assignment's ONLY purpose is to steer the compiler. That's an identity statement. It would likely be rejected.

So I need a genuine restructuring. Hmm.

THINK: is there a genuine program structure where the base pointer is naturally set twice?

What about the loop! The function has a loop (the do-while). Inside the loop, the code uses `param_1` and `p`. Hmm, the base pointer sp10 isn't used in the loop.

Hmm.

What about this: make the ARRAY a local of a smaller scope so it's re-initialized? no.

OK, alternative plan: accept that the *first* call's arg set is the issue, and consider a DIFFERENT decomposition: what if the C has NO pointer variable at all, and the address is computed as part of a larger expression that gcc handles specially?

Honestly, let me now do a quick decisive experiment on the §349 mechanism to see if it even works here, because if it does, I can then look for a non-identity formulation. Experiment:

f1:
```
u16 *base = sp10;
func_800D20C0(base, base + 4, 1);
base = sp10;         // second set
func_800D23D0(base + 4);
```
Hmm, but that's the identity. As a DIAGNOSTIC it's fine (scratch checks need not be kept).

f2 (genuine, non-identity): assign base twice with DIFFERENT values but the address used is the same? Not possible.

f3: What if we use a base pointer that is set to sp10, then bumped, and the address is computed from the bumped one:
```
u16 *base = sp10;
func_800D20C0(base, base + 4, 1);
base += 4;               // genuine bump, 2nd set
func_800D23D0(base);
```
Here: base+4 (call1) = (plus (reg base)(const 8)); base after bump = (plus (reg base)(const 8)) — hmm, the bump's result. If gcc folds the bump into base's value: base's new value = (plus (reg base)(const 8)). And call1's base+4 = (plus (reg base)(const 8)) — SAME rtx → cse unifies them?! But base has 2 sets → hmm.

Hmm, actually here's the thing: with 2 sets, the value at the second use is a DIFFERENT pseudo (base's second set), so the rtx is (plus (reg base_new)(const 8)) vs (plus (reg base_old)(const 8))? No — after the bump, gcc's RTL for `base += 4` is `base_new = base_old + 4` i.e. (plus (reg base)(const 8)) where base is the same pseudo (reg numbers are the same for a variable). Ugh, in RTL a variable is ONE pseudo with multiple sets. So base's value at the second use = (plus (reg base)(const 8)) and base_old+4 in call1 = (plus (reg base)(const 8)) — IDENTICAL rtx → cse unifies → but base's pseudo now has 2 sets, and cse's equivalence chain for the EXPRESSION is separate.

The question is whether cse's unification happens. cse's `record_cse` for the expression (plus (reg base)(const 8)) at the two occurrences: the first occurrence creates a pseudo; the second occurrence is the same expression → cse replaces it with the pseudo. So still one pseudo → live across the call → s0. But wait: is the expression live across the call? The first occurrence is at call1, the second at call2 (after the call at 12). So yes, live across → callee-saved.

Unless cse's reg_tick invalidation (from base's second set) breaks the chain! The second set of base happens BETWEEN the two occurrences → update_stmt(base) bumps reg_tick → invalidates the equivalence chain → the second occurrence is NOT unified with the first → the expression is computed twice → 2 addiu's!

But d1 (p1 = &sp10[4] second set) didn't work... In d1, the expression (plus (symbol_ref sp10)(const 8)) — the second set of p1 doesn't invalidate the chain for the EXPRESSION? update_stmt(p1) bumps reg_tick → invalidate() → cse's reg_equiv chains are invalidated... Hmm, but cse's `invalidate()` is only called for pseudos whose values change; the chain for the expression pseudo is separate.

Hmm, cse's mechanism: cse records equivs in a table with reg_tick as the validity stamp. `update_stmt` calls `update_stmt` → for each pseudo set, it calls `cse->xhmain`... actually `update_stmt` in cse.c bumps `reg_tick`? No: `update_stmt` is in cse.c? It's in `cse.c`:
```
void update_stmt (rtx exp)
{
  ...
  /* If we are in a basic block, ... */
  ...
  cse->new_indirect = ...
}
```
Hmm, in cse.c, `update_stmt` handles the case where a pseudo is set multiple times: it calls `invalidate (reg, ...)` for the pseudo's reg_equiv. And `invalidate` in cse.c:
```
static void invalidate (rtx reg, int reg_tick)
{
  ...
  if (REG_P (reg) && REGNO (reg) != 0 && ! REGNO_IS_ABI_CALL (regno))
    {
      cse_hash_entry *entry;
      ...
      /* If we have some recorded information about this register, clear it.  */
      if (cse->table->other_uses == 0) ...
      entry = (cse_hash_entry *) hash_delete (cse->table, reg, ..., 0);
      ...
    }
}
```
So invalidate deletes the hash entry for the pseudo → the equivalence chain through it is broken. And `update_stmt` in cse.c:
```
void
update_stmt (rtx exp)
{
  int i;
  rtx reg;

  cse_invalidate_jump_tables ();

  /* If we are in a basic block, ... */
  if (cse->in_memory_x == 0)
    ...

  /* If CSE is not in a basic block, ... */
  ...
  /* Clear the register holding the ... */
  for (i = 0; i < (int) FIRST_PSEUDO_REGISTER; i++)
    ...
}
```
Hmm, I don't remember exactly.

Empirically: d1 didn't work. So the second set of p1 didn't break the chain.

What DOES break the chain: the asm (because the asm's output is a hard reg; the value of p1 is then a hard reg, and cse can't substitute it).

OK OK. Let me think about what else makes a value opaque to cse in C:
1. A memory load.
2. A function call result.
3. volatile.
4. An asm.

Hmm... #2! What if the address came from a function call? No, the target has no call.

Hmm, what about a load from a *constant global*? Like `*(u16 **)&D_801xxxx`? That would be a lw from a global — the target has no such load.

Hmm, so we're stuck: the target has `addiu a1,sp,24` and `addiu a0,sp,24` — two independent rematerializations of a frame address. gcc can only do that if the value is not CSE'd.

Hmm! Actually wait. What if gcc DOES do this if the address is used only ONCE as a *pointer* and once... hmm.

Hold on, hold on. What about this: in the target, maybe the two uses are NOT the same address conceptually:
- a1 = sp+24 for call1
- a0 = sp+24 for call2
Both sp+24. Yeah same.

Hmm, but what if the original source had a pointer variable `p` that was passed to call1, and call2 got `p` too, and the ORIGINAL COMPILER (not gcc) just recomputed? Then the game's original code is:
```
u16 *p = sp10 + 4;
func_800D20C0(sp10, p, 1);
func_800D23D0(p);
```
And the original compiler kept `p` in a register (say $s0) — no wait, the target has NO register for it.

The target: `addiu a1,sp,24` at insn 4 and `addiu a0,sp,24` at insn 15. Both computed fresh. So the original compiler did NOT keep it in a register. Which means the original source probably was:
```
func_800D20C0(sp10, sp10 + 4, 1);
func_800D23D0(sp10 + 4);
```
and the original compiler was a simple one that didn't CSE (or that rematerialized constants).

So the question: can gcc be made to rematerialize?

**KEY INSIGHT ATTEMPT #2**: gcc's cse creates a pseudo for a common subexpression only if the expression is "profitable". In cse.c's `record_cse`:
```
	      /* If we are recording a common subexpression, then we must
	         be sure that the value is not going to be changed... */
	      ...
	      if (!cse->const_cse ...
```
Hmm.

Actually there IS a relevant rule in cse.c! In `record_cse`:
```
	  /* If we are in a jump table, ... */
	  ...
	      /* Don't create a pseudo for an expression that is a "simple" 
	         register operation if the expression is used only once? */
```
Hmm.

Actually, I recall cse.c's rule:
```
	  if (n == 0)   /* not seen before */
	    {
	      ...
	      /* If this is a reg, we may not want to record it... */
```
And crucially, in cse.c there's:
```
	  /* If this is a constant, ... */
```
and
```
	  /* Don't create a pseudo for a plus of a reg and a constant if the reg is
	     ... */
```
Hmm, I genuinely recall something like: cse does NOT record an expression that is "reg + const" if the register is a "cheap" one... Not sure.

Let me look at the ACTUAL gcc source available? The project has a toolchain. Maybe the gcc source isn't available. But `tools/` might have gcc pass references (e.g. `tools/localalloc_sim.py`).

Let me try to find gcc source or the pass behavior docs in the repo. Hmm.

PRAGMATIC PATH: Let me test a handful of formulations quickly, including some unusual ones, and see if ANY gives 0:

t1: `u16 *base = sp10;` then call1(base, base+4, 1); then `base = sp10;` (2nd set); call2(base+4).
t2: `u16 *base = sp10;` call1(base, base + 4, 1); `base += 4;` call2(base);
t3: `u16 *base = sp10 + 4;` call1(sp10, base, 1); `base = base;`? no.
t4: use `volatile`? no.
t5: `u16 *base = sp10;` call1(sp10, base + 4, 1); call2(base + 4); (single set, base in a reg) → probably gives `addiu a1,s0,8` etc. Let's see the score.

Let me also test:
t6: what if we make the address expression used via a *cast to a different type* to change the rtx: e.g. call1's arg `(u32 *)((u8 *)sp10 + 8)` — the cast to u32* is a no-op; rtx same.

t7: What if the two uses are separated by a *volatile store*? C0386: "A VOLATILE STORE EVICTS the MEM from cse". A volatile store to memory invalidates cse's memory chains but not register chains. Hmm, but the address expression is a register chain. Hmm, but a volatile store also causes `update_stmt`/invalidate on... hmm. Actually! A volatile store in the middle would force gcc to spill/reload? no.

But hmm: cse's `invalidate` is called on MEMs for volatile stores, and also `reg_tick`? Let me test t7: add a dummy volatile store between the two calls. But the target has no store between the calls (insn 12 jal, 13 sh zero,16(sp) in the delay slot). Hmm, the `sh zero,16(sp)` IS a store between... it's the delay slot of the jal. Hmm, and the delay slot is BEFORE the call executes. So a volatile store would need to be somewhere that doesn't change the instruction stream. There's no free slot. ✗.

t8: What about the `sh zero,16(sp)` store? In the target, the three zero-stores (sp10[2], sp10[1], sp10[0]) happen at insns 10, 11, and 13 (delay slot). Interesting: the store to sp10[0] is in the delay slot of the first jal.

Hmm! Now here's a thought: what if the zero-stores to the array are what make gcc treat the address specially? In the target, `sh zero,16(sp)` is in the delay slot of `jal func_800D20C0` — so it's scheduled into the delay slot, i.e. it was moved across the call setup. gcc's scheduling did that.

OK let me just run the experiments. Let me write t1, t2, t5 and score.

Actually, let me first reconsider ONE more idea which I think is the most promising:

**IDEA: put the second call BEFORE the first?** No.

**IDEA: What if the second call's argument is `sp10 + 4` and the FIRST call's second argument is ALSO `sp10 + 4`, but we make the ARRAY a `volatile`-qualified... no.

**IDEA (promising!): Use a pointer variable that is set ONCE but whose value is a *non-constant* address: e.g. `u16 *base = (u16 *)((u8 *)sp10 + 0);` no.

**IDEA (promising!): Change the ORDER of the calls' argument evaluation so that the shared expression is in a position where gcc's CSE... no.

**IDEA (VERY promising): What if the second call's argument is a pointer variable that is ASSIGNED FROM THE FIRST CALL'S ARGUMENT in a way that creates a copy through a DIFFERENT type, causing gcc to emit the addiu at the assignment point rather than reusing? e.g.
```
u16 *p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
p1 = (u16 *)((u8 *)p1 + 0);   // no
```

Hmm.

**IDEA: what about `p1` being passed BY VALUE to a function and returned? no.

**IDEA: What if we make the SECOND call take the address of a DIFFERENT local that has the same address because of a union, where the union member is a struct field vs an array element?** As established, both give (plus (symbol_ref u)(const 8)). BUT WAIT — is that true for a union member? For a union, the member's offset is 0, so &u.b[4] = (plus (symbol_ref u)(const 8)). And if `u` is a struct containing a union at offset 0 and a scalar at offset 8:
```
struct S { union { u16 a[6]; } u; u16 w; } s;
```
&s.w = (plus (symbol_ref s)(const 8)) and &s.u.a[4] = (plus (symbol_ref s)(const 8)). Same. ✗

The base symbol_ref is the same object. Only way to differ: a different DECL.

Hmm, so what if the two uses have different base DECLs because one is a *global* and one is a *local*, but the addresses coincide? The stack address can't coincide with a global.

WAIT!!! What about the base DECL being different but the *offset* different such that the SUM is the same? E.g. base1 = sp10 (offset 16) + 8 = 24; base2 = something at offset 20 + 4 = 24. If base2 is a different object at sp+20, then base2+4 = sp+24!

YES!!! That's it! Two DIFFERENT base objects whose addresses differ by a different amount, so that base1+K1 = base2+K2 = sp+24. The rtx would be (plus (symbol_ref base1)(const 8)) vs (plus (symbol_ref base2)(const 4)) → DIFFERENT rtx → cse doesn't unify!

But we need base1 and base2 to be objects in the same stack frame with a known layout: base1 = sp10 at sp+16, base2 = a scalar at sp+20. But then the layout must be exactly: sp10 at sp+16 (6 u16 = 12 bytes → sp+16..sp+27) and a scalar at sp+20 — that OVERLAPS sp10[2]! The target writes sh zero at sp+16,18,20 (sp10[0..2]) and reads sp+26. So the scalar at sp+20 would alias sp10[2] — which is fine semantically? It would be a different object overlapping → undefined behavior in C, and gcc would allocate separate stack slots. ✗ gcc won't overlap two locals.

Hmm. So base1 and base2 must be separate objects; their addresses differ by ≥ their sizes. So base1+K1 = base2+K2 requires overlapping ranges. ✗

Unless base1 is an ARRAY and base2 is a POINTER to somewhere... e.g. base2 = a pointer variable pointing to sp+20? Then base2+4 = sp+24 requires base2 to hold sp+20 — a register.

Hmm! What about: base1 = the array sp10 (at sp+16), base2 = a *pointer variable* p2 whose value is sp+20? Then p2+4 = sp+24. But p2 must be loaded/known.

OK: p2 = sp10 + 2 (sp+20) — a pointer variable. Then:
- call1's a1 = sp10 + 4 → (plus (symbol_ref sp10)(const 8))
- call2's a0 = p2 + 4 → (plus (reg p2)(const 4)) where p2 = (plus (symbol_ref sp10)(const 4))
Different rtx → not unified! But p2 needs a register (live across the call) → s0 → the address sp+20 in s0 → `addiu a0,s0,4`. ✗ (wrong insn)

Unless p2 is rematerialized: p2's value = (plus (symbol_ref sp10)(const 4)) → gcc can rematerialize it as `addiu p2,sp,20`? That would be an extra insn. Hmm.

Argh. gcc's local-alloc decides.

OK. Let me now consider: maybe the answer is to make the SECOND use's expression differ by a *constant* in a way that reload folds to the same address but cse doesn't unify — the offset trick requires different base objects.

FINE. Let me now consider the possibility that this item is a WALL, and the wall tag would be something like "cse-const-addr" (from walls.txt: "cse folds or substitutes a constant/absolute address the target keeps base-relative"). Hmm, that tag is about absolute/global addresses. Here it's a frame address. A new tag could be "cse-frame-addr-share" or similar.

Before giving up, let me run the experiments t1/t2/t5 — cheap, and if one works I'll refine it into a non-identity form.

Let me write t1 and t2 and score them.

t1:
```
u16 *base = sp10;
sp10[2] = 0; sp10[1] = 0; sp10[0] = 0;
func_800D20C0(base, base + 4, 1);
base = sp10;
func_800D23D0(base + 4);
```
Hmm, but the order of the zero-stores matters for the target (they're at insns 10,11,13). The source has them before the calls. Keep the same order.

t2:
```
u16 *base = sp10;
... stores ...
func_800D20C0(base, base + 4, 1);
base += 4;
func_800D23D0(base);
```
Hmm, in t2, `base += 4` then `base` → the address. gcc: base's 2nd set = (plus (reg base)(const 8)). And call1's base+4 = (plus (reg base)(const 8)) — same rtx! So they'd be unified (the same expression). Hmm, unless the reg_tick bump breaks it.

Let me test both.

Actually, let me think about t3 which might be better:
t3: make the two expressions differ at RTL by using a cast that produces a MEM offset:
```
func_800D20C0(sp10, (u16 *)((u8 *)sp10 + 8), 1);
func_800D23D0(sp10 + 4);
```
The first: (u8*)sp10 is a no-op cast → (plus (symbol_ref sp10)(const 8)). Same. ✗

t4: use `&sp10[4]` for call1 and `sp10 + 4` for call2:
&sp10[4] → (plus (symbol_ref sp10)(const 8)). Same. ✗

OK, t1 and t2 it is. Let me write them.

Actually, WAIT. One more important idea!!!

**What if the second call's argument is not a pointer to the array but the array's address computed via the ARRAY ITSELF (decay), and the first call's argument is a pointer VARIABLE that was assigned the array?** I.e.:

```
u16 *p1 = sp10;      // p1 = array address
func_800D20C0(p1, p1 + 4, 1);
func_800D23D0(sp10 + 4);
```
- a0 = p1 → (reg p1) → p1 in a register → `move a0,s0`? ✗ (target: addiu a0,sp,16)

Hmm, but if p1 is rematerialized... p1's value = (symbol_ref sp10) → a "constant" frame address → gcc might keep p1 as a rematerializable pseudo → `addiu a0,sp,16` ✓!! And p1+4 = (plus (reg p1)(const 8)) → hmm, if p1 is rematerialized to (plus (reg sp)(const 16)) then p1+4 folds to (plus (reg sp)(const 24)) → `addiu a1,sp,24` ✓!!! And the second use `sp10 + 4` = (plus (symbol_ref sp10)(const 8)) — hmm, is that the same rtx as p1+4's folded form? p1+4 after folding = (plus (reg sp)(const 24))?? No — at cse time (before reload), the frame address is still a symbol_ref. p1's reg_equiv = (symbol_ref sp10) and p1+4 = (plus (reg p1)(const 8)). simplify_rtx with lookup_reg(p1) = (symbol_ref sp10) → (plus (symbol_ref sp10)(const 8)) — IF simplify_rtx does that lookup. Then it'd be identical to the other → unified. ✗ (or maybe simplify_rtx does NOT do the lookup, in which case they stay different → 2 separate computations → but then p1 must be in a reg → `addiu a1,p1reg,8` ✗).

Hmm, but actually if p1 is rematerializable (its reg_equiv is a symbol_ref — is a symbol_ref "rematerializable"? In gcc, `reload_remat` checks if the reg_equiv is a constant or a simple expression that can be recomputed cheaply — `reg_rematerializable_p`? For a symbol_ref (frame address), gcc can rematerialize it as (reg frame_pointer) + offset — actually gcc handles frame addresses via the "frame pointer" and the address is (plus (reg sp)(const N)) after reload; before reload it's a symbol_ref with a frame offset, and reload turns it into (reg sp)+const. So a pseudo holding a symbol_ref IS rematerializable by reload (it's the standard "address" handling: reload's `reload` of a symbol_ref → (reg sp) + offset? Hmm, actually reload handles `SYMBOL_REF` with a frame offset by generating (plus (reg sp) (const offset))).

So p1 = sp10: p1 is a pseudo with reg_equiv = (symbol_ref sp10) → reload can rematerialize it as (plus (reg sp)(const 16)) → `addiu a0,sp,16` ✓ (if p1 is used once, it'd be rematerialized; if used twice, gcc might keep it in a reg).

And p1 + 4: the rtx is (plus (reg p1)(const 8)). If reload rematerializes p1 as (plus (reg sp)(const 16)), then (plus (plus (reg sp)(const 16))(const 8)) → simplify → (plus (reg sp)(const 24)) → `addiu a1,sp,24` ✓!!!

That's promising! The question is whether cse unifies p1+4 with sp10+4. cse compares rtx: (plus (reg p1)(const 8)) vs (plus (symbol_ref sp10)(const 8)) → DIFFERENT → not unified!

Then the second use sp10+4 → reload → (plus (reg sp)(const 24)) → `addiu a0,sp,24` ✓!!!

And p1 itself: used once (a0 for call1) → rematerialized → `addiu a0,sp,16` ✓!

But p1+4's use: is the (plus (reg p1)(const 8)) pseudo rematerialized? It depends on p1 being rematerializable. p1 = sp10 is a local variable assigned the address of a local array. gcc's local-alloc: p1's reg_equiv = (symbol_ref sp10). Is a symbol_ref a valid reg_equiv? Yes (frame addresses are reg_equivs). And reload can rematerialize it.

Hmm, but gcc might instead keep p1 in a register (as a normal variable) and then p1+4 = (plus (reg p1)(const 8)) with p1 in s0 → `addiu a1,s0,8` ✗.

Hmm, but if p1 is used only ONCE, local-alloc will likely not allocate a register for it (dead after the call) — it'd be rematerialized.

Hmm, but p1+4 uses p1 too. So p1 has 2 uses.

Hmm. But this is worth testing! Let me call it t5:
```
u16 *p1 = sp10;
...stores...
func_800D20C0(p1, p1 + 4, 1);
func_800D23D0(sp10 + 4);
```

Hmm, wait: but in the original, the first call's args were (p0, p1) where p0 = sp10 and p1 = sp10+4. And the launders were on both. Since the target's a0 = sp+16, using p1 = sp10 for a0 is fine.

Let me test t5 and t1.

Let me write both.
