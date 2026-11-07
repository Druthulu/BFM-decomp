---
ts: 2026-11-06T21:30:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VMeYyu9Pw1RZ2snvn6VU
---
Item 3 orig.c is current (SAME). 136 includers. tryinc.py rotates the includer list by k. To test all includers, I'd need k=0..135 (or the function's recs count). That's 136 compiles per candidate — expensive but each is a header-include TU compile (~1-2s), so ~3-5 min per candidate. Hmm.

Wait, the moves.md says "0 on 141/141 includers" for other header functions. For this header, 136 includers (grep count; recs count may differ).

The task: header item MATCH only if score 0 on every includer (tryinc.py k = 0..n-1). So I need to find a body that scores 0 on all includers.

First, let me understand the target and try to crack it. The target:
```
addiu sp,sp,-32
move v0,a0            # v0 = arg0
sw s0,16(sp)
move s0,a1            # s0 = arg1 (d)
sw ra,24(sp)
sw s1,20(sp)
lh v1,14(v0)          # arg0->unkE
lui a0,D_80126CB8
lh a0,0(a0)
lh a1,6(v0)           # arg0->unk6
lw v0,32(v0)          # *(arg0+0x20)
subu a0,v1,a0         # unkE - D_80126CB8
lui v1,D_80126CB4
lh v1,0(v1)
lh s1,18(v0)          # s1ang = *(*(arg0+0x20)+0x12) -> s1
jal ratan2
subu a1,v1,a1         # D_80126CB4 - unk6
addiu v0,v0,-1024
andi a0,v0,0xfff      # u5 in a0
sll s0,s0,0x10        # d = (s16)d
andi s1,s1,0xfff      # u6 in s1
bne s1,a0,37f0        # if (u6 != u5)
sra s0,s0,0x10
j 38a0                # return 0
move v0,zero
37f0:
subu v1,a0,s1         # iVar4 = u5 - u6
slti v0,v1,2049       # iVar4 < 0x801? (iVar4 > 0x800)
bnez v0,380c
slti v0,v1,-2048      # iVar4 < -0x800
addiu v0,s1,4096      # t = u6 + 0x1000
subu v1,a0,v0         # iVar4 = u5 - t
slti v0,v1,-2048
380c:
beqz v0,3818
addiu v0,s1,-4096     # t = u6 - 0x1000
subu v1,a0,v0         # iVar4 = u5 - t
3818:
bltz v1,3860          # if (iVar4 < 0) -> else branch
nop
3820: div zero,v1,s0   # q = iVar4 / d
... division checks ...
3848: mflo v1
nop
bnez v1,38a0
move v0,v1            # v0 = q
j 389c
li v1,1               # q=1
...
3860: div ...
3890: bnez v1,38a0
move v0,v1
li v1,-1
389c: move v0,v1
38a0: epilogue
```

Key observations:
- `d` (arg1) is in s0 ($16) — the pin $16.
- `u5` (andi result) is in a0 ($4).
- `u6` (s1ang & 0xfff) is in s1 ($17).
- `s1ang` loaded into s1 at 37c4.
- `q` (division result) in v1/v0.

The pin $16 forces `d` to s0. The keepalive keeps u5 in a0 (the asm use of u5 prevents combine folding? or keeps it in a0).

Actually, the keepalive `__asm__ __volatile__("" : : "r"(u5))` forces u5 to be in a register at that point. Then `u6 = s1ang & 0xFFF` and `if (u6 == u5)`. The target has u5 in a0 and u6 in s1. The asm likely keeps u5 in a0 (its natural arg reg after ratan2's return? no, ratan2 returns v0; addiu/andi into a0). Hmm.

The moves.md line for func_8012BB3C (similar): "C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0) and a 2nd do-while on the cast block replaces the keepalive ang anchor; residual extendhisi2 temp $v1 vs in-place $s0". So for our function, the same techniques may crack the pin and keepalive, but a residual may remain.

Let me first get a baseline: orig.c score. And then try:
1. Remove keepalive only.
2. Remove pin only.
3. Remove both.
4. do-while on the div block + do-while on the cast block.

Let me test on ONE includer first (k=0) to iterate quickly, then verify all includers once a candidate looks good.

Actually, tryinc.py rotates the includer list; the score depends on which includer TU (different globals/layout). The body is shared; the function's code should be the same across includers (same body, same target address 0x80128158? the function is at a fixed address). The differences are the surrounding TU (diagnostics). The score compares the function's bytes in the built object. Since the body is identical, the codegen should be identical across includers (the function is self-contained, using externs). So if it scores 0 on one includer, it likely scores 0 on all. But the task requires verifying all.

Wait, but the header is instantiated at each member's site (per the comment: "ONE source: instantiated by #include at each member's site in address order"). The function is defined once per includer TU. The codegen for the function itself depends only on its body and the extern declarations (which are the same). So all includers should give the same function bytes. The score 0 should hold on all if it holds on one. But the brief insists on checking every includer — maybe because the function's *address* differs or the surrounding code affects the bank judgment? The score is per-function (delever_search compares the function in the built object). Let me trust that one includer is representative, but I'll verify all at the end.

Let me first check the baseline and tryinc usage on k=0.

Let me run orig.c with tryinc k=0.
