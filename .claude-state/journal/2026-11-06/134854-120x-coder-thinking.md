---
ts: 2026-11-06T20:48:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oVe7KgaKzZRpB9NgSx8S
---
Combine deleted insn 92 (the copy) and replaced all uses of 87 with 72 (a0). So it's COMBINE's copy propagation (combine merges a single-use copy into its uses).

So the wall tag `combine-copy-merge` fits better ("combine merges a reg copy the target keeps").

Can we prevent combine from merging? Combine's `try_combine` propagates a copy if the source reg is not modified between and the destination has a single use... Actually combine handles 2-3 insn windows: `set r87 = r72` followed by a use in the next insn. For each use, combine can substitute.

To prevent it, the copy must have multiple uses (combine's `reg_n_sets`/`reg_n_refs`? try_combine requires the copy's dest to be used only in the combined insn and not elsewhere). If `ent` has multiple uses spread out, combine still merges each? Combine merges a copy into ONE following insn if that's the only use (`if (reg_n_refs[regno] != 1) ...`?). Let me check combine.c's condition.

Actually, in combine.c `try_combine`, there's a check `if (! use_crosses_set_p ...)` and `n_occurrences`. Hmm.

Let me grep for the copy-merge logic: `combine` has `subst` and `try_combine` with `i2src`... The relevant condition might be `if (num_sign_bit_copies...` or `if (GET_CODE (i2src) == REG && ...)`.

Actually the pattern: combine merges `i2 = set (reg A) (reg B)` into `i3` if A is used once in i3 and not used elsewhere (`dead_or_set_p`/`reg_dead`). If ent (87) has many uses, combine can't merge the copy into all of them — but it might merge it into the *first* use, leaving the copy for the rest... Combine's `try_combine` requires that the destination of i2 is dead after i3 (or only used there).

Hmm, so if `ent` has many uses, combine shouldn't merge the copy at all. But the dump shows 87 is gone entirely. That means combine replaced ALL uses and deleted the copy — that's not typical try_combine (which handles 2-3 insns). Unless it's the `reg_dead` + `subst` in `try_combine` with a "three-insn" combination.

Wait — maybe it's not combine. Let me check the .cse2 dump (the second cse pass, after loop). cse2 might propagate copies. Let me check .cse2 for 87.

Actually, I checked .combine and found no 87. Let me check .cse2 (which runs before combine).

Let me check .cse2.
