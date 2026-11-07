---
ts: 2026-11-06T04:47:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9y5qAzErlzWbmsLjRdG7
---
b1: mine does `lui v1,0xffff`, then `lui v0 currentLocationId`, `lh v0`, then `ori v1,0xfff`. Target does `lui v1,0xffff`, `ori v1,0xfff`, then `lui v0`, `lh v0`. So sched1 placed the ori after the lh in mine. The difference: in target, the mask constant is formed contiguously. Hmm, this is a sched1 ordering of two independent instructions. Both orderings are valid.

Wait, target: 
```
138 lui v1,0xffff
13c ori v1,v1,0xfff
140 lui v0,currentLocationId
144 lh v0,0(v0)
148 lui a3,D_800C7C60
14c addiu a3,a3,0
150 sw ra,16(sp)
```
Mine:
```
138 lui v1,0xffff
13c lui v0,currentLocationId
140 lh v0,0(v0)
144 ori v1,v1,0xfff
148 sw ra,16(sp)
14c and v0,v0,v1
```
So mine interleaves the lh before the ori. Target forms the full mask first. This is a scheduling tie. In b1 with do-while, the ori got delayed. In b2 same score 5.

Maybe there are other candidates. What controls this? The `mask = ~0xF000` is a constant formed by lui+ori. sched1 prioritizes. In target, ori comes right after lui (adjacent). In mine the load of currentLocationId is scheduled between. Hmm.

Actually wait — in the target, the lh is at 0x140 and ori at 0x13c. Both independent. sched1 chose target order. In mine, sched1 chose lh before ori. Why would sched1 differ? Because the do-while changes block boundaries/dependencies? Maybe the mask variable is used in the and after the lh; the ori's scheduling depends on register pressure. 

Maybe try: make mask a variable computed differently, e.g., `s32 mask = -0xF001;`? Same constant. Or use `idx = currentLocationId & ~0xF000;` directly (no mask var) — then combine forms the constant inline. That could change codegen: `and v0,v0,v1` with v1 = ~0xF000; same.

What if `mask` is declared as u32? `u32 mask = ~0xF000;` = 0xFFFF0FFF; same bits, but signedness could affect combine.

Alternatively, the target has the mask constant in v1 and the loaded value in v0. Mine (a1 without do-while) had mask in a0 and D_800A2E20 in v1. With b1, mask in v1 and value in v0 — matching register assignments. Only the ori ordering differs.

Let's try more variants:
- b5: `s32 mask = -0xF001;` (same value)
- b6: compute `idx = currentLocationId & ~0xF000;` and drop mask var
- b7: declare mask as u32
- b8: use `s32 mask = ~0xF000; s32 idx;` then `idx = currentLocationId; idx &= mask;` (separate and)
- b9: put do-while around whole tail differently.

Actually maybe the issue is the `sw ra,16(sp)` placement: mine has it at 148, target at 150 (after a3 setup). The diff showed mine a3 setup at 15-16 vs target 6-7. So mine's a3 setup (lui/addiu D_800C7C60) is later than target. In b1 the diff was only about ori ordering and a3. Let me see full b1 diff (score 5): "insert mine[3:3] target[3:4] ori" and "replace mine[5:6] target[6:8] ori -> lui a3/addiu a3" and "delete mine[15:17] target[17] lui a3/addiu". So effectively the a3 setup moved from position 15 to 6, and ori from 5 to 3. These are both sched1 orderings of the a3 (D_800C7C60 address) setup.

Why is a3 setup early in target? Because `p = &D_800C7C60` is used in `*p = val` which is in the do-while block later... Hmm in target (barrier) the a3 setup is at 6-7, right after the lh. In b1 it's at 15-16, after the two loads.

So the do-while around the stores made the a3 setup later, but the target (with barrier) has it early. Confusing: with the barrier, a3 was set early; without barrier (a1), a3 was set early too (at 150-154 in a1 dump). In a1: 150 lui a3, 154 addiu a3 — yes early. In b1: a3 setup at 16c — late. So the do-while moved a3 late, overshooting.

Hmm. Maybe the right approach is different: keep the stores' source order but create a dependency that prevents the D_800A2E20 store hoist only. In a1, the problem was: D_800A2E20 address (v1) + store to D_800C7C64 hoisted before the and/loads; mask in a0. In target, D_800A2E20 address is formed late (after lh val) and store after.

So we need D_800C7C64 = &D_800A2E20 to stay late, while keeping p=&D_800C7C60 early. Idea: make the D_800A2E20 store depend on `val`, genuinely? In the target it's after the val load but doesn't depend on val. sched1 schedules it there. We could write `D_800C7C64 = &D_800A2E20;` after `*p = val;`? Then it depends on nothing still.

What if we make it a genuine dependent expression: e.g. `D_800C7C64 = (s32 *)&D_800A2E20;` no. 

Hmm, what about assigning via a local variable initialized with the load: e.g., `s32 *q = &D_800A2E20; ... D_800C7C64 = q;` didn't help (b4 score 17, same as a1).

What about doing the stores through p: `p = &D_800C7C60; *p = val;` and D_800C7C64 store — the target's a3 = D_800C7C60 address is set early, then used for the store in the delay slot of bltz at 18c. The D_800A2E20 store uses `at` (address of D_800C7C64) at 180.

Perhaps a better lever: change the order of declarations/initializers so cse/sched1 produce target order. E.g., `s32 *p = &D_800C7C60;` after val. Already.

Let me try the "no mask variable" variant, and also try declaring mask/idx differently, and try making the D_800A2E20 store use a cast: `*(s32 **)&D_800C7C64 = &D_800A2E20;` — probably same.

Another idea: the `D_800C7C64` is declared as `extern s32 *D_800C7C64;` in-body. The store writes a pointer. What if the value is `(s32 *)&D_800A2E20` vs `&D_800A2E20` — same.

Let me try several quickly.
