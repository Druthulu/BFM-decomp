---
ts: 2026-10-22T12:38:46.703Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a16908c7d82609ecc
model: claude-opus-5-5[1m]
effort: medium
turnId: 4e94d3b6-b649-4184-9959-2cdd8b2eb53d
---
There's no supported way to clear learning mode short of a clean run, since hacking the run record isn't an option. So either I let it continue with the friction being addressed separately, treating the judge's usage-limit refusals as an environment issue, or flag this as a PA3 gap — especially since the expert adding notes after every run is itself what keeps learning mode active.

I should recommend the expert hold off on notes unless there's real teaching value, and separately flag the relative-path false refusal as a PA3 bug to fix. I'll offer a picker: keep one lane with the expert pulling back on notes so a clean run can lift learning mode (recommended), or let in-house Opus coders crack alongside (which breaks the MiniMax-only rule), or leave things as is — noting that the 23 refusals coincided with the judge hitting a subscription usage limit, which is a separate issue.
