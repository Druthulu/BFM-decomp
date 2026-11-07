---
ts: 2026-11-06T15:13:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WT0WssvHRk5QWoXyc36Z
---
i2: the delay slot is a nop and the ori moved later. Worse.

c_i1 (score 2) is the best: only the li a0,2715 vs ori order.

Let me try to flip that. Ideas:
(a) Move `vol = vol | 0x3000;` to AFTER `sx = sx << 8;` — that's i1 (ori before li).
(b) Make the li earlier: the li is arg0 = 0xA9B. What if arg0 is a variable? No (would add a set).

Hmm, sched1 priority: insns are scheduled in order of decreasing priority. The li a0 (constant) has a path to the jal of length 1 (the jal's arg). The ori's path: ori → or → andi → jal = 3. So the ori should have HIGHER priority and go first — that's what mine does. But target has li first!

In target, the ori is *part of the arg expression*, so in the RTL the ori is... hmm, same.

Unless in the target the li a0 is not from the call arg but from something else. `li a0,2715` = 0xA9B. It's the first arg of func_8002D4C8. In target it's at 4b90, before the ori at 4b94.

Hmm, in target the ori is `ori a1,a1,0x3000` where a1 = vol. Maybe in target the ori comes from a different expression: `(0x3000 | sx)`? No, that would be ori a2.

Wait — maybe in the target the `ori a1,a1,0x3000` is scheduled late because of a dependency: vol's value (a1) is only ready at 4b68, and sched1 had to place it... no, both are ready.

Alternatively, sched1's ordering with equal priorities is by insn number (birth order). In target, the li's RTL insn is born BEFORE the ori (the call arg setup order: the first arg is materialised first). In mine, the ori is a separate statement born before the call.

So: make the ori be born AFTER the li, i.e. keep the ori in the call arg expression (as target) and get the 2nd set elsewhere.

Hmm! So back to: 2nd set elsewhere = the u16 cast → delay-slot problem.

BUT: what if the 2nd set elsewhere is a *dead* set (C0414 dead-reset style) that flow keeps? E.g. `vol2 = vol;` (dead copy) + ... moves.md line 199: "dead copy vol2=vol + a 2nd def vol=vol|0x3000 (both dead in the RTL)". 

Idea: 
```
s32 vol2;
...
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol2 = vol;        /* dead copy — gives vol a use? */
...
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
A dead copy `vol2 = vol;` would be deleted by flow (dead store to a dead local) → no effect.

What about `vol = vol;`? folded.

Hmm.

Alternative: get the 2nd set of vol from the *target's own* `ori a1,a1,0x3000` by writing the arg as `(vol | (0x3000 | sx)) & 0xFFFF` (target spelling, no 2nd set) — that's the plain drop (score 30).

So we need the ori to be a real 2nd SET of vol (so that vol is multi-set and sched1 doesn't birth-boost the pan mult), while keeping the arg expression shaped so the li is born first.

Idea: write the arg as `((vol = vol | 0x3000) | sx) & 0xFFFF`? An assignment inside the expression. In gcc 2.7.2, the assignment's RTL would be born at the point of the expression evaluation — i.e. during the arg setup, possibly after the first arg's li. Hmm! That could work: `func_8002D4C8(0xA9B, ((vol = vol | 0x3000) | sx) & 0xFFFF);`

Hmm, but the second arg is expanded... the order of expansion of args is right-to-left typically (PUSH_ARGS_REVERSED). For a call with 2 args, gcc expands args in reverse order (last first) for pushing. On MIPS, args go in registers; expand_call expands them in order? In gcc, `expand_call` expands args in reverse order if PUSH_ARGS_REVERSED.

Risky but cheap to try.

Another idea: keep `vol = vol | 0x3000;` as a statement but place it BEFORE the vol division? No, must be after.

Another idea: place `vol = vol | 0x3000;` right after the vol division (before the sx division). Then the ori is born early; sched1 might schedule it... but it could also fill the delay slot.

Let me try several:
- j1: assignment inside the arg: `func_8002D4C8(0xA9B, ((vol = vol | 0x3000) | sx) & 0xFFFF);` (no separate statement)
- j2: `vol = vol | 0x3000;` placed right after the vol division, arg `(vol | sx) & 0xFFFF`.
- j3: keep the target arg spelling `(vol | (0x3000 | sx)) & 0xFFFF` AND add a dead 2nd set: `vol = (vol | 0x3000) & 0xFFFF;` before the shift? hmm.

Try j1 and j2.
