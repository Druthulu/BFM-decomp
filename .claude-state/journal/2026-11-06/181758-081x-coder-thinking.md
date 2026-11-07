---
ts: 2026-11-07T01:17:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kEEO7oc9yxqc3OKDz17Q
---
Both rows are in. Time 18:17:53.

Now the moves.md appends (one line per item) and the log.

Wait — "Per item append exactly one row to P1x/results.tsv" ✓ (2 items, 2 rows).

moves.md: "after each item append one line `kind | func | MATCH: move / WALL tag — mechanism (P1x)`". I should have appended after each item; let me append both now (2 lines).

Then the log at phase-ends/current/logs/T11.cP1x.md.

Let me check the log dir exists and write the log.

Also the timing: item 1 start 17:54, end 18:10 (16 min); item 2 start 18:09, end 18:18 (9 min)... Hmm, item 2 is only 9 min, under the 20-min rule. Ugh.

Wait — the 20-min rule. Item 2: 18:09 → 18:18 = 9 min. That's well under 20. I need to keep working on item 2 until ~18:29.

Hmm. The rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". Item 2 has 63 tries but 9 min.

I need ~11 more minutes on item 2. Let me continue with more variants. There's a chance of a crack if I find the right schedule. Let me think about what could work:

Since the target's store base is $16 and the only difference is the base, maybe there IS a C spelling that keeps the pseudo from being replaced. Let me reconsider the replacement pass: it's local-alloc's `update_equiv_regs` (or `optimize_reg_copy_1`). Let me read optimize_reg_copy_1 to see the exact condition — maybe it only fires when the copy is inside a loop or when the src dies.

Let me read local-alloc.c optimize_reg_copy_1.

Actually, first: which function did the rewrite? Let me look for the code that changes `mem[...r72...]` to `a0`. In optimize_reg_copy_1: "If SRC is not dead, we can replace uses of SRC with DEST"? Let me read it.

Let me read lines ~600-800 of local-alloc.c.
