---
ts: 2026-11-06T21:47:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_chDwg0SKc74hOLAipLDr
---
All still 13. As notes said. The allocation is robust to these.

Time spent ~30 min on item 1. Budget says 20-30 min per item; past 30 min stop and record a wall, but a WALL needs ≥20 min and ≥30 scored tries. I have ~10 scored tries so far on this item (v0 + 8 variants + orig baseline?). I need ≥30 tries before declaring WALL. Hmm. But I also have 3 more items. The budget is 20-30 min wall per item; a WALL needs ≥30 tries. That's a lot but tries are cheap (~2s each).

Let me think harder rather than brute force. The register swap: target has otz-load/oidx in $3, packet chain in $4. Mine the opposite.

Key insight from RTL: r181 (otz load) has pri 10000, live 2. r194 (ior result) pri 20000, live 1. The packet chain leader r194 wins allocation before r181 and takes $3 (since $2 busy at its range). 

To flip: make r194 not win $3. If r194's live range overlapped $2, it'd take $4... wait it takes the first FREE reg. If $2 were free at r194's live range, it'd take $2 and everything shifts. In target, r194 is a0 ($4), meaning $2 and $3 were both busy at r194's live range when it was allocated. $3 busy because r181/r84 (oidx) already there? But r181 has lower priority (10000) — unless the suggested-copy phase allocated r84 first.

Hmm, actually the copy-suggestion phase: `combine_regs` ties dying inputs. r84 (ashift) — is ashift considered a copy? Let me check local-alloc's combine_regs: it's called for insns of type... Actually local-alloc calls combine_regs for `set` insns with `reg` operands; it handles the case where the destination is a register and the source is a register, and also `if (GET_CODE (src) == ...)`. For a shift, the source r181 is an operand but the set is `(ashift r181 2)` — combine_regs may still record a "copy" relation? It records `reg_copy_sugg` only for actual copies (`set (reg) (reg)`), I think. Let me check.

Let me grep combine_regs in local-alloc.c for how it treats operands.
