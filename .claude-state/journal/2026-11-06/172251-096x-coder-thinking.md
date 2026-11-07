---
ts: 2026-11-07T00:22:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gMl9B5E1vV05DcyRFHBX
---
Still 2. The reorg delay-slot duplication is stubborn.

Let me look at this from the reorg angle. The target's delay slot is nop. Mine's is a duplicated slt.

reorg.c's `fill_slots_from_thread`: it fills the delay slot with an insn from the target thread if `eligible_for_delay`. The slt is eligible. To prevent, the slt must not be at the target or must not be eligible.

Hmm, what if the slt is preceded by a nop in the target? No.

What if the branch target is a label that's shared? Hmm.

Actually — what if the abs block's branch target is a *different* label? Let me think about the RTL:
```
bgez v1, L1
negu v1,v1
L1:
slt v0,s1,v1
beqz v0, L2
move s1,v1
L2:
```
reorg fills the bgez delay slot from L1 (the slt) → duplicates it and changes the branch target to after the slt.

To prevent: the insn at L1 must be ineligible for a delay slot. On MIPS, `eligible_for_delay` excludes jumps, asm, etc.

Lever-free: I could put a jump at L1? E.g., make the max a call? No.

Hmm, what if the max is written so that the slt is not the first insn at L1? E.g., if there's a `move` before the slt. Then reorg might fill with the move (different code).

Hmm.

What if the branch target L1 has a `NOTE` or something? 

OK, this is a reorg wall. Let me record item 2 as is (already recorded as WALL). I've now done more tries (45 + 9 + 4 = 58).

Hmm, but my results row for item 2 says tries 45. Let me update it? The brief says "Per item append exactly one row". I already appended one. Updating would require rewriting the file. Hmm, "Items that already have a results.tsv row are done: skip them." — that's about items, not edits. But I should keep the row accurate. I can edit the tries count. Since it's my own row and accuracy matters, let me update it via a script (rewrite the file with the corrected count). That's a "results.tsv fix" — its own step.

Actually, let me not fiddle; 45 tries is already ≥30, and the additional 13 tries don't change the outcome. But for honesty in the log, I'll mention the total. Let me update the row to 58 to be accurate. Hmm, it's cleaner to leave it as the count at the time of the decision. I'll note the extra tries in the log.

Actually, let me update it properly — the log timeline will say "58 tries". Let me rewrite the results.tsv with the corrected number. I'll do that in one step.

Hmm, but the rule "Per item append exactly one row" — I'll keep one row per item and just fix the tries field. Fine.

Let me first finish: record item 4's moves line, then update item 2's tries, then write the log, then run the expert check (chk.sh) to verify.

Actually, wait. Let me reconsider item 2's nolau once more — it's SO close (score 2, one diff). If I crack it, it's a PARTIAL:pin. Let me think harder about the reorg duplication.

reorg duplicates the target insn into the delay slot when the branch is "likely taken" or when it's safe. The condition in reorg.c: `fill_slots_from_thread` with `thread_if_true`. For a conditional branch, reorg tries to fill from the fall-through first (`fill_slots_from_thread (insn, condition, fallthrough, target, ...)`).

Hmm, the bgez's delay slot: reorg tries to fill from the fall-through (the negu) first — but the negu can't go in the delay slot (it must execute only when taken). Then from the target (the slt) — the slt is safe on both paths, so it can be duplicated/moved.

Hmm, but wait: if reorg MOVED the slt into the delay slot, the target would be 5afc and there'd be no second slt. Mine has BOTH (the slt at 5af0 and again at 5af8). So reorg COPIED it (not moved), because the slt is also needed on the fall-through path.

So the slt at 5af8 is the original (fall-through path), and the delay-slot copy serves the taken path.

To prevent this copy, the slt must not be eligible. Hmm.

What if the slt's operands involve a register that's modified on the fall-through path? The slt uses v1, which IS modified by the negu on the fall-through! So the slt at the target uses the *negated* v1, while the delay-slot copy uses the un-negated v1. Both are correct for their paths.

reorg's condition for stealing from the target: the insn must not be modified on the fall-through path... but v1 IS modified (negu). Hmm, so why did reorg steal it?

Maybe reorg checks `reg_used_between_p` / `reg_set_between_p`... Actually reorg uses `insn_references_resource_p` with the fall-through insns.

Hmm, whatever. Empirically, reorg steals it.

What if the fall-through path modifies MORE registers, so the steal is unsafe? E.g., if the negu also touched s1... no.

Hmm, what if the abs is `iVar4 = -iVar4` and the max uses iVar4 — that's the current setup.

What if I make the max use a DIFFERENT variable that's not modified? E.g.:
```
if (iVar4 < 0) iVar4 = -iVar4;
```
Then max uses iVar4 (modified). reorg still steals.

Hmm, what if the max is `if (iVar5 < iVar4) iVar5 = iVar4;` — the slt uses iVar5 and iVar4. Both... iVar5 isn't modified on the fall-through.

What if I add a modification of iVar5 on the fall-through? No.

OK. Let me try one more: what if the abs block is written so the negu comes AFTER the slt in the RTL? No.

I'll stop. Item 2 stays WALL.

Let me now also double check: for item 2, is `nolau` (score 2, pins kept) a PARTIAL? No — PARTIAL requires score 0.

OK. Let me finalize:
- item 1: WALL best 14
- item 2: WALL best 31
- item 3: WALL best 22
- item 4: WALL best 22

Hmm, wait. For item 1, best should be the lowest score of a LEVER-FREE body = 14 (p14). ✓.
For item 2, best = 31 (perm_1432). But nolau (score 2) is NOT lever-free (keeps the pins). So best = 31. ✓.
For item 3, best = 22. ✓
For item 4, best = 22. ✓

Let me now write the moves line for item 4, update item 2's tries (45→58), and write the log.

Actually, let me reconsider whether to spend more time cracking. The session has been ~1.5h. The task is a singleton crack shard; walling all 4 is a legitimate outcome if the evidence is solid. But let me do one more creative pass on item 1, which has the smallest residual (a pure register swap).

Item 1: base (r72, refs 8, live 158, pri 1518) vs mode (r73, refs 5, live 83, pri 1204). Need mode > base.

Idea: what if `mode` is declared as a `s16`? Then the comparisons `mode >= 0` and `mode == 0` would need sign-extension... Actually mode holds -1 and 0. If mode were s16, `mode = -1` stores -1 as HImode; `mode >= 0` compares HImode. The target's `li s3,-1` / `bltz s3` / `bnez s3` — those are word ops. A s16 mode would still use the same regs but maybe `sh` for stores? No stores. Hmm, `mode` is passed to CdReadRequest as an s32 arg — a sign extension would be needed (sll/sra). The target has `move a2,s3` directly. So mode is s32.

Hmm.

Idea: What if `base`'s live length could be shortened? base's last use is the final `if (mode == 0 && (res & 1))` block. What if I move that block earlier? No.

Idea: What if base is used in a way that... 

Hmm, OK. Let me try one thing for item 1: what if `mode` gets 2 extra refs from a construct that survives to .lreg but produces no extra final insn? For example, a `switch(mode)` with cases? The target doesn't have one.

Hmm.

Actually — here's a thought: the allocno pri uses `allocno_n_refs` which is `reg_n_refs`. What if `mode` is referenced in a NOTE or a REG_DEAD? No.

OK, item 1 is a wall.

Let me finalize. Write the moves line for item 4, update item 2's tries, write the log, run chk.sh.

Let me do the moves line.
