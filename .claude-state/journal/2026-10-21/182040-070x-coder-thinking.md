---
ts: 2026-10-22T00:20:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_be58fshPGeMnzmEgLv5L
---
That header is a different (already lever-free) body — the exemplar was already cracked and banked (the launder is gone). Not directly a template, but it shows the final form.

Let me instead look at the moves.md line 46: "launder,pin | func_80184174 | MATCH — launder->pv=*p; pv&=0xFF000000 split (real 2nd set); $3 pin dropped; $4 ang pin kept (not row kind), pin-free 4". So the original body had:
```
pv = *p;
__asm__("" : "=r"(pv) : "0"(pv));   /* launder */
*(u32*)p = (pv & 0xFF000000) | ...;
```
and the crack was:
```
pv = *p;
pv = pv & 0xFF000000;
*(u32*)p = pv | ...;
```
Hmm, but that header's body doesn't have that pattern at all (it's a different function entirely — the header is a *shared* body for many members, and the pin/lever notes refer to a different variant).

Hmm, the header body shown is short and has no pv. So the exemplar's final banked body is quite different (maybe the "pv" part was in another member's site).

OK. Let me look at a more direct exemplar: the moves.md line 121: "launder | func_800CD674 | MATCH: pm3 reused as the block-2 OT address temp, stepwise (pm3 = D_800BAE22; pm3 <<= 14; pm3 += base; ot = (u32 *)pm3): multi-set pm3 loses the sched1 birth boost, life a3 (G09)". That's a "multi-set loses the birth boost" — the OPPOSITE direction (creating a multi-set variable to kill a boost).

And line 46/49/50: "launder->pv=*p; pv&=0xFF000000 split (real 2nd set); pv $3 pin dropped" — the "real 2nd set" gives the VALUE a 2nd set (so the value's def is multi-set → no boost on it) — and the effect they wanted was to kill the boost on the *value's def* (the load of pv).

Hmm! So in those cases, splitting the mask DID kill the load's boost. So the "real 2nd set" DOES work in some cases.

For our item 5, the split `pv = pv & 0xFF000000;` gave no change (11 = 11). Hmm, but maybe the split needs to be done differently: e.g. `pv = *(u32 *)p; pv &= 0xFF000000;` (using &= on the variable) — semantically the same as `pv = pv & 0xFF000000`.

In the exemplar, the split is written as two statements: `pv = *p;` then `pv &= 0xFF000000;`. The second statement's dest is pv's pseudo. In our case, pv is PINNED to $3 — maybe the pin matters: the pinned variable's pseudo is a hard-reg-bound pseudo, and gcc's cse/flow handles it differently.

Hmm, in the exemplar, "pv $3 pin dropped" — the pin was also removed in that crack. Interesting.

Let me try the variant where I ALSO drop the pin on pv? NO — the row kind is "launder" only; the pins may stay (they're other kinds). But dropping a pin is allowed?? "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". Hmm — "may stay" implies they may also be removed? Removing the pin would change the register allocation drastically (pv would get a normal register) → the score would explode. The pin is load-bearing here. Let me not.

Let me try the &= spelling for item 5 and see. Cheap.

Also try: `pv = *(u32 *)p; pv = pv & 0xFF000000;` (what I did) vs `pv = *(u32 *)p; pv &= 0xFF000000;` — should be identical after cse.

Hmm, so what else could differ? In the exemplar, the load was `pv = *p;` (a plain load into a pinned var) and the split created a 2nd set. The mechanism "2nd set kills the boost" requires the 2nd set to be of the SAME pseudo as the load's dest. In our case, the load's dest = the temp holding the loaded value (call it T). The split's AND's dest = another temp T2 (not T) → the load's dest T still has 1 set.

In the exemplar, the same logic applies (the load's dest is a temp) → so how did it work there?

Unless in the exemplar the load wrote directly into pv's pseudo. Hmm.

OK, enough. Let me try the empirical variants for item 5, and in parallel start thinking about the others. Let me try:
(1) `pv &= 0xFF000000;` spelling.
(2) Split + also split the second store.
(3) Move the first store after the `ot = ...` line (statement order).
(4) A version where the masked value is assigned to a NEW variable and the store uses it (fresh single-set → boost on the AND).

Let me generate these 4 in one sed -z command with h/g, then score each (4 score commands).

Let me write the sed command carefully.

Base file: base5.c (launder removed). I'll apply the transforms to base5.c.

T1: s|    \*\(u32 \*\)p = (pv & 0xFF000000) \|\n|    pv \&= 0xFF000000;\n    *(u32 *)p = pv \|\n|
   Hmm, `&=` in the replacement: `\&` is the escape for &, so "\&=" gives "&=" ✓.

T2: also split the second store:
   s|    \*(u32 \*)(ot + 0x40) = (\*(u32 \*)(ot + 0x40) & 0xFF000000) \| ((u32)p & 0xFFFFFF);|    m2 = *(u32 *)(ot + 0x40);\n    m2 \&= 0xFF000000;\n    *(u32 *)(ot + 0x40) = m2 \| ((u32)p \& 0xFFFFFF);|
   plus a decl for m2: s|    register u32 pv __asm__("\$3");|    register u32 pv __asm__("$3");\n    u32 m2;|

T3: reorder: move the `ot = ...` line before the `pv = *(u32 *)p;` line:
   s|    ot = \*(s32 \*)((u8 \*)\&D_800A651C + (\*bidx \* 20));\n||  (remove)
   s|    pv = \*(u32 \*)p;|    ot = *(s32 *)((u8 *)\&D_800A651C + (*bidx * 20));\n    pv = *(u32 *)p;|
   Hmm, the `&` in the replacement must be escaped: `\&`.

T4: fresh local for the first masked value:
   s|    \*(u32 \*)p = (pv & 0xFF000000) \|\n|    pm = pv & 0xFF000000;\n    *(u32 *)p = pm \|\n|
   plus decl: s|    register u32 pv __asm__("\$3");|    register u32 pv __asm__("$3");\n    u32 pm;|

Let me build one command with h/g between variants. Note that the 'w' command writes the current pattern space (the whole file in -z mode) ✓.

Command:
sed -z \
 -e 'h' \
 -e 's|    \*(u32 \*)p = (pv & 0xFF000000) \|\n|    pv \&= 0xFF000000;\n    *(u32 *)p = pv \|\n|' \
 -e 'w .../v1.c' \
 -e 'g' \
 -e 's|    \*(u32 \*)p = (pv & 0xFF000000) \|\n|    pv \&= 0xFF000000;\n    *(u32 *)p = pv \|\n|' \
 -e 's|    register u32 pv __asm__("\$3");|    register u32 pv __asm__("$3");\n    u32 m2;|' \
 -e 's|    \*(u32 \*)(ot + 0x40) = (\*(u32 \*)(ot + 0x40) & 0xFF000000) \| ((u32)p & 0xFFFFFF);|    m2 = *(u32 *)(ot + 0x40);\n    m2 \&= 0xFF000000;\n    *(u32 *)(ot + 0x40) = m2 \| ((u32)p \& 0xFFFFFF);|' \
 -e 'w .../v2.c' \
 -e 'g' \
 -e 's|    ot = \*(s32 \*)((u8 \*)\&D_800A651C + (\*bidx \* 20));\n||' \
 -e 's|    pv = \*(u32 \*)p;|    ot = *(s32 *)((u8 *)\&D_800A651C + (*bidx * 20));\n    pv = *(u32 *)p;|' \
 -e 'w .../v3.c' \
 -e 'g' \
 -e 's|    register u32 pv __asm__("\$3");|    register u32 pv __asm__("$3");\n    u32 pm;|' \
 -e 's|    \*(u32 \*)p = (pv & 0xFF000000) \|\n|    pm = pv \& 0xFF000000;\n    *(u32 *)p = pm \|\n|' \
 -e 'w .../v4.c' \
 base5.c > /dev/null

Careful: in the pattern, `&` is literal; but the delimiter is `|` so `\|` is needed for literal `|`. In the *replacement*, `&` means "the whole match" → must escape as `\&`.

Also: in the pattern `s|    \*(u32 \*)p = (pv & 0xFF000000) \|\n|`, BRE: `*` → `\*`, `(` `)` literal ✓, `&` literal ✓, `|` → `\|` ✓.

The `\$3` in the pattern: `$` is literal mid-pattern ✓ (no escape needed, but escaping is harmless? In BRE, `\$` = literal $ ✓).

Let me write it out. Long command but one call. Then 4 score calls.

Hmm, this is a big command; risk of a typo. Let me do 2 variants at a time.

Actually, let me reconsider priorities: I have 8 items and limited time. Items 5 and 8 share the same pattern; if I crack the mechanism once, both may crack. Items 1 and 2 share a pattern too. So it's worth investing here.

Let me run the 4 variants.
