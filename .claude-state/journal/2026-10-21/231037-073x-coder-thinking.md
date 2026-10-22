---
ts: 2026-10-22T05:10:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_nBcA1Q57O8XJUXdDkM22
---
No improvement. Best = 9 (vV2_direct / vV3_else / h9 / k6). Tries: 5 + 9 + 12 + 6 = 32 ✓ ≥30.

Wall time: 22:59 → 23:35 = 36 min. Hmm, over 30. The rule says past 30 min stop and record a wall — I'm recording a wall ✓ (and the item has a wall from G08 too).

Let me record item 3:
- win.c = the best body (vV2_direct, score 9).
- results.tsv row: dir, file, func, kinds(pin), result WALL, best 9, tries 32, wall tag, evidence.

Wall tag: reuse "greg-alloc-order" (from walls.txt? it's not in walls.txt — walls.txt has: cse-const-addr, sched1-argcopy-hoist, sched1-birth-boost, callee-saved-order, flow-unused-result, sp-stack-switch, no-c-spelling, hand-asm). "greg-alloc-order" is not in walls.txt but it's an existing tag in moves.md (from G08). The brief says "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". Since "greg-alloc-order" was used by G08 for this very function, reusing it keeps consistency. But it's not in walls.txt... The moves.md line for G08 used it. I'll use "greg-alloc-order" (consistent with the earlier shard's line for the same function) — hmm, but the brief says a tag from walls.txt or a NEW one. To be safe and precise, I'll use a new tag that names the mechanism: "greg-hardreg-reserve" — hmm, but then two tags for the same wall.

Hmm. The evidence should carry the mechanism. Let me use "greg-alloc-order" (the existing tag for this function) — it IS a tag used in the project's moves.md. Hmm, "a tag from walls.txt or a new <pass>-<what>". walls.txt says "A new tag: <pass>-<what>, lowercase, defined in the coder's results evidence". Since walls.txt is the registry and "greg-alloc-order" isn't there, I'd better define a new one OR add it to walls.txt — but I can't edit walls.txt? The constraint says "write only under .run/P40/T11/G08b/ plus appends to .run/P40/T11/moves.md" → so no edits to walls.txt.

So I'll use a new tag: "greg-hardreg-reserve" — hmm, but the pass name: "global.c" → "global-hardreg-reserve"? The format `<pass>-<what>`: the pass is "global" (global.c). Let me use "global-hardreg-reserve" for items 2 and 3, and for item 1 I used "global-copy-pref" ✓ (also a `<pass>-<what>` name ✓).

Hmm, for item 3, is the mechanism "hardreg-reserve" or "alloc-order"? My evidence: the pinned hard-reg pseudo reserves $2 for the whole function; lever-free the load temps take $2 in the first two comparisons (the target has $4/$3). That's the hardreg-reserve mechanism ✓.

Let me use "global-hardreg-reserve".

Evidence (≤140 chars): "the pin's hard-reg pseudo reserves $2 for the whole fn; lever-free the load temps take $2/$3 in the first two compares (target $4/$3); best 9 (vV2_direct)" — let me count: roughly 135 ✓.

Then the moves.md line:
"pin | func_801536DC | WALL global-hardreg-reserve — the pin's hard-reg pseudo reserves $2 for the whole function; lever-free the load temps take $2/$3 in the first two comparisons (target $4/$3) and the value lands in $4; best lever-free 9 (vV2_direct) (G08b)"

Now let me also update the item's notes.md, then move to item 4 (func_8017849C).

Time: 23:36. Items 4 and 5 remain. Let me move fast.

Let me do the recording in one call (copy win.c, append rows, clean dumps) and then start item 4.
