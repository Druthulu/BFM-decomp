---
ts: 2026-11-06T07:41:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Y8iL0edRGcarZ0SrSlUR
---
After the GTE block, s5 isn't used again — but it's saved/restored as a callee-saved register (lw s5,148(sp) at exit). So twicep in s5 is kept live through the GTE block by the keepalive, but no visible use. The natural C must keep twicep live (a real use after the GTE block) OR the allocator must otherwise not reuse s5.

Hmm wait — if the original used twicep after the GTE block, we'd see a `lw`/`use` of s5 there. The target's tail has no s5 use. So the natural C does NOT use twicep after. Then why is s5 kept live? It's saved/restored because it's assigned at entry (callee-saved). The allocator might still keep it live if the pseudo's death is late.

Actually, the register allocator decides w3c's register based on qty priority and free regs, not on "twicep liveness". Let me get the allocation tables for orig vs w1 to see the actual difference. Let me dump orig (with keepalive) and w1 and compare the .lreg.

But maybe there's a simpler real-C move: make w3c's live range or the register order such that it gets a0. E.g., declare w3c as u32 vs s32 (same). Or split w3c into two variables: the loaded value and the pointer. E.g.:
```
u32 w3c;
...
L.w3C = *(u32 *)twicep;   // store directly
...
w3c = (u32)L.o1;
gte_stsv((u16 *)w3c);
```
But target keeps the loaded value in a0 until sp+60, so the source has a variable. However, if we write `L.w3C = *(u32*)twicep;` the store happens at insn 40-ish (right after load), and the load's dest would be a temp. Let me test; maybe the compiler schedules the store later and the temp gets a0. Actually, the target's load at 40 and store at 59 are separated by the v48/v50/v58 setup; sched1 could sink the store. Let me try.

Also, another idea: the original might have TWO variables: `w3c` for the twicep read and another for the L.o1 pointer. The source reuses w3c (`w3c = (u32)L.o1;`). If the original used a separate variable, say `w3d = (u32)L.o1;`, then w3c's live range ends at L.w3C store (insn 59) and w3d starts after; both could be a0. Let me test.

Let me think about why mine gives s5. Local-alloc: w3c's qty is in block 0? Its birth at insn 40, death at 59. The free regs at that range: s5 just died (twicep death at 40). local-alloc's find_free_reg iterates reg_alloc_order. For a non-call-crossing qty, `used = fixed_reg_set`; it excludes regs live in [40,59). s5 is live from entry to 40, so at insn 40 (birth of w3c) is s5 live? The live range for w3c starts at 40; regs_live_at[40] includes s5 if s5's death is after insn 40. The load `lw s5,0(s5)` at insn 40 uses s5 (source) and defines w3c. If twicep dies at insn 40, then at insn 40 s5 is still live (used by the load). local-alloc's `for (ins = born_index; ins < dead_index; ins++) IOR regs_live_at[ins]` — born_index=40? If born_index is the insn where w3c is born, and s5 is live at insn 40, then s5 is excluded from w3c's range... but mine gave w3c s5! So s5 is NOT live at insn 40 in mine, meaning twicep dies at insn 39 (or earlier), and local-alloc reused it.

With the keepalive, twicep is live through insn 59+, so s5 is excluded for w3c's range → w3c gets a0.

So to reproduce without the asm: we need twicep's death to be after w3c's death, i.e., a real use of twicep after the GTE block. But the target has no s5 use after. Contradiction? Unless the real use is optimized into a redefinition that doesn't emit an instruction (e.g., `L.w3C = w3c` where w3c is also... no).

Hold on: maybe the natural C's variable isn't w3c but a value that is used later, extending the *s5* pseudo, and the use is dead-code-eliminated after allocation? No, DCE happens before allocation (flow).

Alternatively, maybe in the target, s5 is NOT twicep's value at the GTE block but something else. The keepalive forces twicep live; the target might naturally have a DIFFERENT pseudo in s5 live across the GTE block. Which? `s1` = sp+96 (used in GTE loads: `addiu s1,sp,96` and `lwc2 $0,0(s1)`?). Let me check: s1 is used for the GTE lwc2 address. s1=sp+96 = L.mat? The function: `func_80013F3C(L.mat); RotMatrixZ(*angp, L.mat); ... func_8004914C(L.mat); func_800491AC(L.mat);` L.mat is at offset 96. So s1 = &L.mat, used for the calls (a0=s1) and the GTE.

Hmm, s1 is used throughout. Fine.

Let me get the lreg dumps for orig and w1 and compare the quantities. Dump orig candidate. Since orig (with the keepalive) is the src body, I can use the src TU directly. Let me dump the scratch for orig via --keep then cc1_dumps_tu, and similarly w1. Actually, I can dump the REAL TU for orig (src/md_MAIN_026/md_MAIN_026.c) — it has the lever and compiles. And for w1, use the --keep scratch.

Let me do orig first.
