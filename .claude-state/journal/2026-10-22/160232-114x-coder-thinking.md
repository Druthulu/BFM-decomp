---
ts: 2026-10-22T22:02:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fxud39FhHerG7cWGwxvH
---
s2's real state: the -0x60 group is STILL in the delay slot (36e0-36f0), and the -0x80 group after the lhu. So the diff vs the target is the same as before; dt.sh's "score 4" hunk list is just abbreviated/misaligned.

OK so the -0x60 group hoisting remains. s2 = 4 because of how the scorer weighs, but the real diff is 5 insns.

Given item 4 needs ~10 more minutes and 34 tries (≥30 ✓), I need 20+ min. Started 15:48:08; I'm at 16:04 → 16 min. Need ~4 more minutes minimum.

Let me try a few more genuinely different ideas in that time:

t6: make the -0x60 group's stores go through a `s16` local declared at the top (init at decl) — the item-3 trick:
```
s16 c60 = -0x60;   // declared with the other decls
...
D_80126976 = c60;
*(s16 *)&D_80126970 = c60;
```
The li would be born at the decl (before the call!). That changes the block.

t7: Make the read `v1 = ...` produce TWO values: `v1 = D_801944F4[idx].f6;` and also `s32 off = ...`.

t8: Use `((Unkstruct*)a0)->unk20C` read into a local before the read, so the lh is born earlier.

t9: Swap the -0x60 group and the -0x80 group AND rely on LAW-1c reversal... tried.

t10: Put the -0x60 group inside an `if (v1 != -1)`? adds a branch.

t11: Make the -0x60 group's store to D_80126970 come first and D_80126976 second with s16 lvalues (m2 = 15).

t12: What about writing the -0x60 pair as an 8-byte... no, they're 4 bytes apart (70 and 76? offsets 0x70 and 0x76 — 6 bytes apart, not contiguous).

Hmm: D_80126970, D_80126974, D_80126976, D_8012697A. The -0x60 pair: 70 and 76. The -0x80 pair: 74 and 7A.

t13: Maybe write the four stores as an array with the right offsets? changes asm.

Let me try t6 and a couple more, then finalize the WALL at ≥20 min.

Actually, one more idea with real promise: the s2 do-while changed the score from 15 to 4. What if the do-while wraps the read and the stores AND the -0x80 pair (q1 = 4)... all 4.

OK let me try t6 (c60/c80 at decl) and t14: move the read before `func_8017E664()`.

Time: I'll do one batch of 4, then finalize.
