---
ts: 2026-10-21T23:47:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG06r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_h28uDgu1Tsw9bWmT3r0B
---
All 11. The compiler is robust: c1 always ends up in $2 and the -160 li always at the const block.

This is a strong indication of a wall: the allocation of the -160 constant to $2 vs $3 is not steerable by C-level moves that I've found; the target's placement requires a hard reg (the pin).

Per the brief, PARTIAL is allowed: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". But here keeping the pin IS the lever — the row kind is "pin". A PARTIAL row means the win.c scores 0 while keeping only the listed levers. Here the only lever is the pin itself, so PARTIAL:pin with score 0 = the original def (the pin kept) — that's trivially the current src. Hmm, is that a legitimate PARTIAL? "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)" — yes: a body that scores 0 while keeping the pin lever. That's just the original code (score 0 with the pin). Hmm, that seems degenerate but matches the definition: the pin couldn't be removed.

But wait, that's the same as the current src which is already known. Is that useful? The moves.md examples show PARTIAL rows like "PARTIAL:keepalive greg-pri-refs — barrier: y store per branch; ... lever-free best 19" — i.e. they cracked some kinds and kept others. Here we'd keep ALL kinds (the pin) → no progress. Then the honest result is WALL.

Hmm, but a WALL means "best = lowest score of a lever-free body" = 11, and the wall tag describes the mechanism. Let me record WALL with best=11 and a tag like "local-alloc-const-qty" — a new tag `<pass>-<what>`, e.g. `local-alloc-const-prio`.

Before that, let me try ONE more idea that could plausibly work: the "priority" formula gives shorter live range → higher priority. c1's live range is short because the compiler sinks the `li` next to its uses. What if c1's value is used at TWO points far apart so the range must be long? E.g. use c1 in a store early AND late? That would add an instruction (the target has only 2 uses).

Alternatively: make c1's live range long by using it in a place that's early: e.g. `*(s16 *)(p + 0x14) = c1;` (x0) and `*(s16 *)(p + 0x24) = c1;` (x2) — both in the const block. The const block is at the end. So c1's range is inherently in the const block.

To make c1's range long, c1's set must be early (byte group) AND its uses late. But the compiler sank the li. Hmm, but wait: did it? The variants with c1's set in the byte group (k00..k11) all gave 11 with the li presumably in the const block. Let me verify with tryc for b_k05_s32: where did the li land?

If the compiler sank the li from the byte group to the const block, then the RTL was reordered. Why would sched1 sink it? Because of register pressure: the li's pseudo must live from the byte group to the const block, increasing pressure → the scheduler moves it down. That's exactly "sched1 sinks a definition to its use when the pseudo is live across a long range".

Unless the constant could be re-materialized... it can't.

OK, one more idea: what if the value -160 is used in a way that requires it to be live across a call? No.

What if I split the const block into two halves with a call in between? No, the target has no call there.

I'm fairly convinced item 1 is a WALL: the target's `li -160` in $3 in a nop hole requires the value to be a hard register (the pin). Any lever-free body puts the constant in $2 (shared with the other constants) and the byte-12 in $3, giving 11.

Let me record the WALL with evidence and move on. Actually, let me first check the "best" claim: is 11 really the lowest across everything? All my variants were 11+. Yes, best 11.

Hmm, but hold on. Let me reconsider one thing: the diff showed "mine 91 ins, target 90" — one extra instruction (a nop). What if I could remove that nop and get the rest to match? The score would still be >0 due to the register differences. So no.

One more idea: `PARTIAL` — is there any lever-free body that scores 0? No.

OK, WALL for item 1. Wall tag: new tag `<pass>-<what>`: e.g. "local-alloc-const-qty" — mechanism: local-alloc merges the -160 constant pseudo into the same qty as the other constants (short live range → highest priority), so it gets $2; the target needs it in $3 ($3 is only reachable for a hard reg). Evidence ≤140 chars: "gcc pass: local-alloc/sched1; the -160 const pseudo shares the $2 qty with 0xA0/-0x78/0x78 (shortest live range wins) and its li sinks to the const block; $3 needs a hard reg".

Let me now write the notes.md, save the best candidate as win.c? For a WALL, the brief says "best = lowest score of a lever-free body". I should record the best candidate file. win.c is for MATCH/PARTIAL; for WALL I can still save the best body as a reference (the brief says "each MATCH/PARTIAL has its win.c scoring 0" — for WALL, not required). I'll save the best as win.c anyway? That could confuse ("win.c" = winner). The other shards' WALL items (e.g. func_80187250) — did they have a win.c? The 8017EEB0 dir has win.c. Let me check what its results row says... it has no results row (it's one of my 5 remaining). Hmm, func_8017EEB0 has a win.c already! Let me look at it later.

For a WALL I'll keep the best candidate as best.c and note it in notes.md, and not write win.c (or write win.c as the best lever-free body for reference). I'll write best.c to be safe and mention it in notes.

Time check: ~18:25. Item 1 used ~50 min. I need to speed up on the other 4.

Let me look at item 2 (func_8017FB50) and item 3 (func_8017D3A0), item 4 (func_8017EEB0 — has a win.c already!), item 5 (func_8014CF04).

Let me first check the 8017EEB0 dir since it has a win.c (maybe the previous run got close).
