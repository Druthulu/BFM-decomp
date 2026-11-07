---
ts: 2026-11-06T07:41:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fFr9dop8kRR4bQQMN61I
---
Target: `lw a0,0(s5)` loads `w3c = *(u32*)twicep` into a0 (caller-saved!), and later `sw a0,60(sp); addiu a0,sp,16` then `sh t4,0(a0)` — so a0 is the GTE dest pointer (L.o1). In the source, `w3c = (u32)L.o1;` assigns the address of L.o1 to w3c, then `gte_stsv((u16 *)w3c)`. Target uses a0 for that pointer. Mine uses s5 (callee-saved).

So the target has a0 free for these locals, whereas mine allocated s5. Why is s5 used in mine? Because the keepalive on twicep was forcing something... wait, we REMOVED the keepalive and got s5. So lever-free mine uses s5; target uses a0. That means the keepalive in orig made... hmm, orig (with keepalive) scores 0. So the keepalive makes the target's a0 allocation happen. The keepalive forces twicep live at a point, and that changes allocation such that w3c gets a0.

Hmm, wait: orig has the keepalive and scores 0 (target uses a0). Removing it → s5. So the keepalive steers w3c into a0. The keepalive is `"r"(twicep)` — forces twicep live in a register at that point. twicep is a parameter; without the keepalive, twicep dies after its last use (`w3c = *(u32*)twicep` at insn 40). With the keepalive, twicep is live until after the GTE block (insn ~?). Hmm, but that shouldn't make w3c a0.

Actually, maybe the keepalive's effect: the `asm` is a use of twicep, extending its live range. This changes global-alloc priorities, causing w3c (which is live across the GTE region) to be allocated a0 instead of s5.

What real C would keep twicep live? In the original, twicep is used for `L.w38 = *(u32 *)twicep;` and `w3c = *(u32 *)twicep;`. After that, twicep is dead. Unless the original used twicep later — e.g., a second `w3c = *(u32 *)twicep;`? Hmm.

Wait, the diff: mine `lw s5,0(s5)` vs target `lw a0,0(s5)`. Both load from s5. So the SOURCE pointer is in s5 in both (twicep). The DEST is a0 in target, s5 in mine. Wait, mine has `lw s5,0(s5)` — loading from s5 into s5 (the same reg, overwriting the pointer). Then later `sw s5,60(sp); addiu s5,sp,16`. So in mine, w3c (the value loaded, which is `*(u32*)twicep`) is in s5 and then reassigned to `(u32)L.o1` in the same s5. In target, w3c is a0.

So the variable `w3c` is allocated s5 in mine, a0 in target. Why? The keepalive extends twicep's live range; twicep is in s5 (callee-saved, crosses calls? there are GTE macros but no calls... RotMatrixZ and func_8004914C are calls earlier). Hmm.

Let me look at the target's use of s5: `lw v0,0(s5)` at insn 37 and `lw a0,0(s5)` at 40 — s5 holds twicep. So twicep in s5. With the keepalive, twicep lives longer, but it's already s5.

What does the keepalive actually change? Let me look at the .greg/.lreg for orig (with keepalive) vs w1. But simpler: the natural C might use `twicep` again later, e.g. the source has a third read. Let me look at the function body: `L.w38 = *(u32 *)twicep;` and `w3c = *(u32 *)twicep;` — two reads. The keepalive after the GTE block. Maybe the original had a third read of twicep later? Or the value in `L.w38` is used later and comes from twicep.

Hmm, let me think about what "real C" keeps a parameter live to that point. The keepalive is placed right after the three gte_stsv calls and before the `L.q2A = ...` block. Maybe the original code re-reads twicep there, e.g. `L.w38 = *(u32*)twicep;` moved later? But the value is already stored in L.w38 (sp+56).

Wait, the diff is only about w3c's register (a0 vs s5). Maybe a real-C move changes w3c's allocation: e.g., declaring w3c differently, or using it differently.

Let me look at the full source body again:
```
u32 w3c;
u16 t;
...
L.w40 = 0x50000000;
L.w34 = *(u32 *)oncep;
L.w38 = *(u32 *)twicep;

w3c = *(u32 *)twicep;
L.v48[0] = ...
...
L.w3C = w3c;
w3c = (u32)L.o1;
L.v58[2] = 0;

gte_ldv0(L.v48); ...
gte_stsv((u16 *)w3c);
...
__asm__ keepalive twicep
L.q2A = ...
```

The target: `lw a0,0(s5)` at 40 loads w3c = *(u32*)twicep into a0. Then a0 is live until `sw a0,60(sp)` (L.w3C = w3c) and then reassigned to sp+16 (w3c = L.o1). So a0 holds w3c across the v48/v50/v58 stores. In mine, s5 holds w3c; but s5 also held twicep, so `lw s5,0(s5)` overwrites the pointer (fine, twicep dead). Target uses a0 for w3c, freeing s5? But target's s5 still holds twicep at insn 40 (source of the load) and is dead after. So in target, twicep's live range ends at insn 40, and w3c is a0.

In mine, w3c gets s5 — reusing twicep's register because twicep dies at insn 40 and w3c is born at 40. That's a "birth/death reuse" (local-alloc reuses the just-freed callee-saved reg). Why is w3c callee-saved at all? w3c is live across the GTE macros, which are NOT calls (inline asm). But gte_ldv0 etc. are macros with asm; do they clobber? They're asm volatile, and GCC treats asm as clobbering... Actually, w3c is live from insn 40 to insn ~59, spanning several inline asm blocks. Inline asm without clobbers doesn't kill registers. So w3c could be caller-saved a0. In target it's a0. In mine it's s5 because s5 (twicep) just died and local-alloc reused it.

Wait, local-alloc is per-block; w3c's block spans insns 40-? The GTE asm blocks might be in the same basic block. local-alloc would allocate w3c within the block: it needs a reg from birth 40 to death 59. The `used` set includes regs live at those insns. If a0 is not live there, w3c could get a0. But local-alloc's find_free_reg iterates reg_alloc_order; maybe s5 is preferred? No, callee-saved are avoided for local quantities unless... Actually local-alloc prefers caller-saved (call_used) regs? It uses `used = fixed_reg_set` for non-call-crossing qtys, then excludes regs live in the range. It iterates reg_alloc_order which for MIPS may be {a0,a1,a2,a3,v0,v1,...}. So a0 would be picked if free.

Why is a0 not free in mine? Because a0 might be live there in mine? No — in mine a0 isn't used at all in that region. Hmm, but the register allocator gave w3c s5, meaning a0..a3 and v0,v1 were all "used" during w3c's range? The GTE asm macros might be written to clobber a0? Let me look at the gte macros. `gte_ldv0`, `gte_rtv0tr`, `gte_stsv`. In common.h/psx macros, gte_rtv0tr uses `asm volatile("c2 ...")` maybe with "memory" clobber or specific regs. If an asm lists no clobbers, a0 stays free.

Actually, the keepalive's absence changes the alloc. Let me look at the difference between orig (keepalive) and w1 in the .lreg/global dumps. But maybe simpler: try real-C variants that keep twicep live or change w3c's birth.

Hypothesis: The original used `twicep` AFTER the GTE block (a third read), which is exactly what the keepalive emulates. What could that be? Perhaps `L.w38 = *(u32 *)twicep;` is not the original; maybe the original had `L.w38` assigned later or twicep used for something. Hmm.

Actually, maybe the original didn't have the `w3c` local at all; maybe it used `L.w3C` directly:
```
L.w3C = *(u32 *)twicep;
...
w3c = (u32)L.o1;
gte_stsv((u16 *)w3c);
```
Then the value loaded from twicep is stored to L.w3C (sp+60) immediately, and `w3c` is only the L.o1 pointer (born later). But the target does `lw a0,0(s5)` then LATER `sw a0,60(sp)` — the load's result is kept in a0 until the store at insn 59, not stored immediately. So the source must have a variable holding it across those statements: `w3c = *(u32*)twicep; ... L.w3C = w3c;`. So w3c is as in the source.

Why would w3c be a0 in target? Because the keepalive extends twicep's life, preventing w3c from reusing s5? Wait, if twicep is live THROUGH the GTE block (keepalive after), then twicep occupies s5 for the whole region, so w3c can't reuse s5 and must go elsewhere → a0! Yes! That's the mechanism. The keepalive keeps twicep in s5 until after the GTE block; without it, twicep dies at insn 40 and local-alloc gives s5 to w3c.

So to remove the lever with real C, we need twicep to be genuinely live across the GTE block. What real C uses twicep after the GTE calls? Maybe the original re-reads it: e.g., `L.w38 = *(u32 *)twicep;` placed AFTER the GTE block? But target stores L.w38 (sp+56) at insn 37, before. Hmm, `sw v0,56(sp)` at insn 37 is L.w38 = *(u32*)oncep? Let me map: 
- insn ~33: L.w40 = 0x50000000
- `lw v0,0(s5)` where s5=twicep? Wait, at insn 35 `sw v0,52(sp)` = L.w34? Let me re-dump from the start.
