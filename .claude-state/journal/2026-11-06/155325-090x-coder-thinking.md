---
ts: 2026-11-06T22:53:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6DFduYqj7WLYQkxfO6lG
---
In w10: r72 (arg0) = $s0 (local, 4/8, crosses a call) — so arg0 took $s0! And d (r74) conflicts s0 → $s1. Also r75 (9/15, pri 18000) is... the mask-in-place s1ang? 9 refs/15. Hmm.

So in w10, the reorder made arg0 cross the call and take $s0. Bad.

OK. Let me now think about the WALL. But first, let me try a few more variants quickly, including some from the moves.md catalog (C0505: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse).

Let me try:
- w18: w0 with `s32 d = arg1;` init at decl.
- w19: w0 with the do-while around the div block.
- w20: w0 with `u6` declared inside? no.
- w21: w0 with the cast as `d = (s16)d;` inside an if(0)? no.
- w22: w0 with the mask-in-place on s1ang but the arms using u6 (u6 kept).
- w23: w6 with `d` init at decl.
- w24: w6 with the declarations reordered (s1ang before d).
- w25: w6 with `q`/`t` scoped.

Let me also try the "pointer reuse" idea: `s32 p = *(s32*)(arg0+0x20); s1ang = *(s16*)(p+0x12);`.

Let me batch these.

Actually, let me think about w22 more: keep u6 for the compare and arms, but ALSO reassign s1ang to globalise the raw load:
```
s1ang = *(s16 *)(...);
u5 = ...;
do { d = (s16)d; } while (0);
u6 = s1ang & 0xFFF;
s1ang = u6;
if (u6 == u5) return 0;
iVar4 = u5 - u6;
if (iVar4 > 0x800) { t = s1ang + 0x1000; iVar4 = u5 - t; }
...
```
The raw load is used by u6's and (block 0). s1ang is a copy of u6, used in the arms. The raw load pseudo is local. Hmm, no globalisation of the raw.

What if instead:
```
u6 = s1ang & 0xFFF;
s1ang = s1ang;   // no-op
```
No.

OK here's one more idea: use the raw s1ang in the arms via a *comparison* that's already there? No.

Let me just run the batch.

Actually, let me reconsider the problem once more. The target's allocation: d=$s0, raw load=$s1, u6=$s1, u5=$a0, iVar4=$v1. 

The mask-in-place gives d=$s0, s1ang(masked)=$s1, u5=$v1, iVar4=$a1. The u5/iVar4 shift is due to the a1 preference on iVar4.

What if I can break the a1 preference? The preference comes from `d = arg1` (r74 = $a1). In the target, d is pinned, so no preference. Without the pin, d = a copy from $a1 → preference a1 → propagates to iVar4.

What if `d` is not a copy from arg1 but from a *memory* or another source? E.g., `d = arg1; ` is required. What if we write `d = arg1; d = d;`? Hmm.

What if d is initialized from arg1 via a cast that goes through a temp? `d = (s32)arg1;` — no-op.

Hmm, what if we swap: use arg1 directly (w4)? w4 still had the preference (r77 prefers a1). Where from? In w4, the parameter arg1 is r73 (born in $a1). Maybe the parameter pseudo's preference for $a1 comes from the function prologue (the parameter is in $a1). set_preference isn't called for parameters... but maybe `hard_reg_full_preferences` for the parameter comes from the initial assignment.

Hmm, in w4's greg: "73 conflicts: ..." no preferences. But r77 prefers a1. So the a1 preference on r77 doesn't come from the parameter.

Let me find the actual source of the a1 preference by instrumenting. I could add a debug print? No, can't modify gcc.

Alternatively, let me look at the expand_preferences chain in w6: the a1 preference must come from some allocno's preference set by set_preference (a set from a hard reg). The only such insn in our function is `(set r74 (reg $a1))` (d = arg1). So r74 prefers a1. Then expand_preferences merges r74's prefs into any allocno connected via a REG_DEAD merge. The div's REG_DEAD r74 is on a parallel → skipped. So how does r77 get it?

Unless the div ISN'T a parallel in the RTL at expand_preferences time... it is.

Wait — maybe there's a `movsi` copy of d created by the *cast*: `d = (s16)d` becomes `sll temp, d, 16; sra d, temp, 16`. No copy.

Hmm, what about the `q = iVar4 / d` — the div. No.

Let me look at the insns where r74 is a REG_DEAD... only the divs (parallels). So expand_preferences can't propagate r74's a1.

So the a1 preference on r77 comes from ANOTHER set-from-hard-reg insn. Which insns set a pseudo from a hard reg? Let me search the w6 lreg dump for `(set (reg/v:SI N) (reg:SI HARD))`. Let me grep for `(reg:SI [0-9]+ [a-z0-9]+)))` patterns... Actually, let me grep for "set (reg" followed by a hard reg on the next line.

Let me search the w6 lreg function section for `(set (reg/v:SI` lines followed by `(reg:SI` with a hard reg name.
