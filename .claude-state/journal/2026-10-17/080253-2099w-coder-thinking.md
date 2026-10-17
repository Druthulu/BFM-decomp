---
ts: 2026-10-17T14:02:53.658Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
Birthing instructions get max priority, so in backward scheduling picking them first places them latest, shortening their life—explaining why the load (as a birth with n_sets==1) and the constant load get placed late. The target likely differs because its registers either have n_sets != 1 (like a pinned hard register) or aren't births at all, so I need to find the legitimate way to replicate that behavior.

That contradicts late-birthing logic — if backward scheduling places highest priority insns last rather than first, the ordering puzzle doesn't resolve cleanly from theory alone, so I should just test it empirically. I'll try giving val a second legitimate assignment, like reusing it in case 1's load-and-check pattern, and see how the scheduler actually orders things.

I'll test these alternative versions—incrementing `val` directly or reusing a function-scoped `val` in case 1—to see if they produce the correct scheduling behavior.
