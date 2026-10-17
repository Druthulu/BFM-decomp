---
ts: 2026-10-17T13:42:01.197Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I'm also noticing the instruction order differs around the sched2 window—my placement of mFF relative to lhu doesn't match the target, which suggests the final scheduling differences stem from register conflicts affecting how sched2 orders things, particularly around how a0 gets scheduled relative to the other locals.

Working through the register allocation priority: pv needs to avoid v1 since that's held by the lhu temp, so pv's load must come before or around that conflict point, meaning pv's lifetime stretches across the address computation and lowers its priority. If allocation picks the first free register in order (v0, v1, a0, a1...), and a1 is reserved for the global idx register even though the local pass can't directly see that, then the ordering of pv, i4, m24, and mFF depends on how sched1 (which schedules backwards by priority) places these instructions in the pre-sched2 sequence.

I'm considering whether the original source computed the pointer into a separate variable before doing the mask-and-store operations, which would reduce redundant loads of the lookup tables -- but the target code clearly reloads those tables twice, which rules out that structure (unless aliasing forces the reload). This points back toward the original addPrim-style code, with the actual register differences coming down to how sched1 breaks ties between ready instructions.

I'm also weighing small variations in how the index gets scaled into a byte offset, whether types are signed or unsigned, and how the branch condition on the lower bits is phrased -- these subtle choices could shift which instruction ends up in which register without changing the overall logic.

This looks like the standard addPrim(ot + idx, p) pattern. I should check the type of the `.a` field in the OtBlk_80016450 struct to confirm the pointer arithmetic is correct.
