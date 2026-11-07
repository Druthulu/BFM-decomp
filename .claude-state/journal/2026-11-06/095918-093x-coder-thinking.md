---
ts: 2026-11-06T16:59:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i9NtwryCgMXwDCzp6JIl
---
z01:
```
e70 andi a0,v0,0xfff
e74 addiu s1,sp,32      ; cache &m
e78 jal RotMatrixY
e7c move a1,s1
e80 move a0,s1          ; &m for func_800484EC
e84 addiu a1,sp,16
```
Target:
```
e70 andi a0,v0,0xfff
e74 jal RotMatrixY
e78 addiu a1,sp,32      ; q (delay slot)
e7c addiu a0,sp,32      ; &m for func_800484EC
e80 addiu a1,sp,16
```
So the target rematerializes &m twice; mine caches in s1. The q dead-reset doesn't prevent it because cse CSEs `&m` (sp+32) from the struct copy's store base.

To prevent: after the struct copy, the register holding sp+32 (s1) must be invalidated. Since the struct copy uses a2 as the source base and the destination base is sp+32 materialized inline in the sw instructions (`sw v1,32(sp)` — no register!). The sw instructions use sp-relative addressing, so there's no &m register after the copy. Then `q = &m` materializes sp+32 into a register (s1), RotMatrixY uses it, and q=0 kills q. But then `func_800484EC((s32)&m,...)` reuses s1.

Wait, the s1 addiu is at e74, before the call. Then `move a1,s1` and `move a0,s1`. So cse decided &m is in s1 and reused it for both. The q=0 reset should invalidate it... unless the reset is a dead store that flow deleted BEFORE cse? No, cse runs first (cse1 before flow? order: cse1 (cse_insn) then jump1 then flow1 then combine... Actually the pass order: ... cse (1st), loop, cse (2nd), jump, flow, combine, sched... So cse1 runs before flow. The q=0 is deleted by flow (after cse). So at cse time, q=0 exists and kills the q equivalence.

Hmm, but the &m value in s1: cse tracks `q` as holding &m. `q = 0` kills q. But the *expression* `&m` might be in the cse table keyed by the address expression (sp+32), and cse might have recorded a register containing it. After q=0, that register (s1) still contains &m but cse's table for the expression is invalidated only if the register is clobbered... Actually cse's `invalidate` on `(set q 0)` removes equivalences mentioning q. The expression `sp+32` was equated to q; after q is set, that equivalence is gone. So at func_800484EC, cse should recompute `&m`. But it reuses s1 anyway.

Maybe the RotMatrixY call is what caches it: the argument q is passed in a1; cse might keep the value across the call in a callee-saved reg (s1) because it's needed later (for the func_800484EC arg). Wait, func_800484EC's arg is `&m` — a separate expression but CSE'd with q's value. cse sees the same expression `&m` at the call site; since the address is constant, it materializes it — but it could rematerialize (addiu) instead of caching. The target rematerializes.

The difference between target and mine might be sched1's placement: the target's `addiu a0,sp,32` at e7c is placed before the RotMatrixY call (a0 is free), while mine caches in s1.

Hmm, this is a cse decision (remat vs cache). gcc's cse has `find_best_addr` and prefers rematerialization for constants? The presence of a register holding the value makes cse use it.

To force remat: make `&m` not CSE-able with q. E.g., don't use a q variable at all:
```
RotMatrixY(ang & 0xFFF, &m);
```
without the q launder/reset. Then there's no register holding &m across the call... but cse may still materialize &m once and reuse it for func_800484EC. Let me test: struct assignment + `RotMatrixY(ang & 0xFFF, &m);` (no q at all) + `func_800484EC(&m,...)`.

Actually, that's the simplest. Let me try ac01: replace the q block with a direct RotMatrixY(ang&0xFFF, &m). And the func_800484EC direct.

Also ac02: keep q but don't reset (q used only for RotMatrixY).

Let me test.
