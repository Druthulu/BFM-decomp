---
ts: 2026-11-06T16:43:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XkSMilw32TxtMASi5t2u
---
Same residual. So even inlining doesn't help; the `lw v1,0(s1)` is still placed late (7 insns after). So the load scheduling is driven by something else (maybe the `p`/`s1` register and the memory dependence).

Hmm. The launder specifically fixes it. Let me understand the actual scheduling. In the target, `lw v1,0(s1)` is at 0x1eec, right after `lhu a0,0(a2)` at 0x1ee8. In mine, the `lw` is at index 137 while the target has it at 130.

Wait, mine[137] = `lw v1,0(s1)` and target[130] = `lw v1,0(s1)`. So in mine, the load moved DOWN by 7. In target it's early.

The launder is at the END of the function. How does an asm at the end affect the schedule of an insn 7 slots earlier? Via reg_n_sets($3) and the birthing boost. So the boost defers the load. Removing the boost (via a second set) lets the load schedule early.

But k01 (no pv local at all) still has a birthing SET: the load's dest is v1/$3, which is a pseudo with one set → boosted. So still late.

To kill the boost without an asm: make the load's destination pseudo have 2 sets. Hmm, what if the load's result is used in TWO places (e.g., stored to two different memory locations)? That doesn't add a SET to the pseudo.

What if we split the load into two: `pv1 = *(u32*)p; pv2 = pv1;`? pv1 has one set; pv2 one set.

What if the same pseudo is set twice by *two different loads* where the first is used and the second is used? E.g.:
```
pv = *(u32*)p;
*(u32*)p = (pv & 0xFF000000) | ...;   // uses pv
...
pv = *(u32*)p;   // second set (live? used?)
```
Second set needs a use. If we then use pv again somewhere... 

What if we restructure so pv is set twice legitimately:
```
pv = *(u32*)p;
pv = (pv & 0xFF000000);      // second set, live (used in the store)
*(u32*)p = pv | (...);
```
This is a real 2-set pseudo, both live! And it might emit the same bytes: `lw v1,0(s1)` then `and v1,v1,a0` (masking) — the target already has `and v1,v1,a0` as a separate insn (0x1f10). So writing `pv = pv & 0xFF000000;` as a separate statement might produce exactly the same instruction stream! Then the second SET of pv is the `and` instruction (a real set, live because used in the OR).

But wait: does this change the schedule? The `and` is a real instruction that already exists. Splitting the expression `(pv & 0xFF000000) | (...)` into `pv &= 0xFF000000; *(u32*)p = pv | (...)` — the `and` now sets pv (same register v1). reg_n_sets(pv)=2 → no boost → the load schedules early. And the bytes should be identical if the scheduler doesn't change.

Let me try! Also the `lui a0,0xff00` would still be needed for the and. In target, `lui a0,0xff00` is at 0x1f08 (after the load). Hmm.

Variant k06:
```
pv = *(u32 *)p;
pv = pv & 0xFF000000;
*(u32 *)p = pv | (CAST_NONSTRUCT(...) & 0xFFFFFF);
```
k07: `pv &= 0xFF000000;` compound.
k08: use a separate temp for the mask: `u32 hi = pv & 0xFF000000; *(u32*)p = hi | ...;` (pv one set again — no).

Also try:
k09: `pv = *(u32*)p; pv = pv & 0xFF000000; *(u32*)p = pv | (...);` with pv pinned $3.

Let me test.
