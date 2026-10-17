---
ts: 2026-10-17T11:22:01.908Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm realizing registers set once with a REG_EQUIV note get their live length doubled, which lowers their global priority — so if k has REG_EQUIV, its live length doubles to 13/148, letting j win. That happens when k is set only once and that set carries a REG_EQUAL note pointing to a constant, converting it to REG_EQUIV, or when it's set from memory.

But k is set twice in this case, so REG_EQUIV never kicks in for it; meanwhile other registers (m24, mhi, pb) that are constants set once do get doubled, explaining their low priority. I'm not finding a clean path where k gets this treatment, so I should step back and reconsider the overall picture given the time spent.

I've confirmed that the priority boost (`reg_live_length *= 2`) only applies to once-set registers with a REG_EQUIV, which k doesn't qualify for since it's global and set from a register. I'll now check the time and log.
