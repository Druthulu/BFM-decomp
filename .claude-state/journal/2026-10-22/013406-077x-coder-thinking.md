---
ts: 2026-10-22T07:34:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_rBuVqOlE1FhyDeZ0JzUA
---
The SCAN item is a MACRO (`#define SCAN()`), used at lines 3081, 3097, 3173 (three expansions). The item's "func" is SCAN and the TU is the file. The list.tsv says: `SCAN__ov_SC06_033_jr_8018D98C src/ov_SC06_033/ov_SC06_033_jr_8018D98C.c SCAN launder 13`.

Hmm, but SCAN is a macro, not a function! The delever_search --try takes a TU and a function name. The item's "fn" file says "SCAN". Hmm, how does the scorer handle a macro? The body would be the macro definition?

The comment says: "Zero-emission launder (see NOTES.md). Each expansion gets a FRESH pseudo that cse/cse2 cannot unify with the other sites' identical (symbol_ref "D_801C8344"), so the address is rematerialised as `la $a1, D_801C8344` at every call instead of being hoisted once into a callee-saved register. Emits no instruction."

Hmm, that comment mentions D_801C8344 (not D_801202A0). Hmm, the SCAN macro as shown doesn't have an asm. Let me look for the launder in the SCAN macro — maybe the current version doesn't have it? The comment mentions a "Zero-emission launder" — where is it? Let me grep for `__asm__` in the file.

Let me look at the whole file structure: the item's body is "SCAN" — but how does the scorer score a macro? Let me check the item dir's `fn` file: "SCAN". And `tu`: the file.

Hmm, delever_search --try TU FN FILE --body: it splices the body as the definition of FN. For a macro, that doesn't work...

Let me look at how the census classified it. Let me check the item dir contents (fn, kinds, tu) and check if there are other similar items handled elsewhere (e.g. other shards with macro items). Let me look at the .run/P40/T11/G*/ dirs for a similar "SCAN" item... Hmm.

Let me just check: what does the delever_search do with fn=SCAN? Let me try scoring the current macro definition as the body. Actually the body must be a C definition.

Hmm, maybe the intended interpretation: the "function" is the whole TU? Or maybe the scoring replaces the macro definition text?

Let me look at the G15/_batch.py and _extract.py scripts — they were in the G15 dir; maybe they explain how the items were extracted.
