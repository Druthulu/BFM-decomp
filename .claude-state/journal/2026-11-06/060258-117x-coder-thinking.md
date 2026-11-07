---
ts: 2026-11-06T13:02:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_l24810Q2wgO7u9g0Ahff
---
All 2. Hmm. The `li v0,36` placement is stubborn.

Let me look at what determines it. In mine: `lw $3,0($4); addu $4,$4,4; li $2,0x24; subu $2,$2,$3`.

The target: `lw v1; li v0; addiu a0,a0,4; subu v0,v0,v1`.

Both have the same 4 insns, just the li and addiu swapped. sched1's hazard choice.

The `addiu a0,a0,4` (dp++) is independent; the `li v0,36` is independent; `subu` depends on both.

sched1 orders by priority then hazard. To flip, maybe change which register dp++ writes or its dependency. Hmm.

What if `dp = dp + 1;` is expressed as `dp++;`? m12 did that for the other item... let me try here. Or `dp = &dp[1];`? Or `dp = (s32 *)((u8 *)dp + 4);`?

Actually: since the target's addiu comes AFTER the li, and mine before, maybe the difference is the *order in the RTL* (pre-sched). In the C, `dp = dp + 1;` is after `tmp = tmp << 4;` — so the RTL order is: lw, li, subu, sll, addu, sll, addiu, addu(ba). sched1 then moves the addiu up. In mine it went before the li; in the target after.

Hmm, the sched1 result depends on the priorities: the addiu's priority depends on its consumers (addu for ba). 

Lever-free: make the addiu's priority lower/higher. E.g., split: `s32 *dp1 = dp + 1;` then `dp = dp1;`? That's the same.

What if `ba` is computed from `dp + 1` directly (r3) — gave 3.

Hmm. What about using a different form for dp++: `dp += 1;` (same).

Since these are pure scheduling choices, maybe a do-while around the `df` computation helps: `do { df = c36 - dcount; } while (0);` (r1 was do-while around c36 = 4).

Let me try a couple more:
- t1: `do { df = c36 - dcount; } while (0);`
- t2: `do { dp = dp + 1; ba = ...; } while (0);`
- t3: `tmp = (df << 1) + df; tmp = tmp << 4;` → `tmp = ((df << 1) + df) << 4;` (single statement)
- t4: reorder `dp = dp + 1;` before `tmp = tmp << 4;`

Let me test t1-t4.
