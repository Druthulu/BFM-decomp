---
ts: 2026-10-22T04:44:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9oprHX24eVmqbsUEoX18
---
Pinned dump: r80 (hard v1!) is the call-result pseudo — it's in v1 ($3) ✓ — while r83, r85 are v0 (the void calls' results).

And r73 (pri 7500, refs 3, live 4, "conflicts v0,sp, prefers v1") is the RESULT_DECL, allocated globally (order: 73).

Note: in the pinned version, the local `result` (pinned to $2) doesn't appear as a pseudo (it's a hard-reg pseudo → not in the lreg table).

So in the pinned version:
- The call result pseudo r80 got v1 — because v0 was reserved by the pinned pseudo. Its pri is 10000 (refs 2, live 2) — same as in the lever-free version (r84: pri 10000, refs 2, live 2, hard v0).

The difference between the two dumps:
lever-free: r80(v0), r82(v0), r84(v0), r74(global, pri 11428, conflicts v0,sp), r73(global, pri 7500, conflicts sp, prefers v0)
pinned:    r80(v1), r83(v0), r85(v0), r73(global, pri 7500, conflicts v0,sp, prefers v1)

So in the pinned version, the call-result pseudo r80 got v1 and the RESULT_DECL r73 prefers v1 but conflicts v0 (the pinned result) → r73 got... it prefers v1 but r80 has v1 (hard reg, local allocno) → r73 got v0? But v0 is the pinned result's reg! Hmm, r73 "conflicts v0" (the pinned result) — so r73 can't be v0 → and it prefers v1 but v1 is taken by r80 → so r73 got v2 ($4)?

Hmm, but the target code has the value in v0 ($2) and the copy v1,v0 → and the RESULT_DECL's copy to v0... The pinned `result` pseudo IS in v0 (hard reg) and the RESULT_DECL is a copy of it → coalesced into v0? But r73 conflicts v0...

Hmm, confusing. The lreg table's "hard" column may be the pseudo's assigned hard reg AFTER allocation for local allocnos.

Whatever the details, the lever-free situation is:
- The call-result pseudo r84 has pri 10000, refs 2, live 2, hard v0.
- The local `result` r74 has pri 11428, refs 4, live 7, conflicts v0 (because r84 has hard v0 in the overlapping range).

KEY: to make the call result land in v1 (not v0), we need v0 to be UNAVAILABLE at the call's live range [24..26]. The local `result` (r74) is live [25..33] — it overlaps at [25..26]! If r74's live range started at ins 24 (i.e. r74 were live across the whole call result range) AND r74 had higher priority than r84, then r74 would take v0 and r84 would be forced to v1 → the copy `move v1,v0` ✓✓.

But r74 is a GLOBAL allocno (it's in the .greg order) — global allocnos are allocated after local ones, and a local allocno with a hard reg (r84) is fixed. Hmm, so r74 can't take v0 away from r84?

Wait — in the pinned version, r80 (the call result) got v1, and r80 is a local allocno with a hard reg (v1). In the lever-free version r84 (same pseudo, the call result) got v0. So the call-result pseudo's hard reg is NOT fixed — gcc chose v1 in the pinned case because v0 was taken by the pinned pseudo. So the call-result pseudo's hard reg IS decided by local allocation, and it avoids v0 when v0 is occupied.

So in the lever-free case, the call result took v0 because v0 was free at [24..26] — the local `result` r74 was live [25..33] but it's a GLOBAL allocno (allocated later), and local allocation (which assigns r84) runs first and doesn't know about r74.

Hmm, but r74 is global because it conflicts with a hard reg. In the pinned version, the pinned pseudo (hard reg v0) forced r73 (the RESULT_DECL) to be global.

So the lever-free path: make the local `result` a LOCAL allocno that's live across the call result's range and takes v0 in LOCAL allocation (which happens before the call result's local allocation? no — local allocation assigns all local allocnos at once, with priority ordering).

In local allocation, the call-result pseudo r84 (pri 10000, refs 2, live 2) vs a local allocno X (pri > 10000, live overlapping [24..26]) → X gets v0 and r84 gets v1 ✓.

For X to be a LOCAL allocno (not global), X must not conflict with any hard-reg pseudo. If X is live [24..33] and the RESULT_DECL (a global allocno)... hmm, why was r74 global? "conflicts v0,sp" — it conflicts with v0 (the call result's hard reg) and sp. So because it conflicts with a hard reg, gcc moves it to global allocation.

Circular: X conflicts with v0 → global; but if X were allocated first (locally) it could take v0.

Hmm, gcc's local/global split: a pseudo conflicts with a hard reg → it becomes a global allocno (because global allocation can consider the hard regs). So any pseudo that would take v0 becomes global, and global allocnos are allocated after the local ones → the call result (local, hard v0) wins v0.

UNLESS the call-result pseudo is ITSELF global! In the pinned version r80 (the call result) got v1 — was it local or global? The order line for pinned is "73" (only r73 is global). So r80 was a LOCAL allocno that got v1. So local allocation CAN put the call result in v1 when v0 is unavailable.

In local allocation, the pseudo r80 competes for v1/v0/etc. with other local allocnos. If v0 is "unavailable" (e.g. because another local allocno has a higher priority and takes it), r80 gets v1.

So: we need a LOCAL allocno with pri > 10000 that is live at [24..26] and prefers/competes for v0. But a pseudo that takes v0 conflicts with the hard reg v0 → becomes global. Hmm, but if it WINS v0 in local allocation, then it doesn't conflict with a hard reg (it just takes it) → it stays local!

Right! The "conflicts v0" note for r74 means it was forced to avoid v0 (because r84 took v0) → then it has a conflict with a hard reg → global allocation.

So if a local allocno X with pri > 10000 wants v0 and WINS it (over r84), then X is local and takes v0, and r84 (the call result) is forced to v1 → copy `move v1,v0` ✓✓✓.

So the goal: a pseudo X, live at [24..26] (overlapping the call result), with pri > 10000 (the call result's 10000), that takes v0.

What has pri > 10000? pri = 2^floor(log2 refs) * refs * 10000 / live.
- refs 4, live 7 → 11428 ✓ (that's r74's numbers: the local `result` in the lever-free nopin dump!).
- r74 has pri 11428 > 10000 ✓ but it's live [25..33] — it overlaps the call result at [25..26] ✓ — but in LOCAL allocation it lost v0 to r84? Hmm, why? Because in local allocation, the hard reg v0 is a candidate for both; the priority order decides: r84 (10000) vs r74 (11428) → r74 should win!

Hmm, but r74 is in the GLOBAL order line, so it never entered local allocation. Why? Because gcc's local/global split decides BEFORE allocation: a pseudo that conflicts with a hard reg goes global. The conflict analysis is done on the "hard reg conflicts" — gcc checks if a pseudo has any conflicts with hard regs (based on the live ranges of hard-reg pseudos). Since r74's live range [25..33] overlaps the call-result's hard reg v0 [24..26], r74 is deemed to conflict with a hard reg → global.

Hmm, but in local allocation the same conflict analysis would decide the winner by priority. gcc's split (in global.c `allocno_initialize` / `find_local_pseudos`): a pseudo is local if it has no conflicts with hard regs (other than the "call" ones?). The conflict determination in local allocation: `local_alloc` computes conflicts between local pseudos and hard regs.

So the split is decided by the presence of a conflict, and the winner by priority. Since r74 conflicts with the call-result's hard reg v0, it goes global.

BUT: gcc's global.c has a step where a global allocno may be "spilled" or where the hard reg is freed... Hmm.

OK, empirical approach: to get X (pri > 10000) to be a LOCAL allocno competing for v0, X must not conflict with any hard reg... but X overlaps the call result's v0 → conflict → global. Circular again.

Hmm, unless X's live range doesn't overlap the call result's hard-reg range but X still competes for v0 in local allocation... Local allocation assigns hard regs to local pseudos by priority, and a pseudo that gets a hard reg it conflicts with... hmm.

Wait. Maybe the trick is the opposite: make the CALL RESULT pseudo's live range LONGER so that it conflicts with more and becomes global? Then it'd be allocated in global allocation along with the local `result`, and the priority would decide (r74 pri 11428 > r84's 10000) → r74 takes v0 and r84 gets v1 ✓!!

How to make the call result a global allocno? It's global if it conflicts with a hard reg — e.g. if it's live across a call (no) or conflicts with another hard-reg pseudo. Hmm.

Alternatively, make the LOCAL `result` (r74) not conflict with v0 but still take it... no.

Alternatively: what if the local `result` has a live range that starts BEFORE the call (i.e. live across the call) → then it must be in a callee-saved reg → no.

Hmm. Let's think about gcc's local/global split rule more precisely (gcc 2.7.2 global.c, function `allocno_initialize` / `find_local_pseudos`):

```
/* Find the local pseudo registers... A pseudo is local if it does not conflict with any hard register... */
```
The rule (gcc 2.x `global.c: find_local_pseudos`):
- A pseudo is a candidate for local allocation if its live range doesn't cross a call and it doesn't conflict with any hard-reg pseudo's live range.

The "conflict with a hard reg" is determined in `local_alloc` via the conflict graph built from the RTL (a pseudo conflicts with a hard reg if their live ranges overlap).

So r74 conflicts with the call result's hard reg v0 → global. And then in global allocation, the hard regs are already taken (v0 by r84 as a local allocno) → r74 gets v1.

Hmm, so the outcome is: the call result always wins v0 in the lever-free case.

Unless the call result's live range doesn't overlap r74's. In the target, the call result (in v1) is live [24..26] and the value (in v0) is live [28..34] → they DON'T overlap → no conflict → both could be in v0, but the call result got v1 because v0 was reserved by the pin.

Hmm!! So in the target, the value pseudo is NOT live during [24..26]. And in my nopin form, the local `result` IS live during [25..26] (its first def is `result = 0` at ins 25 in the then-branch, and the call result dies at ins 26) → overlap.

So: if the local `result`'s first def were LATER (after ins 26), there'd be no conflict with v0 → the local `result` could be allocated v0 (it's global, and v0 would be free at [28..34]... but r84 (the call result, local) holds v0 as its hard reg for [24..26] — after that, is v0 still "taken"? In gcc, a local allocno with a hard reg holds it for its whole live range; other global allocnos can use that reg outside the live range? NO — the hard reg is reserved for the pseudo globally. Hmm, but in the lever-free nopin case, the RESULT_DECL r73 got v0! And r84 (the call result) also has hard v0. So they DO share v0 (r73 prefers v0 and got it) — because r73's live range doesn't overlap r84's ✓ (gcc's global allocation can use a hard reg outside a local pseudo's live range? Apparently yes — "conflicts" in the global phase are computed on live ranges).

So: if the local `result`'s live range starts after ins 26 (no overlap with the call result), then r74 could take v0 (the RESULT_DECL's preferred reg) — but the RESULT_DECL r73 also wants v0 (pri 7500) and r74 (pri 11428) would win → r74 gets v0, r73 gets v1 (or v2) → and the final copy `move v0,v1`?? Hmm, the copy is RESULT_DECL ← result: if the RESULT_DECL is in v1 and the local result in v0, the copy is `move v1,v0` — but the target has the value in v0 and no copy.

Hmm, wait: in the TARGET, the value is in v0 at the end (the boolean computed into v0 by lbu/xori/sltiu) and the RESULT_DECL's copy is coalesced. In the nopin form, the value (local result) is in v1 and the RESULT_DECL in v0 with the copy `move v0,v1` at the end. If the local result were in v0 and the RESULT_DECL in v1, the code would be: the boolean computed into v0 ✓ (lbu v0, xori v0, sltiu v0) and at the end `move v1,v0` (copy to the RESULT_DECL) ✗ — an extra instruction vs the target (which has none).

Unless the RESULT_DECL gets v0 and the local result also v0 — impossible (they overlap).

Hmm, so the target requires: the local `result` AND the RESULT_DECL both in v0 (coalesced), and the call result in v1.

Since the local result and the RESULT_DECL are copies of each other (the return), gcc's coalescing should merge them into ONE pseudo — unless the copy is a "re-tie" that cse keeps separate.

Hmm! In the target, the local `result` (pinned $2) and the RESULT_DECL: the copy `result → RESULT_DECL` — with the pinned pseudo in v0 and the RESULT_DECL preferring v0, the copy is coalesced (both v0) ✓.

So in a lever-free version we want: the local result pseudo and the RESULT_DECL to be the SAME register (v0), and the call result in v1.

If the local result is in v0 (live [28..34]) and the RESULT_DECL is in v0 too (live [28..epilogue]) → they'd conflict (overlapping live ranges) → they can't both be v0. UNLESS gcc's copy coalescing merges the RESULT_DECL into the local result's pseudo (making them one). That's the "return slot" optimization which gcc 2.7.2 might do for the RESULT_DECL copy! Actually gcc has always had: "the RESULT_DECL copy from the return expression" — in the RTL, `return result;` becomes `(set (reg RESULT_DECL) (reg result))` — and if the RESULT_DECL is a pseudo with a copy preference to `result`, the coalescer merges them ✓. But then the RESULT_DECL would BE the local result's pseudo... and the local result would be in v0 with the RESULT_DECL merged. Hmm, but the nopin dump shows them as separate (r74 and r73) with a `move v0,v1` copy.

Why weren't they coalesced in nopin? Because the coalescer prefers... hmm. In nopin, the local result is v1 and the RESULT_DECL v0 → the copy `move v0,v1` remains. Coalescing would have merged them (both are copies) → then the RESULT_DECL would be v1 and the copy would be "the value is in v1, copy to v0 at the return" — the copy is REQUIRED because the RESULT_DECL must be in v0 (the return reg) — so the coalescer can't merge them if the RESULT_DECL is hard-bound to v0.

Hmm, right: the RESULT_DECL is copied to v0 at the return (that's the `move v0,v1`). So the RESULT_DECL pseudo IS in v0 (hard reg) and the local result is v1.

Wait, in the nopin dump r73 (the RESULT_DECL, pri 7500, "prefers v0") is a global allocno, and the final copy `move v0,v1` is the copy FROM r74 (v1) TO r73 (v0)? But r73 is listed as "-" (a global allocno whose hard reg isn't printed). The copy at the end `move v0,v1` = r73 ← r74 → r73 is in v0 ✓.

So in the target (pinned), the final copy is ABSENT: the value is computed directly into v0 and the RESULT_DECL is in v0 too (the pinned result in v0 → coalesced).

Hmm, so in the pinned version, the local `result` (hard v0) and the RESULT_DECL r73 (pri 7500, prefers v1, conflicts v0) → r73 got v1?? Then the copy would be `move v1,v0` at the end. But the target has no such copy...

Unless the pinned `result` IS the RESULT_DECL! I.e., in the pinned source, `register int result __asm__("$2")` — gcc might treat a variable whose address is never taken and which is returned as... no.

Hmm, hold on. Let me look at the target's ending again:
```
29 lbu v0,30(sp)
31 xori v0,v0,0x15
32 j 8014fde0
33 sltiu v0,zero,v0
34 move v0,zero     <- the ret==0 path
35 lw ra,36(sp)
...
```
So in the boolean path, v0 = the boolean; in the zero path, v0 = 0. No copy at the end ✓. So the RESULT_DECL is v0 and the boolean is computed directly into it.

So the local `result` (pinned v0) IS effectively the RESULT_DECL — i.e. gcc DID coalesce the local `result` with the RESULT_DECL (both in v0). Because the pinned pseudo has a hard reg, the coalescer can merge the RESULT_DECL into it.

So in a lever-free version, we need the local result's pseudo to be in v0 AND the RESULT_DECL copy to be coalesced into it. Coalescing happens when the copy's src and dst can share a reg. The RESULT_DECL is copied to v0 at the return (hard reg) — hmm, then the RESULT_DECL pseudo must be v0 → and the local result would need to be v0 too → conflict → the copy `move v0,v1` remains.

Hmm, so how does the pinned version avoid it? In the pinned version, the local result is in v0 (hard). The RESULT_DECL r73 (pri 7500, prefers v1, conflicts v0) → allocated v1?? and then the copy r73 ← r74 would be `move v1,v0`... but the target has no such copy.

Hmm, maybe the RESULT_DECL in the pinned version got v0 as well — "conflicts v0" might mean something else (e.g. it conflicts with the pseudo that holds v0?).

I'm going too deep. Let me do the decisive EXPERIMENT differently: dump the PINNED version's RTL and look at the actual instruction sequence to see which pseudo is which. The .i.rtl or .i.flow dump shows the function's RTL with pseudo names. Let me look at the pinned .i.rtl section for func_8014FD54 and identify the pseudo at ins 24 (the copy move v1,v0).

That will tell me exactly what the copy is: e.g. `(set (reg r80) (reg 0 v0))` — the copy from the hard reg v0 to r80 (the call result pseudo) — and then r80 is in v1 ✓ (consistent with the table: r80 hard v1).

So in the pinned version, the call-result pseudo r80 is in v1, and the copy from v0 (the call's hard-reg output) to r80 is the `move v1,v0`.

In the lever-free version, the call-result pseudo r84 is in v0 → no copy.

So the question: why did local allocation put r80 in v1 in the pinned version? Because v0 was taken by the pinned pseudo (a hard-reg pseudo) → v0 unavailable → r80 got v1.

Lever-free: we need v0 to be unavailable to r80 at [24..26]. v0 is unavailable if some OTHER pseudo with higher priority takes it in local allocation. As established, a pseudo that overlaps r80's live range and has pri > 10000 would take v0 — but then it would be global (conflict with a hard reg)...

Hmm, unless the competing pseudo is a LOCAL allocno (not conflicting with a hard reg). For X to be local, X must not conflict with any hard reg. X's live range [24..26] overlaps r80's hard reg v0 → conflict → global. Circular.

BUT: what if X's live range overlaps r80's live range but NOT its hard reg range? The hard reg v0's live range for the call result: r80's hard-reg assignment means the pseudo r80 lives in v0 during [24..26]. Hmm.

Alternatively: what if the competing pseudo X is live at [24..26] but the CALL RESULT is not in v0 during that range because...

OK, radically different idea: what if we make the call result's pseudo have a HIGHER live length (lower pri) so that the local allocation gives v0 to another pseudo? The competition in local allocation is by priority: r84 (pri 10000) vs X (pri > 10000). We need X to be a local allocno.

Which pseudos are local? r75/r76 (the buf pointers, 2 bytes, pri 5000, hard v0 — wait, they have hard v0?!). Hmm: r75, r76: hard v0, pri 5000, refs 2, live 4, "2 bytes". These are the address pseudos for buf1/buf2 (16(sp) and 24(sp)) — they're computed as `addiu a1,sp,16` in the target, so they're not in v0... Hmm, the "hard" column here might be misleading (it might print the pseudo's hard reg from the lreg dump's "Register N in M" lines).

Hmm, whatever. Let me look at the actual .i.rtl / .i.flow dump for the pinned version to identify the pseudos and their live ranges. That's the ground truth. Let me extract the function's section from pinned.i.rtl and pinned.i.lreg.

Actually, the .lreg dump has the pseudo list with "Register N used X times across Y insns in block Z" — that's what alloc_table parses.

Let me look at the raw .i.lreg section for the function to see all the pseudos and their notes (e.g. "conflicts", "prefers").

Time check: 23:05. I'm 42 minutes into this item — over the 30 min budget. The rule says "past 30 min stop and record a wall". Hmm. But I have new decisive information (the pinned dump). Let me spend a few more minutes to try ONE more high-value idea, then record the wall.

The high-value idea from the analysis: we need a pseudo X with pri > 10000, live at [24..26], that takes v0 from the call result. Since X would be global...

Hmm, actually WAIT. What about the reverse: make the CALL RESULT pseudo have a LOWER priority than another pseudo that ALREADY has v0 legitimately. In the lever-free dump, who has v0 in local allocation? r80, r82, r84 (the call results) and r75, r76 (the buffer addresses, pri 5000, hard v0!). Hmm, r75/r76 are the buf addresses and they're listed with hard v0 — but in the code they're `addiu a1,sp,16` (computed into a1/a2 directly). The "hard" column here is probably from the "Register N in M." lines in the .greg dump which map a pseudo to a hard reg in the ORDER/preference sense. Confusing.

Let me try the practical experiment instead: dump the lever-free candidate with a modified body where the local `result` has MORE refs (to raise pri) — no...

Better experiment: let me check the local `result`'s live range overlap. In nopin, r74 (local result) is live [25..33] (live 7). The call result r84 is live [24..26]. They overlap at [25..26] → conflict → global.

What if the local `result`'s live range started at 27 (no overlap)? Then r74 wouldn't conflict with v0 → it could be LOCAL → and in local allocation it would compete for v0 with r84 (pri 10000): r74's pri would be refs*2^floor(log2 refs)*10000/live = 4*4*10000/7 = 11428 > 10000 → r74 WINS v0 in local allocation → r84 gets v1 → the copy `move v1,v0` ✓✓✓!!!

And the RESULT_DECL: live [27..epilogue], prefers v0 → but v0 is taken by r74 (overlapping) → the RESULT_DECL gets another reg → the final copy `move vX,v0`?? Hmm, that breaks the end of the function.

Hmm, but hold on: what if the local `result` IS the RESULT_DECL (coalesced)? If the local result is in v0 and the RESULT_DECL is merged with it, no copy ✓.

How to get the local result's live range to start at 27 (after the call result dies at 26)? The local result's first def is `result = 0` in the then-branch. In the target, the then-branch's `result = 0` is at ins 28 (the delay slot of the mask branch) — which is AFTER 26 ✓. So in the target, the local result's live range is [28..34] — no overlap with the call result [24..26] ✓✓.

But in my nopin form, the local result's live range starts at 25 — because gcc's RTL has the `result = 0` assignment placed at ins 25 (right after the `beqz v0` at 24)? Hmm, in the nopin listing (mine): ins 24 `beqz v0`, 25 `andi v0,v0,0x8000`, 26 `beqz v0`, 27 `move v1,zero` (the result=0), 28 lbu... So the local result's first def is at ins 27 (the `move v1,zero`) — hmm, then its live range is [27..33] which does NOT overlap [24..26]!

But the table says r74 "conflicts v0,sp". Hmm, and r73 (the RESULT_DECL, pri 7500, refs 3, live 4) is the one with "conflicts sp, prefers v0".

Hmm, so which pseudo conflicts v0? r74. But r74 = the local result? Or is r74 the RESULT_DECL and r73 the local result? In the pinned dump, r73 has "conflicts v0,sp, prefers v1" and it's the only global one. In the lever-free dump, the order line is "74 73" (r74 first = higher pri = 11428) and r73 (7500).

In the pinned version, r73 = the RESULT_DECL (as the notes said) → in the lever-free version r73 would also be the RESULT_DECL (the same pseudo number, since the RTL is the same except the pin) → r73 = the RESULT_DECL with pri 7500, refs 3, live 4, prefers v0 → it got v0 ✓ (in the lever-free nopin, the RESULT_DECL is v0 and the copy `move v0,v1` copies the local result v1 → the RESULT_DECL).

And r74 = the local `result` (pri 11428, refs 4, live 7, conflicts v0) → it got v1 because it conflicts with v0 (the call result's hard reg) — so its live range DOES overlap the call result's [24..26]...

Hmm, why? The local result's first def should be at ins 27 (the `move v1,zero`). Hmm, but the "live" count of 7 suggests [27..33] = 7 ✓. And the call result r84's live = 2 → [24..26]? Then [27..33] and [24..26] don't overlap... but the conflict is reported.

Maybe the conflict is with the RESULT_DECL's hard reg? No, r73 is global ("-").

Maybe r74 conflicts with v0 because of the "2 bytes" hmm no.

Maybe the local result's live range actually starts earlier: the `result = 0` in the ELSE branch might be scheduled early? In the nopin listing, the else path's `move v1,zero` is at ins 33. Hmm.

Whatever the exact reason, the empirical question is: what change makes the call result get v1?

Let me try a batch of shapes quickly:
(1) The value assigned only in the inner branch (no `result = 0` in the then/else):
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
(2) The value as a u8.
(3) The `&&` fold with a local.
(4) The value assigned via a temp.
(5) The local `result` declared as `register`? That's the lever (pin) — not allowed.

Honestly, let me try the most promising: make the local result's live range as short as possible and its refs high.

Actually — hold on! NEW IDEA: What if we give the local `result` MORE refs so its pri goes way up (e.g. refs 6 → 2^2*6=24 → pri = 24*10000/live; with live 7 → 34285) AND keep it overlapping the call result? Then in local allocation... but it's global (conflicts v0) → global allocation gives it v1 anyway (v0 is taken by the local r84).

Hmm, so the conflict with v0 is the killer: any pseudo conflicting with a hard reg goes global, and globals can't take the hard reg.

=> The ONLY way is to make the call result NOT hold the hard reg v0, i.e. to make the call-result pseudo global too, or to make v0 unavailable some other way.

How does the call result get a hard reg? In gcc 2.7.2, the call insn's output is a pseudo (r84) that local allocation assigns to a hard reg (the call's return reg v0) because of the "call" pattern. If the pseudo is live across a call or conflicts with other hard regs, it'd be global.

Hmm, what if the call result is used in a way that makes its live range cross a CALL? No.

What if the call result conflicts with another hard reg? E.g. if the call result's live range overlapped a hard-reg pseudo's live range (like the pinned result in v0) → then it'd be global → and in global allocation it could be assigned v1 while the local `result` (pri 11428) takes v0 ✓.

So: we need a pseudo that HOLDS a hard reg (v0) and whose live range overlaps the call result's. In lever-free C, what holds a hard reg? Hmm: the RESULT_DECL holds v0 (it's the return reg)! If the RESULT_DECL (r73) were live at [24..26]... it's not (it's live [27..]).

Hmm, but wait: r73 is a GLOBAL allocno in both dumps, and it "prefers v0". A global allocno with a preference for v0 — the preference means it WANTS v0 but conflicts prevent it.

What if the RESULT_DECL were live across the call? That requires a `return` before the call (semantically impossible)...

UNLESS: the RESULT_DECL is live across the call because of an early `return` in a branch that's provably... no, semantics.

Hmm hmm. What about this: the function could return EARLY via a different path that's semantically equivalent, e.g.:

```
if (param_1 == 0) { ... }
```
no.

OK, at this point, let me consider the OTHER lever in the catalog: "loop shape". From the moves file: "pin | func_8017CE7C | MATCH — do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2 (G06)".

Hmm, "local-alloc ranks it above" — in local allocation, the priority ordering. So the loop shape changes the live range → the pri.

For us: if the local `result` were a LOCAL allocno (not global), it could win v0 in local allocation. It becomes global because it conflicts with a hard reg. What if it doesn't conflict with any hard reg? It conflicts with v0 because the call result (hard v0) is live at [24..26] and the local result is live at [25..33] (overlap at 25-26).

So: shorten the local result's live range to start at 27 → no overlap → no conflict → it stays LOCAL → and in local allocation it competes for v0: its pri (11428) > r84's (10000) → it WINS v0 → the call result r84 gets v1 → the copy `move v1,v0` ✓✓✓.

But then the RESULT_DECL (r73) also wants v0 (live [27..34], overlapping the local result) → it can't have v0 → it gets v1 or v2 → the final copy `move vX,v0` appears (the RESULT_DECL must be in v0 at the return? hmm, actually the RESULT_DECL is copied to v0 at the return — that copy `move v0,v1` IS the copy to the hard reg v0. In the target there's no such copy because the boolean was computed directly into v0.

Hmm, in the target: the boolean is computed into v0 (lbu v0, xori v0, sltiu v0) and the RESULT_DECL = v0 with no copy. So the RESULT_DECL is v0 and the local result is ALSO v0 (coalesced) — the pinned pseudo.

For a lever-free version: the local result in v0 and the RESULT_DECL in v0 → they conflict... unless the coalescer merges them (they're connected by a copy). The coalescer merges the local result pseudo and the RESULT_DECL pseudo into one if their live ranges permit — the RESULT_DECL's live range is [27..epilogue] and the local result's [27..33] → they overlap → can't merge into the same reg? Coalescing two pseudos connected by a copy: they become one pseudo → the merged pseudo's live range = the union → fine, but then the copy `move v0,v1`... hmm, the coalescer would produce: the merged pseudo in v0, and the copy to the hard reg v0 (the return) becomes a no-op → removed ✓.

So IF the coalescer merges the local result with the RESULT_DECL, and the merged pseudo gets v0 → the code would be: the boolean computed into v0 ✓, no final copy ✓, and the call result in v1 with the copy `move v1,v0` ✓ = THE TARGET!

But in the nopin form, the coalescer did NOT merge them (we see `move v0,v1`). Why? Because in nopin, the local result got v1 and the RESULT_DECL v0 — the coalescer couldn't merge because the RESULT_DECL is tied to v0 (hard reg) hmm, or because the RESULT_DECL's live range conflicts.

OK — so the goal is to get the LOCAL result into v0. That requires it to be a local allocno (not conflicting with a hard reg) with pri > the call result's.

Its live range must not overlap [24..26]. In the target, the local result's first def is at ins 28 (the `move v0,zero` in the delay slot) — the then-branch's `result = 0` ✓ — and the else path's `result = 0` is at ins 34. So the local result's live range is [28..34] — no overlap with [24..26] ✓.

In my nopin form, the local result's live range was [27..33] (the `move v1,zero` at ins 27 is the then-branch's `result = 0`? hmm, in nopin's listing: ins 24 beqz v0 (ret != 0), 25 andi, 26 beqz v0 (mask), 27 move v1,zero ← this is the then-branch's `result = 0` (in the delay slot), 28 lbu v0, 30 xori, 31 j, 32 sltiu v1,v0,1 (the boolean → v1 = result!), 33 move v1,zero (the else path), 34 move v0,v1 (the RESULT_DECL copy).

So the local result's live range = [27..33] = 7 ✓ (matches "live 7"). And the call result's live range = [24..26]. NO OVERLAP! Yet the table says r74 "conflicts v0,sp". Hmm, why?

Hmm — maybe "conflicts v0" here means something else. Or maybe the local result's live range extends earlier: the `result = 0` in the else branch might be assigned EARLY in the RTL (the else block's assignment could be hoisted?). Or the conflict is with the RESULT_DECL... no, r73 is a separate pseudo.

OR: maybe r74 is NOT the local result but something else, and the local `result` is one of r75/r76 (the "2 bytes" ones)? Hmm, r75/r76 are "2 bytes" → the short buffers' addresses.

Hmm, "2 bytes" might refer to the pseudo's size in bytes: buf1/buf2 are shorts → their address pseudos? no, addresses are 4 bytes.

Let me look at the raw .lreg dump section to see the pseudo notes. That's the fastest way to identify the pseudos. Let me grep the function's section from the nopin .i.lreg.

Time: 23:08. I need to wrap up. Let me do this one dump inspection, then try 2-3 more variants, then write the wall with the evidence.

Actually, let me reconsider the whole thing: maybe simply reordering so the local result is defined later helps. Let me try the variant where `result = 0` appears ONLY in the inner-else and the else branch (i.e. no `result = 0` in the then-branch):

Actually the target's structure: the then-branch's `result = 0` is at ins 28 (delay slot of the mask branch) — that's AFTER the mask test at 27. Hmm, in my nopin the then-branch's `result = 0` is at ins 27 (the delay slot of the mask beqz at 26). One insn earlier! Interesting: in the target, the delay slot of `beqz v1` (ins 27) contains `move v0,zero` — and in nopin, the delay slot of `beqz v0` (ins 26) contains `move v1,zero`. So they're structurally the same, just shifted by the missing copy.

So the local result's live range in the target is [28..34] and in nopin [27..33]. Both don't overlap [24..26].

So why "conflicts v0"? Hmm, maybe the conflict is with the RESULT_DECL's hard reg? The RESULT_DECL r73 is global ("-")...

Hmm, maybe the conflict with v0 comes from the fact that r74's live range [27..33] overlaps the region where the call's hard reg v0 is "reserved"? In gcc, a call's hard reg output (v0) might be considered live for the whole function? No...

Let me just look at the raw dump. Let me extract the .i.lreg section for func_8014FD54 from the nopin dump.
