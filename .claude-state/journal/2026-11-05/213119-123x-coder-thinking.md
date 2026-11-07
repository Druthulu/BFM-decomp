---
ts: 2026-11-06T04:31:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Loj9IwRLC4Ugf2kTD6i
---
CAST_NONSTRUCT is just a cast — the name hints it produces a non-struct MEM. `(*(T*)((p)+(k)))` — a cast through a pointer, likely non-struct. The current p load uses `((Unkstruct_800B5CB8 *)a0)->unk20`, a struct member → struct MEM. In the target, the model load is `mem/s:SI`? The combine dump showed `mem/s:SI` for insn 232 (the p load) — struct. So the target's p load is struct too.

Let me try y8 = `p = CAST_NONSTRUCT(s32 *, (s32)a0, 0x20);` (non-struct load). If the first model load (raw store) is struct and the p load non-struct, cse's invalidation might differ, and the scheduling might change.

Let me also try y9 = the 0x1A store via a `s32 *q` local in the arm, with the p load through a different expression.

And y10: make the `<0x11` arm's 0x1A store use `p` (loaded first) and then reload p — i.e., the store through p (one load), then p reload. Wait, that gives the store's model load into p, then p reload; both p. That's the u1 approach (score 32). Hmm.

Let me try y8 and a couple others to reach 30 tries. Current tries: 19 + 7 = 26. Need 4 more.

y8: CAST_NONSTRUCT p load.
y9: `p = *(s32 **)((s32)a0 + 0x20);` (same as struct? no, this is a plain cast → non-struct).
y10: swap the two statements `v = v + 0x600;` and `p = ...` back (w4 order) — already w4.
y10: make the addiu use a temp: `{ s32 w = v + 0x600; v = w; }`.
y11: do-while around the p load + add (w7 did; 14).

Let me run y8, y9, y10, y11.
