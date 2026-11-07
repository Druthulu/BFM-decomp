---
ts: 2026-11-06T06:39:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8sBdm4FGiDpbgYmVGmve
---
v_s16t uses `lhu` instead of `lh` and adds sll/sra (sign extension) — because t is s16, the load of unkA becomes lhu + sign extend. Not the right path (the target has `lh`).

The base candidate (s32 t) gives 17 with the v0/v1 swap.

So the only real difference is: t in v1 vs v0 (the target's t is v0).

Given my analysis (t conflicts with the load dest in $2), the pin is required.

Hmm, but wait. Let me verify the conflict claim by looking at my candidate's conflicts for r73: "conflicts v0,sp". Yes.

But hold on — the target's t is a hard reg $2 and the load is `lw $2,D_801D0A3C($2)`. In gcc's RTL, the load's dest pseudo would be a different pseudo (allocated to $2), and t (hard reg $2) is live at that insn. gcc does NOT check conflicts for hard-reg variables, so it's fine.

For plain C, t and the dest pseudo are both pseudos → conflict → different regs.

So the target's sequence requires t in $2 while a *different* pseudo (the load dest) is also $2 at the same insn. In plain C that's a hard conflict... unless the load dest and t are the same pseudo (my v_self idea), which gave 19.

Let me look at v_self's residual — maybe it's closer in the tail but worse elsewhere.

Actually, maybe with v_self + s16? Hmm.

Let me look at v_self's residual.
