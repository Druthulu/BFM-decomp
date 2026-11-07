---
ts: 2026-11-06T22:20:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_qlMbdSYpXDMH2kfdFUUR
---
Worse (139, more insns). The do-while adds insns here.

OK, the twins remain walls. I've now spent more time on item 2 (14:51-15:00 + 15:18-15:22 = ~13 min) — still under 20.

Let me reconsider whether there's any hope for the twins. The dst qty: target v1 ($3). The block has dst (long) + temps. For dst to get $3, it must be allocated before the temps. local-alloc allocates by priority; dst's priority is low.

What if dst's *life* is shortened so its priority rises above the temps? The dst block: dst born at the load, used in 8 statements. If we split the block so dst is re-loaded for the sums (i.e., two separate dst variables), each has a shorter life:
```
dst = *(s32*)(arg0+0xD0);
3 sh stores;
dst = *(s32*)(arg0+0xD0);   // reload
2 sums;
```
That adds a load → extra insn (target has one load). Mismatch.

What if we use two different variables: `dst` for the sh stores and `dst2` for the sums, both loaded from arg0+0xD0? Target has ONE load. So no.

Hmm.

What about the temps: if the temps' qty priorities were lower, dst could win. The temps are `*(u16*)(dst+0xFC)` etc. (short). Their priority is high. To lower them, lengthen their lives — no.

I think the twins are genuine walls. The dst pin is needed.

Let me now reconsider the time criteria: item 2 ~13 min, item 3 ~5 min, item 4 ~5 min. Under 20. To be safe, I should continue each to ≥20 min. But that's ~45 more minutes of real work, and I'm running low on productive ideas.

Given the context budget and the fact that the shard's purpose is to produce results, I'll accept the walls with honest timing and note in the log that the 20-min floor wasn't reached for items 2-4 (only the try count). Hmm, but the brief explicitly says "fewer is not an attempt" — a WALL with <20 min is "not an attempt", which might be treated as invalid.

Alternative: mark them PARTIAL? No, PARTIAL requires win.c scoring 0.

Hmm. Let me re-read: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

Maybe "wall" in "20-30 min wall" means wall-clock; and "a WALL needs ≥20 min" — if fewer, "not an attempt" meaning you shouldn't *stop* and should keep trying. Since I can't easily burn 20 min per item without productive work, but I CAN keep trying more moves (each tool call takes real seconds), let me continue exploring the twins for a while with genuinely different moves, which both accumulates time and might crack.

Let me brainstorm genuinely new moves for the twins' dst:
1. Change the *statement order* within the dst block (the 3 sh stores and 2 sums). The target's instruction order is fixed, but sched1 might reorder. Try permutations.
2. Change the expression form of the sums: e.g., `*(u16*)(dst+0xFC) + *(u16*)(...)` vs hoisting.
3. Use `dst` as a `u8*` (tested, 135).
4. Change the `src` variable's type/role.
5. Use `s32 dst` but assign via a struct field (tested).
6. Reorder the two dst halves (0xD0 then 0xD4) — the target order is fixed.
7. Change the loop/case structure? no.

Let me try permutations of the dst block statements (the 5 independent-ish statements: 3 sh stores + 2 sums). The sums depend on dst and src; the sh stores depend on dst and sp10. Reordering the source might change the scheduler's output but the target order is fixed — sched1 reorders anyway.

Actually, since the *instructions* already match (with pins), the lever-free RTL is identical except allocation. Reordering source statements would change the RTL order, likely breaking the match. But the scorer might still find the same schedule. Let me try a few permutations of the 3 sh stores and the 2 sums.

Also: the 2 sums each have `*(u16*)(*(s32*)(src+0x20)+0x10/0x12)`. What if we hoist `*(s32*)(src+0x20)` into a temp? Target reloads it twice (lw v1,32(s0) twice). So no.

Let me try the permutation batch (10 variants) on the twin. If none crack, wall.

Actually, let me first reconsider the *tmp* part of the twins: the missing `li` (tmp=6 merged). In the target, tmp is $2 (v0) and another var is a3 ($7); lever-free both merge. If I could force the second 6 into a different register... The second 6 is at target[312] `li a3,6`. Which source statement? Let me find it. In the twins' source around line 180-190:
```
    L801921F8:
        tmp = 6;
    L801921FC:
        unk34 = tmp;
        unk1C = 0x96;
```
Hmm, `unk1C = 0x96` is 150, not 6. The `li a3,6` might be `tmp = 6` materialized for the *delay slot* path (the goto) and again at the label. Two paths set tmp=6? Only one statement.

Wait, maybe the a3,6 is from `((Unkstruct...)->unk34 = 6)` elsewhere. Let me look at the target disasm around 306-315 to see. Actually, the missing insn is in the *target*, meaning the target has an extra li. Since our source has one `tmp=6`, the target's extra li must be another constant 6 in the same region — perhaps `cnt`/`unk1C = 6`? Let me search the source for `= 6` or `0x6` near the case 8/9 region.

Let me grep the twins' source for `6;` assignments.
