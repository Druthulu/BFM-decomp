---
ts: 2026-11-06T10:03:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PeYqEmW8OEkdft4DkZKA
---
In the ORIG (matching) body: r74 conflicts v1,a0,s0,sp; **prefers v0**. So t is r74, conflicts v1 (because tb is pinned to v1!) and prefers v0 (copy preference from something). So t gets v0.

In the lever-free body: r74 conflicts v0,a0,sp; **no prefers**. So t loses its copy preference for v0 and conflicts v0 instead.

The "prefers v0" copy preference comes from a move/copy involving v0. In the orig, the pin tb=$3 means... hmm, t prefers v0. Where does the preference come from? Probably the value `t` is used in `sh t,6(s0)` and `addiu v0,t,-8` — the addiu's destination is v0! So t has a copy preference to v0 because the addiu produces into v0 (a hard reg output). In global-alloc, when an allocno is used in an insn that also defines a hard reg, it gets a preference for that hard reg (via `set_preference`).

In the lever-free body, the addiu output is not v0 anymore (it's whatever). Hmm, in the nopin code, line 59 `addiu v0,v1,-8` — the addiu destination IS v0. So why no preference? Because the addiu output in lever-free is a pseudo, not a hard reg? In the orig, maybe the addiu's output was forced to v0 by the t-8 being used as the call arg? no.

Wait: in the orig, the final `sh v0,10(s0)` uses v0. The addiu writes v0. The preference "prefers v0" for r74 (t) arises because t is copied to/from v0? Actually set_preference is called in global-alloc when an allocno is in an insn that references a hard reg, giving a preference (not copy pref). The dump shows "prefers v0" = normal preference.

In orig, t is used at `addiu v0,t,-8` where v0 is a hard reg output → t gets preference for v0. In lever-free, same instruction exists (`addiu v0,v1,-8`), so t should still prefer v0. Unless in lever-free, that addiu's destination is a PSEUDO (not hard v0) because the result goes to a pseudo then stored.

Ah, that's it: in the orig (matching), the `t - 8` result is computed directly into v0 (hard reg) because the sh's source... hmm, no.

Actually in the lever-free nopin code, line 59 `addiu v0,v1,-8` — v0 is hard. So t (v1) is used with hard v0 output. Preference should be set. But the table shows r74 "conflicts v0,a0,sp" without "prefers v0".

The difference: in orig, r74 conflicts v1 (tb pinned to v1), a0, s0, sp. In lever-free, r74 conflicts v0,a0,sp. So v0 is live at r74's birth in lever-free. What's in v0? Perhaps another allocno that in orig went to v1 or elsewhere. Since tb is now free, tb's qty... but tb is r75 (pri 2500). If r75 got v0 and overlaps r74, then r74 conflicts v0. But r75 is allocated later (lower pri). The conflict set is computed before allocation: "conflicts v0" means v0 is live at r74's start due to hard regs only, not allocnos. Hmm.

Let me look at the .greg dump around r74 to see the exact conflict list and preferences. Search the greg dump.
