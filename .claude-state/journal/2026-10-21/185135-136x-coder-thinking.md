---
ts: 2026-10-22T00:51:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_tQlNdRIePht4yb35ygM1
---
func_8017D9D8 = MATCH with:
- `s32 pad[2];` (the frame: 32 bytes, matching the target — the asm's "m"(pad) made pad address-taken)
- `do { } while (0);  // !FAKE: do-while` + `v0 = (s16)v0;` in place of the asm.

Hmm, wait: the do-while AND the cast? Let me check whether the do-while is needed: cb018_casts16_arr2 scored 1 (the cast + pad[2] without the do-while). So the do-while adds the last bit.

Hmm, is the do-while + cast combination "one move" or two? It's fine — both are plain C and allowed (the do-while with the !FAKE marker).

Hmm, but hold on: is the *do-while* here doing the "keep the copy v0/v1 separate" job? Let me think: the empty do-while splits the basic block → cse can't merge the copy across the block boundary? Hmm, cse is a global pass but the *value* merging (make_regs_eqv) happens within the block. Hmm, but the value numbering is global... whatever, it works.

Let me write win.c for func_8017D9D8 (with proper indentation) and record.

Tries: 13 (variants) + 16 (frame) + 6 (castframe) + 12 (x) + 10 (y) + 24 (combos) = 81 ✓.

Let me write win.c.
