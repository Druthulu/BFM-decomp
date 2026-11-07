---
ts: 2026-11-06T15:40:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pFEqRXoMgt2KwDuiy0mm
---
28 scored tries now (c1 + 6 + 4 + 3 + 4 + 2 + 8 = 28). Let me do a few more with the "dead reset immediately after" per C0414 but in different positions, plus the `do{}while(0)` C0535 idea (splits cse1 EBB!). That's a promising one: C0535 says do{}while(0) splits cse1's EBB. If the do-while splits the EBB between the two calls, cse can't merge across the EBB boundary!

C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". The mechanism: cse1's EBB is split at the loop boundary, so expressions don't propagate across. If we wrap the first call in `do { ... } while(0)`, the EBB splits before the second call → the second `mb+0x18` can't reuse the first's sum → addiu re-emitted!

But wait, the launder's effect is *within* one EBB: the sum is computed before the first call and reused after. Splitting the EBB at the do-while should prevent that. Let me test:

```
mb = (u8 *)&D_800AF630;
do { func_8004914C(mb + 0x18); } while (0);  // !FAKE: do-while
func_800491AC(mb + 0x18);
```
Note the constraint: `do{}while(0)` only with `// !FAKE: do-while`.

But does an empty do-while split the EBB in cse1? The do-while creates a NOTE_INSN_LOOP_BEG/END or a jump? With -O, gcc recognizes `do{}while(0)` and may delete the loop notes but the EBB split may persist. C0535 says it works.

Also C0414 dead-reset after the call, combined with a do-while.

Let me test:
ba: do-while around first call.
bb: do-while around both calls separately.
bc: do-while around the assignment + first call.
bd: do-while around second call only.

The target must still have same insn count (397). do-while(0) should be zero-cost.
