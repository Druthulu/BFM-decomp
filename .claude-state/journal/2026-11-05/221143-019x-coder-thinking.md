---
ts: 2026-11-06T05:11:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_72uazRnHdbTykWehnLPZ
---
Now I see. In the barrier-free candidate:
- It loads `lh v0,18(sp)` (a+2) and `lh v1,26(sp)` (b+2) and does `move a1,v0`, `move a0,v1`.
- Then in the then-arm: `sh a1,122(s0)` (store a+2) — it uses the moved reg a1 rather than reloading.
- Target reloads: `lhu v0,18(sp); sh v0,122(s0)`.

Also the frame is 72 vs 56: target uses frame 56, with a at 16..? Wait, target stores a at 16(sp)? In candidate, a at 16(sp) and 24(sp) = b? Let me map: sh v0,24(sp) and sh v0,16(sp): the double assignment `*(s16*)(a+0) = *(s16*)(b+0) = ...`. So b at 24, a at 16? Actually `a` at 16(sp), `b` at 24(sp), `out` at 32(sp). Wait, candidate: `addiu a1,sp,16` (a), `addiu a2,sp,32` (out). Then call func_801502EC(e, a, out) — a1=a (sp+16), a2=out (sp+32). Then `move a0,s0; addiu a1,sp,24` (b) — func_80150460(e,b).

So a=16, b=24, out=32..40. Then out at 32, frame 72 means out could extend... Actually out[8] at 32-39. Frame 72: 40 + alignment 8? Hmm 72 = 40 + 32? Not sure.

Target frame 56 means a=16? Let me disassemble the target too. The target is in build/. Let me find the target object. `delever_search --explain` reads residual but let's dump the target from build. Actually easier: the dt diff shows target insn indices; let me get the target asm via the tool's --keep? No, target is the baseline object. Let me find build objects. The TU is src/shared/ov/func_80150170.h instantiated at each member's site. Hmm.

Alternatively, `--explain TU FN` prints the target? Let me check. Actually simpler: run --try with the orig body and --keep, then objdump: that gives the "target-equivalent" (score 0). Let me do that.
