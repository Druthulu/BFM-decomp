---
ts: 2026-11-06T16:55:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Op5sgTpR5v0GJ5A0da85
---
- x1 (remove only the s-launder): 19, 79 ins → the s-launder is load-bearing (6 ins).
- x2 (remove only the q-launder): 3, 74 ins (one extra addiu s1,sp,32).
- x3 (remove only the keepalive): 2 ORDER (same count, different order).

w2 (remove keepalive + q-launder, keep s-launder) = 4.

Interesting: the q-launder removal adds `addiu s1,sp,32` (the &m materialization) — cse remat. The keepalive removal reorders.

So all three levers are load-bearing in different ways:
1. s-launder (keep base in reg): removing costs 6 ins (the copy block goes wrong).
2. q-launder (cse remat kill): removing adds an `addiu s1,sp,32`.
3. keepalive (sched barrier): removing reorders.

Now, the s-launder `__asm__("" : "=r"(s) : "0"(s))` — it ties s to itself, keeping the base in a register. Real-C replacement? It forces `s` (the pointer &D_800AE620) into a register rather than re-materializing. Hmm.

The q-launder: `q = &m; RotMatrixY(ang&0xFFF, q); asm("=r"(q))` — kills cse's remat of &m. Without it, cse rematerializes &m at the func_800484EC call site (`addiu s1,sp,32` and uses s1). Hmm, actually the extra `addiu s1,sp,32` appears; with the launder, the compiler uses `addiu a1,sp,32` twice? Let me look at w2's diff: mine[40] addiu s1,sp,32 (extra), then move a1,s1 vs target sw v1,56(sp), and addiu a1,sp,32 / addiu a0,sp,32.

The target at e78: `addiu a1,sp,32` (delay slot of RotMatrixY), e7c `addiu a0,sp,32`, e80 `addiu a1,sp,16`. So the target materializes &m twice (a1 and a0) — that's the *remat* the launder supposedly kills? Wait, the launder's comment says "cse_expr.md §2 remat kill". Hmm.

With the q-launder (orig), the bytes match. Without it, cse keeps &m in a register (s1) across the call, adding `addiu s1,sp,32` and using `move a1,s1`. So the launder *forces* cse to NOT keep &m in a register, causing remat at each use. Interesting.

Real-C to force remat instead of a cached address: C0414's dead-reset! `q = &m; RotMatrixY(..., q); q = 0;` — cse invalidates the equivalence, flow deletes the dead set before sched1 → zero bytes. That's exactly the C0414 pattern. Let me try: replace the q-launder with `q = 0;` after the call.

The s-launder: `s = &D_800AE620; asm("=r"(s) : "0"(s))` — ties s to itself. Without it, the copy block (6 ins) differs. Let me look at x1's diff to understand.

Let me first try the q-launder replacement (dead-reset) and see. And the keepalive: removing it gives ORDER 2. Let me look at x3's diff.

Let me run:
- y01: orig minus q-launder + `q = 0;` after RotMatrixY.
- y02: w2 + q=0 (i.e., remove keepalive too, keep s-launder) → then handle the keepalive.
- y03: remove keepalive + q-launder + q=0.

Let me test.
