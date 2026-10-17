---
ts: 2026-10-17T11:56:49.411Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
I'm figuring out how priority is computed in this scheduler — it seems to represent distance from the block start, so scheduling proceeds backward from the end, placing the highest-priority (earliest) instructions last. That explains why insns 15 and 18 both end up with priority 1, creating a tie I need to resolve.

When priorities tie, I think ordering falls to class, then LUID — comparing the computed order gives 18 scheduled before 15 in the bottom-up pass, meaning 15 actually ends up first in final program order. I'm trying to figure out why 15's lower LUID wins over 18 despite both being loads with equal latency class, which means something else (maybe the dependency through insn 22) is breaking the tie.
