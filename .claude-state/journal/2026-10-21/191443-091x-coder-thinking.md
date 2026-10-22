---
ts: 2026-10-22T01:14:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_swyDZPukhe8IgOndFjdp
---
Now I see the pinned version's RTL:

- insn 65: `(set (reg/v:SI 3 v1) (reg:SI 2 v0))` — the call result copied from $2 into pseudo r80 (which is allocated $3) ✓ → the `move v1,v0` at ins 24 ✓.
- insn 72: `(set (reg/v:SI 2 v0) (const_int 0))` — hmm, this sets $2 = 0 — that's the "return 0" (the RESULT_DECL = 0 in $2!). So the RESULT_DECL is IN $2 here! (a hard reg set, `(reg/v:SI 2 v0)` = a pseudo allocated to $2 → r83 or r85?).
- insn 74: `(set (reg:SI 3 v1) (and:SI (reg/v:SI 3 v1) (const_int 32768)))` — the mask in $3 ✓.

So the RESULT_DECL r73 is allocated $2 ✓ (the disposition line "73 in 3" might mean something else — maybe it's the class/preference info; the actual allocation shows r73 in $2 via `(reg/v:SI 2 v0)`).

Hmm, the "Register dispositions" line format in gcc 2.7.2's global.c: "73 in 3" might mean "pseudo 73 has preference for reg class 3" or something. Whatever.

KEY: the pinned var (the hard reg $2) is what makes the RESULT_DECL be $2 AND makes the ret var ($3) separate.

In the pinned version:
- The RESULT_DECL (r73) → $2 ✓ (it conflicts with the pinned $2 var → "conflicts v0" — hmm, but then how is it $2?).

Hmm, insn 72 sets `(reg/v:SI 2 v0)` = a pseudo in $2 — that could be the pinned var (a hard reg pseudo) rather than the RESULT_DECL. And the RESULT_DECL's copy `move $2, <pinned var>` would be a no-op ✓.

OK. So the practical conclusion stands: the target needs $2 reserved for the whole function by a hard-reg var (the pin) — lever-free, $2 is only reserved for the RESULT_DECL's short live range.

So the question remains: what lever-free source shape makes the RESULT_DECL's live range cover the call?

IDEA!!! What if the source has the RESULT_DECL set EARLY because the function returns EARLY on some path — specifically, what if the source's `return 0` paths come BEFORE the call in the RTL order? No...

Hmm, hold on. Let me reconsider: the RESULT_DECL's live range in gcc's global-alloc for a function = from the point where it's set to the end of the function. But maybe gcc computes it as: the RESULT_DECL is live-out → in the global allocator, the live range of a live-out pseudo starts at the function's START? Let me check gcc 2.7.2's global.c: `allocno_live_ranges` computes the live range by scanning; for a reg that's live at the function's end (live-out), the live range extends to the end. The start = the first set ✓.

In MY P1 version, the table showed r73 (the RESULT_DECL) with live 3 → so it starts at ~ins 36. In the pinned version, r73 has live 4.

Hmm, so both are short.

But the difference: in the pinned version, the ret var (r80) got $3 — why not $2? Because $2 was occupied by the PINNED var for the whole function ✓ (hard regs are reserved globally).

So the lever-free version must have $2 occupied across ins 24-27 by a LOCAL pseudo. Which local? The RESULT_DECL — but its live range is short.

Hmm, so what if the RESULT_DECL's live range were extended by an early `return`? Let me think about whether an early return could be added without changing the instruction stream...

IDEA: the source could have a `return` in a block that gcc's flow optimization merges into the existing code. Hmm.

Alternatively: what if the RESULT_DECL's live range could be extended by making the source's `result` variable live across the function and allocated... hmm, $2 is taken by the RESULT_DECL (global alloc). Hmm, but wait: is the RESULT_DECL really allocated by global-alloc? In gcc 2.7.2, the RESULT_DECL is a pseudo that is live-out → global-alloc handles it ✓ → it gets $2 (preferred v0) for its live range.

So the local allocator knows $2 is busy in [36..39] and free elsewhere → the ret var takes $2 at [24..27] ✗.

To block that, we need $2 busy at [24..27]. Options:
(a) A local pseudo live across [24..27] that gets $2 — but $2 is reserved by the RESULT_DECL only in [36..39]; a local live across [24..27] could get $2 if it doesn't conflict with the RESULT_DECL's range ✓!! E.g. a local live from ins 20 to ins 30 (not overlapping [36..39]) → it could take $2 ✓✓. But then the ret var would need another reg ($3) ✓✓ and the RESULT_DECL $2 ✓.

So: I need a local variable that is live from before the call until after the mask test, and is allocated $2 (or at least takes $2 away from the ret var).

Hmm, but which local? The `result` variable in the nopin shape is live from ins ~24 to the end (overlapping the RESULT_DECL's range) → it gets $3 ✗.

What if the source has a local that is live ONLY in [24..27]? E.g. a copy of the call result:
```
ret = func_80133784(...);
t = ret;             /* t is live [24..27] */
if (t != 0) { if ((t & 0x8000) != 0) {...} }
```
Then: the call result pseudo ($2 hard?) → the copy to `t`... hmm, `t` and `ret` would be coalesced (one use each) → the same problem.

Hmm, what if the local is live across the CALL? Then it must be in a callee-saved reg ($16-$23) ✗ (the target has $3 = $v1, caller-saved — so the ret var is NOT live across a call ✓ consistent).

OK, so the local must be live in [24..27] but not across the call. Then it can be $2 or $3 or $4... and the ret var needs another. The allocator picks by priority: both would want $2 → the higher priority wins $2. The ret var (r80 in the pinned version) had pri 10000, refs 2, live 2.

Hmm, so if I introduce another local with a HIGHER priority that lives in [24..27], it would take $2 and the ret var would go to $3 ✓✓!

What local could have a higher priority? pri = refs*10000/live. The ret var: refs 2, live 2 → 10000. A local with refs 3, live 2 → 15000 ✓.

Hmm, how to get a local with 3 refs in a short live range? E.g. a variable used 3 times:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) { ... }
    ...
}
```
ret has 2 uses.

What if we introduce:
```
m = ret & 0x8000;    /* m: 2 refs (the set + the use) */
```
Hmm, the andi's destination would be a separate pseudo (not $3's v1 = the ret var) — the target's `andi v1,v1,0x8000` writes into the SAME reg as the ret var ✓ → so the mask is computed in place into the ret var → the source is `if ((ret & 0x8000) != 0)` ✓ (gcc's temp is coalesced with ret).

OK so let me think about the "3 refs" local: what if the source uses the call result 3 times? E.g.:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        if (ret != 0) { ... }   /* a redundant test — extra instructions ✗ */
    }
}
```
✗.

Hmm. What about the priority of the RESULT_DECL vs the ret var: the RESULT_DECL (global) gets $2 by preference, but the LOCAL allocator assigns the ret var $2 because $2 is free in its range. Hmm, so the local allocator's choice is "the first free reg in the preferred order".

So the ret var gets $2 (its preference, v0) if $2 is free in [24..27] ✓.

To make it take $3, I need $2 to be occupied in [24..27] by another pseudo.

What pseudo could that be? The `result` local in the nopin shape is live from ins 24 (the `result = 0` set) to the end ✗ (it conflicts with the RESULT_DECL's range → it can't be $2 → it gets $3 → and the ret var takes $2 ✗ — exactly nopin's outcome).

Hmm! But what if the `result` local's live range does NOT overlap the RESULT_DECL's? Then it could be $2 ✓ and the ret var $3 ✓ and the RESULT_DECL... would be $3?? (since $2 is taken by the local in [24..39]... hmm, the RESULT_DECL's range is [36..39] and the local's [24..35] → they don't overlap → both could be $2! But the coalesce: the copy `move $2, $2` → elided ✓✓.

So: the local `result` must be live from ~24 to ~35 and the RESULT_DECL from 36 to 39, and BOTH allocated $2 (the local allocator would give $2 to one and $3 to the other...). Hmm: the local allocator assigns hard regs to the LOCAL pseudos; the RESULT_DECL (a global) got $2 from the global allocator. Then the local `result` can't be $2 (the global allocator reserved $2 in [36..39] — but the local's range is [24..35] → no overlap → the local CAN be $2!).

Hmm, but gcc's local-alloc: for each local pseudo, it tries the preferred reg first (the local has no preference → it uses the "reg_preferred_class" of the pseudo's mode = the class order) → it would pick $2 if free in its range ✓.

But the RESULT_DECL's preference for $2 ("prefers v0") and the local's allocation... The local `result` would get $2 (the first free reg in the class order) and then the copy `move $2, $2` (the RESULT_DECL = the local) → elided ✓✓✓!!! And the ret var (live [24..27]) would find $2 taken by the local `result` (live [24..35]) → it takes $3 ✓✓✓!

THAT'S THE MECHANISM! So the lever-free body needs:
- a local variable (`result`) that is live across the ret var's range (i.e. set BEFORE the call or right after and live until the end), and
- the RESULT_DECL's set at the very end (so the copy is elided and the local's range doesn't overlap... hmm, but the copy point IS the overlap).

Hmm, the coalesce: the copy `move RESULT_DECL, result` at ins 39 — the RESULT_DECL is $2 (global) and the local is $2 → the copy is `move $2,$2` → deleted ✓.

But hold on: in the nopin shape, the local `result`'s live range = [24..39] (it's used at the return) and the RESULT_DECL's = [39..39] → they overlap at ins 39 → the local can't be $2 (the global allocator reserved $2 for the RESULT_DECL in [39..39] — hmm, the overlap is just at ins 39; the local is live AT ins 39 (its use) → conflict → the local can't be $2 ✗ → it gets $3 ✗ (as in nopin).

Hmm! So for the local to be $2, the RESULT_DECL must NOT be in $2. Hmm, circular.

Hmm, but wait: the coalesce could resolve this: the copy `move RESULT_DECL, result` — reload1's coalesce tries to merge the RESULT_DECL and the local into the same reg. If the local is $2 and the RESULT_DECL is $3 → the coalesce would prefer $2 (the RESULT_DECL prefers v0)... but the RESULT_DECL was already allocated by global-alloc.

Hmm, in the pinned version, the RESULT_DECL's copy is `move RESULT_DECL, $2` (the pinned var) — and the RESULT_DECL ended up in $2 too (via the coalesce? the pinned var is a hard reg $2, so the copy `move $2, $2` is elided at RTL level ✓ — that's it! The copy from a hard reg to a pseudo that will be allocated the same hard reg: the reload/coalesce handles it.)

So for a lever-free body: the local `result` is a pseudo; the copy `move RESULT_DECL, result`; the RESULT_DECL is allocated $2 (global, preferred); the local is allocated by local-alloc → it can't be $2 (the RESULT_DECL's $2 conflicts at the copy point) → $3 → the copy `move $2,$3` remains ✗ (nopin's outcome).

Unless the local's live range does NOT include the copy point — impossible (it's the source of the copy).

Hmm, BUT: what if the local `result` is live across the ret var's range AND the RESULT_DECL gets $3 while the local gets $2? Then the copy would be `move $3, $2` ✗.

Hmm, so we need the copy to be elided: the local and the RESULT_DECL in the same reg. The coalesce does this when possible: reload1's coalesce merges the copy's src and dst if they can share a reg. If the local gets $2 (because $2 was free in the local's range except at the copy point...) — the conflict at the copy point is exactly the problem.

Hmm, unless the local's live range ENDS at the copy (it's the last use) and the RESULT_DECL's live range STARTS at the copy. In gcc's live-range computation, a pseudo that's live up to ins 39 and the RESULT_DECL live from ins 39 — do they overlap? The local's live range = [24..39] and the RESULT_DECL's = [39..39]. At ins 39 the local is USED (read) and the RESULT_DECL is SET (written) → they interfere at ins 39 (a read-write conflict on the same reg is fine if the read happens before the write! But gcc's conflict matrix is conservative: for a copy `move dst, src`, the interference is computed such that dst and src CAN share a reg — that's exactly what the coalesce exploits.

Hmm, gcc's live-range computation: for the copy insn, the "reg_where_born" logic handles the copy specially: the dst is considered to be born at the copy and the src to die at the copy → they don't conflict ✓. So the local `result` and the RESULT_DECL DON'T conflict at ins 39 ✓.

So the local could be $2 and the RESULT_DECL $2 → the copy is elided ✓✓. But then the ret var (live [24..27]) conflicts with the local `result` (live [24..39]) → the ret var gets $3 ✓✓✓!!!

So WHY did nopin give the local $3? Because the local allocator gave $2 to... hmm. In nopin's diff: mine[32] `sltiu v1,v0,1` — the byte comparison is in $3 (v1) and `move v0,v1` at the end (the copy into $2) → so the local `result` = $3 and the RESULT_DECL = $2.

Hmm! So in nopin the local got $3, not $2. Why? The local allocator's reg choice for the local `result`: its live range [24..39] overlaps the RESULT_DECL's [39..39] — hmm, they don't conflict (per the copy rule) → so the local COULD be $2 ✓. But the allocator gave it $3.

Hmm, maybe because the local's live range overlaps the ret var's [24..27] and the ret var was allocated FIRST (higher priority: the ret var's pri 10000 vs the local's pri = 2*10000/15 = 1333) → the ret var got $2 (its preference) and the local got $3 ✗.

So the priority decides: the ret var (pri 10000) > the local `result` (pri 1333) → the ret var wins $2.

=> To flip: the local `result` must have a HIGHER priority than the ret var, or the ret var must have a lower priority.

The ret var's pri = refs*10000/live = 2*10000/2 = 10000 (refs 2, live 2 — hmm, in the table r79: pri 10000, refs 2, live 2 ✓).

The local `result` in nopin: refs 2 (the set + the use), live ~15 → pri 1333.

To raise the local's priority: more refs (uses) or a shorter live range. Hmm: if the local `result` were live [24..27] only (short) — but it must be live until the return.

Hmm, what if the local is used MORE times? E.g. the `result` variable assigned and used in multiple places:
```
result = 0;
if (ret != 0) { if ((ret & 0x8000) != 0) { result = byte != 0x15; } }
return result;
```
refs 2.

What if:
```
result = 0;
if (ret != 0) {
    result = 0;             /* an extra set → refs 3 */
    if ((ret & 0x8000) != 0) { result = byte != 0x15; }
}
return result;
```
Hmm, the extra set is redundant → cse removes it → the refs stay 2. Hmm, but the PRIORITY is computed at the global-alloc stage (after cse) → the redundant set is gone.

Hmm. What if the local `result` is assigned in two DIFFERENT places with different values? e.g.
```
result = 0;
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = byte != 0x15;
    } else {
        result = 0;
    }
}
return result;
```
Hmm, the else branch's `result = 0` is redundant (result is already 0) → cse removes it.

Hmm, what about making the local's live range SHORTER by moving the final return earlier? E.g.:

```
result = 0;
if (ret != 0 && (ret & 0x8000) != 0) {
    result = byte != 0x15;
}
return result;
```
The local's live range = [the set .. the return] — still long.

Hmm, what if the local is set AFTER the call (so its live range is shorter)? E.g.:
```
ret = func_80133784(...);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = byte != 0x15;    /* the set is inside */
        return result;
    }
}
return 0;
```
Then the local `result` is live only in the inner block [29..33] → its live range is short → pri = 2*10000/4 = 5000 (like r75/r76 in the table) → still < 10000 ✗.

Hmm. And this shape returns 0 at the end (2 returns) — the RESULT_DECL's refs = 2.

Hmm, the ret var's pri = 10000 is hard to beat: refs 2, live 2 → 10000 is the max for refs=2. With refs 3 and live 2 → 15000. So I need a local with 3 refs and a live range of 2, live in [24..27].

What local would have 3 refs in [24..27]? Hmm: a variable used 3 times:
```
ret = func_80133784(...);
if (ret != 0) { if ((ret & 0x8000) != 0) { ... } }
```
Hmm.

What about the RESULT_DECL itself getting $2 (it does ✓) — the issue is only the ret var taking $2 in [24..27]. Hmm, but WAIT: the RESULT_DECL's live range in nopin = [36..39] (late) — so $2 is free in [24..27].

Hmm, what if the RESULT_DECL's live range started EARLIER? Then $2 would be reserved in [24..27] ✓ and the ret var → $3 ✓✓✓.

The RESULT_DECL's live range starts at its first set. In nopin, the RESULT_DECL is set only at the end (the copy) → [39..39] hmm, but the table said live 3.

In P1 (3 returns), the RESULT_DECL is set at the `return 0`s (early-ish) → hmm, but the table showed live 3 for P1's r73 → so the RESULT_DECL's first set is at ~ins 36 ✗.

Hmm, why? In P1, the `return 0` statements set the RESULT_DECL = 0 at the return points — but gcc's flow optimization may have merged them into a single exit block at the end (the `move v0,zero` at the end) → so the RESULT_DECL's first set is late ✓.

In the TARGET, the `move v0,zero` sets are at ins 28 (the delay slot) and ins 34 → the RESULT_DECL's live range = [28..39] → $2 is reserved from ins 28 — but the ret var is live [24..27] → NO overlap → the ret var could still take $2 ✗ (in the target it's $3 — because $2 was reserved by the PINNED var for the whole function ✓).

So the target's key: $2 reserved for the WHOLE function. Lever-free, that requires a pseudo live across the whole function allocated $2 — the RESULT_DECL (live [28..39]) doesn't cover [24..27] ✗.

Hmm, so we need $2 reserved from before the call. What pseudo could be live from before the call to the end and allocated $2?

The RESULT_DECL could be! If the source has an early `return` (before the call) → the RESULT_DECL's live range starts early ✓✓.

But an early return adds instructions ✗... UNLESS the early return is on a path that the code already has!

Hmm, hold on: is there any way to have the RESULT_DECL set before the call without extra instructions? What if the source's structure is:

```
ret = func_80133784(...);
...
```
Hmm.

Alternatively, a LOCAL pseudo live across the whole function and allocated $2: the local `result` (nopin shape) is live [24..39] — it doesn't cover the call (ins 22) but it DOES cover [24..27] ✓✓!! So if the local `result` were allocated $2, the ret var would go to $3 ✓.

So the question reduces to: how to make the local `result` get $2 instead of $3?

The local allocator gives $2 to the highest-priority pseudo whose range allows. The ret var (pri 10000) vs the local `result` (pri ~1333) → the ret var wins.

To flip: make the local's priority > 10000: refs*10000/live > 10000 → refs > live. With live 15, refs ≥ 16 ✗ (impossible).

Hmm, that formula gives the local a very low priority. So the local `result` will never get $2 over the ret var.

Hmm, unless the local's live range is SHORT. E.g. if the local `result` is set right before the return (in the inner block) → live 4 → pri 5000 < 10000 ✗. Hmm, still less.

With live 2 and refs 3 → 15000 ✓. Hmm, what local has 3 refs and lives in 2 insns? E.g.:

```
if (cond) { x = 1; y = x; z = y; }   /* 3 refs, live ~2 */
```
Contrived ✗.

Hmm, what about the ret var's priority: refs 2, live 2 → 10000. Can I lower it? If the ret var's live range were longer (live 3 → pri 6667) then a local with pri 10000 (refs 2, live 2) would beat it ✓!

How to make the ret var's live range longer? Its live range = [the copy at ins 24 .. its last use at ins 26]. If the source used `ret` LATER (e.g. after the mask test), its live range would extend → pri drops → the local `result` (pri 10000 if live 2) hmm.

Hmm, hmm. But wait: the local `result` in the nopin shape is live [24..39] → pri 1333.

I need a local with a SHORT live range that overlaps [24..27] and has a higher priority than the ret var. What if the source has a local that's live only in [24..27] with 2 refs → pri 10000 = a TIE with the ret var → the lower allocno wins → the local was created first? Hmm! The allocno order = the pseudo creation order = the source order. If the local is declared BEFORE the ret var, it gets the lower allocno → it wins the tie → it takes $2 ✓✓ and the ret var takes $3 ✓✓!

Hmm, but a tie at pri 10000 with the same live range... let me think: a local `t` live in [24..27] with 2 refs (the set and the use):
```
t = ret;            /* hmm, this adds a copy instruction ✗ */
```
The copy would add an instruction ✗ (the target has no such copy).

Hmm. But maybe the copy is coalesced: `t = ret` where ret is the call result → the copy is the reload copy ✓ (that's exactly `move v1,v0`!). Hmm! So if the source is:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) { ... }
```
the call result pseudo → the variable `ret` — the copy at ins 24 IS the reload copy (because the call result pseudo is allocated $3 and the copy from the hard $2 is emitted by reload). Hmm! So the `move v1,v0` at ins 24 might not be a source-level copy at all — it's the reload copy from the call's return reg $2 to the pseudo's reg $3 ✓.

So the source's `ret` variable = the call result pseudo → allocated $3 in the target (because $2 was reserved by the pinned var).

So the lever-free requirement is just: $2 must be occupied in [24..27] by something else, OR the call result pseudo must be allocated $3.

The call result pseudo's allocation: it's a global? No — the call result is a local pseudo (set by the call). It prefers $2 (the return reg preference: "prefers v0" per the note). In the pinned version's table, r80 (the ret var) → v1 ($3) ✓ with pri 10000 — so the call result pseudo lost $2 to the pinned var ✓.

In my P1 version, the call result pseudo (r79?) → v0 ($2) ✓.

So: the call result pseudo's preference for $2 is overridden in the target by the pinned var.

Lever-free: we need another pseudo to take $2 in [24..27] with a priority ≥ the call result's.

Hmm! What about the RESULT_DECL? In the target, the RESULT_DECL is $2 with a live range of [28..39]... no overlap with [24..27] ✗.

Hmm, so even the target's lever-free-equivalent... ugh.

OK, wait. Let me reconsider: maybe the game's source had the RESULT_DECL set EARLY (a `return` before the call). Let me check: is there any early-exit path in the target's code? The first branch is at ins 25. So no.

Hmm, unless the game's source had a `return` in a block that gcc's crossjumping removed... but then the RESULT_DECL's live range would still start early? No — after crossjumping, the set moves with the block.

Hmm, hold on! What about this: the RESULT_DECL's live range in gcc 2.7.2 for a function where the result is set on all paths: gcc computes the live range of the RESULT_DECL as [the first set .. the end]. But if the RESULT_DECL is set in a block that's NOT reachable... no.

Let me look at the target's .greg (pinned) to see the RESULT_DECL's live range: the table said r73: refs 3, live 4. Live 4 = 4 insns. Hmm, so the RESULT_DECL's live range is [ins 36..39]-ish — SHORT even in the pinned version ✓ (the pinned var holds the value; the RESULT_DECL is a copy of it... hmm, but then the copy `move $2, $2` is elided ✓).

OK, so in the pinned version the RESULT_DECL is a pseudo in $2 whose live range is short, and the PINNED var (a hard reg) holds the value across the function ✓.

So the target's $2 reservation comes ONLY from the hard-reg pin. There's no lever-free way to have a hard reg...

=> Item 2 is a WALL (the pin reserves $2 for the whole function; lever-free, the call result takes $2).

Hmm, but wait! What if a LOCAL pseudo could be given $2 by the LOCAL allocator with a priority higher than the call result's? The call result pseudo: pri 10000, refs 2, live 2, blk 1. Hmm, from the table (my P1 version): r79 (blk 1), r82 (blk 2), r84 (blk 2) — all pri 10000, refs 2, live 2.

Hmm, interesting: three pseudos with pri 10000 (the call result, the mask temp, ...).

To beat them, a local needs pri > 10000 → refs/live > 1 → e.g. refs 2, live 1 → 20000 ✓ (a pseudo live in ONE insn with 2 refs!). Hmm, what pseudo is live in 1 insn? E.g. a copy `t = ret` — hmm.

Hmm, what about the RESULT_DECL with refs 3, live 3 = 10000 → a TIE with the call result (pri 10000)! And in the tie, the lower allocno wins → the RESULT_DECL (r73) has a lower allocno than the call result (r79) → the RESULT_DECL wins $2 ✓ — but only for its live range [36..39]; the call result then takes... $2 is free in [24..27] → the call result takes $2 anyway (the allocator assigns per pseudo, and $2 can be reused for non-overlapping ranges!).

Hmm!! That's the key: $2 is assigned to BOTH the RESULT_DECL (live [36..39]) and the call result (live [24..27]) — legal since they don't overlap!

So in the lever-free version, the call result takes $2 in [24..27] ✗ (the target has $3).

For the target, the call result must NOT take $2 → $2 must be occupied in [24..27] → the pinned var does that.

So we need a pseudo live in [24..27] (or spanning it) with a priority ≥ the call result's (10000) and a lower allocno.

The call result's allocno (r79 in mine) — its pseudo is created at the call site. A pseudo created EARLIER (a lower allocno) with pri ≥ 10000 and live in [24..27]...

The RESULT_DECL (r73, created first) has pri 10000 ✓ and a lower allocno ✓ — but its live range is [36..39] ✗.

So: if the RESULT_DECL's live range covered [24..27], it would take $2 there and the call result would take $3 ✓✓✓.

=> I need the RESULT_DECL to be SET before ins 24. The RESULT_DECL's sets = the `return` statements. So the source needs a `return` before the call!

Hmm, what if the source has a `return` that produces NO extra instructions? For example, if the source's structure is:

```
int result;
result = 0;    /* hmm, this is a local, not the RESULT_DECL */
```
✗.

Hmm, what about the RESULT_DECL being set by an early `return 0;` in a block that is later merged? E.g.:

```
if (param_1 == 0) {
    return 0;      /* an early return */
}
```
✗ — adds a branch + a move.

Hmm. Unless the early return is in a block whose condition is provably false... then gcc removes it (no set) ✗.

Hmm, what about a `return` inside a loop that never executes? no loop.

Hmm, what about the ORDER of the returns: what if the source's structure is:

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return byte != 0x15;
    }
}
return 0;
```
(2 returns: the value one and the final 0). The RESULT_DECL's sets: the value return (ins 29-33) and the final 0 (ins ~34) → the live range = [29..39] → doesn't cover [24..27] ✗.

What if the source has the "return 0" FIRST (early) — e.g.:
```
if (param_1 == 0) { return 0; }   ✗ extra code
```

Hmm, what if the early return is the `return 0` at the END of the function but the function's structure puts it BEFORE the call in the RTL? No.

OK, so item 2 = WALL (sched1-hardreg-sink / the $2 reservation). The best lever-free = 6.

Hmm, but hold on. Let me reconsider the priority numbers: the call result pseudo has pri 10000, refs 2, live 2, blk 1. What if I make the call result's live range LONGER (live 3 → pri 6667) so that a local with pri 10000 (refs 2, live 2) beats it? Which local has pri 10000, refs 2, live 2? In the table: r79, r82, r84 (all the call-result-related pseudos). Hmm, and r73 (the RESULT_DECL) has pri 10000 (refs 3, live 3) ✓ — a tie with the call result (10000) → the lower allocno (r73) wins ✓.

So if the call result's pri dropped below 10000 (live > 2), the RESULT_DECL would win the tie... but the RESULT_DECL's live range is [36..39] → $2 is still free in [24..27] → the call result would take $2 anyway (the allocator can share $2 for non-overlapping ranges). Hmm, right: the allocation isn't "first come first served for the whole function" — it's per live-range interval. So the RESULT_DECL having $2 doesn't prevent the call result from having $2 in a non-overlapping range.

Therefore, the ONLY thing that matters is whether some pseudo is live in [24..27] and gets $2.

Hmm, so what if the local `result` (nopin) were live in [24..27]? It is (it's set at ins 24-ish: `result = 0`) — but it got $3 because of the priority.

So: raise the local `result`'s priority above the call result's 10000. pri = refs*10000/live. The local's live range is long (15) → pri ~1333 ✗.

Unless the local's live range is SHORT. Hmm: what if the local `result` is set right after the call and returned immediately?

```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = byte != 0x15;
        return result;
    }
}
return 0;
```
The local `result` is live [29..33] → live 4, refs 2 → pri 5000 ✗ (still < 10000).

Hmm, and this shape has 2 returns (the RESULT_DECL's refs 2 → pri 2*10000/live).

Hmm, so the call result's pri 10000 (refs 2, live 2) is hard to beat: a local needs refs*10000/live > 10000 → refs > live. E.g. refs 3, live 2 → 15000 ✓. A pseudo live in 2 insns with 3 refs: e.g. a variable used 3 times in a short range:

```
b = *(u8 *)((char *)buf2 + 6);    /* the byte */
```
used once → refs 2, live 2 → pri 10000 (a TIE) and its allocno: if `b` is declared BEFORE `ret`, its allocno is lower → it wins the tie → $2!! But then the ret var → $3 ✓✓ and the byte load would be in $2 (the target has `lbu v0,30(sp)` = $2 ✓✓!!).

Wait, the target's byte load IS in $2 (`lbu v0,30(sp)`) ✓ and the final comparison in $2 ✓. So in the target, $2 holds: the call result (ins 24-27 is $3 though), the byte load (ins 29), etc.

Hmm, in the target $2 is used for: the byte load (ins 29), the xori (31), the sltiu (33), the zeros (28, 34). And $3 for: the call result (24-27) and the mask.

In our P1 version: $2 = the call result (24-27), then the byte load (29+?) — hmm, the diff showed mine[29..31] matched the target's ins 29-31 ✓ (`lbu v0,30(sp)`, `nop`, `xori v0,v0,0x15`) — so in ours, $2 = the byte load too ✓ (sequentially after the call result died).

So the difference is just the call result's reg.

So: I need the call result pseudo to be allocated $3. The call result pseudo is created at the call; its priority is 10000 (refs 2, live 2). To beat it, another pseudo must have a higher priority AND overlap [24..27].

Candidates in [24..27]: the mask temp (r82? refs 2, live 2, pri 10000, blk 2) — hmm, the mask temp IS in [26..27] and has pri 10000 (a tie with the call result) → the lower allocno wins. In ours, the mask temp got $2 too? Hmm, the diff showed mine[25] `andi v0,v0,0x8000` → the mask is computed into $2 (the same reg as the call result — the andi is in place) ✓ — so in ours, the mask temp was coalesced with the call result ✓ (the target has the mask in $3 = the call result's reg ✓ — same, just a different reg).

OK so in the target: the call result AND the mask temp are both in $3 (coalesced) ✓, and in ours they're both in $2 ✓.

So the fix: the call result pseudo must not get $2. Its pri is 10000 (the max for refs 2, live 2). A pseudo with pri > 10000 must exist and overlap [24..27]... but which? The only pseudos there are the call result and the mask temp.

Hmm! What if there were a THIRD pseudo in that range with a higher priority? E.g. if the source had a variable live in [24..27] with 3 refs.

Hmm, e.g.:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return byte != 0x15;
    }
    return 0;
}
return 0;
```
Hmm.

What if the source tests `ret` THREE times? E.g.:
```
if (ret != 0 && ret != 0 && (ret & 0x8000) != 0)  /* the redundant test → extra insns ✗ */
```

Hmm.

What if the source used `ret` in a way that creates a copy:
```
t = ret & 0x8000;    /* t: refs 2 (set+use), live 2 → pri 10000, and its allocno is lower if declared first */
if (t != 0) { ... }
```
Then the mask is computed into `t` (a separate pseudo) → the target's `andi v1,v1,0x8000` (in place) ✗ — the target's andi writes into the same reg as the call result. Hmm, but with `t` declared BEFORE `ret`, `t` (allocno lower, pri 10000 tie) would win $2 → the call result → $3 ✓ and the mask temp `t` → $2 → the code would be `andi v0,v3,0x8000`? Hmm, the target has `andi v1,v1,0x8000` (in place). ✗ — a different instruction.

Hmm, unless gcc computes `t = ret & 0x8000` with the destination being a temp and then coalesces... the andi's destination would be `t` → `andi $2,$3,0x8000` ✗.

OK. Hmm.

Let me try a slightly different approach: maybe the game's source had the mask test as `if ((ret & 0x8000) == 0) return 0;` — hmm, same.

What if the game's source had TWO variables: `ret` and a copy used for the mask? The target's `andi v1,v1,0x8000` (in place, v1 = the call result's reg) suggests the mask is computed into the call result's reg ✓ — i.e. the source is `if ((ret & 0x8000) != 0)` ✓.

OK. So item 2's wall is: the call result pseudo (pri 10000) always wins $2 lever-free; the ROM needs $2 reserved for the whole function (the pin).

Hmm, but hold on: what if the call result's live range were LONGER (so its pri drops) AND the RESULT_DECL's live range covered [24..27]? Then the RESULT_DECL (r73, pri 10000, lower allocno) would win $2 in [24..27] ✓ and the call result → $3 ✓.

The RESULT_DECL's live range covers [24..27] iff the RESULT_DECL is set before ins 24 — i.e. an early return ✗ (instructions).

Hmm, alternatively: the RESULT_DECL's live range could be extended by gcc if the RESULT_DECL is "live at entry" — hmm.

Hmm, what if the function's return value is used... no.

OK, let me consider the possibility that the early return can be FREE: what if the source is:

```
int result;
result = 0;
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) { ... }
return result;
```
The local `result` is set BEFORE the call → live [20..39] → pri = 2*10000/19 = 1052 → it gets $3 (or $4) ✗ (the call result still gets $2).

Hmm.

What if the local `result` is live across the whole function AND has many refs? E.g. if `result` is read multiple times:
```
result = 0;
ret = f();
if (ret != 0) { if (...) result = byte != 0x15; }
if (result == 0) return 0;    /* an extra test ✗ */
return result;
```
✗.

OK, I'm now confident item 2 is a WALL. Best = 6 (P1/P2/U1/U5/U6 etc.).

Let me count the tries for item 2: existing 12 (vM2, vM4, vM5, vM6, vP1, vP2, vQ1, vQ2, vR2, vR3, vS1 = 11 + nopin + orig = 13) + mine (t0_stub, T1, T2, T4, T6, T9, U1, U3, U5, U6 = 10) = 23. I need ≥30 for a WALL. Let me score the remaining existing ones (11 files) to reach 34+.

Let me batch-score the existing item 2 candidates.

Actually, time is a concern: I'm ~1h40m in with 3 items left. Let me be efficient: score the remaining existing candidates for item 2 in one batch (11 scorings, ~15 s), then move to items 3-5 with a leaner approach (each: stub listing + the best existing diff + a few variants).

Let me do that.
