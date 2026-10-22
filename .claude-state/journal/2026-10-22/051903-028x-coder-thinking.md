---
ts: 2026-10-22T11:19:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4slhY2umBNcJvv6txd7M
---
"A pointer local assigned exactly once receives gcc-2.7.2's maximum scheduling priority, and because sched2 works BACKWARD that pushes it LATE".

Hmm, that's about sched2. Our issue might be sched1.

Let me look at C0391 too, and also search the cookbook for something about "call group" or "arg setup" or "sched1 birth".

Actually, more useful: let's look for the "sched1 launch priority" / "birthing_insn_p" definition. `birthing_insn_p` in GCC's sched1.c:

```c
/* Return true if INSN is a "birthing" instruction: one that can be
   issued at any time.  */
static int
birthing_insn_p (insn)
{
  ...
  /* An insn is birthing if it has no unscheduled predecessors AND
     all its operands are available. */
}
```

Actually in GCC 2.7 sched1.c:
```c
/* Return 1 if INSN is a "birthing" instruction -- one which is ready
   to execute at any time.  ... */

static int
birthing_insn_p (insn)
{
  rtx reg;

  /* Note: insns that have no dependencies are birthing. */
  ...
}
```

And `launch_priority`:
```c
/* Return the launch priority of INSN -- the number of insns that
   must be scheduled before INSN ... */
```

Hmm, GCC 2.7 sched1.c has:
```c
/* Return the launch priority of INSN -- the number of insns that
   must be scheduled before INSN can be executed.
   ...
   We increase the priority of birthing instructions ...  */

static int
launch_priority (insn)
{
  int priority = 0;
  ...
  /* If this is a call, then we must schedule ... */
}
```

Hmm, I recall from GCC source (sched1.c in 2.7):

```c
/* Return the launch priority of INSN -- the number of insns that
   must be scheduled before INSN can be executed.

   We add the priority of the dependencies of INSN to the priority
   of INSN itself...

   INSN is a birthing instruction if it has no dependencies...  */

static int
launch_priority (insn)
{
  int priority = 0;

  if (insn->dependences)
    for (dep = insn->dependences; dep; dep = dep->next)
      priority += dep->insn->priority + 1;

  /* ??? */
  if (insn->priority > priority)
    priority = insn->priority;
  ...
}
```

Not sure. Let's approach it empirically instead: the KEY question is how to give the load a "second set" without emitting extra instructions.

Idea: **Make the load's pseudo have 2 sets in a way that combine merges into one instruction.** For example:

```c
s32 t;
t = load;      /* set 1: 167 = mem */
t = load;      /* set 2: 167 = mem (CSE'd away) */
```
CSE would remove the second load → 1 set. Unless there's something in between that makes them non-redundant... but then it's a different address/value.

Idea: 
```c
s32 t;
t = load;
t = t;   /* set 2: 167 = 167 */
```
combine would remove `167 = 167`? combine does remove self-moves ("set x,x" → nothing). Hmm, but maybe not at the sched1 stage? combine runs before sched1 (combine is in pass_all_optimizations? no, combine is in the "final" phase: `pass_all_optimization` includes `pass_combiner`?).

In GCC 2.7 the pass order is roughly:
- pass_all_early_optimizations: expand, sra, cse1, cse2, jump1, cse3, jump2(?), ...
- pass_all_optimizations: local opt (expand, ...), global opt (sched1, ...), flow, ...
- pass_all_late_optimizations: cse4, jump3, dbr, ...

Where does `combine` run? In GCC 2.7, `pass_all_optimizations` contains `pass_combiner`? Hmm — in GCC 2.7, the flow is:
```
  /* Local transformations.  */
  NEXT_PASS (pass_all_optimizations);
```
and `pass_all_optimizations` = `pass_expand, pass_sched, ...`? 

I recall GCC 2.7's `pass_all_optimizations`:
```c
  /* Major loop optimizations.  */
  NEXT_PASS (pass_loop);
  /* Misc passes.  */
  NEXT_PASS (pass_stub);
  NEXT_PASS (pass_extract);
  ...
  /* Gate the register allocator.  */
  NEXT_PASS (pass_ra);
```
and `pass_all_early_optimizations`:
```c
  NEXT_PASS (pass_fixup_cfg);
  NEXT_PASS (pass_local_function);
  NEXT_PASS (pass_reorder_blocks);
  NEXT_PASS (pass_expand);
  NEXT_PASS (pass_sra);
  NEXT_PASS (pass_cse);
  NEXT_PASS (pass_ce1);
  NEXT_PASS (pass_ce2);
  NEXT_PASS (pass_ce3);
  NEXT_PASS (pass_cse3);
  NEXT_PASS (pass_jump);
  NEXT_PASS (pass_subst);
  NEXT_PASS (pass_ce3);
  ...
```
Hmm, no.

OK, empirically the dump file names tell us the order of the passes that dumped: rtl, loop, cse, jump, cse2, jump2, sched, sched2, lreg, greg, dbr. Plus "combine" and "flow". So `combine` runs somewhere. Let me check by looking at the dump listing order... it's alphabetical. Hmm.

Let me look at the dump file timestamps or sizes to infer order. Actually, cc1's `-d<pass>` dumps happen as the pass runs, and the files are created in order. `ls -la --time-style=full-iso` would show creation times! Let's check.

Actually, an easier approach: the file names have a numeric order in the cc1 command line: `-dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd`. The output files: cand.i.rtl (r), cand.i.sched? hmm. Let's map: -dr → rtl, -ds → sched? no, -ds is "sched2"? Hmm. In GCC, the dump flags: -dr = RTL, -ds = final, -dj = jump, -dl = loop, -dg = global, -df = flow, -dc = cse, -dS = combined, -dL = linenum, -dR = RTL after ra? -dt = cse2, -dJ = jump2, -dd = delayed.

Whatever — the ORDER of file creation gives the pass order. Let me check with ls -U (unsorted, directory order) or stat.

Actually simpler: let me just test whether `t = t;` (self-copy) survives to scheduling, by trying it and looking at the score. Cheap.

But actually, I realize there might be a MUCH better approach for this item. Let me reconsider.

Since the mechanism is "the li a1,320 is scheduled before the load because the load is a single-set local that gets scheduled last (C0434: single-set local is scheduled LAST; give it a second set)", the fix is to give the load's pseudo a second set.

What if the second set is the COPY to a0 that already exists?! In the no-asm case, the copy `set a0 = 167` got coalesced into the load, making the load a HARD REG (a0) definition with 1 set. In the orig, the copy survived (because of the asm).

**So: if we can prevent the coalescing, we'd have `set 167 = mem` (load) and `set a0 = 167` (copy) — the copy is a second... no, the copy is a different reg.**

Hmm, but the load 167 would then have 1 set still.

Hmm. But maybe preventing coalescing alone changes the scheduling! In the orig the load was scheduled before the li because of the asm's REG_DEP_OUTPUT on the li.

Hmm.

Let me think about the "second set" idea concretely: we want the pseudo holding the loaded value to have 2 sets, where the second set emits NO instruction.

What if the pseudo is assigned twice with the SAME value but the second assignment is not recognized as redundant until later?

```c
s32 t;
t = load;
t = load;      /* cse removes the second load */
```
CSE removes it → 1 set.

```c
s32 t;
t = load;
t = t;         /* combine removes self-move */
```
Hmm, GCC's front end: `c_expand_assign` for `t = t` — GCC's `expand_expr` for a MODIFY_EXPR with identical operands... The front end has an optimization in `c_expr_stmt`/`expand_expr`? There's `fold` on MODIFY_EXPR: `case MODIFY_EXPR: if (operand_equal_p(op0, op1)) return op0;`? Hmm, GCC's fold.c does have:
```c
    case MODIFY_EXPR:
      if (TREE_CODE (t) == MODIFY_EXPR && ...)
```
Not sure.

Even if `t = t` survives to RTL, `combine` would remove it before sched... but combine might run AFTER sched! Let's check: in GCC 2.7, the "combine" pass is in `pass_all_optimizations`? Actually GCC 2.7's c-passes.c:

```c
  /* Once all optimizations have been done, ... */
  NEXT_PASS (pass_all_optimization);
```
and
```c
const pass *pass_all_optimization =
{
  NEXT_PASS (pass_local_optimization),
  NEXT_PASS (pass_all_optimizations),
  ...
```
Hmm.

Honestly, let me just TEST. Cheap experiments:
E1: `t = t;` after the load.
E2: `t = load; t = load;`
E3: `t = load; u = t; call(u, ...)` (2 sets of t? u is a copy)
E4: `t = load; call(t, 0x140, 0xF0);` with `t` also used in a dead statement `if (t == 0) {}`.

Let me write these and score.

Also, for item 2, another idea: **change the type of the loaded variable to force a copy**. E.g. `u16 t` — but the value is a pointer (32-bit).

Another idea: what if we make the call take the value via a pointer dereference: `func_8001D0E8(*(s32*)&t, ...)` — no.

Let me also try:
E5: `t = load; func_8001D0E8(t, 0x140, 0xF0);` but with the whole thing inside `if (1) { }`? front-end folds.
E6: `do { t = load; func_8001D0E8(t, 0x140, 0xF0); } while (0);` — tried (v05) → 2. Hmm, that gives the load a second set? No.
E7: `while (1) { t = load; func_8001D0E8(t, 0x140, 0xF0); break; }`

Let me run a batch of ~20 experiments.

Actually, also very important: maybe I should test whether a "second set" of the load's pseudo is even the issue, by testing the simplest thing: put the load into a pseudo that is used twice via two different call args? no.

Let me write the batch.

One more important idea: **the `t = t;` self-copy**. If GCC's front end doesn't fold it, the RTL would have `set 167 = 167`, and `reg_n_sets` for 167 = 2 (load + self-copy). Then sched1's birthing boost is killed → the load gets scheduled EARLIER. And combine (if it runs after sched) would remove the self-copy at the RTL level without changing the schedule! That's exactly the C0434 mechanism applied to a copy instead of an asm.

But does combine run after sched1? In GCC 2.7, the order in `pass_all_optimizations`:
```
  /* Scheduling.  */
  NEXT_PASS (pass_sched);
  ...
  /* Register allocation.  */
  NEXT_PASS (pass_ra);
```
and combine is in `pass_all_optimizations`? GCC 2.7's `pass_all_optimizations`:
```c
  /* Scheduling.  */
  NEXT_PASS (pass_sched);
  /* Optimizing the register allocator. */
  ...
```
Combine (`pass_combiner`) in GCC 2.7 is in `pass_all_optimization` AFTER `pass_ra`? Hmm — in GCC 2.7, `pass_combiner` was `NEXT_PASS (pass_combiner)` inside `pass_all_optimization` right after `pass_ra`? Hmm, I think combine runs late (after register allocation) as "pass_all_optimization": 

GCC 2.7 c-passes.c:
```c
const pass *pass_all_optimization =
{
  NEXT_PASS (pass_local_optimization),
  NEXT_PASS (pass_all_optimizations),
  NEXT_PASS (pass_delete_trivial_lang_elements),
  NEXT_PASS (pass_local_optimization),
  NEXT_PASS (pass_all_optimizations),
  ...
```
Ugh.

BUT: the `combine` dump exists (cand.i.combine). And combine ran — where? Let me check whether the coalescing happened in combine. In the no-asm .sched dump, the load was already merged into the a0 copy BEFORE sched (the .cse2 dump had them separate: 235 load→167, 238 set a0=167). Then in .sched they're merged. So the coalescing happened between cse2 and sched — that's combine! So combine runs BEFORE sched1.

Hmm, that kills the `t = t;` idea IF combine removes self-moves. Does combine remove `set 167 = 167`? Combine's `simplify_reg`/`reg_move` handling: combine has code for `set x, x` → it may convert it to a no-op. In `combine.c`, `do_combine` case SET: "if (REGNO (src) == REGNO (dst) ...) " hmm, there is code: `/* If the source and destination are the same, ... */`.

Risky but let's test — it's 1 second.

Also: after combine coalesces the load into the a0 copy, the resulting insn is a HARD REG (a0) definition with ONE set. In the orig, the load sets a pseudo (167) — a LOCAL. So `birthing_insn_p` may differ for hard-reg vs pseudo definitions!

**BIG IDEA**: If the load wrote a hard reg directly (a0), it's a "call clobber" register... Hmm.

**ANOTHER BIG IDEA**: What if we make the load's result be used by something OTHER than the call, so it can't be coalesced into a0? E.g. what if the value is also used in the `if` that follows? No, the call is the last thing.

Hmm, what if we make the a0 copy not coalesce by using a DIFFERENT expression for the load's destination? Like:

```c
s32 t;
t = load;
func_8001D0E8(t, 0x140, 0xF0);
```
The copy to a0 coalesces. What if the call's first argument is `t` but `t` is ALSO used later? Not possible.

What if the load is `u32` and the arg is `s32`? Sign-extension would add an instruction. no.

What if we force a copy by making the load's pseudo a "reg/v" (virtual) with 2 uses? E.g.:
```c
s32 t;
t = load;
if (t == 0) { }    /* dead but might keep a copy */
```
The `t == 0` test would need t in a register → after the call, t is dead. GCC would fold the whole if away (t is not known). Hmm, `if (t == 0) {}` with an empty body → GCC removes the test entirely (empty body). Then t has 1 use.

What about `t = load; u = t;` where u is used in the call? Then: load→167, copy 168=167, then call a0=168. Combine might coalesce 167→168 and 168→a0, resulting in load→a0. Hmm, but the coalesce of 167 into 168 might be blocked if... Let's just test.

Let me write a batch of experiments now.

Batch 2 for item 2:
e01: `t = t;` after load
e02: `t = load; t = load;`
e03: `u = t;` extra local
e04: `if (t == 0) { func_8001D0E8(t, 0x140, 0xF0); } else { func_8001D0E8(t, 0x140, 0xF0); }` (cross-jump merges? gives 2 arms)
e05: `while (1) { ... break; }`
e06: `t = load; t += 0;` 
e07: `t = load; t = t | 0;`
e08: `t = load; { s32 u = t; func(u, ...); }`
e09: `func_8001D0E8(load, 0x140, 0xF0)` inline (already v03 = 2)
e10: cast the function pointer
e11: `t = load; func_8001D0E8(t, 0x140, 0xF0);` with t declared `s32` at function top (different scope)
e12: `volatile`? no (barrier).
e13: put the call in a `switch(t & 0)`.
e14: `t = load; if (t) { func(t,...); } else { func(t,...); }` 

Hmm e14 changes semantics? No — both branches do the same call. But it adds a branch on t (which might be optimized since both arms are identical → cross-jump merges → back to the same).

Let's think about e04/e14: GCC's cross-jump (in the jump pass, before sched) would merge the two identical arms back into one → same as now.

Hmm.

OK — let me think about **what other lever-free C construct creates an RTL "barrier" that the scheduler respects**: 

**A function call!** A call is a barrier for scheduling (GCC won't move insns across a call that may clobber registers). But adding a call changes the code.

**A store!** A store to memory that might alias... The load is `lw a0,32(s0)`. If there were a store before it that might alias, GCC would... hmm, but the store is already there (the `sh v0,14(s0)` before the block).

Hmm! **What about the `*(u8 *)(p + 0x75) = 0;` store that FOLLOWS the call?** It's after.

**What if we move a store between the load and the call?** That changes the instruction count.

OK, let me think about it from the angle of: **the target's `li a1,320` is in the SAME block as the call but AFTER the load.** In the target's .sched dump (orig), the order was load(235), asm(237), a0=167(240), a1(242), a2(244), call(246) — all in RTL order, unchanged by sched1.

So in the orig, sched1 did NOT reorder. Because the asm created dependencies.

So the question is: **why did sched1 reorder in the no-asm case?** Let's compare the two blocks' insn lists:

no-asm block: [240: a1=320], [238: a0=mem], [242: a2=240], [244: call]
orig block: [235: 167=mem], [237: asm], [240: a0=167], [242: a1=320], [244: a2=240], [246: call]

In the orig, the deps: a0=167 depends on asm(237); a1=320 depends on asm (REG_DEP_OUTPUT 237); a2=240 depends on asm; call depends on asm(REG_DEP_ANTI 237) and 240,242,244.

So in the orig, everything after the asm depends on the asm, and the asm depends on the load. It's a strict chain: load → asm → {a0, a1, a2} → call. The scheduler has NO freedom. 

In the no-asm: [238: a0=mem], [240: a1=320], [242: a2=240], [244: call]. Deps: call depends on 238, 240, 242. So 238, 240, 242 are all independent of each other and all feed the call. The scheduler chose the order 240, 238, 242.

Interesting: 240 before 238 before 242. That's neither RTL order nor reverse. 

In GCC's sched1, when several insns are ready, it picks by priority. And GCC's `launch_priority` for an insn = the sum of its dependencies' priorities + 1, and for the CALL, the arg-setup insns must be scheduled before the call.

Hmm, `a2=240` (242) scheduled LAST, `a1=320` (240) FIRST.

Hmm, could the "delay slot" be the key? The join block's FIRST instruction goes into the delay slot of the `sh`. GCC's sched1 tries to fill the delay slot with an instruction that is "cheapest". `compute_insn_cost` in sched1:
```c
/* Return the cost of an instruction, given the number of insns that
   depend on it.  */
static int
compute_insn_cost (insn, ...)
```
Hmm.

Whatever the mechanism, the practical question: how to make the load come first.

**PRACTICAL IDEA**: since `a1=320` is scheduled first and the load second, maybe we can make the load "unavailable" early so it's forced later... no, we want it earlier.

**PRACTICAL IDEA 2**: Make the a1 argument NOT a constant at the RTL level, so it's not a "birthing insn" with priority. If a1's setup were a dependent instruction (e.g. `a1 = a1 + 0`... no).

Hmm, hold on! What if a1's value 320 were produced by a computation that depends on the LOAD? Like... the call is `func_8001D0E8(t, 0x140, 0xF0)`. What if we write it as `func_8001D0E8(t, 0x140, 0xF0)` — no.

OK, radical: **what if the 2nd argument is spelled such that GCC emits it in a different form**? The target's `li a1,320` — li with a 16-bit immediate. Any spelling of the constant 320 gives `li a1,320`.

What if the arg were `(s32)(u16)320`? Same.

Hmm.

**PRACTICAL IDEA 3**: What if we ADD an extra (dead) use of the loaded value that requires an extra register but no extra instruction? Impossible.

**PRACTICAL IDEA 4**: What if the load is made to write a pseudo that is NOT coalescable into a0 — e.g., by using `t` in a `?:` or by making the call take `t` while `t` is also the base of another expression? 

Hmm, what if we write the call as:
```c
func_8001D0E8(t + 0, 0x140, 0xF0);
```
`t + 0` → combine folds to t. Might block the coalesce at the combine stage? Let's test.

Or `func_8001D0E8((s32)t, 0x140, 0xF0);` — a cast to the same type.

Or `func_8001D0E8(t - 0, ...)`.

Let me test a batch of these.

**PRACTICAL IDEA 5**: Use the "call group" — GCC's sched1 forces the arg setup insns of a call to be scheduled together in RTL order if they're all "call operand" insns. Hmm, in the no-asm case they weren't in RTL order.

Let me now look at GCC 2.7's actual sched1.c to settle this. Is the source available? Let me check tools/bin/gcc-2.7.2-psx/ for source. Probably not, but let me look for a "gcc-2.7.2" source tarball in the repo.

Let me check.
