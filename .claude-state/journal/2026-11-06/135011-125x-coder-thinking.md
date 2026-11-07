---
ts: 2026-11-06T20:50:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HhXXBxlwA8oBdYKJ8Lmy
---
This deletes only self-copies (dest regno == src regno). Our copy is `87 = 72` — different regnos.

So the deletion must be combine. Let me check combine.c's `try_combine` conditions more carefully. The key: combine can merge `i2 = copy` into `i3` even when i2dest is used elsewhere, by keeping the set in the merged insn (added_sets_2). But then the merged insn would set 87 too, and the other uses would still use 87 — the dump shows they use 72.

Unless... combine's `subst` in `try_combine` replaces i2dest with i2src in i3 only, and the other uses of 87 remain. But the dump shows them as 72. Hmm.

OH WAIT. Maybe combine processes each use in turn: i2 = copy (insn 92), i3 = insn 101 (first use). After combining, the copy is deleted and the merged insn 101 sets 87 (added_sets_2). Then for the next use (insn 126), combine combines the merged insn? No...

Hmm, but the dump's insn 101 does NOT set 87.

Let me look at the actual .combine dump for insn 99/101/126 to see what they look like. Earlier I saw:
```
(insn 99 97 101 (set (reg:HI 91) (mem ... (plus $fp 18))))
(insn 101 99 104 (set (mem:HI (plus:SI (reg/v:SI 72) (const_int 10))) (reg:HI 91)))
```
So 101 uses 72, and no 87 set. So combine replaced 87 with 72 in 101 and deleted the copy. That's a *copy propagation* of the whole pseudo.

This is combine's `try_combine` in the "i2 is a copy, i3 uses it, and i2dest is dead after i3" case. But 87 is used later... UNLESS combine processes the uses in REVERSE order? `combine_instructions` iterates forward over insns; for each insn (i3), it tries to combine with the previous insn(s). So the first use processed is 101 (i3=101, i2=92). `dead_or_set_p (i3=101, i2dest=87)`? The check is whether 87 is set or dead in i3 — `dead_or_set_p` looks at REG_DEAD notes or a set in the insn. 87 is not set in 101 and has no REG_DEAD note there. So added_sets_2 = 1.

Hmm, but then the merged pattern should include the set of 87. Let me look at combine's code around 1588 (`newpat = subst (PATTERN (i3), i2dest, i2src, ...)`) and how added_sets_2 is used.

Maybe combine builds `newpat` and then at the end, if `added_sets_2`, it adds `(set i2dest i2src)` to the new pattern. Let me look at the code after the subst.

Actually, there's `combine_instructions`'s "if (added_sets_2) ... add the set". Hmm.

Alternatively, maybe the mechanism is `i2dest` was replaced because `reg_n_sets[i2dest] == 1` and the pseudo is a "user var"? Line 1764: `reg_n_sets[REGNO (i2dest)] == 1 && ! added_sets_2 && ! REG_USERVAR_P (i2dest)`.

`REG_USERVAR_P (i2dest)`! The `ent` pseudo is a user variable (a VAR_DECL). If `REG_USERVAR_P` is set, the condition fails and `ni2dest` stays as the original... hmm.

Let me look at the code at 1740-1800.
