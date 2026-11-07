---
ts: 2026-11-06T06:12:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eZktiqbE3gOnxirQRHbp
---
No s0 in the .lreg section at all. So the conflict with hard reg 16 isn't from a hard-reg use... but wait, maybe my section range is wrong (2316-3600 may not cover the function). Let me check where the next ";; Function" starts after 2316.

Also possible: the conflict list includes hard regs that are "live at entry" — global.c's global_conflicts() marks all hard regs live at function entry? Let me look at global_conflicts.

Actually, hmm! Important: in global.c, before allocation, `global_conflicts()` initializes `hard_regs_live` for the first insn with `regs_live_at` ... plus there's this: "If a hard register is used as a value in an insn, it conflicts". 

Let me just check the source quickly for how hard reg conflicts are recorded, particularly for callee-saved regs.

Alternatively — maybe I should stop the deep dive and test empirically: does the param get $16 if I make it conflict-free? Let me test a hypothesis: the conflict with 16 comes from `D_801202A0`? no...

Actually — WAIT. I bet the conflict with $16 comes from the *pin in the ORIGINAL src file*, which is still in the TU at the src level? No, we replaced the body.

Hmm, but hold on: does the spliced TU still have the original function elsewhere? No.

Another idea: `Hard regs used: 2 3 4 5 16 17 18 19 20 21 31` — these are after allocation.

Let me check global.c for how it handles the initial hard_regs_live: search for "hard_regs_live" init.
