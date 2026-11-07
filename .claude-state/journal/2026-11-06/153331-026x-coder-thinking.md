---
ts: 2026-11-06T22:33:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1hImtEBSLo5rXGdVdg7D
---
Both 38 — same as w0, so cse2 merged the duplicate and s1ang stayed local. Let me verify by dumping w1 and checking r75. But likely.

Different approach needed. Let me think about local-alloc ordering.

Actually, wait. Let me reconsider: maybe we can make r75 (s1ang raw) get $s1 by giving it a preference for $s1. Preferences come from `REG_EQUIV`/copies. Hmm.

Or: make r75's qty order such that local-alloc assigns $s1. In local-alloc, the allocation order among block-local pseudos is by qty (refs/live). If there are TWO block-local pseudos needing callee-saved regs, the first gets $s0, second $s1. If we add a *dummy* block-local pseudo that also crosses a call and has higher qty, it takes $s0 — but then d conflicts it. Unless that dummy's live range is entirely in block 0 before... d is live across block 0 (defined insn 6, used insn 57). So it conflicts.

Hmm, unless the dummy is dead before insn 6? d is defined at insn 6 (`move d,a1`). The dummy would have to be live and dead entirely before insn 6. The only code before insn 6 is the prologue (insns 4: move v0,a0). Hmm, could we create a block-local that's live only at the very start? E.g., a computation before `d = arg1`? The target's first instruction is `move $2,$4` (arg0 → v0). If we add something, extra instructions.

Alternatively, make d's definition later? No.

Hmm, what about making d's live range start at the cast (insn 57) rather than entry? The target has `move $16,$5` at entry. If d were assigned at the cast from arg1, the move would be at the cast, changing the instruction order (target has move at entry). Not matching.

OK, so we need s1ang raw off $s0.

What about making s1ang raw NOT cross a call by having it die and be recomputed? The target has `lh $17,18($2)` before the call. What if we load it before the call into a caller-saved reg and then it's used after the call? Impossible — it would be clobbered by the call, so gcc must save it. Unless the call is at a point where s1ang isn't live... The target keeps it live across.

Hmm, what if the load is after the call in source but sched1 moves it before the call? Interesting! sched1 can hoist the `lh` above the call? No, calls are scheduling barriers for memory... Actually sched1 doesn't move insns across calls.

What if the s1ang load is in the same statement as the ratan2 arguments, and gcc orders the load first? The target order: `lh $3,14($2)`, `lh $4,D_80126CB8`, `lh $5,6($2)`, `lw $2,32($2)`, `subu $4,$3,$4`, `lh $3,D_80126CB4`, `lh $17,18($2)`, `jal`, `subu $5,$3,$5`. Note: `lh $17,18($2)` is after the `lh $3,D_80126CB4`, and the `lw $2,32($2)` (the arg0+0x20 pointer load) is early. So s1ang's load is scheduled among the ratan2 arg computation.

So s1ang's load is before the call, necessarily.

Hmm, so how could the target's r75 not be block-local? It is block-local (the pin table shows r75 s1 — local-alloc'd). So in the target it's a local pseudo that took $s1 because $s0 was pinned.

To crack without a pin: we need a real-C reason for $s0 to be unavailable to r75 but available to d... contradiction since local-alloc runs first and d is global.

Wait, unless d is ALSO local-alloc-allocated? d is global (used in many blocks).

Hmm, is there any other mechanism? Local-alloc only considers pseudos whose all refs are in one block. What if we make r75 have refs in two blocks so it becomes global? We tried via cse-merge. But maybe there's a form where the second use is NOT mergeable: e.g., use s1ang in a different expression that cse can't merge, in a later block, but which is dead or folds away.

Actually! Idea: make the second use a *dead* use that combine/flow removes. E.g., `if (0) u6 = s1ang;` — folded away early.

Hmm. What about a use in a branch condition after the return? 

Alternatively: change the block structure so the andi lands in block 2 naturally. What if the compare is `if (u5 == (s1ang & 0xFFF)) return 0;` and then `u6 = s1ang & 0xFFF;` — the first andi is in block 0, second in block 2; cse2 merged (w2 gave 38).

What if we force cse2 not to merge by making the second expression use a different form that's still the same instruction? E.g., `u6 = (s1ang & 0xFFF);` vs `u6 = s1ang & 0xFFF` — same.

What if the second use is in a different order: `iVar4 = (s1ang & 0xFFF); iVar4 = u5 - iVar4;`? Still the same expression.

CSE merges identical expressions. To defeat it while producing the same code, use a different expression that produces the same instruction... e.g., `s1ang & 4095` is the same constant. `(s1ang << 20) >> 20`? That's different instructions.

Hmm, what about making s1ang raw global through a *loop*? No.

Wait, maybe there's another lever: local-alloc's behavior depends on the pseudo's qty. What if s1ang raw is a different mode or has different refs such that local-alloc assigns $s1 instead of $s0? Local-alloc allocation order for block 0: it processes qty in order. If r75 has the highest qty, it picks the first free hard reg. The first free is $s0 unless something else already took it.

What if there's ANOTHER block-local pseudo in block 0 that doesn't conflict with d? Impossible if d is live throughout.

Hmm, unless d's live range doesn't actually span block 0 fully! Let's check: d defined insn 6 (move s0,a1). In the target, d is live from insn 6 to the end. So it spans all.

Wait, what if we change WHEN d is defined so it's not live in block 0 until the cast? The target's `move $16,$5` at entry is required. Hmm, but is it? The target instruction `move $16,$5` exists because d is assigned at entry. If we write `d = arg1` at entry, yes.

Hmm, but what if d's live range as seen by local-alloc... local-alloc only deals with block-local pseudos. d is global so it's not considered. The conflict for d is computed in global-alloc against hard regs occupied by local pseudos.

New idea: what if we make r75's live range NOT cross the call by moving the call to the END? No, order.

New idea: reduce r75's "crosses 1 call" property by making the call not clobber... no.

Let me look at this from the actual GCC source: local-alloc's allocation of a pseudo that crosses a call requires a call-clobbered-free reg. It uses `reg_alloc_order` and qty. Could we influence which reg via the pseudo's *preferences*? In local_alloc, `qty_phys_copy_sugg` and preferences. If s1ang's load result has a copy preference... e.g., if we write `s1ang = *(s16 *)(...); d2 = s1ang;` — copy coalescing.

Hmm, what if we make s1ang the destination of a copy from a variable that's in $s1? No.

Alternative: what if we make d not conflict $s0 by giving d a preference for $s1 and making it not need $s0? No — target requires d=$s0.

Hmm, hold on. Let me reconsider the target's register assignment. Maybe the target's `d` doesn't have to be $s0 in our lever-free body if we can get the same *instructions*. The score compares instruction streams (with register renaming? No — score 0 means identical). The register numbers must match exactly ($16 vs $17).

So d must be $s0.

Let me look at whether there's another way to get d into $s0: make d's pseudo have a hard register through a *copy* from a hard-reg expression. E.g., if d is assigned the result of a call (call returns in $v0), no.

What about making d the result of `arg1` where arg1 is used in a way that prefers $s0? Global-alloc preference: r77 prefers 16 (s0) — why? Because of a copy. Let's understand: r77 = u6 = s1ang & 0xFFF. Why does it prefer $s0? Preferences in global.c come from `reg_preferred_class` / copies (REG_NO_CONFLICT) or from insn operands where the pseudo is used in a context requiring a specific reg? Hmm, "77 preferences: 16". Where would that come from? Possibly from the `andi` where one operand is a constant, so no. Maybe from the divide: the div uses $s0? No, MIPS div uses any reg.

Hmm, maybe from `q = iVar4 / d` — the MIPS div instruction uses LO/HI and any GPR.

Actually, the preference could come from the local-alloc decision: r77 was allocated to $s0? No, r77 is global.

Wait, "preferences" in global-alloc are set by `reg_preferred_class`? Or by copy insns: `setup_preferences`/`set_preference` in global.c. A preference of 16 for r77... In the w0 code, u6 = s1ang & 0xFFF, and r75 (s1ang) was assigned $s0 by local-alloc. The `andi` reads r75 and writes r77; there might be a preference for r77 to be in the same reg as its input (a "copy" preference because the andi can be in-place?). Actually GCC's global.c sets preferences from REG_EQUIV or from insns where an operand is a register that dies (prefer same reg for the output). Yes! `andi r77, r75, 0xfff` with r75 dying → preference for r77 in r75's reg (16). That explains it.

OK so if r75 moves to $s1, r77 would prefer $s1 (r75's reg).

Now the target: r75 in $s1 (local-alloc), r77 prefers $s1 → u6 in $s1. And d in $s0. Consistent.

So the only blocker is local-alloc giving r75 $s0.

Let me look at local-alloc more carefully. In local_alloc, for each basic block, it allocates pseudos that are "local" (all refs in the block) AND not already allocated. It processes them in qty order. qty = `floor(10000 * refs / live_length)`? Let me check: pri in the table: r75 2857 = 2 refs / 7 live → 2*10000/7 = 2857. Yes! pri = 10000*refs/live_insns. And d: 9 refs / 27 live = 3333, but shown 10000... hmm. Actually the global pri caps at 10000 and includes loop depth. d: 9 refs across 27 insns = 3333. But shown 10000. Hmm, maybe pri = floor(1e6 * refs / live) capped? 9/27 = 0.333*30000 = 10000. r75: 2/7*10000 = 2857. Hmm inconsistent scale.

Whatever. The point: local-alloc allocates r75 to $s0 because it's the first free callee-saved.

Can we make another local pseudo take $s0 first? It would need higher qty and be in block 0, crossing a call, and dead before d's live range starts... impossible.

UNLESS: d's live range in global-alloc is computed per basic block and the conflict is only where they overlap. d is live in block 0 from insn 6 onward. A local pseudo in block 0 with a live range entirely before insn 6 (i.e., in the prologue) would not conflict with d. But the prologue has no pseudo.

Alternatively, a local pseudo in a *different block* that takes $s0 doesn't conflict with r75 (different block), and d conflicts it → d gets $s1. Bad.

Hmm, what if we make r75's live range not cross the call *in local-alloc's view* by making the load's value used before the call and the after-call use be a *reload from memory*? That is, reload the field after the call. Then the target's `lh $17,18($2)` would appear twice. Not matching.

OK here's another thought: what if we make the s1ang load result a *global* pseudo by making it live across a block boundary, and defeat cse2 by making the two uses have different values that happen to compute the same instruction. Hmm.

Actually, wait. Let me reconsider the whole thing. Maybe there's a different structure that produces the same target code where s1ang's raw value is naturally global. What if `u6` is computed inside a conditional block?

Look at the target block structure:
- block 0: entry through `bne $17,$4,$L72` / `sra $16,...`
- block 1: the return-0 arm
- block 2: $L72: iVar4 computation and branch arms
...

What if we write the source so that the `andi` for u6 lands in block 2 (after the branch) and the compare uses the raw value differently? E.g.:

```
if (s1ang == u5) return 0;   // wrong semantics
```
No.

What about:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
```
vs
```
if (s1ang == u5) return 0;  // compare raw
```
Not the same.

Hmm.

What if we make s1ang raw global by using it in a *second* block in a way that cse2 cannot merge because the expression involves a different register (e.g., compare against a variable)? Like:

```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (s1ang == 0) iVar4++;   // extra instruction - no
```

Adds instructions.

Hmm, what about the `t` variable in the arms: `t = u6 + 0x1000`. If instead `t = (s1ang & 0xFFF) + 0x1000`, cse2 might merge the andi (u6 dominates). Same.

What if the second use is in a block NOT dominated by the first? E.g., the arms are reached from block 2 which is reached from block 0 via the branch. u6 computed in block 0 dominates. cse2 merges.

What if we compute u6 in one arm and the compare elsewhere? Semantics.

OK, different tack: maybe we can prevent cse2 from merging by making the value's register *modified* in between? No.

Let me step back and consider: is there any other real-C way to reserve $s0? The `pin` lever is a hard-reg variable. What about a *global register variable*? `register s32 d asm("$16")` is exactly the pin. Not allowed.

What about using an argument in $s0? Function args are $a0-$a3, no.

What about the `s1ang` load being HImode and local-alloc treating HImode differently? Let me try `s16 s1ang`. In local-alloc, a HImode pseudo crossing a call — still needs callee-saved. But maybe its qty changes or it gets combined.

Actually! Another idea: what if we make s1ang raw's *load* happen in a way that it's part of a larger expression, e.g., `u6 = (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) & 0xFFF;` — then the load and andi are combined into one pseudo (no separate s1ang raw), and there's no cross-call pseudo! But then the `lh` must happen after the call (since it's part of the andi after the call). The target has `lh` before the call. So the instruction order changes.

Hmm, unless sched1 hoists the lh above the call — it won't.

OK, let me look at the actual target instruction scheduling to see if the lh is genuinely before the call due to source order. In the source, `s1ang = ...` is a separate statement before u5's ratan2 call. So yes.

Let me look at what happens if we reorder the source: compute u5 first, then s1ang. Then the lh would be after the call. Not target.

Hmm.

Let me look at the problem from the "global-alloc priority" angle again but for a different lever: what if we make d's allocation happen via local-alloc? If d were block-local, local-alloc would give it $s0 (if first). But d spans many blocks. Unless we duplicate d into per-block locals? E.g., use `arg1` directly in the div instead of `d`? Then the div would use arg1's pseudo ($a1, clobbered by the call) → gcc would spill/reload.

Hmm, what if we make d a *parameter copy* in each block? No.

Wait, actually — what if the divisor `d` is not live across the call as a pseudo because we write `d = arg1` AFTER the call? The target has `move $16,$5` at entry (before the call). If we move `d = arg1` to after the call (before the cast), the move would be after the call. Different order.

Unless sched1 moves it? `move $16,$5` — a simple reg copy could be scheduled... but $16 is callee-saved and the move from $a1 must happen before $a1 is clobbered. If the move is after the call, $a1 is dead/clobbered. So it must be before. Actually the move could be placed after the call only if arg1 is still live, but the call clobbers $a1.

Hmm, so d=arg1 must happen before the call, meaning d is live across the call regardless. So d is a global pseudo live across the call. But wait — global-alloc: d is global (crosses blocks). It can't be local-alloc'd.

What if d is live across the call but we could make d NOT global by... it's used in blocks 2-11. No.

Hmm, hold on. Let me reconsider: maybe the answer is to make r75 (s1ang raw) global by *declaring* it so that it's referenced in two blocks via the `if` arms, and defeat cse2 not by expression difference but by cse2 being unable to forward across a block that has a call... no, cse2 runs after the call is placed; it does value numbering across blocks but a call clobbers registers, so it won't keep a value in a register across a call? Actually cse2's `cse_basic_block` handles calls: values in registers are invalidated across calls (they're not live in regs unless allocated). Hmm, cse2 does global cse and can keep a value in a pseudo across a call if the pseudo is live. The first andi (u6) is after the call, so no issue.

Wait, actually, maybe cse2 didn't merge w1's duplicate! Let me verify by dumping w1 and checking whether r75 is local or global. The score was 38 same as w0, but the alloc table would tell. Let me dump w1.

Actually, hold on — in w1, the second use `(s1ang & 0xFFF)` is in block 2. If cse2 merged it, the result is identical to w0 (score 38). If it didn't merge, we'd have an extra andi (77 ins vs 75). Since mine = 75 ins, it merged. Confirmed by instruction count.

So cse2 merges. Need to defeat cse2 or find another way.

Idea: make the second use in a block that cse2's value numbering can't reach because the value is killed. The value u6 (r77) is computed after the call in block 0. Block 2 is the branch target of the bne. cse2 processes blocks in order and the andi result is available. 

What if the second use is in block 1 (the return arm)? No.

What if we compute u6 in block 2 instead, and the compare in block 0 uses a *different* computation? E.g.:

```
u5 = ...;
do { d = (s16)d; } while (0);
if ((s1ang & 0xFFF) == u5) return 0;
u6 = s1ang & 0xFFF;
```
That's w2 (merged).

What if:
```
if ((s1ang & 0xFFF) == u5) return 0;
iVar4 = u5 - (s1ang & 0xFFF);
u6 = s1ang & 0xFFF;
```
Still merged.

Hmm. What if the second use is in a *loop* (block 4 has a loop back edge)? cse2 might not propagate into loops easily. The arms `if (iVar4 > 0x800) { t = u6 + 0x1000; ... }` are separate blocks. Let's use s1ang there: `t = (s1ang & 0xFFF) + 0x1000`. The block containing that is not dominated... it is dominated by block 0. cse2 should merge.

Actually, maybe cse2's cross-block merging is limited to the extended basic block? cse2 in gcc 2.7.2 does global cse with a table per basic block, and it can forward values across blocks (it's "global cse"). Let me check the source at tools/reference/gcc-2.7.2/cse.c.

Let me search for how cse2 handles this. But maybe a simpler empirical approach: try the use in the loop block and see the instruction count / alloc table.

Alternatively, defeat cse by making the two andi computations differ in a way that still generates `andi` with the same constant but different insn patterns... e.g., `s1ang & 0xFFF` vs `(u32)s1ang & 0xFFF`. Same.

What about `s1ang % 0x1000`? That's a different instruction (div). No.

Hmm, what about using `(s16)s1ang` vs? s1ang is s32 already sign-extended.

OK here's another idea entirely: make r75 global by using s1ang in a *conditional expression* that gcc evaluates in a later block, e.g.:

```
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (s1ang & 0x800) { ... }  // adds an instruction
```
No.

Let me think about whether there's a way to make local-alloc skip r75. Local-alloc allocates pseudos that need a hard reg. What if s1ang raw is assigned a *call-clobbered* reg because it's not actually live across the call in local-alloc's view? The call is at insn 47; r75 def 20, use 69. It IS live across.

But what if the call is moved after insn 69? No.

Hmm, wait wait. What if we restructure so the s1ang load happens before the call but the *value* is used before the call too, and the after-call value is re-derived from memory in a way the target does? The target has `andi $17,$17,0x0fff` after the call using the register saved across the call. So no.

Let me reconsider: maybe there's a different real-C move that changes local-alloc's choice for r75 from $s0 to $s1 by making another local pseudo take $s0 in block 0 and NOT conflict with d because its live range is before d's def... The prologue: insn 4 `move $2,$4` (v0 = a0). d's def is insn 6. So a pseudo live in insn 4-5 could take $s0 without conflicting d? But d is live from insn 6. A local pseudo born at insn 4 and dead at insn 5 would not conflict. But there's no such pseudo, and adding one adds instructions.

Hmm, what about the save/restore of $s0? The prologue `sw $16,16($sp)` is generated because $16 is used. That's fine.

Let me look at the actual local-alloc algorithm to find a lever. In gcc 2.7.2 local-alloc.c, `local_alloc()`:
- For each block, it computes qty for each pseudo.
- Then `alloc_qty` / `qty_compare`.
- It allocates in order of qty (highest first), using `reg_alloc_order` and checking conflicts with other pseudos in the block, hard regs, calls.

The key function `local_alloc_1` / `block_alloc`: it walks `qty` list. The pseudo gets the first hard reg in `reg_alloc_order` that isn't used by another live pseudo at any point and isn't call-clobbered across a call.

So r75 takes $s0. To make it take $s1, we'd need $s0 to be "used" by another pseudo in block 0 that doesn't conflict with d... 

What if we create a block-local pseudo in block 0 with a live range entirely within the call-clobbered region... no, it would conflict with d if it's live after insn 6.

Actually hold on: what if the other pseudo is live ONLY at insn 4-6, i.e., dead before d's first use? Local-alloc's conflict is based on live ranges at each insn. d is live from insn 6. A pseudo live at insn 4-5 doesn't conflict.

But we can't add instructions.

Hmm, but wait: what about the arg0 copy `move $2,$4`? r72 = arg0 copy? "Register 72 used 4 times across 6 insns in block 0" → assigned $v0. And in the target, `move $2,$4` is at insn 4.

What about r81 (2 refs, 3 insns, pointer) = the arg0+0x20 pointer, gets $v0. 

Hmm.

New angle: maybe we can make r75 NOT be the s1ang raw load, but instead make the s1ang raw value a *global* by putting the load in a block and the use in the same block but the pseudo is considered global because of `REG_USED_ACROSS_CALL`? No.

Wait, actually, let me re-read the lreg dump: "Register 75 used 2 times across 7 insns in block 0; crosses 1 call". Local-alloc treats pseudos with all refs in one block as local. But maybe local-alloc gives up on it if it "needs" a reg that conflicts... it found $s0.

Hmm, what if we make s1ang raw cross a call AND have a *conflicting* local pseudo in block 0 that's live across the call too? Then the second one gets $s1. But both would conflict d → d gets $s2. Bad.

Unless d gets $s0 because the conflicting pseudo's range doesn't overlap d... but d spans.

Hmm, OK. Let me question the premise: does d really conflict with a local pseudo assigned $s0 if that pseudo is live in a *different* block? Global-alloc computes conflicts: for each global pseudo, it conflicts with hard reg R if R is live at any point in the pseudo's live range. d is live from block 0 to block 11. A local pseudo in block 5 assigned $s0 would make d conflict $s0. Yes.

So no local $s0 allowed anywhere in d's range. d's range = whole function. So we need s1ang raw to take $s1.

To make local-alloc give r75 $s1: we need $s0 to be occupied by a local pseudo whose live range doesn't overlap d's... impossible, OR by making r75's qty ordering/reg preference pick $s1.

Wait — preferences! In local-alloc, `qty_phys_copy_sugg` and `qty_phys_num_copy_sugg`... The allocation considers "copy suggestions" and "preferred" registers. If r75 has a preference for $s1, local-alloc tries that first.

Where do local-alloc preferences come from? From `REG_EQUIV` notes and copies: if a pseudo is set from another pseudo that has a hard reg, it prefers that reg. For r75 = load result, no.

Hmm, but there's `qty_preferred`? Actually local-alloc uses `reg_preferred_class` and `qty_phys_reg`?

Let me look at the local-alloc source to see how the hard reg is chosen: `block_alloc` in local-alloc.c.

Actually, maybe simpler: what if s1ang raw is *not* a separate pseudo but the same as u6, and the load is HImode so the andi is combined... Let me think about `s16 s1ang`:
```
s16 s1ang;
s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
u6 = s1ang & 0xFFF;
```
Here s1ang is HImode. The load is `lh` into a HImode pseudo (still a full reg). Then `andi` needs SI, so extendhisi2 (or the andi with a HImode operand sign-extended). In the target, the `lh` loads the full register and `andi` uses it directly — consistent with sign extension being free (MIPS lh sign-extends). So the HImode pseudo would be used directly in the andi. The pseudo's refs: 2, in block 0, crosses the call. Same as before. But maybe HImode pseudos are treated differently by local-alloc qty (they have `n_refs` 2 but maybe the qty calculation differs). Probably not.

Hmm, let me try it anyway; cheap.

Also try: declare `u16 s1ang`? No, target does sign extension (lh).

Another idea: make s1ang raw's live range not cross the call by loading it *after* the call and relying on sched1... no.

OK, let me look at the sibling function func_8012BB3C's cracked approach: "C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0)". In that function the divisor became $s0 after a do-while raised its refs. But here the problem is different (local-alloc r75).

Hmm wait, actually, is it? Let me re-read the W50x note: "div do-while (w5) lifts d's global-alloc pri 5185->12222 and puts r74 ahead of r77 in the .greg order, but r74 conflicts with hard reg $16, so d still lands $s1". So d pri 5185 (before do-while) → r74 was after r77? And the conflict with $16 is r75. Yes.

OK so the wall is lreg-qty-priority (r75 local takes $s0).

Let me now think about making r75 global *without* cse2 merging. What if the second use is in a block that cse2 does NOT process with the value available because of a `setjmp`/call... Hmm, cse2's global cse: it uses `cse_basic_block` for each EBB and merges values across blocks via `reg_eqv`... In gcc 2.7.2, cse2 (`cse_main` with `after_loop`) does global CSE: it maintains a table across basic blocks and invalidates on jumps? Let me check: in cse.c, `cse_basic_block` starts a new table at each label (`new_basic_block`) — actually cse2 is "global" because it processes each EBB and the table persists across blocks that don't have labels? Hmm. GCC's cse does "extended basic block" CSE — the table persists through straight-line code including jumps to the next block? Let me check the source.

Actually, the classic GCC cse pass is global CSE: it keeps a hash table and processes the whole function, flushing at labels where needed. `cse_end_of_basic_block` determines the end of an EBB; the table persists through blocks that are only reachable from the previous block (no other predecessors)? In w1, block 2 ($L72) has the bne as its only predecessor, so it's in the same EBB. So cse merges. If we put the second use in a block with multiple predecessors, cse would start a new table and not merge!

So: make the second use of s1ang in a block with multiple predecessors. Which blocks have multiple preds? The arms after the `if (iVar4 > 0x800)` — $L80 is the merge point of the two if arms. Hmm, the code:
```
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
```
The second `if` is in the merge block. If we use s1ang there, that block has multiple predecessors (the two arms). cse would not forward across a block with multiple preds? Actually cse processes blocks in a linear order and only keeps the table if the block is reachable only from the previous block (i.e., `cse_end_of_basic_block` returns the end of an EBB). Let me check gcc 2.7.2 cse.c.

Let me grep the source.
