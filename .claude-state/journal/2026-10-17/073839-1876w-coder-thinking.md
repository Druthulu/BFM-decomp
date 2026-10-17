---
ts: 2026-10-17T13:38:39.164Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm noticing something odd in the a2 case—the diff score only flagged one line, but there may be a similar store instruction that should differ too. It looks like this is related to how reload or scheduling moves the instruction setting a0 right after the call, possibly a pre-reload scheduling pass behavior.

The real issue appears to be sched1 hoisting the a0 = P72 assignment above the stores before reload_cse runs, which lets reload_cse substitute a0 for s0 in both stores. In the original code, sched1 didn't hoist that assignment the same way because of true and anti dependencies on earlier instructions, so I need to figure out why the scheduler's dependency ordering differs between the two cases and how to prevent the hoist from happening prematurely.

Wait, actually the greg dump already shows a0 for the stores, not s0 — so this isn't about reload_cse substitution at all. It's more likely global register allocation assigned the same hard register a0 to the pseudo used for stores, and reload's register inheritance after insn 25 is what's causing a0 to persist into the store addresses.

For the target asm, I'm trying to trace the exact instruction order sched1 and the delay-slot filler produce — specifically whether the store at offset 516 gets pulled into the jal's delay slot or whether the move into a0 ends up there instead.

So the real fix is making sched1 keep the a0 copy below the 516 store while letting sched2 (which handles delay slots) hoist it. I'm wondering if this ties into how GCC's scheduler treats hard-register sets feeding a call — there may be dependency logic in sched.c around call insns and pending register sets that controls this ordering.

I realize cse would likely fold that offset arithmetic back to P72 anyway, so that approach won't create the needed distinction. I'm now considering splitting the pseudos differently: have the stores go through a separate copy pseudo while the call argument retains the original parameter pseudo, so they aren't trivially equated.

Looking at the original ordering more carefully — the param gets copied into hard register s0 only after the first call, meaning both the original parameter pseudo and the s0 copy are simultaneously live across that call. That seems like it should create a register conflict, but the original allocator still assigns s0 to the copy, so I need to figure out why that doesn't clash.

Without pinning registers, maybe I can trick scheduling into preserving order by introducing an artificial dependency — like making the argument copy depend on something that only becomes available after the 516 store executes, rather than relying on hard register constraints directly.

Still trying different variable arrangements for the pointer casts and store offsets, but they keep collapsing to the same CSE'd form. I'm considering whether disabling scheduling or restructuring the call into a separate statement might break the dependency differently, and pausing to check how much time I've spent on this.

Found the root cause for S01: sched1 hoists the `a0 = P72` arg copy above both pseudo stores, and reload_cse then rewrites the store bases to `a0`, whereas in the pinned original the copy reads hard `$16` (set after the first call) and stays put until sched2. I'll check elapsed time before trying dependency-shaping spellings.
