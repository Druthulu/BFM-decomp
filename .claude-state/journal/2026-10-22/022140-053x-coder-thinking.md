---
ts: 2026-10-22T08:21:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2EKyLjClL9hXkBseXq3B
---
c7/c8 → 36 ins (the copies vanished). Hmm.

So with v as s16, the copies died. Because `tmp = v` (same mode) → cse merged tmp and v → and then `c = tmp`... hmm, and the copy died.

Hmm. x3 (in the harness) kept the copy. But in the real function it died. Hmm, x3's copy `c = tmp` survived.

Hmm, the difference: in the real function there's more pressure.

OK, I'm burning time. Let me step back and think about the time budget: I've used ~1h50m. The brief says 20-30 min per item. I have 2 items left (8018302C, 8017E6EC) and I should leave time for the log and commit.

Let me consider: for 8018302C, the best so far is score 2 (c2.c). The blocker: the compare's operand gets rewritten to the copy.

NEW IDEA: what if the compare's operand is a value that gcc CANNOT rewrite because it's used in a way that requires the exact reg... hmm.

NEW IDEA (promising!): **What if the copy's destination is used in the compare AND the compare's other operand...** no.

NEW IDEA: **What if we make the copy's value NOT equal to the compare's operand by making the copy happen BEFORE the compare on a DIFFERENT value, and the compare's operand is the value that the copy came from?**

Wait — I have it backwards! Let me re-read the target:
```
lh v0,24(a0)      ; the load
move v1,v0        ; the copy: v1 = v0
slti v0,v0,2049   ; the compare reads v0
addiu v0,v1,-512  ; the subtraction reads v1
```
So the compare reads the ORIGINAL and the subtraction reads the COPY.

In my c2.c, gcc made the compare read the copy. What if I make the compare read the copy and the subtraction read the ORIGINAL — but arrange the regs so that the compare's reg is v0 and the subtraction's source is v1?

The compare reads the copy (c) and the subtraction reads the original (v). For the target: the compare's operand reg = v0 and the subtraction's source reg = v1. So c → v0 and v → v1. But the copy is `or v1,v0` — the copy's DEST is v1 and its SOURCE is v0. So the copy's dest (c) = v1 and its source (tmp/v) = v0. So c is in v1, not v0 ✗. So the compare (reading c) would read v1 ✗.

Hmm. So no.

Hmm, so the compare MUST read the copy's SOURCE reg (v0) and the subtraction must read the copy's DEST (v1).

Since the copy's source is the load's value (which is also the compare's operand value), gcc rewrote the compare to read the copy.

**To prevent this: make the copy's source a DIFFERENT pseudo than the compare's operand, but with the same value, and gcc must not merge them.**

The only way to have two pseudos with the same value that gcc doesn't merge: a copy that escapes cse (like the HImode trick). But the HImode trick's copy makes them equal in gcc's view...

Hmm! Actually NO: the HImode copy `tmp = (s16)v` — cse's equivalence class for a HImode copy: gcc's cse2 (the pass that handles reg equivalences) tracks HImode copies as "the low 16 bits are equal" but not the full 32-bit value. Hmm! Actually the G06 note says "the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0".

"escapes cse2's equivalence class" — so the values are NOT in the same equivalence class! Then how did gcc avoid substituting the compare's operand?

Because the equivalence is only on the low 16 bits, and the compare needs the full 32-bit value → gcc can't substitute ✓✓!

Hmm! But in our case, the compare reads v (the full 32-bit value) and the copy's source is tmp (16-bit). Since v's value is fully determined by its low 16 bits (it's sign-extended), gcc might still know they're equal... but empirically in c2.c the substitution DID happen. Hmm.

Hmm, but hold on: in c2.c the chain was v → tmp → c. gcc might have propagated v ≡ c through the two steps: v ≡ tmp (HImode, 16-bit) and tmp ≡ c (the full value). Hmm.

So maybe the fix is to have ONLY the HImode copy (no s32 copy of it). I.e.:
```
v = *(s16 *)(p + 0xC);      /* v */
tmp = (s16)v;                /* the HImode copy: tmp's low 16 = v's low 16 */
c = tmp;                     /* the copy: c = sign_extend(tmp) */
```
That's c2.c. Hmm.

What if we skip the `tmp` and make the copy's source the load directly with an HImode destination:
```
v = *(s16 *)(p + 0xC);      /* v: s32 */
c16 = (s16)v;               /* c16: s16 — the HImode copy */
c = c16;                    /* the copy */
```
same as c2.

Hmm.

OK, let me try: what if the compare reads `v` and the copy's source is `tmp` (s16), and the SUBTRACTION reads `c` — but we prevent the compare's rewrite by making the compare's operand NOT v but a separate variable holding the load:
```
v = *(s16 *)(p + 0xC);
w = v;             /* hmm, a plain copy → cse merges w and v */
```
✗.

Hmm, what if `w` is assigned from the load directly:
```
v = *(s16 *)(p + 0xC);       /* for the copy */
w = *(s16 *)(p + 0xC);       /* for the compare */
tmp = (s16)w;  ...
```
cse merges the loads ✗.

Hmm, what if the two loads are separated by a STORE (which prevents cse from merging them)? E.g.:
```
v = *(s16 *)(p + 0xC);
*(s16 *)(p + 0xD) = v;    /* a store — but that changes the semantics! */
```
✗.

Hmm.

OK — alternative: **accept score 2 and look for a different lever**? The result must be MATCH (score 0) or PARTIAL or WALL. A score-2 with a WALL tag is a valid outcome if I document it.

Hmm, but let me try ONE more idea: what if the copy's destination `c` is used in the compare and the compare's operand is the ORIGINAL — i.e. TWO compares? ✗ extra insns.

**IDEA**: What if we make the subtraction read the copy's SOURCE (tmp) and the compare read the copy's DEST (c)? I.e. swap:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (c >= 0x801) { v = tmp - 0x200; ... }   /* the subtraction reads tmp */
```
Hmm: the compare reads c (v1) ✗ (the target reads v0).

**IDEA**: what if the compare reads `v` and the subtraction reads `tmp`?
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = tmp - 0x200; ... }
```
Then the subtraction reads tmp — but tmp is the copy's SOURCE (its reg = v0 after coalescing) → `addiu v0,v0,-512` ✗ (the target reads v1).

Hmm.

OK, let me try the reverse: maybe I should attack it from the "make the compare read the original" angle by keeping v's value alive AFTER the compare. In the target, `v` is dead after the compare (it's reassigned inside the if-arm). Hmm, but the target's compare reads v0 = the original. So in the target, the compare's operand is the original even though it's dead after → because there's no equality.

In our version there IS an equality → gcc picks the copy.

Hmm, what if we make the copy's value NOT equal by making the copy's source a value with a DIFFERENT (but asm-equivalent) representation...

AH WAIT!!! **What if the copy's source is the value AFTER the sign extension but the compare's operand is the value BEFORE?** Hmm, same value.

Hmm, what if the copy's source is `v` and the compare's operand is `v` — and we make the copy a copy of a DIFFERENT variable that happens to hold the same value, e.g. `x`? no.

OK. Let me try a slightly different tack: **what if the copy's destination is `s16` and the compare reads `v`, with the subtraction `v = c - 0x200` where c is s16?** Then:
- c = tmp (both s16) → an HImode copy → escapes cse ✓ (the copy survives!)
- the compare reads v ✓ (c is a different mode, and c ≡ v only in the low 16 bits → gcc shouldn't substitute the full 32-bit compare operand... hmm, but v's value IS fully determined by its low 16 bits).
- the subtraction `v = c - 0x200` → c promoted (sign-extended) → free? gcc would need to materialize the sign extension ✗ (maybe).

c3 was: `s16 c; s16 tmp;` → score 10 (36 ins) → the copies vanished. Hmm, so `c = tmp` (both s16) got merged by cse → hmm, so the HImode copy did NOT escape cse in that case?!

Hmm, c3 used `tmp = (s16)v; c = tmp;` where c is s16 → `c = tmp` is a same-mode copy → cse merged c and tmp → and then... the copy `c = tmp` vanished → the value v was used directly.

Hmm, so HImode copies do NOT escape cse in general. The G06 note said "the copy through an s16 temp escapes cse2's equivalence class" — cse2 is the pass that creates equivalences for the FINAL register allocation. Hmm.

OK. Time to make a decision. I've spent ~2h on this shard; 8018302C is at score 2. Let me try 2-3 more quick variants (10 min) and then move to 8017E6EC (which has a clearer path), then write up.

Quick variants to try:
V-a: `c` is s32, `tmp` is s16, and the compare reads `v` — but with the copy `c = tmp` placed AFTER the compare in the source (inside the entry block, before the if)? That's the same.

V-b: Make the compare's operand `v` but add `(void)v;`? no.

V-c: **Use a `u16` temp and change the load to `lhu`?** The target has `lh` ✗.

V-d: **What if the copy's source is `v` and the compare's operand is `v`, but we prevent the substitution by making the copy's destination LIVE ACROSS THE BRANCH in a way that forces a different reg?** Hmm.

V-e: What if the copy is `c = tmp` where tmp is s16, and we ALSO use `tmp` (not c) in the subtraction: `v = tmp - 0x200`? Then the copy's dest c is used... nowhere → DCE ✗.

V-f: What if we swap which value the subtraction uses so that the compare reads the copy and the copy's reg is v0? I.e. make the COPY's dest be the compare's operand and the compare's reg = v0:
For the target, the copy is `or v1,v0`: the dest v1, the source v0. The compare reads v0 = the source. So the compare must read the copy's SOURCE. And the copy's source is the value that's also the compare's operand — but they're the same pseudo in the target (v0 = the load).

So in the target, the compare's operand IS the copy's source pseudo! So the compare reads the load's pseudo, and the copy's dest is a different pseudo (c).

So in our version, we need the compare to read the LOAD's pseudo (not c). gcc rewrote it to c. The load's pseudo and c are in the same equivalence class.

**THE FIX: make the copy's dest pseudo NOT equivalent to the load's pseudo.** The copy `c = tmp` with tmp ≡ v (HImode). gcc's equivalence: c ≡ tmp (32-bit) and tmp ≡ v (16-bit). Combined, c ≡ v in the low 16 bits. Since v's value is sign-extended-16, c == v fully. But does gcc's cse reason that deeply? Apparently yes (it substituted).

Hmm, what if we break the v ≡ tmp link? The link is the truncation `(s16)v`. gcc creates the equivalence because tmp's low 16 = v's low 16.

**What if tmp is assigned from a DIFFERENT value with the same low 16 bits?** Hmm.

**What if the compare's operand is `v` and the copy's source is `tmp` where tmp is NOT derived from v but from a re-loaded value?** cse merges the loads ✗ (unless a store separates them).

Hmm, hmm. What if we introduce a store between the two loads that is SEMANTICALLY NEUTRAL? Hmm, e.g. `*(s16 *)(p + 0xC) = v;` — no, that changes semantics.

OK. Let me consider the possibility that the compare's operand substitution is actually a *register allocation* choice, not a value rewrite! I.e. maybe gcc kept the compare's operand as the load's pseudo, but allocated the LOAD's pseudo to v1 and the copy's dest to v0?! But then the copy would be `or v0,v1` — the diff shows `move v1,v0` in mine (same as the target) — hmm, so the copy's dest is v1 and the source is v0.

Hmm, so the load is in v0 (the copy's source) and the copy's dest is v1. And the compare reads v1 = the copy's dest. So the compare's operand pseudo = the copy's dest pseudo → a VALUE rewrite ✓ (as I thought).

Hmm, so gcc rewrote the compare's operand from the load's pseudo to the copy's pseudo.

Hmm! Hold on: is it possible that gcc did this because the LOAD's pseudo was DEAD after the compare (its value not needed) and the copy's pseudo was live? Yes — cse's "prefer the live reg".

So: **make the load's pseudo live after the compare!** Then gcc can't prefer the copy.

How? The load's value must be used after the compare. In the target, the load's value IS used after the compare? Hmm: `addiu v0,v1,-512` — the result goes to v0 (the load's reg) — so the load's reg is reused for the result → the load's VALUE is dead after the compare in the target too.

Hmm, but in the target there's no equality so it doesn't matter.

Hmm, so how do I make the load's pseudo live after the compare in our version? By using `v` (the load's value) somewhere after the compare. The only place: the store `*(s16 *)(p + 0xC) = v;` — but v is reassigned before that.

What if we DON'T reassign v but use a different variable for the result?
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) {
    w = c - 0x200;
    *(s16 *)(p + 0xC) = w;
}
```
Then v's value is dead after the compare ✗ (v isn't used later).

Hmm, what if v is used after the if-block? E.g. the second arm reloads v → v's value is dead anyway.

Hmm, what if we use the ORIGINAL v's value after the if-block in a way that's free? E.g. `if (v >= 0x801) { w = c - 0x200; *(s16*)(p+0xC) = w; }` and then... v is not used.

Hmm, what if we keep the store as `*(s16 *)(p + 0xC) = v;` with v NOT reassigned:
```
if (v >= 0x801) {
    v = c - 0x200;    /* v is reassigned — its old value dies */
    *(s16 *)(p + 0xC) = v;
}
```
✗ v's old value dies at the reassignment... but the reassignment is INSIDE the if-arm, and the compare is before it. So at the compare point, v's value is live (the compare uses it) and dies right after (in the then-arm). Hmm, so v's value is live AT the compare and dead after.

The copy's value (c) is live from the copy through the if-arm.

Hmm, so at the compare, both are live. gcc still preferred c.

Hmm, hmm. What if the compare uses v AND v's value is used again later (so it's live across the branch)? E.g.:

```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) {
    w = c - 0x200;
    *(s16 *)(p + 0xC) = w;
}
```
v is dead after. ✗

What if the second arm's code uses the first arm's v? Nah.

OK — RADICAL: what if we make the compare's operand a value that is NOT the load: e.g. compare the LOAD EXPRESSION with a cast that gcc handles separately:
`if ((s16)*(s16 *)(p + 0xC) >= 0x801)` — hmm, the cast to s16 → the compare's operand is a QI value → the promotion → hmm.

Hmm! Actually: `if (*(s16 *)(p + 0xC) >= 0x801)` — the field is s16 → the comparison promotes it to s32 (sign-extended). gcc's expand: the load is `lh` (sign-extending) → the promotion is FREE ✓ → the compare reads the load's reg ✓. And cse merges the load with the other load (the same address) → the compare's operand = the merged load pseudo ✓.

But c6 (which did exactly this) gave score 2 — the same as c2. Let me check c6's diff: maybe the substitution still happened (c ≡ the merged load pseudo).

Hmm.

OK, let me try a DIFFERENT approach to the whole problem: **what if we make the copy's dest pseudo be used in the compare, and the compare's operand (the load) be used in the subtraction — but arrange the reg allocation so that the copy's SOURCE is v0?**

Target: `or v1,v0` — the copy's dest is v1, the source is v0. The compare reads v0 (the source). The subtraction reads v1 (the dest).

If our C were:
```
v = *(s16 *)(p + 0xC);     /* the load */
tmp = (s16)v;
c = tmp;                   /* the copy */
if (c >= 0x801) { v = v - 0x200; ... }   /* the compare reads c, the subtraction reads v */
```
Hmm: the compare reads c and the subtraction reads v. For the target's asm: the compare's operand = v0 and the subtraction's source = v1. So c → v0 and v → v1. But the copy `c = tmp` has its dest = c → v0 and its source = tmp ≡ v → v1 → the copy would be `or v0,v1` ✗ (the target has `or v1,v0`).

✗.

OK. Let me now consider the possibility that gcc's rewrite is not a value rewrite but a REGALLOC preference that could be flipped by changing the ORDER/NUMBER of refs. Hmm.

Let me try: **give the copy's dest an extra reference** so that cse's canonicalization prefers the LOAD's pseudo. E.g. use `c` twice:
```
v = *(s16 *)(p + 0xC);
tmp = (s16)v;
c = tmp;
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p + 0xC) = v; }
```
c has 1 use. The load v has 2 uses (the copy source + the compare).

Hmm, cse's canonicalization: "the reg with MORE references wins"? Then v (2 refs) should be canonical → the compare reads v ✓. But the observed result was the opposite (c won). So the rule isn't ref count, or the refs are counted after the copy.

Hmm. What if we give c MORE references? E.g. use c twice in the subtraction:
```
if (v >= 0x801) { v = c - 0x200; *(s16 *)(p + 0xC) = v; }
```
c is used once. To use it twice without extra insns... hmm: `v = c - 0x200;` and then `*(s16*)(p+0xC) = v;` — that's c once.

What about `v = c - 0x200 + 0;`? folded.

Hmm, what about making the compare's operand have MORE uses: e.g. `if (v >= 0x801 && v >= 0x801)`? ✗.

Hmm, what if the compare's operand is used twice in a way that's free: e.g. `if (v - 0x801 >= 0)`: that's a different comparison form. Hmm: `v >= 0x801` ≡ `v - 0x801 >= 0` — but the asm would be `slti`? For `v - 0x801 >= 0` gcc computes `v < 0x801` → hmm, it might use `addiu` + `slti`? Probably it simplifies back.

Hmm.

Time check: 2 hours in. Let me time-box: 10 more minutes on 8018302C, then move to 8017E6EC, then write the log.

Let me try these 4 variants in one batch (2 min):
1. c used twice: `v = c - 0x200;` → hmm.
2. The compare's operand v used twice: `if (v >= 0x801) { ... }` where v is also used in the store of the ORIGINAL value... hmm.

Hmm, let me think about #2 concretely: what if the store uses the ORIGINAL v when the condition is false? Not expressible.

Hmm. What about making the load's pseudo live by using it in the SECOND arm? E.g. the second arm's compare could use the first arm's v? No (different values).

OK, let me try the simplest remaining idea: **the `do{}while(0)` trick** (used in other shards: "do-while(0) around the tail gives the byte temp a loop-shaped live range"). Hmm.

And: **the copy inside a do-while(0)**:
```
tmp = (s16)v;
c = tmp;
do { } while (0);   /* hmm, needs a !FAKE comment */
```
The brief says `do{}while(0)` only with `// !FAKE: do-while`. And "do-while(0) ref boost breaks loop opts". Hmm.

Hmm, from the moves.md: "pin | func_8017F470 | WALL cse-copy-merge — mode=cnt copy: cse makes mode canonical (lives past block end), slt reads a1; u8/(u16) copy escapes cse but splits mode's a1 pseudo (2) or adds andi 0xffff (1)".

Hmm! "u8/(u16) copy escapes cse but splits mode's a1 pseudo (2) or adds andi 0xffff (1)". So a u16 copy escapes cse but adds an andi.

Hmm, in our case, an andi would be an extra insn ✗.

OK. Let me try just a couple of things quickly and then move on:

Test A: `if (v >= 0x801)` where the copy is `c = tmp` and `tmp` is s16 — but ALSO the copy's dest c is used in the compare AND in the subtraction:
```
if (c >= 0x801) { v = c - 0x200; ... }
```
We showed the compare's operand = c = v1 ✗.

Test B: What if the copy's dest is `c` and the compare's operand is `v`, and we add a SECOND use of v that's free: the store! I.e.:
```
if (v >= 0x801) {
    v = c - 0x200;
    *(s16 *)(p + 0xC) = v;
}
```
v is reassigned. What if instead:
```
if (v >= 0x801) {
    w = c - 0x200;
    *(s16 *)(p + 0xC) = w;
}
```
and v is used after the if (dead) ✗.

Hmm, what if the second arm uses v?
```
v = *(s16 *)(p + 0xC);
...
if (v >= 0x801) { w = c - 0x200; *(s16*)(p+0xC) = w; }
v = *(s16 *)(p + 0xD);
```
v's value is dead after the first if ✗.

OK. Let me try Test C: **the copy `c = tmp` where tmp is s16, but the compare's operand is `v` and we ALSO write the store as `*(s16 *)(p + 0xC) = v;` where v is NOT reassigned** — i.e. the result goes to a new var w:
```
if (v >= 0x801) { w = c - 0x200; *(s16 *)(p + 0xC) = w; }
```
Hmm, then v's value is dead after the compare ✗ (but maybe cse's preference differs!). Let me test it — cheap.

Let me batch: c9 = the "w" variant; c10 = the copy's dest used in the compare.

Let me run.
