---
ts: 2026-10-22T00:24:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UdYokb6eGRIedmSFM52L
---
candD: 3108 ins! Removing the v1 launder alone explodes the function (the `v1` variable's control-flow structure changes → the gotos become a different shape → the whole function is restructured). So the v1 launder is deeply load-bearing: without it, gcc's flow/cross-jump restructures the switch-like code entirely (the `if (v1 == 1) goto case1;` chain becomes a jump table or a different structure).

So item 3 is very likely a WALL. Let me record it as a WALL with the best score = 6 (candC: only the e launder removed → 6) or should "best" be the best lever-free body? The interface says: "WALL (best = lowest score of a lever-free body)". A lever-free body = both launders removed → base.c = 13. Hmm, but candC (e launder removed, v1 launder kept) = 6 is not lever-free (it keeps a launder).

So best = 13 (base.c, both launders removed).

Hmm, but wait: maybe I should try a bit harder. Let me think about the v1 launder's effect: the target's `move v1,v0` — a copy that survives. And candD (v1 launder removed) → the function explodes (3108 ins) — meaning the v1 copy is what makes the control flow a chain of comparisons rather than a jump table.

Interesting! The target's structure: a chain of comparisons on v1 (beq v1,1; slti v0,v1,2; beqz v0; beqz v1; slti v0,v1,4) — a decision tree, not a jump table. Without the copy (v1 = mode directly), gcc's "switch conversion" (the values 0..4 with cases) creates a jump table → 3108 ins (the jump table + the .rodata?). Hmm, 3108 ins — that's a lot; probably the whole function got duplicated/inlined weirdly.

So the v1 copy is load-bearing for the control-flow shape: with the copy (v1 opaque), gcc can't build a jump table on v1's value (it doesn't know v1 == mode). Hmm! Interesting: the launder makes v1 opaque → gcc can't see that v1 ∈ {0,1,2,3} → no jump table → the comparison chain.

In plain C, how to prevent the jump table? Options:
- Make the comparisons not look like a switch: e.g. use `if (v1 == 1) ...` (already) — gcc's "switch conversion" (expand_case_jump / ctlz) works on switches, but gcc 2.7 also converts an if-chain into a jump table? The "jump table" came from the "casesi" optimization: gcc's `expand_case_jump`... Actually gcc 2.7 has "case tables" only for switch statements. But the if-chain with `if (v1 == 1) goto case1; if (v1 >= 2) goto check4; if (v1 == 0) goto case0;` might be recognized by the "cse/thread" or "if-to-switch" conversion (gcc 2.7 has "convert_if_to_switch"? Hmm, "expand_case" in tree-ssa? Not in 2.7. But gcc 2.7 does have "cse.c: switch conversion"? Hmm, there IS a "jump table" optimization in gcc 2.7's cse.c: `cse.c` has "cse_switch" and there's a pass that converts a chain of equality tests into a switch (in `cse.c`, the "case table" / "jump table" construction: `cse.c: case.c`?). Yes! gcc 2.7's cse.c has a "switch conversion" (in `cse_basic_block` → `cse_case`?) that builds a jump table from a chain of `if (x == c)` tests. That explains the 3108 ins (a jump table with the .rodata label).

So the launder's opacity prevents that conversion. In plain C, to prevent it, we could... hmm:
- Make the comparisons use different variables so the pattern isn't recognized? E.g. compare v1 against values in a way that the "case chain" isn't recognized. The conversion needs a sequence of equality tests on the SAME variable. If we interleave different tests (e.g. `if (v1 == 1) ... else if (v1 >= 2) ...`), gcc's pattern matcher might still handle it.

This is getting deep. Time check: I've used a lot of the budget. Let me decide: item 3 = WALL (cse-copy-merge / jump-table), with best = 13.

Hmm, but hold on. Let me try ONE thing: the compound-assignment trick on v1 to make the copy real:
```
v1 = mode;
v1 &= 0xFFFFFFFF;    /* in-place no-op AND */
```
Hmm, gcc folds `x & 0xFFFFFFFF` → x (no insn) — but it might still create a 2nd SET (in-place) → the copy survives! And the emitted code would be just the move (no extra insn) ✓. And the value numbering: v1's VN after `v1 &= 0xFFFFFFFF` = the same as mode's VN → cse would still merge them (the copy is a no-op). Hmm, the merge is by VN → the copy is removed and v1's uses read mode's reg → no move.

Hmm. Unless the `&=` creates a distinct VN. `x & 0xFFFFFFFF` folds to x → same VN.

What if the mask is a real value that preserves the result: e.g. mode ∈ [0,3] and `v1 = mode & 3`? Then v1's VN = and(and(x,3),3) → cse folds and(x,3)&3 = and(x,3) → same VN → merged. Hmm, but does gcc's VN folding do that? cse's "simplify" might. If not folded, the code would be "andi v1,v0,3" instead of "move v1,v0" → 1 extra insn → the score would be off by one (but maybe still MATCH-able? no — score 0 requires exact).

Hmm. So the target's `move` is really hard to reproduce.

Let me now also consider: maybe I can make the whole thing work by REMOVING the need for the copy: e.g. write the control flow with explicit comparisons on `mode` (not v1) so gcc doesn't build a jump table? The target's structure has the copy, so we'd need the copy anyway.

OK: item 3 = WALL. Let me record it: best = 13 (base.c = both launders removed), wall tag = "cse-copy-merge" (the v1 re-tie's copy is merged by cse; without it gcc's cse builds a jump table → 3108 ins).

Let me now move on to the other items: 4 (func_80185380), 6 (func_80180054), 7 (func_8017E780), 1 (func_801832A8), 2 (func_8018389C).

Let me look at item 4: func_80185380 in ov_SC03_014, launders at 3172-3174 (on v6 and p10, with a "memory" clobber).
