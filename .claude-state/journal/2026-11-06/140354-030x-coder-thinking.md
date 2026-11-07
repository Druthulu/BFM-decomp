---
ts: 2026-11-06T21:03:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MZyGWCP0JB7o97LWkpHt
---
So function section is lines 2-895. The lreg dump is the RTL after local-alloc (with reg renumbering?). Actually `-dl` dumps the "local-alloc" pass output, which is the RTL with registers allocated. Hmm, that doesn't show priorities. `-dL` might show... Let me check the dump suffixes: .lreg is -dl. Is there a priority dump? Not by default.

But the .lreg dump shows the assigned registers. I can inspect which pseudo got which reg. Let me look at the region with sll/addu. Actually the RTL will show the actual hard regs after local-alloc.

Let me just look at lines 2-895 for the relevant part. But that's ~900 lines; I should grep for sll or the sym.

Actually, a better idea: I need to compare against the TARGET, which I can't dump. But the target's allocation is what I want to reproduce. Since only 5 insns differ, and it's a clean a0/a1 swap, I can reason: I need e to be allocated before off.

Let me try a different real-C approach: force e's birth to be earlier AND extend off's live range. Or, more robustly, introduce an extra reference to e that is genuinely part of the code but folds to nothing... 

Hmm wait. Actually there's another classic: make the *second* use of the load a separate variable so e is referenced again. But the load is shared.

Let me reconsider the whole structure. The barrier and launder were "NEEDED DIFFERS (P36 rung B tus9)" — a known hard case. Let me check if there's prior work on this exact function in research/moves. grep moves for func_8017E590.
