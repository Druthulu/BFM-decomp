---
ts: 2026-11-06T09:27:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UpuSdoanpmKVXZKgbJO2
---
Still 6. Time 02:27. Need to reach 02:33 for the 20-min wall. Let me try a few more genuinely different structures, maybe targeting the whole block.

Actually — wait. Let me reconsider the problem: maybe the real C for the fc block differs more fundamentally. Look at target insns 74-101:

```
74 lh a1,12(a2)      fc
75 lh a0,14(a2)      lim
76 nop
77 slt v0,a1,a0      fc<lim
78 beqz v0, 91
79 move v1,a1        iVar7=fc (delay slot, unconditional)
80 addiu v0,v1,1024  t=iVar7+0x400
81 sh v0,12(a2)
82 sll v0,v0,0x10
83 lh v1,14(a2)      lim reload
84 sra v0,v0,0x10
85 move a0,v1
86 slt v1,v1,v0      lim < (s16)t
87 beqz v1, 102
88 nop
89 j 102
90 sh a0,12(a2)      store lim
91 slt v0,a0,a1      (else) lim<fc  [a0=lim, a1=fc]
92 beqz v0,102
93 addiu v0,v1,-1024 t=iVar7-0x400
94 sh v0,12(a2)
95 sll v0,v0,0x10
96 lh v1,14(a2)
97 sra v0,v0,0x10
98 slt v0,v0,v1
99 beqz v0,102
100 move a0,v1
101 sh a0,12(a2)
102 move a0,s8
```

Interesting: at 91, `a0` is the limit from insn 75 (still live!) — so the limit's first pseudo lives from 75 to 91 (used in both comparisons). And the reload at 83 is v1. So the first limit load (a0) is used at 77 and 91. fc (a1) used at 77, 79, 91.

So in the target: fc=a1, lim=a0. In mine: fc=v1, lim=a1.

Local-alloc priorities: fc 3 refs; lim 2 refs. Live ranges similar. Hmm.

Maybe the difference is that in the target, the *limit* pseudo was allocated first (it's loaded first?) and got a0; then fc got a1. In mine, fc got v1 and lim got a1 — meaning lim was allocated before fc and got a1 (since a0 maybe taken? by what? a0 might be used elsewhere). Hmm, in mine at insn 74: `lh v1,12(a2)` fc; 75: `lh a1,14(a2)` lim. So lim got a1, fc got v1.

What's a0 used for at that point in mine? Perhaps a0 holds something live (e.g., the &0x10 andi result? or the fc/lim). In mine, insn 69-73 use v0/v1... a0 might be free. Hmm.

Honestly, without deeper alloc analysis, this is a rabbit hole. It's 02:27, 14 min in. Let me look at the .lreg dump to understand the qty priorities — that might reveal a real-C lever (e.g., change a type width or add a genuine use).

Let me dump s251_57 (K1 kept) and look at the lreg table for the fc/lim pseudos. hdump with outdir.

Actually, hdump splices into the TU and dumps. Let me run it for s251_57 and grep the alloc table.
