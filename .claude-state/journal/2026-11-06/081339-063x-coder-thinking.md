---
ts: 2026-11-06T15:13:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8Ap0oSZ3GxvLwZRLDsrf
---
245 ins — 8 more. Something went wrong: probably the `vol` variable's live range extended and changed allocation (or the split statements prevented the fold that produced `ori a1,a1,0x3000` etc.). Hmm, +8 is a lot.

Wait, 245 vs 237. Maybe removing the launder changed the block's allocation and everything shifted. Actually e1 also removed the launder — the no-launder base is 236. So e1 added 9 insns?! That's odd for a 3-statement rewrite.

Maybe the issue: `vol = vol | (0x3000|sx); vol = vol & 0xFFFF;` — the OR/AND now write vol (a live variable across the call) whereas before they wrote the arg temp. This extends vol's live range and maybe forces the value into a callee-saved reg or changes the or/and sequence.

Hmm.

Let me step back and reconsider the budget. Item 1 is eating a lot of time (~25 min?). Let me check the time. Started 07:59. Let me check now.

Actually, let me reconsider the problem from the "launder catalog" perspective: the moves.md entries for launder show many MATCHes with `pv &= 0xFF000000` (real 2nd set) — i.e., the second set is PART of the real computation, and the code still matches because the original code NEEDED that masking. Here, the target's code has no mask on vol... 

Hmm wait. Maybe I should reconsider: is the launder in this body really "lever 3" (the re-tie) or is it possible the natural body has vol computed differently? The note says "only the re-tie does" — the original dev concluded no plain C spelling works (9 spellings swept). But our job is to try anyway.

Given b4 is score 2 (1 insn off), maybe a variant of b4 with the mask placed to avoid reorg stealing it can reach 0. The mask must stay a real insn but not be delay-slot-eligible. Options:
- Put the mask BEFORE the block's start label (i.e., in the previous block). The previous block ends at the `bgez a2,53c` branch. The mask would be before that branch... but vol isn't set yet (dead store). Unless we move the vol computation earlier — impossible (depends on av).

- Make the mask an insn reorg won't move because it's a *call* or *jump*: no.

- Make the mask's destination a register the branch needs: the branch needs a2 (sx) and v0 (16). If the mask's dest were a2... but then it'd clobber sx. No.

- What if the mask is `vol = vol & 0xFFFF` but vol is in a *callee-saved* reg that the branch... no.

- Make the mask a *delayed* insn? no.

Alternative: give vol a second set that reorg deletes? no.

Hmm, what about the resource-conflict route: `insn_references_resource_p (trial, &set, 1)`. set = resources SET by the branch insn. For a bne, sets nothing except pc. Then accumulates skipped insns. The andi sets a1; a1 was set by `subu a1,a0,v1` which is among the skipped insns → a1 ∈ set → conflict. So the andi should NOT be eligible! Yet it ended up in the delay slot.

Unless the andi is NOT moved by reorg's backward scan but by sched2 or by the thread copy. Wait — maybe the andi was scheduled after the branch by sched2? Let's check the .sched2 dump for b4 to see the pre-reorg insn order.

Let me look at b4's .sched2 RTL around the region. Actually .sched2 is a dump of the pass; the final RTL is in the .sched2 file's tail? Let me grep for the bne and andi order in the .dbr (reorg) dump, which shows the delay-slot decisions.

Let me look at the .dbr dump for b4.
