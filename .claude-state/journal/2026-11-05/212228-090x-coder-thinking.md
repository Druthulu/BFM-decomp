---
ts: 2026-11-06T04:22:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_31sjoCz31ezkYweNxI0f
---
r1 = 33 (worse), r2 = 14, r3 = 22. So the source order store-then-multiply is right.

Let me think about the p reload hoist once more. The target schedule: lw obj->1C, sll, addu, sll, lw p, addiu, sh. Mine: lw obj->1C, lw p, sll, addu, sll, addiu, sh.

sched1's list scheduler: it processes insns in the block. The p load and the multiply are both ready at the block start. Priority: p's load has a use (addiu/sh) further down; the multiply chain has 3 insns. sched1 uses `priority` = the sum of the lengths of the dependency chains starting at the insn (the "height"). The p load's height: lw → addiu → sh = 3. The multiply's first sll's height: sll→addu→sll→addiu→sh = 5. So the multiply should be scheduled first! Then why did mine schedule the p load second (after the first lw, before the sll)?

Wait, the first insn scheduled is the `lw obj->1C` (height 5). Then the next ready: the p load (height 3) and the sll (height 4, depends on lw). The sll should win (height 4 > 3). But mine scheduled the p load (4930) before the sll (4934). Hmm, so the heights must differ. Maybe the p load's height is higher because its use (sh) is a store with... Or sched1's `priority` also includes the number of dependent insns and the insn's "birth".

In target, the order is lw obj->1C, sll, addu, sll, lw p, addiu, sh — the multiply chain fully first. In mine, lw obj->1C, lw p, then chain. So the target's sched put the chain first.

Maybe the difference: in the target, the p load is born LATER in the RTL (after the multiply insns), and sched1's "birth" term (SCHED_BIRTH?) gives earlier-born insns priority. In mine, the p load is also born after the multiply (source order). Hmm, same.

Wait — maybe the difference is that in the target, the RTL order has the p load AFTER the `v = v + 0x600` (because the original C had the add before the p load?). If the p load's birth is after the add, sched1 might still schedule it early (height). Hmm.

Let me test moving the p load after the add (w9) — did that produce 14 with the same hoist? Let me check w9's disassembly to see if the p load position changed.
