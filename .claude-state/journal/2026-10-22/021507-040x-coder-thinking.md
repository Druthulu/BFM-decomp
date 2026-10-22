---
ts: 2026-10-22T08:15:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_6TXC2lc6LnNw5wmdZnGu
---
KEY FINDING — line 147:

"pin | func_8017E204 | MATCH — the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0 (G06)"

So the s16 trick DID work for func_8017E204! "the copy through an s16 temp escapes cse2's equivalence class". Hmm, so a copy THROUGH an s16 temp escapes cse.

"copy through an s16 temp" — maybe:
```c
s16 tmp;
tmp = t;      /* t s32 -> tmp s16 */
u = tmp;      /* tmp s16 -> u s32 */
```
Two steps! The first is a truncation (escapes cse), the second is a sign extension (which combine folds to a move if the range is known...).

Hmm, or maybe:
```c
s16 tmp;
tmp = t;   /* the copy escapes cse */
u = tmp;   /* u gets the sign-extended value */
```
For our case, t = sign-extended s16 → tmp = (s16)t = t exactly. Then u = tmp → sign_extend:SI(tmp) → sll/sra ✗.

Hmm. But the G06 note says the copy escapes cse2's equivalence class "so v1 keeps its own register instead of being merged with v0". So the result was `move v1,v0`? Let's think: if `tmp` is s16 and holds t's value, then `u = tmp` → the sign extension... Hmm, if the value's sign bit is known 0, the extension folds to a move.

Hmm! In G06's func_8017E204, the copied value probably had a known range.

Also line 110: "pin | func_8018188C | MATCH — $0 zr copies: s16 u and s16 a0 (HImode copy a0 = u keeps the move); negative-const lines get own s32 temps w,w2 (HImode const would be li 0xf900 = ori)"

"s16 u and s16 a0 (HImode copy a0 = u keeps the move)" — a copy between two s16 vars keeps the move! Because it's an HImode copy (same mode) — hmm, but a same-mode copy would be cse-propagated... unless the HImode copy escapes cse's equivalence class because cse2 tracks HImode copies differently (cse2 is the "cse with register equivalence" pass; for HImode it might not create the equivalence).

AH — that's the key: **cse2 (the second CSE pass, `pass_cse2`) is the one that creates reg equivalences.** And for HImode (16-bit) copies, cse2 might not treat them as full-register equivalences.

Hmm, "the copy through an s16 temp escapes cse2's equivalence class" — so a copy THROUGH an s16 temp (s32 → s16 → s32) escapes.

So for our case:
```c
s32 t, u;
s16 tmp;
...
} else {
    tmp = t;      /* s32 -> s16: truncation, escapes cse */
    u = tmp;      /* s16 -> s32: sign extension */
    t = u - 1;
}
```
Hmm, the second step is a sign extension → sll/sra ✗ — unless the value's range is known.

Hmm. But hold on: what if the SIGN extension is free because the s16 pseudo's reg already holds the sign-extended value? Hmm.

Hmm, wait. Let me reconsider: in G06's case, maybe the structure was:
```c
s16 u;    /* the copy target is s16 */
...
u = t;   /* s32 -> s16 truncation */
```
and then the use of u in a context where the s16→s32 conversion is needed... they said "keeps the move".

Hmm, let me look at the G06 item's win.c to see the exact spelling! G06 dir: .run/P40/T11/G06/func_8017E204*. Let me look.

That's the fastest way to learn the trick.
