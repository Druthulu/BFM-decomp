---
ts: 2026-11-06T21:58:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dpLXM4RmaQ8BxyEKnpj5
---
Combine uses LOG_LINKS, which are computed by flow analysis and do NOT cross basic block boundaries (LOG_LINKS only link within a basic block? Actually LOG_LINKS are per-insn def-use links; they can cross blocks? They're built by flow.c's `find_basic_blocks` and `life_analysis`... LOG_LINKS are added in `add_insn`? Hmm, LOG_LINKS come from `flow.c: insn_dead_p`... Actually LOG_LINKS are set in `flow.c` by `propagate_block`? No — LOG_LINKS are built by `local-alloc`'s `update_equiv_regs`? Let me recall: LOG_LINKS is filled in by `flow.c` (in `find_basic_blocks`? no) — it's `flow_analysis` → `propagate_block`... Hmm, LOG_LINKS is built in `flow.c` function `insn_dead_p`? I think it's in `flow.c`: `add_insn`? Not sure.

But the key: try_combine requires the insns to be in the same basic block? can_combine_p doesn't explicitly check basic blocks, but LOG_LINKS only connect insns in the same basic block (they're built by `propagate_block` which works per block). Actually LOG_LINKS are set up in `flow.c`'s `find_basic_blocks`? Let me check: `REG_NOTES (insn) = alloc_EXPR_LIST (REG_...` hmm.

There's a simpler empirical route: try adding a real label between the copy and the compare (via a goto that jump1 keeps) and see if the copy survives. But we need semantics.

WAIT. Actually — here's a thought. What about `if (iv2c != one) uVar5 = 0;` written as a *conditional expression assigned to uVar5*:

```
uVar5 = (iv2c != one) ? 0 : uVar5;
```
This might produce a different RTL where the compare is a SET of a condition... On MIPS without scc, it becomes a branch. Hmm, but the structure would be: compare → branch → li. Could change.

Let me think about `uVar5 &= (iv2c == one);`? That's `slt/sne`... changes code.

OK, let me try yet another idea: **make the copy's destination die at the compare but make combine's substitution invalid because the source (iVar2) is a hard register with a REG_USERVAR... no, iVar2 is a pseudo.

Hmm hold on, look at can_combine_p's check:

```
      if (GET_CODE (src) == REG
	  && ((REGNO (dest) < FIRST_PSEUDO_REGISTER && ! HARD_REGNO_MODE_OK (...))
	      || (REGNO (src) < FIRST_PSEUDO_REGISTER
		  && (! HARD_REGNO_MODE_OK (REGNO (src), GET_MODE (src))
#ifdef SMALL_REGISTER_CLASSES
		      || ! REG_USERVAR_P (src)
#endif
		      ))))
	return 0;
```
If the copy's SOURCE is a hard register and SMALL_REGISTER_CLASSES is defined (MIPS defines it!), and the source is not a user variable, combine refuses. Interesting! But our source is a pseudo at combine time.

Hmm.

What about making the copy's source a hard register that's a user variable — like `one` ($2)! If the copy were `iv2c = one`, combine would be allowed (REG_USERVAR_P true).

Hmm, but the value must be iVar2.

OK, let me consider the possibility that we need to make the *destination* a hard register — i.e., iv2c pinned. That's a new pin: forbidden.

Alright. Let me reconsider the problem: is it possible that the *launder* can be replaced by a different kind of lever-free construct that produces the same code — e.g., making the compare use a **volatile-free memory temp**? No.

Hmm, let me look at the actual target source for this header: maybe the ORIGINAL source (from the game) used a different construct, and the launder was invented because the disassembly demanded it. The notes say: "The launder was anti-coalescing: without it `iv2c = iVar2` folds into iVar2 (no `move v1,a0`)".

Given the difficulty, maybe this is genuinely a WALL: "combine-copy-merge" — combine merges the copy the target keeps. The walls.txt has `combine-copy-merge`: "combine merges a reg copy the target keeps, so the pin stays (G23)".

But the task says: a WALL needs ≥ 20 min and ≥ 30 scored tries on that item. I've done about 8 tries on this item. I need to do more before recording a WALL.

Let me look at what other approaches exist. Let me check the walls list for "launder" walls, e.g. func_8017E590 (launder, greg-ref-count).

Let me think about the *possibility* that the move can come from a different place in the code. The target's move is at the join. What if I restructure the code so the compiler *must* keep a copy for a different reason — e.g., making iv2c a variable that is *set in both arms* but where one arm's value comes from a copy that combine can't fold...

Actually, WAIT. What about the do-while trick applied to make the copy and its use be in *different EBBs for cse*, and rely on **cse not propagating** so that the copy survives to local-alloc, where the copy preference coalesces it away... no, we need it to survive.

Hmm, what about making iVar2 *die* at the copy and iv2c live on, so local-alloc coalesces them (no move), then... no.

Let me try the "second use" diagnostic for real to confirm the combine hypothesis. If confirmed, I'll know a block boundary is needed.

Diagnostic: use iv2c in the `r` line AND keep iVar2 alive artificially by ALSO using it in r (extra or) — just to see if the move appears. Actually simpler: use iv2c in the r line only (iVar2 dies at copy). If the move appears → combine was blocked but coalescing didn't happen (maybe because iv2c is live across the compare and beyond, and iVar2's death at the copy... local-alloc WOULD coalesce). Let's see.

Let me test:
w11: move `int iv2c;` to the function scope (before `p1 = ...`), assign at the join (no asm), and change `r = (uint)(iVar2 << 3) | c6b;` to `r = (uint)(iv2c << 3) | c6b;`.

If the result is 56 ins with the move → great, but registers may differ.

Let me do it.
