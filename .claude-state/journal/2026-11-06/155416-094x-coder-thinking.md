---
ts: 2026-11-06T22:54:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hd1kTJsZtuCsIUAFoqiq
---
It prints `hard_reg_preferences[i]`. So r77's allocno has the a1 bit set. It must come from set_preference or expand_preferences.

Let me look at expand_preferences again: it merges `hard_reg_preferences[a1] |= hard_reg_preferences[a2]` for any single_set insn whose dest is an allocno and a dying REG src is an allocno, with no conflict.

For r77 (iVar4), the sets are insns 81, 90, 100. At insn 90: dest r77, dying r79. Merge both ways.
At insn 100: dest r77, dying r76 and r79. Merge r77↔r76, r77↔r79.

r76 (u5): `(set r76 (and r98 4095))` with REG_DEAD r98. At insn 52: dest r76, dying r98 (local → reg_allocno[r98] = -1) → skip.

So r76 has no prefs (dump confirms no line for 76).

Hmm. So where does r77 get a1?

OH WAIT. Maybe expand_preferences iterates in insn order and merges iteratively. r79 gets prefs from somewhere, then r77 from r79. The dump says r79 prefers 2 (v0). If r77 got v0 from r79, it would show v0, not a1. Unless the merge is asymmetric due to the CONFLICT check order.

Hmm, at insn 90: dest r77, dying r79. The check `!CONFLICT(a_dest, a_src)` — r77 conflicts r79? "77 conflicts: 74 75 76 77 2 29 64 65 66" — no 79. And "79 conflicts: 74 75 76 79 29" — no 77. So the merge happens: r77 gets r79's prefs (v0) and r79 gets r77's.

Then at insn 100: dest r77, dying r76, r79. Merge again.

So r77 should get v0 (from r79). But the dump says a1. Unless r79's prefs at expand_preferences time were a1 (not v0)? The dump is printed AFTER prune_preferences, which modifies the prefs. Hmm, prune_preferences removes prefs that conflict. So the dump shows the pruned prefs.

Hmm, the dump is called at the END of global_alloc? Let me check where dump_global_regs is called. If after allocation, the prefs shown are pruned.

OK, this is extremely deep. Let me stop and accept the empirical situation.

Let me now focus on reaching 30 tries and recording a solid WALL. But before that, let me try 2-3 more promising ideas:

Idea: The a1 preference on iVar4 causes the shift. What if we prevent r74 (d) from being set from $a1 by using a different source order: `d = arg1;` is required for the move at entry. But what if we write `d = arg1; ` and then also use arg1... no.

What if we make `d` a `u32`? The cast `d = (s16)d` on a u32... the RTL might differ.

What if `d` is `s16`? `s16 d; d = arg1;` — then the move and the sll/sra differ.

Let me try a few type variants: `u32 d`, `s16 d`, `s1ang` as u32.

Also, the C0505 catalog: `&&`/`||` folds, loop shape. Let me try `if (iVar4 >= 0)` vs `if (0 <= iVar4)`, and the arms.

Honestly, the probability of cracking is low. Let me do a final batch of ~15 tries covering plausible moves, then write the WALL.

Batch:
- w17: w0 with `s32 d = arg1;`
- w18: w0 with `u32 d;`
- w19: w0 with `s16 d;` — careful: `d = arg1` truncates; the div uses d. Semantically maybe wrong but the code must match; if it changes the insns it won't match anyway.
- w20: w0 + div block do-while.
- w21: w6 + `s32 d = arg1;`
- w22: w6 with declarations reordered (s1ang before d).
- w23: w6 with the pointer reuse `s32 p = *(s32*)(arg0+0x20); s1ang = *(s16*)(p+0x12);`
- w24: w6 with `u32 d`.
- w25: w0 with `if (0 <= iVar4)`.
- w26: w0 with `iVar4 = u5 - u6;` moved after the compare? same.
- w27: w6 with the arms using `(s1ang + 0x1000)` etc. (already).
- w28: w6 with `t` scoped: `{ s32 t; ... }`.

Let me create them. But I should be careful with semantic changes: the score is against the target; if the insns differ, it'll be a low score, not a MATCH.

Let me write a batch.
