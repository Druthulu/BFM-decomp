---
ts: 2026-11-06T22:45:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QIMBwNRtjjATruKjmtdb
---
So a preference is set when a pseudo is set from a hard reg: `dest = src` where dest is a pseudo and src is a hard reg → the pseudo prefers that hard reg.

Which insn sets iVar4 (r77) from a hard reg $a1? Let me find it. The lreg dump at insn 81: r77 = r76 - r75. Not a hard reg. But maybe there's another insn: after cse/combine, some `r77 = $a1` copy?

Wait — maybe iVar4's preference comes from a *different* insn where the pseudo is the SRC and the dest is a hard reg: `$a1 = r77`? Then set_preference is called with dest=$a1 (hard) and src=r77 (pseudo) → the pseudo r77 gets a preference for $a1. Yes! Line 1582: if dest is a hard reg and src is a global pseudo, the pseudo prefers the dest hard reg.

So some insn does `$a1 = iVar4` or `$a1 = <expr with r77>`. Hmm, when? The call argument `subu $5,$3,$5` sets $a1 from the ratan2 arg — but that's before iVar4.

Hmm, wait: mark_reg_set is called for the dest of each set. For `(set (reg:SI 5 a1) (minus ...))`, dest=$a1, src=minus → set_preference($a1, minus) → src is not a REG → return. So no.

Unless the src is a pseudo: `(set (reg $a1) (reg r77))` — a move. Is there such an insn? Maybe from the call argument setup: the ratan2 second argument is `D_80126CB4 - *(s16 *)(arg0 + 6)`, computed into $a1. That's a minus, not a reg.

Hmm. What about the div? `(set (reg $v0) (reg r78))`? The move q→v0. That's a pseudo-to-pseudo move.

Let me search the w6 lreg dump for "set (reg:SI 5 a1)" or "reg:SI 5".

Actually, maybe the preference comes from the *epilogue*: `lw $17,20($sp)` etc. No.

Let me grep the w6 greg dump insns for "a1" sets. The greg dump shows the insns after global-alloc (with hard regs). Let me grep for "reg:SI 5 a1)" as a set dest.
