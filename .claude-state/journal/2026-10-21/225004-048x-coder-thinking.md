---
ts: 2026-10-22T04:50:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_TStFuhdZ9t7xcM5hb8G8
---
PINNED RTL:
- insn 63: the call, output = hard reg v0.
- insn 65: `(set (reg/v:SI 73) (reg:SI 2 v0))` — the copy into r73 (the call-result copy) — SAME as lever-free ✓.
- insn 72: `(set (reg/v:SI 2 v0) (const_int 0))` — the `result = 0` writes directly to the HARD REG v0 (the pinned pseudo!) ✓.
- insn 74: `(set (reg:SI 80) (and (reg 73) 32768))` — the AND into r80 (a temp).

So in the pinned version, r73 (the call-result copy) is in v1 (per the table) → the copy `move v1,v0` remains ✓.

And in the lever-free version, r73 is in v0 → the copy is coalesced.

The difference: r73's live range is [65..74]. In the pinned version, the hard reg v0 is occupied by the pinned pseudo from insn 72 → but r73's live range is [65..74] which overlaps [72..74] where v0 is occupied by the pinned pseudo → so r73 CONFLICTS with v0 → it can't take v0 → it takes v1 ✓✓✓.

So the mechanism is precise: the pinned pseudo occupies v0 from insn 72 (the `result = 0` def) and r73 is live until insn 74 → overlap → r73 can't be v0.

LEVER-FREE EQUIVALENT: we need SOME pseudo to occupy v0 during [72..74] — i.e. a pseudo whose live range overlaps r73's tail. In the lever-free y1, the local `result` (r74) is live from insn 74 (after the AND) → no overlap → r73 can be v0.

So we need the local result's FIRST DEF to be BEFORE the AND in RTL order (like the nopin form, where r74 is live from insn 72) AND r74 to win v0 over r73.

In nopin: r74 live [72..97], r73 live [65..74] → overlap [72..74] → they conflict → one takes v0, the other v1. The result: r73 took v0 (the copy preference) and r74 got v1 (and the value was computed in v1, with the final copy `move v0,v1`).

In the target: r73 → v1, r74 (the pinned hard reg) → v0.

So we need r74 to win the conflict. In gcc's global allocation, when two pseudos conflict and both prefer v0, the one with the higher PRIORITY wins (the preference is a tiebreak within the same priority?). Let's check the numbers in the nopin dump:
- r74 (the local result): pri 11428, refs 4, live 7, "conflicts v0,sp" (no preference).
- r73 (the call-result copy): pri 7500, refs 3, live 4, "conflicts sp, prefers v0".

r74 has a higher priority but NO preference; r73 has a lower priority but a preference for v0 → r73 won.

So the preference beats the priority. To make r74 win, r74 needs a preference for v0 as well! Where would r74's preference for v0 come from? A copy preference: r74 is the source of the final copy `(set v0 r74)` → gcc computes copy preferences: for a copy `(set a b)`, both a and b get preferences toward each other. So r74 SHOULD prefer v0 (it's the src of a copy to v0). But the dump shows no "prefers" for r74.

Hmm, in the nopin dump r74's note is "conflicts v0,sp" and no "prefers" — while r73 has "prefers v0". Maybe the dump prints "prefers" only for the pseudo's own hard-reg preference (from the "Register N in M" mapping), not copy preferences.

Hmm. In gcc 2.x's global allocation, the preferences are handled in `global.c: preference_to_...`. The allocation order line ";; N regs to allocate: 74 73" shows r74 first (higher pri). In gcc's global allocation, the allocnos are processed in order of priority; for each, it tries to assign a hard reg, avoiding conflicts with already-assigned ones. r74 is first → it should get v0 if v0 is free at that point! But the result shows r74 got v1 and r73 got v0.

Hmm, that contradicts. Unless the order line is not the allocation order but the "regs to allocate" list in a different sense.

Hmm, wait. Maybe in nopin, r74 conflicts with v0 because of the HARD REG conflict (v0 is used by the local allocnos r80/r82/r84 = the AND/load/xor temps, and by the call's output). The hard regs assigned to local allocnos are NOT available to global allocnos at all (they're reserved). So the global allocnos can only use hard regs not taken by local allocnos. In nopin, the local allocnos took v0 (r80, r82, r84 all show hard v0 — hmm, three pseudos with hard v0? they must be sequential).

Hmm, the "hard" column for local allocnos: r80 (the AND temp), r82 (the byte load), r84 (the xor) — in the lever-free machine code: the AND is in v0 (insn 25), the byte load `lbu v0,30(sp)` (insn 28) → r82 in v0, the xor `xori v0,v0,0x15` (insn 30) → r84 in v0. So all three temps got v0 (sequentially, they're chained). And the call-result copy r73 also got v0 (sequentially, before the AND).

So the local allocation gave v0 to a chain of pseudos: r73 (copy) → r80 (and) → r82 (load) → r84 (xor). And the global allocnos (r73? no r73 is global in lever-free) hmm.

In lever-free y1: r73 (the call-result copy) is GLOBAL (in the order line) and r74 (the local result) is GLOBAL. The temps r80/r82/r84 are LOCAL with hard v0.

In the pinned version: r73 (the call-result copy) — is it global? The pinned order line is "73" → r73 is global ✓ (same as lever-free). And in the pinned dump r73 "conflicts v0,sp, prefers v1" → it got v1 ✓ (because v0 was reserved by the pinned hard-reg pseudo).

So in both versions r73 is global; the difference is whether v0 is reserved.

Now: in the lever-free version, the global allocnos r73 and r74 must share the hard regs with the LOCAL allocnos' hard regs. The local allocnos r80/r82/r84 hold v0 (as their assigned reg). In global allocation, a global allocno can take a hard reg only outside the local allocnos' live ranges... but here r74 needs v0 during [72..97] and the local temps use v0 at [74..85] → conflict → r74 gets another reg (v1) ✓ (in y1, r74 got v0! hmm).

In y1: r74 (live [74..97]) got v0 ✓ — and the temps r80 (live [74..76]) also use v0 → conflict?! But y1's machine code has the AND in v0 (insn 25 `andi v0,v0,0x8000`) and the boolean in v0 (lbu v0, xori v0, sltiu v0) — so the AND's temp r80 and the local result r74 BOTH in v0, sequentially? r80's live range is [74..76] and r74's is [74..97] → they overlap → conflict! Yet both are in v0 in the machine code?!

Hmm, wait: in y1's machine code, is the AND's result in the same reg as r74? The `andi v0,v0,0x8000` (insn 25) is on r73's reg (r73 is live until the andi) → r73 = v0. Then the AND result r80 is ALSO v0 (the andi is in-place on r73's reg, so r80 = r73's reg = v0; r73 dies). Then the branch tests r80 (v0). Then the boolean is computed into v0 (r74 = v0): lbu v0, xori v0, sltiu v0 → so r80 (v0) dies and r74 (v0) takes over ✓ sequentially.

So in y1: r73, r80, r74 are all v0 sequentially. But r74 (live [74..97]) overlaps r80 (live [74..76])?? Both start at 74. Hmm, r80 = the AND result defined at 74 and used at 76 → live [74..76]. r74 = defined at 74 (in y1? the `result = 0` is at RTL 72 in nopin; in y1 the def order differs) hmm.

OK, the live ranges overlap but the RELOAD phase resolves them by inserting moves or by the coalescer merging. Fine.

So the picture: everything is chained through v0, and the call-result copy r73 gets v0 because it's the head of the chain (the copy from the call's v0 output).

To break the chain at the head, r73 must not be able to take v0 — i.e. v0 must be occupied/reserved during r73's live range [65..74].

In the pinned version, the pinned pseudo occupies v0 during [72..97] → r73 (live [65..74]) overlaps at [72..74] → r73 can't take v0 → v1 ✓.

LEVER-FREE: we need a pseudo occupying v0 during [72..74]. What if the local `result` (r74) is live from insn 72 (as in nopin) AND r73 is denied v0 by... hmm, in nopin r74 conflicts v0 and got v1 while r73 got v0. The conflict is symmetric but the winner is decided by the preference.

So the question becomes: how do we give r74 (or another pseudo) the v0 preference so it beats r73?

Hmm! What if there were TWO pseudos competing: r74 (the local result, live [72..97]) and something else... The winner of the v0 preference: r73 has "prefers v0" (its copy preference from the call's v0 output).

What if the call's output were NOT v0? The call insn's output is v0 because gcc's mips pattern for a call returns in v0. Fixed.

Hmm, what if the call result is used by something else first, so the copy chain starts elsewhere? E.g. if the call result is immediately copied to a variable of a different type (a mode change), the chain would be: v0 → r73 (SI) → ... and the preference might pass along differently.

Honestly, the most promising remaining idea: make the local result's def come before the AND (nopin structure) AND give the local result MORE priority so it beats r73. But the preference beat the priority in nopin (11428 vs 7500)...

Hmm, unless the preference for r73 is only "soft". Let me test: in the nopin structure, if the local result had pri >> r73's, would it win? Let me construct: r73 (the call-result copy) pri = refs*2^floor(log2 refs)*10000/live. To lower r73's pri, make its live range longer or its refs fewer. r73's refs = 3 (the copy def, the test use, the and use) and live 4.

To lower r73's pri: increase its live range. E.g., if the mask test used a variable assigned from ret earlier...

Alternatively, RAISE r74's pri massively: refs 4, live 7 → 11428. If refs were 8 → 2^3*8 = 64 → pri = 64*10000/7 = 91428. How to get 8 refs on the local result? Each extra def/use adds 1 ref.

Hmm, what if the local result is assigned in MORE places (but the code stays the same)? E.g. `result = 0;` in three places? Each def is a ref. But extra defs → extra code (mov v0,zero) → mismatch.

Unless the extra defs are in the SAME place (a re-tie): `result = 0; result = 0;` → the second is dead → removed by DSE → no extra ref? Hmm, DSE at the RTL level might leave it (gcc 2.7.2's cse removes redundant stores to a local? "cse.c: cse_basic_block" removes a store if the value is the same? gcc's cse has "store merging" for the same value).

The moves file mentions "re-tie" as a real lever: "the v1 re-tie materialises a real move (v1=mode) that cse merges in plain C" — so a re-tie CAN create a real move.

Hmm! What about: `result = 0;` then later `result = 0;` again in the same block — if cse merges them, no extra ref. If not, we get an extra `move v0,zero` (a mismatch).

Risky. Let me instead try to lower r73's priority by making the call-result copy's live range longer — e.g. by using `ret` again LATER in the code (after the branch). Semantically we could use ret in a way that's equivalent... e.g.:

```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = X;
    } else {
        result = 0;
    }
} else {
    result = 0;
}
```
Here `ret` is used twice, both before the branch.

What if we write it as:
```
mask = ret & 0x8000;     /* the AND into a variable */
if (ret != 0) {
    if (mask != 0) { result = X; } else { result = 0; }
} else { result = 0; }
```
Here `ret`'s live range extends to the `mask` assignment... but the AND is now a separate insn? It would be the same `andi` but into a variable (the same reg). Hmm, this could work: the AND temp becomes a variable (r_new) instead of a temp, and `ret`'s live range might extend.

Hmm, but the ORDER changes: `mask = ret & 0x8000` before the `ret != 0` test → the RTL would have the AND before the branch → the machine code order changes (the AND would be before the first branch, not in its delay slot) → mismatch.

Alternatively:
```
if (ret != 0) {
    mask = ret & 0x8000;
    if (mask != 0) { result = X; } else { result = 0; }
} else { result = 0; }
```
The AND is inside the then-branch → the machine code: the branch, then the andi (not in the delay slot) → mismatch? In the target, the andi IS in the delay slot of the first beqz. With the AND inside the then-branch, gcc might still schedule it into the delay slot (the scheduler can hoist it) ✓ — that's what happens in the current form (the AND is in the delay slot even though the source has the mask test inside the branch).

So this variant might produce the same machine code but with the AND's result in a variable (r_new, live [74..76] → same) and `ret`'s live range [65..74] (same). Hmm, no change to r73's live range.

To extend r73's live range, `ret` must be used AFTER insn 74. E.g. the else-branch could test ret again? Not semantically equivalent.

OK, alternative: reduce r73's REFS. r73's refs = 3: (1) the copy def, (2) the test `eq r73 0`, (3) the AND's use. Can't reduce.

Hmm, so r73's pri is fixed at 7500 in the nopin structure. r74's pri = 11428 (refs 4, live 7). r74 already beats r73 on priority but loses on preference.

So the question: does gcc's global allocation prefer the pseudo with the copy preference over the one with a higher priority? In the nopin dump, the ORDER line is "74 73" (r74 first) — so r74 was considered FIRST but ended up in v1 while r73 got v0. That means when r74 was processed, v0 was unavailable (because the local allocnos r80/r82/r84 hold v0 — reserved!). Ahh, that's it: v0 is reserved by the LOCAL allocnos (the temps r80, r82, r84 which were assigned v0 by local allocation). So r74 couldn't have v0 at all → got v1. And r73 (processed second) preferred v0 → but v0 is taken by the local allocnos... hmm, but r73 DID get v0 in the end.

Hmm, in the lever-free code the AND/load/xor temps are in v0 and the call-result copy is also in v0 — sequentially. So global and local allocnos can share a hard reg if their live ranges don't overlap.

So when r74 was processed (first), v0 was... available? Its live range [72..97] overlaps the temps' live ranges ([74..76], [81..83], [83..85]) → conflict → r74 gets another reg (v1) ✓✓. And r73 (live [65..74]) overlaps only the AND temp (r80, live [74..76]) at insn 74 → hmm, borderline. r73 got v0 ✓.

So the reason r74 lost v0: it conflicts with the TEMPS' v0 usage (the AND/load/xor chain), not with r73!

The temps are in v0 because... local allocation gave them v0 (they're the standard mips temp regs: the AND's result prefers v0? the load's result prefers v0? etc.). Hmm, in the PINNED version, r83/r85 (the load/xor temps) also got v0, and r80 (the call-result copy) got v1.

So in the pinned version, the call-result copy r80 got v1 — why? Because v0 was reserved for the pinned hard-reg pseudo (the local `result` = hard reg v0), so the LOCAL allocation couldn't use v0 for the call-result copy → it got v1.

Hmm! So the call-result copy r73/r80 is a LOCAL allocno in the pinned version (assigned v1 by local allocation) but GLOBAL in the lever-free version? Let me check: in the pinned dump, the lreg table has r80 (hard v1) — is r80 in the .greg order line? The pinned order line was "73" → only r73. So r80 is LOCAL ✓ (assigned v1 by local allocation).

In the lever-free dump, the order line was "74 73" → r73 is GLOBAL. Why is r73 global in lever-free but local in pinned? Because a pseudo becomes global if it conflicts with a hard reg... In the pinned version, r73's copy is from v0 — hmm.

The difference: in the lever-free version, r73 (the call-result copy) conflicts with the hard reg v0 (because the local result r74 wants v0 and r74 is global...). Circular reasoning again.

OK. Time to stop analyzing. Practical approach: TRY to make r73 LOCAL and land in v1. r73 is local if it doesn't conflict with any hard reg. It conflicts with v0 because... the local result r74 (global) prefers v0? Hmm, in the nopin structure r74 is global and conflicts v0.

Let me try the y1 structure (r74's def after the AND) but with r74 made GLOBAL and conflicting... hmm, y1 has r74 global (order 74 73) and r73 global. Both global, and r73 got v0 while r74 also got v0 (they don't overlap).

What if we make them overlap AND have r74 take v0 by raising r74's priority even higher? In the nopin structure, r74's live range [72..97] overlaps the temps' v0 usage → r74 can't be v0 regardless of priority (the conflict with the local allocnos' hard regs is structural).

Hmm, wait. Is that true? The conflict is with the temps r80/r82/r84 which are local allocnos holding v0. If r74 is processed first (higher pri) and takes v0, the temps would be forced to other regs (the reload phase would insert moves). gcc's global allocation: global allocnos can take hard regs that local allocnos hold, if the live ranges don't overlap; the local allocnos' hard regs are "preferred" but the global allocation has priority over the local allocation's choices? In gcc, the local allocation happens first and assigns hard regs; the global allocation then avoids them where they conflict.

Since r74 conflicts with the temps' v0 (overlapping live ranges), r74 can't be v0 — UNLESS the temps' live ranges shrink or move.

Hmm, in the TARGET (pinned), the value (the pinned pseudo, hard v0) coexists with the temps in v0 (the load/xor chain is in v0: `lbu v0,30(sp)`, `xori v0,v0,0x15` — those are the PINNED result's reg!). So in the pinned version, the temps' chain is in v0 because the pinned pseudo occupies v0 and the temps are chained onto it.

So in the target, the AND temp r80 is in v1 (the call-result copy's reg) and the load/xor temps r83/r85 are in v0.

In the lever-free version: the AND temp r80 is in v0 (chained onto the call-result copy in v0) and the load/xor temps r82/r84 in v0 as well.

So everything is consistent with "v0 is the chain register" in the lever-free case.

To get the target, we need: the call-result copy in v1, the AND temp in v1 (chained), the load/xor temps in v0 (chained onto the local result which is in v0).

So the local result (r74) must be in v0 and the call-result chain in v1. The chain break must happen between the call-result copy and the load/xor chain. In the target, the break is at the AND: r73 (v1) → r80 (v1, the AND result, in-place) → then the load/xor chain starts fresh in v0.

In the lever-free y1: r73 (v0) → r80 (v0, the AND) → then the load/xor chain continues in v0 → and r74 (the local result) also v0.

So the difference: in the target, the local result (v0) and the AND temp (v1) are in different regs; in y1 they're both v0 (sequentially).

Hmm! In the target, the local result's live range [72..97] overlaps the AND temp's [74..76] → they MUST be in different regs ✓ (that's forced!). In y1, the local result's live range starts at 74 — hmm, exactly at the AND's def → also overlapping? But y1 put them both in v0 (sequentially: the AND dies at 76, and the local result's first def is at... hmm).

Let me check y1's RTL: in y1, the `result = 0` (in the inner else) comes after the AND in RTL order? Let me check the y1 dump: the local result's def order. Let me grep y1's lreg RTL for the region.

Actually, in y1's machine code the AND is in v0 and the boolean is computed into v0 (lbu v0, xori v0, sltiu v0) → so the AND's reg (v0) and the local result's reg (v0) — the AND dies before the load, so they're sequential ✓ no conflict.

But in the TARGET: the AND is in v1 and the load in v0 → they're in different regs even though sequential. Why? Because in the target the call-result copy is in v1 and the AND is chained onto it (in v1), while the local result (pinned, v0) starts a new chain.

So in the target, the local result's def (insn 72, the `result = 0` = the pinned v0) comes BEFORE the AND (insn 74) in RTL order → the local result is live [72..97] → it overlaps the AND temp [74..76] → they need different regs → the AND temp takes the call-result copy's reg (v1, chained) and the local result keeps v0 ✓.

So the target structure REQUIRES: the local result's first def BEFORE the AND in RTL order (nopin structure!), and the local result in v0.

And in the lever-free nopin structure, r74 (the local result, live [72..97]) conflicts with v0 (the temps' reg) → gets v1.

Hmm, but WHY does r74 conflict with v0 in nopin? Because the temps r80/r82/r84 (local allocnos) hold v0. r74's live range [72..97] overlaps r80's [74..76], r82's, r84's → conflict with v0.

But in the pinned version, the local result IS the hard reg v0 (the pinned pseudo), and the temps r83/r85 (load/xor) got v0 too — because in the pinned version the hard reg v0 is already the pinned pseudo's, and the temps were assigned v0 by local allocation as well (they're sequential with the pinned pseudo's use).

So the difference is: in the pinned version, the local `result` doesn't need a reg from the pool (it's hard-assigned v0), so the temps can use v0 freely around it.

Lever-free: r74 needs a reg from the pool; the pool's v0 is taken by the temps.

So to make r74 take v0, the temps must NOT be in v0 during r74's live range. The temps are the AND/load/xor. Hmm, the load/xor chain is in v0 in both versions.

In the target, during r74's live range [72..97], the regs in use: v0 (the pinned result + the load/xor chain) and v1 (the call-result copy + the AND temp).

In the lever-free nopin, r74's live range [72..97] and the temps' v0 usage overlaps → r74 → v1.

So lever-free, the local result can only be in v0 if the temps are NOT in v0 during [72..97]. The temps are in v0 because local allocation put them there (they're the standard temps with v0 preference? Hmm, why would the AND temp prefer v0? The `andi` instruction on mips can use any reg...).

Hmm, r80 (the AND temp) has hard v0 in the lever-free dump. In the pinned dump, the AND temp is r80 → hard v1! So in the pinned version, the AND temp took v1 (the call-result copy's reg) and in the lever-free it took v0.

The AND temp's hard reg choice: local allocation picks by priority among the free hard regs. The AND temp (pri 10000, refs 2, live 2) vs the call-result copy (r73, pri 7500, live 4) — the AND temp has a higher priority → it gets v0 first, and the call-result copy gets... v1? But in the lever-free, the call-result copy IS in v0 and the AND temp in v0 too (sequentially, they don't overlap: r73 [65..74], r80 [74..76] → hmm, they overlap at 74).

Hmm, they're chained: r73 dies at 74 (the AND uses it), r80 is defined at 74 → so r73's live range is [65..74) and r80's [74..76] → no overlap ✓ → both can be v0 ✓ (a chain).

In the pinned version, the AND temp (r80, pri 10000) got v1 — why not v0? Because in the pinned version, v0 is reserved for the pinned pseudo → the AND temp couldn't take v0 → v1 ✓. And the call-result copy (r73, pri 7500) also couldn't take v0 → v1 ✓ (both in v1, chained ✓).

So in the pinned version, EVERYTHING that would be v0 is pushed to v1 except the pinned pseudo's chain.

Lever-free: the AND temp (pri 10000) takes v0 (highest priority among the v0-preferring pseudos) and the call-result copy (pri 7500) also gets v0 (chained before it).

To make the call-result copy land in v1, we need the AND temp (or something) to take v0 and the call-result copy to NOT be chainable with it — i.e. their live ranges must overlap so they conflict.

The call-result copy r73 is live [65..74] and the AND temp [74..76]. They chain. If they overlapped, r73 would be forced to v1 (since the AND temp has the higher priority and takes v0) ✓✓.

How to make them overlap? The AND temp's live range would have to extend back before insn 65 — impossible — or the call-result copy's live range must extend past 74.

The call-result copy r73 = the copy `(set r73 v0)` — its live range ends at its last use (the AND at 74). To extend it, `ret` must be used after the AND. Semantically: the mask test uses ret; could we use ret again later without changing the code?

IDEA: use `ret` in the ELSE branch of the inner if:
```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = X;
    } else {
        result = 0;
    }
} else {
    result = 0;
}
```
No extra use of ret.

Hmm, what about using `ret` in a way that's dead but survives to RTL? E.g. `if (ret == 0x7fffffff) result = 1;` — an extra branch (code changes).

What about the ORDER of the two tests: `if ((ret & 0x8000) != 0)` first and `ret != 0` second? Then the AND happens first (before the branch) → the AND temp's live range would start at 65-ish → overlapping the call-result copy ✓!!

Wait: the source
```
if ((ret & 0x8000) != 0) {
    result = X;
} else {
    result = 0;
}
```
(the outer `ret != 0` test dropped — but that's semantically different! Well, actually: (ret & 0x8000) != 0 implies ret != 0, so dropping the outer test is semantically EQUIVALENT ✓ (for a signed int, bit 15 set → negative → != 0). gcc might even fold it.)

But the ROM HAS the outer test (`beqz v1` then `andi`). So we need both tests, in the order: outer test first (on the call result), then the AND.

The AND's temp live range: [def, use]. The def is right after the outer test. The call-result copy's live range: [65..74] where 74 = the AND's def (which kills r73).

To overlap, the call-result copy must be live AT the AND's def — i.e. the AND must not kill it... but the AND USES it (r73 is the AND's operand) → r73 dies at the AND ✓. So they're inherently adjacent: r73 [65..74], r80 [74..76]. Always adjacent → chainable → always share a reg.

Hmm!! Unless the AND's result is computed BEFORE the outer test (i.e. the source computes the mask first):
```
mask = ret & 0x8000;      /* the AND before the test */
if (ret != 0) {
    if (mask != 0) { result = X; } else { result = 0; }
} else { result = 0; }
```
Then the AND temp r80 is live [65..76] (defined at 65, used at 76) and the call-result copy r73 is live [65..74] → they OVERLAP ✓✓ → they need different regs → the AND temp (pri 10000) takes v0 and the call-result copy (pri 7500) gets v1 ✓ → the copy `move v1,v0` remains ✓✓✓!!!

And the machine code: the AND would be computed BEFORE the outer branch (in the delay slot? the AND is at RTL 65-ish, before the branch at 68) → the machine order: `move v1,v0` (insn 24), `andi v?,v?,0x8000` (insn 25), `beqz v1` (insn 26)? But the target has: move v1,v0 (24), beqz v1 (25), andi v1,v1,0x8000 (26) — the AND is in the delay slot of the beqz!

In my variant the AND would be before the branch → the machine order would be: move v1,v0; andi v1,v1,0x8000; beqz v1 → the branch's delay slot would be something else → the order differs from the target (the target has beqz then andi).

Hmm. But the scheduler might hoist the AND into the delay slot anyway (the branch delay slot can hold the AND if the AND is independent of the branch). In the target, the AND is in the delay slot of the FIRST branch (which tests the call result) — the AND is independent of that branch (it uses the call result, which is live across the branch) ✓. So the scheduler CAN put the AND in the delay slot even if the AND is defined before the branch in the RTL. But then the AND's live range would still start before the branch → overlapping the call-result copy ✓.

So this variant might give exactly the target! Let me try it!

The source:
```
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    int mask;
    ...
    ret = func_80133784(1, buf1, (int)buf2);
    mask = ret & 0x8000;
    if (ret != 0) {
        if (mask != 0) {
            result = X;
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}
```
Hmm, but `mask` as a variable → the AND's result is stored in a variable (r_new) — that's the same pseudo. The extra `int mask;` declaration is fine (C0505 allows temps).

Careful about semantics: `mask = ret & 0x8000` — for a signed int, `ret & 0x8000` = the bit-15 mask ✓ (same as the ROM's andi).

Let me also try variants where the mask test is done directly on `ret & 0x8000` but the ORDER of the two tests is swapped:
```
if ((ret & 0x8000) != 0) { result = X; } else if (ret != 0) { result = 0; } else { result = 0; }
```
Hmm, the outer test would be dropped by gcc maybe.

Let me try the mask-variable variant now! This is very promising.

Also variant: keep the mask inline but compute it in a temp assigned before the outer test:
```
mask = ret & 0x8000;
if (ret != 0) { if ((mask & 0x8000) != 0) {...} }
```
Hmm, that changes the AND's operand.

Let me generate:
z1: mask variable, computed before the outer test, tested inside.
z2: mask variable computed before, and the inner test `mask != 0`.
z3: like z1 but with the direct-return form.
z4: mask as unsigned int.
z5: mask computed before the outer test, but the outer test first in the source... can't.

Let me write andscore them.
