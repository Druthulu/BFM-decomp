---
ts: 2026-11-06T15:51:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7r3OkNIz9Uj05kaZGQEA
---
Target: `la a0` at insn 2-4, and the call at insn ~35 (jal func_80052E38) with `addu s8,v0,v1` in the delay slot. So a0 is loaded early and held until the call.

Interesting: `sll v0,v0,0xe` before the jal — the OT computation.

So the la a0 is early because the arg's set is the first statement (low LUID), and sched2 put it first. The value in a0 is live until the call.

If plain C materializes the la at the call copy, the la's LUID is the call's — late. So the la would be right before the jal. Let me check c2.dis: where is the la a0? Earlier I saw mine has `lui a0; addiu a0` at insn 15-16 (after the pointer setups). Hmm, that's not at the call (which is ~insn 35). Why 15-16?

Because combine substituted the constant into the call-arg copy and deleted the first set; then the copy `a0 = const` is a separate insn at... its LUID is where the assignment statement was? The copy insn inherits the LUID of the original call-arg copy? Hmm.

Actually in c2, the la is at 15-16 which is right after `addiu s6,s4,4` and before `lui v0, D_800B9A02`. The source order: arg = ...; r = ...; mlo; mhi; c; va; vb; ot = ...; call. So the la at 15-16 corresponds to the `arg = &D_800AF648` statement's position (before ot), not the call. Wait, but combine deleted the first set and moved the constant into the call copy. The resulting `set a0 = const` would be at the call's position (after ot). Hmm, but the disassembly shows la at 15-16, before the D_800B9A02 load (which is the `ot = ...` computation). So maybe the la IS at the arg set's position: combine substituted but the set survived as `a0 = const`? Actually no: maybe cse changed the first set to `set (a0)` directly? 

Let me look at c2's disassembly around 15-40 and the call.
