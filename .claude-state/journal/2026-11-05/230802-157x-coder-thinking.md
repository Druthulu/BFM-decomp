---
ts: 2026-11-06T06:08:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_27T2IM0byzsiJUc0YGo1
---
Target asm:
```
286c addiu sp,-48
2870 sw s0,40(sp)
2874 sw ra,44(sp)
2878 jal func_8012C1B8
287c move s0,a0          (delay)
2880 bnez v0, 2898
2884 sw v0,32(s0)        (delay — unk20 = result)
2888 jal func_8012CAE4
288c move a0,s0
2890 j 295c
2894 nop
2898 jal func_8001C2C4
289c move a0,v0          (delay)
28a0 lh v0,112(s0)       unk70
28a8 sll v0,v0,1
28ac lui at, D_80184CA8
28b0 addu at,at,v0
28b4 lh v1,0(at)         v1 = D_80184CA8[unk70]
28bc andi v0,v1,0xf000
28c0 sra v0,v0,0xc
28c4 sh v0,254(s0)       unkFE
28c8 andi v0,v1,0xf
28cc sh v0,256(s0)       unk100
28d0 lw v0,32(s0)        v0 = unk20
28d4 andi v1,v1,0xff0
28d8 sh v1,18(v0)        unk12
28dc lh v1,256(s0)       v1 = unk100 (2nd set)
28e0 li v0,2
28e4 bne v1,v0, 28f8
28e8 li v0,1024
28ec lw v1,32(s0)
28f0 nop
28f4 sh v0,16(v1)
28f8 jal func_8012B2CC
28fc move a0,s0
2900 sw zero,20(sp)
2904 sw zero,16(sp)
2908 lh v0,256(s0)
290c move a0,s0
2910 sll v0,v0,2
2914 lui at, D_80184D0C
2918 addu at,at,v0
291c lw v0,0(at)
2920 addiu a1,sp,16
2924 jal func_8012B14C
2928 sw v0,24(sp)
292c move a0,s0
2930 lui v1, D_80184CCC
2934 addiu v1,v1,0
2938 lh v0,256(s0)
293c lh a1,112(a0)        ← note: uses a0 (which is s0, set by move a0,s0 at 292c!)
2940 sll v0,v0,4
2944 addu v0,v0,v1
2948 lui v1,0x4000
294c or v0,v0,v1
2950 sw v0,88(a0)
2954 jal func_8012AD50
2958 sw a1,28(a0)         (delay)
295c epilogue
```
Interesting: the target's s0 is in $16 (s0) — the pin. The prologue: `sw s0,40(sp); sw ra,44(sp); jal; move s0,a0`. So s0 = a0 copied in the jal delay slot.

Mine (n2/p1): frame 56, `sw s1,44(sp); move s1,s0` — so mine uses s1 instead of s0! Wait, the diff said mine `move s1,s0` at insn 6. Hmm, but s0 is $16; why would gcc copy s0 to s1?

Oh I see — the source has `s0 = (s32)a0;` as a variable named s0, and the *pin* makes it $16. Without the pin, gcc allocates the variable to s1 (or a0). The target's variable is in $16 (s0) — because of the pin.

So the pin $16 forces the pointer into s0. Without it, gcc picks s1 (or another callee-saved).

Hmm. So the pin is load-bearing for the register choice.

Can we make gcc choose $16 naturally? $16 is the first callee-saved register (s0). gcc's global alloc assigns callee-saved regs in some order; the highest-priority allocno gets the first. In the target, the pointer gets s0 ($16).

Without the pin, mine: the pointer in s1 ($17)? and something else in s0? Let me check the mine asm.

Hmm, the diff showed mine: `sw s1,44(sp); move s1,s0` — wait, that means the *incoming* a0 was copied to s1? And `move a0,s1` for the calls. So the pointer is in s1.

And the frame 56 vs 48 — mine saves s1 and something else?

Let me look at the full mine asm.

Actually, let me reconsider: maybe the launder's removal (pa0) is the issue: with `pa0 = s0`, gcc had two variables; without, one. Hmm, but the pointer register choice should be the same.

Let me look at p1's asm.

Actually, the key question: why does the target's pointer get $16 while mine gets $17?

In the target, the pin forces it. Without, global_alloc assigns by priority: the pointer (s0) is the highest-priority allocno → should get the first callee-saved reg. Which is first in reg_alloc_order? For MIPS, probably $16,$17,... or maybe $17 first.

Hmm, in the target, the pin makes the pointer $16; the other callee-saved uses... the target only saves s0 (frame 48: sw s0, sw ra). So only ONE callee-saved reg is used.

Mine uses s1 (frame 56 = sw ra, s1, and maybe another). Hmm, frame 56 with sw ra,44; sw s1,44? The diff showed mine `sw ra,48(sp); sw s1,44(sp)` and frame 56. So mine uses s1 only (plus ra) but the frame is 56 vs 48 — 8 extra bytes for the 5-word loc array? Hmm.

Wait, the target's frame is 48: sw s0,40; sw ra,44; loc[5] at 16-36 (sw zero,20; sw zero,16; sw v0,24). So loc[] at sp+16..36, s0 at 40, ra at 44.

Mine's frame 56: loc[] at 16..36, s1 at 44, ra at 48? That's 8 bytes more.

Hmm, why? Maybe because mine has an extra callee-saved reg (s1) and the frame rounds up.

Anyway, the pointer register is s1 vs s0. Since both are callee-saved, the difference is which one.

To make gcc pick $16: maybe the *priority* of the pointer allocno. Or maybe use a different structure.

Hmm, in gcc 2.7.2 global.c, `reg_alloc_order` for MIPS: let me check the machine description. Typically it's $16..$23 for callee-saved (or maybe $17,$18,...). Let me check tools/reference/gcc-2.7.2/... the mips.h REG_ALLOC_ORDER.

Actually, in gcc's global.c, the order is `reg_alloc_order[]` from the machine description. For MIPS (mips.h), it might be:
```
#define REG_ALLOC_ORDER { 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,... }
```
Hmm, if caller-saved come first, then callee-saved.

But the pointer is live across calls → it can only use callee-saved. The first available callee-saved in the order would be $16.

Mine uses s1 ($17) — why not $16? Maybe $16 is taken by another allocno! In mine, is there another cross-call allocno? The `v1` variable? No, v1 isn't live across calls. Hmm.

Wait — maybe mine's frame saves s1 AND s0? The diff showed mine `sw ra,48(sp); sw s1,44(sp)` and `lw ra,48; lw s1,44`. So only s1. But the frame is 56 — odd.

Hmm, maybe the frame size differs because of the loc array alignment.

Let me look at p1's full asm.
