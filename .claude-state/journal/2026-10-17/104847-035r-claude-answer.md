---
ts: 2026-10-17T16:48:47.680Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 22591948-c82d-4a2b-b612-af26462bd9d3
usage: {input: 6, cacheRead: 199956, cacheWrite: 1989, output: 1817}
---

Mostly yes. Building structs as we went would have saved the most, and with no real downside. A strict "pure C only" rule from day one would have cost us, unless it came with an escape hatch. Naming as we went is worth doing only when there's evidence behind the name.

**1. Structs as you go: yes, clearly.** This is the biggest avoidable cost we have. The cleanup has dealt with about 292,000 cast sites that were left as residue, and nearly 12,700 placeholder struct types. Most of those placeholders are the same handful of real structs, found again in 218 separate binaries. If every agent had been told to look up the existing struct and extend it before writing a cast, most of that would never have existed. Doing it during matching is cheap, because the agent already understands the memory it's reading at that moment. Doing it now, Phases 3.38 to 3.40 have spent days of restruct cycles on it.

The one real cost: early on, a canonical struct is wrong in places, and fixing it ripples through every file that uses it. That's still far cheaper than merging the duplicates afterwards.

**2. No levers, pure C: right as the default, wrong as an absolute rule.** The evidence cuts both ways.
- **For it:** T7 found that most pins were really wrong declarations, such as a missing parameter. T10 showed that about 60% of the remaining levers fall to plain C when an agent is given 20 to 40 minutes.
- **Against it:** the other 40% hit real compiler walls. Examples are constant-address folding, instructions the compiler moves ahead of where they're written, a stack switch, and GTE (the PlayStation's geometry coprocessor) instructions with no C spelling. A strict ban would have left those functions unmatched, or had agents burning hours on them, and 100% matching would have come much later.

The rule I'd use from the start: a lever is allowed only when the agent records, at the moment it matches the function, which wall forced it and what it tried first. That's exactly the "survivors name their wall" rule you just chose for 3.40, applied at matching time instead of afterwards. It keeps the agents honest without blocking progress.

**3. Understanding the function and naming as you go: partly.** Human decomp projects do this, and it's why their code reads well. For us, there's a catch. A name guessed with no evidence is worse than a placeholder, because people trust it. That's why the 3.43 plan says "unnamed beats wrong".

So I'd ask agents to name only what they can back up: parameters and locals whose role is obvious from the code, and struct fields confirmed by more than one function. Everything else keeps its placeholder until real evidence turns up, such as strings, the debug menu, or watching the game's memory live.

**The trade-off overall.** A "human way" setup would have made the road to 100% slower, maybe by a third, judging by how long the cleanup phases have taken. In exchange, most of Phases 3.35 to 3.40 wouldn't have been needed. For a project starting today, I'd take that trade.

**Where this goes.** T14 already adds the "do sooner" lessons to the from-the-start guide, `docs/how-to-ai-decomp/03-bootstrap-order.md`: canonical types during matching, declarations before pins, and a debt chart from day one. Two points from your question aren't in it yet: levers only with their wall recorded, and names only with evidence. I'd add both to T14. It's a small docs change and doesn't touch the milestone. Pick an option in the picker.
