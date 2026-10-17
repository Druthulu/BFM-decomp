---
ts: 2026-10-17T16:47:09.272Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm down to two remaining launders with no match yet, wondering whether CSE truly preserves pseudo-register equivalence across calls. Maybe the mismatch isn't about the symbol itself but about an argument expression—like a pointer-plus-offset computation—that CSE wouldn't recognize as equal to the symbol reference.

Since func_80016714 returns void, there's no way to reassign m through the call like the earlier cp trick, so this path is a dead end. I'll finalize win.c as win2.c with partial success—2 of 3 launders preserved—and update the results and notes accordingly.
