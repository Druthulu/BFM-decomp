---
ts: 2026-11-06T16:39:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fZyaU0Ey0c37IHwVEXVt
---
Item 2 orig.c is fresh. Good.

Now item 2: launder only. The launder is `__asm__ __volatile__("" : "=r"(pv));` at the end, a "zero-byte 2nd SET: kills the sched1 birthing boost". Let me look at the target.s for item 2 to understand the residual and think about the crack.

The launder is an asm with an output operand (out-only, "=r"(pv)) — it's a zero-byte 2nd SET of pv that kills sched1's birthing boost. The mechanism: `pv = *(u32*)p;` is a single-set value that sched1 boosts (sinks to its consumer). The asm out-only re-defines pv, making it a 2-set value → no birthing boost.

Real-C replacement: make pv a 2-set value with a dead second set, e.g., `pv = ...; pv = pv;`? A self-assignment folds. The dead-reset trick (C0414): `p = expr; f(...); p = 0;` — a dead reset immediately after. Here: `pv = *(u32 *)p; *(u32*)p = ...pv...; pv = 0;` — a dead reset after the last use would be a 2nd set, killing the birthing boost, and flow deletes it before sched1 (zero bytes!). C0414 says exactly this. Let me try `pv = 0;` after the uses.

Wait, but the launder is out-only asm placed at the very end (after func_80016638). It re-defines pv (a 2nd set). C0414's dead-reset: put `pv = 0;` after the last use. That should be equivalent. Let's try.

Also the launder is "out-only" which means it doesn't read pv — a dead 2nd set. So `pv = 0;` (or any constant) is the natural replacement. Let me test.

First baseline: orig scores 0. Then w1: remove the asm line → score? Then add `pv = 0;`.

Let me also read the target.s to know what to expect. But let's just test.

Item 2 timing starts now (09:39:33). Let me do the tests.
