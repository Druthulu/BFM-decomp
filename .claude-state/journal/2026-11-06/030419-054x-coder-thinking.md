---
ts: 2026-11-06T10:04:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y037rvGyHjVvEGG49gaS
---
So within func_800CD314, dispositions list r75 in 2 (v0), r78 in 5 (a1), r79 in 2, r80 in 2, r84 in 4 (a0), r85 in 4, r86 in 3, r87 in 2, r88 in 2, r89 in 2, r90 in 3, r91 in 4, r92 in 2, ... r100 in 2, r101 in 2.

No r74 in this list. r74 has no disposition (global allocno not assigned? It's in the "8 regs to allocate" order). Hmm, r74 is a global allocno; global-alloc assigns it but the disposition line might not print for it.

Wait — r74 is in "8 regs to allocate: 74 78 75 77 76 79 72 73" but r74 got no `;; Register 74 in N.` line. Odd.

Actually, the `;; Register N in M.` lines are printed by global-alloc's final assignment? For allocnos 72-79. r74 missing means r74 didn't get a hard reg? But the final code has t in v1.

Hmm, maybe r74 is not a pseudo that maps to t. Let me directly map by looking at the RTL in the .lreg dump: find `(set (reg:SI 74)` or the insns around the loads. Let me grep the lreg RTL for "76" and "84" offsets.

Actually the .lreg dump is post-local-alloc but pre-global. Pseudos are still pseudos. The insns for our loads would be:
(insn ... (set (reg:SI <t>) (mem:SI (plus:SI (reg:SI 72) (const_int 76)))))
Let me grep for "const_int 76".
