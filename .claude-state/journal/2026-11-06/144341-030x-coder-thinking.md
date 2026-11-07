---
ts: 2026-11-06T21:43:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y5WD5Y646nG1ufhEbsDX
---
Score 5, 55 ins (target 56). The do-while didn't stop cse copy propagation.

Need another approach for the anti-coalescing copy. Ideas:

A. s16 temp: `{ short t2 = (short)iVar2; iv2c = t2; }` — HImode copy escapes cse (per func_80182ED4). But will it emit extra sll/sra? Let's test.

B. Use a different type for iv2c, e.g. `unsigned short iv2c;`? Then `iv2c = iVar2` is a narrowing copy; compare `iv2c != one` etc. Might produce andi/sll.

C. Reuse: make iv2c's value come from a different expression that isn't equivalent: e.g. `iv2c = t + 1;` computed separately instead of iVar2? That would duplicate the computation — the target has the move.

D. Volatile? Not allowed? volatile on a local... that's a launder-ish? Not in the listed kinds; but "no new lever of any kind" — volatile is a codegen lever. Avoid.

E. do-while around something else to stop cse: the issue is cse's copy table within an EBB. Actually `do { iv2c = iVar2; } while (0);` splits the block: the copy is in a block of its own; the use is in the next. But the score 5 shows a0 used directly — maybe cse still propagated because the do-while got merged into the same basic block? GCC 2.7.2's jump optimization might merge the blocks back (jump2? no, before cse there's jump1 which can merge blocks that fall through). Yes — `jump_optimize` runs before cse and merges a block whose only predecessor falls through. So the do-while split is undone by jump1. In C0535 cases it worked because of loop structure or the block wasn't merged? Hmm, it said do{}while(0) splits cse1 EBB. Maybe jump1 doesn't merge when there's a barrier note... Actually jump1 merges "jump to next instruction" only if the jump is the only insn? Not sure.

Let me test the HImode copy idea first — it's the proven move (func_80182ED4, func_80182A24? no that's andi).

Test w2: `iv2c = (short)iVar2;` (simple cast). In GCC 2.7.2, assigning int from (short)int does a sign extend: `sll a0,16; sra v1,a0,16` if not provable. iVar2 comes from t+1 where t is s16-ish... combine may prove range. Let's test and look.

Also w3: two-step with a short temp declared in the block.

Let me create several candidates at once and score them with sc.sh? sc.sh takes item dir, tu/fn — for header items tu = header path, and delever_search --try <TU> <fn> <file> — that's the same as tryinc with k=0 rotation? tryinc just rotates includer order. For scoring many candidates, sc.sh works (it doesn't rotate but still compiles against an includer). Score is per-includer; for a header, score on includer 0 is representative initially.

Let me make w2, w3, w4:
- w2: `iv2c = (short)iVar2;`
- w3: `{ short t2; t2 = (short)iVar2; iv2c = t2; }`
- w4: `iv2c = iVar2 + 0;`? That's an identity launder — not allowed.

Alternative real-C: change iv2c's type to s16 and compare with `one`? The target's move v1,a0 suggests a full 32-bit move.

Another approach: make iVar2's own live range end at the copy by recomputing iVar2 later. E.g., instead of `iv2c = iVar2` and later `r = (iVar2<<3)|c6b`, compute r from a fresh expression... but the target uses the same register.

Hmm. Think about what actually creates the move in the target. In the target: iVar2 in a0 (from the else arm: t+1 computed in a0). Then `move v1,a0` copies to v1 for iv2c; then beq v1,one? Actually diff showed target `beq v1,v0` (v1 vs v0=one). And mine `beq a0,v0`.

For the copy to survive: iv2c must not be coalesced with iVar2. Local-alloc coalesces only if the source dies. iVar2 is used later (`iVar2 << 3`), so it doesn't die... but cse's copy propagation doesn't care about death — it substitutes uses of iv2c with iVar2 anywhere dominated. So the fix must stop cse from seeing the equivalence, i.e., make the RTL not a simple reg-reg copy in the same EBB as the use.

The proven HImode trick: `tmp = (s16)t; u = tmp;` — the (s16) copy is a SIGN_EXTEND rtx, which cse cannot equate with the original. Then u = tmp is a copy... would cse then propagate u = tmp? It could, but tmp is a distinct pseudo that's not equal to t, so the move from tmp to u might be merged by local-alloc (tmp dies at the copy -> coalesce). Hmm, but the observed result in func_80182ED4 was that `or v1,v0` survived — i.e., the copy of the *sign-extended* value survived as `or v1,v0`.

Let me look at func_80182ED4's win.c to see exactly what it did. It's in .run/P40/T11/RM1/. Let me find.
