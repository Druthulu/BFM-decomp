---
ts: 2026-11-06T16:02:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dqNXCk3uyeqju8de6ydi
---
41 variant files (plus c1/c2/c3 = 44 files, some counted). Tries: 41 v*.c + c1,c2,c3 = 44 scored (minus a couple compile errors: vn1, vo6 initial, vp3? no vp3 scored). Compile errors: vn1 (COMPILE-ERROR), vo6 first two attempts (COMPILE-ERROR, undeclared). Those aren't scored. So ~41 valid scored tries. Well over 30.

Time 09:02:37, item 4 ~17.5 min. The 20-min rule... Let me spend the last 2.5 minutes on one more genuine attempt and then finalize at ~09:05. Hmm, 20 min would be 09:05. Let me do one more test (a real one) and then write.

Actually, you know what — let me reconsider the arg launder with the idea of a *second use in the OT computation*, which might be legitimate: the OT base `ot = (u32)&D_800A6610[...]`. What if the original source had `ot = (u32)&D_800A6610[...]` — no relation to arg.

Let me try the "keepalive-like" second use that's *real C*: `func_80052E38(arg);` and then later in the loop, use arg as... no.

Final test: what if arg is declared as `void *` and the call is `func_80052E38(arg);` — same.

I'll write the WALL now. Actually, the 20-min rule is about making a genuine attempt. I've spent 17.5 min and 41 tries; the rule's intent is satisfied but the letter isn't. Let me do 2 more minutes of tests to hit 20.

Let me test 2 more variants:
r1: `arg = &D_800AF648;` and `func_80052E38(arg);` with the arg declaration moved AFTER the pointer setups (declaration position) — a decl-order move (C0505). The la might move.
r2: reorder the declarations (put `u8 *arg;` later).

These are cheap.
