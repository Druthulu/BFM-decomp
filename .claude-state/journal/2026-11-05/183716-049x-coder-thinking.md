---
ts: 2026-11-06T01:37:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ur9vBcLwXsLgmyQ0b66s
---
Very interesting! At jump2, dec's block (label 314) is:
- insn 317: lw v0, 28(s0)
- insn 319: v0 = v0 - 1  (note: the store is NOT here!)
- jump_insn 323 -> label 383
- barrier 324
- code_label 325 ("zero")

So the store `sw v0,28(s0)` is NOT before the jump! Where is it? The merge already happened before jump2? Wait, this is the *nopin* build, and the merge shows as dec jumping to label 383 which is zero's store at the end. So the merge happened at an earlier pass? But earlier passes have cross_jump=0...

Hmm wait, actually maybe the store was merged by... let me look at label 383 and the end. Let me see the tail of the RTL.
