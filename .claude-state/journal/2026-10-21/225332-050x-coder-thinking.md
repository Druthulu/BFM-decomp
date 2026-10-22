---
ts: 2026-10-22T04:53:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_f7duRqOqzhCuEjKxPWUA
---
Now z3's machine code:
```
24 beqz v0        <- the outer test on the call result (v0)
25 andi v1,v0,0x8000   <- the mask computed into v1 (a different reg!)
26 (the branch on v1 is at 26?)
```
So now the AND's temp is in v1 and the call result in v0 — the opposite of the target (the target has the call result copy in v1 and the AND in v1 too: `move v1,v0; beqz v1; andi v1,v1,0x8000`).

Interesting! So now the AND temp (v1) and the call result (v0) are in different regs — but the roles are swapped relative to the target. The target: the call result copy is in v1 (with the copy `move v1,v0`) and the AND is in-place in v1.

So in z3, the AND temp got v1 (a separate reg) — because now the AND temp's live range overlaps the call-result copy's? Hmm, no: mine[25] `andi v1,v0,0x8000` computes the AND into v1 from v0 — so the call result is in v0 and the AND result in v1, and the branch at 26 tests v1.

The target: `move v1,v0` (the call result copied to v1), `beqz v1`, `andi v1,v1,0x8000` (the AND in-place in v1).

So the difference: in the target, the call result is COPIED to v1 and the AND is in-place in v1; in z3, the call result stays in v0 and the AND goes to v1.

So both have the call result and the AND in different regs, but the target copies the call result to v1 while z3 keeps it in v0 and puts the AND in v1.

Score 4 now (vs 6). The remaining diff: the missing `move v1,v0` and the branch offsets.

Hmm! Now, what if the AND temp's live range could be pushed to overlap the call result copy... Let's think: in z3, the AND temp (v1) is live [after the andi..the branch] and the call result (v0) is live [..the andi]. They're adjacent → the scheduler chose to put the AND in a different reg rather than in-place.

Hmm, in the target the AND is in-place in v1 (the call result's copy reg).

So the target's structure: the call result is copied to v1 FIRST (the copy is a separate insn), and then the AND is in-place in v1.

In z3, the copy `(set r73 v0)` was coalesced (r73 = v0), and the AND needed a different reg (v1) because... hmm, why couldn't the AND be in-place in v0 (r73's reg)? Because the AND's live range overlaps r73's? The AND is defined at the point where r73 dies → no overlap → it could be in v0. But gcc's local allocation gave the AND temp v1 (maybe because the andi pattern requires... hmm, on mips, `andi` can use any reg; but gcc's reload phase might prefer a different reg).

Hmm, wait. In z3, the AND is at machine insn 25, in the delay slot of the branch at 24? Let me get the full machine listing of z3 to understand the shape.

Let me disassemble z3's candidate. Actually, let me use --keep and objdump.

Alternatively, think: what I want is the call result COPY to survive (r73 ≠ v0) and the AND in-place in r73's reg.

In z3 the AND went to a different reg (v1) — so r73 and the AND temp conflict → the AND temp has a higher priority (pri 10000 vs r73's 7500) → the AND took v0?? no, the AND took v1 and r73 took v0.

Hmm, so r73 (the call-result copy) won v0 (its preference) and the AND temp got v1. To flip: the AND temp should take v0 (higher pri) and r73 should take v1 → then the copy `move v1,v0` survives ✓ and the AND would be in-place in... hmm, the AND's operand is r73 (in v1) and its result in v0 → `andi v0,v1,0x8000` — but the target has `andi v1,v1,0x8000` (in-place in v1) ✗.

Hmm. So we want: r73 in v1, the AND temp coalesced with r73 (in-place) → the AND temp must be in v1 too. But the AND temp has a higher priority → it takes v0 first → then r73 takes v1 → the AND would be `andi v0,v1,0x8000` (not in-place).

Unless the AND's result IS r73 (i.e. the AND is done in place into the same pseudo) — that's what happens when the AND's temp is coalesced with r73 (the copy chain: v0 → r73 → and-result). The coalescer merges r73 with the AND's result pseudo if their live ranges allow (r73 dies at the AND) ✓ — that's the normal case.

In z3, they were NOT coalesced: `andi v1,v0,0x8000` — the AND's result is a different reg than r73's. Why not coalesced? Because the AND's result must live PAST r73's death?? Hmm, r73 dies at the AND (it's the operand) → the AND's result is defined after → coalescible.

Unless in z3 the source's `mask` variable is used in a way that its live range starts earlier. Hmm, in z3 the mask is computed BEFORE the outer test (`mask = ret & 0x8000;` then `if (ret != 0)`) → so in the RTL: the AND is defined BEFORE the outer branch, and r73 (the call-result copy) is live across the AND (the AND uses r73!) → so the AND's result and r73 overlap → they CAN'T be coalesced (both live at the branch) → the AND needs a separate reg ✓ (that's z3's shape).

So z3's shape is forced by the source order. To get the target's shape (the AND in-place in the copy's reg), the AND must come AFTER the outer branch in the RTL — i.e. the original source order (mask computed inside the branch) — but then the AND's temp and r73 are adjacent → chainable → the AND is in-place in r73's reg ✓ (that's the y1/nopin shape: `andi v0,v0,0x8000` in-place ✓).

So:
- Original order (AND inside the branch): the AND is in-place in the call result's reg (v0) → `andi v0,v0,0x8000` ✓ shape matches the target's `andi v1,v1,0x8000`, but the reg is v0 (the target has the call result copy in v1).
- z3 order (AND before the branch): the AND goes to a separate reg → `andi v1,v0,0x8000` ✗ shape (the target has the in-place form) but the call result stays in v0.

Hmm. So neither matches. We need the call-result copy in v1 AND the AND in-place in v1.

For the AND to be in-place in the call-result copy's reg, the AND's result must be coalesced with r73 → the AND must be defined after r73 dies → the AND inside the branch (original order) → and then r73 and the AND chain share a reg → whichever reg they get, both are the same.

So we need the chain (r73 → AND temp) to be in v1 rather than v0. The chain takes v0 because r73 prefers v0 (its copy preference from the call's output).

To deny v0 to the chain: another pseudo must take v0 with a higher priority, live in the same window. Candidates: the local result r74 (pri 11428 in nopin) — but in nopin r74 lost v0 due to a conflict with the temps.

Hmm! But now, with the z3-style structure... let me think about the nopin structure with the mask inside the branch (y1) — there, the chain (r73+AND) is in v0 and r74 (the local result) is also v0 (sequential).

What if we could make the local result's live range OVERLAP the chain's? Then they'd conflict, and the local result (pri 11428) would take v0 (higher pri) and the chain would go to v1 ✓✓✓ — and then the AND would be in-place in v1 ✓ = the target!

The local result's live range [72..97] vs the chain's [65..76]: they overlap at [72..76] ✓ ALREADY (in the nopin structure)! Hmm, in nopin r74 (live [72..97]) and the chain (r73 [65..74], r80 [74..76]) overlap → so they DO conflict → r74 should have taken v0 (higher pri 11428 > 10000) and the chain v1.

But the observed nopin result: the chain in v0, r74 in v1. Hmm! So the priority did NOT decide; the preference did (r73 prefers v0).

Hmm, but in gcc's global allocation, the order line "74 73" means r74 is allocated FIRST. When r74 was allocated, v0 must have been unavailable → because the local allocnos (the temps) hold v0? In nopin, the temps are r80 (AND), r82 (load), r84 (xor) — all with hard v0 (per the table). So during r74's live range, v0 is occupied by the temps → r74 can't take v0 → r74 gets v1 ✓✓.

So the blocker is the TEMPS holding v0 (local allocation gave them v0). The temps: the AND temp (pri 10000), the load temp (pri 10000), the xor temp (pri 10000). They got v0 in local allocation.

In the PINNED version, the temps got v0 too (r83, r85) but the AND temp got v1 (r80). Hmm, because in the pinned version v0 was reserved for the pinned pseudo... and then the load/xor temps STILL got v0?! That's contradictory: if v0 is reserved for the pinned pseudo, the temps couldn't have v0.

Unless the pinned pseudo's hard reg is only "reserved" in the sense that the copy into it is a hard reg... In gcc, a hard-reg pseudo (a variable with a fixed register) is allocated that reg in local allocation; other pseudos CAN use the same reg if their live ranges don't overlap. The pinned pseudo's live range is [72..97] (from the `result = 0` def to the last use). The load/xor temps are live within [81..85] → they OVERLAP the pinned pseudo's range → so they should conflict!

But the target's machine code has the load/xor in v0 (the pinned reg) ✓ — because the pinned pseudo's value is dead after its def in that path? Hmm, the pinned `result` is live from 72 to 97 (the final use). The load temp r83 [81..83] overlaps...

Hmm, in the pinned version the load/xor temps are in v0 and the pinned pseudo is in v0 — but they're chained: the pinned result's value is dead in the branch where the load/xor happen (the value is redefined there). GCC's live ranges are per-path; the "live across" analysis handles this (the pinned pseudo's live range at the merge point). So in the branch, the pinned pseudo is dead → the temps can use v0 ✓.

OK so the same should apply lever-free: r74 (the local result) is dead in the branch where the load/xor happen? No — r74 is live at the merge (it's the returned value). Hmm, in the inner branch, r74 is defined (the boolean) at insn 85 → so r74 is live from 72 (the `result = 0` def) through the branch. In the inner branch (the mask != 0 path), r74's value from insn 72 is dead (it's redefined at 85) → so r74 is NOT live in the branch's interior (except at the def) → the temps can use v0 ✓ in the branch, and r74 takes v0 at the merge.

So why did nopin's r74 conflict v0? Because r74's live range [72..97] spans the AND temp's [74..76]... but the AND is in the branch AFTER the def at 72. Hmm, at insn 72 r74 is defined (0) and is live until the def at 85 (in the branch) → so r74 IS live across the AND (74-76) in the then-branch path (its value 0 is live until the branch decides). Hmm, in the mask != 0 path, r74's value is redefined at 85; but in the mask == 0 path, r74 keeps the value 0 (defined at 72) and goes to the merge.

So r74 IS live across [72..76] on the mask==0 path. So r74 conflicts with the AND temp ✓ (as reported).

And in the pinned version, the pinned pseudo is also live across [72..76]... but the AND temp got v1 (not v0) ✓ — the pinned pseudo holds v0, so the AND temp was pushed to v1 ✓ and the call-result copy r73 also v1 (they chain: r73 → AND temp, both in v1) ✓✓.

So in the pinned version, the chain (r73 → AND) is in v1 because v0 is held by the pinned pseudo.

Lever-free: we need the chain to be in v1 and the local result (r74) in v0. The chain's reg is decided by local allocation (the temps): the AND temp (pri 10000) and r73 (pri 7500) both prefer v0.

In local allocation, the pseudo with the higher priority gets v0: the AND temp (pri 10000) > r73 (7500). So the AND temp should get v0 and r73 v1 — but in y1/nopin they're chainable and share v0 (r73 first, then the AND in-place). Hmm, in local allocation, if two pseudos don't conflict, they can share a reg. The AND temp and r73 don't conflict (adjacent) → they share v0 ✓.

For them to be split (r73 → v1, AND → v0), they must conflict → their live ranges must overlap → the AND must be defined BEFORE r73 dies... but the AND uses r73. Contradiction? No: the AND's result (a new pseudo) is defined at the AND, and r73 dies at the AND → adjacent.

UNLESS the AND's result is needed while r73 is still live: e.g. if the AND's result is used BEFORE r73's last use... no.

Hmm, but in z3, the AND was computed BEFORE the outer branch → the AND's result is live across the branch while r73 is live across the branch too → they overlap ✓ → they're split: r73 in v0 (preference) and the AND in v1 ✓ (observed: `andi v1,v0,0x8000`).

So in z3, the split happened but the roles are reversed vs the target. In the target: the AND is in-place in the copy's reg (v1) and the copy is v1.

What if in the z3 structure the AND temp took v0 and r73 took v1? Then the machine code: `move v1,v0` (the copy) ✓, `beqz v1` ✓, `andi v0,v1,0x8000` ✗ (the target has `andi v1,v1,0x8000`).

Hmm! So close. The difference: in the target the AND's result is coalesced with r73 (in-place). For that, the AND's result pseudo must be coalesced with r73 → they're connected by the "the AND's operand is r73" relation? No — the coalescer merges a pseudo with the pseudo it's copied from. The AND's result is defined from r73 (not a copy) → they're NOT coalescable (the AND is not a copy of r73).

Hmm! But in the target, the machine code `andi v1,v1,0x8000` IS the in-place AND on r73's reg. That happens when the AND's result pseudo is allocated the same reg as r73 (allowed because they're adjacent/chainable).

In z3, the AND's result is live across the branch while r73 is live across the branch → they overlap → they can't share a reg → the AND goes elsewhere.

In the target, the AND's result is defined at the AND (after the branch? no — in the target the AND is in the DELAY SLOT of the first branch, so it's before the branch's target but after the branch's condition test).

Hmm, in the target's RTL (pinned): insn 68 = the branch on r73; insn 72 = the set of the pinned v0 to 0; insn 74 = the AND into r80 (using r73). So in the RTL, the AND (74) comes AFTER the branch (68) ✓ → the AND's result is live only after the branch → and r73 dies at the AND → adjacent → chainable ✓ → the AND's result can share r73's reg (v1) ✓.

So the target's RTL order = the original source order (the mask test inside the branch) ✓. And in that structure, the chain (r73 → AND) shares a reg, and that reg is v0 (lever-free) because r73 prefers v0 (the copy from the call's output).

=> To break it: the chain must not prefer v0. The chain's preference comes from r73's copy `(set r73 v0)` (the call's output in v0).

So: if the call's output weren't v0, r73 wouldn't prefer v0 and would take... hmm, the chain would take v1 (the next free reg) and r74 would take v0 ✓✓✓!!!

When is the call's output not v0? In gcc, `expand_call` puts the result in the call's return register (v0) — always. BUT the copy `(set r73 v0)` — hmm, that's the "reload" of the call result into a pseudo. gcc's reload phase: after local allocation, the call's result is in v0 and the pseudo r73 needs a reg; the reload phase inserts a copy if r73 isn't in v0.

Hmm, so the preference for v0 comes from the reload phase's copy.

Hmm, what if the call result is used by TWO different pseudos (e.g. `ret` and a copy)? Then the reload phase would need the value in two places...

What if the call result is used in a context that requires a move anyway? E.g. if the value is compared with a constant using an instruction that requires the operand in a specific reg (like `sltiu v0,zero,v0`)? no.

IDEA: what if the call result is passed to ANOTHER call as an argument? Then the reload phase must move it to a0 → `move a0,v0` — an extra insn (not in the target).

IDEA: What if the call result is stored into a local variable whose address is taken? → memory.

Hmm.

OK — alternative: make the chain's reg v1 by making r73 NOT prefer v0. The preference comes from the copy `(set r73 v0)`. What if the copy's source were a pseudo? I.e., what if the call's result were first copied to another pseudo by the compiler? That happens when the call's result is used in a context that...

Hmm, actually! What if the call result is used by the COMPARE in a way that requires a specific register? On mips, the `beqz` can test any reg.

Hmm, what if the source assigns the call result to a variable of a different TYPE (like `unsigned int` vs `int`)? Same mode → no.

What if the source assigns the call result to a variable and then the variable is used in a 64-bit context? no.

OK, let me try yet another angle: what if the call result is stored in a variable that ALSO gets assigned elsewhere (a re-tie)? E.g.:

```
ret = func_80133784(...);
...
```
Hmm.

What about making the call result's copy have a different source: e.g., the call result is assigned to a variable that is ALSO the result of another expression later:
```
ret = func_80133784(1, buf1, (int)buf2);
x = ret;         /* the copy */
```
cse merges x←ret.

OK OK. Let me look at this from the "what did the ORIGINAL source look like" angle once more. The ROM's `move v1,v0` + `beqz v1` + `andi v1,v1,0x8000`: the tests are on v1. In the pinned source, the tests are on `ret` (the local). So `ret` = v1 in the ROM. The pin reserved v0 for `result`.

Without the pin, the compiler gives `ret` = v0 (the copy preference). To get `ret` = v1, `ret` must lose the v0 preference.

The preference is created by the reload phase: the call's result is in v0 (hard reg) and r73 (the pseudo for `ret`) is copied from it. The reload phase's "prefer" analysis: when a pseudo is copied from a hard reg, gcc prefers to keep the pseudo in that hard reg.

BUT: the reload phase inserts a copy when the pseudo's allocated reg differs from the source's reg. The pseudo r73 was allocated... hmm, in global allocation r73 is a global allocno that "prefers v0".

Hmm, what if r73's preference were v1 (as in the pinned case, "prefers v1")? The preference comes from the copy's source reg.

So: the copy's source must not be v0. The copy's source is the call's hard-reg output (v0).

Hmm, unless the call's result is first moved by the compiler into a pseudo for another reason — e.g. if the call's result is used by a call to another function (the value must survive across the call → into a callee-saved reg or a pseudo).

IDEA!!! What if we add a second use of the call result AFTER another call? Not semantically possible.

IDEA: What if the source calls the function through a POINTER (an indirect call)? Then the call's output is still v0.

IDEA: What if the call result is assigned to a variable AND the variable's address is taken (so it's in memory)? Then the code would have sw/lw → mismatch.

Hmm.

Let me try a completely different tactic: maybe the "lever-free" spelling that reproduces the ROM uses a DIFFERENT function structure: what if the original code was:

```
if (func_80133784(1, buf1, (int)buf2) & 0x8000) {
```
Hmm, with the call result used once (in the AND), the copy `(set r73 v0)` would still exist.

What if the call result is used TWICE with different values, e.g. `ret` and `ret2`?

Hmm, what about this: what if the outer test is on a COPY of the call result, e.g.:

```
ret = func_80133784(...);
if (ret != 0) {
    ret = ret & 0x8000;     /* a re-tie: ret is redefined */
    if (ret != 0) { result = X; }
}
```
Hmm, this creates a second def of ret → the pseudo would have 2 defs → the "re-tie" materialises a real move (as the moves file says: "a re-tie materialises a real move"). Hmm! And the semantics: `ret = ret & 0x8000` then `if (ret != 0)` — the outer test ensures ret != 0 → the inner test on the masked value ✓ equivalent.

But the code shape changes: the AND's operand would be a copy... Let's see what the RTL would look like: `(set r73 (and r73 32768))` — that's in-place, no new pseudo. Hmm, but gcc would need a new pseudo if r73 is live after (r73's value after the AND is the masked value; the original value is dead after the AND) → in-place ✓. So the machine code: `andi v0,v0,0x8000` (in-place) — the same as now, but the chain is r73 → r73.

Hmm, no gain.

Let me try instead to think about what gives the copy `move v1,v0` naturally in a lever-free program: a copy from v0 to another reg happens when a value in v0 must be preserved while another value is put in v0. E.g.:

```
ret = call();        /* ret in v0 */
x = ret;             /* x in v1: the copy */
...                  /* something else uses v0 */
```
So if something else needs v0 after the call, the copy `move v1,v0` would be emitted. In the target, what needs v0 after the call? The local result (the pinned pseudo) — it's defined at insn 72 (after the call) — but that's a different reg (v0 = the pinned one) — in the pinned version, the pinned pseudo IS v0 and the call result must move out of v0 → the copy ✓.

So in the target, the "something else" is the pinned result. Lever-free, the equivalent would be another pseudo that needs v0 at insn 72 — e.g. the local `result` (r74) if it were in v0.

Circular: r74 in v0 → the chain (r73) pushed to v1 ✓. But r74 can't get v0 because the temps hold v0 in local allocation.

Hmm, hold on: in the PINNED version, the temps (r83 = the load, r85 = the xor) DID get v0 (they're in v0 in the machine code: `lbu v0,30(sp)`, `xori v0,v0,0x15`). And the AND temp (r80) got v1 (chained with r73). And the pinned pseudo (hard v0) coexists with the load/xor temps in v0 (sequentially: the pinned value is dead in that path).

So in the pinned version, the local allocnos got: r73 (call copy) → v1, r80 (AND) → v1 (chained), r83 (load) → v0, r85 (xor) → v0 (chained).

In the lever-free y1: r73 → v0, r80 (AND) → v0 (chained), r82 (load) → v0, r84 (xor) → v0.

So the ONLY difference in the local allocation is the chain's reg: v1 (pinned) vs v0 (lever-free). In the pinned version, v0 was reserved for the pinned pseudo → the chain took v1 ✓. Lever-free, v0 is free → the chain takes v0.

So the question is: how can we make the chain (r73 → AND) not take v0 in local allocation?

In local allocation, the pseudo r73 (the call-result copy) has pri 7500, refs 3, live 4; the AND temp r80 pri 10000, refs 2, live 2. Both prefer v0 (r73 via the copy preference; r80 via...?).

Local allocation assigns hard regs to local pseudos by priority; r80 (10000) > r73 (7500) → r80 gets v0 first. Then r73 (which doesn't conflict with r80 — adjacent) → v0 is taken by r80, but since they don't conflict, r73 can also use v0?? In gcc's local allocation, each hard reg is assigned to ONE pseudo (the "local" allocation gives each hard reg to at most one pseudo!). Hmm, but then r73 and r80 couldn't both be in v0.

But the observed code has both in v0 (the AND in-place on r73's reg = r80's reg = v0). Hmm, that could be a coincidence of the reload phase: the reload phase may merge r80 into r73's reg (they're connected: r80 = r73 & C, and r73 dies → the reload phase can put r80 in r73's reg).

Hmm, so in the machine code, `andi v0,v0,0x8000` could be r80 allocated in v0 where r73 was (r73's reg reused).

OK, so the chain's reg is determined by r73's allocation (v0 due to the copy preference).

To break the preference: the reload phase's preference for v0 comes from the call's output being in v0.

!!!! IDEA !!!!: what if the call result is used in a way that the reload phase must keep v0's value intact? E.g. if the call result is needed LATER (after another use of v0). But we can't.

Hmm, what if the function calls something else after the call? The ROM has no other calls.

What if the local result's def (insn 72) requires v0 (the pinned-like chain)? In lever-free, r74 (the local result) is a pseudo; if it were allocated v0, the reload phase would insert a copy from wherever r74 is to v0 → `move v0,v1`?? Hmm, that would be an extra insn.

Honestly, maybe the answer is that this item's ROM was produced from a source with a `register` variable (the pin) and the lever-free spelling doesn't exist — a WALL. The evidence is strong: the copy `move v1,v0` exists ONLY because v0 was reserved for the whole function by the hard-reg pseudo.

But wait — the brief says the lever-free body must score 0. Maybe there's a spelling where the local result is a hard-reg-like construct... but `register` is banned and `__asm__` is banned.

Hmm, hold on! What about the C0505 catalog: "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse".

"loop shape"! What if the whole tail is wrapped in a loop (e.g. a do-while(0))? From the moves file: "pin | func_8017CE7C | MATCH — do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2 (G06)".

Interesting: a do-while(0) changes the live range shape (the loop back edge extends the live range) → changing the priority. For us: we want the chain (r73) to have a LOWER priority than the local result, or to make the local result win v0.

In local allocation, the priorities: r73 (7500) and r80 (10000, the AND temp). If we could make r80 (the AND temp) conflict with r73 (so they can't share v0), then r80 (pri 10000) takes v0 and r73 takes v1 ✓ → the copy `move v1,v0` survives ✓ and the AND would be `andi v0,v1,0x8000` ✗ (not in-place).

Hmm, but hold on: if r73 is in v1 and the AND's result r80 is in v0, the machine code would be:
```
24 move v1,v0      ✓ (the copy survives!)
25 beqz v1         ✓
26 andi v0,v1,0x8000   ✗ (target: andi v1,v1,0x8000)
```
Then the branch tests v0. Hmm, the target's andi is in-place in v1. So we'd have a mismatch on the andi but a match on the copy. Score-wise that might be ~4-5.

Hmm, but z3 already scores 4 with the opposite arrangement.

Hmm, let me look at z3's actual full listing to see how close it is, and think about whether a variant could give the target's exact shape.

Actually — KEY INSIGHT attempt: in the target, the AND's result r80 is in v1 (chained with r73). For that, r73 must be in v1 AND r80 must be chainable with r73 (adjacent live ranges). r80 gets v1 because r73 has v1 (the reload phase reuses r73's reg for r80 since r73 dies at the AND).

So the whole chain is in v1 in the target and v0 lever-free. The chain's reg = r73's reg. r73's reg = the reload phase's choice: it prefers v0 (the call's output reg) unless v0 is occupied at that point.

In the pinned version, v0 is occupied by the pinned pseudo (whose live range covers [72..97] and the copy happens at 65 — hmm, r73's live range [65..74] overlaps the pinned pseudo's [72..97] at [72..74] → so v0 is occupied at [72..74] → r73 can't be v0 → v1 ✓✓✓ (that's the mechanism I identified earlier).

So lever-free: we need v0 to be occupied during [72..74] by another pseudo. The local result r74 IS live during [72..74] (its def at 72). So if r74 were allocated v0, r73 would be pushed to v1 ✓✓✓ and the AND (r80, chained with r73) would be in v1 ✓ and the load/xor chain (r82/r84) would be in v0 (chained with r74? hmm, in the target the load/xor are in v0 = the pinned result's reg).

So everything hinges on: can r74 (the local result) get v0?

r74's conflict with v0 (in nopin) came from the temps r80/r82/r84 holding v0 — but those are LOCAL allocnos assigned v0 by local allocation. In local allocation, the pseudo with the highest priority gets v0. The temps have pri 10000 each. r74 is a GLOBAL allocno (it conflicts with hard regs) → global allocnos are allocated AFTER local ones → the local temps own v0 → r74 can't have it.

Hmm! Unless r74 is NOT global — i.e. r74 doesn't conflict with any hard reg. r74 conflicts with v0 because the temps (local, hard v0) overlap it. Circular again.

Hmm, but in the PINNED version, r74 doesn't exist (it's the hard-reg pseudo) — the analogue is the pinned pseudo, which IS a hard-reg pseudo (local allocation gives it v0 directly).

So: to have a pseudo own v0 from the start (like the pinned pseudo), it must be a LOCAL allocno with a preference/priority that beats the temps, and it must not conflict with the temps' live ranges.

r74 (the local result) conflicts with the temps (the AND temp r80 overlaps [72..76]). Hmm, so even if r74 were local, it'd conflict with r80 (the AND temp) → they can't share v0 → one of them goes elsewhere.

In the target, the pinned pseudo (v0) coexists with the AND temp (v1) ✓ — they conflict, so the AND went to v1 ✓ (that's exactly what the pinned pseudo forced).

So lever-free: r74 (v0) and the AND temp (v1) and r73 (v1, chained with the AND). For that, r74 must win v0 over the AND temp (pri 10000) — r74's pri is 11428 (refs 4, live 7) ✓ HIGHER. But the preference for v0 (r73's copy preference) beat the priority in the nopin case.

Hmm, but in the nopin case, r74 lost v0 to... whom? The temps r80/r82/r84 (local allocnos, hard v0). Since they're local and assigned v0 first, r74 (global) can't have v0.

So we need r74 to be LOCAL. r74 becomes global when it conflicts with a hard reg. In the nopin structure, r74 conflicts with v0 (the temps' hard reg). Hmm, but in the pinned version, the analogue (the pinned pseudo) is local by construction (it has a fixed reg).

Circular: r74 conflicts with the temps' v0 → global → can't own v0.

Hmm, unless r74's live range does NOT overlap the temps'. r74's live range [72..97] overlaps the AND temp [74..76] inherently (the AND is between the def at 72 and the use at 97).

Unless the AND's result is not a separate pseudo but merged with r73 (in-place) — that's the case when r73 and r80 are chainable (adjacent) ✓ (the original source order). Then r74 [72..97] vs r73+r80 [65..76]: they overlap at [72..76] → r74 still conflicts with the chain's reg (v0) → global.

Hmm, but wait: r74's conflict with v0 — is it with the chain (r73/r80 in v0) or with the load/xor temps? Both.

So: r74 conflicts with v0 no matter what (as long as the chain is in v0 and overlaps [72..76]).

=> The only way: the chain must NOT be in v0 → the chain must be in v1 → but the chain prefers v0 (the copy preference) and the local allocation gives v0 to the highest-priority pseudo that wants it.

Hmm, in local allocation, which pseudo gets v0? The candidates: r73 (pri 7500, prefers v0 via the copy), r80 (AND temp, pri 10000), r82 (load, 10000), r84 (xor, 10000). If the local allocation assigns v0 to r80 (the highest pri among those that can use it), then r73 (7500) would get another reg (v1) — BUT they don't conflict (adjacent) → hmm, in gcc's local allocation, each hard reg goes to ONE pseudo. So v0 → r80 (pri 10000) and r73 → v1 (pri 7500, next free reg) — but then the machine code would show the AND in v0 and the call result in v1 — hmm, that's z3-ish but not exactly.

But the observed lever-free code has the chain all in v0 (`beqz v0`, `andi v0,v0,0x8000`). So the local allocation gave v0 to r73 (the copy) and the AND reused r73's reg in the reload phase.

Hmm, so gcc's local allocation DOES allow sharing when they don't conflict (it's a "conflict graph"-based allocation, not one-pseudo-per-hard-reg).

OK. I've spent a lot of time. Let me consider the practical: the best lever-free score so far is 4 (z3/z6). Let me try a few more permutations around z3 (the mask computed first) to see if I can get the target's exact shape:

z7: mask computed first, but the mask variable is declared/assigned such that the AND's result is chained with the call result copy. Hmm.

Actually, what if the mask is computed first AND the outer test uses the mask's ORIGINAL value...

Let me think about the target's RTL once more:
```
(insn 65) (set r73 v0)        <- the copy
(insn 68) branch on r73 == 0
(insn 72) (set v0 0)          <- the pinned result = 0 (hard reg)
(insn 74) (set r80 (and r73 32768))
(insn 76) branch on r80 == 0
```
So the AND (74) is AFTER the branch (68) ✓ and the pinned v0 def (72) is between them.

Lever-free equivalent with r74 as a pseudo:
```
(insn 65) (set r73 v0)
(insn 68) branch on r73 == 0
(insn 72) (set r74 0)
(insn 74) (set r80 (and r73 32768))
```
That's the nopin structure ✓ (r74 live from 72).

For the target's allocation: r74 = v0, r73 = v1, r80 = v1 (chained with r73).

Lever-free, r74 must be v0. r74's conflicts: with r73/r80 (in v0) and r82/r84 (in v0).

What if the load/xor temps were in a different reg so that v0 is less contended? The temps' reg choice is also by local allocation.

Hmm, what if the temps' live ranges didn't overlap r74? The load/xor temps are in the branch where r74 is live (r74's value is dead there but r74 is "live" in the sense of being on the path). Hmm, in the pinned version, the pinned pseudo (v0) coexists with the load/xor temps (v0) — so they're chainable/sequential there. Because the pinned pseudo's value is dead in that path.

For r74 (a pseudo), the same reasoning should apply: r74's value is dead in the branch (redefined at 85) → r74 shouldn't conflict with the load/xor temps. But the dump says r74 conflicts v0 — maybe that conflict is only with the chain (r73/r80).

So: if the chain (r73/r80) were in v1, r74 could take v0 ✓ (no conflict with the load/xor temps, since they're chainable with r74 in the branch).

So everything comes back to: the chain must be in v1.

The chain's reg = r73's reg. r73 is a global allocno (in the order line) in the lever-free version, and in the pinned version it's also global ("73" in the order line) — but in the pinned version it "prefers v1"!! Why does it prefer v1 there and v0 lever-free? Because the preference is computed from the copy's source: in the pinned version, the copy `(set r73 v0)` — the source is still v0 → the preference would be v0. But the dump says "prefers v1" for the pinned r73. Hmm, and "conflicts v0" (because the pinned pseudo holds v0) → so gcc chose v1 as the alternative preference.

Hmm, interesting: so the "prefers" in the dump = the preference AFTER conflict resolution? In the pinned version, r73 prefers v1 (v0 excluded by the conflict).

So in the lever-free version, r73 prefers v0 (no conflict) → gets v0.

CONCLUSION: the lever-free spelling cannot deny v0 to the call-result copy without a hard-reg pseudo. The mechanism is inherent to the ROM's shape: the `move v1,v0` exists because the ROM's original code had v0 reserved.

Hmm, BUT: what if we make r73 conflict with v0 by having ANOTHER pseudo hold v0 during [65..74]? The candidates in that window: the local result r74 (live [72..97] — overlaps [72..74] ✓). If r74 were allocated v0, r73 would conflict with v0 → r73 → v1 ✓✓✓.

And r74's allocation: it's global (conflicts with the hard reg v0 → because the chain/temps hold v0) → hmm, circular again. BUT: what if the chain were NOT in v0? The chain is in v0 because r73 prefers v0. Circular.

Unless... the load/xor temps (r82/r84) take v0 and the chain takes v1 by priority! In local allocation, the temps (pri 10000 each) vs r73 (7500): if the temps get v0 first, r73 gets v1 ✓. But the observed code has the chain in v0 and the temps also in v0 (sequentially).

Hmm, in the observed code: `beqz v0` (r73), `andi v0,v0,0x8000` (r80 in r73's reg), `lbu v0,30(sp)` (r82), `xori v0,v0,0x15` (r84 in r82's reg), `sltiu v0,zero,v0` (r74!). So ALL of them are in v0 — a single chain through v0! And r73's pri is the lowest (7500) but it got v0 first (it's first in the chain).

So the reload phase merges the chain into v0.

OK: FINAL IDEA before I write this up as a wall: what if we make the call-result copy's preference be v1 by making the CALL's result land in a pseudo first? E.g., if the source has the call result assigned to a variable AND the same variable is used in a context requiring...

Hmm, what about this: `ret = func_80133784(...)` where the call is INDIRECTED through a function pointer? The call's output would still be v0.

What about: the call result is used in a comparison with a 64-bit constant? no.

What about: the call result is stored into a `char` variable and then... no.

Hmm, what about the ORDER of the two uses: what if `ret` is used in the AND first and the zero-test second? The RTL:
```
(set r73 v0)
(set r80 (and r73 32768))    <- the AND right after the copy
branch on r73 == 0           <- the outer test
```
Hmm, then r73 is live [65..74] and r80 [65..76] → they overlap → the AND gets a different reg → `andi v1,v0,0x8000` and the outer test on v0 ✗.

Alright. Let me try a slightly different family: what if the outer test is on the MASK variable and the inner test on the call result? Hmm.

Let me try a small batch of "shape" variants around z3 (score 4) to see if any reaches 0:

z7: z3 but with `mask` as `unsigned short`? hmm, `ret & 0x8000` as unsigned short → the AND in HImode → `andi v1,v0,0x8000` (16-bit) — the target's andi is 16-bit? `andi v1,v1,0x8000` — the target's is a full 32-bit andi (0x8000 fits in 16 bits either way).

z8: z3 with the mask computed before the call? no.

z9: z3 with `mask` declared as `unsigned int` (z4 = 6).

z10: z3 but the outer test on `mask` and the inner on `ret`:
```
mask = ret & 0x8000;
if (mask != 0) {
    if (ret != 0) { result = X; } else { result = 0; }
} else { result = 0; }
```
Semantically equivalent ✓ (mask != 0 implies ret != 0). The machine code: the AND, then the branch on the mask, then... the outer branch on ret would be folded away (gcc knows mask != 0 → ret != 0? it knows bit 15 set → negative → != 0 ✓ probably folded).

z11: z3 with the boolean expression assigned via a temp.

Let me try z7, z10, z11 and a couple more, then stop.

Actually, let me reconsider z3's diff: the missing insn is `move v1,v0` and the branch offsets. If I could get the call result into v1 with the copy, the rest would match.

In z3 the chain is: r73 (the call copy) in v0, the AND temp in v1 (separate reg, since they overlap).

What if the AND's result were coalesced with the CALL copy (in-place) but the call copy were in v1? That's the target: `move v1,v0; beqz v1; andi v1,v1,0x8000`.

For the AND to be in-place in r73's reg, they must be chainable (adjacent) → the AND must be defined after r73 dies (the original source order) ✓. And r73 must be in v1 → r73 must lose v0.

In the original source order (nopin/y1), the chain is in v0. In z3 (the AND before the branch), the chain is split.

What if the AND is defined after r73 dies BUT the chain is forced to split? They only conflict if they overlap...

Hmm, what if the AND's result is used TWICE (so its live range extends)? E.g. if the mask value is used in both the branch and something else. Then r80's live range would extend beyond r73's death → still adjacent at the start. Hmm, adjacent is enough for chaining.

What if r73's live range extends BEYOND the AND (i.e. `ret` is used after the mask test)? Then r73 [65..later] and r80 [74..76] overlap ✓ → they split → but then the AND is not in-place ✗.

Hmm, the target has the AND in-place in the copy's reg. So r73 and r80 must share a reg, and that reg must be v1.

Sharing v1: they chain, and the chain's reg is v1 if the chain's head (r73) is v1. r73 = v1 requires it to lose v0.

In local allocation, r73's preference for v0 comes from the reload copy. BUT hold on — is r73 really assigned by local allocation? In the lever-free dump, r73 is GLOBAL (in the .greg order). In the pinned dump, r73 is also global. Hmm, but the pinned dump's r73 has pri 7500, refs 3, live 4, "conflicts v0,sp, prefers v1" — the same numbers as the lever-free r73 (the call-result copy). So the pinned r73 IS the call-result copy ✓ (and it's global, preferring v1 because v0 is taken by the pinned pseudo).

So in the pinned version, the global allocation gave r73 (the call copy) v1 because v0 was reserved. Lever-free, r73 gets v0 (its preference).

So: in global allocation, r73's preference for v0 wins over r74's higher priority. And in the pinned version, r73's preference for v0 was impossible.

So the ONLY way lever-free: r73 must conflict with v0 → some other pseudo must hold v0 during [65..74] → r74 (the local result, live [72..97]) if r74 could hold v0. But r74 can't hold v0 because it conflicts with the chain in v0 (r73/r80) and the temps.

Circular — UNLESS the chain and the temps are in a reg OTHER than v0, freeing v0 for r74. But the chain wants v0 (r73's preference) — and r74 (pri 11428) would beat r73 (7500) in the global allocation IF r74 were allowed v0.

The allocation order line "74 73" means r74 is processed FIRST → r74 would get v0 if it could... but it conflicts with v0 (because of the local allocnos holding v0 in the overlapping window).

Hmm, so the local allocnos (the chain r73? no, r73 is global) — the LOCAL allocnos holding v0 are r80 (the AND temp), r82 (the load), r84 (the xor). Those are local (pri 10000 each) and they hold v0 → r74 conflicts with them → r74 gets v1.

Wait, but in the PINNED version, the same temps (r83/r85) held v0 and the pinned pseudo (a local allocno with a fixed reg) coexisted ✓ (they're chainable with it).

Hmm, so for r74 (a pseudo), the conflict with the temps is because r74's live range [72..97] overlaps the temps' live ranges ([74..76], [81..83], [83..85])? In the branch, r74's value is dead (redefined at 85) → so r74 should NOT conflict with the load/xor temps (chainable) — but it does conflict with the AND temp (r80 [74..76]) because r74's value (def at 72) is live across the AND on the mask==0 path.

So r74 conflicts with v0 via the AND temp r80 (in v0). If the AND temp were in v1 (as in the pinned version), r74 could take v0 ✓ and then r73 (the chain head) would conflict with v0 → v1 ✓✓✓ = the target!

So the requirement: the AND temp must NOT be in v0 — i.e. the chain must be split such that the AND is in a different reg from r73, AND r74 takes v0.

In z3, the split happened (the AND in v1, the call copy in v0) but r74 didn't take v0 — why? Because r74 conflicts with... let me check z3's alloc table! In z3, the local result r74's live range starts after the AND (the def order differs) → maybe r74 doesn't conflict with v0 → r74 could take v0 ✓. Let me dump z3's alloc table to see.

Let me do that now — it's cheap and decisive.
