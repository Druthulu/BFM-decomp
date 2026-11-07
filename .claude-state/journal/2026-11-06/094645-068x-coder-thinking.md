---
ts: 2026-11-06T16:46:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JMDci4ru2MRPOg7BCNj3
---
Without the launder, the body spills: it uses s7,s6,s5,s4 (extra callee-saved regs) and a bigger frame (64 vs 48). The launder was keeping the address `D_801BFCC4 + 0x84` etc. as a symbol constant (lui/addiu) rather than keeping values in registers.

Target uses `lui a1,0; addiu a1,a1,0; addiu a2,a1,48` — i.e., a1 = D_8018E2DC (symbol), a2 = a1+0x30. Mine uses `move a1,s2; move a2,s5` — keeping the symbol address in a callee-saved register (s2/s5). So the launder made the compiler reload the global symbol address per call instead of hoisting it into a register.

So the real-C fix must prevent cse/loop from hoisting the `(s32)D_8018E2DC` load into a register across calls. The asm forced a fresh load each time.

The pattern: `func_8017D8A4(D_801BFCC4 + 0x84, (void *)m, (void *)(m + 0x30), 0, 1);` where m = D_8018E2DC (a symbol address? D_8018E2DC is likely a u8 array or a symbol). Note the non-laundered calls exist too: `{ s32 m = (s32)D_8018E2DC; func_8017D8A4(D_801BFCBC + 0x84, ...); }` — so the same m is used without a launder later, and target shows those as `move a1,s2` (register) vs `lui/addiu` for the laundered ones? Let's look at the target to understand which sites use symbols and which use registers.

From the diff: target lines 151-157: 
```
lui a1,0
addiu a1,a1,0
addiu a2,a1,48
```
and mine uses `move a1,s2; move a2,s5`. These are the laundered sites (first 3 for D_8018E2DC/E2E8/E2F4 with D_801BFCC4).

The non-laundered ones (D_801BFCBC + 0x84 etc.) — target presumably uses `move a1,s2` (register) since the symbol was loaded once earlier? Actually the source has three groups:
1. D_801BFCC4 + 0x84/0x90/0x9C with m = D_8018E2DC/E2E8/E2F4 — laundered.
2. D_801BFCBC + 0x84/0x90/0x9C with m = D_8018E2DC/E2E8/E2F4 — not laundered.
3. D_801BFCB4 + 0x3C/0x48/0x54 with m = D_8018E27C/E288/E294 — laundered.
4. D_801BFCBC + 0x3C/0x48/0x54 with m = D_8018E27C/E288/E294 — not laundered.

Target: for group 1, a1 = symbol (lui/addiu) and a2 = a1+0x30. For groups 2/3/4? Let's look at target.s around those.

So the launder forces a fresh symbol load for group 1; the non-laundered groups use a register holding m from... hmm, but the groups are in source order: group1 (laundered) first, then group2 (not laundered). If m were hoisted into a register at the first use, group2 would reuse it. But target's group1 uses the symbol each time and group2 uses a register. That suggests the register is set at group2's start.

So the launder's effect: the first three calls (group1) each load the symbol fresh (3 lui/addiu pairs); then group2 loads D_8018E2DC into a register (s2) and reuses. Hmm.

Let's read the target.s.
