---
ts: 2026-10-22T04:37:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4WC3jfKbIwlFvm7b9RmD
---
The priority formula: `floor(log2 refs) * refs / live * 1e4`.

So pri = floor(log2(refs)) * refs / live * 10000.

Check: refs 3 → floor(log2 3)=1 → 1*3/live*10000 = 3*10000/live ✓ (matches my earlier fit).
refs 2 → floor(log2 2)=1 → 2*10000/live ✓.
refs 4 → floor(log2 4)=2 → 2*4/live*10000 = 8*10000/live ✓ (the 11428 = 8*10000/7 ✓ !!). Great, formula confirmed: refs 4, live 7 → 11428 ✓.

So pri = 2^floor(log2(refs)) * refs * 10000 / live.

Now: to beat the call-result pseudo (refs 2, live 2 → 10000), the local `result` needs pri > 10000: with refs 3 → 3*10000/live > 10000 → live < 3. With refs 4 → 8*10000/live > 10000 → live < 8. With refs 5 → 4*5*10000/live = 200000/live > 10000 → live < 20.

refs 4, live < 8: the local `result` in nopin has refs 4 (2 defs of 0, 1 def of the bool, 1 use) and live ~9-10. If we could shorten its live range to 7, pri = 80000/7 = 11428 > 10000 → it wins $2 ✓✓.

That's a concrete, cheap target: shorten the local's live range by ~2 instructions!

The local `result`'s live range: from its FIRST def to its LAST use. In the nopin structure:
```
if (ret != 0) {
    result = 0;            <- first def (ins ~25)
    if ((ret & 0x8000) != 0) {
        result = (...);     <- def
    }
} else {
    result = 0;            <- def
}
return result;            <- use (ins ~33)
```
The live range spans from ins 25 to ins 33 → ~9.

How to shorten it? If the first def were later (closer to the use). E.g.:

```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = (...);    /* def at ~27 */
    } else {
        result = 0;        /* def at ~28 */
    }
} else {
    result = 0;            /* def at ~25 (else path) */
}
return result;
```
Hmm, the else path's def is early in the layout? gcc's layout: the else block might be placed after the then block. The live range starts at the EARLIEST def in the block order.

To shorten: make the value's defs as late as possible and the use as early as possible. The use is the return (last). So the live range ≈ from the first def to the return.

Alternatively reduce the number of instructions between. The `move v0,zero` at ins 34 (else path) is at the end. Hmm.

Alternatively: increase refs! With refs 5, pri = 4*5*10000/live = 200000/live > 10000 → live < 20 ✓ (easier!). How to get refs 5 without changing the code?

Hmm — refs counts the RTL references of the pseudo. If `result` is assigned 0 twice and the boolean once and used once = 4 refs. What if we assign it a third time (e.g. `result = 0;` in a third place)? That changes the code (an extra store) — unless the extra assignment is in a path that already exists...

Hmm! What about this: the else-branch `result = 0;` and the then-branch `result = 0;` — what if we restructure so there are 3 defs but only 2 code paths? E.g.

```
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) {
        result = (*(u8*)((char*)buf2+6) == 0x15);
    }
} else {
    result = 0;
}
```
= 3 defs. To get 4 defs we'd need another path.

Alternatively: what about the `&&`/`||` folds producing an extra assignment?

Hmm, alternatively: the "use" count — `return result;` is 1 use. What if the value is used twice, e.g. `return result + 0;`? That folds.

Hmm. What about a different approach: the local's live range in the RTL is measured from the first def to the last use — but gcc's "live length" in the alloc table might be computed differently (the number of insns the pseudo is live). Let me get the actual dump for the nopin candidate and see the numbers for the relevant pseudos. Then I can compute what's needed.

Also the dump gives the allocation ORDER line and preferences — the ground truth for who got $2.

The dump requires a real TU (t.c). The cc1_dumps_tu.sh takes a work dir containing <fn>/t.c or a .c file. I need the TU: src/shared/ov/func_8014FD54.h is a header; the tool compiles it as a stub TU (ov_MAIN_012). Let me look at the scratch dir the tool made: .run/P36/engine/score/ov_MAIN_012__func_8014FD54/p3/ — it has inc/ and shared/ dirs (the compile error message showed ".../p38/inc/../shared/ov/func_80..."). So the tool builds a scratch TU dir with the header included.

So I can dump using the scratch dir: run the tool with --keep, then use its scratch dir's t.c? Let me look at what's in the p3 dir.

Let me check.
