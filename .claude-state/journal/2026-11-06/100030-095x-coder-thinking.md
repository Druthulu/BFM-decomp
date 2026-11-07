---
ts: 2026-11-06T17:00:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EyEYXEIJytbOMTzdOwYw
---
Still 3. The cache persists.

Let me reconsider: maybe the `addiu s1,sp,32` comes from the *struct copy* itself, not from the RotMatrixY arg. Look at the objdump: e74 `addiu s1,sp,32` is placed right before the RotMatrixY call, after the copy. Then e7c `move a1,s1` (delay slot), e80 `move a0,s1`.

Hmm, so s1 = &m is computed once and used for both. If I could make the copy use a *different* base spelling... The copy's destination is `m` (sp+32). After the copy, cse knows sp+32.

Idea: do the struct copy into a *different* variable and then... no, m is needed.

Idea: make the func_800484EC call's &m a *fresh* address by using a pointer variable that's assigned AFTER the RotMatrixY call:
```
RotMatrixY(ang & 0xFFF, &m);
...
q = &m;
func_800484EC((s32)q, ...);
```
That still computes &m once (after the call) — the target's addiu a0,sp,32 is placed BEFORE the call by sched, but it's still a remat. If q = &m is after the call, cse can't cache it across the call... but sched might hoist the addiu. Let me try.

Actually the target has `addiu a0,sp,32` at e7c (before the call) — sched hoisted it into the pre-call region. So the source probably had the &m use after the call, and sched hoisted the addiu. That's consistent!

So: move the &m computation for func_800484EC to AFTER the RotMatrixY call (in source order):
```
RotMatrixY(ang & 0xFFF, &m);
q = &m;
func_800484EC((s32)q, ...);
```
Hmm, but that's the same value.

Wait, the key: if the &m for func_800484EC is a *separate* expression after the call, cse still CSEs it with the RotMatrixY arg if it's live in a register. But if the RotMatrixY arg's register dies at the call, cse must remat.

In mine, cse cached &m in s1 (callee-saved) across the call, so it survives. Why? Because cse saw the later use and decided to keep it.

Hmm, cse doesn't "decide" to keep values in callee-saved registers — that's global-alloc's job. Actually, cse replaces the later `&m` computation with a register copy if the value is available. Since the value must survive the call, global-alloc puts it in a callee-saved reg (s1).

To prevent cse from doing that, the expressions must differ or the value must be invalidated by the call. A `&m` (sp+32) is not clobbered by a call (it's a constant address, cse treats it as rematerializable). Hmm, cse's `find_best_addr` might prefer remat for constants. But here it chose a register.

What if the RotMatrixY argument is a *variable* q, and the later use is `&m` (a different expression)? Then cse equates q's value with &m... 

I think the cleanest fix: make the RotMatrixY argument NOT share the &m expression, e.g., pass `q` where `q = &m;` and then dead-reset q, and pass `&m` later. That's y01's structure (q block + &m later) — which worked with the hand-expanded copy. In z01 it doesn't.

Hmm, why did it work in y01? Let me objdump y01 to see the &m handling and compare. Maybe the difference is the s-launder (an asm) which acts as a cse barrier. In y01, the s-launder is before the copy block; cse's equivalence table might be reset by the asm? No, asm doesn't reset cse.

Let me objdump y01's tail.
