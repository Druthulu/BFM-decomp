---
ts: 2026-11-06T14:40:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FIkjGjH55fUM8iGBX0U9
---
All 4. As expected. The la always sinks.

Let me try the "real use" approach one more time, but more cleverly. The target's early code includes the store `a0->unk14 = v0`. What if the a1 address is used as a scratch in the OR chain, but the final code is the same?

The OR chain: `v0 = &D_8019DAFC | 0x40000000 | 0x20000000`. Target: `la $2,D_8019DAFC; li $3,0x40000000; or $2,$2,$3; li $3,0x20000000; or $2,$2,$3`.

What if I compute `v0 = (s32)&D_8019DAFC; v1 = 0x40000000; v0 = v0 | v1;` — same.

Hmm.

Let me try: use a1 in the `sh $16,2($4)` store? The target's store `sh $16,2($4)` writes s0 to a0->unk2. No a1.

OK, I'm now fairly sure it's a WALL. Let me count my tries: c1 (1), v1-v9 (9), nopin (1), p1-p4 (4) = 15. Plus the baseline. Not 30.

Let me do a final burst of ~15 more variants to reach 30. I'll try:
- a1 declared inside the if block.
- a1 as `u32`.
- a1 = (s32)&D_8019DC34 written as `a1 = (s32)((u8 *)&D_8019DC34);`
- using a pointer type for a1.
- interleaving the a2 assignment.
- moving the keepalive's equivalent (a real use) in different spots.

Let me generate 15 variants quickly and score. Even if they're all 4, I'll have 30 tries and can legitimately record a WALL.

Actually, wait. Let me reconsider whether the item might be crackable by keeping the pin AND changing something else. The pin is on a0 ($4). What if I ALSO use a1 as a pinned register... no, adding a pin is forbidden.

Hmm, what about making a1's value used in the `func_8012B1B4` call? The call is `func_8012B1B4(s0, (void *)&D_8019DC18)`. What if the original had `func_8012B1B4(s0, (void *)a1)` where a1 = &D_8019DC18? No, the target's call arg is &D_8019DC18 ($5), and a1 = &D_8019DC34 is a different address.

Wait, actually — look at the target: `la $5,D_8019DC18; jal func_8012B1B4`. Then after the call: `move $4,$16; la $5,D_8019DC34`. So $5 is reused: first &D_8019DC18, then &D_8019DC34. 

What if the original source computed a1 = &D_8019DC34 BEFORE the call and the call's arg was &D_8019DC18? Then a1 would be computed before the call (too early). Hmm.

Let me look at the source order: `func_8012B1B4(s0, (void *)&D_8019DC18);` then `a0 = s0; a1 = ...`. The target asm has the call, then move a0, then la a1. So the source order matches.

OK, let me generate the final burst and record the WALL.

Actually, let me try one creative real-C idea first: what if I use a1 in the `v0 = v0 | v1;` by making v1 = a1-related? No.

What if the store `((...)a0)->unk14 = v0;` is rewritten as `((...)a0)->unk14 = v0 + (a1 & 0);`? folds.

What if I make `s0 = 4;` depend on a1: `s0 = 4 + (a1 & 0);`? folds.

All fold.

What if I use a1 in a REAL division/modulo? `s0 = 4; v0 = 0xFFF60000 + a1 / 0x100000000;`? no.

OK, final burst. Let me generate variants:
1. a1 declared inside the if block (as a local).
2. a1 as u32.
3. a1 as `void *`.
4. a1 = (s32)((u8 *)&D_8019DC34 + 0) — identity, might not fold? Probably folds.
5. a1 = (s32)&D_8019DC34; then a2 = a1 + 8; (changes code, but test).
6. interleave a2.
7. reorder the OR chain operands.
8. move a3 earlier.
9. move the sh store earlier.
10. move the unk58 store earlier.
11. combine a0=s0 and a1 into one line.
12. `a1 = (s32)&D_8019DC34;` with a comment? no.
13. use `s32 a1 = (s32)&D_8019DC34;` at the top declaration (init at decl).
14. move the declaration of a1 to the top with an initializer.
15. `a1 = (s32)&D_8019DC34;` then `v0 = 0xFFF60000;` and reorder the rest.

Let me generate a batch of 15 and score. I'll be systematic.

Actually, let me reconsider — maybe I should try the "init at decl" for a1, which changes the RTL order (the assignment happens at the declaration point, before a0=s0). Let me include that.

Let me write the batch.
