---
ts: 2026-11-06T20:15:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cl9J1ZZEH0PVinCYknyP
---
Item 1 cracked: MATCH, 197 ins.

Wall: "-". Evidence: loop.c hoist threshold (insn_count 28 vs 29) — the pin's fix_register lowered n_non_fixed_regs by 1. Our crack: two address temps raise insn_count to 30 so -1024 isn't hoisted; combine folds the addius away.

Let me record the results row and moves line, notes.md. Then move to item 2.

results.tsv row format (tabs): dir file func kinds result best tries wall evidence.
- dir: func_80180254__ov_SC03_121_jr_8017E1D0
- file: src/ov_SC03_121/ov_SC03_121_jr_8017E1D0.c
- func: func_80180254
- kinds: pin
- result: MATCH
- best: 0
- tries: count scored tries. Let me count: orig(1), nopin(2), vA(3), vC(4), vD(5), vE(6), vF(7), vG(8), vH(9). 9 tries (scoring runs; dumps not counted). Say 9.
- wall: -
- evidence: "loop.c hoist: pin's fix_register lowers n_non_fixed_regs (threshold 28 vs 29) so -1024 stays in-loop; 2 addr temps (combine-folded) raise insn_count 28->30" ≤140 chars. Let me count: that's about 150. Trim: "loop.c threshold: pin fix_register drops n_non_fixed_regs 1 (28 vs 29); 2 addr temps combine-folded raise insn_count 28->30, -1024 stays" — ~140.

Let me write notes.md and the results row + moves line.

Timing: item 1 started 13:03, now ~13:20.

Let me write notes.md per item dir. Then append results row (one action) and moves line (one action).

Actually "append exactly one row to W49/results.tsv (format under INTERFACES)" and "after each item append one line kind | func | MATCH: move / WALL tag — mechanism (W49)".

Let me do the notes write first.
