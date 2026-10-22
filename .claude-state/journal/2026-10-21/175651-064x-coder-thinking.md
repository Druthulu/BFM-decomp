---
ts: 2026-10-21T23:56:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_TAwN0m2QVIKThbQVBBsb
---
Now the insn count matches (115 vs 115) — the load became `lhu v0,0(v0)` (using the address's reg v0) instead of `lhu v0,0(s0)`.

So: the address pseudo is in v0 and the load uses v0. If the load used p (s0), we'd get `lhu v0,0(s0)`.

**So the fix**: make the load use p (s0) while p is a COPY of the address pseudo (v0)!

I.e.: p = &D_800B99DC (p is a copy of the address pseudo A) and the load uses *p. The address pseudo A must be a separate quantity from p.

How? The address expression must be used TWICE so cse creates A:
- use 1: `p = &D_800B99DC` → p = A
- use 2: the load's address → but the load uses p...

Hmm. Alternatively:
- use 1: `p = &D_800B99DC` → hmm, if the expression is used only once, no A is created; p = the constant directly.

So I need the address expression to appear twice in the C while the load uses p.

What if the load is `*p` and the address expression is used twice: once in `p = &D_800B99DC` and once in the assignment `p = &D_800B99DC`... no.

Hmm! What if there are TWO pointer variables both assigned the address, one used by the load and one in the loop? E.g.:
```
    p = &D_800B99DC;      /* A created (used twice) */
    pp = &D_800B99DC;
    D_801E86BC = (*pp & 1) + 3;   /* hmm, the load's base would be A's reg */
```
Hmm, in v9 the load's base was v0 = A's reg (not p's). Because find_best_addr picked A (the cheapest/first). Hmm, so with 2 uses, the MEM's address = A.

So I need the MEM's address to be p (the copy) while A is a separate quantity. In v9, the MEM's address was the raw symbol → find_best_addr replaced it with A (the reg). If instead the MEM's address is p (a reg), find_best_addr leaves it alone → `lhu v0,0(s0)` ✓ — and then the address expression is used only ONCE (in p's assignment) → no A → p = the constant → no copy. ✗ (that's the x1 case).

So: I need BOTH: the MEM's address = p (a reg) AND p's value = a copy of a separate quantity A.

Hmm! What if the MEM's address is p AND the address expression is used twice: once for p's assignment and once for... hmm, we need A to exist.

What if A is created by the LOAD's address being the raw symbol AND p being assigned from the raw symbol — that's v9: the load's base became A (v0). The problem: the load used v0, not s0.

Hmm, but in v9 the load's MEM address was the raw symbol_ref, so find_best_addr replaced it with A. What if instead the load's MEM address is p (a reg) but p's assignment is from A?

I need: A (a CSE pseudo for the address) and p = A. That requires the address expression to be used twice, one of which is p's assignment. The other use must be something that (a) doesn't generate code, and (b) makes the MEM's address p rather than A.

Hmm! What if the other use is in a *different function call*? no.

What if the other use is `*p` itself? I.e., the C is:
```
    p = &D_800B99DC;
    D_801E86BC = (*p & 1) + 3;
```
The MEM's address is p (a reg). The address expression is used ONCE. ✗

Hmm, so how do we get 2 uses of the address expression where one is p's assignment and the other is not the MEM's address?

**What if the OTHER use is a second pointer variable that is DEAD?** e.g.
```
    p = &D_800B99DC;
    pd = &D_800B99DC;   /* dead */
```
A dead assignment → flow deletes it → but cse already created A (used twice) → A survives? Hmm: cse creates A for the address (2 uses) and both assignments become p = A and pd = A. Then flow deletes the dead pd = A (a copy) → but the copy p = A remains!! ✓✓✓

Hmm! And then A (the address pseudo) is a separate quantity from p → local-alloc: A is short-lived (its uses are the two copies) → A gets a caller-saved reg (v0) → `lui v0; addiu v0,v0,0` and p = A → `move s0,v0` ✓✓✓ AND the load `*p` uses p (s0) → `lhu v0,0(s0)` ✓✓✓

Hmm, but is the dead assignment to pd "a dead store kept only to steer a pass"? It's a dead assignment (deleted by flow). Hmm, risky per C0505.

Hmm, alternatively, make the second use a REAL one: e.g., q and r are also addresses of globals. What if p's address is used for BOTH p and something else real?

Hmm! What about: the loop's `*p` and the preheader's `*p` — the address expression appears once but p appears twice.

Hmm.

Hmm, what about making A's 2nd use a REAL pointer variable in the C that is used in a way that generates the same code? E.g. what if q (or r) is ALSO assigned &D_800B99DC... no, different address.

OK, hmm, what about this cleaner idea: **make the load use p and give p a second (real) use of the address expression via a pointer that is passed to a call**? The target has no such call.

Alternatively — hmm! What if the address expression is used twice because of the C0505 "pointer reuse" where p is assigned the address and then p is re-assigned to the same address later? Hmm.

Hmm, hold on. What about the simplest: the dead assignment `pd = &D_800B99DC;` — hmm, that's exactly the "identity" flavor.

Hmm, alternatively: what if the second use of the address expression is in a *dead but real* statement, like `if (0) ...`? ✗ (invented always-false condition — refused).

Hmm. What about the second use being a *pointer equality* test that gcc folds? e.g. `if (pd == &D_800B99DC) { }` — gcc folds it to nothing? An empty if with a folded condition → no code. Hmm! `if (pd == &D_800B99DC) ;` — gcc would fold the comparison (pd's value is known) → no code. Hmm, but is the comparison folded at the RTL level? gcc's fold would see pd = &D_800B99DC and the comparison → true → the if is removed. Then the address expression's use count... hmm, if the comparison is folded away BEFORE cse, the address is used once again. ✗

Hmm.

What about the address expression being used twice via a *union* or a *struct copy*?

Hmm, let me think about the DEAD-ASSIGNMENT idea more: is it really refused? C0505: "Refused as closes: an invented always-false condition, a dead store kept only to steer a pass, a pointer alias invented only to dodge cse." — "a pointer alias invented only to dodge cse" — that's EXACTLY what `pd = &D_800B99DC;` (a dead alias) would be. ✗✗

Hmm!! But wait — the v9 result gives me a KEY new insight: with 2 uses of the address expression, the load's base became the address pseudo A (v0) instead of p. What if I make the load use `p` AND have the address expression used twice in a way where p is the SECOND use?

Hmm: what if the C is:
```
    p = &D_800B99DC;      /* use 1 */
    D_801E86BC = (*p & 1) + 3;   /* p's use */
```
The address expression's uses: 1 (in p's assignment). ✗

Hmm, what if p's assignment is written as `p = &D_800B99DC;` and the LOAD is `*(u16 *)p`... same.

Hmm, so for A to exist, the address expression must appear twice. The 2nd appearance must be in a statement that generates no code but keeps the expression alive until cse.

Hmm! What about the SECOND appearance being in the SAME statement as the first: e.g.
`p = &D_800B99DC;` and `p2 = &D_800B99DC;` — two copies (that's v4, which failed: 5).

Hmm, v4 failed. Why? In v4, pb had 2 sets. Hmm.

Hmm, what about a REAL second use: what if the C uses the address in a way that's semantically real but generates no extra code because it's the SAME value used by the same register? E.g.:

```
    p = &D_800B99DC;
    D_801E86BC = (*p & 1) + 3;
```
Hmm, the address expression appears once.

WAIT!!! What if we write the load as `*p` but p is assigned from a variable that was assigned the address:
```
    u16 *pp = &D_800B99DC;    /* use 1 of the address */
    p = pp;                    /* the copy */
    D_801E86BC = (*p & 1) + 3;
```
That's v2/x3 — the address expression appears ONCE (in pp's assignment) → no A → coalesced. ✗ (consistent with the results).

And in v9, the address expression appears twice (p's assignment + the raw MEM) → A exists → the MEM's base = A (v0) and p = A → hmm, but the result showed `lui s0; addiu s0,s0,0` (p's materialization directly in s0) and the MEM using v0. So there WERE two quantities: A (v0) and p (s0), and p = A was COALESCED (the copy disappeared!). Hmm! Wait: mine[17-18] = `lui s0; addiu s0,s0,0` — so s0 holds the address, and mine[21-22] = `lui v0; addiu v0,v0,0; lhu v0,0(v0)` — so v0 ALSO holds the address (a second materialization!). So there were 2 materializations (4 insns) + the load, and the target has 1 materialization + a copy + the load.

Interesting! So in v9, the address was materialized TWICE (once for p → s0, once for the MEM → v0). The target has it once (v0) and copies to s0.

So the target's shape: ONE materialization (v0) + a copy (s0) + the load using s0.

So in the target, the MEM's address = p's reg (s0) and the materialization is in v0, copied to s0.

So A (the materialization) is in v0 and p = A (the copy) — the copy was NOT coalesced in the target.

In v9, the copy p = A WAS coalesced (s0 materialized directly) — but the MEM's address became A (v0) instead of p (s0). Hmm! So in v9, cse's find_best_addr replaced the MEM's address with A (v0) rather than p (s0) — and the copy p = A was coalesced away?! But then p's reg (s0) holds the address and A (v0) holds it too → 2 materializations.

Hmm OK. So in v9, the two quantities are p (s0) and A (v0) — but they're not connected by a copy: A is a separate CSE pseudo created for the MEM's address, and p is p's own copy of the constant. gcc's cse: p = &D_800B99DC → p's reg_equiv = the symbol; the MEM's address = the symbol → find_best_addr → replaced with a REG (A) holding the address. A is a new pseudo created to hold the address.

So the target wants: A (v0) holds the address, p = A (a copy!), and the MEM's address = p's reg.

Hmm! So the target's dataflow: the address is computed into A (v0), p = A (move s0,v0), and the MEM's address = p (s0).

In v9, the MEM's address became A (v0) — because find_best_addr picked A. For the MEM to use p, find_best_addr must pick p's reg. Hmm — find_best_addr picks the "best" entry: it looks at the cse table for entries with the same value. Both A and p (s0) have the address. ADDRESS_COST(REG) = 1 for both. The tie-break: `(p->cost + 1) >> 1 > best_rtx_cost` — the elt->cost of the expression. Hmm.

Hmm, so in the target, find_best_addr picked p's reg (s0) over A (v0). Hmm, in v9 it picked A.

The difference might be the ORDER of the entries in the cse table, or the fact that in the target A was created FIRST and p was the copy of A (so p's reg isn't a separate entry — p IS a copy).

OK, so the target: A is created by cse (the address expression used twice), p = A (a copy), and the MEM's address = p.

In v9, the address expression was used twice: once for p's assignment and once for the MEM. And gcc created A for... hmm, in v9, p = &D_800B99DC gave p the constant (p's reg_equiv = symbol_ref) and the MEM's address = the symbol → find_best_addr found the reg holding it (A = v0, a new pseudo). Hmm, so A was created by find_best_addr (not by cse's expression sharing), and the MEM's address = A.

So in the target, the MEM's address = p's reg. That means p's reg must be in the cse table as a REG with the address value. p's reg_equiv = the symbol_ref → so p's reg is a candidate for find_best_addr → the MEM's address = p's reg ✓. But in v9, the MEM's address became A (v0) instead of p (s0). Hmm, why? Because A was found FIRST (A is the "elt" and the loop looks for something cheaper).

Ugh, the ORDER matters. In the target, maybe there's no A at all: the MEM's address = p's reg (s0) and the materialization in v0 + the copy is a RELOAD artifact.

Hmm! Let's revisit: in the target, p's reg = s0 and the address is materialized in v0 and copied to s0. What if the materialization in v0 is the "CONST pseudo in a hard reg" and the copy is p = A?

Hmm, hmm. OK, let me try the inverse of v9: the load uses p (as in the source) and the address expression is used twice via a SECOND real use that generates no code but is not an "alias invented to dodge cse"...

What if the second use is the LOOP's `*p`? Hmm: `*p` in the loop — the MEM's address = p (a reg). The address EXPRESSION (&D_800B99DC) appears once.

Hmm, hmm.

OK: let me try v10 = the source's load (using p) + the address expression ALSO used in the assignment of p in a way that...

hmm, what about: `p = &D_800B99DC;` where the address expression is used in a statement that ALSO assigns p:
```
    p = &D_800B99DC;
```
Hmm.

**IDEA**: what if we use the address expression twice via the two pointer variables q and r — no, different addresses.

**IDEA**: what if the second use is `*(u16 *)&D_800B99DC` in the loop (instead of *p)? Then the loop's MEM address = A (v0)... and A would be live across calls → s0 → hmm, then the MEM's base = s0 ✓ and p = A → coalesced → p = s0 too. Hmm.

Honestly: v9 got us to 115 vs 115 insns with the load using the wrong reg. Let me try v10: v9 but with the load using p AND the address expression used twice — by making the LOOP use the raw address? no...

Hmm, what about v11: the load uses p, and the address expression is used twice because p is assigned the address TWICE in different statements:
```
    p = &D_800B99DC;    /* use 1 */
    ...
    p = &D_800B99DC;    /* use 2 — but this is an identity */
```
With 2 uses of the address expression, cse creates A. Then p = A twice → hmm, the second assignment is a copy of A (or forwarded). Hmm, and the load uses p.

Hmm, but the two assignments are to the same variable p → p has 2 sets → the load (after the 2nd) uses the 2nd value. And cse's A would be shared → the materialization happens once (in A) → A is used by both assignments → A is live across... if the assignments are close, A is short-lived → v0 → and p = A (the 2nd assignment) → `move s0,v0` ✓ and the 1st assignment p = A → also a copy → but p is overwritten → the 1st is dead → deleted by flow ✓ → so only ONE copy survives ✓✓✓

And the load `*p` → the MEM's address = p (s0)? Hmm, or = A (v0) via find_best_addr. Hmm! The MEM's address in the source is p (a reg) → find_best_addr leaves it (it's already a REG) ✓ → `lhu v0,0(s0)` ✓✓✓

So v11:
```
    i = 0;
    q = &D_801E87B2;
    p = &D_800B99DC;      /* use 1 */
    r = &D_8018F078;
    D_801E86BC = (*p & 1) + 3;    /* hmm — this uses p, but which set? set 1 */
    D_801E86C0 = D_800B99D8;
    p = &D_800B99DC;      /* use 2 (identity) */
    for (...) { ... }
```
Hmm, but the ORDER: the target's materialization (17-19) is before the load (22). If the 2nd assignment is after the load, the copy `move s0,v0` would come after the load ✗ (the target has it before).

Hmm. So the 2nd assignment must come BEFORE the load:
```
    p = &D_800B99DC;      /* use 1 */
    p = &D_800B99DC;      /* use 2 */
    D_801E86BC = (*p & 1) + 3;
```
Then set1 is dead (p is overwritten) → deleted → and the copy survives ✓. And the materialization+copy would be at the position of set2 ✓ (before the load ✓).

But `p = &D_800B99DC;` twice in a row is an obvious identity — likely judged as an identity statement. Hmm.

Hmm, but hold on: would cse even create A? Two assignments of the same expression: cse's forward scan would forward the expression's value (the second assignment gets the cached value = the same pseudo) → A is created only if the expression is used ≥2 times. Here the expression appears twice (in 2 assignments) → cse creates A ✓ (cse counts uses of the expression in different statements).

Hmm, hmm. But the identity-ness...

ALTERNATIVELY: make the two assignments genuinely different in a way that's not an identity: e.g.
```
    p = &D_800B99DC;
    p = (u16 *)((u8 *)&D_800B99DC + 0);   /* identity address spelling — banned */
```
✗.

Hmm. What about: the second use is a REAL, different statement whose value is the same but is not an "alias to dodge cse"?

What if the second use is a call argument? e.g. `func_80049CAC((s32)q - 2, (s32)&D_800B99DC)` — that changes the call's semantics ✗.

Hmm.

OK, let me try v11 (the double assignment) as a MECHANISM TEST. If it produces the `move s0,v0` and scores 0 (or close), then I'll know the mechanism and can look for a legit variant (e.g. maybe the double assignment can be replaced by a pointer-reuse that's natural). If it doesn't work, WALL.

Let me write v11.
