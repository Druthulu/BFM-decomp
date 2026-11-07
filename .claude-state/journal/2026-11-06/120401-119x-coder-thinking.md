---
ts: 2026-11-06T19:04:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6Ffb2FKTSwm3R2rZ9IYL
---
The orig's loop increment block (52..114): insns 39, 42, 45, 48, 113, 114.
Trace:
- T-2: ready list "39 (1) 42 (1) 48 (1) 113" → picked 113 (the branch).
- T-3: "48 (1) 42 (1) 39 (1) 45 (1)" → picked 48.
- T-4: "45 (1) 42 (1) 39 (1)" → picked 45.
- T-5: "42 (1) 39 (1)" → picked 42.
- T-6: "39" → 39.

Final order = reverse of scheduling: 39, 42, 45, 48, 113.
So the orig's final order: 39 first. Which insn is 39? Let me check the RTL: in the orig, the increments are (a7, v1, a6, a5) = insns 39, 42, 45, 48? The target's asm order: a3+104, v1+104, a2+1, a1+104 → so 39 = a7's increment, 42 = v1's, 45 = a6, 48 = a5.

In h049: the trace: T-3: "46 40 37 43" → 46; T-4: "43 40 37" → 43; T-5: "40 37" → 40; T-6: 37. Final order: 37, 40, 43, 46. So 37 first. h049's RTL: 37 = 76 (the first increment in the source = v1), 40 = 74 (a7). So the final order = v1, a7, a6, a5.

The difference: in the orig, the final order is the RTL order (39=a7, 42=v1, 45=a6, 48=a5) — the source order. In h049, the final order is the RTL order too (37=v1, 40=a7, 43=a6, 46=a5) — the source order. So sched1 preserves the RTL order in both!

So the increment order in the asm = the source order (with these simple insns). Therefore, to get the target's asm order (a7 first), the source must have a7's increment first — but that flips the allocation (a7 becomes the canonical pseudo → $3).

Hmm. Unless the allocation flip can be achieved differently with the a7-first source.

Let me look at the orig's allocation vs w1's. In the orig (pinned), a7 is a hard reg (7). In w1 (a7-first, no pin), the .lreg had 76 = ? Let me check the .lreg for w1: "insn 14 sets 76 = symbol; insn 17 sets 74 = 76" — cse swapped. Hmm.

In h049 (v1-first), the .lreg: insn 14 = 76 (symbol), insn 17 = 74 (76). The same numbering! So the cse swap is the same; the difference is which *source variable* maps to 76/74.

Hmm, so with a7-first increments, cse maps a7→76? and with v1-first, v1→76?

The cse canonicalization depends on the copy propagation: `v1 = a7` — cse's `make_regs_eqv(dest=v1, src=a7)`. The canonical is chosen by `reg_eqv`/`qty` rules: the pseudo with the smaller number? a7 is created first (pseudo 74 in the initial RTL) and v1 second (76). cse canonicalizes to the *older* (74?) or the one with more uses?

In w1's final .lreg, insn 14 (a7 = symbol) sets 76 and insn 17 (v1 = a7) sets 74. So cse made the *symbol* go into 76 and the copy into 74 — meaning cse renamed a7's uses to 76? or v1's to 74?

The RTL after cse: insn 14 sets 76 (which was v1's number) — so cse rewrote the symbol's dest from 74 to 76? That's odd.

Honestly, the numbering doesn't matter. What matters: with the a7-first increments, a7 gets $3; with v1-first, a7 gets $7.

Is there a way to get a7=$7 with a7-first increments? The allocno priorities: the pseudo with the higher priority gets $3. The priorities depend on refs/live, which depend on which variable is which pseudo.

With a7-first (w1): 76 (pri 20000) = a7 → $3; 74 (5833) = v1 → $7.
With v1-first (h049): 76 (19285) = v1 → $3; 74 (9600) = a7 → $7.

So the pseudo 76 always gets $3; the variable mapped to 76 gets $3. The mapping flips with the increment order.

What determines the mapping? Probably cse's copy canonicalization: it merges `v1 = a7` into one pseudo, keeping the one that... In w1, a7 → 76; in h049, v1 → 76.

Hmm, since the *uses* of a7 and v1 are in different statements, cse's choice might depend on the first use order.

Let me think about what else could flip the mapping without changing the increment order: the *init* order (INIT1/INIT2) was swept — with a7-first increments and INIT2 (v1 = symbol; a7 = v1), the result was still 3 (wrong alloc) per the sweep? The sweep's 192 included perm=A-first × INIT1/INIT2. All A-first perms scored 3 (from the score distribution: 20 score-3 = ... hmm, 20 score-3, 20 score-2, etc.). Let me check whether any A-first perm scored 2. The score-2 files were h049-h071 (perm 6-8) and h161-h175 (perm 20-21). Perm 6 = (B,A,C,D); perm 20 = ? Let me compute: itertools.permutations("ABCD") index 20: the list is ordered lexicographically: 0 ABCD, 1 ABDC, 2 ACBD, 3 ACDB, 4 ADBC, 5 ADCB, 6 BACD, 7 BADC, 8 BCAD, 9 BCDA, 10 BDAC, 11 BDCA, 12 CABD, 13 CADB, 14 CBAD, 15 CBDA, 16 CDAB, 17 CDBA, 18 DABC, 19 DACB, 20 DBAC, 21 DBCA, 22 DCAB, 23 DCBA.
So perm 20 = (D,B,A,C) = a5, v1, a7, a6. And h161-h175 (n=161-175): perm = (n-1)//8: 160//8=20 → perm 20,21. So (D,B,A,C) and (D,B,C,A).

So the score-2 perms: 6 (B,A,C,D), 7 (B,A,D,C), 8 (B,C,A,D)?? h057 = n=57 → perm 7; h059 → perm 7? Let me not.

The score-2 perms all start with B (v1) except perm 20 (D,B,A,C). Hmm, perm 20 starts with D (a5) then B (v1).

So the "B before A" (v1 before a7) ordering flips the mapping. No A-first variant scores 2.

So: the mapping flip requires v1's increment (or a5's) to come before a7's.

Hmm, what about a *different* statement that makes v1 canonical without changing the increment order? E.g., the order of the load `v0 = v1` or the store `*v1 = *a0`? The sweep covered the load (LOAD1/LOAD2) but not the store position.

What if the store `*v1 = *a0;` is moved within the else block? The target's store order is fixed (it's the 2nd store). Hmm.

What if the *init* has v1 first (INIT2) and the increments a7-first? The sweep covered that: score 3? Let me check h001-h024 (perm A-first): h001 = perm 0 (A,B,C,D), init INIT1, load1, ret a7 → score 3 presumably. h005 = perm 0, INIT2... Let me check the actual scores of the A-first variants in the log.

Let me grep the log for h001-h024 scores.
