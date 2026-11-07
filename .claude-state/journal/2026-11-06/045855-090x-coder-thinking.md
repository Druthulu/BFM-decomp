---
ts: 2026-11-06T11:58:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wARsDVT1QJVMrKLlgZpc
---
Still 8; the pin $5 is needed. The residual: the address materialization hoisted to the top + a missing nop.

Since p2 keeps the launders (kind launder) and drops barriers, if I could get 0 it'd be PARTIAL:launder. Not there yet.

Let me think about the address hoist: mine emits `lui a1; addiu a1` at insn 3-4, target at 9-11 (after `lw s2,32(s3)`). The address is used by the first block. sched1 in mine hoisted it because the pin makes it a single insn group? 

Real C: introduce a dependency so the address computation is born later, e.g. compute `s` inside a block whose first use is later. It already is.

What if the address is `&D_800AE620` computed via a variable: `Blk20 *s = &D_800AE620;` outside the block (declared among the locals) with the pin? Hmm.

Alternatively: the target's order has `lw s2,32(s3)` (arg0->unk20 = obj) at 7 before the address at 9. In mine, the address is at 3-4 (before obj/ent loads?). So sched1 hoisted the address above the obj load.

Since the barrier after `obj = ...` was removed, the scheduler moved the address earlier.

Real C idea: make the address computation depend on obj: e.g., `s = &D_800AE620;` after the obj load — it already is textually after. sched1 reorders by priority; the address has priority 1 and the loads 1...

What if we add the *second* block's address usage earlier/later...

Alternative: give the address a real dependency: e.g. `Blk20 *s = &D_800AE620;` where the index into an array: `D_800AE620` is a struct. Could write `&((Blk20 *)&D_800AE620)[0]` — identity spelling (forbidden as a launder-equivalent).

Hmm.

Let me look at the target's first ~15 insns to understand.

Target (from the earlier partial dump):
```
0: ? 
1: lui a1,0x0 (D_800AE620)
...
```
Let me dump the target function fully for item 3.
