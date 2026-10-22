---
ts: 2026-10-22T01:15:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8rMbSxZVX8cXl9mlOiiz
---
Now the results.tsv. Let me write the whole file (header + 2 rows).

Item 1: dir=func_8018A180__ov_SC06_029_jr_801898CC, file=src/ov_SC06_029/ov_SC06_029_jr_801898CC.c, func=func_8018A180, kinds=launder, result=MATCH, best=0, tries=2, wall=-, evidence.
Item 2: dir=func_8017FE9C__ov_SC06_030_jr_8017F65C, file=src/ov_SC06_030/ov_SC06_030_jr_8017F65C.c, func=func_8017FE9C, kinds=launder, result=MATCH, best=0, tries=25, wall=-, evidence.

Tries for item 2: let me count the scored tries:
1. orig (baseline, 0 — the reference, not a candidate try)
candidates: cand01, cand02, cand03, cand04, cand05, cand06, cand07, cand08, cand09, cand10, cand11 = 11
+ sed sweep 1 (4 variants: 127/160, operand order, 160/20, *0x100) = 4 → 15
+ round A (4: flg|vol, 2366, x==16, |=) = 4 → 19
+ cand01 sweep (3: precedence, 127/160, *256) = 3 → 22
+ cand11 sweep (3: dead-def moved, copy moved, arg uses vol) = 3 → 25
+ cand12 (the cleaned winner) = 1 → 26

So tries = 26 (excluding the orig baseline). Let me say 26.

Hmm, the "wall" column for a MATCH row = "-". And "best" = 0.

Evidence ≤ 140 chars:
item 1: "gcc -O2: 63 ins = target, byte-identical; dead-reset pb=0 after each &buf use breaks cse's addr class; 6x addiu aN,sp,56" (113) ✓
item 2: "gcc -O2: 111 ins = target, byte-identical; dead vol2=vol copy + 2nd def vol|=0x3000 -> vol has 2 defs (chain order) + ori in call group" (129) ✓

Let me write results.tsv.

Then the log file: phase-ends/current/logs/T11.cG15.md with the timeline per item + the handoff for items 3-7.

Then delete the dumps.

Also: should I add notes.md to the item dirs? The brief says "Notes in <dir>/notes.md". Let me write short notes.md for items 1 and 2 (they're part of the shard record). Good practice; cheap.

Let me do the results.tsv + notes.md writes in parallel.
