---
ts: 2026-11-06T22:47:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wfIa5HSTNUodF2oICs3c
---
w0: r77 (u6) prefers 16 (s0) — from the tie with s1ang (r75 in s0). r78 (iVar4) prefers 5 (a1). r79 (q) prefers 5 (a1). r80 (?) prefers 2 (v0).

So iVar4 (r78) and q (r79) prefer a1. Where from?

Chain: insn 100 `(set r78 (minus r76 r77))` with REG_DEAD r76 (u5) and r77 (u6). expand_preferences: dest r78, dying srcs r76 (allocno) and r77 (allocno). It merges r78's prefs with r76's and r77's. r77 prefers s0. r76 (u5)? no prefs. So r78 should prefer s0 (from r77), not a1.

Hmm, unless there's a REG_DEAD for a hard reg... no, the condition requires the dying reg to be an allocno.

Hmm, what if the merge happens at a DIFFERENT insn: `(set r78 (div r77 r74))` is a parallel. Hmm.

Wait — maybe expand_preferences iterates ALL insns, and at insn 112 `(set r78 (const_int 1))` no. At insn 125 `(set r78 (const_int -1))` no.

Hmm, maybe the a1 preference comes from the *first* div (insn 108 parallel): no.

Hold on, maybe it's from `hard_reg_copy_preferences` vs `hard_reg_preferences`? The dump prints `hard_reg_preferences`. 

Let me look at `set_preference` call sites again: only mark_reg_set (line 1348). mark_reg_set is called via note_stores for every set. For a parallel, note_stores calls mark_reg_set for each set? Let me check: `note_stores(PATTERN(insn), mark_reg_set)` — for a parallel, it iterates the vector and calls the function for each set. So for the div parallel, `(set r78 (div ...))` → set_preference(r78, div) → src is a div, not a REG → no. `(set r103 (mod ...))` → no.

For the call insn: `(set $v0 (call ...))` → no.

For insn 6: `(set r74 (reg $a1))` → r74 prefers a1. 

So r74 (d) prefers a1. Now, does any *single_set* insn have a dying src that is an allocno and merge with r74? expand_preferences requires the dest to be an allocno AND the dying src to be an allocno. The div's REG_DEAD r74 is on a parallel (skipped).

Hmm, unless the div isn't a parallel at expand_preferences time. Wait, expand_preferences is called in global_alloc, which runs after... the divmodsi4 pattern is a parallel in the RTL. Hmm.

Wait, maybe I should check whether the div is a single_set: `single_set` returns the SET if there's exactly one non-clobber set. The parallel has 2 sets (div and mod) → returns 0. So skipped.

Hmm.

Let me look at the *call* insn: `(call_insn (parallel [(set $v0 (call...)) (clobber $ra)]))`. single_set returns the v0 set? The parallel has one set + one clobber → single_set returns the set (clobbers ignored). So dest = $v0 (hard), src = call → set_preference($v0, call) → no.

Hmm.

OK, let me try yet another approach: maybe the preference is set by `record_one_conflict`/`mark_reg_clobber`? Let me grep for other preference-setting in global.c: `hard_reg_preferences` assignments.

Actually, maybe `expand_preferences` DOES propagate through the div because the REG_DEAD r74 is on a set... no.

Let me just test empirically whether the a1 preference matters: what if I add `d` as a parameter reuse (w4) — w4's greg also showed r77 prefers a1. So it's robust.

New idea: what if I make the divisor d's pseudo NOT set from $a1 at entry, so r74 has no a1 preference, breaking the chain? E.g., `d = arg1` but arg1 is already copied... Or `d = (s16)arg1` at the top (the cast at entry) — then the sll at entry (wrong order).

Hmm.

OK, let me step WAY back. Time check: I started at 15:26. Let me check the time now.
