---
ts: 2026-11-06T08:03:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZxSeVpWEo57JQSUhhTFn
---
The best path: "R8 temp tmp0 @443 + R12 width tmp0 u32->u16 @413 + R7 block @431" → best 1 at depth 3. The second move changed tmp0 from u32 to u16 at line 413 (the declaration). The third was a block at @431.

The body version at P36 had line numbers: the temp declared at 413. In the current body, the declaration area is around line 411-426. The engine's @413 corresponds to a declaration line. Our current body's `u16 t;` is at line 426. So the engine's body is quite different (P36 body had fewer lines?). The current src may have changed since P36 (the brief warns). So not reproducible directly.

I'm confident item2 is a WALL. Let me record it. Best 5 (v5_split), ~60 tries, 24 min, wall tag `lreg-copy-pref-dying-base`.

Wait, let me reconsider the wall tag semantics. The mechanism: the load `w3c = *(u32*)twicep` — the dest w3c is a global pseudo that keeps the copy preference for s5 (the dying base). The target needs s5 to be live across w3c's range so the conflict pushes w3c to a0. Since twicep has no real use after the load, no lever-free spelling reproduces the conflict. Tag: `lreg-copy-pref-dying-base`. Evidence ≤140 chars: "w3c load keeps the dying base $s5's copy pref; target's $a0 needs twicep live across w3c's range; no real C use exists after the load (best 5)".

Let me finalize item2: win.c = v5_split.c (best), notes.md, results row, moves.md line. Then clean dumps.

Actually, wait: should win.c for a WALL be the best body? The brief says "write a lever-free body ... that scores 0" and result WALL (best = lowest score). I'll put the best body in win.c and note it scores 5. That's consistent with "best = lowest score of a lever-free body".

Let me do it.
