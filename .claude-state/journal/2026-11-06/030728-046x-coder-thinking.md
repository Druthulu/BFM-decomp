---
ts: 2026-11-06T10:07:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6FJq0MTKdsY0oVYlmwMJ
---
Best keepalive-kept = 6 (MIXED). The register diff v1→v0. No 0. So PARTIAL:keepalive not reachable.

So all three clones → WALL expand-void-return, best 13 (lever-free u16 d), with keepalive-kept best 6.

Wait — but the "best" for a WALL is "lowest score of a lever-free body". The lever-free best is 13 (v05). But is v05's body something I'd keep as win.c? The win.c must score 0 for MATCH/PARTIAL. For WALL, win.c maybe holds the best lever-free body? The brief: "For each item ... write a lever-free body ... that scores 0" and results row best = lowest score. "win.c scores 0" only for MATCH/PARTIAL. For WALL, I should still keep a win.c? DONE WHEN says "each MATCH/PARTIAL has its win.c scoring 0". For WALL, no win.c requirement, but I should keep the best lever-free body as win.c for the record. Let me put v05.c as win.c for the clones (score 13). Actually, the "best" is 13, but that's a weird body (u16 d) that isn't close. Hmm, but it's the lowest.

Hmm, wait. Let me reconsider: is a lower score really "better" if it's semantically wrong? The task defines best = lowest score of a lever-free body. So yes.

But hold on: maybe I should look for a lever-free body that's structurally the same but gets a lower score. The 11-ins deletion gives 15; u16 d gives 13 because it retains more (andi/sltiu) but adds mismatches. Is there a variant that keeps even more and reduces to <13? Let me think: the target has 26 ins; ours 23 with u16 d. The remaining 3 missing are the rv value in the first branch paths. Score 13 = 3 count mismatches + register mismatches? Let me see: with u16 d, score 13, mine 23 target 26. The diff showed replace blocks. Hmm.

Could a `s16 d` variant do better? v20 (s16 d) = 15. u16 = 13. What about `u32 d`? Not tested. Or making `x`/`y` u16 while d s32? v06 (x,y u16) = 31. What about `d` as u16 but `x-a0` cast? Hmm.

The fundamental missing value is rv. Any variant that keeps rv alive is a lever. So the minimum is bounded by the deletion. 13 is the best found.

Actually, let me reconsider: the "best" for WALL is the lowest score, but the *purpose* is to show the residual. Fine.

Now, before finalizing the clones, let me reconsider whether the *definition signature* trick could work within the rules. "no signature or decl change outside the body". Hmm. Actually, re-reading: "no signature or decl change outside the body (callers stay as they are)". Maybe it means: changes are allowed only inside the body; no signature or decl changes outside. So the def line (signature) is outside the body's braces. Forbidden. Confirmed by compile error anyway.

OK. Now item 4 (func_8017D730). Let me do the same: generate ~32 lever-free variants and score. Its wall is likely flow-unused-result (dead second-branch computation) plus register allocation.

Let me design variants for item 4. The body has many real-C move opportunities:
- v0/v1/t/rem/a0 declarations and types
- the second branch: try different spellings of the dead clamp (but any real use would be a launder)
- first branch: v1 type, clamp structure
- the `%` computations
- `(u16)(v1 | 0x1000)` cast placement
- `a0 = 0x406` placement
- combine conditions
- loop? no

The best lever-free b1 = 22 (108 ins vs 119). The missing 11-12 ins are the second branch's dead computation. Let me try variants that keep some of it:
- In the second branch, write `v1 = 0x7F - v0;` and then use v1 in the call in a way that folds to 0? That's a launder. Not allowed for MATCH, but for WALL best? The best lever-free body — a launder would be a lever, so not lever-free. So no.

Hmm, what if the second branch's call actually passes a value derived from v1 that is a *real* argument in the target? The target passes 0. So no.

So the second branch's 12 ins are unreachable lever-free. Best ~22.

But maybe the first branch's allocation can be fixed to reduce score. b1 had a1↔v0/v1 swaps. Let me try variants (types, declaration order) to see if any reduces below 22.

Let me write a generator for item 4. 32 variants.

Variants:
1. b1 baseline (lever-free)
2. v1 as u16
3. v0 as u16
4. t as s16
5. rem as u16
6. compute v0 inline: `v1 = 0x7F - ((((t * 96)) >> 12));`
7. `t = ...; v0 = (t * 96) >> 12;` vs `v0 = ((t * 0x60) >> 12)`
8. reorder clamp checks
9. use `if (v1 < 0x1F) v1 = 0x1F; if (v1 >= 0x80) v1 = 0x7F;` (b1) vs combined
10. move `a0 = 0x406` after clamps (b1 has it between)
11. `a0 = 0x406;` before the clamps
12. second branch without any computation (b1)
13. second branch with t/v0 computed but v1 omitted
14. second branch with v1 computed (dead, will be deleted)
15. use `s32 v0` vs `u16`
16. `(t * 0x60)` vs `(t * 96)`
17. `((a0 - 0x171) << 12) / 81` vs `/ 0x51`
18. `rem = a0 % D_80185CFC;` vs `rem = a0 % (s32)D_80185CFC;`
19. declare rem as s16
20. reuse `t` for rem
21. `if (a0 == 0x5A)` vs `if (a0 - 0x5A == 0)`
22. `D_801F8094 = D_801F8094 + 1;` vs `D_801F8094++;`
23. `if (!func_8018034C())` vs `if (func_8018034C() == 0)`
24. combine the two func_8017FECC calls? no
25. `if (D_80185CF8 < a0)` vs `if (a0 > D_80185CF8)`
26. `v1 = 0x7F - v0` vs `v1 = 127 - v0`
27. `(u16)(v1 | 0x1000)` vs `((u16)v1) | 0x1000`
28. `(t * 96) >> 12` vs `(t * 3) >> 12 << 5`? changes codegen
29. `v0 = t * 96 >> 12;` no parens
30. separate `s32` block scoping for the second branch
31. second branch: `t = ...; v0 = ...;` only (no v1)
32. first branch: clamp via `if (v1 < 0x1F) v1 = 0x1F; else if (v1 >= 0x80) v1 = 0x7F;`

Many. Let me write the generator.

Actually, the second branch is the wall. Any variant that omits v1 will lose 12 ins. The b1 already omits the dead v1 and gets 22. A variant that *includes* v1 (`v1 = 0x7F - v0;`) will have it deleted → same 22. So best ~22 unless register diffs improve.

Let me focus on the first branch's register allocation: b1 mine uses a1 for v1 (a1↔v0/v1 swaps). The target uses v1. Why does mine use a1? Because without the $2 pin, v0 (the var) got allocated elsewhere. Let me try making v0 a different type or reordering so v1 gets $3. Hmm.

Let me just generate and score. Let me write gen_item4.py.
