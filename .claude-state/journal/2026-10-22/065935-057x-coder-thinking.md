---
ts: 2026-10-22T12:59:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_eyzYANpEEGZKtcbjmX4i
---
All 4. As expected: cse folds the constant address.

Now let me test the "compare forces a register" hypothesis — a quick semantic-neutral-ish experiment to confirm the mechanism, and more importantly, to see whether a COMPARE that is *always true* but not provable keeps the base in a register.

Experiment: in item 2, add `if (it == (s32)D_80120194) goto test;` — GCC folds the compare (both constants) → the branch is removed → no effect. Let's see.

Better experiment: use a compare that GCC cannot fold: `if (it == (s32)D_80120194 + (0))`... folded.

Hmm, what about comparing the base against the SECOND symbol: `if (it == (s32)D_801202A0) goto zero;` — that's a false condition (different addresses) → the branch would be taken/never taken — a semantic change ✗ (but as an EXPERIMENT it tells me whether a compare keeps the base in a reg).

Let me run that experiment (not as a candidate, just to learn).

Actually, better experiment: make the compare ALWAYS TRUE at runtime but not provable: `if (it == (s32)D_80120194) ...` is provable. Hmm, what about `if ((it & 0) == 0)`? folded.

Let me do the "false compare" experiment to learn the mechanism:
`if (it == (s32)D_801202A0) goto zero;` placed right after the base assignment (and the following code unchanged). GCC can't fold it (two different constants) → it becomes a compare + branch → the base must be in a register → and the plus would then be base-relative!

If the resulting code has `addiu a0,v1,25996` (base-relative), the mechanism is confirmed, and then I need a semantically-neutral way to get such a compare.

Let me run it.
