---
ts: 2026-10-22T00:56:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_i6wkjWGgdNccGnwr1ERl
---
I see it: at 1b64, mine has `lh v1,32(s0)` — the load of unk20 in the *case1* branch — while the target has `lw v1,32(s0)`.

So in mine, the compiler narrowed the load of the pointer e to a halfword! Why? Because... hmm! The `e` variable in the case1 branch: `e = unk20; do{}while(0); *(s32*)(e+4) = t;` — the pointer must be a full word.

Hmm, unless the *narrowing* came from the earlier part: the case0 branch has `e = unk20;` and the shared block uses `*(s32*)(e+4)`.

Hmm, why would GCC narrow a load of a pointer to `lh`? That would be a bug... unless the value is *known* to fit in 16 bits! Hmm: `unk20` — hmm.

OH WAIT. I bet this is the "cast" effect: the *cast* at site 1 was applied to... hmm, the cast is `v1 = (s16)v1`.

Hmm, but hold on: maybe the site order in the generated file is wrong! Let me check the file: pg018_c-d. Let me grep the file for the replacements.

Let me look.
