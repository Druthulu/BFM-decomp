---
ts: 2026-11-06T21:04:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GWX3avfjaNijl8ipTI5a
---
Now clear! The structure: 
- insn 27: reg 78 = (zero_extend:SI (mem:HI ...)) — the lhu.
- insn 29: reg 74 = plus(reg 78, -256) — the sub! reg 74 is a *global* allocno (live across blocks? r74 used 9 times across 10 insns; dies in 3 places). Wait — reg 74 is the `t` variable, and it's GLOBAL (allocated by global.c, not local-alloc)! In the .greg table r74 shows "-" and pri 27000, conflicts v0,sp, dies in 3 places. So `t` is a single pseudo live across the three blocks — because the C variable `t` is defined and used in each of the three if-blocks, and GCC's flow analysis... hmm, it says r74 used 9 times across 10 insns, "dies in 3 places" — so it's ONE pseudo, live in blocks 1,3,5,7? It's the same variable t used in all three regions plus... Wait 9 refs.

But the target's assembly has t in v0 in each block. In the lever-free candidate, global-alloc gives r74 a register: the .greg table said "-" (dump doesn't show), and the .s shows t in $3. So global-alloc assigned r74 = $3 (v1)!

And r78 (the load) got v0, r79 (sll result) got v0. Hmm, and in the .lreg "Register 78 in 2", "Register 79 in 2", r74 is not in the local list (it's global).

So the decisive allocation is GLOBAL: r74 (t) vs other allocnos. The .greg order line: "74 72 73" — three allocnos to allocate: r74 (pri 27000), r72 (12580), r73 (8918). Wait, that's the global allocno order. r74 highest priority → allocated first → should get the first free reg. It got $3, while r72 (s1) got $17 and r73 got $16 presumably. Hmm, but why $3 and not $2?

In global.c, the register order for GENERAL_REGS: `regs` array order. For MIPS, `REG_ALLOC_ORDER` might put $2 first... but maybe the MIPS reg class order is different, or global-alloc avoids $2 because it's a call-clobbered reg that crosses calls? r74 "conflicts v0,sp" per the table — meaning r74 has a conflict with something already in v0? The note "conflicts v0,sp" is the hard-register conflict list from the .greg dump.

Hmm: "conflicts v0,sp" — r74 conflicts with v0. Why? Because r74's live range includes an instruction that uses v0 as a fixed hard register (e.g., a call clobbers v0, or the return value). r74 dies in 3 places... The allocno crosses calls? No, it says "dies in 3 places" not "crosses calls". But a call insn clobbers v0 (the return register is v0 and call insns clobber v0). Wait, does r74's live range span a call? It's used in blocks 1,3,5,7 — each block is a separate region; the calls are in block 0, 5(?), 6... Hmm.

Actually the "conflicts v0,sp" note might be the conflict vector: r74 cannot use v0 because v0 is live/clobbered at some point in its live range.

In the target (with pin), t was forced into v0 by the asm pin, so the target's code has t in v0. Lever-free, global-alloc refuses v0 for r74 because of a conflict (call clobber). So t goes to $3.

So we need to make t NOT conflict with v0. The conflict arises because the pseudo's live range covers a point where v0 is used/clobbered. Since t is a single pseudo spanning blocks 1,3,5,7, and the function has calls (block 5 has func_80146CA0? and block 6/7 the func_800CC6C4 call), the live range spans a call → v0 clobbered → conflict.

Wait but the target with the pin keeps t in v0 across the call at 1700? Let's check target: the call at 1700 (jal func_80146CA0) — after it, at 1704 `sh zero,24(s1)`, then block 7 computes x/y in v0. t is not live across the call (t's last use is before). So t's live range doesn't span the call.

Hmm, but r74 "dies in 3 places" means it has 3 live ranges (in blocks 1,3,5?) and block 7 uses r79 etc. Let me check the .greg dump for r74's conflicts and live ranges.

Let me grep the .greg section for our function.
