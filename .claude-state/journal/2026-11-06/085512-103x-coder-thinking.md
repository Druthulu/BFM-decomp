---
ts: 2026-11-06T15:55:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_x2zPnoKmzudgr5zEyIoA
---
Same 39. The #line doesn't matter without the asm.

Item 4 started around 08:47? I extracted orig at ~08:47. So ~8 min. Budget 20-30 min. Let me continue.

For the 2-output launders, the target needs two copies of the `if (n<4)` block (no cross-jump) and n/otz re-tied. The cross-jump merge in mine is because the two blocks are identical. To make them non-identical at zero cost, we could use the `#line` trick: cross_jump's rtx_equal_p for ASM_OPERANDS compares file+line. Without the asm, the blocks are identical. So we need something in each block that differs but costs 0 bytes.

Idea: use `do{}while(0)` around the *first* tail's block only? That would make it non-identical (different notes?) — but notes aren't compared; the insns would still be identical. Hmm, a do-while splits the EBB but the insns are the same.

Idea: make the two blocks differ by a zero-byte insn difference, e.g. use a different variable for the q temp in one tail (both pins? q is pinned $2; qt pinned $5). The blocks use q and qt. If in one tail we use a different spelling that produces the same code... e.g. in the LINE tail, use `q2` (another variable pinned to $2)? But that adds a pin (new lever of kind pin — not allowed? pins are a lever kind; adding one is "no new lever of any kind" → not allowed).

Hmm. What about the `#line` trick with a *dummy* zero-byte asm? Not allowed (asm is a lever).

Hmm, so the 2-output launders may also be a wall.

But wait — maybe the *real C* difference is that the two tails should NOT be identical because the source wrote them differently (different variable names/spellings), and the compiler's cross-jump doesn't merge them. But cross_jump works on RTL, so different C spellings that produce identical RTL still merge.

The target has them separate, so the original compiler didn't merge them. Why? Because the asm insns (with outputs) were present in the original source! The original source likely had inline asm or the compiler produced non-identical code due to register differences.

Hmm, actually, maybe the original code had a *different* structure: e.g., the two tails differ in the `q = func_80010A08(8)` call — in the POLY tail, q is used after with the tpage chain; in the LINE tail, same. If the register allocation differs slightly (q in a different reg), the blocks differ and cross-jump won't merge. The launders force n/otz to be unknown, changing the register allocation between the tails.

Given the difficulty, this item may be a WALL. But let me check: maybe I can crack the *arg* launder differently — the score-4 residual is just the la position. If I can't, and the 2-output ones are also hard, the item is a WALL with best 43.

Hold on. Let me reconsider the 2-output launders: what if we remove them but add a *real second set* of n and otz that's zero-cost? A second set that flow deletes but that cse sees? Hmm.

Actually, what about `n = n;`? Identity — disallowed. `otz = otz;` identity.

What about `n = w >> 8;` — we tested (e2: 350 ins, score 54). The extra 2 insns come from recomputing the shift. What if n's recomputation reuses an existing register... no, it's an extra srl.

Hmm.

What about reordering so the tail block is naturally non-identical? E.g., in the LINE tail, swap two statements (the color loads) so the RTL differs? But the target's tails are identical (the diff showed target has identical `slti v0,s0,4; beqz` twice). So the blocks ARE identical in the target, yet not merged. That means the compiler had a barrier. The asm was that barrier.

So without an asm, jump.c will merge. Plain C can't prevent cross-jump of identical blocks... unless the blocks' *addresses/relocations* differ? No.

Wait — cross_jump only merges blocks whose labels/branches allow. Maybe the merge in mine happens because the *tests* are unified by cse (the n<4 test computed once), not cross-jump. The diff showed mine: `slti a2,s4,4; beqz a2,18b8` and target: `slti v0,s0,4; beqz v0,18c0` twice. So mine has ONE test and target has TWO. If cse unified the test (because n's value is the same), the second test is gone. That's cse, not cross-jump. The launders make n unknown → each tail computes its own test.

So the fix: make n's value not unifiable across the tails. n = w >> 8 at the top; in the tail, `n < 4`. The two tails are in different branches (POLY vs LINE), and n is set once before the branch. cse (a global pass) sees `n = w >> 8` and knows n in both branches; the `n < 4` test is the same expression → cse may share the comparison? Actually cse doesn't share comparisons across branches unless the values are available. The two tails are in the same function, different blocks. cse's global value numbering could unify the `slti n,4` if n is available... but n's value is in a register; both tails compare the same register. Hmm, why would mine compute it twice vs target twice? Mine computes ONE test and branches to a shared block (cross-jump), target computes TWO.

OK so it IS cross-jump: the two `if (n<4) { ... }` blocks are identical, so jump.c cross-jumps them: the first block jumps to the second's code (shared), eliminating one copy. Target has two copies because the blocks are NOT identical.

Why would the target's blocks not be identical? Because of the asm outputs: in the POLY tail, the asm sets n and otz to unknown; in the LINE tail, same. The asm insns are identical (same #line). Hmm.

Maybe the asm's presence prevents cross_jump from merging because cross_jump doesn't handle asm insns with outputs (it only merges blocks whose insns are "simple"?). Actually jump.c's cross_jump has restrictions: it won't cross-jump blocks containing certain insns. Let me check jump.c:2371 region.

This is deep. Given time, maybe I should accept a WALL for item 4, but first let me see if there's a simpler path: the brief says MATCH = the kinds in <dir>/kinds gone. The kind is "launder" only. The 2-output launders are load-bearing, the arg launder is load-bearing. Best lever-free = 43 (c1). That's a WALL with tag... maybe "jump2-cross-jump" or "combine-argcopy-sink". The walls.txt has tags; let me check for a cross-jump tag.

Let me look at walls.txt.
