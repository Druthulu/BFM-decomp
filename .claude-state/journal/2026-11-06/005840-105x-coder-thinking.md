---
ts: 2026-11-06T07:58:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qDssYwl4goKnrfjH9b2K
---
All ~6. The score-1 was on a different body version. Let me think differently.

Let me reconsider: maybe the natural C doesn't have the `w3c` variable at all, and the loaded value is used in a way that gives a0. Let me look at the target's a0 usage more: `lw a0,0(s5)` at 40, `sw a0,60(sp)` at 59, `addiu a0,sp,16` at 60, `sh t4,0(a0)` etc. So a0 is the loaded value then the pointer.

What if the source is:
```
w3c = *(u32 *)twicep;
...
L.w3C = w3c;
w3c = (u32)L.o1;
```
and the natural C has `w3c` declared as `s32` (not u32)? Same.

What if `w3c` is a `void *`? Then `L.w3C = (u32)w3c;` and `w3c = L.o1;` — pointer class. The allocno would be a pointer; the target's r79 is not marked pointer (per alloc_table "GR_REGS or none" without "; pointer"). Hmm.

Let me look at what the target's r79 conflicts would be. In the natural target, r79 gets a0. The conflict set must include 21 (s5). Let me check the target's .greg? We don't have the target's RTL (only the object). But the orig (keepalive) RTL reproduces the target's allocation (score 0). So in orig, r79 conflicts with 21. The keepalive gives r77 a long life. So the natural C must give r77 a long life too.

Therefore the natural C MUST keep twicep live across w3c's range. There must be a real use. Since the target binary has no s5 use after insn 40, the use must be one that produces no instruction. 

What produces no instruction? A use of a value that's already available in a register AND the result is used in a way that doesn't need an instruction... For example, a use in an inline asm! But the original is pure C.

Wait — maybe the original DID have an inline asm (the Sony GTE macros are asm!). The GTE macros (`gte_ldv0`, `gte_rtv0tr`, `gte_stsv`) are inline asm. If one of them mentions `twicep`... no.

What if the original passes `twicep` to `func_800174DC`? Let me check func_800174DC's signature. The final call in target: `jal func_800CAE0C` (relocated) with `sh v0,48(sp)` in the delay slot. If func_800174DC took an argument, there'd be an a0 setup. There isn't. But wait — maybe func_800174DC takes an argument and the source passes `arg0` which is still in a0? Let me check: at the final call, what's in a0? a0 was set to sp+16 and used for the sh stores. So a0 = sp+16. If func_800174DC(arg0) were called, a0 would be arg0, not sp+16. No.

Hmm, let me look at the source's `func_800174DC()` declaration. It's called with no args. Let me check the function definition.

Alternatively, maybe the natural C's use of twicep is `L.w38 = *(u32 *)twicep;` placed at line 59 (after the stores) instead of line 440, and the target's early `lw v0,0(s5); sw v0,56(sp)` at 37 is sched1 hoisting it. Then twicep is used at ~59, so live across w3c's range → conflict → a0! And the load at 37 could be hoisted by sched1? That's a long hoist (from 59 to 37). Unlikely but let me test: move `L.w38 = *(u32 *)twicep;` to after `L.w3C = w3c;` and see.

Actually, the target's `lw v0,0(s5)` at 37 loads *twicep for L.w38, and `lw a0,0(s5)` at 40 loads *twicep for w3c. If the source had both reads at ~59, sched1 would need to hoist both. Hmm.

Wait — maybe the two reads are at 440 and 442 in the source, and the natural C's *third* use of twicep is the `L.w38` store repeated? Let me look at the target's `sw v0,56(sp)` at 38 — L.w38. And `sw a0,60(sp)` at 59 — L.w3C. 

Let me try moving `L.w38 = *(u32 *)twicep;` down to just before `L.w3C = w3c;`:
```
L.w34 = *(u32 *)oncep;
...
L.w3C = w3c;
L.w38 = *(u32 *)twicep;
w3c = (u32)L.o1;
```
Then twicep is used at 59 (late), keeping it live across w3c's range. The L.w38 load would be at 59-ish; sched1 might hoist it to 37. Let me test.

Also: maybe `L.w38` is written twice? Hmm.

Let me try a batch of "move L.w38 read later" variants.
