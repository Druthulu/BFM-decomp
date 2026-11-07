---
ts: 2026-11-06T13:04:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LjckspGFJCyoRUVkxXIO
---
The RTL order: 373 (lw), 376 (li 36), 379 (subu), 381, 383, 385, 388 (addiu a0+4), 390 (a0=153), 393 (addu), 395 (a1 = ba).

So pre-sched, the li (376) is BEFORE the addiu (388). After sched1, mine has `lw; addiu; li` — the addiu moved up before the li. The target has `lw; li; addiu` — i.e., sched1 kept the li before the addiu.

Interesting: `a0` (dp) is a *hard reg* (a0 = $4). insn 370 sets a0 to the symbol; 373 reads (mem (a0)); 388 computes a0+4 into 153; 390 sets a0 = 153.

Hmm, note that a0 is a hard reg here (because the variable dp is pinned $4 in the C!). The pin `register s32 *dp __asm__("$4")` is in the original and stays.

sched1 moved the addiu (388) before the li (376). Since a0 is a hard reg, insn 373 (lw from a0) and 388/390 (write a0) — 388 computes into 153 (a pseudo), 390 sets a0 = 153.

So the addiu at 388 is `set 153 = a0 + 4` — a pseudo. sched1 can move it up (it only reads a0).

In the target, the addiu stayed after the li. Hmm.

What if `dp = dp + 1;` is written so that gcc emits `set (reg 153) (plus (reg 4) (4))` then `set (reg 4) (reg 153)` — that's what we have (2 insns, one of which is the copy that gets deleted).

Hmm, sched1's ordering of 376 (li) vs 388 (addiu): both ready after 373. The li has priority 1, the addiu priority... depends on consumers: the addiu's result (a0) is used by 393 (addu) which feeds 395 (a1) which feeds the loop. The li's result feeds 379.

The scheduler picks the highest priority first; if equal, the hazard decides.

Idea: make the addiu's priority LOWER than the li's, or vice versa. Priority = length of the dependency chain (INSN_PRIORITY). The addiu's chain is longer (to the loop) → higher priority → scheduled first. In the target, the li came first, so its priority must have been ≥.

What if I reorder the C so that the `ba` computation depends on the li? no.

Hmm, what if `c36`'s li is used by more things... 

Honestly, this 1-insn order is a sched1 wall of the kind "sched1-birth-order" (moves.md 335, C0535). The C0535 do-while trick splits cse1's EBB — I tried t1 (do-while around df) → 2.

Let me try a do-while around the whole dp block (from `dp = D_80127548;` to `ba = ...`), which I did in j1 for c1 (18). For p2, let me try:
- v1: do-while around `{ dp = D_80127548; ... ba = ...; }` (the whole block)
- v2: do-while around `dp = dp + 1; ba = ...;` (t2 did that: 2)
- v3: do-while around the `tmp` computations.

Let me also consider: maybe the difference is not sched1 but reorg/dbr? No, these are plain insns.

Let me try v1 and v3.
