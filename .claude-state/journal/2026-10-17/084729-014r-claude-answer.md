---
ts: 2026-10-17T14:47:29.298Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: b704fb85-213b-42d5-bada-88d73dab8ae4
usage: {input: 8, cacheRead: 204751, cacheWrite: 3979, output: 1525}
---

T10 needs your decision. Its pilot shows that the lever goal, a true zero on the strict lever check, can't be reached this phase. Changing that goal changes the milestone, so it's your call.

**What the pilot did.** A "lever" is a pin or a bit of inline asm we use to force the compiler to produce matching bytes. T10 picked 20 functions that each have their own one-off levers, across every lever kind and body size. It gave 4 coders up to 40 minutes per function to rewrite each one in plain C with the bytes still identical. They cracked 12 of the 20, about 60%. All 12 are committed, and every check is green, including 218/218 byte-identical. Each attempt cost about 40k tokens and 8 minutes of coder time. The 8 that failed all hit a specific compiler behaviour, for example the compiler folding constant addresses or reordering instructions, or a stack switch that plain C can't express.

**The projection for the remaining 430 functions:**

| | Estimate |
|---|---|
| Cracked | about 258 (range 168 to 335) |
| Left over | about 172 functions, roughly 230 rows |
| Cost | about 19M tokens, about 14 hours at your 4-coder cap |

Even a complete wave leaves some levers. Other leftovers also keep the strict check from reaching zero: the missing-parameter pins T7 kept as scratch registers, the asm macros and the GTE instructions. GTE is the PlayStation's geometry coprocessor, and its instructions have no C spelling. So no realistic cap reaches a true zero. That also means the generation's own goal of zero levers would need the same change.

**My recommendation is (a).** Run the full wave at your cap, and change the milestone. Every lever that survives keeps its row, which names the pass, the instrument and the specific compiler wall that stopped it. That replaces "strict check 0". The wave would use shorter budgets of 20 to 30 minutes per function. It would skip the two lever families that look hopeless: the instruction rows, and the group of 11 functions sharing the same 7 levers.

The wave isn't cheap, but about 60% of the attempts turn a lever into plain C. Option (b) costs about a third as much and still gets most of the easy wins. Raising the cap would finish sooner, but it still wouldn't reach zero.

**One loose end, whichever you pick.** The cast check (`type_census --check-casts --residue`) is failing again on 4 sites that came from T8's edits. Three are wrong empty-parameter declarations and one is a cast with no recorded decision. T10 didn't touch them. I'll add a small plan task to clean them up, so T13's milestone gate doesn't trip on them.

Pick an option in the picker.
