---
ts: 2026-11-06T11:57:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_77ZDk4EdFerlSWtkkwjG
---
Target disassembly (44 insns):
0 addiu sp
1 sw s0,16
2 move s0,a0
3 sw ra,20
4 lw v0,32(s0)     <- p = *(a0+0x20)
5 li v1,2          <- two = 2 (in v1)
6 sh v1,2(s0)      <- unk2 = two
7 sh zero,52(s0)   <- unk34 = 0
8 sh zero,20(v0)   <- p+0x14 = 0
9 sh zero,18(v0)   <- p+0x12 = 0
10 jal func_8012B2CC (delay: sh zero,16(v0))  <- p+0x10 = 0
11 ...
12 jal func_8012B200
13 move a0,s0 (delay)
14 lh v0,6(s0)      <- v = *(s16*)(a0+6)
15 nop
16 bgez v0, 46f8
17 nop (delay)
18 lh v0,112(s0)    <- unk70 (v = a0->unk70)
19 nop
20 bnez v0,470c
21 lui v0,0x4       <- 0x40000 (delay)
22 j 470c
23 lui v0,0x3       <- 0x30000 (delay)
24 lh v0,112(s0)
25 nop
26 bnez v0,470c
27 lui v0,0xfffc    <- -0x40000 (delay)
28 lui v0,0xfffd    <- -0x30000
29 sw v0,16(s0)     <- CAST_WIDTH(...,0x10) = v
30 li a0,2432       <- func_8002D4C8(0x980,...)
31 lui v0,0x20       <- 0x200000
32 sw v0,20(s0)      <- unk14 = 0x200000
33 lui v0,0x2        <- 0x20000
34 move a1,zero
35 sw zero,24(s0)    <- 0x18 = 0
36 sw v0,72(s0)      <- unk48 = 0x20000
37 jal func_8002D4C8 (delay: sw zero,28(s0))  <- unk1C = 0
38 ...

So the `li v1,2` is in v1 (target). Mine has `li v0,2` in v0. The pin `two __asm__("$3")` forced $3 = v1. Without it, gcc picks v0.

And the `sw v0,16(s0)` at insn 29 (target) vs mine insn 30 (one later). The barrier kept the store at 29 (before the `li a0,2432`? no). Actually mine has the store at 30 (after `li a0,2432`?). Let me see mine's order. The diff said: insert mine[29] target[29:30] (target has sw at 29), delete mine[30:31] (mine has sw at 30). So mine's sw is one insn later than target. The barrier `__asm__ __volatile__("")` at the end of the middle block prevented sched from sinking the store past something.

So the barrier keeps the store at 29. Without it, the store sinks to 30. This is a sched store-sink (walls.txt: `sched-store-sink sched sinks a store past the target slot (G28)`).

Real C to fix the store position: maybe reorder statements, or add a dependence. Hmm.

And the register swap: `li v1,2` vs `li v0,2`.

Let me try variants:
1. v_two: keep the `two` variable (s32 two; two = 2; store two). Without pin.
2. v_two_decl: `s32 two = 2;`
3. v_two_u16: `u16 two = 2;`
4. v_store_reorder: move the 0x10 store to a different position / wrap in do-while.
5. v_two + do-while.

Let me generate and score.

For the register swap: the target has p in v0 and two in v1. Mine has p in v1 and two in v0. This is a local-alloc ordering. If I make `two` born before p (currently p is computed first, then two), the allocation might swap. In the original, `p = ...` then `two = 2`. Mine (literal 2) has p first then li 2. The target has lw p (v0) then li 2 (v1). So p in v0, two in v1. Mine: lw p (v1), li 2 (v0). So the allocation of p and two is swapped. The pin forced two to $3=v1, leaving v0 for p.

Real C to flip: maybe declare `two` before `p`, or use `two` in a way that gives it priority. Local-alloc assigns based on ref counts/priority. If `two` has more refs, it might get v0... hmm, target wants two in v1 (lower priority). Mine gives two v0 (higher priority?). Confusing.

Actually, local-alloc assigns the first-allocated pseudo to v0. The order depends on qty priority. To get two in v1, p should be allocated first (gets v0). Currently mine allocates two first (v0) then p (v1). So I need p to have higher priority than two. p is used 3 times (sh zero 20/18/16(v0)), two is used once (sh v1). So p should have higher priority → p gets v0. But mine gives p v1 and two v0. Hmm, maybe the birth order matters (local-alloc allocates in order of first use). p is born at insn 4 (lw), two at insn 5 (li). So p born first → should get v0. But mine gives two v0. 

Wait, mine's diff: `lw v1,32(s0)` (p in v1) and `li v0,2` (two in v0). So two got v0, p got v1. Despite p being born first. Odd.

Maybe because `two` is a constant (li) and gcc's local-alloc gives constants to v0? Or the register preference.

Let me try keeping `two` as a variable — it might change the allocation. Let me test.

Let me write gen.py.

Variants:
1. v_two: `s32 two; ... p = ...; two = 2; unk2 = two;`
2. v_two_decl: `s32 two = 2;`
3. v_two_u16: `u16 two = 2;`
4. v_two_s16: `s16 two = 2;`
5. v_two + do-while store
6. v_store_dw: wrap the CAST_WIDTH store in do-while

Let me test.
