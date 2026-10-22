---
ts: 2026-10-22T11:11:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_PsssmpTYXThdXgXTWYB5
---
All the same. Interesting: the goto didn't change anything (GCC removed it), the switch(0) didn't add instructions (GCC optimized it to nothing and merged blocks).

So block-splitting via goto/switch didn't work — the front end/flow removed them before scheduling.

I need a different mechanism. Let's think about WHY the load goes after li a1.

Hypothesis: **sched1's "birth boost"** — from moves.md: "sched1-birth-boost — sched1 vs local-alloc: birthing-insn priority boost against a local-alloc constant". And "sched1-birth-boost — sched1 puts index addr chain (feeds call a0) above v1b".

Hmm. Let me look at the RTL dump to see the block structure and where the load sits.

Let me use cc1_dumps_tu.sh on the candidate TU. The scratch dir from --keep has the spliced TU source: .run/P36/engine/score/ov_SC03_092__func_8017E780/p3/*.c

Let me run cc1_dumps_tu.sh on it and look at the .sched dump.

Note: dumps go under my item dir per constraints ("cc1 dumps go under your item dir and are deleted as soon as you have read them"). I'll use DUMP_ROOT=<itemdir>/dumps.

Let me do that.
