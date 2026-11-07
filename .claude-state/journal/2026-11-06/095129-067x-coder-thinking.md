---
ts: 2026-11-06T16:51:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pHgXlpm67m4PzQi5uHcT
---
No REG_ALLOC_ORDER, so the order is 0..31: $0,$1,$2,$3,... but $0/$1 are fixed. So the first free is $2. Confirmed.

So the highest-priority qty gets $2. In the target, {77,83} (t) got $2, meaning it had the highest priority among the groups in the original build. With the same RTL, that can't happen unless the RTL differs.

Maybe the original RTL had a DIFFERENT tie structure. E.g., maybe the h group is {76,81} and {82} separate, or the t group has more regs.

Alternatively, maybe the original had `h` loaded into a HImode pseudo (84-like) and the sign-extend separate. Let me look at the RTL for a variant where h is `s16`:

In w6_s16 (score 6), the RTL might differ. Let me dump it and compare. Actually, the score is the same 6 (same swap), so probably the same RTL.

Let me look at the sched1 dump for the base to see the pre-sched order and understand. Actually, let me look at the .rtl dump (before sched1) for the insn order.

Hmm, time is limited. Let me count the tries so far for item 3: base win0 (1), w6: 7 candidates = 8. I need up to 30 for a wall, but I should try harder first.

Let me think about what makes the t group get $2. What if the t group's priority can be raised by making t's *nrefs* higher: the group nrefs is the sum of tied regs' refs. If t were tied to a third reg, nrefs 12 = h's, then the qty number tie-break decides (lower qty wins). The t qty (77) is born before h (76) in the a,t,h order? In the current a,h,t order, h is born first (qty lower). If I get the a,t,h order, t's qty is lower → on a tie, t wins → $2! That's promising.

So: (1) make the t group have 3 tied regs (nrefs 12), and (2) ensure t's qty number < h's (a,t,h order).

How to add a third tied reg to the t group? The chain: 77 (t = s0<<1) → 83 (83 = 77 + 82). If the sum 83 is used in another tied arithmetic op, e.g., the address computation `*(u16*)(83)` is a memory op (no tie). 

What if I split the sum: `idx = t + h4; ... *(u16*)idx`? Then 83 = 77 + 82 ties to 77, and the load uses 83. No third tie.

What if the address is `*(u16*)(t + (h << 4) + s2)` reassociated as `((t + (h<<4)) + s2)`: 83 = 77 + 81' (tie), 84' = 83 + 75 (tie 84'→83). Then the t group = {77, 83, 84'} (3 regs, nrefs 12). And the h group = {76, 81} (2 regs, nrefs 8). Then:
- t group: nrefs 12, life? birth of 77 to death of 84'.
- h group: nrefs 8, life birth of 76 to death of 81.
This might flip! And the instruction order would change: target has sll h,4; addu h,s2; addu t,h. If I write `(t + (h << 4)) + s2`, the order is sll h,4; addu t,h; addu s2. Different order. sched1 might reorder to the target? The target's order is h<<4, +s2, t+h — which corresponds to `t + ((h << 4) + s2)`. So the C is already the target order.

Hmm. But maybe sched1 reorders anyway. Let me test the reassociated forms:
1. `(t + (h << 4)) + (s32)s2` — hmm, the types: t is s32, h<<4 is int, s2 is s32.
2. `(t + (s32)s2) + (h << 4)`.
3. `t + (h << 4) + (s32)s2` (left-assoc = (t + (h<<4)) + s2).

Let me also try making `s2` a local copy so the tie at +s2 is different.

Let me batch these.

Also: what if I use `s0 << 1` inline in the expression instead of t? Then t wouldn't be a separate variable and the tree would be different.

Let me test 3 reassociations + a couple of temp variants.

Actually, also note: the target's `addu v0,v0,v1` (83 = 77+82) has v0 = t and v1 = 82. The tie is 83→77 (t). So the t group is {77,83}. In the target, the h group is {76,81,82}. So the tie structure IS the same as mine. Therefore the original's priorities differed with the same tie structure. The only remaining lever: the RTL order (births) — which changes the qty birth/death and the qty numbers.

With the a,t,h order and the same ties:
- t group {77,83}: birth 6 (t born at insn 3), death 18 (83 at insn 9) → life 12, nrefs 8 → pri 2.
- h group {76,81,82}: birth 8 (h at insn 4), death 16 (82 at insn 8) → life 8, nrefs 12 → pri 4.5.
h still wins.

Hmm. What if the order is t, h, a? 
- t group: birth 4, death 16 → life 12 → pri 2.
- h group: birth 6, death 14 → life 8 → pri 4.5.
Still.

What if the h group's life is longer? For h's life to be longer, the h<<4 must happen later. In the target, h is loaded at 2738 and h<<4 at 2740 — adjacent.

Hmm, so with the same tie structure and same order, h wins. So the original must have had a different tie structure or a different insn count/order.

Wait — maybe the original had the h load in a DIFFERENT basic block? No.

Let me reconsider the tie at insn 35: `81 = 76 << 4` — 76 dies. The tie loop ties 81 to 76. But hold on: does the tie loop really tie when the used reg is a `reg/v` and the setreg is a `reg`? Yes.

Hmm, let me reconsider whether the tie happens in the TARGET. The target's 76,81,82 all in $3. Could that be coincidental allocation rather than ties? If not tied:
- 76: birth 6, death 10 → nrefs 4, life 4 → pri = 2*4/4 = 2.
- 81: birth 10, death 12 → nrefs 4, life 2 → pri = 4.
- 82: birth 12, death 14 → nrefs 4, life 2 → pri = 4.
- 77: birth 8, death 14 → nrefs 4, life 6 → pri = 1.33.
- 83: birth 14, death 16 → nrefs 4, life 2 → pri = 4.
Then allocation order: 81, 82, 83, 89... (pri 4), then 76 (2), then 77 (1.33).
81 gets $2, then 82 (can't be $2, overlapping) → $3, 83 → ... hmm, 83 could reuse $2 if free at its range? 81 is live 10-12, 83 born 14 → $2 free → 83 gets $2. But 81 already has $2. Hmm, allocation: 81 gets $2. 82: born 12, dies 14; 81 live until 12, so 82 can't use $2 (conflict at 12)? They touch. So 82 → $3. 83: born 14; 82 dies at 14 → $3 free? 83 could get $3. Then 76: born 6, dies 10 → $2 is free in 6..10? 81 is born 10, so 76 could take $2 (live 6-10, 81 starts at 10). Hmm, but 76's allocation happens after 81/82/83; $2 is marked live 10-12 by 81, so 76 (6-10) doesn't conflict → 76 gets $2. That gives 76=$2, 81=$2 — but then the move? No.

This is getting complicated. The point: the tie structure determines everything, and the target's all-$3 for {76,81,82} and all-$2 for {77,83} is consistent with ties + allocation.

Let me try a different approach: brute-force the source shape with the help of the twin func_8017EA24 (the next function in the TU) — maybe it's the same pattern and was cracked. Let me look at it.

Actually, better: let me look at other jr_8017C294 TUs for the same function. The `ls src/ | grep jr_8017C294` returned nothing?! Because the files are named like ov_SC03_112_jr_8017C294.c — the grep on `ls src/` should match the directory... wait, `ls src/` lists directories like ov_SC03_112. Let me list the files.

Let me search all src for a function with `(h << 4)` and `0x70`: grep "(h << 4)".
