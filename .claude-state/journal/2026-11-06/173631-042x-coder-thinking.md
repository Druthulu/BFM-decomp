---
ts: 2026-11-07T00:36:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_39f5FihBwXlnWqNUrzXE
---
It's 17:36, not 18:02 — my earlier estimates were wrong (the date at start was 17:24, so 12 minutes). 

win.c scores 0 with no asm/register.

Now append the results row and moves.md line, and notes.

results.tsv row format: dir file func kinds result best tries wall evidence
- dir: func_801805EC__ov_SC02_027_jr_8017D898
- file: src/ov_SC02_027/ov_SC02_027_jr_8017D898.c
- func: func_801805EC
- kinds: barrier
- result: MATCH
- best: 0
- tries: 30
- wall: -
- evidence: gcc pass + mechanism ≤140 chars: "cse: dead reset `cam = 0` (C0414) after use1 kills the D_80126B78 symbol-load equivalence; 2nd use re-loads; flow deletes the dead set (0 bytes)"

Let me count tries precisely: orig.c baseline isn't a try. w1 (1), w2 (1), w3 (1, scored twice but one body), w10..w36 = 27. Total 30 distinct bodies. Good.

Append with a command. One action per command. Use printf >> results.tsv.
