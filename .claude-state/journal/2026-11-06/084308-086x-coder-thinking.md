---
ts: 2026-11-06T15:43:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Te28Uy3OdCDWZVToTh9x
---
This is the sched1 dump with priorities. The block containing the mult is a different block. Rather than dig deep, let me try experiments.

The difference: in mine the constant load chain (lui/lw/nop/addiu) is hoisted before mflo (into the mult delay slots), using v1; target places it after `addiu a2,v0,8` using v0.

This looks like a sched1 ordering where the launder's 2nd set of n makes the `addiu a2,v0,8` (n = q+8) an "insn" that... hmm.

Let me just try variants:
f1: temp for the constant: `s32 c = D_80126950 + 0x1F4; d = n * c / (ret * 4);`
f2: reorder: move `x = o.sxy[0]; y = o.sxy[1];` before `d = ...`.
f3: `d = n * (D_80126950 + 0x1F4) / (ret * 4);` written as `d = (n * (D_80126950 + 0x1F4)) / (ret * 4);` same.
f4: dead-reset n: `{ s32 keep = n; n = 0; n = keep; }` before d.
f5: `n = n + 8`? no, n = q + 8.

Wait — maybe the launder here is about the *value* of n being needed twice? n is used only in `d = n * (...)`. Hmm, then what does a 2nd set of n do? It changes the birth of n's value: n = q+8's addiu gets a REG_DEP_OUTPUT? sched1's birth boost is for insns that birth a register.

In mine, `addiu a2,v0,8` is at 8a4 AFTER mflo (8a0) and the constant chain is hoisted into the mult's delay slots. In target, `addiu a2,v0,8` at 894 right after `sra v0,t0,0xc` (890), then the constant chain at 898-8a4, then mult.

The difference: target has n's addiu before the constant chain; mine has the constant chain before n's addiu. So the launder delays/advances the addiu.

The sched1 priority: an insn that births a register (REG_DEP_OUTPUT?) gets a boost. The launder is a second set of n, which might make the addiu's output less "birth"-critical... 

Actually the moves note: "the re-tie's REG_DEP_OUTPUT on the arg-setup pins the load before li a1,320; lever-free the load coalesces into a0". Here the asm has "=r"(n) as output and "0"(n) as input — REG_DEP_OUTPUT on n.

Hmm. What real C creates a REG_DEP_OUTPUT-ish effect? 

Honestly, let me just try a bunch of variants quickly:
f1: const temp
f2: reorder x/y before d
f3: dead-reset n via keep
f4: `n = q + 8; n += 0;` folds
f5: compute d in two steps: `d = n * (D_80126950 + 0x1F4); d = d / (ret * 4);`
f6: `d = (D_80126950 + 0x1F4) * n / (ret * 4);` (operand order swap)
f7: `d = n * (0x1F4 + D_80126950) / (ret * 4);`

Let me test.
