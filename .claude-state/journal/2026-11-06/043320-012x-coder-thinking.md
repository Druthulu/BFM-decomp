---
ts: 2026-11-06T11:33:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_p91Inu7NUqFyi51hezMp
---
The --body mode scores a bare body file. So win.c is a bare function definition.

Now, what score = the masked mismatch count. I need score 0.

Let me start with item 1: func_80015B6C in src/800.c lines 2429-2487. It has pins mFF $7, tag2 $6, barriers, launders. Kinds are barrier,launder (pins are "levers of other kinds the def already had (pins under other causes) may stay, never added"). Hmm — pins are not in kinds, so they may stay. Interesting: the row kinds are barrier,launder. Pins ($7 mFF, $6 tag2) may stay. Wait but does the pin kind get counted in "kinds"? list.tsv says kinds barrier,launder. So pins can stay.

But careful: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." That first sentence says no pin... but then CONSTRAINTS says "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". The list row kinds are barrier,launder so pins may stay. Right — the constraint clarifies. PARTIAL: keeping only some kinds, e.g. keeping pins while removing barrier/launder → if that scores 0 it's PARTIAL:pin. But actually a MATCH requires barrier and launder gone; pins kept are fine.

So for func_80015B6C: remove the 4 barriers and 2 launders (and the `= 0`? The launder is `__asm__("" : "=r"(x) : "0"(x))`), keep pins mFF $7 and tag2 $6. Try to find real C to preserve the schedule.

Let me first set up orig.c and a baseline lever-free body (v0) with barriers/launders simply deleted, and score it.

First, copy orig.c from src. I need a script to extract lines 2429..2487 (externs + function). Actually the bare body can include the extern decls before the function? win.c example includes externs inside the function body (block-scope). The body file probably needs to compile as a function definition in the TU context. delever_search --try TU FN FILE --body: presumably it substitutes the body into a copy of the TU. Let me check the --try implementation briefly.
