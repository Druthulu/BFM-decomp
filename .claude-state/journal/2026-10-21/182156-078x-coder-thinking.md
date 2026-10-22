---
ts: 2026-10-22T00:21:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_J2vHdb8KaS81sPOY9Dfd
---
Item 3: func_8017DE84 has TWO launders: at 3291 (on v1) and 3317 (on e). Both are "re-tie" style: `__asm__("" : "=r"(v1) : "0"(v1));`.

The launder on v1 (line 3291) is right after `v1 = mode;` — a re-tie of the value mode. Its purpose: v1 is used in the comparisons (v1 == 1, v1 >= 2, v1 == 0). The re-tie gives v1 a 2nd set → kills the birth boost of `v1 = mode` → so `v1 = mode` stays at its source position (right after the store) rather than sinking to its consumer.

And the launder on e (3317) similarly.

So for this item: the fix is to give v1 (and e) a real 2nd set via a compound assignment? Hmm, v1 = mode; then v1 is compared. A "real 2nd set" for v1: e.g. `v1 = mode; v1 &= 0xFFFFFFFF;`? That's a no-op that gcc folds. Hmm.

The `&=` trick worked when the value was masked. Here v1 = mode (mode is `CAST_SIGN(u16,...) & 3`).

Hmm. What if we write: `v1 = mode;` → `v1 = mode; v1 |= 0;`? gcc folds `x | 0` → x (a copy? no, it folds to the same value, and cse removes it).

Hmm, the compound-assignment trick works because `x &= C` is an in-place operation with a REAL semantic effect. For v1, there's no mask to apply.

Alternatively, maybe the launder's effect for v1 is different: maybe it's a CSE/flow effect rather than a boost.

Let me look at the whole function and the target code to understand. Let me get the target's disassembly for func_8017DE84 and the diff after removing the launders.

Plan: extract the def, score it (0 expected), then remove the launders and score → see the residual; then experiment.

Let me first find the function's end line. The function starts at 3273; let me find the closing brace. Let me read further.
