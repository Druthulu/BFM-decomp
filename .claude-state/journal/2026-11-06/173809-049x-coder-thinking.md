---
ts: 2026-11-07T00:38:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FwnandXdw0rVLL7uua7c
---
priority(insn) = max over dependents of (priority(dependent) + cost - 1), minimum 1. So a load whose dependent chain is longer gets a higher priority.

In the target, the val load is scheduled before the stores. In mine, after. Since priority depends on the chain length from the load: load → addiu → sw. That's priority 1 + ... let's compute: the final `sw v0,0(at)` has priority 1 (no dependents). addiu has priority = priority(sw) + cost - 1 = 1 + 1 - 1 = 1 (if cost 1). The load: priority(addiu) + cost - 1 = 1 + (load latency 2?) - 1 = 2? So the load has priority 2. The stores (sw zero) have priority 1.

So the load should be picked first! Unless the "ready list" order and LUID tie-breaking matter. Hmm, mine schedules it later — maybe because the load is not ready at the start (its address computation lui v0; lw v0 — the lui is the first insn, and the lw depends on it). Wait: mine has lui v0; lw v0 at 39-41, meaning the lui is also late.

Hmm, maybe the load in mine got a lower priority because the value's use (addiu) is farther... Let me look at the full mine listing to see where the addiu is.

Let me get mine's full object listing. Use --keep.
