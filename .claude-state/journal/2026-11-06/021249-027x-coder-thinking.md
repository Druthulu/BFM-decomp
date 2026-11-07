---
ts: 2026-11-06T09:12:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SsPyMi1XsZI4dZKFKq5g
---
Item 1 MATCH: keepalive removed, 0 on 141/141 includers. But wait — win.c still contains the pins ($7, $5, $4, $3). Constraint says pins under other causes may stay, never added. Kinds = keepalive only, so fine. But is the keepalive genuinely gone and the body lever-free w.r.t. keepalive? Yes.

Hmm — but the brief says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." Then the parenthetical "levers of other kinds the def already had (pins under other causes) may stay". There's tension. The results format says PARTIAL:<kinds still kept>. Kinds row is keepalive only, so pins aren't row kinds here. Fine — MATCH.

But careful: the keepalive asm also may have been what made `pm` "used" in the target. The score 0 proves it's not needed.

Now append the moves.md line and results row, write notes.md. Then item 2.

Let me record item 1. Need "wall `-`" for MATCH, evidence = gcc pass + mechanism ≤140 chars.

Evidence: "keepalive asm redundant: pm used by `rem = pm % dm` two insns later; expand drops empty asm, same insns (all 141 includers)" — but if it was redundant, the mechanism is "keepalive redundant — real use of pm already keeps $3". Let me phrase ≤140.

Actually let me double check whether the keepalive removal changed anything at all vs with keepalive: both 0. So the asm was a no-op in codegen (GCC expands empty asm with a register operand to nothing, but the operand keeps the pseudo live — here pm was already live). Good.

Results row fields: dir file func kinds result best tries wall evidence. dir = func_80139D04__func_80139D04, file = src/shared/ov/func_80139D04.h, func, kinds=keepalive, result=MATCH, best=0, tries=2, wall=-, evidence.

Moves line: `keepalive | func_80139D04 | MATCH: keepalive asm redundant, pm already live via rem = pm % dm; 141/141 includers (G25x)`.

Let me append with a single action per command (results.tsv fix is its own step). I'll use printf append. Actually writing via Write would need whole file; append with bash >> is fine.

Do it in separate commands: one for results.tsv, one for moves.md, one notes. Or combine? "One action per command: a results.tsv fix is its own step, never folded into a check command." So separate.
