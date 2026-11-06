---
ts: 2026-10-22T21:43:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AB1X1vnqPPpx6ME9HqJe
---
Scheduling is bottom-up (from the end of the block). The block: insn 34 is the branch (last), then 33, 30, 27, 25, 22, 16, 11, 14, 4, 83, 85, 81.

So the schedule order at the end of the block is: 81 (first in program order) ... 34 (last).

The order is: 34 (branch, T-1), 30 (T-2), 27 (T-3), 33 (T-4), 25 (T-5), 22 (T-6), 16 (T-7), 14 (T-8)... wait it's confusing. The final program order is the reverse of the launch order: T-13 = 81, T-12 = 85, T-11 = 4, T-10 = 14, T-9 = 83, T-8 = 11, T-7 = 16, T-6 = 22, T-5 = 25, T-4 = 33, T-3 = 27, T-2 = 30, T-1 = 34.

So program order: 81, 85, 4, 14, 83, 11, 16, 22, 25, 33, 27, 30, 34.

I need the target order: addiu sp(81?), sw s0(85?), move s0(?), sw ra(?), li -64, sh zero, sh v0, ...

Hmm, insn numbers: 4 = probably the prologue sw s0? Let me map: the -dS dump shows the insn numbers with patterns. Let me look at the .sched2 file for the insn bodies... Actually the "insn[ N]" lines in the sched2 dump only give priorities.

Let me instead compare: in the target, the order is 81, 85, <move s0>, <sw ra>, <li -64>, <sh zero>, <sh v0>, ...

In mine: 81, 85, 4, 14, 83, 11, ... So insn 4 is the move s0 (3rd). Then 14 = li v0,-64, 83 = sw ra. So sched2 put li (14) before sw ra (83).

In the target, sw ra comes before li. So in the ROM's build, at T-9/T-10 the choice was sw ra first.

The "potential hazard" rule: at T-9 "insn 83 has a greater potential hazard, now 83 14 4" — but then it launched... hmm, at T-10 the ready list is "14 (1) 4 (1)" — so 83 was launched at T-9? Let's see: "ready list at T-9: 14 (1) 4 (1) 83 (1), now 14 4 83" then "insn 83 has a greater potential hazard, now 83 14 4" then "ready list at T-10: 14 (1) 4 (1), now 14 4" — so 83 launched at T-10? Actually the ready list at T-10 shows what's left, so 83 launched at T-10, 14 at T-11... but the dump says T-11: 4 (1) and T-12: 85. Hmm, so 14 launched at T-11 and 4 at T-12? Then order reversed: 4 before 14? 

Whatever. Empirically the li ends up before sw ra.

The lever: make sched2 prefer sw ra. In the target, the barrier forced it.

Idea: what if the ALU insn (li) isn't ready at that point — e.g. if the li depends on something scheduled later. E.g. if -0x40 came from a variable assigned after the b-copy... but the store order in the asm is sh zero then sh v0 (both before the lwl copy).

Hmm, in the target: sw ra, li v0,-64, sh zero,16, sh v0,18. So the li is still 2 slots before its use.

What if I write `*(s16 *)&loc.a.raw[2] = -0x40;` AFTER the b copy in source? Then the sh would move after the lwl/lwr — changes asm.

What if the two raw stores are done in the reverse source order? c1.

Let me try:
c1: raw[2] = -0x40 first, then raw[0] = 0.
c2: m variable.
c3: `loc.a.raw[0] = 0; loc.a.raw[1] = 0;` (byte stores)? changes asm.
c4: b-copy first.
c5: init at decl with a compound literal: `S16_SC02_005_8017F7CC loc = {{0,0,0xC0,0xFF,0,0,0,0},{0,0,0,0,0,0,0,0}};` → byte stores, changes asm. Skip.
c6: `*(s16 *)&loc.a.raw[2] = (s16)-0x40;` same.

Hmm. Alternatively: what if I move the `iVar2` computation BEFORE the loc stores? Then the ALU insns (sub) are born earlier and sched2... changes order.

Honestly, let me think about the real mechanism differently: the barrier is a memory clobber. sched2's "potential hazard" for sw ra: a MEM insn. In mine, sw ra also got "greater potential hazard" at T-9 but was scheduled at T-10 anyway (blocked?). 

Actually the key line: ";; blocking insn 23 for 1 cycles" in item 2. Here, no blocking.

Let me try a different approach: reduce the number of insns the scheduler can reorder before sw ra. E.g. if the li were merged with the store... 

Or: make the two raw stores a single 32-bit store: `*(s32 *)&loc.a.raw[0] = 0xFFC00000;`? That gives `li v0,0xffc00000; sw v0,16(sp)` — different asm (sw vs 2 sh). No.

OK, let me try the c-batch and if none works, WALL.

Actually, wait. Another idea in the same family as item 2's crack: **init at decl for the whole `loc`**: 
`S16_SC02_005_8017F7CC loc = { 0 };` — all zeros. Then the -0x40 store remains a separate statement. That gives sh zero for raw[0..7]? Actually `= {0}` for a struct of two S8Blob{u8 raw[8]} would zero all 16 bytes → 4 sw or 8 sb stores. Changes asm.

Hmm, what about the possibility of writing the s16 store as part of the declaration: `S16_SC02_005_8017F7CC loc = {{0,0,0xC0,0xFF,0,0,0,0},{0}};` → byte stores, no.

Let me just test c1, c2, c4, c6 + a couple of statement reorderings, then decide.
