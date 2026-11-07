---
ts: 2026-11-06T05:43:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_euisglHjIyqgRu7Vjjth
---
Item 1 is a MATCH: bare win.c scores 0 on all 141 includers.

Wait — I should double check that the bare body compiles in every includer without the externs (score 0 means it compiled). Yes.

Let me record item 1's results row:
- dir: func_80150170__func_80150170
- file: src/shared/ov/func_80150170.h
- func: func_80150170
- kinds: barrier
- result: MATCH
- best: 0
- tries: how many? I scored 25 + 9 + 3 fixes + 141 includer checks. Tries = scored candidate bodies: 25 (wave1, including 1 compile error → 24 scored) + 9 (wave2) + 3 (fix iterations) = ~36. Let me count "tries" as distinct candidate bodies scored: v_* 25 (one COMPILE-ERROR), w_* 9, v_fix1, v_fix2, win.c = 3. Total 37 scored (36 with a score). Let me say 37.
- wall: `-`
- evidence: "s16 a[4]/b[4] arrays (byte-identical to the u8[8] stack layout): the comparison reads a[1]/b[1] and the arm stores reuse those s16 elements, so no post-compare reload is needed; tail loads stay u16 (lhu). 0 on 141/141 includers."

Wait — that's the mechanism: changing the array type to s16 made the comparison and stores use the same pseudo in a way that... hmm, actually what exactly cracked it? Let me understand: the original u8 arrays with `*(s16*)(a+2)` casts; the new s16 arrays with `a[1]`. The difference: with s16 element accesses, GCC's cse/combine treats the comparison load and the store value as the same *element* and... it produced the reload pattern. Interesting: the score went from 22 to 0.

Actually the key was that the *tail* loads needed to stay lhu, and the then-arm stores with `a[0]`/`a[1]`/`a[2]` (s16) produced the target's reloads. Hmm, why? Let me look at the final win asm to describe the mechanism accurately. Let me diff win vs target — it's 0, so identical. Let me look at the win asm to see the reloads present.

Let me disassemble win.c's object to confirm the reload pattern.
