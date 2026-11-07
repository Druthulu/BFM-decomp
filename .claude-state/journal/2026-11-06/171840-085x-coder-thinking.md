---
ts: 2026-11-07T00:18:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tp20lsYE3mCA89627vK2
---
All 82 insns — the const fold persists. g06 produced no score (maybe a compile error — `&D_80126B58[0]` requires D_80126B58 to be an array; it's declared `extern s32 D_80126B58;` so indexing fails).

So the const-addr fold is robust: no C spelling prevents it. This is the documented `cse-const-addr` WALL.

Now, could the 3-cycle (nopin, 15) be fixed? Let me check: nopin has the right insn count (79) and only a 3-cycle register issue. Let me see if statement reordering fixes it. The 3-cycle: mine a0=s1, s1var=s2, s4var=s3, tp=s4; target a0=s2, s1var=s1, s4var=s4, tp=s3.

Hmm, target: s1var=s1, a0=s2, tp=s3, s4var=s4.
Mine: a0=s1, s1var=s2, s4var=s3, tp=s4.

So a0 and s1var are swapped; tp and s4var are swapped.

To fix lever-free: the allocation order must be s1var, a0, tp, s4var (target) instead of a0, s1var, s4var, tp (mine).

Hmm. Let me check the priorities (nopin body — with the launder kept, so the allocnos differ slightly).

Hmm, let me dump the nopin body's allocno table.

Actually, time check: ~17:28. Item 4 at 13 min. Let me spend ~10 more minutes.

Let me try reordering statements in the nopin body (launder kept, pin removed) to fix the 3-cycle. But wait — the pin is what we want to REMOVE for PARTIAL:launder. nopin = pin removed, launder kept. If I can get it to 0, that's PARTIAL:launder.

The 3-cycle is an allocation order issue. Let me try statement reorders.

Hmm, but nopin has 79 insns (correct) and score 15 (only register pairs). Let me look at its full diff to be sure there are no other issues.

Let me check the nopin diff.
