---
ts: 2026-11-06T10:12:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TC481PaElPSgjN3b2AKL
---
Started 02:54, now 03:11 → 17 min elapsed total (items 1 and 2). Item 2 started around 03:00. So ~12 min on item 2. Let me continue a bit but I should move to items 3/4 soon. The brief says 20-30 min per item.

Let me think about item 2 differently: what if I can't crack the pin but the keepalive is crackable? Then result would be WALL (best = lowest lever-free score = 21). 

Actually, let me reconsider the whole thing: maybe the target's register assignment can be achieved by making s1ang *global* through a real use that doesn't add instructions: what if the `u6` variable is REMOVED and s1ang is masked in place, but WITHOUT losing the u5 andi? g1 lost an instruction. Why? Let me investigate g1's RTL. Maybe the u5 andi was merged because `(x & 0xFFF) == (y & 0xFFF)` got optimized... Actually, gcc's combine might see `andi a0,a0,0xfff` and `andi s0,s0,0xfff` then `bne` — it could combine the comparison into `(a0 ^ s0) & 0xFFF`? No, MIPS has no such.

Hmm, maybe g1's lost instruction is the `move v0,a0` or something. Let me count g1's asm. Actually the diff showed mine[1:1] target[1:5] insert 4, and mine[14:18] delete 4 — net 0? But score says 74 vs 75. Confusing.

Let me try a cleaner g1 variant: keep u6 but ALSO write s1ang's mask in place, so s1ang is global:
```
s1ang = s1ang & 0xFFF;
u6 = s1ang;
if (u6 == u5) return 0;
...
```
Then s1ang is used at the andi (block 0) and at the copy (block 0) — still local! And u6 = s1ang is a copy, u6 global. Same.

What if `u6` is eliminated and s1ang used directly, but keep u5's mask separate by writing the comparison differently:
```
s1ang = s1ang & 0xFFF;
if (s1ang == (u5 & 0xFFF)) ...
```
u5 is already masked. Hmm.

Let me look at g1's full asm to find the missing instruction. Let me dump g1's asm via hdump.

Actually, let me just look at the .s. But hdump needs a body file; g1.c is a body. Let me run hdump on g1.

Hmm, this is a lot. Let me instead consider: maybe g1 lost the `move v0,a0` (arg0 copy). In g1's diff, mine[1:1] target[1:5]: mine is missing `move v0,a0; sw s0; move s0,a1; sw ra` at position 1. Then mine[2] is `move s1,a1`... So mine still has `move s1,a1`. Hmm, the diff alignment is confusing.

Let me get g1's full asm and compare to target. Let me use --keep and objdump.

Actually, let me be pragmatic. I have 4 items and limited time. Item 1 is a confirmed WALL. Item 2 is looking like a WALL (lreg-qty-order). Let me do a quick batch of remaining tries for item 2, then move to items 3 and 4.

Let me try 5 more quick variants:
- t1: u32 s1ang
- t2: s1ang = s1ang & 0xFFF; u6 = s1ang (alias)
- t3: do-while around the tail (C0535)
- t4: d as `u32`
- t5: s1ang load via `(s16)` explicit

Let me create and score.
