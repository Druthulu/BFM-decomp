---
ts: 2026-10-22T11:16:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_za2vAKzgubwXZTLvxy3b
---
In the orig:
- The load (235) is in its OWN block! `(note 232 230 248 "" NOTE_INSN_BLOCK_BEG)` then `(note 248 232 235 "" NOTE_INSN_BLOCK_END)` — so the block ends at 248 (which is the asm's "block end" note), and then insn 235 starts a new block (the note 248 is BLOCK_END and the insn 235 follows).

Wait, the notes: `NOTE_INSN_BLOCK_BEG 232` ... `NOTE_INSN_BLOCK_END 248`. In GCC's RTL dump, a block is [BLOCK_BEG note, ...insns..., BLOCK_END note]. Here BEG is at 232 and END at 248, and the insn 235 comes AFTER the END note (as the first insn of the next block). Hmm, that's odd. Actually in GCC the layout is: BLOCK_BEG note, then insns, then BLOCK_END note. But here END(248) comes right after BEG(232) and before insn 235.

Hmm, the note numbering: `(note 248 232 235 "" NOTE_INSN_BLOCK_END)` — this note's prev is 232 and next is 235. So in the insn list order: note 232 (BLOCK_BEG), note 248 (BLOCK_END), insn 235, insn 237, insn 240, ...

That's GCC's convention: BLOCK_BEG and BLOCK_END notes bracket... hmm, actually in GCC 2.7 the RTL dump for a basic block is:
```
(note X "" NOTE_INSN_BLOCK_BEG)
(insn ...)
...
(note Y "" NOTE_INSN_BLOCK_END)
```
Hmm, but here END is before the insns. Let me look at another block in the dump to understand. Earlier in the no-asm dump we saw:

```
(note 232 230 235 "" NOTE_INSN_BLOCK_BEG)
(note 235 232 246 "" NOTE_INSN_DELETED)
(note 246 235 240 "" NOTE_INSN_BLOCK_END)
(insn 240 246 238 ...)
```
So BEG(232), DELETED(235), END(246), then insn 240. So the convention here is: BEG note, then (deleted insns), then END note, then the actual insns. So the END note precedes the block's insns. OK so in the ORIG:

```
(note 232 230 248 "" NOTE_INSN_BLOCK_BEG)
(note 248 232 235 "" NOTE_INSN_BLOCK_END)
(insn 235 ...)   <- load
(insn 237 ...)   <- asm
(insn 240 ...)   <- a0 = 167
```
All in ONE block (232-248). So the asm did NOT split the block here!

Hmm! So the block structure is the same. Then why is the order different?

The difference: in the orig, the sequence is load(235) → asm(237) → a0=167(240) → a1(242) → a2(244) → call(246).
In the no-asm: load(235) → a0=167(238) → a1(240) → a2(242) → call(244). Then COALESCE merged the load into the a0 copy → the load becomes `set a0 = mem` with uid 238.

So the key difference is the COALESCE. In the orig, the load stays separate (uid 235) because the asm breaks the coalescing chain. In the no-asm, the load and the copy coalesce into one insn (uid 238).

And then in the no-asm, the scheduler puts the coalesced load AFTER the li a1. In the orig, the load (235) is before the asm, and the asm is a barrier for scheduling: GCC's sched1 doesn't move insns across a volatile asm (the asm has a "barrier" property? Actually sched1 treats the asm as an insn with no deps but GCC's `insn_barrier`?). The asm insn is `set 167 = asm_operands(...)` with input 167 → so the load must precede the asm, and the a0 copy must follow the asm (REG_DEP on 237). And the li a1 has REG_DEP_OUTPUT on 237 (the asm clobbers a1? yes — the asm's output clobbers all caller-saved regs? no, but REG_DEP_OUTPUT 237 on 242/244 means those insns depend on the asm's output).

So in the orig: the asm acts as a barrier: the li a1 (242) depends on the asm (REG_DEP_OUTPUT), so it must come after the asm. And the load must come before the asm. Hence load first, then asm, then li a1, then call.

So the mechanism is: **the asm's output creates a dependency for the li a1** (because the asm might clobber a1 — the compiler must assume the asm clobbers caller-saved registers unless declared). That's why the li a1,320 must come AFTER the asm, and the load (feeding the asm) must come BEFORE.

So to replicate in plain C: we need the li a1 to be "blocked" from being hoisted above the load. That means the li a1 must depend on something that depends on the load.

Hmm! What if the second argument's value were derived from the load? Semantically it must be 0x140 constant.

Hmm, but wait: `func_8001D0E8(t, 0x140, 0xF0)` — the call's args. What if we could make GCC think the li a1 depends on the load?

Alternatively: prevent the coalescing of the load with the a0 copy, AND make the load have a higher priority.

Hmm, but even without coalescing, would the scheduler put the load first? In the orig the load is first because of the asm barrier, not because of priority.

Let's think about what makes the li a1 lose priority. In GCC sched1, `li a1,320` (a constant birth) gets a "birth boost". In the no-asm version, the coalesced load insn (uid 238) vs the li (uid 240): the scheduler picked the li first.

**What if the load is given a HIGHER birth?** The load's operands: reg 73 (s0) — available. The li's operands: constant. GCC's sched1 `rank_for_schedule`: for each insn it computes "birth" = the number of insns in the block that must precede it... and there's a rule: "if an insn has no unscheduled predecessors, its priority is boosted by 1" (the "birth" of the block).

Actually in GCC's sched1.c `rank_for_schedule`:
```c
      /* Calculate the number of insns that we must wait for: the birth. */
      ...
      if (insn->priority > max_priority) ...
```
Hmm.

Let me look at it from the "what changed" perspective: the coalesce merged the load and the copy. The merged insn's uid is 238 (the copy's), and the li is 240. So the load-insn has a LOWER uid than the li. Yet it was scheduled after.

In GCC's sched1, when priorities tie, the tie-break is by "insn->priority" then... GCC 2.7's sched1 uses a "ready list" sorted by priority, and when priorities are equal, by LUID DESCENDING or ascending? Hmm.

Actually, GCC's sched1 has this important detail: `sched1` computes for each insn a "priority" = the number of insns in the block that must be scheduled before it (its "birth" within the block), plus a special bonus for calls. And the "dependency" of the call on the a0 copy.

The li a1 (240) is independent of everything except the call. The coalesced load (238) is also independent of the call's args but IS used by the call (REG_DEP).

In GCC sched1, the call is a "group": `SCHED_GROUP_P` — the call and its arg-setup insns are scheduled together. When the scheduler picks the call, it also picks the group. Hmm, but then the load would be part of the group (a0 setup) and the group order is fixed by RTL order.

Hmm, but the li (240) came before the load (238) — so they weren't in the same group, OR the group order isn't fixed.

Hmm, actually in GCC's sched1, `SCHED_GROUP_P` is used for "the call and the instructions that set up its arguments" — they're scheduled as a unit, in their RTL order? If so, the order within the group would be load(238), li(240), li(242), call(244) — but the actual is li(240), load(238), li(242), call(244). So not a rigid group.

OK. Let me try a different empirical approach: try MANY variants of the load/call region and see if anything changes the order. Let me specifically try to prevent coalescing by using a form where the load's result must be copied:

Idea: `t = load; call(t, ...)`. The copy `a0 = 167` was created by expand. If instead we write `t = load; call(*(s32*)&t, ...)`? no.

Idea: Make the pseudo used twice: `t = load; u = t; call(u, ...)`. Then the load→t→u chain: t is used by u's copy and u by the call. Coalescing might still merge.

Hmm, what if we give the load TWO uses: `t = load; call(t, 0x140, 0xF0);` and also `if (t == 0x1234) {}` — no.

**NEW IDEA**: What if the load's result is used to compute the SECOND argument in a way that GCC folds to 320 but only AFTER scheduling? Like:

```c
s32 t = load;
func_8001D0E8(t, 0x140 + (t & 0), 0xF0);
```
`t & 0` → folded to 0 by the front end? `fold` in the front end: `x & 0` → 0 is folded only if x has no side effects — the front end's fold does handle `x & 0` → 0 when x is not a "volatile" lvalue... Actually GCC's fold-const.c `fold` for BIT_AND_EXPR: `if (integer_zerop (TREE_OPERAND (t, 1)) && ! TREE_SIDE_EFFECTS (TREE_OPERAND (t, 0))) return 0;`. Yes! The front end folds `t & 0` → 0 immediately. Damn.

What about `0x140 + (t - t)`? `t - t` → the front end's fold: `fold` for MINUS_EXPR with identical operands → 0? GCC's fold has: `case MINUS_EXPR: if (operand_equal_p (TREE_OPERAND (t, 0), TREE_OPERAND (t, 1), 0) && !TREE_SIDE_EFFECTS(...)) return 0;`. I believe GCC 2.7's fold does have that. Hmm.

What about `0x140 ^ (t ^ t)`? Same issue.

What about using a value GCC can't fold but which is still 320 at runtime? Like `0x140 + (t & 0)` where t is volatile? no.

Hmm, what if the argument is a global `const`? `extern const s32 D_801x;` — reading a const global requires a load → extra instruction.

**Different approach**: make the SECOND argument not a constant at the RTL level but still produce `li a1,320`. E.g., `0x140` is a constant → `li`. What if we write `320` vs `0x140`? Same.

Hmm, what if the value is computed as `(s32)(u16)0x140`? Same constant.

**Different approach**: What if we don't need the li a1 to be blocked, but instead make the LOAD have higher priority?

In GCC sched1, the priority of an insn is based on:
```
  /* The priority of an insn is the number of insns that must be
     scheduled before it (its "birth") plus a bonus. */
```
And there's this in `rank_for_schedule`:
```c
      /* Add the dependencies' priorities. */
      ...
      /* If this is a call, then we must schedule the insns that set up
	 the arguments. */
```
And there's the "delay slot" logic: `sched1` tries to maximize the number of insns scheduled in the delay slot of the preceding branch — `compute_insn_cost`/`fill_delay_slot`.

AH WAIT. Here's a thought: the join block's first instruction goes into the delay slot of the `sh` (the previous block's last instruction). GCC's `sched1` has a special feature: it tries to fill the delay slot of the *first* block's preceding branch. And the "cost" of an insn for the delay slot: `compute_insn_cost` in sched1 gives a bonus for insns that can be safely moved into a delay slot (fewer dependencies).

Hmm. In our case, the delay slot of the `sh` — the sh is not a branch. But GCC's `fill_delay_slot` in delayed.c (late pass) handles branches.

Hmm, honestly, let me consider that the difference might be from **coalesce**: in the no-asm case, the load merged with the copy, so the load insn became `set a0 = mem` which is a HARD REG (a0) definition. In the orig, the load sets a pseudo (167) and then a separate copy sets a0. In the no-asm version the merged insn writes a0 directly.

Does that matter for priority? Possibly! In the orig, the insn `set a0 = 167` (240) depends on the asm. The li (242) depends on the asm (REG_DEP_OUTPUT). So the load (235) has to be before the asm.

In the no-asm, the load writes a0 directly and is used by the call.

Hmm, what if I prevent coalescing by making the pseudo's value have ANOTHER use that requires a separate register? Then we'd get an extra move. No good.

**KEY ALTERNATIVE**: what if we could make the load's result go through a pseudo that is ALSO used later, so the coalesce can't merge? Hmm.

Let's try: **use the loaded value twice** in a way that produces no extra instruction. E.g., `t = load; call(t, 0x140, 0xF0);` — the target's a0 is the loaded value, used once.

Hmm OK.

**RADICAL ALTERNATIVE**: maybe I should look at whether the target's `li a1,320` really comes after the load because of the asm, or because of something else entirely — like the `sched1` "call group" behavior where the a0 setup is scheduled with the call.

Let me test: in the no-asm version, what if the load's pseudo is NOT copyable to a0 (e.g. the load's result is needed in a callee-saved register)? Then the load would be `set 167 = mem` and the copy `set a0 = 167` would remain, giving [load, copy, li, li, call] in the RTL. Then the scheduler might order [load, copy, li, li, call]? If the copy stays, the li might still be hoisted before the load.

Hmm, but actually! Interesting: in the ORIG, the order within the block is load, asm, copy-a0, li-a1, li-a2, call — that's the RTL order preserved. The scheduler didn't reorder at all (because the asm is a barrier for the li's REG_DEP_OUTPUT).

Now: is the ASM really needed, or would a plain-C construct that creates a REG_DEP_OUTPUT-like dependency work? The dependency is: "the li a1 must come after the load" — because the asm might have clobbered a1.

In plain C, the li a1 is only clobbered by... nothing. So there's no natural dependency.

**UNLESS**: the li's value is derived from a variable that is also derived from the load.

OK, radical idea: what if we RESTRUCTURE the function so the call's arguments are computed differently? E.g., what if `func_8001D0E8(t, 0x140, 0xF0)` becomes `func_8001D0E8(t, 0x140, 0xF0)` where 0x140 is a `static const int` declared at file scope in the body file? But the body file is spliced into the TU — can I add file-scope declarations? The `--body` mode replaces the function definition; the file might allow other declarations. Hmm, but the constraint says "no signature or decl change outside the body". So no file-scope decls.

Hmm. But wait — what about a local `const`? `const s32 k = 0x140;` — the front end folds a local const initialized with a constant into the constant. Yes.

What about `volatile const`? That changes code.

Hmm, what about `static s32 k = 0x140;` inside the function? A function-local static! The front end creates a static VAR_DECL initialized to 0x140. GCC would load it... but for a local static with a constant initializer, GCC 2.7 might treat it as a constant (folding). Actually, GCC creates the static in .data and reads it. But GCC's front end may fold `static int k = 5;` uses into the constant 5 (yes — GCC's front end does "fold_static_initializer"/`c_static_initializer` puts it in the constant pool and `fold` uses the constant). In GCC 2.7, a local static int with a constant initializer used in an expression → the front end's `fold` has `case VAR_DECL: if (TREE_CODE (t) == VAR_DECL && TREE_STATIC (t) && DECL_INITIAL (t) ...) return DECL_INITIAL (t)`. I believe GCC does fold static vars with constant initializers when they're not volatile. Yes, GCC's fold.c: `fold` on a VAR_DECL with TREE_STATIC and a constant DECL_INITIAL returns the constant (with a "must not modify" caveat — for `static int k = 5;` GCC actually does fold it, but only if the variable is never modified... hmm, GCC's fold has:
```c
    case VAR_DECL:
      if (TREE_CODE (t) == VAR_DECL && TREE_STATIC (t) && DECL_INITIAL (t)
	  && TREE_CODE (DECL_INITIAL (t)) == INTEGER_CST
	  && ! DECL_REGISTER (t) ...)
```
Hmm, I'm not 100% sure for GCC 2.7. There's `fold_static_initializer`.

Let's just TEST it. If `static s32 k = 0x140;` isn't folded, the RTL would have a load from .data → extra instruction. But if GCC's fold keeps it as a constant in RTL but with a "load" that's optimized... hmm.

Actually, the RTL for a static var read is `(mem (symbol_ref k))` — a load. GCC's RTL-level folding (in `simplify`/`fold_const`) can turn `(mem (symbol_ref k))` into the constant IF the variable is known not to change — GCC's `cse`/`simplify` does this: `simplify_expr` has a case for MEM with a symbol_ref → look up the DECL_INITIAL if the var is not volatile and... GCC does have `lookup_expr` in tree-ssa; in RTL mode, GCC 2.7's `simplify_expr`:
```c
    case MEM:
      ...
      if (GET_MODE (x) == VOIDmode) return 0;
      /* Handle the case of a symbol ref. */
      if (TREE_CODE (addr) == SYMBOL_REF && DECL_P (TREE_OPERAND (addr,0))) {
	  if (DECL_INITIAL (decl) && TREE_CODE (DECL_INITIAL (decl)) == INTEGER_CST
	      && ! DECL_REGISTER (decl) && TREE_STATIC (decl) && ! TREE_SIDE_EFFECTS(...))
	      return DECL_INITIAL (decl);
      }
```
Hmm! I'm not sure. But there IS such folding in GCC — `simplify_expr` in simplify.c does:
```c
    case MEM:
      if (GET_MODE (x) == VOIDmode) return 0;
      ...
      /* ??? */
```
Hmm.

Actually, you know what — GCC definitely does this optimization: `static const int x = 5; return x;` compiles to `li 5`. Yes, GCC folds static const ints. But `static int x = 5;` (non-const) — GCC also folds it if x is never modified? I believe GCC does NOT fold non-const static vars in general (the value could change via another TU). But for a function-local static, GCC knows it's only accessible in this function... but it can be modified. If never modified, GCC's "fold" would need flow analysis.

Hmm, GCC 2.7's front end for a function-local static with a constant initializer: `c_static_initializer` puts it in the static pool, and the reference is a VAR_DECL. Then `fold` on the VAR_DECL: GCC 2.7's fold.c has:

```c
    case VAR_DECL:
      if (TREE_CODE (t) == VAR_DECL && TREE_STATIC (t) && DECL_INITIAL (t)
	  && TREE_CODE (DECL_INITIAL (t)) == INTEGER_CST
	  && ! DECL_REGISTER (t) ...
```
I really don't remember. Let's just test it! It's cheap.

If GCC folds it at the FRONT END → `li a1,320` as before → no change.
If GCC keeps it as a load until LATE (after sched1) → the a1 setup becomes a LOAD (not `li`), which changes the instruction. Not good either.

Hmm, that changes the instruction from `li a1,320` to `lw a1, k` — wrong.

OK, different tack.

**Think about `sched1`'s handling of the call group.** GCC's sched1.c has this (2.7):

```c
	  /* If we have a call, then we must schedule all the insns that
	     set up the arguments ... */
```
Hmm.

Actually, here's a MUCH more promising idea. Let's revisit: in the no-asm case, the difference arose AFTER coalesce. What if we simply prevent the coalescing by making the load's pseudo have a second use that requires it to be a specific register? Hmm.

Actually — hold on. Let's look at the no-asm .sched dump again:

```
(insn 240 246 238 (set (reg:SI 5 a1) (const_int 320)) 159 {movsi_internal2} (nil)
(insn 238 240 242 (set (reg:SI 4 a0) (mem/s:SI (plus:SI (reg/v:SI 73) (const_int 32)))) 159 {movsi_internal2} (nil)
```
So insn 240 (li a1) is first, then insn 238 (load into a0).

Now — what determines this order? GCC sched1 sorts by priority. Let me consider that GCC's sched1 processes the block and for each insn computes `priority` via `rank_for_schedule`, which computes the "birth" = the number of insns that must be scheduled before it. Both have birth 0.

But then, GCC's `sched1` has this special rule in `rank_for_schedule`:
```c
	  /* If the insn is not dependent on anything, and the block's first
	     insn can go in the delay slot, ... */
```
and
```c
      /* Compute the priority of the insn: the number of insns that
	 depend on it (its "fan-out") plus ... */
```

Hmm — actually I recall GCC's sched1 `rank_for_schedule` computes:
```c
  /* Compute the dependencies of each insn. */
  ...
      /* The priority is the number of insns that must be scheduled before
	 this one (its DEPENDENCY DEPTH). */
```
and then there's the "birth boost" in `sched1`: `if (insn->priority > max_priority)`.

And crucially, GCC's sched1 has the "call group" logic:
```c
      /* If this insn is a call, then the insns that set up its arguments
	 must be scheduled with it. */
```

I recall in GCC 2.7 sched1.c:
```c
	  /* We must schedule the insns that are operands of a call
	     immediately before the call.  */
```
Yes! GCC's sched1 has a mechanism where for a call_insn, all the "argument setup" insns (those that set the arg registers) are forced to be scheduled right before the call, in their RTL order. That's `SCHED_GROUP_P`.

If that's the case, the group = [a0 setup (238), a1 (240), a2 (242)] and they should be scheduled in RTL order: 238, 240, 242. But the actual order is 240, 238, 242. So NOT a rigid group.

Hmm.

OK. Let me stop analyzing and start brute-forcing. Given ~1s per score, I can try 100 variants cheaply. Let me generate lots of variants programmatically around this region and look for anything with score < 2.

Variants to generate:
1. Different types for t (s32, u32, s16, u16, long).
2. The load written differently (through u8*, s32*, char*).
3. The call written with a cast on the function pointer: `((void(*)(s32,s32,s32))func_8001D0E8)(t, 0x140, 0xF0)`.
4. The load split across two statements: `t = ...; t = t;`
5. `t` declared as a register? No (register is forbidden).
6. Add `t = t + 0;`.
7. Use a comma operator.
8. Use a conditional expression with a constant: `func_8001D0E8((t, t), 0x140, 0xF0)`.
9. Put the call inside a `while` with `break`.
10. Move the whole block before the `if ((func_80029178(0xB3) & 0xFF) != 0) {...}` block? No.
11. Change the enclosing `if` structure: e.g., invert the condition to `== 0` and swap the arms.
12. Put the load+call inside the `if` body and duplicate in else? no.

Hmm, #11 is interesting! The target has `beqz v0,3ad4` — the ==0 path branches to the join. If in C we write `if (cond == 0) { ... } else { ... }` with the arms swapped, GCC might generate the branch differently. But the target's structure has the !=0 body fall-through and the ==0 branch to the join. That's what `if (cond != 0) { body } ` + join gives.

Hmm.

Let me think about #12 variant: what if the load+call is placed inside the if-body (the !=0 arm) AND the ==0 arm ALSO has the load+call? Then GCC would have 2 loads and 2 calls → 202 ins. No.

Hmm hold on, let me reconsider. Actually — what if we could get GCC to schedule the load first by making the load's register a0 have a "higher priority" because the a0 setup is part of the call's "operand group" and the call group is scheduled as a unit, with the group placed at the block's end, and the load being part of the group...

Actually here's a thought: in the no-asm case, the order was li-a1, load-a0, li-a2, call. The a2 li came after the load. Weird! So the group order isn't the RTL order.

Wait, that's really odd: RTL order was a0(238), a1(240), a2(242). Final: a1(240), a0(238), a2(242).

Hmm, so sched1 chose: a1 first, then a0, then a2.

What if the difference is the "delay slot" of the block's first instruction? The join block's first insn goes into the delay slot of the sh. GCC's sched1 has a heuristic to maximize the number of insns in the delay slot — and the delay slot must not have a dependency on the branch. Both a1=320 and the load are fine.

Hmm, `sched1`'s `compute_insn_cost`:
```c
  /* Compute the cost of an insn: the number of insns that depend on it,
     etc. */
```
GCC's sched1 ranks by "priority" where an insn's priority = the number of insns that depend on it (its fanout) + 1? The load (a0) has fanout 1 (the call). The li a1 has fanout 1 (the call). Tie.

OK, ENOUGH. Let me look at this from the "GCC source" angle — is the gcc 2.7.2 source available? The toolchain is at tools/bin/gcc-2.7.2-psx/. Maybe the source is available somewhere. Let me check.

Actually, let me check if there's a cookbook entry about this. The brief says "Consult before, capture after. Grep cookbook/INDEX.md and rules/INDEX.md for the task's subjects before recurring work".

Let me grep the cookbook for "sched1" / "birth" / "asm" / "launder".
