---
ts: 2026-10-22T11:42:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_NiieDX98juErZXapEq4N
---
The pre-sched RTL is IDENTICAL between orig and w4 in this region (insn 462-478). So the difference is purely in the SCHEDULER's decision.

Now: in the ORIGINAL, the scheduler moved insn 471 (the constant) to the TOP of the block (before 462). In w4, it left it in place.

**The dependency difference**: In the original, the vol pseudo (196) is set by the ASM (which is after insn 476). Hmm, let me look further: in the original, after insn 476 (the division result 196), the asm sets 196 again.

Let me look at the original's RTL after 38630 vs w4's.

Original (from the earlier read):
```
38630: (insn 476 ... set 196 = 207 - 208)   [division result]
```
then presumably the asm: `(insn 478: set 196 = asm_operands ...)`.

Let me read the original at 38630-38680 and the candidate at 38630-38680 to compare.

Actually, the KEY question: what makes the scheduler hoist insn 471?

**HYPOTHESIS**: In the original, pseudo 206 (the constant) has TWO uses: insn 472 (the vol mult) and the sx mult. In the candidate, maybe pseudo 206 has only ONE use and the sx division uses a DIFFERENT pseudo (e.g. 210) set to the same constant.

Why would that differ? Because of CSE! CSE (cse.c) merges two pseudos set to the same constant into one — but only if CSE runs BEFORE sched. CSE runs before sched (cse1, cse2). So in BOTH cases CSE should merge them.

Hmm, unless the ASM blocks the CSE merge in the original?! No, the original has the merge (one lui/ori).

Hmm, wait: in the ORIGINAL there IS one lui/ori (at 198). In the CANDIDATE there's one lui/ori (at 202). Both merged.

So in both cases one pseudo with 2 uses.

**So why does the scheduler hoist it in one and not the other?**

Let me look at the ACTUAL difference in the RTL between orig and w4 AFTER insn 478. In the orig, insn 478 is the asm; in w4, insn 478 is the sx division's expansion. The sx division's expansion includes a SET of the magic constant pseudo (a second pseudo with the same value).

Hmm! **In the ORIGINAL, is the sx division's magic constant a SEPARATE pseudo?** If so, in the original there would be TWO pseudos set to 1717986919 (206 and another) — and CSE merged them into 206 (the earlier one), so 206 has 2 uses.

In the CANDIDATE, the same. Hmm.

OK — let me look at the difference more concretely: let me read both files' lines 38630-38720.

Let me do that.
