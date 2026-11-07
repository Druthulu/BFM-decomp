---
ts: 2026-11-06T23:52:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9qnVCLoao4vqdZQQVFYA
---
Confirmed. G (nopin, launder kept) differs only by the s3/s4 swap of base and mode.

So two sub-problems:
1. Reg allocation: base s4, mode s3.
2. The copy.

For #1: base is a u8* set once and used in many places (10 refs). mode is s32 set in two places (mode=-1 and mode=0) and used in 4 places. Global-alloc priority: pri = floor_log2(n_refs)*n_refs/live_length.

base: n_refs maybe 11 → floor_log2(11)=3 → 3*11=33; live_length ~ 161? → 0.205
mode: n_refs maybe 5 → floor_log2(5)=2 → 2*5=10; live_length ~ from insn 34 to 139 = 105 → 0.095

base wins → s3. Need mode to win. Hmm.

But wait, in the target (with pin), base got s4 because s3 was reserved. Lever-free we need the same *result* without a pin. Options:
- Increase mode's refs/live ratio: e.g. make mode used more (more refs) or live shorter.
- Decrease base's priority: make base live longer or fewer refs.

Hmm, but the code is fixed by the target bytes. Adding refs changes code.

Wait — maybe base isn't the only allocno. Let me check which variables exist: base, file(s1), val(s2), st(s0?), cnt, res, p, mode. Target: s0=cnt? Let's see: at 1108 `move s0,v0` after func_80029504 → cnt=s0. s1=file, s2=val, s3=mode, s4=base. 

So the callee-saved regs s0-s4 are assigned to cnt, file, val, mode, base respectively. Hmm, and `st` is in v0/v1 (caller-saved, dies early). res=s0? At 124c `li s0,1` (res=1) and 1270 `move s0,v0` — so res is also s0, reusing cnt's register after cnt dies. And cnt is s0 from 1108 to 1158.

Interesting: so s0 is shared by cnt then res.

Now allocation order: global-alloc sorts allocnos by priority and assigns. The result: s0=cnt, s1=file, s2=val, s3=mode, s4=base. Hmm, actually the assignment isn't necessarily in that order; find_reg picks the first free register in the alloc order (reg_alloc_order or the order of allocno_order). Let me look at find_reg and how hard regs are ordered.

In global.c find_reg, it iterates over `regs_allocated` (a HARD_REG_SET) in increasing register number order? Let me check.

Actually the natural order s0,s1,s2,... suggests find_reg tries s0 first, then s1, etc. So the FIRST allocno (highest priority) gets s0. Then next gets s1 (or s0 if conflict allows).

Priority order: highest priority gets s0. In target: cnt→s0 (highest), file→s1, val→s2, mode→s3, base→s4.

But that ordering (cnt, file, val, mode, base) doesn't match ref counts: base has 10 refs, mode 4, file 4, val 6, cnt 2.

Hmm, so global-alloc's priority isn't just refs. Let me check what regs are actually global vs local. Maybe base/mode/file/val are LOCAL-alloc candidates (block-local) and local-alloc assigns them.

Actually local-alloc runs first and assigns pseudos whose live range is within one basic block. base, mode, file, val all span multiple blocks → global.

Hmm, but in this function, everything is one big straight-line sequence except the ifs. Actually, the if bodies are small. base is live across the whole function.

Hmm, let me just use tools/alloc_table.py to see the allocno priorities. The brief mentions `tools/alloc_table.py` for TU dumps.

Actually, easier: let me check global.c find_reg order.
