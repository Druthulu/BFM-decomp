---
ts: 2026-11-06T09:11:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tZBFUKTVWJIIQihLLRWX
---
All orig bodies are fresh against the current src. 

Time 02:11:28. Item 3 wall floor: 20 min → 02:14. Let me use ~2.5 more minutes on one more real probe and then write the log.

Probe: let me look at whether the product could be used as the *first argument* to `func_8017E410` — no, that's mode1.

Probe: check the second loop's `func_8017E410(mode, buf)` — could the product be assigned to a variable used in the loop? e.g. `mode = product`? mode is assigned in the loop (`mode = 0;`) before use. Dead.

Probe: `buf[0] = product`? buf is used later (uv0 = buf[1]...). buf[0] is used in `p->uv1 = buf[0] | ...`. So `buf[0] = product` would change uv1 → wrong.

Probe: what about `ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];` — no.

OK. One more genuinely new idea: **make the product the value of a variable that is used in an `if` that the target ALREADY has, in a way that folds to the same condition**. The target has `if (a[7] == 0) a[7] = 1; else if (a[7] == 1) a[7] = 2;`. What if we write `if (a[7] == 0 && product == product)`? `x == x` folds. No.

What about `if (a[7] == 0 && (product || 1))`? `x || 1` folds.

What about `if (a[7] == 0 && (product, 1))`? comma with a side-effect-free left → dropped.

What about `if (a[7] == 0 && (product ? 1 : 1))`? folds.

What about using the product as an *array index* into an array that the compiler turns into a scaled load? changes.

Done. Let me write the log now and finalize at ~02:14. Writing the log takes a minute or two anyway.

Let me write phase-ends/current/logs/T11.cG24x.md. Need to check the dir exists.
