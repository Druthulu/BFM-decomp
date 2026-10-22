---
ts: 2026-10-22T11:11:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_QhEcMtEnvLfkL71JL3Tq
---
Confirmed:
- Target: 3ad4 lw a0,32(s0); 3ad8 li a1,320; 3adc jal; 3ae0 li a2,240
- Candidate: 3ad4 li a1,320; 3ad8 lw a0,32(s0); 3adc jal; 3ae0 li a2,240

So the load and li a1 are swapped. Both are in the same block.

Now, in the target, the load comes first. The asm is what made it so. The asm is BEFORE the call in the source (between load and call).

Hypothesis: with the asm, the load and the call are in DIFFERENT blocks, and the block ordering forces load first. Without, same block → sched1 reorders.

Now: how do we get a block boundary in plain C?

**Option A**: The load in a block that ends with a jump. Hmm.

**Option B**: Use a construct where the load's result must be computed before a conditional. Hmm.

**Option C**: What if the whole `{ s32 t; t = load; call(t,...); }` is restructured so the call happens in a nested `if`? Adds a branch.

**Option D**: **Use a `goto`**. Let's think about whether GCC removes a `goto` to the next statement. In the C front end, `goto L; ... L: stmt;` — the label is at the next statement, so CFG: block1 ends with goto L, block2 = L: stmt. GCC's `jump` pass (after scheduling) would thread the goto if the target block's first insn has no dependency on the goto's block... Actually `jump_threading` would replace the goto with a jump to the target's first real insn — but the target block IS right after, so the goto would be removed and blocks merged? Actually jump threading removes a `goto` when it can jump directly to a successor, but here the successor IS the next block, so it's not a "jump" to eliminate — GCC would keep the goto as a real jump instruction.

Hmm, actually GCC has `flow` pass (before expand) that removes unreachable code and does "jump to the next block" removal? There's `redirect_label`/`thread_prologue`. Hmm.

Actually, in GCC's CFG cleanup (`cleanup_cfg` in flow.c), a block that ends with a goto to a label that is the next block... `cleanup_cfg` does remove "jump to the next block"? I believe there is such a case: `if (LABEL_ALT_P (label) && ...)` — hmm.

Let's just test empirically! GCC 2.7.2 is right there. Let me test a `goto` variant.

**Option E**: A `switch` statement on a constant? `switch (0) { case 0: ... }` → GCC turns into a jump/branch.

**Option F**: What about making the load's result used in a way that creates a dependency for the li? Like `func_8001D0E8(t, 0x140, 0xF0)` — the 2nd arg 0x140 is a constant.

Hmm, what if we swap the roles: make the LOAD the 3rd argument? No.

**Option G**: What if the load feeds the call but we add an intervening *arithmetic* that GCC optimizes away but which creates a scheduling barrier? E.g. `t = load; t = t;` → GCC removes. `t += 0;` → removed.

Hmm, what about `t = load;` then `if (t == t) call(...)` — GCC removes the condition (t==t is always true) but might leave a branch? GCC would fold `t == t` to 1 (since t is a register, `t == t` → true). Then the if is removed. But does the folding happen before or after scheduling? The front end folds `x == x`? In C, `t == t` with t being a variable — the front end doesn't fold it (it can't, t could be NaN for floats, but for ints it's fine; GCC's fold in front end does handle `x == x`? I don't think so at the front end). Later, in cse or fold, `if (t == t)` → the comparison is on the same reg → cse removes it. That happens before sched1 (cse is before sched). Hmm, so no branch.

But wait — what if the comparison is `t == t` where the two t's are DIFFERENT pseudos but provably equal? Then the branch might survive to the branch-level opt pass which runs after scheduling... Actually `jump`/`cse` run before `sched1`? GCC pass order: ... `expand`, `sched` (sched1), `rebuild`, ... Hmm, let me recall: in GCC 2.7, the passes are: ... combine, expand, jump (jump_opt?), cse, sched1, ... Actually the order in c-passes.c: `pass_expand`, `pass_sra`?, `pass_cse`, `pass_schedule` (sched1), `pass_rebuild`, `pass_combiner` (combine), `pass_expand`, `pass_jump` (jump), ...

Hmm. Let me check the actual order for gcc 2.7.2. From c-passes.c in GCC 2.7:
```
NEXT_PASS (pass_fixup_cfg);
NEXT_PASS (pass_local_function);
NEXT_PASS (pass_all_early_optimizations);  /* includes expand, cse1, cse2, jump1, ... */
NEXT_PASS (pass_local_optimization);
NEXT_PASS (pass_all_optimization);  /* expand, sched (sched1), ... */
```
Actually pass_all_optimizations in GCC 2.7: `pass_expand, pass_sched, pass_rebuild, pass_combiner, pass_rtl_*`... and `pass_all_early_optimizations` = `pass_fixup_cfg, pass_local_function, pass_reorder_blocks, pass_split_edge, pass_ce1, pass_ce2, pass_ce3, ...`.

Hmm, in GCC 2.7:
- pass_all_early_optimizations: expand, cse1, cse2, jump1, cse3, jump2? Actually: `NEXT_PASS (pass_expand); NEXT_PASS (pass_sra); NEXT_PASS (pass_cse); ...`

I recall GCC 2.7 order: expand → sra → cse1 → cse2 → jump1 → cse3 → jump2 (all early) → ... → local opt → global opt (sched1, combine, etc.) → flow → jump3 → cse4 → ...

So jump2 (jump threading/optimization) runs BEFORE sched1. That means a `goto` might be threaded away before scheduling.

Hmm, but a `goto` to the immediately-following block: jump2's `jump_thread_block` won't remove it (there's no branch to thread). `jump_optimize` might merge.

Let me just test empirically. That's much faster than theorizing.

Let me set up a quick test harness: a script that takes a body file and prints the score, and I can create variants.

Let me first write a helper to create variants by editing the body text with Python.

Plan for item 2 experiments (30+ tries):
1. goto label before the call.
2. goto with the label after (forward goto).
3. do-while(0) around the call.
4. do-while(0) around the load+call.
5. Nested block scopes.
6. `if (t == t) { call }` — hmm.
7. Load with different address spellings.
8. Load assigned to a variable of different type (u32 vs s32) — affects nothing?
9. Passing t as an expression: `func_8001D0E8(((Unkstruct_80126B58 *)p)->unk20, 0x140, 0xF0)` — inline the load directly into the call! Then there's no separate variable. Might change scheduling (the load becomes part of the call's operand setup → group).
10. `func_8001D0E8(*(s32*)((u8*)p+0x20), 0x140, 0xF0)`.
11. Reorder args in C but keep semantics — no.
12. Use `s32 t = ...; func_8001D0E8(t, 0x140, 0xF0);` (init at decl).
13. Put the load at the top of the enclosing block and use it later.

Hmm, wait. Let me reconsider option 9: if the load is inlined into the call's argument, GCC creates the call's a0 = load. In the target, the load IS at 3ad4, before li a1. Hmm.

Actually, hold on! Let me reconsider the target more carefully. Is the difference really about blocks? Let me look at where the asm would be. The asm is between the load and the call. With the asm present:

Block structure:
- B1: [ ... store sh v0,14(s0) ] (end of if-body)
- B2 (join): [ lw a0,32(s0) ] then asm → B3
- B3: [ li a1,320; jal; li a2,240 ]

Hmm, but the asm is a barrier; GCC splits the block at the asm. So B2 = [load], B3 = [call group]. The load's block is separate → it stays first.

Without the asm: B2 = [load, call group]. sched1 reorders → [li a1, load, jal, li a2].

Hmm interesting: why would sched1 put li a1 BEFORE the load? Because li a1 is a "birth" instruction with high priority (constant). And the load is a normal instruction. But the load must precede the jal (dependency), and the jal group...

In the target, the group is [li a1, jal, li a2] and the load is in a preceding block, so it must be first.

So yes: I need a block boundary.

**Key question: what plain-C construct creates a block boundary that GCC keeps?**

Hmm — here's one: the `if` statement itself! The load is currently in the join block after the if. What if I restructure so the load is at the END of the if-body block? Then... no, the load must execute in BOTH paths (the `beqz` path jumps to 3ad4).

Hmm wait, actually look at the target flow again:

```
39dc: andi v0,v0,0xff
39e0: beqz v0,3ad4      ; if zero -> join (3ad4)
39e4: li a1,832  (delay)
... body ...
3ad0: sh v0,14(s0)
3ad4: lw a0,32(s0)      ; join
```
So the join block's first insn is at 3ad4. It serves both paths. Good.

So the join block = [lw, li a1, jal, li a2]. It's the block after the if.

Now — here's an idea: **what if the join block ends with something and the call is in a nested block?** Blocks in GCC are created by control flow. The join block after an `if` is one block.

**Another idea**: what if we restructure the `if` so that the join point is different? E.g., make the call part of a `do {} while(0)` inside the join. do-while(0) is removed by the front end (in `c_do`? no). Actually GCC removes `do{...}while(0)` in the `gimplify`/`cgraph`? In GCC 2.7 (C front end), `do stmt while (0)` is NOT specially removed at the front end! The removal happens in the optimizer's `pass_flow`/`jump` or in `tree-ssa`? In GCC 2.7, `do{...}while(0)` becomes a LOOP in the CFG (loop struct in the front end: `c_do` in c-typeck.c creates a LOOP_EXPR? No, in GCC 2.7 the front end has `do_stmt` creating a `LOOP_EXPR`? Hmm, actually GCC 2.7's C front end had `c_do` → `build_loop`? Let me think.

GCC 2.7 tree representation: statements are tree chains; `c_do` in c-typeck.c calls `build_loop` which creates a `LOOP_EXPR`? Actually GCC 2.7 did NOT have loop expressions; it had `WHILE_LOOP`/`DO_LOOP` tree codes added in GCC 2.7? The `WHILE_LOOP` and `DO_LOOP` tree codes were added in GCC 2.6/2.7 era for the "loop optimizer". Yes, GCC 2.7 had WHILE_LOOP/DO_LOOP tree codes.

And GCC's flow pass converts them into CFG loops. `do {...} while(0)` → a loop with 0 iterations after loop optimization. But GCC has a special case: `while (0)` loops are removed in the front end? There's `c_do` → if the condition is a constant 0, GCC's `fold` might remove it.

The notes said the do-while(0) wrapper gave the same score 2. So do-while(0) doesn't create a persistent block boundary.

OK so let me think about **other ways to get the load first**.

Alternative: make the load a HIGHER-priority instruction than li a1,320 so sched1 puts it first even in the same block.

How? sched1's priority = "birth" priority based on dependencies. The load depends on s0 (a pseudo). If the load had a dependency chain that made it earlier... Hmm, in GCC's sched1, `rank_for_schedule` computes priority = number of insns that must precede it in the block (its "dependency order"), plus boosts.

The `li a1,320` has NO dependencies → priority 0 → it should be scheduled FIRST (highest priority = first). The load depends on s0 → priority ≥1. So the li goes first. That matches the candidate.

In the target (with asm), the load is in a separate block → block order dominates.

Hmm, so how does the load get to be first in the target? Because the load is in B2 and the group in B3, and blocks are laid out in order.

**So the crux: create a block boundary.** Plain C options that create CFG blocks in GCC 2.7's front end:
1. `if`/`else`
2. `while`/`for`/`do`
3. `switch`
4. `goto`/labels
5. `break`/`continue`/`return`
6. `&&`/`||` (short-circuit) — creates blocks!

**`&&` / `||`!** The task brief mentions "`&&`/`||` folds" as a legal move. A short-circuit operator creates a CFG block in the front end!

So: `func_8001D0E8(t, 0x140, 0xF0)` could be written as something with `||` that folds away... but a folded `||` would be removed before scheduling. Hmm. But if the condition is a RUNTIME condition that GCC can't fold, we'd get a branch.

Hmm, but the constraint says "&&/|| folds" is a legal C0505 move — meaning the resulting code should be the same as the folded version. If `||` folds at the front end, the block is gone.

Hmm. But wait — maybe not! GCC's front end builds the short-circuit expression as nested statements (COND_EXPR). The CFG for `a || b` has a block. If `a` is a constant true, the front end folds it (in c-fold / the front end's `fold` in build_binary_op). Actually the front end's `fold` handles `truth && 0` etc. But for `x || 1` where x is a variable, the front end can't fold (x might be... no, `x || 1` is always 1, but the front end doesn't know that x has no side effects).

Hmm — what if the left operand is a constant? `1 || x` — the front end folds `1 || x` → 1, removing the block.

What we want: a construct that creates a block boundary in the CFG (so sched1 sees two blocks) but produces NO extra instructions.

Idea: `if (cond) { ... }` where cond is a runtime condition that's always true but GCC can't prove... no, that adds a branch.

**Idea**: the `&&`/`||` where the left side has side effects and the right side is the load:
```c
t = 1 && ((Unkstruct_80126B58 *)p)->unk20;
```
Hmm, `1 && x` → the front end folds to `x` (since 1 is truthy, the right side is evaluated) — GCC's fold: `build_binary_op` for `&&` with a constant left operand: in c-typeck, `truth && x` → x. That happens at the front end (in `c_binary_op` → `build_binary_op` → `fold`). Actually GCC 2.7's `fold` in fold-const.c handles `&&`/`||` with one constant operand: `case TRUTH_AND_EXPR: if (integer_zerop (TREE_OPERAND (t, 0))) ...`. Hmm, `TREE_OPERAND(t,0)` is `truth_is_true` (1) → `fold` returns `TREE_OPERAND (t, 1)`. Yes! So `1 && x` folds to x at the front end → no block.

What about `x && 1` where x is a variable? fold can't fold (x might be 0 → result 0). But the RESULT is `x && 1` = `x != 0`. GCC's later optimization would fold it, but the front end creates a CFG block! Then the block would be removed by the flow/if conversion... but is that before or after sched1?

In GCC 2.7, `flow` (the CFG pass) runs as part of pass_all_early_optimizations? Let's check: GCC 2.7's pass_all_early_optimizations:
```
NEXT_PASS (pass_fixup_cfg);
NEXT_PASS (pass_local_function);
NEXT_PASS (pass_reorder_blocks);  /* maybe */
NEXT_PASS (pass_split_edge);
NEXT_PASS (pass_ce1); ...
```
Hmm, I really should check. Let me find the gcc source... not available probably.

Let me instead do an EMPIRICAL test: write a small C file, compile with the project's gcc-2.7.2-psx cc1 and dump passes, to see the block structure and where things get scheduled. That's exactly what cc1_dumps_tu.sh is for.

OK, given the complexity, let me set up the dump workflow for item 2 to understand. Actually, maybe simpler: let me just TRY a bunch of variants and see which ones change the score. That's faster than analysis.

Let me create a variants directory and a scoring script.

Let me set up:
- .run/P40/T11/RM2x/func_8017E780.../w/ for candidates
- Use sc.sh to score multiple at once.

Let me write a Python generator that produces variants from a template.

First, let me get the baseline template. The body file passed to --try with --body is the function definition alone (spliced into the TU). So my candidate files contain just the function definition.

Let me create variants for item 2. The relevant region:

```c
        {
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            __asm__ __volatile__("" : "=r"(t) : "0"(t));  // !FAKE: launder
            func_8001D0E8(t, 0x140, 0xF0);
        }
```

Variants:
V1: remove asm only (known: 2)
V2: `s32 t = ((Unkstruct_80126B58 *)p)->unk20;` then call (init at decl)
V3: inline the load into the call: `func_8001D0E8(((Unkstruct_80126B58 *)p)->unk20, 0x140, 0xF0);`
V4: goto:
```c
        {
            s32 t;
            t = ((Unkstruct_80126B58 *)p)->unk20;
            goto L1;
        L1:  func_8001D0E8(t, 0x140, 0xF0);
        }
```
Hmm, but `t` scope — declare t at function scope.

V5: `if (t == t) { func_8001D0E8(t, 0x140, 0xF0); }` — hmm t==t.
V6: `do { func_8001D0E8(t, 0x140, 0xF0); } while (0);`
V7: `while (t) { func_8001D0E8(t, 0x140, 0xF0); break; }` — changes semantics (loop).
V8: reorder: move the `{...}` block's content before the `if` block? No.
V9: Make the load happen at the END of the enclosing block and the call after.

Hmm, let me think about V5 more: `if (t == t)`. In GCC, `t == t` where both are the same SSA name → folded to 1 at the front end? In GCC 2.7, the front end's fold doesn't know t == t for a variable (it does for `x == x`? there's `fold` handling COMPARISON with identical operands? I don't think GCC 2.7 folds x==x at the front end). Later, in the SSA-based opt (cse), `t == t` → true. GCC 2.7's early opt included `pass_cse` (cse1) operating on RTL. But the CFG structure (the branch) is created by the front end and `flow` runs before.

So `if (t == t) { call }` would create a CFG with a branch; cse1 (early) might remove the comparison but the branch would be removed by the `jump`/`flow` pass which might run before sched1.

If the branch is removed before sched1, no block boundary remains. If after, we get a block boundary but also a branch instruction (extra).

Hmm.

**Alternative idea — much better**: use `&&`/`||` with the LOAD on the right and a *side-effect-free but non-constant* left operand... no.

**Alternative: use the `?:` conditional operator.** `t ? call(...) : call(...)`? Adds a branch.

**Alternative: think about the OTHER direction.** Instead of moving the load earlier, move the `li a1,320` LATER. In the target, `li a1,320` is at 3ad8, right before the jal. In the candidate it's at 3ad4. Both are "before the jal". The load must be before li a1.

Since both are in the same block and sched1 sorts by priority, maybe we can make the load's priority HIGHER than li a1's. Priority in sched1 is based on the number of predecessors in the block + birth. A load from s0 has 1 predecessor (the li? no). Hmm.

Actually, GCC's sched1 priority: `rank_for_schedule` gives `priority = 1` for most, but instructions that "can be issued early" (birth) get more. Actually GCC's sched1 uses "dependency order" computed via `compute_dep_list` — the priority of an insn = the number of insns in the block that must precede it (transitively). So the load has priority = (insns that depend on it) ... no, it's the count of predecessors.

li a1,320: 0 predecessors → priority 0? Then it'd be scheduled FIRST. Hmm, in GCC's sched1, `priority` = the "birth" (number of predecessors). Instructions with birth 0 (ready) get scheduled first. But GCC's sched1 has a special rule: within the same "birth", the order is by LUID.

The li has birth 0 (nothing depends on it in the block). The load has birth 0 too (s0 is available before the block). Hmm, so both birth 0 → tie broken by LUID (the order they appear in RTL). In the RTL, which comes first? The source order: `t = load;` then `call(t, 0x140, 0xF0)` → the load is emitted first, the li second. So LUID order: load < li. Then the load should be scheduled first!

But the candidate has li FIRST. So something else: the delay-slot filling pass (delayed.c) runs AFTER sched1 and may swap instructions to fill delay slots!

YES — that's likely it. The `delay_slot_filling` pass (delayed.c) runs after scheduling and picks instructions for delay slots, potentially moving the li a1,320 into the delay slot of the `sh v0,14(s0)`.

Wait, but `sh v0,14(s0)` is not a branch. On MIPS, non-branch instructions also have delay slots! And delayed.c's `mips_fill_delay_slot` handles both. It picks an instruction from the same block with the highest priority.

In the target, the delay slot of `sh v0,14(s0)` holds the `lw a0,32(s0)`. In the candidate it holds `li a1,320`.

Hmm! But wait: in the target, the lw is at the JOIN block, which is a different block than the sh. Delayed.c's delay-slot filling can take an instruction from the NEXT block? There's `delay_slot_filling` with `INSN_DELAYED`... GCC's delayed.c `fill_simple_delay_slot` picks from the same block only.

Hmm, but the `sh v0,14(s0)` is the last instruction of the if-body block; the join block starts at 3ad4 with the lw. The sh's delay slot at 3ad4 must be filled from the if-body block (the same block) — but the if-body block ends at the sh. Hmm, so what fills the sh's delay slot? The `lw a0,32(s0)` from the JOIN block!

Interesting: so the sh is the last instruction of the fall-through path, and the join block's first instruction (lw) is placed in the sh's delay slot. That's normal block layout: the delay slot of the last insn of a block is filled with the first insn of the successor block if there's no branch. That's standard MIPS layout, not a special pass.

So: the if-body block ends with `sh v0,14(s0)`, and the successor (join) block's first instruction goes into the delay slot. The join block's first instruction is chosen by sched1 (which schedules within the join block).

So back to sched1: within the join block [load, li a1, jal, li a2], sched1 chose [li a1, load, jal, li a2].

Hmm, but wait: in the target, the join block (after the asm split) is [load] and then [li a1, jal, li a2]. Two blocks. So the load is in the first.

OK so the question remains how to split. And I showed sched1 within a block prefers li a1 first (birth 0 + LUID... but LUID should favor the load).

Hmm, unless the load has a HIGHER LUID. Because the call's operand setup is generated during expansion, and the "li a1,320" is part of the call insn's operand setup (generated at expand time, before the load? No — the load is generated first from the assignment).

Hmm, GCC's expand: the call `func_8001D0E8(t, 0x140, 0xF0)` is expanded into `jal` + arg setup insns. The arg setup for a1 = 320 is `li a1,320`. These are emitted right after the call insn. The `t = load` was expanded earlier. So LUID: load < li.

But wait — GCC's MIPS expand for a call: the `jal` is expanded, and the argument setup instructions are inserted BEFORE the jal. The order of the args: a0 = t (needs a copy? no, the load result is already in a reg — actually the load was assigned to a pseudo and the call needs it in a0, so a copy `move a0, reg` might be inserted, or the pseudo is allocated to a0).

Hmm! Here's a thing: `t` is a pseudo. The call needs a0 = t. GCC's expand will emit `move a0, t_reg`? No — GCC's RTL for the call has the operand as a REG, and the register allocator assigns t to a0 if possible, OR expand emits a copy. In the target, there's no separate move — the load result IS in a0 (`lw a0,32(s0)`). So the pseudo t was allocated to a0.

OK whatever. Let me just try things empirically. Time to write a script.

Let me create the variants and score them. I'll write a Python script to generate variants from a template string, then use sc.sh.

Let me define the item-2 template as the region text and generate variants.

Actually, simpler: I'll write each variant as a full body file using a Python script with string replacement on the orig body.

Let me write the generator.
