---
ts: 2026-11-07T00:49:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ErXhFRHQOFLegBKEeAE1
---
Mine: 842c sw zero,0(s0); 8430 addiu v0,v0,1; 8434 lui at; 8438 sw v1,0(at); 843c lui at; 8440 sw v0.

Target: 842c sw zero,0(s0); 8430 lui at; 8434 sw v1,0(at); 8438 addiu v0,v0,1; 843c lui at; 8440 sw v0.

So in the target the addiu comes AFTER the sw v1 (and after its lui at). Mine has the addiu before the lui at.

The addiu is independent of the sw v1 group (it feeds the last store).

So sched1 placed the addiu differently. Since the scheduler is reverse, it schedules the last insns first: the final sw v0 (8440) ← addiu (8438) ← lui (843c)... hmm.

The difference: in mine, the addiu was placed before the lui at/sw v1; in the target, after.

What determines this? The addiu's priority (chain) and the hazard blocking.

Since w42's `one` variable moved the li early, the whole shape is now nearly right. The remaining addiu placement might be affected by the `one` variable's birth position. In w42, `s32 one = 1;` is declared at the top of the case block — but the li appears at 8410 (after the load), meaning the compiler placed the li near its use (combine/cse moved it or the assignment was sunk).

Hmm, wait: in w42, `one = 1` is at the top; the li appears at 8410 — right after the load. In the target, the li is at 8410 too. Good.

Now the addiu placement. Let me try variants of the `one` declaration position and the do-while placement:

- w50: w42 without the do-while (plain)
- w51: w42 with `one` declared before `val`
- w52: w42 with the D_801B7988 store moved before *p=0
- w53: w42 with an extra do-while around the tail (`*p = 0; D_801B7988 = one;`)
- w54: w42 with the do-while around all four stores (the three + *p)
- w55: w42 with the do-while moved to after the tail (around nothing)... 
- w56: w42 with `val` used as `D_801B7A84 = val + 1` but `one` assigned right after the load

Let me try these.

Actually, another thought: the addiu placement depends on the REG_DEAD note / the value's life. `val`'s last use is the addiu; the addiu's result feeds the final sw.

What if I change `D_801B7A84 = val + 1;` to `D_801B7A84 = val + 1;` with a different temp — e.g., `s32 nv = val + 1; D_801B7A84 = nv;`? That adds a copy (movsi) which may be coalesced. Might change the schedule.

Let me batch:
- w50: no do-while (plain w42 shape)
- w51: `one` declared before val
- w52: D_801B7988 = one; before *p = 0;
- w53: do-while around *p=0 and D_801B7988
- w54: do-while around all four stores
- w55: `s32 nv = val + 1; ... D_801B7A84 = nv;`
- w56: `one` assigned right after the load: `one = 1;` after `val = D_801B7A84;`
- w57: two do-whiles (three stores; then *p+flag)
- w58: the addiu via a temp: `val = val + 1;` after the three stores, then `D_801B7A84 = val;` — hmm, that changes val's life.

Let me write gen4.py from w42 as the base.
