---
ts: 2026-11-06T11:54:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_k2fxeLWOIQtPV5BBMCuL
---
EXCELLENT. The header comment explains everything:

(2) sched2 ORDER in the outer-loop head block. "Statement order cannot reach the target shape -- sched1 normalises every permutation to one insn order (verified: 470+ statement orderings, MEM_IN_STRUCT_P forms, box aggregate forms and loop forms all bottom out at closeness 5)."

So the re-tie (launder) is load-bearing for the sched order, and 470+ statement orderings were already tried by the original author. So this is a genuine wall for real C.

(1) The barrier/sliders: "Two independent mechanisms... N=4 zero-byte insns" — the file carries 2 re-ties + 2 sliders. The sliders are `__asm__ volatile ("")` inside `if (lim >= g.otz)`. The barrier in our function is one of the sliders (`__asm__ volatile ("");` with the comment "Deliberately in THIS block, not the loop head").

Wait — the header says "This file carries N=4 (2 re-ties + 2 sliders)". Our function has 2 re-ties (launders) + 1 slider? The barrier at 2864 is one slider. Hmm, maybe the second slider is elsewhere. Let me check for other `__asm__ volatile ("")` in the function range. Earlier grep for asm in the function: l1, l2, b. So 1 slider in this function. The header mentions the N=4 budget across... maybe both functions.

Anyway: mechanism (1) is a global-alloc priority tie that needs N zero-byte insns in the loop to shift live lengths. Mechanism (2) needs the re-ties.

The comment explicitly says statement order cannot reach the target shape (470+ orderings tried). So this is a legitimate WALL for the launder part, and the barrier part is a global-alloc priority tie.

So item 2 = WALL. Tag options: `sched1-birth-order` (or sched2-order), and `global-pri-bank-order` for the slider. Best lever-free = v1 = 45 (both removed) — but wait, v1 removes all 3 levers and scores 45. The header says the sliders are also part of the N=4 budget. So removing all levers gives 45.

Hmm, but let me reconsider: the brief says the kinds are barrier,launder. Removing all of them = v1 = 45. Best = 45.

Hmm, but maybe I can do better than 45 by keeping the *other* slider... there's only one.

Wait, let me re-read: "N=4 (2 re-ties + 2 sliders)". Our function has 2 re-ties + 1 slider = 3. Maybe there's another slider I missed. Let me grep the function range for `__asm__ volatile` more carefully.

Actually my earlier `grep -c asm orig.c`... let me check orig.c for all asm lines.
