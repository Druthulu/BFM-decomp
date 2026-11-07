---
ts: 2026-11-06T11:58:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LL87RYmODj6PzQrdewFl
---
Declaration order doesn't change it. The rotation is stable.

Let me think about why the rotation happens. In y07, temp_a0=v1, temp_v0=a0, temp_v1=v0. The allocation seems to be: the values that cross the call or have long lives get the callee-saved? No.

Hmm, maybe the intervening store extends temp_v1's live range so it conflicts differently, causing the rotation.

Let me look at the y07 alloc table more carefully:
- r72: arg0 pointer, 16 refs, pri 27826, crosses call, conflicts v0,v1,a0,sp → s0 (saved).
- r75: 8 refs, live 13, dies in 2 places, conflicts v0,v1,sp → no hard reg? maybe temp_v1? 8 refs: andi? negu? sh×2... Hmm temp_v1 has: andi result? Actually temp_v1 = -(temp_v0 & 0xFF): refs = 1 (def) + 2 (sh) = 3. Not 8.

Let me not.

The final asm shows the rotation. Let me try a different intervening store that uses a DIFFERENT value: what if the intervening store is to +6 itself with the SAME value (a redundant store)? cse would... the second store would overwrite the entry, still recorded.

What if the intervening "store" is a store to an address computed from the reload's value? no.

Alternative: instead of an intervening store, make the reload's address appear different by using a **different base expression that cse can't equate**, without changing the asm. Hmm.

What about using `*(u8 *)((u8 *)arg0 + 6)` for the store and `*(u8 *)((u8 *)arg0 + 6)` for the load but with the load's address computed through an `s32` intermediate:
```
s32 off = 6;
temp_v0 = *(u8 *)((u8 *)arg0 + off);
```
Then the address is `(plus (reg) (reg off))` where off is a constant 6 pseudo. cse might fold off to 6 and equate. Or it might not! And the asm might still be `lbu v0,6(s0)` if cse folds the constant.

Let me test: `s32 off = 6; temp_v0 = *(u8*)((u8*)arg0 + off);` — but the front-end folds `arg0 + off` with off=6? If off is a local const variable, gcc may not fold it at the tree level; cse would fold it to 6 and equate to the store address. Hmm.

Another: `temp_v0 = *(u8 *)((u8 *)arg0 + 6 + 0);` folds.

What about reading through an `s32` variable that holds the address: `s32 addr = (s32)arg0 + 6; temp_v0 = *(u8*)addr;` — cse folds.

Hmm.

Let me revisit the intervening-store approach but find one that doesn't perturb regalloc. The perturbation comes from the store being moved by sched1 but still counted in the alloc. What if the intervening store is one that sched1 keeps in place? The target order has no store between sb6 and lbu6, so any intervening store must be moved. But maybe sched1's move is what causes the regalloc change.

What if the intervening store is placed AFTER the lbu in source but cse processes it before? No, cse processes in order.

Hmm, wait: cse1 runs BEFORE sched1. So the source order (after cse) determines what cse sees. The source order has the intervening store between. Then sched1 moves it. So the alloc sees the sched1 order (same as target) but the *uids* differ. The uids affect global-alloc's tie-breaking? The alloc table shows "TIE (lower allocno wins, global.c:607)" — allocno numbers, not uids. Allocnos are created in the order pseudos appear in the RTL (after sched1). Since the sched1 order is the same, allocno numbers should be the same...

Unless the reload's pseudo is different. In the target (no forward), the reload is `lbu v0,6(s0)` — a load. In y07, the reload is also a load. But maybe the pseudo for the reload differs in numbering because cse created extra pseudos.

Hmm.

Let me try yet another approach: make the store and the load use different **mem modes** so the hash differs. E.g., store as `sb` (QI) and load as... must be QI for lbu.

What if the store is done through a `union` that cse sees as a different mode? E.g., store an `s32` to a union member that overlaps? No, would be sw.

OK. Let me consider the possibility that the target's regalloc is achievable by a different route: maybe the ORIGINAL source had the `sh 16` store between the sb and lbu, and sched1 moved it, and the original regalloc matches the target. That would mean my y07 should match... but it doesn't. So maybe the original had a different intervening statement.

Let me look at the target order again:
```
sb v0,6(s0)
lbu v0,6(s0)
addiu a0,a0,255
sb a0,5(s0)
sh v1,16(s0)
sh v1,12(s0)
sh v0,22(s0)
...
```
The lbu immediately follows the sb. So in the ORIGINAL, cse didn't forward. 

Given the difficulty, maybe I should accept WALL. But I've made real progress: the lbu is preserved by an intervening store, with the rest of the code order matching. Only the register rotation remains. That's a `global-alloc` / `lreg` issue.

Let me try a few more intervening-store choices: what if the intervening store is the `sh 0x16` (first in target order after 12)? y03 = 14. All 14.

What if TWO intervening stores? Might perturb more.

What if the intervening store is a store to the SAME address +6 but of a DIFFERENT value (e.g., store temp_v1's low byte)? That would change the final value — no.

What if the intervening store is `sb` to +6 of the SAME value, i.e., a redundant store? Then cse invalidates (any store invalidates) and records the new entry; the load would still forward to the second store. Unless the second store's src isn't recordable... circular.

Hmm.

Let me try: intervening store to +6 of the value via a different expression (a launder — not allowed).

OK, let me try to fix the regalloc by making the temps have different types:
- temp_v0 as `u32`? 
- temp_a0 as `s32`? (x05 was score 2 without the intervening store)
- temp_v1 as `s32`?

Let me test y07 with temp types varied. Quick batch.

Actually, let me look at the register assignment mechanism: target has temp_a0=a0, temp_v0=v0, temp_v1=v1. Mine has a rotation. If I can shift the priority so temp_v0 gets v0 and temp_a0 gets a0...

In mine, temp_v0=a0, temp_v1=v0, temp_a0=v1. So temp_v1 got v0 (highest). Why? temp_v1 is s16 and used in 2 sh stores. Its live range: defined before the sb6, used at the end (after the reload). So it's live across the sb/lbu/addiu/sb — long. In the target, temp_v1 is also live across that. But the target gives it v1.

Hmm, maybe in the target the pins forced temp_v1 to $3 (v1) — yes! The pin was `register s16 temp_v1 __asm__("$3")`. So the target's v1 for temp_v1 is FORCED by the pin. Without the pin, temp_v1 might naturally get v0.

So the pin's removal causes temp_v1 to take v0, shifting everything. To compensate without a pin, I need temp_v1 to naturally get v1.

Since temp_v1 is a long-lived value, maybe I can make another value "more important" for v0. temp_v0 (the subtraction result, used 5+ times) should have higher priority than temp_v1 (3 refs). In mine, temp_v0 got a0 and temp_v1 got v0 — backwards.

Hmm, maybe local-alloc's qty priority: temp_v1 (s16, QI/HI mode) has 3 refs; temp_v0 (SI) has more refs. Higher qty → better reg. But temp_v1 got v0.

Wait, maybe temp_v0 and the reload pseudo are separate, and the reload has many refs.

Let me look at the actual .lreg table for y07 in detail. The table showed r74=v0 (3 refs, 7 live), r90=v0 (2 refs, 6 live, blk1), r73=v1 (3 refs, 16 live). Hmm.

I think the cleanest way forward is to try many small variations and look for score 0. Let me generate a batch varying:
- temp types (s16/s32/u8/u32/s8)
- reload into a separate variable with different types
- declaration orders (done)
- the intervening store choice (done)

Given time (~05:05), let me do one more batch and then decide.

Actually — wait. Let me reconsider the pin: the pin is `register s16 temp_v1 __asm__("$3")`. The kinds are barrier,pin. The task says MATCH requires the kinds gone. But maybe the original code had `temp_v1` as a specific type that naturally lands in v1. 

What if temp_v1 is declared as `s32` and assigned `-(temp_v0 & 0xFF)`? Then the sh stores cast to s16. The target's `andi v1,v0,0xff; negu v1,v1` — the andi produces a 0..255 value, negu negates it (as s32). Then `sh v1,16` stores the low 16 bits. So temp_v1 could be s32! In the current code it's s16 with a cast. Let me test temp_v1 as s32.

That might change the allocation (a 32-bit value vs 16-bit).

Let me test y07 with temp_v1 s32, and other type combos.

Let me write a quick batch.
