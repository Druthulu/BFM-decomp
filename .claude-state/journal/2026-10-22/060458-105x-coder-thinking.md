---
ts: 2026-10-22T12:04:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_flpR3uyXfEQzjOqUmKpq
---
w01 (s16 v1): score 6, 89 ins exact. The remaining differences:
1. The branch target differs (2060 vs 2064) — just a layout artifact from the missing instruction.
2. The case0 arm's `lw v1,32(s0)` is missing (the target has it at 36).
3. Mine has an extra nop at 46.

So the ONLY substantive issue is: **the unk20 load must be in the case0 arm** (and in the case1 arm).

Target:
- case0 arm: `lw a0,32(s0)` (arg), `li a0,409`, `lw v1,32(s0)` (e), `j 2084`, `li a1,2` (delay)
- case1 arm: `lw a0,32(s0)`, `li a0,409`, `lw v1,32(s0)` (e), `li a1,3`

Mine: the e load is sunk to the shared block (one load instead of two).

**SO THE WHOLE ITEM 1 IS NOW: keep the unk20 load in BOTH arms.**

The load in the target is `lw v1,32(s0)` — the SAME register v1 in both arms. So GCC allocated the same register to both arms' `e` values (a phi). That happens when the two arms' `e` are a phi with 2 definitions.

In plain C, the front end creates a phi for `e` at the join. GCC 2.7's front end (c-typeck.c) has "phi optimization": if all the phi's args are the same variable → replace the phi with that variable. Here the args are two DIFFERENT expressions (both `unk20` loads, but in different blocks) — the front end's phi args are the RHS expressions. Since both are `((Unkstruct*)s0)->unk20` (the same TREE), the phi is folded → one load → placed in the join.

**So: make the two arms' `e` RHS TREES DIFFERENT so the phi isn't folded!** But then the two loads would be in different blocks and the join needs a phi → GCC would need to copy. Hmm — but GCC 2.7's front end for a phi with different args creates a "phi" statement that assigns the phi variable from the arg, in each arm (a copy). Hmm, that would add a copy instruction.

Hmm, but wait: the target has NO copy in the arms — the loads write v1 directly. So GCC allocated the phi variable to v1 and the loads wrote it directly.

Hmm! Actually, in GCC 2.7 the front end's phi handling: the phi's "args" are the RHS values in each predecessor. When the args are different trees, the front end creates copies. But GCC 2.7's front end (c-typeck.c) has an optimization where the phi is only created for "simple" cases.

Hmm, but the ORIGINAL (with the asm) has the SAME source structure and GCC produced the target! So the asm made the difference at the RTL level, not the tree level. In the original, the tree-level phi would ALSO be folded (both arms assign `unk20`)! But the asm makes the case1 arm's `e` an asm output → the tree for case1's e is the ASM's result, not `unk20` → the phi's args differ → the phi survives → 2 loads → and the phi variable is allocated to v1 with the loads writing it directly?

Hmm, but in the original, case1's `e` = the asm's output (a copy of the loaded value), and the asm's input is `e` = the load. So case1 would have: load unk20 → e → asm → e. That's 2 definitions of e in case1 (the load and the asm). And the target shows only ONE load in case1 (`lw v1,32(s0)` at 207c). So the asm's copy was coalesced into v1.

OK. So in plain C, to get the target, I need:
- 2 loads of unk20 (one per arm).
- No extra copies.
- The join uses v1.

**How to make the front end NOT fold the phi?** The phi folding (in GCC 2.7's c-typeck.c `c_phi`?) — hmm, actually where does this folding happen? GCC 2.7's front end: the "phi" is created by `c_expr`/`expand_end_case`? Hmm, GCC 2.7's front end for a variable assigned in multiple branches and used after: the front end creates a `PHI` node in the tree? GCC 2.7 didn't have tree PHIs (that came with SSA in 3.x). In GCC 2.7, the front end creates a `VAR_DECL` with multiple assignments and the RTL expansion handles the "pseudo with multiple sets" via `expand_end_case`...

Hmm. In GCC 2.7, the front end (c-typeck.c) creates for a variable assigned in a conditional:
```
CASE_LABEL (case1)
  ... assign e = X ...
CASE_LABEL (case2)
  ... assign e = Y ...
CASE_LABEL (case3)
  ... use e ...
```
and the RTL expansion creates a pseudo with 2 sets (one per branch) — the "phi" is implicit in the RTL (a pseudo with multiple sets in different blocks; the register allocator handles it via local-alloc's "reg_n_sets" and the "REG_EQUIV"/"reg_equiv" mechanism).

So in the RTL, `e` is a pseudo with 2 sets: `e = unk20` in case0 and `e = unk20` in case1. **CSE would CSE the two loads?** No — CSE works within a block, but the two sets are in different blocks. Hmm. But the LOADS are the same MEM → GCC's CSE (cse.c) has "cse across blocks" via `cse_basic_block` only within a block. Hmm.

Hmm, but GCC 2.7's cse has a `record_eqv` mechanism that works across blocks: `cse.c`'s `record_eqv` records equivalences between a reg and a constant/reg, and these propagate across blocks via the "reg_equiv" table (which is per-block but saved/restored at block boundaries). So a load in case0 could be recorded as equivalent to... hmm, the MEM is not a reg.

Hmm! But `cse.c` has this: "If we see a load from an address, and later in a DIFFERENT block we see the same load, we can forward the value" — that's the "cross-block CSE" in GCC 2.7's cse.c? I believe GCC 2.7's cse.c does have limited cross-block CSE: `cse.c`'s `record_eqv` for MEMs isn't done, but `update_flow`...

Hmm. Actually, the sinking I observe (both loads → one in the join) is most likely done by the **front end's "phi" handling in `stmt.c`/`expand.c`**: GCC 2.7's `expand_end_case`/`expand_start_case` — when a variable is assigned in multiple branches of a case statement, GCC's front end (c-typeck.c) creates the assignments and the RTL expansion creates the pseudo with multiple sets. Then the REGISTER ALLOCATOR (local-alloc) sees the pseudo with 2 sets in 2 blocks and needs ONE register for both → it can use the same register (they're in exclusive blocks) → so the loads in both arms write the SAME register → the target's form!

So WHY did my candidate sink the load to the shared block? Because CSE (or cse's cross-block propagation) found the two loads equivalent and eliminated one, then the remaining load... hmm, but the remaining load is in ONE arm, so it can't be used at the join.

Hmm, unless: the load in case0 was eliminated (CSE'd with case1's) and then the value is available in the join via the "reg_equiv" forwarding. Then GCC's "jump" pass hoists the load to the join.

Hmm — that's exactly "cse forwards only within a block, cse.c:7358-7369" from the cookbook. Hmm.

OK, PRACTICAL: how do I prevent the two loads from being CSE'd/forwarded?

**The cookbook's R41: "A store in EACH arm when the target reloads a global after it (cse forwards only within a block, cse.c:7358-7369, :8039) or when sched1 treats two symbols as non-aliasing"**.

Hmm! "cse forwards only within a block" — so the FORWARDING is within a block. So the cross-block elimination isn't CSE.

Hmm. Let me think about GCC 2.7's **jump.c's `jump_combine`/`thread_prologue_and_epilogue`**: the `shared` block has 2 preds. `thread_prologue_and_epilogue` moves the prologue of a block into its predecessors — that would move the shared block's insns INTO each predecessor (duplicating), not the reverse.

Hmm, what moves a load INTO the join from the arms? That's "hoisting to the common dominator" — the join's predecessors are case0 and case1, and their common dominator is the block before the branch. Hoisting the load there would put it BEFORE the branch → the target doesn't have that.

Hmm, so it's not hoisting; it's that the load exists ONCE in the join.

**AH — maybe the front end does it!** GCC 2.7's front end, for a variable assigned in two branches of a `case` statement and used after: the front end's "phi" handling in c-typeck.c has:
```c
/* If the variable is assigned the same value in all branches, ... */
```
Hmm.

OK, ENOUGH THEORY. Let me EXPERIMENT with ways to keep the load in each arm:

**E1**: Make the two arms' `e` assignments textually different in a way that changes the TREE but not the code:
- case0: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;`
- case1: `e = *(s32 *)((u8 *)s0 + 0x20);`   ← tried (w04 etc.), no effect.

Hmm, w04-w11 all gave 8 (with u16) — the same as the plain u16. So the alias/tree trick did nothing.

**E2**: Make the two arms' e values differ SEMANTICALLY but evaluate to the same thing — impossible.

**E3**: What if `e` is loaded in each arm and the JOIN doesn't use `e` but the arms each do their own work? I.e., DUPLICATE the shared block into the arms (each arm does its own `t = e->4; t |= 0x8040; e->4 = t; func_8012C658(...)`). Then there's no join use of e → each arm has its own load → 2 loads. But the target has the shared block ONCE (the code at 2084 is shared).

Hmm, but if the arms are duplicated and cross-jump re-merges them... the arms differ in argmode (2 vs 3). Hmm.

Hmm, hold on! Let me look at the target again:
```
2054: li a0,409
2058: lw v1,32(s0)
205c: j 2084
2060: li a1,2      <- delay slot of the j
2064: lw a0,32(s0)   <- case1's arm starts
...
2078: li a0,409
207c: lw v1,32(s0)
2080: li a1,3      <- falls through to 2084
2084: lw v0,4(v1)  <- shared
```
So case1 FALLS THROUGH into the shared block (no j), and case0 jumps to it. The shared block is at 2084. So the "shared" label in the C is the join.

OK so in the target, both arms set v1 (the load) and the join uses v1.

**E4**: What if the `e` variable is declared as a POINTER (`s32 *e`)? Then the phi would be a pointer phi. GCC's local-alloc treats pointers specially. And the assignment `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` requires unk20 to be a pointer type. Let me check the struct!

Let me look at Unkstruct_800B5CB8's unk20 type. If it's `s32 *`, then declaring `e` as `s32 *` is natural and the loads stay in the arms (pointer phis are often kept).

Let me check the struct definition and the CAST_WIDTH macro.

Let me grep.

Actually, hold on. Let me think about what the original does once more:

In the ORIGINAL, the tree for case1's `e` is the ASM (a special tree). So at the RTL level, case1's e = the asm's output = a copy of e_old (which = the load). Hmm, so the original has in case1: `load unk20 → e`, `asm(e) → e`. Two definitions of e in case1 + one in case0 = 3 definitions.

The RTL: e is a pseudo with 3 sets. The register allocator: local-alloc sees e with sets in case0, case1 (twice) and the use in the join.

Hmm, and the loads: case0 has `e = load`, case1 has `e = load` + `asm`.

The target's case0 arm has `lw v1,32(s0)` and case1 has `lw v1,32(s0)` — so 2 loads, one per arm. The asm's copy was coalesced (the asm's output v1 = the same reg).

So in the original, CSE did NOT eliminate one of the two loads (they're in different blocks) — good. And the register allocator gave both the same register v1 → the join uses v1.

**So in plain C, why does ONE load survive and end up in the join?**

AH, maybe it's the **front end's phi optimization**: GCC 2.7's front end, when a variable is assigned in multiple case branches, creates a "phi" and there's an optimization in c-typeck.c/expr.c: if the phi args are all the same, the phi is replaced. Then only ONE assignment remains... and where is it placed? If the phi is replaced by the common expression, the expression is evaluated at the JOIN. **THAT'S THE SINK!**

And in the original, the asm makes the args different → the phi survives → 2 assignments in the arms.

**SO: to keep 2 loads, the two arms' `e` RHS must be different TREES.** But my char* vs struct test (w04/w05/w06/w07) didn't change it! Hmm.

Unless the front end's phi optimization compares the expanded values or the front end normalizes them.

Hmm, wait — w04 (u16 v1 + case1 e char*) gave 8, the same as the plain u16 (v17 = 8). If the phi weren't folded, the load count would change (2 loads instead of 1) → the count would be 90, not 89. It stayed 89 → the phi WAS folded.

Hmm. So the tree difference didn't prevent the folding. Which means the folding happens at the RTL level (cse/jump), not the tree level.

**RTL-LEVEL: GCC 2.7's cse.c has "cse across blocks" for REG_EQUIV: when a pseudo is set to the same value in two blocks, cse's `record_eqv` can make them equivalent.** cse.c's `record_eqv`:
```c
      /* If we have a set of a reg to a reg, and we see another set of the
	 same reg to the same reg, we can record them as equivalent... */
```
For MEMs, cse.c's `record_eqv` doesn't handle MEMs. BUT: the two loads `e = mem[s0+0x20]` — cse's `record_eqv` for a SET to a MEM isn't done.

Hmm, but the two loads are the same MEM → cse's `equiv_find`? Hmm.

OK — what about GCC's **jump.c's `jump_combine`** or the **"local reg" mechanism**: the pseudo `e` has 2 sets in 2 blocks; local-alloc assigns one reg; both loads write that reg. That's what we want! So the RTL should have 2 loads.

Hmm, so maybe the RTL DOES have 2 loads, and the sinking is done by the **reload/reload1** pass (which hoists a load to the common block if it's the same)? Hmm, no.

Hmm, OR the sinking is done by the front end after all, via the "phi" in the TREE. Let me check GCC 2.7's front end: `c-typeck.c`'s `c_save_expr`/`expand_end_case`... In GCC 2.7, the front end handles a variable assigned in branches via `c_expr` → the assignment becomes a `VAR_DECL` with `TREE_CODE (decl) == VAR_DECL` and the RTL expansion (`expand_end_case`) creates a pseudo with multiple sets. There's no tree PHI in GCC 2.7 (PHI nodes came with the SSA rewrite in 3.0). So the front end can't fold a phi.

**THEREFORE the folding happens at the RTL level.** And the RTL-level pass that removes one of two identical loads in different blocks and hoists the survivor to the join... hmm, that's "PRE" (partial redundancy elimination) — GCC 2.7's jump.c has `jump_combine`? Or **cse.c's `cse_basic_block` + `update_flow`**?

Hmm, GCC 2.7's cse.c DOES do cross-block CSE! It has:
```c
/* Find the smallest common ancestor of the blocks... */
static int
find_common_ancestor (blocks, nblocks)
```
and `cse_basic_block` is called per block, but there's also `record_eqv` which stores equivalences in `reg_equiv` and `reg_equiv_init`/`reg_equiv_exit` at block boundaries. So a value computed in case0 CAN be forwarded into the join (since case0 dominates... no, case0 doesn't dominate the join).

Hmm, the join's preds are case0 and case1. cse processes blocks in some order; if it processes case0 first and records `e ≡ mem[...]`, then in the join it could use that value. But that would be wrong for the case1 path! GCC handles this by invalidating the equivalences at the join (reg_equiv_exit/init at block boundaries).

Hmm.

OK: **LET ME JUST TRY THINGS.** Concrete attempts to keep the load in each arm:

**A1**: Give `e` a pointer type (if unk20 is a pointer).
**A2**: Insert a store between the load and the join in each arm (so the join's use can't be forwarded) — but that adds instructions.
**A3**: Use `e` in the arms (e.g. `argmode = 2 + (e == e)`)? That changes the code.
**A4**: Make the shared block use `e` in a way that requires the arm's value: e.g. the shared block does `t = e->4` — the value flows.
**A5**: **Make the two arms' e assignments use DIFFERENT pointers that alias the same address**: e.g. case0 `e = ((Unkstruct*)s0)->unk20;` and case1 `e = ((Unkstruct*)s1)->unk20;` where s1 = s0 (a copy). The addresses are the same but the trees differ → hmm, tried similar.
**A6**: **Make the shared block's use of `e` a pointer deref that the compiler can't hoist**: e.g. `CAST_WIDTH(s32, e, 4) |= 0x8040;` (v20) — that was tried with s32 v1 (13). Let me try it WITH s16 v1.

**A7**: Change the ORDER: put the `e` load BEFORE the `func_8001C810` call in the arms. Then the load is before the call in each arm → the load can't be sunk past the call? Hmm, and the target has the load AFTER the call. But the final ORDER might be rearranged by sched1... risky but worth a try.

**A8**: Use `e` in each arm for something that dies there (so the load is in the arm). Hmm.

**A9**: Make `e`'s two definitions have DIFFERENT values that are equal at runtime: impossible.

**A10**: **Make the phi not foldable by having `e` assigned in only ONE arm and in the OTHER arm assigned a value derived from a different variable.** Hmm.

**A11 (VERY PROMISING)**: What if we DUPLICATE the shared tail into each arm (the cookbook's "a shared tail written out per site")? Then each arm has its own `e` load and its own use → the load MUST stay in the arm! The code would be duplicated, but cross-jump might re-merge the two tails IF they're identical. They're not identical (argmode 2 vs 3). Hmm, but the tails differ only in the argmode value → GCC's cross-jump compares the blocks; they'd differ → no merge → 2x the code → the count would grow a lot. Not a match.

Hmm, unless the `argmode` difference can be eliminated: what if `argmode` is set BEFORE the branch (in the shared prologue)? No — the target sets a1 = 2 in case0's delay slot and a1 = 3 in case1. So argmode differs per arm.

Hmm, so the shared tail can't be duplicated.

**A12**: What if the `e` load in each arm is kept by making `e`'s phi a "real" phi via the arm values being different TYPES? e.g. case0 `e = (s32)unk20;` and case1 `e = unk20;`. Hmm.

**A13**: What if we make the join's use of `e` require a value that's arm-specific, like `e` being used as the base of a store that must happen in the arm?

Hmm, let me look at the TARGET's shared block:
```
2084: lw v0,4(v1)
2088: move a2,s0
208c: ori v0,v0,0x8040
2090: jal func_8012C658
2094: sw v0,4(v1)
```
So the shared block loads from v1+4, ORs, stores back, and calls.

So the shared block uses `e` (=v1) as a pointer. For the load to be in the arms, the arms must define the same register.

Hmm hold on — what if the trick is to make `e` a POINTER variable? Let's check: is `unk20` a pointer? The source `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` then `CAST_WIDTH(s32, e, 4)` — if unk20 were a pointer, `e` would be a pointer and CAST_WIDTH(s32, e, 4) would be `*(s32*)((u8*)e+4)`. Hmm, but `e` is declared `s32` in the source, so unk20 is probably an s32 (an address stored as an integer). Let me check the struct.

Let me grep for Unkstruct_800B5CB8 and unk20.

Let me do that now — it's quick and could unlock the answer.

Also let me check the CAST_WIDTH macro.

Let me run the greps.
