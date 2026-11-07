---
ts: 2026-11-06T09:25:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MShY7o3BsM9yUjbRjm33
---
x9: keep K1 only, fc plain (no pin) → 6 REG-caller (same as before). x5 all-removed with fc load moved → 12, slightly better than 14 but still far.

Tries now: ~36. Time ~02:47, started 02:13 → 34 min. Past budget. Item 2 = WALL with best 12 (x5) lever-free. Wait, is x5 lever-free? Yes: all keepalives removed; pins kept (other kind). x5 = 12 COUNT. Best lever-free = 12.

Actually let me double-check x5 is lever-free: allrm removes all three keepalives; fc load moved. Yes.

Let me confirm x5's score with a rerun (single observation is diagnostic; but for a WALL, best is just the lowest observed). Let me rerun x5 to confirm 12. And then record WALL.

Wall tag: need a tag from walls.txt or a new `<pass>-<what>`. Mechanism: local-alloc assigns the AND temp to the dying t0 (K1) and fc gets v1 instead of a1 (K3). A new tag: `lreg-hardreg-dead-reuse` — local-alloc reuses a hard reg that dies at the AND/uses the dying reg, so the target's separate dest cannot form. Evidence: gcc local-alloc; both are register-allocation liveness effects.

Hmm, but maybe I should use existing tags: `lreg-qty-priority` (local-alloc qty priority gives the hard reg to the other pseudo) fits K3. And `lreg-hardreg-live-end`? That's "a hard reg stays live to the block end, so the target pairing cannot form" — not quite.

For K1: t0 dies at the AND, so the AND dest reuses t0. Tag: `lreg-dead-hardreg-reuse` (new). Let me define: "local-alloc reuses the hard reg that dies at the same insn for the result pseudo; target keeps the result in a fresh reg".

Evidence ≤140 chars: "lreg: bVar1($8) REG_DEAD at the andi -> local-alloc puts the andi result in t0; target needs a fresh v0 (keepalive was the only live-extender); fc likewise v1 vs a1".

Best = 12.

Wait — but before walling, let me reconsider one more real-C idea for K1 that I haven't tried: make the AND's *result* used in the branch and ALSO in a later real expression via common subexpression: e.g., the &0x10 test could be folded into the following fc comparison? No.

What about making the &0x10 test part of a `while` loop? No.

One more idea: the AND result could be kept in v0 if t0 is live *at* the AND for a different reason: e.g., if bVar1 were used in the *same insn* but... it is.

Actually, hmm, what if the source tests `bVar1 & 0x10` where bVar1 is *s32* (word) instead of u8? The load would be lbu/lw? If bVar1 were declared `u32 bVar1` and loaded from a u8 pointer, the value would be zero-extended; the AND would be word. The target uses `andi` (word AND on t0). Same.

What if we make bVar1's last use the &0x80 test and the &0x10 test use a *separate load* into another reg? That adds an lbu.

OK. Also consider: maybe the real C used `bVar1` in the +8 negation: `*(s16 *)(param_1 + 8) = -*(s16 *)(param_1 + 8);` — could the original have written `= -sVar5` where sVar5 is reloaded? Target at 54-57: `lhu v0,8(a2); negu v0,v0; sh v0,8(a2)` — reloads from memory. So the source is `-*(s16*)(param_1+8)`. Fine.

I'll wall item 2 with best 12 (x5). Actually wait: the WALL row wants "best = lowest score of a lever-free body". x5=12. But is x5 "lever-free"? It removes the keepalives but keeps pins — allowed. Yes.

Let me rerun x5 to confirm, then write results/notes/moves.

Also I should double check: does x5 score 0 on all includers? No, it's a WALL, not a MATCH. Fine.

Let me confirm x5.
