---
ts: 2026-10-22T11:28:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Alb9csJToaTJTNh1TqmQ
---
Item 4's orig.c contains OTHER levers too: `register void *r4 __asm__("$4")` (a PIN) and `register s32 av __asm__("$5")` (a PIN). But the row kind is only "launder" — the constraint says "levers of other kinds the def already had (pins under other causes) may stay, never added". So the pins may stay! Only the launder must go.

Good, that simplifies: for item 4, I only need to remove the `__asm__("" : "=r"(vol) : "0"(vol));` launder.

The notes say: "VOL as a COMPOUND division: vol = (0xA0 - av) * 0x7F; vol /= 0xA0; -> 14, and the instruction count becomes EXACT (237 = 237). The compound assignment writes the division result IN PLACE into vol's pseudo (a real 2nd SET), which puts the VOL chain first, as in the target."

So the best lever-free body so far is 14 with exact count. The residual: "the shared 0x66666667 magic constant is materialised (lui/ori) right before its mult instead of at the top of the tail, plus a v0/v1 transposition."

Hmm, wait — "the shared 0x66666667 magic constant" — but the divisions here are by 0x14 and 0xA0, not by 3 or 5. Hmm, 0x66666667 is the magic for division by 10? Actually 0x66666667 with `mulhi` is for division by 10 (0xA). Yes! `/0xA` → magic 0x66666667.

So `vol = (0xA0 - av) * 0x7F / 0xA0` and `sx = (sx + 0xA0) / 0x14`.

Hmm, 0x14 = 20 → magic 0xCCCCCCCD. And 0xA0 = 160 → magic 0x0A0A0A0A? Hmm.

Anyway. The launder `__asm__("" : "=r"(vol) : "0"(vol));` sits between `vol = ((0xA0 - av) * 0x7F) / 0xA0;` and `sx = (sx + 0xA0) / 0x14;`. The launder keeps the VOL chain first (sched1 would otherwise hoist the PAN chain ahead).

The compound-division trick (vol /= 0xA0) gives 14 with exact count.

Now, the residual is about the constant's birth position. Let me look at the target's tail disassembly.

Let me get the target for func_801832A8 and compare with the best candidate (w8.c or whichever scored 14).

Let me first find which candidate file scored 14. The notes mention the compound division. Let me look at the w*.c files.

Let me diff orig.c against the candidates to find the compound-division one.
