---
ts: 2026-11-06T10:04:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yaaQWMC4ka69IU25jx4z
---
So t = reg 74, tb = reg 75. Confirmed.

The lreg dump order: insn 68 (t=76), insn 71 (store t at 6), insn 83 (t=80), insn 74 (tb=84). Interesting: the lreg insn order is 68, 71, 83, 74 — so t's second def (83) comes BEFORE tb's def (74) in the RTL list? That's odd numbering: insn numbers 68,71,83,74. The sequence chain: 68→71→83→74→93. So after store at 71, next is insn 83 (t=80), then insn 74 (tb=84). Wait the chain says `(insn 68 65 71 ...)`, `(insn 71 68 83 ...)`, `(insn 83 71 74 ...)`, `(insn 74 83 93 ...)`. So order: 68, 71, 83, 74, 93.

That means in the lever-free body, the compiler reordered: t=unk4C, store t, t=unk50, tb=unk54, ... But the final assembly has 52 lw v1,76; 53 lw v0,84; 54 sh v1,6; 55 lw v1,80. So sched1 reordered again.

Hmm wait, the lreg RTL order doesn't match the final asm order because sched1 runs before local-alloc? Actually local-alloc runs after sched1 (in 2.7.2 the order is: ... combine, sched1, local-alloc, global-alloc, ...). So the lreg RTL is already scheduled. The order 68,71,83,74 = load t, store t, load t(80), load tb. Then later the store tb. And final asm shows lw 76, lw 84, sh 6, lw 80 — different. Hmm, maybe I misread the chain.

Anyway: t=74, tb=75. r74 conflicts v0,v1,sp (from greg line 233). Yet final t is v1. Contradiction unless the conflict list is from a different point.

OH WAIT. The greg dump line 233 `;; 74 conflicts: 73 74 75 76 77 78 79 2 3 29` — the numbers 2,3,29 could be *allocno numbers* 2,3,29? No, allocnos start at 32. So they're hard regs v0,v1,sp. If r74 conflicts v0 and v1, it cannot get either. But t is in v1.

Unless the greg dump is from the FIRST global-alloc pass and there's a second? Or the "8 regs to allocate: 74 78 75 77 76 79 72 73" is a DIFFERENT function's block. Let me check which function section line 230 is in. The greg file has multiple functions. alloc_table's `section()` extracts func_800CD314's section. The order line at 230 came from the extracted section (alloc_table found it). Hmm.

Hmm, wait: r74 conflicts list includes 74 (itself) — allocno numbers include themselves? "74 conflicts: 73 74 75..." includes 74, itself. That's odd. Unless these are allocno *indices* in a different numbering (e.g., 74 could be a hard reg $t2=10? no).

Actually in global.c's dump, conflicts are printed as hard register numbers only (the `conflicts` array is indexed by hard reg). The values listed are hard regs. 74 is not a hard reg. So these must be allocno numbers or something else.

Hold on — maybe the greg dump's "N conflicts:" uses `allocno` numbers that are actually REGNOs of pseudos? In GCC, allocnos are indexed by regno (the pseudo regno). So "74" is pseudo reg 74, and "2 3 29" are hard regs. So conflicts lists: pseudos 73,74,75,... and hard regs 2,3,29. The pseudo entries in a conflicts list would be weird; the conflict array is over hard regs only.

Hmm, maybe alloc_table's regex `;;\s*(\d+) conflicts:\s*([0-9 ]+)` catches a line from the .lreg dump instead, where the format is different. Let me directly look at line 230-238 context in the greg file.
