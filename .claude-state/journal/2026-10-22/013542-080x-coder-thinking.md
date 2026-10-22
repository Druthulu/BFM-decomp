---
ts: 2026-10-22T07:35:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_fNjLP2OOyrfX6w4MOuA5
---
The work list has W08 with SCAN (launder, 13 lines). The G15 list was drawn from work.tsv.

So the SCAN macro is a "body" in the census with a launder kind. Since the macro has no asm, the census must have attributed something. Hmm, 13 lines = the macro's length (the macro is ~13 lines: from `#define SCAN()` to `} while (i < 0x60);` — yes ~13 lines!).

So the census treats the macro as a body with 13 lines and kind "launder". Where's the launder in it? Hmm... maybe the census counted the `e = D_801202A0;` (an address assignment = a "launder" of the address?) Hmm.

Hmm, maybe the census's "launder" for SCAN refers to the address rematerialization: the macro's `e = D_801202A0;` — the address of a global in a loop.

Regardless: how do I score this item? The scorer (delever_search --try TU SCAN file --body) needs a body to splice. For a macro, there's no function.

Let me try: what does delever_search do with fn=SCAN? The "body_span" logic looks for "Function SCAN" in the dumps. Since SCAN isn't a function, the score would fail.

Hmm, but the harness's scoring (the "bank") for this item... Let me look at how the item is meant to be scored. Maybe the scoring uses the FUNCTION that contains the macro (func_8018D98C) — the macro's expansions are inside it.

Hmm, but the item's fn is "SCAN" and the item dir's fn file says "SCAN".

Let me look at how another shard handled a macro item (e.g. W08 or another shard's list). Let me grep the other shards' lists for macro-like items and see their results.

Let me check .run/P40/T11/*/results.tsv for rows with fn=SCAN or similar macronames.
