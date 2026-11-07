---
ts: 2026-11-06T14:08:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IjbqlRj2qePNTeXAnqtr
---
Some of these are useful. But my specific case is about ref counts in sched1. Let me look for a similar case: keepalive asm that adds refs to influence priority. The mechanism here is REG_N_REFS for sched1.

Let me understand what real C can do to increase refs on src and i. Since adding dead uses is not allowed (no identity launders), we need real code that naturally uses them.

Hmm, wait. Let me re-read the constraint: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." And "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack".

So we need genuine restructuring. The two asm statements add refs. If we restructure the loop so src and i are used more naturally (or so the register pressure/scheduling naturally matches), we can drop them.

Let me examine the target's sched1/greg dumps to understand why src/i get $9/$10. Let me look at the .greg dump for the loop. Actually the .s shows the final regalloc. The question: with the asm removed, what changes?

Let me just try: remove both asm statements and score. That gives the baseline "lever-free best" to start from. Let me create win.c without the two asm lines and score.

Actually, more efficient: let me create several candidates and score with sc.sh.

First, let me try simple removal.
