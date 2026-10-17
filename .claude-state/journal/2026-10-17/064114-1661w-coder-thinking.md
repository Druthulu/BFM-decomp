---
ts: 2026-10-17T12:41:14.668Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm noticing the giv corresponds to y3's last store at p0+0x22, and wondering why that single giv represents the combined group rather than another store in the loop body — checking whether the target's +46 offset (12+34) matches regardless of which insn is treated as the representative giv, so I want to dig into the sched dump to see if the vVec initialization is tied to a different instruction in the target case.

Tracing through the scheduler's backward pass, both my output and the target pick insn 269 first, but then diverge: mine picks insn 566 before 266, while the target needs 266 to rank higher. I'm checking whether this could stem from a LOG_LINK dependency cost between 269 and 566, or from differing insn priorities between the addsi3 and movsi instructions, but both have identical latency of 1 on MIPS ALU, so that's not it — now I'm considering whether adjust_priority's readiness boost treats these insns differently when they become ready.

I'm looking at reg_n_sets counts to see if either insn's destination register is set exactly once, which would trigger a priority boost, but both 239 and 73 appear to have two sets each so that doesn't explain the difference either. I'm now wondering if the target's loop counter is actually a different pseudo entirely — perhaps one tied into loop.c's biv/giv elimination — which would change which register gets the single-set boost.

Since REG_DEAD notes are stripped, n_deaths is always zero, so the real trigger must be the "birthing" check: any insn whose destination is live and has exactly one set gets boosted to max priority as it becomes ready. Looking at my block, insns like 263 (single-set, becomes boosted), 251, and 269 (whose dest 139 stays live because its use at 271 gets scheduled) would all qualify for this boost during backward scheduling.

I'm trying to figure out whether vVec itself could have only one set — that would force it to be scheduled first via the same boosting mechanism. But since vVec is the loop counter used directly in the address computation (not eliminated by biv analysis), it necessarily gets two sets, so this boosting path doesn't apply to it. That rules out this explanation, so I need to look at LUID ordering instead, since insn 566 has a smaller LUID than 266.

Maybe with a loop_start structure where the exit test gets duplicated and placed between preheader and LOOP_BEG, CSE could fold away the copied test, leaving the giv insertion stuck right after vVec=0 anyway. I'll wrap up this class here—about 25 minutes spent.
