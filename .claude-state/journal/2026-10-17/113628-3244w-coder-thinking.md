---
ts: 2026-10-17T17:36:28.275Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: acf1e900976d98019
model: claude-opus-5-5[1m]
effort: medium
turnId: 82d9c87a-028e-4c83-b14d-9d07f43471e2
---
I'm wondering whether large integer constants always need splitting into register sets, or whether there are cases—like when a constant is forced through `force_reg` during expand for operations like `andsi3`, or when CSE rewrites an insn into a plain set with a constant—where the split logic wouldn't apply the same way.

Actually, a better explanation emerges: if m24's pseudo doesn't get a hard register during allocation and instead carries a REG_EQUIV constant, reload would materialize it directly at the use site via `li`, choosing the first free hard register (t0) and reusing it across uses through reload inheritance. Since reload insns run after sched1, they escape splitting, and sched2 could then shuffle the materialized `lui`/`ori` pair past a dependent `sw`. This would explain why t0 is shared across all four `and` instructions—it's the reload register chosen because it's free after e1b's death, likely due to high register pressure from v0–a3 and t0–t6 all being live simultaneously.

Right, priority 1 constants lose to the dependent stores with higher priority, so the lui keeps floating up until only other priority-1 insns remain. That confirms the float-to-top behavior, so m24 is likely a reload-generated or birthed pseudo — I'm now checking whether global-alloc even bothers allocating pseudos marked with a REG_EQUIV constant when they have few references.

I'm wondering if update_equiv_regs treats these single-assignment constant pseudos as rematerializable, so reload just re-emits the constant into a spill register ($t0) at each use point rather than keeping it in a hard register. That would mean the pseudo never gets a real allocation because register pressure or rematerialization logic deprioritizes it.

Shifting focus now, I should decide how to log this finding — likely as PARTIAL since only some pin subsets score zero, while the best lever-free configuration (score 55) still beats other variants like r00 (97) or nat (90), so I'll record it as WALL with sched1-split-const-hoist.
