---
ts: 2026-11-06T06:41:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VNsK4X4UI83q3uONBi8l
---
In v_direct, t lands in a0 ($4)! Even worse.

So the allocation of t varies: $3 in base, $4 in direct.

Hmm, in v_direct, t is not used in the tail (no `t = unk2`), so t's live range is only the middle. It got a0.

I need t in $2. Since t (13 refs, live 14, pri 27857) is first in the order, it takes the first free reg. If $2 is free, t gets $2.

In v_direct: t got $4 (a0)! That means $2 and $3 were taken/conflicted. t conflicts with v0? and something took v1.

Hmm.

OK, let me think about what the pin does: the pin `$2` makes t a hard reg. The target's other temps then take v1 etc.

Let me look at the target's allocation: order 76 72 74 — r76 (ST_REGS) first, r72 (a0 param) second, r74 third. The compare temp r88? got v0? From the target asm: `lh $3,D_80126B62` (the compare value in v1) and `slt $3,$3,$2`.

In my base candidate, the compare value (r88) is in v0 and t in v1. So the order: t (27857) first → but t conflicts with v0, so it takes... hmm, if t conflicts only with v0, t should take $3 (v1), and then r88 (the compare) would take $2. That matches mine!

In the target, t is $2 (pinned) and r88 takes $3.

So to get t in $2, the conflict must go. Then t → $2 and r88 → $3. 

So: WHERE does t conflict with v0?

Let me look at the .greg dump conflict line and cross-reference. In the earlier table: "r73 ... conflicts v0,sp". Let me look at the .greg text around it... The conflicts are printed in the .greg dump.

Hmm, but understanding requires knowing which insn. Let me think about global.c's conflict recording: a pseudo conflicts with a hard reg if the hard reg is live when the pseudo is born or vice versa. $2 (v0) is live: at the call insn (clobbered → marked live) and at any `(reg 2)` use.

In the RTL, is there a `(reg 2)` anywhere? The call insn's pattern: `(parallel [(call (mem (reg 98))) (clobber (reg 31))])`. Hmm, no v0.

But wait — global.c marks call-clobbered regs live at CALL insns. If t is live at the call, it conflicts. t dies at insn 90, before the call at 98. So no.

Unless the REG_DEP_ANTI... no.

Hmm, what about `insn 104`: `(set (reg/v:SI 73) (symbol_ref D_801D093C))` — no.

OK — maybe the conflict comes from a *different* reason: `mark_reg_clobber` is called via note_stores on every insn; for insns with `(clobber (reg ...))`. Are there any? The call has clobber ra.

Hmm, what about the pseudo's own class: r73 "GR_REGS or none".

Let me look at the actual .greg conflict text and see if v0 appears for r73 there.

Actually — maybe simpler: the conflict with $2 might be a *false* conflict from the hard-reg variable... no, we removed the pin.

Let me look at the .flow dump's register info... 

Alternatively — empirical: let me test a variant where the tail's `t = unk2` uses a *different variable* (split) — that gave 16. Let me look at that one's conflict/pairs. In v_split, t (middle) and t2 (tail) are separate; the middle t should now not conflict with v0 (since t isn't used at the load).

v_split scored 16, mine 41 insns (target 42) — one insn short.

Let me look at v_split's residual.
