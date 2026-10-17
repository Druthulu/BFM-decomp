---
ts: 2026-10-17T16:46:41.457Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a26a2e7a9927b54ee
model: claude-opus-5-5[1m]
effort: medium
turnId: 253b27e4-07a4-41f7-b188-1141b6e4bbf5
---
I'm comparing the instruction ordering between mine and the target version—loads versus stores and register differences (health v1 vs v0, obj a0 vs v1). The target stores unkE and unk2 before the loads, so without a scheduling barrier the compiler hoists loads above stores; I'm trying to figure out if those stores were originally placed differently to prevent that reordering.

I'm wondering if gcc 2.7's lack of strict type-based aliasing means the stores were done via a different pseudo or pointer type, since memrefs_conflict_p would treat a different base expression conservatively. I'm also considering whether sched1's per-basic-block scope matters here—if there was a label or block boundary (maybe around the func_8012A828 call) separating the stores from the loads in the original code, that would explain why no hoisting occurred in the target.

Now I'm checking whether sched2/reload explains it instead: in the target, loads land in v0/v1 right after a li instruction, consistent with no hoisting happening in sched1 and register allocation just reusing v0. I'm also testing whether MEM_IN_STRUCT_P flags on the memory references could make gcc 2.7 treat them as potentially conflicting even with non-overlapping offsets, since that would block the reordering without needing any block boundary at all.

Maybe it's about scheduling priority instead: gcc 2.7's backward list scheduler picks insns by dependency-chain length to the block end, so longer chains (health load feeding the later add and store, obj load feeding the later or and store) get higher priority and get placed earlier, which could explain why the loads end up positioned mid-block rather than grouped at the start.

Maybe the stores were combined with other dependent statements, so reordering the six statements (unkE, unk2, obj, health, unk6, unk70) while keeping obj/health before their uses could change the schedule outcome. I should try generating permutations of that block to see which ordering produces the matching instruction sequence.
