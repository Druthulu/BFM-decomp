---
ts: 2026-11-06T20:49:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cb4wWq6vS06GCuArhB5i
---
Combine merges i2 (the copy) into i3 (the first use) when the copy's dest dies in i3 (`dead_or_set_p`). But here the copy's dest is used MANY times, so it shouldn't die in i3...

Unless combine's `added_sets_2` keeps the copy: `added_sets_2 = ! dead_or_set_p (i3, i2dest)` → since 87 is not dead after i3, added_sets_2 = 1 → the merged insn still sets 87 (`ni2dest`) and the copy insn i2 is deleted, replaced by the merged i3 which sets both. So the copy insn is deleted but the value is recomputed in the merged insn.

Hmm, but the dump shows the uses of 87 replaced by 72 everywhere. So it's not just one merge.

Wait, maybe what happened is different: combine's `try_combine` merged the copy into i3 and then `SUBST (regno_reg_rtx[REGNO (i2dest)], ni2dest)` — line 1795! That substitutes the register in the *global* rtx array? That looks like a "copy propagation" of the pseudo: `SUBST (regno_reg_rtx[REGNO (i2dest)], ni2dest)` replaces the pseudo's register object with ni2dest. Hmm, that's for the split case.

Let me look at 1780-1800.

Actually, the key question for a crack: how to prevent combine from merging the copy. The condition at line 1763-1765: `(REGNO (i2dest) < FIRST_PSEUDO_REGISTER || (reg_n_sets[REGNO (i2dest)] == 1 && ! added_sets_2 && ! REG_USERVAR_P (i2dest)))`.

Hmm, that's for a different case (newpat's dest).

Let me look at the actual combine dump for insn 92's deletion context — maybe there's a note in the dump showing which combination did it. The .combine dump may include "deleted insn" notes. Let me search the combine dump for "NOTE_INSN_DELETED" around insn 92 — it's a note 92.

Actually, since the .combine dump shows `(note 92 90 94 "" NOTE_INSN_DELETED)`, and insn 99 etc. use 72, combine did a global substitution. This is likely combine's "i2dest = i3src" case: the copy `87 = 72` followed by... hmm.

Let me look at the combine dump before/after: is there a REG_EQUAL note or something?

Alternatively, maybe it's the `combine_instructions` "try_combine (i3, i2, i1)" where i1 = insn 88 (the store `sh v0,6(s0)`) — no, i1 must feed i2.

Hmm, let me look at the combine dump around insn 92 and see the preceding insns (the copy was between note 90 and note 94). The dump shows `(note 92 90 94 "" NOTE_INSN_DELETED)` where the copy was. And the first use (insn 101) now uses 72.

So combine merged the copy into i3 = insn 99? i3 = `(set (reg:HI 91) (mem ...))` — doesn't use 87.

Wait, the first use of 87 is insn 101 `(set (mem:HI (plus (reg/v:SI 87) (const 10))) (reg:HI 91))`. Combine i2 = insn 92 (copy 87=72), i3 = insn 101. Merging: `(set (mem (plus 72 10)) 91)` and since 87 is not dead, the merged insn would also set 87 = 72... but the dump of insn 101 shows just the mem store using 72, no extra set.

Hmm, but the dump at .combine shows insn 101 as `(set (mem:HI (plus:SI (reg/v:SI 72) (const_int 10))) (reg:HI 91))` — no 87 set. And `added_sets_2` should have kept the 87 set. Unless `dead_or_set_p (i3, i2dest)` was TRUE — i.e., combine thought 87 dies in i3? That would be wrong if 87 is used later... unless the uses after were already rewritten by earlier combinations (combine processes insns in order and can propagate the copy into each use, one at a time, deleting the copy when the last use is handled? no).

Hmm, combine's `try_combine` with i2 = copy and i3 = use: after merging, it does `undo_all` or accepts. If accepted, the copy insn is deleted. For the other uses, they'd still reference 87 (which is now undefined!). That can't be.

Unless combine's `subst` for the whole function... 

Wait, maybe the merge order is reversed: combine processes from the end backwards, merging the copy into the LAST use first, then the next... Actually `combine_instructions` iterates insns forward, trying to combine each insn with its predecessors.

Let me look at the .combine dump more carefully: maybe all the uses show 72 because the dump was printed after the *final* combine, and combine's `SUBST (regno_reg_rtx[REGNO (i2dest)], ni2dest)` at line 1795 replaces the pseudo's reg rtx globally — but that's only for the split case.

Hmm, line 1794-1795:
```
if (REGNO (i2dest) >= FIRST_PSEUDO_REGISTER)
    SUBST (regno_reg_rtx[REGNO (i2dest)], ni2dest);
```
This is in the branch where `newpat` was split. Not our case.

OK, let me take a different approach: test empirically whether a second use of ent that is NOT a memory base (e.g., a scalar use) prevents the merge. If combine's merge requires the uses to be in combinable patterns... 

Hmm, this is deep. Let me step back: the practical question is whether a plain-C variant can keep the copy. I've tried many. The empirical evidence is that combine propagates it.

Let me look at the actual combine dump for insn 92 to see if there's a comment. Let me print the combine dump region around insn 92 with more context.
