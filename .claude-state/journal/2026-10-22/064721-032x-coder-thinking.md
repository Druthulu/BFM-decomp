---
ts: 2026-10-22T12:47:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_d6o5oUBVO8AJJfqeG5AB
---
Excellent! Both w2 and w3 score 0! The dead-reset trick works: giving `it` a second set keeps the base in a register.

Now, which one is legitimate? w2 (`it = 0;` before the base assignment) vs w3 (`it = 0;` after p = it + 0x658C).

Hmm, "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". A dead store `it = 0;` is not an identity statement — it's a dead reset, which the project's cookbook §373 explicitly endorses ("DEAD-RESET CSE-BREAKER": "pb=&buf; call(pb); pb=0; before every site"). And G15 used it for a MATCH: "launder | func_8018A180 | MATCH — DEAD-RESET CSE-BREAKER (§373): pb=&buf; call(pb); pb=0; before every site; cse's &buf address class breaks, so all 6 sites rematerialise addiu aN,sp,56".

Hmm, but wait: in that G15 case, the dead reset was used to break the cse *address class*, a different mechanism. Here the mechanism is "the pseudo has 2 sets → reload keeps it in a register (no rematerialization)".

Which is better/cleaner? w3 puts `it = 0;` after the use of `it`; but `it` is then reassigned to D_801202A0 at `test:`. Hmm, in w3 the dead store is at the top of the function, before the `goto test`. Fine.

Hmm, but is w2's `it = 0;` before the base assignment "dead"? Yes, overwritten immediately.

Which is more likely the original source? Neither, probably. But the task only requires a lever-free body that scores 0, using real C moves. A dead store is a real C move (the project's own §373 technique).

Hmm, but is a dead store "adding a lever"? No lever kinds: pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. A dead store is none of these.

But hold on — I should double check the "no identity launder" rule: `it = 0;` is not an identity (it changes the value). It's dead code that the compiler keeps as a second SET. Fine.

Now, which of w2/w3 is safer? Let me think about "does the dead store survive as a second set?" Both gave score 0, so yes.

Hmm, one concern: the dead store `it = 0` might make the frame slot non-eliminable → stack traffic? No: score 0 means the instruction stream is identical (19 ins, no stack ops). The dead store is optimized away but the *quantity* effect remains at the RTL level.

Now, let me double check that this is really removing the launder kind: yes, w2/w3 have no asm at all.

Also need to check: does the whole OBJECT stay byte-identical (the bank judges the whole object)? For headers, each includer's object contains other functions; our change only affects this function. But the header is included in 141 TUs, and the object must be byte-identical to the baseline for the whole object to be judged IDENTICAL. The header's function must be byte-identical (which score 0 confirms) — but the rest of the object is unchanged since we only changed this function's body. However! The `it = 0;` dead store — does it affect anything else in the object? No.

But wait: does the dead store affect the *stack frame size*? The function has no frame in either version (score 0 = same instruction stream, and the frame is part of the prologue which is in the instruction stream). Since score 0 means the function's instructions are identical, the frame is identical.

Now the header rule: "MATCH only if score 0 on every includer (tryinc.py k = 0..n-1)". 141 includers × ~1s = ~2.5 min. That's affordable. But is it needed? The score is per-includer; the function's code could differ per includer if the includer's context changes register allocation (it shouldn't — each function is compiled independently) — but the header might be included in a TU where the surrounding code affects... no, register allocation is per-function. However, the *address materialization* could differ if the includer defines a macro that changes the type of s32 etc. Unlikely but the rule requires checking all.

Let me run the 141-includer check for the winning candidate. I'll write a loop over k=0..140 using tryinc.py.

But careful: tryinc.py calls delever_search's main with the rotated recipes. Each call takes ~1s → 141s per candidate. Acceptable for the final winner.

Before that, let me continue with the other items and do the 141-check at the end for each item's winner (or do it now for item 2 to validate the approach). Let me do the 141-check now for w3 (I prefer w3? let me think).

Hmm, w2 vs w3: In w2, `it = 0; it = (s32)D_80120194;` — the dead store is immediately overwritten. In w3, `it = (s32)D_80120194; p = it + 0x658C; it = 0;` — the dead store comes after the use.

Both work. Which is more "natural"? Hmm. Honestly, for the MOVE line I'd describe: "the base pseudo needs a second SET so reload keeps the address in a register (no rematerialisation): a dead reset `it = 0;` gives the variable two sets".

Hmm, wait. Actually, let me reconsider — maybe there's an even more natural spelling that achieves the same: e.g. `it = (s32)D_80120194; p = it + 0x658C;` where the base is used twice.

Let me think about a formulation where the base's address is naturally used twice... The C750 pattern: `base` used in `p = base + 0x6480` and `if (p != base)`. In C2D0, the equivalent would be a comparison with the base — but there is none.

Hmm! What about this: the loop could be written as a do-while over the base:

Actually, hmm, hold on. What if the ORIGINAL source was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
```
with `it` REUSED for the loop start:
```c
test:
    it = (s32)D_801202A0;
```
Hmm no.

What if the original was:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
```
and the original compiler produced this because the ORIGINAL source had `it` as a *pointer* variable (`u8 *it`), so `p = it + 0x658C` where `it` is a pointer → the front end's plus_expansion with a *pointer* base that's a variable → it produces reg + const (not an address), and the load of `it`... same as before.

OK, let me also consider: maybe the original had the base used twice like this:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
Hmm what if `p` were computed as `p = it + 0x658C` where `it` is the SECOND symbol? No.

I'll go with the dead-reset. But hmm, let me reconsider the rules once more:

"Real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, `&&`/`||` folds, pointer reuse)."

The catalog doesn't mention dead stores! Hmm. "pointer reuse" is in the catalog — i.e., reusing a variable for two purposes. The dead reset isn't in the catalog. Hmm. But the project's own cookbook §373 (DEAD-RESET CSE-BREAKER) was used for a MATCH in G15 — that's a project-endorsed technique, and the brief says "no new lever of any kind" (a dead store isn't a lever) and "identity-statement launders ... do NOT count as a crack" (a dead store is not an identity statement).

Hmm, but is a dead store an "identity statement launder"? No: it changes the value.

Still, to be safe, maybe I should prefer a formulation that's in the catalog. Let me think about "pointer reuse": reuse a pointer variable for two purposes so it has 2 sets naturally!

In C2D0, `it` is already reused (base then loop pointer). The problem is that the *first* set is a single constant.

What if we introduce the base via a variable that's ALSO used for the loop? E.g.:

```c
s32 p;
s32 it;
it = (s32)D_80120194;   /* set 1: base */
p = it + 0x658C;
it = (s32)D_801202A0;   /* set 2 */
```
The pseudo for set 1 is separate from set 2. GCC creates 2 pseudos (or 1 pseudo with 2 sets?). In GCC 2.7, a local variable in memory: the front end emits stores to the frame slot; the loads are separate pseudos. The load after store 1 has quantity 1 → rematerializable.

Hmm! Unless the *variable* is a register variable... but "no register vars".

OK, what about this alternative: **use the same variable for the base and the loop pointer, where the base's load is followed by another store** — that's the case already. And the quantity of the load pseudo: in cse, when a load is replaced by the value of a preceding store, the pseudo gets the store's quantity? The quantity of the load pseudo = the number of sets of that pseudo. The load pseudo is a fresh pseudo with 1 set (the load) → quantity 1 → but its *value* is known (the constant) via cse's "the load is equivalent to the store's value" → so it's reg_equiv to the constant → rematerialized.

With the dead store, the load after store 1 is still equivalent to store 1's value... hmm, then why did w2/w3 work? Because the DEAD STORE to the same slot invalidates the cse equivalence: cse's memory handling sees the slot's value change (to 0) after the use, so the load's "known value" is invalidated? Hmm, in w3 the dead store is AFTER the use, so the use's value is still known...

Hmm, in w3: stores: [addr], [0]; loads: after store [addr] → load L1 (used for p). cse: the last store to the slot before L1 is [addr] → L1 = addr constant. Then the store [0] happens after L1 → cse removes the dead store? If cse removes it, we'd be back to the fold. But the score is 0, so something else happened.

Maybe: the presence of 2 stores to the same slot makes the load pseudo's quantity 2? Hmm.

Whatever the mechanism, it works. But I want to understand it enough to be confident it's robust (e.g. across all 141 includers) and to write a good evidence line.

Actually, let me look at the cc1 RTL dump to see. The brief mentions tools/cc1_dumps_tu.sh for TU dumps. But the disk cap and time... Let me consider: is understanding necessary? For the evidence line I need "gcc pass + mechanism ≤ 140 chars". "gcc pass" probably means the command that passes (the scoring command). E.g. "delever_search --try src/shared/ov/func_8012C2D0.h func_8012C2D0 w3.c --body: score 0".

I'd like a brief mechanism description: "the base's 2nd SET (dead reset) keeps reload from rematerialising the address into the addiu".

Let me now check the RTL quickly with cc1 dumps to confirm the mechanism (this is cheap and useful). Let me check tools/cc1_dumps_tu.sh usage.

Actually, let me prioritize: 4 items, ~20-30 min each. Item 2 is nearly done (need the 141-includer check). Let me first quickly check the other items' leverage with the same trick, then do the includer checks.

Let me look at item 3 (C750): the launders are in the else branch:
```c
    } else {
        it = (s32)D_80120194;
        [launder]
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        [launder]
        if (it == p) goto zero;
    body:
        ...
```
Note: in C750, the else branch's `it` (base) is used once for p... AND the `copy: p = it;` uses `it` (the loop pointer). Same as C2D0.

And the second launder (on the D_801202A0 assignment) — in C2D0 that one was fine without the launder (the value is used as a MEM base). In C750 the same.

So for C750, try: remove both launders and add a dead reset for the base.

Also C750 has the IF branch with `s32 base = (s32)D_80120194; p = base + 0x6480; if (p != base) {...}` — no launder there (base used 3 times → reg). Good, consistent with my theory!

Wait, this is a great confirmation: C750's IF branch has NO launder and the base is used 3 times. The ELSE branch HAS a launder and the base is used once. So the mechanism is confirmed: the number of uses of the base determines whether GCC keeps it in a register.

So for C2D0, the original source must have used the base more than once... OR the original had a different structure. Hmm! Since C750 (the same family) uses `base` 3 times in the if-branch, maybe C2D0's original was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
```
Hmm.

Whatever. Let me now proceed with the dead-reset approach for all items, but first let me reconsider whether a *natural* C spelling exists that gives the base 2 uses in C2D0.

IDEA!!! What about this: in C2D0 the loop could be written as:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
```
What if instead the source computed p differently: the loop scans from D_801202A0 upward to p. What if the source were:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
Yeah I keep going in circles.

Hmm, hold on! What about the possibility that the base is used twice in the ORIGINAL because of the `copy: return it;`?! Look at C2D0's copy block: `return it;` — in the target, `move v0,v1` where v1 = the loop pointer. But WAIT: what if in the original, the copy block returned the BASE (D_80120194) rather than the loop pointer?! Then the base would be live across the whole function → definitely a register!

Let's check the target: at 418c `move v0,v1`. The path to 4188/418c is from 41a8 (beqz v0 → 4188). At that point v1 = the loop pointer (the address of the zero entry). So the returned value is the loop pointer, not the base. Confirmed by the semantics: the function returns the address of the found zero entry.

Hmm, but hold on: is that right? Let's re-derive: `body: if (*(u16*)it == 0) goto copy;` — when the entry's u16 is 0, it returns `it` (the address of that entry). Yes.

So the base is used once. Therefore the original source must have had something else. Since the target shows the base in v1 (a callee-saved reg $23) — hmm, v1 = $23. And the loop pointer also uses v1. So the base's register is shared with the loop pointer.

Hmm, that raises the question: why would GCC put the base in a callee-saved reg rather than a0? Because the register allocator chose v1 for both the base pseudo and the loop pointer pseudo (their live ranges don't overlap: base live 4178-4184, loop pointer live 4190-418c... wait, the loop pointer v1 is live from 4190 to 418c (the copy block) — they overlap? Base: 4178-4184. Loop ptr: 4190-41b4 and 418c. No overlap. So both can be v1.

But in MY compile, the base was folded away, so the only v1 use is the loop pointer. And the fold also changed the compare order (beq a0,v1 vs beq v1,a0) — because in the target p is in a0 and the loop ptr in v1: `beq v1,a0` (first operand = the loop pointer). In mine, p is in a0 and the loop ptr in v1 → `beq a0,v1`. Hmm, the operand order in the beq comes from the source `if (it == p)` → beq it, p → it=v1, p=a0 → `beq v1,a0`. In mine: it = v1 (loop ptr), p = a0 → should also be `beq v1,a0`! But mine shows `beq a0,v1`.

Hmm! That means in my compile, GCC swapped the operands. Why? Because in mine, `it` and `p`... hmm, `it` (the loop pointer) is v1 and `p` is a0 → the source `it == p` → beq v1,a0. But mine emitted beq a0,v1. So in mine, the loop pointer was in a0 and p in v1?? Let's re-read my candidate:

```
4190: lui v1, hi(D_801202A0)
4194: addiu v1,v1,lo
4198: beq a0,v1,41bc
41a0: lhu v0,0(v1)
41b0: addiu v1,v1,268
41b4: bne v1,a0,41a0
```
So the loop pointer is v1 and p is a0 → `beq a0,v1` means the compare is (p, it) — operand order swapped vs the source (it, p). GCC's `reverse_condition`/compare optimization may swap operands for better branch prediction (mips `beq` is the same cost). Actually GCC's final comparison reversal (in `final.c`/`jump.c`?) can swap the operands of an equality compare. In the target, it's `beq v1,a0`.

Anyway, with w3 the score is 0, so all this matched.

Let me now check: which of w2/w3 to keep? Both score 0. I'll keep w3 (dead reset after the use) — hmm, or w2? Let me think about which is less likely to be seen as "an identity launder". Neither is.

Hmm, actually — maybe I should think about whether there's a formulation where the base naturally has 2 uses, which would be the most faithful. Let me try: what if `p` is computed and then the loop compares against the base as well? Not semantically equivalent.

I'll go with the dead reset. But let me pick the variant that reads most naturally as "the original":

w3:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    it = 0;
```
Hmm, "it = 0" then later "it = (s32)D_801202A0" — the dead store is redundant-looking.

w2:
```c
    it = 0;
    it = (s32)D_80120194;
    p = it + 0x658C;
```
Also redundant-looking.

Alternatively, a "pointer reuse" formulation: use a separate variable for the base so that IT has two sets naturally? E.g.

```c
s32 base;
s32 it;
base = (s32)D_80120194;
p = base + 0x658C;
base = 0;   /* dead */
```
same thing.

What about making the base's second set be a *meaningful* one? Like:
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
→ change to
```c
it = (s32)D_80120194;
p = it + 0x658C;
it = p;      /* NOT dead: it is reassigned later anyway */
```
Hmm! `it = p;` — a real second set whose value is used? No, `it` is reassigned at test: so `it = p` is dead too. But it's not an identity statement (it's a copy). Hmm, but that's "an identity-ish copy".

I think the cleanest and most defensible is a dead reset to 0, per the project's §373 DEAD-RESET technique (endorsed by G15's MATCH). Let me check the cookbook for §373 to cite it correctly.

Let me grep the cookbook index.
