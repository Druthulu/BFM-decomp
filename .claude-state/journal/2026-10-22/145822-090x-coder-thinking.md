---
ts: 2026-10-22T20:58:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mQlmSnEpl7JzcQYfqVFF
---
This is the sched1 dump. I need the block containing the corner-1 adds (insns ~72-80 in the final numbering, but the RTL insn uids differ). This is getting deep. 

Given the time (item 3 started 14:50, now ~15:08 = 18 min), and the prior coder's extensive work, let me consider: the residual is a pure ORDER (scheduling) diff of 4 with identical insn count. The wall tag would be sched1-related. The prior coder's log/moves would have this. Since I can't read the prior log, let me check if there's a wall tag like `sched1-*`.

Options: keep trying source order variants for another ~10 min, or wall at 4.

Let me try a few more targeted at the ay/chain order:
- Move the `op` computation to a *statement before* `ay = ay + 0x75` (already via the initializer).
- Compute `op` via a temp pointer declared earlier, assigned right after bx: 
```
Gline_801372B0 *op;
...
bx = bx - 0x57;
op = (Gline_801372B0*)&D_800A6518[(u32)aD800B9A02 * 0x14];
ay = ay + 0x75;
```
This makes the chain a statement between bx and ay — the source order matches the target. sched1 may still move it.

- Make the chain *longer*/more dependent so sched1 can't defer it? no.

- Make ay's add depend on the chain? e.g. `ay = ay + 0x75 + ((u32)op & 0)`? folded.

Let me try the explicit op statement variant (x1) and a variant where op is assigned before bx (x2), and one where the chain is computed as `op = &D_800A6518[aD800B9A02 * 0x14]` with the multiply written differently.

Also for the by/ax swap: try making ax's add use a *different* temp (e.g. `ax = ay + 0x7B;` vs `ax = 0x7B + ay;`) — commutative, same RTL.

Try `by = bx - 0x5D;` written as `by = bx + -0x5D;` — same.

Let me try x1, x2 and a variant where the ay add is written with a cast to s16: `ay = (u16)(ay + 0x75);` (gen_o3 has u16 ay, so the add is on u16? `ay = ay + 0x75` with u16 promotes to int then truncates → gcc may use addiu + andi? but no andi appears).

Let me run x1, x2, x3.
