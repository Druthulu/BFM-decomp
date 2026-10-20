---
ts: 2026-10-17T17:15:57.367Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm noticing sched1 keeps placing a1's computation later, likely because the asm keepalive acts as a barrier anchoring it right before the volatile asm instruction, since a1 is only used as a call argument at the final jal and the backward list scheduler's priority ordering would naturally delay it until then.

To get it earlier, a1's set would need a dependency forcing it before something earlier—like if it were reused right after a prior call's delay slot (move a0,s0; lui a1; addiu a1 pattern), which is exactly where the target places the second call's argument setup but where my version pushes it further down.

Thinking through priority: backward scheduling picks the highest-priority ready insn, and the longer v0 dependency chain (lui/addiu/or/or/sw) likely outranks a1's shorter chain, pushing a1 later in the final forward order unless its priority is boosted by being tied directly to the call's argument cost.

If volatile asm acts as a scheduling barrier, that would force a1's set to precede everything that comes after it, which could explain why a1 appears right after a0 in the target — I'm now wondering if there's a natural code structure, like splitting into basic blocks, that would produce this ordering without artificial tricks.

Since a0 is a hard register ($4), I'm checking whether treating a1 similarly, or restructuring the call arguments so a1's assignment happens inline within the function call itself, would produce equivalent RTL and match the target's instruction order.

Actually, I suspect this is a scheduler priority wall — the two-instruction load of a1's symbol address (lui/addiu) might behave differently depending on how early or late it's scheduled relative to the call. I want to try a couple more variations where a1 is declared or assigned in a different position to see if that shifts the output.
