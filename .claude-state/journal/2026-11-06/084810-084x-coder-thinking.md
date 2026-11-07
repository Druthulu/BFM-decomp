---
ts: 2026-11-06T15:48:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5x1OZJIUC5ysNNLIQB08
---
Big diff. The launder removal shifted many things:
1. The `arg` launder: mine has `lui a0; addiu a0` at insn 15-16 and no `la`? Target has `lui s3... ori s3,s3,0xffff`... hmm.

Wait, target insn 3: `ori s3,s3,0xffff` vs mine `addiu s3,s3,0`. That's about mlo=0xFFFFFF being in s3? Hmm, target: lui s3,0xff; ori s3,s3,0xffff → 0xFFFFFF. Mine: lui s3,0xff; addiu s3,s3,0 → 0xFF0000? Wait that seems wrong... Actually mine insn 3 `addiu s3,s3,0` = 0xFF0000? and target `ori s3,s3,0xffff` = 0xFFFFFF. Hmm but mine should still be correct; maybe mine has mlo in s3 as 0xFFFFFF via a different sequence (lui s3,0x100; addiu s3,-1)? Let me not over-analyze the diff listing (it's a shifted alignment).

The real issue: the `arg` launder removal caused the base register to shift: mine uses s3 for r, target uses s4; and mine materializes arg (a0 = &D_800AF648) inside the loop prologue instead of the first statement.

Actually the C says the `arg` launder is load-bearing to keep `la $a0, D_800AF648` first in the prologue: "The zero-byte __asm__("" : "=r"(arg) : "0"(arg)) blocks that substitution; the call's argument copy becomes a no-op and is deleted."

So the `arg` launder must be replaced by a real-C construct that blocks combine's substitution of cse's REG_EQUAL constant into the call-site copy, and deletes the first set. Hmm — the target has the `la` (lui/addiu a0) at the very beginning (insn 15-16 in mine vs target?). Wait, target insn 12-16: `addiu s2,s4,41`, `addiu s5,s4,20`, `addiu s6,s4,4`, then nothing at 15-16. Mine has `lui a0,0x0; addiu a0,a0,0` at 15-16. So MINE has the la in the prologue; target does NOT at 15-16? Hmm, the target's insn 23-25 has `sw s0,72(sp)`.

Let me disassemble both to see the actual first 40 insns. Since orig (with launder) = target. Let me disassemble orig and c1.
