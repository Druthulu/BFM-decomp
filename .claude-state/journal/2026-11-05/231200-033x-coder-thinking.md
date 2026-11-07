---
ts: 2026-11-06T06:12:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OQe8jA7S1FnL4wmasmnb
---
No asm/register left in the body. So where does the conflict with hard reg 16 come from?

Hmm — maybe from the TU-level: this function is called elsewhere, but that doesn't matter.

Wait, maybe the conflicts line means: "72 conflicts: 72 73 74 75 76 77 78 80 134 140 167 2 3 4 5 16 29" — the first entries are allocnos 72..167, then hard regs 2,3,4,5,16,29. $2,$3 = v0,v1 (call-clobbered, all call-crossing allocnos conflict), $4,$5 = a0,a1 (params hard regs), $29 = sp, $16 = s0.

Why would r72 conflict with $16? In global.c, `global_conflicts` marks hard regs live at the same time as the allocno. $16 (s0) is callee-saved: it is live throughout the function if used. But before allocation, no pseudo is in $16... unless a hard reg is live because the function is entered with s0 live? No, s0 is callee-saved: on entry, s0 holds the caller's value and must be preserved — gcc treats callee-saved regs as live at entry? Yes! In gcc, for a function, all callee-saved registers are considered live at the start (their incoming values must be preserved) — actually the prologue saves them if used. Hmm, global.c's conflicts with hard regs consider hard regs live at points.

Hmm, but then EVERY allocno crossing the whole function would conflict with $16-$23, making callee-saved unusable. Not the case.

Let me look at global_conflicts code: it uses `hard_regs_live` computed by scanning the insns. A hard reg becomes live when it's set and dies at REG_DEAD. Since s0 isn't set before allocation (no pin), it wouldn't be live.

Unless... there IS a hard reg 16 in the RTL: a call's CLOBBER? No.

Hmm, let me grep the pre-allocation RTL. The .greg dump is post-allocation. The .lreg dump is pre-global-allocation. Let me grep the .lreg dump for "16 s0" within the function.
