---
ts: 2026-10-17T14:13:07.522Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm tracing where cse might reuse a register holding the symbol base plus an offset, so that two separate constant computations could end up sharing the same base register instead of being kept distinct.

I'm going too deep speculating on struct member addressing through a pointer — time to pull back from S09 and return to S01 for a bit longer, trying the birthing insight where the a0 copy gets placed adjacent to the call by scheduling so reload_cse won't rename the store. But birthing needs the destination register to have exactly one set, and a0 as a hard register likely has multiple sets across both calls, so I'm questioning whether that condition can even hold given how combine might have altered the parameter copy.

Reconsidering through sched1's priority computation — since stores aren't births themselves but constants loaded before them can be, I'm walking through how INSN_PRIORITY would rank the a0 copy versus the store chain under backward scheduling, trying to see if a tie in priority could force the right ordering through rank_for_schedule's tie-breaking.

I'm also checking whether changing the second call's argument type (maybe `u8*` vs `void*`, or an `s32` param with casts) would change the RTL enough to matter, but it looks like a no-op either way. Finalizing now — writing the log and computing the timing periods for S01/S05/S09 based on when each attempt started and ended.

The dump confirms the S09 wall: the `+0x18` constant gets merged into a pseudo that crosses the call, and no C formulation keeps it out of that class for the target's `addiu a0,s0,24` pattern. I'm stopping here and gathering final timings.
