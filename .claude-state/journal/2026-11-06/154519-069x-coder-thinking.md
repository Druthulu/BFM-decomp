---
ts: 2026-11-06T22:45:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jw2b6XK3CIA44PceCEbu
---
Interesting! In the w6 greg dump, the insns already show hard regs (this is after global-alloc). Insn 6: `(set (reg/v:SI 16 s0) (reg:SI 5 a1))` — d = arg1, and d is already $s0! Wait, the greg dump is after global-alloc, so the pseudos are replaced by hard regs. So `reg/v:SI 16 s0` is d. OK.

So the greg dump's insns show the final assignment. The preferences were computed before.

Let me look at the lreg dump (before global-alloc) for the insns. Actually, the preference for r77 (iVar4) on a1 — maybe it comes from an insn where r77 is copied to a hard reg. Let me look at the lreg dump around insn 81-100 for any `(set (reg:SI X) (reg/v:SI 77))`.

Hmm, wait. Actually, maybe the preference comes from the *call argument*: `subu $a1, $v1, $a1` sets $a1 from a minus of hard regs → no.

Let me look at the w6 lreg dump's full insn list between the call and the div, looking for hard-reg sets involving pseudos.

Alternatively — maybe I should check the lreg dump for "5 a1" as a SET DEST with a pseudo SRC.

Let me grep the lreg dump section for "set (reg:SI 5 a1)".
