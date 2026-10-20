---
ts: 2026-10-17T17:32:42.240Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm noticing the lui/ori pair for large constants gets split apart, likely after CSE or at combine, since MIPS handles big constants as a single move that's split later in scheduling. The lui at insn 225 has no dependencies so it gets hoisted early, while the ori at 226 stays later, placed according to instruction ordering (luid).

In backward scheduling, the lui only becomes ready once its ori partner is scheduled, giving it lower priority and placing it later in backward order but earlier in forward order. In the target, m24's lui ends up right after e1b's store because of a shared hard register t0, creating a WAR dependency that sched2 can't avoid — so m24's lui placement is driven by that register conflict rather than luid ordering alone.

I'm now wondering whether m24 wasn't actually hoisted in sched1 at all, and whether the difference comes from how m24's constant gets materialized: if the lui wrote into a fresh single-use temp pseudo rather than the same register used by the ori, REG_N_SETS would treat it as "birthing" — a value with exactly one def — which gets boosted in priority and scheduled immediately before its use, matching what we see in the target.

But the standard mips constant-split pattern reuses the same destination register for both the lui and the ori, giving it two sets, so that explanation doesn't quite fit. I'm checking the clock — I've spent about five minutes on this one point without resolving it.

Given my budget runs to roughly 11:58 and there are four separate pins to puzzle through, I should move faster: let me try spelling things out with literal constants instead of named temporaries, since that might reveal a closer match.
