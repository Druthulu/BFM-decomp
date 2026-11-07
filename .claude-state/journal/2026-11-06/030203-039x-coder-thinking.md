---
ts: 2026-11-06T10:02:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vbs3tWBM6cT3GyM0PKgh
---
Item 4: the difference is a register swap: f (the flag) should be in v1, but mine has it in a1. And the loop counter i1 should be in a1, but mine has it in v1. So v1↔a1 swap. This is the greg priority issue that the keepalive addressed: the keepalive added a reference to i1 so i1's priority > f's... wait.

Target: f in v1 (`move v1,zero`, `li v1,1`, `beq v1,v0`), i1 in a1 (`lui a1`, `lw v0,0(a1)`, `addiu a1,a1,4`, `beq v1,v0`).

Mine: f in a1, i1 in v1.

The keepalive `__asm__("" :: "r"(i1))` inside the loop adds refs to i1, raising its priority so it gets a1 (the lower-priority caller reg?) over f which gets v1. Hmm, actually target has i1 in a1 and f in v1. Without the keepalive, i1 gets v1 and f gets a1.

To fix lever-free: increase i1's ref count/priority or decrease f's. Real-C moves: 
- Use i1 in more expressions (add a reference): e.g., write the loop so i1 is used twice per iteration.
- The loop is `for (i1 = 0; i1 < 5; i1++) { if (*(u16 *)(D_801AECD8[i1] + 2) == 5) f = 1; }`.

C0535: `do { } while (0)` inside a loop body increases loop_depth-weighted refs. But here the keepalive is `"r"(i1)` — it adds a use of i1 per iteration. A do-while wrapper around a use of i1: `do { r = i1; } while (0);`? Hmm, but that would add a use of i1 in a statement. Actually the note in the source says: "the zero-byte `"r"(i1)` keepalive adds the 5th reference to the loop counter, which lifts its global_alloc priority above the strength-reduced pointer giv's -- that is what puts the counter in $a0 and the giv in $a1 (without it they swap)."

Wait, it says "puts the counter in $a0 and the giv in $a1". But target shows i1 (counter) in a1? Hmm, and the giv... let me check: target has `lui a1,0; addiu a1,a1,0; lw v0,0(a1)` — that's the D_801AECD8 base? and `addiu a1,a1,4`? Hmm, the giv is the pointer into D_801AECD8: `D_801AECD8[i1]` → base + i1*4. If i1 is in a1 and used with `lw v0,0(a1)`, then a1 is the pointer giv, not the counter! Let me re-read.

Target at 135-137: `lui a1,0x0; addiu a1,a1,0` (D_801AECD8 address); `lw v0,0(a1)`. Then 147: `addiu a1,a1,4` — yes, a1 is the pointer giv walking D_801AECD8. And v1 is the counter: `move v1,zero` (i1=0), `li v1,1` (comparison with 5? no...), `beq v1,v0`. Hmm, `li v1,1`? The loop condition is i1 < 5, so `slti v0,v1,5` maybe. Let me look at the actual target loop region.

Wait, the diff lines: mine[143] `li a1,1` vs target `li v1,1`; mine[147] `addiu v1,v1,4` vs target `addiu a1,a1,4`; mine[153] `beq a1,v0` vs target `beq v1,v0`.

Hmm, confusing. Let me dump both loops fully. Let me get mine and target around those indices.

Actually, the source note says the keepalive puts the *counter* in $a0 and the *giv* in $a1. But target here: which reg is the counter? Let me look at the full target loop.

Let me disassemble both objects around the loop (addresses ~2e?? for target). Let me find the loop by searching for `slti` or the branch to 2fb4.

Let me get mine's disassembly too.
