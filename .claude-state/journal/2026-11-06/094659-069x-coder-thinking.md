---
ts: 2026-11-06T16:46:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F2aPuHqv4XSIWtu3k7BX
---
Target: for the laundered calls (D_801BFCC4 + 0x84), it emits:
```
lui a1,0; addiu a1,a1,0   (D_8018E2DC)
addiu a2,a1,48
lui a0,0; lw a0,0(a0)     (D_801BFCC4)
move a3,zero
sw s3,16(sp)
jal func_8017D8A4
addiu a0,a0,132           (delay slot)
```
So a1 = symbol address, a2 = a1+0x30 — no register holding m.

Mine without the launder: `move a1,s2; move a2,s5` — hoisting the symbol address into callee-saved registers s2/s5 across calls, adding spills.

Why does the compiler hoist? Because `(s32)D_8018E2DC` — if D_8018E2DC is a scalar global (s32?), the value is loaded once and kept in a register across the intervening calls (the compiler thinks the value doesn't change... but calls could modify globals; GCC must reload globals after calls unless it can prove). Hmm, actually the value IS the address of a global array (used as a pointer `(void *)m`). `D_8018E2DC` might be declared as `u8 D_8018E2DC[]` → `(s32)D_8018E2DC` is the address (a constant!). Then cse/loop hoists the constant address into a register once and reuses it across calls. That's why mine has `move a1,s2` where s2 = &D_8018E2DC.

The asm launder forced a fresh materialization per call. To get the target's behavior in real C, we need to prevent the address constant from being hoisted into a callee-saved register while still using it. The target materializes the address fresh at each of the first 3 calls (lui/addiu) and then... let's see group 2: `D_801BFCBC + 0x84` with m = D_8018E2DC. In target, does group 2 use lui/addiu again or a register? Let's read further.

Actually, an easier thought: maybe the original source used the symbol differently, e.g. passing `&D_8018E2DC` as a `void *` (address-of) rather than `(void *)(s32)D_8018E2DC`. That's the same address constant. Hmm.

Why does the target materialize it fresh each time for the laundered sites but keep it in a register for the non-laundered ones? Wait, let me look at group 2 in target.
