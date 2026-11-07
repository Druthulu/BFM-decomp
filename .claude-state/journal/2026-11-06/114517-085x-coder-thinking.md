---
ts: 2026-11-06T18:45:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9RQoGkUcpL67plZ4Fws4
---
Same. OK, WALL for item 1. Let me write the notes and append the results row. Then item 2 (header pin) — the last item.

Let me also clean up the dump dirs for item 1 (dump1, dump2) and the --keep scratch after reading.

Notes for item 1:
- FRESH: orig.c == src:7641-7679.
- Result: WALL sched1-argcopy-hoist, best 4 (51/51 ins; only the a1 lui/addiu pair moved from position 22-23 to 31-32).
- Mechanism: without the keepalive asm (a volatile memory barrier + a use of pseudo 77), combine folds `(set 77 (symbol_ref D_801A15AC))` into the call-arg move `(set (reg 5 a1) (77))`; sched1's backward pass then makes that insn ready only when the call is scheduled (near the block end), so it is emitted at the call setup (position ~15). With the asm, insn 55 had a use (the asm at insn 57) that sched1 schedules at T-17 (a memory barrier), so 55 became ready at T-18 → position 5, matching the target (801c/8020).
- Evidence: sched traces (dump1/dump2, deleted), orig .rtl insn 55/57/96, w1 .sched.
- Tries: ~200 (w1-w6, p001-p180 statement-order sweep, v1-v5, v10-v12, d1-d4, l1-l2, p1).

Wall tag: sched1-argcopy-hoist (from walls.txt: "arg-copy hoisted/sunk across the call setup").

Hmm, is that the best tag? The existing wall "sched1-argcopy-hoist" was T10 S01. Our mechanism: the arg copy (the constant materialization) is sunk to the call. I'd say yes.

Let me write the notes and results row, then clean up.
