---
ts: 2026-10-22T07:35:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_GB2iSAHbHOVokGIGPdQS
---
The SCAN macro is used in the function func_8018D98C. The macro itself contains no asm. The launders in the file are in the CHAIN/LAST macros (lines 3036, 3051, 3102, 3116, 3156, 3158, 3244, 3258).

The item is "SCAN" — hmm. The census presumably attributed the SCAN macro's site (the "13 lines" = the macro's line count?) as a launder site.

Hmm, wait: the SCAN macro has no asm. So how is SCAN a "launder" row?

Hmm, maybe the census treats the macro body as a "body" and the launder kind came from... Hmm.

Wait — maybe the SCAN macro is where the launder SHOULD be. Let me look at the comment again: "Zero-emission launder (see NOTES.md). Each expansion gets a FRESH pseudo that cse/cse2 cannot unify with the other sites' identical (symbol_ref "D_801C8344"), so the address is rematerialised as `la $a1, D_801C8344` at every call instead of being hoisted once into a callee-saved register."

That's about D_801C8344 — the CHAIN/LAST macros.

Hmm, so where's the SCAN-related launder? The SCAN macro walks a table D_801202A0 — and the address `e = D_801202A0` — hmm.

Hmm, let me look at the NOTES.md in that directory (maybe there's a notes file explaining). And let me check the item's `kinds` file content: "launder".

Hmm, since the census lists "SCAN" as a body with a launder kind, maybe the census's body-span logic picked up the macro region including a nearby launder? Hmm.

Let me check the census data: .run/P40/T11/census? There's a `census` dir under .run/P36. The lever census file may list the sites for (tu, fn). Let me grep for "SCAN" in the census sites file.

Let me find the census file.
