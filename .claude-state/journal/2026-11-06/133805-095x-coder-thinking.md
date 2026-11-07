---
ts: 2026-11-06T20:38:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yy5aJFpsD0GiuLQW8NBl
---
Time is 13:38. I need 2 more minutes. Let me use it for one more genuinely different experiment — maybe the most promising untried idea for cluster 2: making the constant non-constant by using a `register` variable? No (pin, banned).

What about making the call's second argument come from the *store*: e.g., if we write `((Unk*)s0)->unk2 = 7;` then read it back as a value? no.

Actually, let me try one thing for cluster 1 that I haven't: making the join's xori not the first insn by putting the `((Unk*)s0)->unkDC = v;` store *before* the xori in a value-preserving way. The target has xori then sw. What if we write `((Unk*)s0)->unkDC = v ^ 1;` — vW tested (10). What about `((Unk*)s0)->unkDC = v; v ^= 1;`? That stores the wrong value (v instead of v^1). Not equivalent... unless the field is later XORed? No.

Hmm, what about `v ^= 1; ((Unk*)s0)->unkDC = v;` — current.

OK. Let me try a different cluster-2 idea: what if `r` is assigned from a *static const* variable? e.g. `r = D_800B9A02;`? wrong value.

Let me instead do something useful: verify item 4's setup while waiting (read its orig/target). That's productive and passes time.

Item 4: func_8018C14C in src/ov_SC04_011/ov_SC04_011_jr_8017D494.c, kinds pin, 51 lines.

Let me start item 4 now (the wall for item 3 is essentially recorded; elapsed time will be ≥20 min by 13:39:48). Actually I should append the moves line for item 3 first.

The moves line format: `kind | func | MATCH: move / WALL tag — mechanism (W49)`. For a WALL: `barrier,launder | func_801852B0 | WALL dbr-delay-fill — ... (W49)`.

Let me append it now.
