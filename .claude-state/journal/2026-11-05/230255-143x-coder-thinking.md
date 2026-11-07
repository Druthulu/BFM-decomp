---
ts: 2026-11-06T06:02:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rWaDMy90UOQ0gnPiqyyr
---
The lreg dump shows global allocnos (72, 73, 76, 77, 78) and block-1 qtys (74, 75). Reg 74 (3 refs/14 insns in block 1) and 75 (5 refs/5 insns in block 1).

Hmm, the local qtys in block 1: 74 (3/14) and 75 (5/5). Density: 74 = floor_log2(3)*3*4/14 = 1*3*4/14 = 0.857; 75 = 2*5*4/5 = 8. So 75 (u) gets $2, 74 (q) gets $3. That's mine.

In the target (with the launder), the qty structure differs. Hmm, but the launder is in the same block... Let me check the orig's lreg for comparison. But I don't need to.

The evidence: q/u swap is a local-alloc density consequence of the launder's absence (the launder's qty changes the block's qty landscape). Plus the extra andi.

OK. Let me finalize item 4 as a WALL with best 10.

Time: ~23:03. Started ~22:51 → 12 min. Need 20 → 23:11. 8 more minutes.

Hmm, let me do a few more experiments. Actually, let me try to attack the andi: what if the mask is applied to the value *before* the sign-extend chain, so it replaces an existing instruction?

`cc = (s16)func(...)`: sll v0,v0,0x10; sra s1,v0,0x10.
What if `cc = (s16)(func(...) & 0xFFFF)`: the AND then the sign-extend — gcc would emit andi + sll + sra? Or the AND is redundant with the sll? Hmm: (s16)(x & 0xFFFF) = (s16)x. So gcc folds. Hmm.

What if `cc = (u16)func(...)` and the comparisons use the u16 value? The asm would be sll+srl (vs target sll+sra). Different opcode → mismatch.

OK.

Let me try yet another idea for the second test: what if we make the *first* test compare a value that gcc can't connect to cc, without extra instructions? For example, if the first test uses `cc` but the second uses a *different variable that gcc can't prove equal*, where the different variable is assigned cc via a **store/load pair that gcc keeps in a register**... no.

What if `cc` is a `union` member? `union { s32 i; s16 h; } u;` — u.i = call; the first test on u.h? The RTL would use subregs of the same register → gcc knows.

Hmm.

Let me try the union idea quickly? Unlikely.

OK, let me instead use the remaining minutes to write the notes for item 4 and then move to item 5 — but the rule says ≥20 min. Hmm.

Let me do 4-5 more scored variants over the next few minutes, then write up. Each batch takes ~30s.

Batch:
z1: union approach.
z2: `cc` as a struct field of a local struct.
z3: the second test `if (cc == one) goto rejoin;` with the first test `if (cc != one) goto second;` and a `do{}while(0)` around the first test.
z4: `one` declared `const s32 one = 1;`.

Let me run.
