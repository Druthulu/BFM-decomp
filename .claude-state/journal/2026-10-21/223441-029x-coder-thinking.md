---
ts: 2026-10-22T04:34:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_gapMp4vUNRoVJUWG9f7o
---
Now write variants. Base text pieces:

```
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    buf1[0] = 0;
    buf1[1] = 0;
    buf1[2] = 7;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf1, buf1);
    buf2[0] = 0;
    buf2[1] = 0;
    buf2[2] = (short)0xffe8;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf2, buf2);
    ret = func_80133784(1, buf1, (int)buf2);
    ...
}
```

Let me write a generator script under .run/P40/T11/G08b/ (allowed: write only under G08b). Actually "write only under .run/P40/T11/G08b/ plus appends to moves.md". A generator script under G08b/ is fine.

Let me write the variants directly with Write tool (a few files), then score.

Variant w1: block decl after call, init 0:
```
    ret = func_80133784(1, buf1, (int)buf2);
    {
        int result = 0;
        if (ret != 0) {
            if ((ret & 0x8000) != 0) {
                result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
            }
        }
        return result;
    }
```
Variant w2: block decl after call, no init, both branches:
```
    {
        int result;
        if (ret != 0) {
            result = 0;
            if ((ret & 0x8000) != 0) {
                result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
            }
        } else {
            result = 0;
        }
        return result;
    }
```
Variant w3: top decl result, assigned right after the call:
```
    int result;
    ...
    ret = func_80133784(1, buf1, (int)buf2);
    result = 0;
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
```
Variant w4: block decl with init, but the boolean expression assigned via a temp:
```
    {
        int result = 0;
        int t;
        if (ret != 0) {
            t = *(unsigned char *)((char *)buf2 + 6) == 0x15;
            if ((ret & 0x8000) != 0) result = t;
        }
        return result;
    }
```
Hmm, that changes the code (the lbu would be hoisted). Skip for now.

Variant w5: `ret` declared after the call too (so ret's pseudo number is later) — no, ret holds the call result; its pseudo number doesn't matter much.

Hmm wait, actually important: the tie-break is on the pseudo number of the ALLOCNO, and the local `result` in w1/w2 is created after the call → higher number. But also, in w1/w2 the local `result` conflicts with the call-result pseudo (overlapping live ranges) → so one of them takes $2 and the other $3, decided by pri then number.

The local `result`'s pri: refs and live. In w2: refs = def0(then), defbool, def0(else), use(return) = 4; live = from first def (ins ~25) to the return (ins ~33) ≈ 8 → pri = 4*10000/8 = 5000 < 10000 → the call result still wins $2 → then the local gets $3. Damn.

Unless the live range is shorter. Hmm, in w2 the local's live range starts at the first def. If the def is inside the branch, its live range starts there.

pri = refs*10000/live. To beat 10000 we need refs > live. With live ~8 and refs 4, no.

Hmm! But hold on: how is "live" counted in gcc 2.x? It's the "live length" in the allocno — measured in instructions (or in "life length" units). If the local `result` is live from ins 25 to ins 33 → live ≈ 8-9.

To get refs > live we'd need e.g. refs 9 live 8. Each extra reference adds a ref but the live range doesn't grow. Can we add references to `result` without changing the code? E.g.:

```
result = 0;
if (ret != 0) { if (ret & 0x8000) result = X; }
else { result = 0; }
if (result) { }        /* extra use → extra ref */
return result;
```
An extra use of `result` would change the code (a test) unless it's dead. gcc's DCE would remove `if (result) {}`? The value is used → not dead, but the branch has no effect... gcc might keep the test (it's not pure). Actually `if (result) { }` → the test is a use; gcc's flow analysis would keep the conditional jump (empty body) — it changes the code. Bad.

Alternative: use `result` in a way that produces no code: e.g. `result = result + 0;`? That's an extra copy (adds an insn) but adds refs (3 more). Hmm: `result = result + 0;` → gcc folds to a copy → the copy may be coalesced but still a ref. Actually gcc's fold would remove `result + 0` → `result = result` → then the copy is a no-op but the ref count... after folding, the assignment disappears entirely (self-assignment is dropped by the fold in the RTL? `x = x` → no-op, removed).

Hmm.

What about the expression `result = result ? result : 0;`? Ugly.

Let's think differently: increase the CALL-RESULT pseudo's live range instead, so its pri drops below the local's.

The call-result pseudo's live range = from the call to its last use. Currently the last use is the `andi` (ins 26). If the local `result`'s pri is 5000 and the call result's is 10000, we need the call result's pri < 5000 → refs*10000/live < 5000 → live > 2*refs. With refs 2 → live > 4.

How to extend the call result's live range without changing the generated code? Extend the live range by using `ret` later... changes the code.

Hmm. But wait: maybe the live range of the call-result pseudo in the current form is longer than I think, and the "live 2" from the dump refers to something else.

OK, let me stop theorizing and get the data: run the cc1 dumps for the current best candidate and read the alloc table to see the actual pri/refs/live of the relevant pseudos. The notes say cc1 dumps were used before (tools/cc1_dumps_tu.sh + tools/alloc_table.py). The constraint says dumps go under my item dir and are deleted after reading. Disk is tight (4 GB free).

Let me look at those tools' usage.

Actually, the notes already give the dump for the lever-free and pinned cases:
- lever-free: r73 = RESULT_DECL (pri 10000, refs 3, live 3, prefers v0), call-result pseudos r79/r82/r84 (pri 10000, refs 2, live 2).

Hmm interesting: the lever-free dump has the RESULT_DECL at pri 10000 refs 3 live 3 → 3*10000/3 = 10000 ✓. And the call-result pseudo refs 2 live 2 → 10000 ✓. Both tie at 10000 → the higher pseudo number (r79 > r73) wins → the call result gets $2. ✓ consistent with observation.

- pinned: r73 = pri 7500, refs 3, live 4 → 3*10000/4 = 7500 ✓. Call-result pseudo r79: pri 11428, refs 4, live 7 → 4*10000/7 = 5714 ✗. Hmm, doesn't fit. Maybe that dump was of a different body (the notes mention item4/item4b). 11428 = 8*10000/7 = 11428.57 → refs 8, live 7! Or 4*20000/7. So maybe refs 8.

Anyway pri = refs*10000/live seems right (in gcc 2.x: `allocno_priority` = REG_FREQ_PRIORITY-based? Actually the formula in gcc 2.x global.c is:

```
static int
allocno_priority (n)
     int n;
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* Priority is the number of references divided by the live range length */
  ...
  pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
```
Whatever, the empirical formula fits well: pri = refs * 10000 / live.

So the local `result` in nopin: what are its refs/live? It got $3. If pri = 5000 and the call result 10000, the call result wins. To flip we need pri(result) > 10000: refs > live.

Alternatively: reduce the call result's pri below the local's. The call-result pseudo's refs/live: 2/2 → 10000. If the call result's live range were longer (e.g. live 4, refs 2 → 5000) and the local's pri 5000 → tie → higher pseudo number wins → the call result (higher number) still wins. Hmm. Unless the local's number is higher (block-decl after the call).

Combined plan: local `result` declared AFTER the call (higher pseudo number) AND its pri ≥ the call result's pri.

How to make the local's pri higher? refs > live. E.g. the local with refs 4 and live 3.

Hmm, how about making the local's live range SHORT: define it late and use it soon. In the target, the value is computed at the end (lbu/xori/sltiu) and returned. The local `result`'s live range in nopin covers from the branch to the return.

What if the structure is: compute everything into the local right before the return? Like:

```
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            return *(unsigned char *)((char *)buf2 + 6) == 0x15;   /* direct return */
        }
        return 0;
    }
    return 0;
```
That's win.c: the RESULT_DECL is the $2 holder (refs 3, live ~10?) — hmm, the RESULT_DECL is created at function entry → LOW pseudo number → loses ties. Its pri: refs 3? live 3 → 10000 (per the dump) — hmm the dump said refs 3, live 3 → 10000, which ties with the call result (10000) but the call result has a higher number → wins $2. And the RESULT_DECL gets $3?? But in win.c the boolean is computed into $2 (lbu v0, xori v0)!

Hmm, that contradicts. Unless in win.c the RESULT_DECL is in $2 and the call result also in $2 (they don't overlap in live range: the call result dies at ins 26, the RESULT_DECL is live from ~27).

Right — the RESULT_DECL in the direct-return form: its first def is at the `return 0` inside the branch (target ins 28) → live from ins 27 → no overlap with the call result [24..26] → both can be $2. But then the call result in $2 means the tests are on $2 (v0) — matches mine[24] `beqz v0`. ✓.

And in the nopin form, the local `result` is live from ins 25 (its first def, inside the then-branch) → overlaps the call result [24..26] → conflict → one gets $3. The local's pri (refs 4, live 8?) = 5000 < 10000 → the call result wins $2, the local gets $3, and the RESULT_DECL (live from ins 27, prefers v0) gets $2 with a final copy `move v0,v1`.

So to get the target, we need the local `result` (or whatever holds the value) to be live at [24..26] AND win $2 over the call result.

Wait, but in the TARGET, is anything live at [24..26] besides the call result? The pinned `result` is in $2 but its live range starts at ins 27 or so. So the call result's pseudo is $3 simply because $2 was reserved by the pin.

So for a lever-free body, we need the call-result pseudo to be pushed to $3 by a conflict with a pseudo that wins $2.

Alternative: make the call result live LONGER so that its pseudo gets a different reg? No — $2 is free in [24..26] unless someone else wants it.

Hmm, what if the local `result` is live across [24..26] — i.e. defined BEFORE the tests? E.g.:

```
ret = call();
result = 0;             /* def right after the call: live from ins 24 */
if (ret != 0) { if (ret & 0x8000) result = X; }
return result;
```
Now `result` is live [24..33], refs: def0, defbool, use = 3, live ~9 → pri 3333 < 10000 → the call result wins $2 again. ARGH.

The local always loses because it has few refs and a long live range.

Unless... we increase the local's refs! How about assigning it in multiple places that all get merged? E.g.:

```
result = 0;
if (ret != 0) {
    result = 0;               /* redundant */
    if (ret & 0x8000) result = X;
}
```
The redundant `result = 0` might be removed by gcc's store merging (dead store) → no extra ref.

Hmm, what about the boolean expression being assigned to the local via a temp that increases refs?

Let me think about the pri formula more: pri = refs*10000/live. Maybe "live" is measured in a different unit (e.g., the number of instructions the allocno is live). If the local is live [24..33] = 9 insns and has 3 refs → 3333.

The call-result pseudo: live 2 (ins 24..26 = 2 units?) refs 2 → 10000.

To beat it, the local needs refs/live > 1 → e.g. live 3 with refs 4, or live 2 with refs 3.

Can we make the local's live range 2-3 instructions? Its live range must span from its def to its use. If the def and use are adjacent (e.g. def right before the return), the live range is tiny. E.g.:

```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = X;    /* def */
        return result; /* use */
    }
    return 0;
}
return 0;
```
Here the local `result` is defined and used immediately → live ~2-3, refs 2 → pri ~7000. Still < 10000. And the other paths return 0 directly (no local).

Hmm, but the structure differs: the local exists only in the inner branch. But `result` must be declared before use — could be at the top (low number) — the number matters for ties only.

pri 7000 < 10000 → the call result still wins $2 → no copy → mine[24] beqz v0 → score stays 6-ish.

To get pri > 10000 we need refs > live for the local. With a def+use adjacent, live might be 1-2 and refs 2 → pri 10000-20000. Hmm! If live = 1 and refs = 2 → pri = 20000 > 10000 → the local wins $2!

Interesting: a local defined and used immediately (live 1) with 2 refs → pri 20000.

But careful: the local's reg must be $2, and it must conflict with the call result (which is live at [24..26]). But in this variant the local is defined at ins ~28 (after the tests) → no overlap with the call result → no conflict → the call result can still be $2. We need the local to be live at [24..26] AND win $2.

Hmm, but if the local is live at [24..26] and wins $2, then the call result goes to $3 ✓. But then the final value must be in $2 — the local is in $2 ✓ and the RESULT_DECL copy would be coalesced into $2 ✓ (if the local's reg is $2 and the RESULT_DECL prefers $2 and they don't conflict).

So we need a local that is live at [24..26] (i.e. defined right after the call or before it) with high pri (refs > live).

A local defined right after the call and used at the return: live ~9, refs 3 → pri 3333.

Unless the local is defined right after the call AND used right after (then a second local carries the value to the return)? Two locals:
```
ret = call();
{
    int r = 0;              /* live [24..], def at 24 */
    ...
}
```
Hmm.

What about: a local defined right after the call, used immediately, and the RESULT value carried by another mechanism? E.g.:

```
ret = call();
if (ret != 0) {
    int r = (ret & 0x8000) != 0;   /* hmm changes code */
```

Let me think again about the exact target code and what C produced it. Target:
```
24 move v1,v0        <- copy of the call result into $3
25 beqz v1
26 andi v1,v1,0x8000 (delay slot)
27 beqz v1
28 move v0,zero (delay slot)
29 lbu v0,30(sp)
31 xori v0,v0,0x15
32 j
33 sltiu v0,zero,v0
34 move v0,zero
```
The value is computed into $2 at ins 29-33. The `move v0,zero` at 28 and 34.

Which pseudo is in $2 at ins 29-33? The pinned `result` ($2) — the boolean assignment. And the RESULT_DECL — coalesced with it.

In lever-free terms, we need a pseudo X in $2 live from ins 29 to the epilogue, and the call-result pseudo in $3.

$2 must be free for X during [24..26]? No — X's live range starts at ins 28/29 (after the tests). But $2 holds the call result at [24..26] in the target too! Wait: in the target, at ins 24 the copy `move v1,v0` moves $2 → $3, and then $2 is free (the raw call value is dead). So $2 is used for the call result only at ins 24 (before the copy).

So in the target, the call-result PSEUDO is in $3 and the raw hard reg $2 is dead after ins 24.

So the question: why did the call-result pseudo go to $3 in the target? Because $2 was reserved by the pin. In a lever-free version, $2 is not reserved; the pseudo just takes $2 (no copy).

To force the copy, we need the pseudo to NOT be in $2 — i.e., $2 must be occupied by another pseudo in the pseudo's live range [24..26], OR the pseudo must be forced elsewhere.

What occupies $2 in the target at [24..26]? Nothing (the pinned `result` is live from ins 28).

Hmm, so in the target, $2's occupancy doesn't force the call pseudo to $3 — the pin's hard-reg constraint does (the pinned pseudo is assigned reg 2 globally, so the conflict graph marks reg 2 as unavailable to the call pseudo? Actually the conflict is only where they overlap in live range... but the pinned pseudo's live range might be considered to span the whole function? The notes said "the hard reg $2 is reserved for the whole function").

OK so what lever-free mechanism could reserve $2 for the whole function? A variable live across the whole function → callee-saved reg → no.

Hmm, what about a variable that is live at [24..26] and gets $2 by priority? Then the call pseudo gets $3 ✓ and the boolean must ALSO be in $2 → so the SAME variable must hold the boolean value... but then it's live from before the call → callee-saved. Unless the variable holding the boolean is a DIFFERENT pseudo that also gets $2 — impossible, they'd conflict (both live at 28-33? the first is live [24..26], the second [28..33] → they don't overlap → they CAN share $2!).

So: X = a pseudo live [24..26] that wins $2 (pri > 10000) and dies at 26; Y = the boolean's pseudo live [28..33] that gets $2 (as $2 is free after 26).

For Y to get $2: Y is the RESULT_DECL (prefers v0) or the local `result`. In the direct-return form (win.c), the RESULT_DECL is live [27..epilogue] and got $2 ✓ (it's the boolean holder).

So we need X: a pseudo live across [24..26] with pri > 10000, and NOT conflicting with the RESULT_DECL (live [27..]).

What could X be? Something defined right after the call and dead right after the tests. E.g. the `ret` variable itself! In the current form, `ret` IS the call result's holder: `ret = func_80133784(...)` → the call-result pseudo IS `ret` (no copy). The copy appears when the call-result pseudo is not in $2.

Hmm, what if we introduce a SECOND variable: `int t = ret;` right after the call? Then `t` is a copy of the call result → t is live [24..26] and the call-result pseudo is live [24] (just the copy) → the copy `move vX,v0` would appear! And the call-result pseudo (live 1, refs 2 → pri 20000?) would win $2 → the copy becomes `move v1,v0`?? Hmm, wait: if the call-result pseudo is in $2 and `t` is in $3, the copy is `move v1,v0` — EXACTLY the target's ins 24!!

So the move: `t = ret;` — but then `ret` (or `t`) is used in the tests. The target tests on $3 = t. So `t` in $3 and the call-result pseudo in $2.

But hold on: in the target, the call-result pseudo is dead right after ins 24 (the copy), so its live range is 1 → pri = refs*10000/1. The copy pseudo `t` is live [24..26] → refs 2, live 2 → pri 10000. So the call-result pseudo (pri 20000 if refs 2) beats `t` (10000) → the call result gets $2 and `t` gets $3 → the copy is `move v1,v0` ✓✓✓ and the tests are on $3 ✓.

Wait, but this is exactly what happens in the current nopin form? No — in nopin, `ret` IS the call result holder (no separate copy), so the call-result pseudo = `ret`'s pseudo, live [24..26], refs 2, live 2, pri 10000, and it wins $2 → no copy.

With the extra copy `t = ret;`, the call-result pseudo has live 1 (dies at the copy) and refs 2 (the call def + the copy use) → pri 20000 → wins $2 → and `t` (live [24..26], refs 2, live 2, pri 10000) gets $3 ✓.

Hmm, but wait: does gcc keep the copy `t = ret`? It might coalesce `ret` and `t` (both are the same value, copy propagation) — gcc's copy propagation (cse) would eliminate `t = ret` and substitute t with ret → back to the same situation. Hmm. But cse's copy propagation requires the copy to be safe; `ret` is not modified after, so cse would propagate. Unless `ret` has 2+ uses (the notes from another shard: "the copy through an s16 temp escapes cse2's equivalence class").

Hmm! But if cse propagates t←ret, then `ret` (the call-result pseudo) is used in the tests directly, live [24..26].

To defeat cse's copy propagation, the copy must go through a different type (e.g. s16) or the value must be modified. But the target's copy is a plain `move v1,v0` — the same type.

Hmm, but here's the thing: does gcc's cse actually propagate `t = ret` when `ret` is a local variable that's not address-taken? Yes, likely (local var copy propagation).

Unless `ret` is volatile? no.

OK but wait — maybe there's a better route: what if the extra copy is not of the call result but the call result is used TWICE such that gcc needs a copy? Hmm.

Alternatively: what if the call result's pseudo naturally has live 1 and refs 2 in a different formulation? E.g. if the call result is used only ONCE but in two places... no.

Hmm, what about making the call result's live range longer (which lowers its pri below `t`'s)? no.

Let me reconsider: maybe the real lever is the type of `ret`. If `ret` is `unsigned int` vs `int` — no code change but maybe different pseudo treatment? The notes say "unsigned int ret (6)" — tried.

What if `ret` is a `short`/`u16`? The truncation adds insns. But what about `unsigned short ret` where the call result is known to fit? No.

Hmm, what about this: the target's copy `move v1,v0` — in the PINNED version, this copy exists because the pinned `result` conflicts. What if in a lever-free version we have a local variable that is live at [24..26] with pri > 10000?

What has pri > 10000? refs*10000/live > 10000 → refs > live. A pseudo with live 1 and refs 2+ (like the call-result pseudo with an immediate copy), or live 2 with refs 3+.

Hmm, so: `t = ret;` where the copy survives cse. To survive cse, `ret` must be modified between the copy and its uses, or the copy must be to a different type.

Type difference: `s16 t = ret;` → the copy would be `move v1,v0` + truncation (sll/sra or andi) → extra insns → the target has no truncation. Unless the truncation is folded because... no.

What if `t` is `unsigned int` and `ret` is `int`? cse might still propagate (same value, just a different "type" — gcc's cse treats them as different if the types differ in representation? unsigned vs signed int have the same representation → cse would fold them).

Hmm.

What about the "dead-reset CSE-BREAKER" trick from the moves file! "launder | func_8018A180 | MATCH — DEAD-RESET CSE-BREAKER (§373): pb=&buf; call(pb); pb=0; before every site; cse's &buf address class breaks...". So a dead reset breaks cse's equivalence.

For our case: `ret = call(); t = ret; ret = 0;` — the dead reset of `ret` after copying to `t` would prevent cse from propagating t←ret? Hmm, cse propagates the copy t←ret at the point of the copy; then `ret = 0` kills ret's value but t already has the copy. Actually cse's copy propagation replaces the uses of t with ret's reg... it happens at the copy point; if ret is redefined later, the propagation is still valid for uses before the redefinition. But the uses of t are AFTER `ret = 0` → so the propagation would be invalid → cse keeps the copy ✓.

So: `ret = call(); t = ret; ret = 0; if (t != 0) {...}` — hmm, but `ret = 0` is a dead store that gcc will remove (DSE). The §373 trick worked in a case where the reset mattered. If gcc removes the dead store, the copy may be propagated. But the dead-store elimination happens after cse? Order: cse runs early (before dce?). In gcc 2.7.2, the pass order: cse, then jump, then dce? The "dead reset" trick in the other shard apparently worked.

But hold on: does this change the generated code? `ret = 0` is dead → removed → no insn. But it breaks the cse equivalence → the copy `move v1,v0` survives ✓ and the tests use `t` in $3 ✓.

But wait: would the copy `move v1,v0` be emitted at all? The call-result pseudo in $2, `t` in $3 → yes, the copy is `move v1,v0` ✓ (matching target ins 24!).

And the RESULT_DECL/local `result` handling: the value pseudo gets $2 (free after ins 26) ✓.

This looks very promising! Let me write it:

```
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int ret;
    int t;
    buf1[0] = 0;
    buf1[1] = 0;
    buf1[2] = 7;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf1, buf1);
    buf2[0] = 0;
    buf2[1] = 0;
    buf2[2] = (short)0xffe8;
    ((void (*)(int, void *, void *))func_80149290)(param_1, buf2, buf2);
    ret = func_80133784(1, buf1, (int)buf2);
    t = ret;
    ret = 0;
    if (t != 0) {
        result...
    }
}
```
Hmm, but `ret = 0` dead store: gcc removes it. Does the removal happen before or after cse? In gcc 2.7.2, the pass order (from the .i?): the "cse" pass runs after expand? Let me think: gcc 2.7.2's pass list: ... tree optimization passes (cse, jump, dce, loop...), then RTL passes (expand, combine, flow, cse2, sched...). The `cse` (tree-level) pass does copy propagation. Dead store elimination at the tree level is in "dce" or in the store-merging pass ("stmt")? The dead store `ret = 0` might be removed by the "dead store elimination" in the local pass or in cse itself (cse does remove dead stores to a local whose address isn't taken? cse has "store motion"/"DCE of dead stores" I think).

If cse removes the dead store BEFORE propagating the copy, the trick fails. But the other shard's move (§373 dead-reset) suggests it worked there.

Also: `t = ret; ret = 0;` — after removing `ret = 0`, cse might then propagate t←ret. Order matters. Alternatively use a different breaker that's not dead: e.g. `t = ret; ret = ret;`? Hmm, `ret = ret` is a self-assignment (dead).

Another breaker: make `ret` address-taken? `&ret` forces it to memory → changes the code.

Another: make the copy go through a variable that is later modified — but we need `t` to keep the value.

Hmm, alternative breaker: `t = ret; ret = 0;` where ret=0 is NOT dead because `ret` is used later? It's not used later.

OK, but honestly, gcc's tree-level cse in 2.7.2: the pass "cse" performs "global common subexpression elimination" and copy propagation via `cse_record`/`cse_replace`. Dead stores are removed in "dce" (dead code elimination) which comes after cse? In gcc 2.7.2's pass list, the order is roughly: ..., cse, jump, expand?, no.

Let me just try it — the scoring is cheap. Let me generate a batch of variants:

w1: `t = ret; ret = 0;` then use t.
w2: `t = ret;` then use t (no reset) — tests if cse propagates.
w3: block-decl `t` after the call.
w4: `t = ret; ret = 0;` with t declared at the top.
w5: `ret = call(); t = ret; ret = 0;` but with `t` used in the mask test and `ret` in the != 0 test? Hmm, that changes semantics? `ret != 0` and `(ret & 0x8000)` — using t for both is equivalent.
w6: the "copy through s16 temp" idea: `s16 t = ret;` → truncation insns. skip.
w7: `t = ret; ret = 0;` where the local `result` is declared at the top (like the original) — the local `result` gets $2?
w8: `unsigned int t = ret; ret = 0;`

Also variants where the value-holding variable is `result` as in the original, plus the copy trick.

Let me write ~8 variants and score them.

Note the C0505 catalog: "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse" — the copy-through-temp is a "temp" ✓. The dead reset is a "statement order" move ✓.

Let me write these files now.
