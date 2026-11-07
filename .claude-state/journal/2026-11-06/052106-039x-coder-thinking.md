---
ts: 2026-11-06T12:21:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Zjpw3C1suFXCe1LCkmCu
---
`lreg-v0-local-first` — "local-alloc hands $v0 to a block-local pseudo first; target keeps it for the value". That fits well: vh (block-local, dies at its store) takes v0 while the target keeps v0 for vw. Yes, in mine vh→v0 and vw→v0... Actually in h2, vh→v0 and vw→v0 too (different times). Hmm.

`global-pri-bank-order`: "global-alloc priority order assigns the hard regs in a different order than the target" — vh should get a0, vv2 a1. That fits the observed pair a0->a1.

I'll use `lreg-v0-local-first` or `global-pri-bank-order`. The evidence: "lever-free: vh (rec>>24) takes $v0, vv2 $a0; target vh $a0, vv2 $a1; sched1 sinks the vh shift to its store".

Let me write notes.md and results row for item 1, then move on. Also append a moves.md line.

Also FRESH: orig.c was generated now from src (no prior orig.c existed) — note that.

Let me now write item 1's notes and results row, and the moves.md line.

results.tsv row format: `dir file func kinds result best tries wall evidence` (tabs).
dir = func_8001EFE0__800, file = src/800.c, func = func_8001EFE0, kinds = barrier,keepalive, result = PARTIAL:keepalive, best = 6, tries = 35, wall = lreg-v0-local-first (for PARTIAL the wall column = a tag), evidence = "sched1/global-alloc: vh (rec>>24) born at its store, takes $v0; target vh $a0 live 373-383, vv2 $a1".

Count tries: v0(1) v1..v5(6) f1..f8(14) g1..g8(22) h1..h8(30) i1..i4(34) + win_partial(35). Plus v3 rescored once (not counted). So 35.

Now the log line in moves.md: `kind | func | MATCH: move / WALL tag — mechanism (G31)`.

For a PARTIAL: `barrier,keepalive | func_8001EFE0 | PARTIAL:keepalive lreg-v0-local-first — barrier->do{}while(0) around the tpage store (C0535); keepalive: vh/vv2 register bank (G31)`.

Hmm, the format for moves.md: `kind | func | MATCH: move / WALL tag — mechanism (G31)`. I'll write it in that spirit.

Let me write these files now.
