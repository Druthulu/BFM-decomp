---
ts: 2026-11-06T08:55:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FYyJz38XSf7ZmMLhyeHu
---
The residual: mine has 512 insns and target 512? The diff shows jumps at different addresses — a 5-insn shift between mine and target (mine[162] ↔ target[167]). That means mine is missing 5 instructions *before* insn 162, i.e., the asm's computation `(a[2] - z) * buf[5]` produced 5 instructions (load a[2], subu, load buf[5], mult/mflo, etc.) that the target keeps? Wait no: the asm is a *use* of `(a[2]-z)*buf[5]` — the expression's code is generated to feed the asm's register operand. Removing the asm removes the whole computation (5 insns). The target (compiled with the asm) has those 5 insns. So we need real C that keeps those 5 insns and the result is used or not.

The target's 5 insns are probably: lw a2? `(a[2] - z) * buf[5]`: lw t,8(a); subu t,t,z; lw u,20(buf?) buf[5] is at offset 20; mult; mflo → 5 insns. The asm makes the result live into a register but the value is unused.

So the real C must compute `(a[2] - z) * buf[5]` and use it in a way that generates the same 5 insns but the result is not stored. Real C can't have an unused expression... unless it's assigned to a variable that is later used? If assigned and used, extra code. If assigned and unused, flow deletes it (flow-unused-result wall).

Hmm. But wait: maybe the original C *did* use this value somewhere, and the decompiler replaced that use with the asm because... Let me look at the target's disassembly around the asm to see what the 5 insns are and what happens to the result. Since the pins $4 are involved: `idx` and `otp` are pinned to $4. The asm's expression is `(a[2] - z) * buf[5]`. The result might be computed into a register that's then... The asm `"r"(expr)` forces the expr into a register, but the register is arbitrary.

Let me dump the target asm around that point. The build object: build/src/ov_SC02_021/ov_SC02_021_jr_8017C294.o. Let me disassemble func_8017DC10 and find the region: the asm is after `func_8017E410(mode1, buf)` in the first if-block. Search for the mult/div sequence. The first if-block is early in the function. Let me disassemble and look at the first ~100 insns.

Actually, better: diff mine vs target gives the 5-insn shift starting at insn 162. So the asm's 5 insns are at target[162..166]. Let me dump the target and print insns 155-175.

The target disassembly = build object. Let me objdump func_8017DC10.
