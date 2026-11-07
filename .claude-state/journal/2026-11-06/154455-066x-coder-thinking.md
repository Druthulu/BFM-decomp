---
ts: 2026-11-06T22:44:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tXlxcuGadBhpjEdFLG5l
---
Interesting! In w6:
- insn 81: r77 = r76 - r75 (iVar4 = u5 - s1ang)
- insn 90: r77 = r76 - r79 (iVar4 = u5 - t) where t = r79
- insn 100: r77 = r76 - r79
- insn 110: r78 = div(r77, r74) [q]
- insn 112: r78 = 1
- insn 125: r78 = -1
- insn 61: r77 = r75 & 4095 (u6 = s1ang & 0xFFF)?? 

Wait, insn 61 sets r77 = r75 & 4095 — but r77 is also iVar4 (insn 81)! That means the SAME pseudo r77 is used for both u6 and iVar4?! That can't be right — they're different variables. Unless the register allocator reuses the same pseudo after the value dies.

Oh! This is the lreg dump — the pseudo numbers are after *local-alloc* and possibly after some register renumbering? No... Actually, the lreg dump shows the RTL after local-alloc, where local-alloc has assigned hard regs to some pseudos, but the global pseudos keep their numbers. Hmm, but r77 can't be both u6 and iVar4.

Wait, maybe u6 = r77 at insn 61, and iVar4 = r77 at insn 81 — but r77 was redefined. Let me check the live ranges: insn 61 (block 0) defines r77 = u6; insn 81 (block 2) defines r77 = iVar4. If u6 dies before insn 81, the pseudo can be reused. But GCC doesn't reuse pseudo numbers unless it's the same pseudo (e.g., via cse/combine).

Hmm, actually, in w6 the source uses `s1ang` for the arms, so `u6` doesn't exist. Let me re-read w6.c: it has no u6; it does `s1ang = s1ang & 0xFFF;` then uses s1ang. So r75 = s1ang, r77 = iVar4. But insn 61 sets r77 = r75 & 4095 — that would be iVar4?? No...

OH WAIT. I bet the lreg dump at line 679 is from a different point — the grep -A3 matched a different function section? No, the +700 lines window. Hmm, line 679 in the window. The insn numbering restarts? The window starts at the function header; 700 lines covers multiple functions? The function is ~200 lines, so 700 lines includes the next functions. Line 679 might be in func_8012BA10 or another function! Let me check: the lreg dump has many functions; the +700 window includes the next functions.

So insn 61 at line 679 is a different function. Ignore.

OK so in w6: iVar4 = r77, q = r78, d = r74, u5 = r76, s1ang = r75, t = r79.

Preferences: r77 (iVar4) prefers a1 (5). Where from? Hmm. Let me look for a copy involving r77. Maybe `q = iVar4 / d` produces a div with a copy? No.

Wait, maybe the preference is from the *div* insn: MIPS `div` is a parallel with (div:SI ...) and (mod:SI ...) and a clobber. Hmm, no preference.

Hmm, but the target's r78 (iVar4) has NO preference. The difference between w6 and the target: the source structure (mask-in-place vs u6) and the pin. 

Let me look at w0 (no pin, u6, do-while): "78 preferences: 5" too. So the a1 preference on iVar4 exists in w0, w4, w6, w7 — all lever-free bodies. Only the pinned target lacks it.

So the a1 preference on iVar4 is a consequence of removing the pin (d becomes a pseudo copy of arg1). Let me find the mechanism: d = arg1 → `r74 = $a1` (set_preference on r74 → a1). Then `expand_preferences` merges preferences between a dest and a dying src in a copy. Which copy involves r74? Hmm, r74 (d) is not copied anywhere.

Wait, maybe the preference propagation is via `prune_preferences`: "regs_someone_prefers: a bitmask of hard regs preferred by conflicting registers of lower priority. If possible, we will avoid using these registers." Hmm, that's about avoiding.

Hmm, actually, maybe the a1 preference on iVar4 comes from `hard_reg_copy_preferences` being merged through the div's REG_DEAD. Let me look at the div insn: `(parallel [(set r78 (div r77 r74)) (set r103 (mod r77 r74)) (clobber ...)])`. The REG_DEAD notes on the parallel: r77 and r74 die? At insn 110, `(expr_list:REG_DEAD (reg/v:SI 77) ...)`.

Hmm, expand_preferences looks at `single_set(insn)`: for a parallel with 2 sets, single_set returns 0. So no.

Let me look at the actual preference mechanism differently: maybe `set_preference` is called for insn 112: `r78 = 1` (movsi). SET_SRC is a const → no.

I'm stuck on the mechanism. Let me try an empirical approach: the preference a1 on iVar4 might be avoidable by changing the source so that the copy `d = arg1` isn't a plain copy from $a1. For example, `d = arg1 + 0;`? That would add an instruction. Or initialize d at declaration? Same.

What if d is initialized from arg1 but through a cast: `d = (s16)arg1;` at the top? Then the copy is from a SUBREG? Hmm, that changes the instruction order (the sll at the top).

Hmm, what if we write `d = arg1 & 0xFFFF` or similar? That changes instructions.

Alternatively, what if we avoid the d variable and use arg1 directly (w4)? w4 still had the preference ("77 preferences: 5" for iVar4, r73 = d = arg1 pseudo). In w4, the divisor is the arg1 pseudo (r73), which is a parameter (born in $a1). Does a parameter get a preference? In w4's greg: "73 conflicts: ..." no preferences line for r73. Yet r77 prefers a1. So the a1 preference on iVar4 exists even without a copy from $a1.

Hmm! So where does it come from? Let me look at the w4 greg dump more: r77 preferences: 5, r78 preferences: 5, r79 preferences: 2.

Maybe the preference comes from `record_one_conflict`/`set_preference` for the *call* insn: the call `ratan2` uses $a0 and $a1 (arguments). During the call, r76 (u5) etc. are live. set_preference isn't called for calls (no single set of a reg from a reg).

Hmm, wait: set_preference is called from mark_reg_set with SET_SRC. For a call insn `(set (reg $v0) (call ...))`, SET_SRC is the call → not a reg.

Hmm. What about `subu $4,$3,$4` (the ratan2 arg): sets a hard reg $a0 from r3 and r4. mark_reg_set for hard regs → set_preference($a0, SET_SRC=minus) → no.

Let me look at what `preferences` the dump prints. Maybe it's `hard_reg_full_preferences` which includes propagated ones. The propagation in expand_preferences only merges between copy-connected allocnos. So iVar4 must be copy-connected to something with an a1 preference. The something with an a1 preference: maybe the arg1 pseudo or d.

Let me look for a copy between iVar4 and d... `q = iVar4 / d` — not a copy.

Hmm, what about `t`? In the arms: `t = u6 + 0x1000; iVar4 = u5 - t;`. t is r79? In w6, insn 90: `r77 = r76 - r79` with REG_DEAD r79. So t = r79. r79 prefers v0.

I'm going in circles. Let me try a completely different tactic: since the *target* body (with the pin) scores 0, maybe I can find a real-C move that makes the pin's effect without a pin by studying what the pin does to the RTL. The pin forces d into $s0; the rest follows. The problem is the preferences.

Alternative idea: what if we make d's pseudo get $s0 by giving it a *hard-reg preference* through a copy from a hard reg $s0? No hard reg $s0 is available... except maybe the stack pointer or a return value.

Hmm, what about making the arg1 value pass through a call that returns in $s0? No.

What if we use a global variable's address that's in $s0? No.

OK, let me reconsider: maybe the a1 preference on iVar4 is actually benign and the target's iVar4=$v1 can be achieved by a different .greg order. Let me think: in w6, iVar4 (r77, 30000) is first in .greg and prefers a1 → gets a1. If the preference were pruned (because a1 is preferred by a conflicting lower-priority reg), iVar4 would get v1.

`prune_preferences`: "Compute regs_someone_prefers, a bitmask of the hard registers that are preferred by conflicting registers of lower priority. If possible, we will avoid using these registers." So if a lower-priority conflicting allocno prefers a1, iVar4 avoids a1 → gets v1. 

In w6, which lower-priority allocno conflicts with iVar4 and prefers a1? r78 (17500, prefers a1) — does r78 conflict with r77? "77 conflicts: 74 75 76 77 2 29 64 65 66" — no r78. So no.

Hmm.

Let me look at the target: iVar4 (r78, 30000) has no preference and conflicts 76,77,2,16,29,64,65,66. It gets $v1 (the first free in the alloc order after $a0? The hard reg allocation order for MIPS: $v0,$v1,$a0,... hmm).

Actually, global-alloc's hard reg order is REG_ALLOC_ORDER. For MIPS: $v0=2,$v1=3,$a0=4,$a1=5,$a2=6,$a3=7,$t0=8,... and $s0=16,...

For the target: r78 (iVar4) gets $v1. Why not $v0? Because $v0 is taken by another allocno (r80/r99). And $a0? $a0 might be reserved/pruned. Hmm, the target's u5 = $a0.

For w6: r77 (iVar4) prefers a1 → gets $a1 (preference wins over the order). Then r79 (20000) gets $v0 (prefers v0). r78 (17500, prefers a1) gets $v1? Then d (10000) gets $s0. u5 (7142) gets $a0? But w6's u5 = $v1, not $a0. Hmm, contradiction.

Wait, w6's dispositions: 76 in 3 (u5 = $v1), 77 in 5 (iVar4 = $a1), 78 in 5, 79 in 2. So r78 also in $a1 — two allocnos in $a1? r77 and r78 both in 5 ($a1). That means r78 is allocated $a1 after r77 dies (non-conflicting). OK.

So in w6: r77 → $a1 (preference), r79 → $v0 (preference), r78 → $a1 (after r77 dies? but r78 conflicts 77? "78 conflicts: 78 2 29 64 65 66" — no r77, so they don't conflict; r78 can reuse $a1), d (r74) → $s0, u5 (r76) → $v1 (first free after v0,a1 taken; v1 is free), s1ang (r75) → $s1.

In the target: iVar4 (r78) → $v1 (no preference; $v0 taken by r80, so v1), u5 (r76) → $a0 (v0,v1 taken; a0 free), u6 (r77) → $s1.

So the preference on iVar4 ($a1) is what shifts u5 from $a0 to $v1. If iVar4 had no preference, it'd take $v1, and u5 would take $a0. That matches the target!

So the fix: remove iVar4's preference for $a1. The preference comes from the lever-free body (the pin removal). 

Where does it come from? Let me look at the cse dump or the RTL for a copy setting iVar4 from $a1. Hmm.

OH WAIT. I bet I know: `if (iVar4 >= 0) { q = iVar4 / d; ...}`. The div on MIPS: `div $zero, iVar4, d`. But the *mod* part: `(set (reg 103) (mod ...))` — and then `q`... Hmm.

Alternatively, maybe the preference comes from the *call*: the call clobbers $a1, and iVar4 is live across the call? No, iVar4 is born after the call.

Hmm, let me look at the actual insns between the call and iVar4's birth. Actually, let me use the greg dump to find all insns mentioning $a1 and a pseudo in a set. Let me grep the w6 greg dump for "a1" near "set".

Actually, let me look at set_preference's other call path: mark_reg_set is called via note_stores for every set. For the call insn, the parallel sets $v0 = call. Not a reg src.

Hmm, what about `(insn 6 (set (reg/v:SI 74) (reg:SI 5 a1)))` — d = arg1. This sets a preference for a1 on r74 (d). Then expand_preferences: r74 is the dest of a copy from a hard reg (not an allocno), so no merge.

But then how does r77 (iVar4) get it? Maybe via prune_preferences? Let me read prune_preferences.
