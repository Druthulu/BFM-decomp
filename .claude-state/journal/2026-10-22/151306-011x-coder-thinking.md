---
ts: 2026-10-22T21:13:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KIsBhVIT1fAbZ7BSwz9y
---
No dis helper. Let me use --keep to get the candidate object and disassemble. Or check tools/ for a disassembler. Let's try `--try ... --keep` and then look for the object path, then objdump.

Actually simpler: I know the target disassembly must be somewhere. Let me just run --keep and disassemble both.

Actually first, let me think about the plain-C move without needing full dumps.

Target 114 ins, mine 106. The diff shows:
- mine[47] bnez v0,14a0 vs target beqz v0,146c — branch structure differs
- insert target[49:57]: the full arm body (sh v0,32(s0); li v0,1536; sh v0,34; li v0,-80; sh zero,36; sh zero,46; j ...; sh v0,48)

So the target has arm3's body inline at 49-56 with `j` at 55 and `sh v0,48(s0)` in the delay slot. Mine has a `j` somewhere pointing to a merged block.

Since arms 1 and 3 are identical (both end with unk30 = -0x50), the target must have them duplicated — which the ROM does because the original source presumably had the barrier or just different scheduling.

Hmm wait, target arm1 also would be duplicated. Total target 114. Mine 106 = 8 fewer = exactly one arm body (8 insns: sh, li, sh, li, sh, sh, j, sh = 8). So one full arm tail was merged.

Which arm? The insert is at mine[49] in the arm3 region (target 49-56). Given the barrier was in arm3, the merge was arm3's tail into arm1's (or vice versa).

To defeat cross-jump in plain C: make the RTL of the two arms differ. Cross-jump (gcse.c/crossjump in jump.c? in gcc 2.96 it's "cross-jumping" in jump.c: `merge` of identical blocks) compares insns with rtx_equal_p.

Idea: make the arm3 store use a different but equivalent form that produces a different insn. E.g., in arm1 store `unk30 = -0x50;` and in arm3 store `unk30 = k;` where k is s16 born above. If the RTL still shows both as a constant store, they merge. If in arm3 k is a register (not propagated), then it's `li v0,-80; sh v0,48(s0)` — the same instruction sequence but the RTL differs (one is a store of a constant, the other a store of a pseudo that happens to be -0x50). Cross-jump compares the final RTL though (after cse/propagation) — if cse propagates k into the store, they're identical again.

The comment says "born ABOVE the barrier so sched1 can hoist the li" — so k exists as a pseudo. If cse propagates constants into stores... In gcc 2.96 cse does propagate constants. Hmm, but the target clearly has `li v0,-80` then `sh v0,48(s0)` rather than `sh` with a direct constant — well, on MIPS you can't store a constant directly; you always need li into a reg. So the store is `(mem (plus reg) (reg v0))` where v0 holds the const. In arm1 it's the same.

So what distinguishes them in the target? Ordering: in arm3, `li v0,-80` is at slot 52, before `sh zero,36` and `sh zero,46`. In arm1 presumably `li v0,-80` comes at the end right before `sh v0,48`. So the difference is *scheduling*: the li is hoisted in arm3 because k is born earlier.

So the merge isn't just about identity — cross-jump requires identical blocks; the target's arm3 block has the li at a different position, so the blocks differ → no merge. In mine, the li is at the same position (at the end) in both arms → merge.

Wait but if the barrier was there to hoist... the comment says "born ABOVE the barrier so sched1 can hoist the li". So the barrier's role: k is born above the barrier; sched1 can move the li up because the barrier is a scheduling barrier? No — an asm volatile is a scheduling barrier, which would *prevent* movement across it. Hmm, "born above the barrier so sched1 can hoist the li" — meaning k's li can be scheduled anywhere above the barrier within its live range, i.e. the barrier bounds the motion so the li doesn't sink below.

Actually sched1 runs before the barrier is... no, sched1 works on the whole function; the asm volatile has a scheduling barrier attribute so insns don't move across it. So the li born above the barrier can be hoisted up (above the barrier) but not below. And the store is below the barrier. So the li ends up somewhere above.

So my job: get `li v0,-80` scheduled at slot 52 (after sh zero,46, before... wait target order is: sh v0,32; li v0,1536; sh v0,34; li v0,-80; sh zero,36; sh zero,46; j; sh v0,48). So the li -80 is 3 insns before its use.

And crucially that makes arm3's block differ from arm1's → no cross-jump.

So the lever-free fix: hoist `k`'s birth in plain C so that the li is born early and sched1 places it there, AND the arms differ.

How to make the li be born at that point in plain C: assign k earlier — e.g. move `s16 k = -0x50;` before the unk24/unk2E stores. Then sched1 schedules the li. But the merge might still happen if both arms end up identical.

Hmm — but wait: if I move `k = -0x50` earlier in arm3, sched1 will hoist li in arm3 and it will land at a different slot than arm1's li, so the blocks differ → no cross-jump. That's plausible and it's plain C (decl order / statement order / init at decl).

But careful: the declaration `s16 k = -0x50;` is inside the if-block. If I keep it there it's already "born" before the stores... Hmm, actually the current source has `s16 k = -0x50;` as the first statement in arm3, before unk20=0x71. But the barrier is after unk2E=0. So the li should be hoistable already... yet mine merged. Because without the barrier, the merge happens first? Order of passes: cross-jumping (jump_optimize) runs after cse, before sched1? In gcc 2.96: jump_optimize (cross-jump) is part of `jump_opt` which runs early (after cse1?). Actually toplev: cse1, jump_opt (jump2?), ... sched1 is `schedule_insns` called from `rest_of_compilation` after cse2? Let me recall gcc 2.96 MIPS flow: ... expand, jump (jump_optimize), cse, ... , jump2 (cross-jumping happens in jump_optimize when flag_cross_jumping), sched1 (scheduler) later.

The point: the cross-jump compares RTL before scheduling, so sched1 differences don't prevent the merge. Then, after merge, both paths share the block, and scheduling happens once.

So the merge is decided pre-scheduling. The RTL blocks: arm1 = 5 stores; arm3 = 5 stores. Identical except the value of the last store (-0x50 vs k's value... same constant). And `k` being a pseudo vs a direct constant — after cse, if k is propagated, identical.

But the barrier in the ROM's source prevented the merge at the RTL level (asm blocks aren't mergeable). So in the target, the two arms stayed separate and sched1 scheduled each independently, hoisting li in arm3 (k born at the top) and in arm1 the li -0x50... in arm1 it's a direct constant store; the li is born at the store, and sched1 can still move it up within the arm.

Hmm, so why does arm1 not have the li hoisted too? Let me get the actual target disassembly. I need to see. Let me use --keep to get my object, and find the target dump. Let me check what --try --keep prints.

Actually simpler: tools/ has a disassembler? Let me check for the target binary. `bin/dt.sh` computes diff — delever_search has the target. Let me look at tools/delever_search.py briefly for a dump mode... `--explain TU FN` reads one body's residual (no writes) — maybe with disassembly.

Let me just run --try with --keep and see what it prints.
