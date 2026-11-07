---
ts: 2026-11-06T21:40:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8vvoSyyy5F5AJ0XqJ4ZJ
---
No s0 uses in func_8012B8E4's lreg RTL?! That means local-alloc didn't assign s0 to anything in this function. But the alloc table said r75 in 16 (s0). Hmm, maybe r75 is in a different block and the .lreg RTL doesn't show it because it's dead/deleted?

Wait, maybe I'm misreading. Let me grep for "s0" generally in that range.

Actually, the `.lreg` dump is after local-alloc but before global-alloc. The register 75 in 16 line is at section line 98 (22404+98 = 22502). Let me look at the RTL around there? No, line 98 is in the candidate list, and the RTL starts after.

Hmm, the RTL in the func section (22404-22846) doesn't use s0. So where does the conflict "74 conflicts ... 16 ..." come from? Maybe from the global-alloc's view of *other* functions? No, per function.

Wait — the conflict list in the .greg dump: "74 conflicts: 74 76 77 78 80 2 3 4 5 16 29 64 65 66". The numbers 2,3,4,5,16,29,64,65,66 are hard regs (v0=2, v1=3, a0=4, a1=5, s0=16, sp=29, 64-66 = ?). So r74 conflicts with s0 (16). This is because d is live across the call, and s0 is a callee-saved... no, callee-saved regs aren't clobbered by calls. The conflict with 16 might come from the register allocator's model that s0 is used by another allocno (r77) which conflicts with r74? No, the conflict list would name 77, not 16.

Hmm, "16" in the conflict list might be an allocno number (not a hard reg). Allocno 16? But allocnos are numbered 72+. Hmm.

Actually, in global.c, `conflicts` lists both hard regs and allocnos by number. Hard regs are 0..FIRST_PSEUDO_REGISTER-1 (0-31 for MIPS). So 16 = s0, 29 = sp, 64-66 = ? (maybe $f? or the hi/lo?). And 2,3,4,5 = v0,v1,a0,a1.

So r74 conflicts with s0. Why? Because s0 is live somewhere in r74's range — perhaps an instruction explicitly uses s0 (a local-alloc pseudo). But the lreg RTL has no s0... 

Wait, maybe the `.lreg` dump is per-function but the RTL shown is the *pre*-local-alloc? Let me check: the .lreg dump header lines "Register 74 used 11 times..." are local-alloc candidates, and the RTL after is post-local-alloc (with hard regs substituted). If there's no s0 in the RTL, then s0 isn't used. So the conflict with 16 is puzzling.

Maybe "16" is not s0 but allocno 16? No.

Alternatively, the conflict is because the function *clobbers* s0 in the prologue/epilogue? The prologue saves s0 if used. If r75 (some pseudo) is in s0, the RTL would show it. Unless r75 is the function's frame/arg pseudo.

Hmm, maybe r75 is `u5` or the andi result that local-alloc assigned s0, and it's used in a block that I'm not seeing because the .lreg RTL range is wrong.

This is a deep rabbit hole. Let me stop and accept PARTIAL:pin.

Actually, wait. Let me reconsider: maybe the MATCH is achievable with a *different* real-C structure that avoids the conflict. But I've spent ~25 min on item 3. The budget is 20-30 min. Let me finalize PARTIAL:pin.

Let me wait for the background verification to complete, then finalize.

Meanwhile, let me prepare the notes and results text.

Actually, let me check the background job status. It may take a few minutes. Let me do the notes.md now.

Item 3 notes:
- orig.c == current header (diffed; same).
- kinds keepalive,pin.
- w1 (keepalive removed, pin kept): score 2 ORDER (sll order).
- w7 = w1 + do-while on cast block: score 0 → PARTIAL:pin.
- MATCH attempts: removing the pin (w2, w3) → d=s1 instead of s0; div do-while (w5) raises d's priority (pri 5185→12222) but d conflicts with s0 (global-alloc conflict with hard reg 16), so d still gets s1; cast do-while makes it worse (38). Wall: global-pri-bank-order / lreg-index-conflict.
- Verification: all 141 includers score 0 for w7 (pending).

Let me write notes.md.

Actually, let me wait for the verification result before writing the results row (result depends on all-includers check). Let me write notes.md now (I can adjust).

Let me also double-check w7's lever diff vs orig.
