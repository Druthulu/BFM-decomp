---
ts: 2026-10-22T00:04:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_vdr8rTYeBztsnVIqHIec
---
OK. So the item func_801832A8 has levers: pin $4, pin $5, launder. The row kind is "launder" only. So MATCH requires: the launder gone (kind launder removed) but pins may stay (levers of other kinds the def already had). Per constraint: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

So for func_801832A8: remove the launder `__asm__("" : "=r"(vol) : "0"(vol));` and find a C-level move that keeps score 0.

The comment says the launder's purpose: "lever 3: sched1 otherwise hoists the PAN multiply ahead of this one". Hmm, but also lever 4 says reuse one variable for X and PAN: "writing sx = (sx + 0xA0)/0x14 instead of a fresh pan". The launder on vol forces the two magic-multiplies to be tied to the same scratch.

Alternative: use a real second set of vol (e.g. `vol2 = vol;` — but that's identity launder? "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack"). Hmm, that's about laundering via C. Actually the constraint says identity-statement launders don't count as a crack. So we can't just do `vol = vol;`.

Hmm. What is a "real 2nd set" per moves.md: "launder->real 2nd set pv &= 0xFF000000" — i.e. splitting the value into a separate computation so cse doesn't merge.

Let me look at the pattern from earlier launder MATCHes in G09 (many launder items MATCHed via "real 2nd set"). E.g. line 97-124: various.

For this item: the launder ties the two multiplies to the same match_scratch (vol). Without the launder, sched1 hoists the PAN multiply (sx = (sx+0xA0)/0x14 → mult by 0x...?) ahead. Wait lever 4: pan uses sx in place: sx = (sx+0xA0)/0x14 uses a multiply by magic. The launder on vol prevents sched1 from swapping the two multiplies (the two magic-multiply chains write to match_scratch, and swapping changes which one is first).

The real 2nd set for vol: instead of relying on the launder, compute vol in a way that has 2 sets, e.g.:

vol = ((0xA0 - av) * 0x7F) / 0xA0;
then later use `vol` — one set only. The "real 2nd set" pattern: split the value: `vol = ((0xA0 - av) * 0x7F) / 0xA0; vol = vol & 0xFFFF;`? That adds an and instruction — changes codegen.

Hmm, but for the earlier examples: "launder->real 2nd set pv &= 0xFF000000 split (real 2nd set); $3 pin dropped" — there the launder was an asm fence that made pv opaque; replacing it with an actual second assignment of pv gave the same effect on cse (the value no longer equivalent), with the second set being real code that existed anyway.

Here the launder is a zero-byte fence. The equivalent C would be to re-assign vol from something else, e.g. `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then `vol = vol;`? no.

Alternative: maybe the answer is that the two multiplies can be ordered by source order if the PAN multiply is expressed in a way that has a dependency... Actually lever 3 says "Source statement order does NOT move it (9 spellings swept, all identical); only the re-tie does."

Hmm. But maybe with lever-4-style reuse (sx reused as pan) the multiply order can be flipped by reordering statements: pan first then vol? The launder is between vol computation and sx computation. If we move the pan computation before vol, the order of the two multiplies swaps in source but the target has PAN first? Let's check: the comment says "sched1 (the PRE-reload pass) is free to swap them and always hoisted the PAN multiply first, inverting the whole tail schedule and losing the mfhi→mult hazard nop". So the target order is: PAN multiply first? Wait: "always hoisted the PAN multiply first, inverting the whole tail schedule" — so without the launder, PAN comes first (wrong); with the launder, vol first (correct). Hmm, actually the launder is placed after vol, so with it, vol's multiply stays before PAN's.

Hmm wait, but the source order is vol first then sx (pan). Without the launder, sched1 hoists PAN's multiply first anyway — because the launder (an asm) blocks reordering? Actually no: the launder is AFTER the vol computation, so it doesn't block vol's multiply from being swapped with PAN's multiply... unless the asm "=r"(vol) : "0"(vol) constrains vol to a register and creates a dependency/barrier for sched1.

Per C0170 §153: a launder is used to defeat cse for a value (the value is opaque). The effect: cse can't propagate vol's value. Here the effect: sched1 (PRE-reload) hoists the PAN multiply first because vol's value... hmm.

Honestly, this is deep. The practical approach: try candidate bodies and check score with dt.sh. Let me first establish the baseline: copy the current def as orig.c and run dt.sh to see the score (should be 0 since the src def matches the target).

Wait — the src def is the *banked* body which matched the target exactly (MATCH 237 ins). So orig.c scores 0. Then I need a lever-free variant that still scores 0.

Approach: try the "real 2nd set" idea: give vol two sets by computing it in two steps where the second set is real code that already exists in the target. E.g. the target's use is `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF)`. Hmm, vol's final use is OR'd.

Alternatively: maybe removing the launder and instead giving `av` a second set works: av = sx; if (sx<0) av = -sx. That's already 2 sets.

Another approach: the launder blocks sched1's reordering of the two magic multiplies. Alternative C-level: express the vol computation so it doesn't use match_scratch at all? e.g. compute via a different form that yields the same instructions: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` — gcc 2.7.2 uses the classic multiply sequence with match_scratch ($at?). Actually for /0xA0 = /160: magic number. The multiply uses `mult` then `mfhi`. The PAN division /0x14=20 also uses mult/mfhi. gcc uses a scratch register (match_scratch) for the multiply in old gcc? Actually in gcc 2.7, for division by constant, the code is `mult`/`mfhi` using $at? Hmm.

Given the complexity, maybe the practical approach for each item: copy the def, delete the launder, run dt.sh, look at the diff tail to see the mismatch, and iterate with C moves.

Let me set up the first item and get the baseline. Also check that dt.sh works (it needs build/ present with the compiled function, and a compiler).

Let me try: copy the def to orig.c in the item dir. I need the exact function text. I'll extract lines 6919-7016 into orig.c. But Edit/Write requires reading... I can use sed to extract (denied earlier? the awk one was denied due to "multiple operations" - the awk with quoted NR>= was flagged). Let me try a simple sed.

Actually the denial message said the command contains multiple operations; the flagged part was the awk command itself (maybe due to the `>` or `&&`?). Let me try `sed -n '6919,7016p' file > out`.

Also, dt.sh takes a "candidate body file" — the function's definition only (bare definition). So orig.c should contain just the function definition (like the def). The externs are in the TU already presumably.

Let's test.
