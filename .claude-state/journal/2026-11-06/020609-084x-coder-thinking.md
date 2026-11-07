---
ts: 2026-11-06T09:06:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LrcFaeqaipv4GUbCeJvt
---
v27: 37 (516 ins) — the temp live across the GTE region caused extra register saves. v30: 48 (the product computed at the wrong place).

So best lever-free score = 20 (v18/v19/v20). WALL with tag `flow-unused-result`.

Let me record:
- results.tsv row: dir file func kinds result best tries wall evidence
  - result: WALL
  - best: 20
  - tries: count lever-free scored bodies: c1, c2, c3, v01-v30 = 3 + 30 = 33. Plus orig = 34 scored runs. Let me say 33.
  - wall: flow-unused-result
  - evidence: "product (a[2]-z)*buf[5] kept only by a store (+1 insn, best 20); dead reg set deleted by flow (insn_dead_p, flow.c:1705); no zero-cost use" ≤140 chars.

Let me count: "product (a[2]-z)*buf[5] kept only by a real store (+1 ins, best 20); flow insn_dead_p deletes any dead reg set (flow.c:1705); asm-free zero-cost use none" — ~150. Trim.

"dead product kept only by a real store (+1 ins, best 20); flow insn_dead_p deletes dead reg sets (flow.c:1705); no asm-free zero-cost use" — ~130. Good.

- moves.md line: `keepalive | func_8017DC10 | WALL flow-unused-result — dead (a[2]-z)*buf[5] kept only by a store (+1 ins, best 20); flow insn_dead_p deletes dead reg sets; no zero-cost real use (G24x)`

- notes.md with details.

- Also: the WALL requires ≥20 min. Item started 01:54; now let me check the time. Also need to clean up the scratch files? The shard dir must stay <200 MB — fine.

- DONE WHEN: every item has exactly one results.tsv row. Items 1,2 done, item 3 now.

Also, should win.c exist for a WALL? The brief: "each MATCH/PARTIAL has its win.c scoring 0" — WALL doesn't need win.c. I'll keep the best candidate as best.c? Not required. I'll leave the variants (they're small). Actually, the brief says scratch files under the shard dir are fine; the shard stays <200MB. The variants are tiny. But maybe clean up the list_*.txt files. I'll keep a couple of key ones? Let me remove list files to keep it tidy.

Let me also double check item 1 and 2 results rows and the win.c files score 0 (already verified). And the DONE WHEN: exactly one row per item. Let me verify results.tsv has 3 rows + header.

One more consideration: the brief says "First grep .run/P40/T11/moves.md for your kinds" — done for keepalive.

Let me finalize item 3. Check the time first.
