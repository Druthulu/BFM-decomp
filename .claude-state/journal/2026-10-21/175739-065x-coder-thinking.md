---
ts: 2026-10-21T23:57:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Kh85JI9LSgOTVVrKlLQw
---
Still 5. The double assignment didn't create a copy (cse forwarded).

I've spent a lot on this item (~1h). Let me make the final decision: this is a WALL, with a well-characterized mechanism.

But wait — one more consideration based on the v9 insight. v9 gave 115 ins (matching the count) with the load using v0 instead of s0. What if I combine: v9's structure (address used twice) BUT the load uses p (so the MEM's address = p's reg)?

The MEM's address = p's reg requires the source to spell `*p`. But then the address expression is used once...

UNLESS the second use of the address expression is a real one that generates no code...

Hmm, hold on! What about using the address expression in the *loop* as the MEM's address instead of p? I.e.:
```
    p = &D_800B99DC;                       /* the address, used once as p */
    D_801E86BC = (*p & 1) + 3;             /* *p */
```
✗ (once).

What if we use the raw address in the loop's `*p` and p elsewhere? Then the address expression is used twice: p's assignment and the loop's MEM. cse creates A. The MEM's address = A (a reg). A is live across the loop's calls → A must be an $s reg (s0!) → and p = A → coalesced → p = s0 → the loop's MEM's base = s0 ✓ and the preheader's load `*p` → p (s0) ✓. Then: A = s0 (materialized directly: `lui s0; addiu s0,s0,0`) — no copy ✗.

Hmm, but v9 showed that when the address is used twice, gcc materialized it TWICE (once for p → s0, once for the MEM → v0). That means cse did NOT share the address expression between p's assignment and the MEM's address! Interesting — because p's assignment is a SET (cse's canon_reg/reg_equiv) and the MEM's address is a different expression context.

Hmm, so in v9, the MEM's address got its own materialization (v0) via find_best_addr creating A.

So the target's single materialization (v0) + copy (s0) means: A (v0) is used for BOTH p and the MEM's address, and the MEM's address = p (s0) after the copy.

So: p = A (a copy) and the MEM's address = p. For p = A to be a copy (not coalesced), A must be a REG (not a constant) at that point.

Hmm, what if A is created by find_best_addr (as in v9) and p is assigned from A?! In the C, that would be... hmm, p = A isn't expressible in C directly.

Hmm! But what if the C is:
```
    p = &D_800B99DC;         /* p's value = the symbol (a constant) */
    D_801E86BC = (*(u16 *)&D_800B99DC & 1) + 3;    /* the MEM's address = the symbol → A (v0) via find_best_addr */
```
That's v9 → the load used v0 (A) and p was materialized into s0 separately.

For the target, the load must use s0 = p's reg. So the MEM's address must be p.

=> The C must have `*p` for the load, and the address expression used twice somewhere.

Hmm, what if the address expression is used twice as: `p = &D_800B99DC;` and the LOOP's `*p` — hmm, `*p`'s MEM address is p (a reg), not the address expression.

OK: so the address expression's 2nd use must be another assignment to a variable. And that variable must be p (or a copy of it).

So: `p = &D_800B99DC;` TWICE (v11) → cse forwarded (the 2nd assignment got the cached value → p = the constant, no A).

Hmm, so cse's forward scan forwarded, meaning A was never created. Hmm! But in v9, the MEM's address DID create a separate materialization (A). Because the MEM's address is not a "forwarded" context.

So: to create A via a 2nd USE (not a 2nd assignment), the 2nd use must be a MEM (a load/store) — because the MEM's address is an expression context that cse doesn't forward.

So the C must have: `p = &D_800B99DC;` AND a load/store through the raw address `*(u16 *)&D_800B99DC` (or `*&D_800B99DC`).

And the target's load `lhu v0,0(s0)` uses s0 = p's reg. So the MEM's address must end up as p's reg, not A.

In v9, the MEM's address = A (v0) and p = s0 (a separate materialization). Hmm.

But what if the load is `*p` (using p) AND there's ANOTHER MEM through the raw address elsewhere? Then:
- A = the raw-address MEM's reg (v0, short-lived)
- p = &D_800B99DC (materialized into s0)
- the load `*p` → s0 ✓
That gives: `lui s0; addiu s0,s0,0` (p) + `lui v0; addiu v0,v0,0` (A) + the load — 2 materializations ✗ (the target has 1).

Hmm! The target has ONE materialization. So the raw-address MEM and p must share it.

In the target: the materialization (v0) is shared, and p is a copy of it. So the source of the copy is the address pseudo A, and the MEM's address is p (the copy).

For p to be a copy of A (not coalesced), A must be a REG at the copy point. A is a REG if A was created by find_best_addr (as a pseudo holding the address) — hmm, but then p = A isn't expressible in C...

UNLESS: A is the CSE pseudo created because the address expression is used twice, and one of the uses is a MEM (so cse creates A for the MEM's address) and the other is p's assignment (so p = A). Hmm! In v9, that's exactly what happened — and p was NOT a copy: p got its own materialization (s0) while A got another (v0). Hmm, so cse did NOT unify p's assignment with A.

Hmm. Wait, maybe it did unify and the difference is elsewhere. In v9: mine[17-18] = `lui s0; addiu s0,s0,0` and mine[21-22] = `lui v0; addiu v0,v0,0; lhu v0,0(v0)`. So 2 materializations: s0 (for p) and v0 (for the MEM).

If cse had unified them, there'd be 1 materialization + a copy.

So cse did NOT unify the MEM's address with p's value. Why? Because p's value is a reg_equiv (a constant) and the MEM's address is an expression — cse's find_best_addr found no reg with that value in the table at that point (the table has the EXPRESSION, and the reg p is... hmm).

OK. So in the target, the MEM's address = p's reg (s0) — meaning find_best_addr DID find a reg holding the address and used it. That reg = s0 = p's reg. And the materialization is in v0 → so p's reg (s0) got its value by a COPY from v0.

So the target's dataflow: A (v0) holds the address; p (s0) = A (copy); the MEM's address = p (s0).

For find_best_addr to pick p's reg (s0) over A (v0): both are REGs with cost 1... the tie-break picks by the table's "best" logic. Hmm, but in v9 it picked A.

Hmm, in the target, maybe there's no A at all: maybe the materialization in v0 IS p's reg_equiv materialization but into a DIFFERENT reg...

AH WAIT!!!! What if p's reg_equiv is a REG (not a constant)?! Then reload would copy it. And find_best_addr would find p's reg.

When is a pseudo's reg_equiv a REG? When p is assigned from another pseudo. And when is that copy not coalesced? When the source's value is a REG.

So: A = &D_800B99DC (A's reg_equiv = the symbol → A is a CONST pseudo) and p = A → p's reg_equiv = A (a REG) → p is NOT a CONST pseudo → reload materializes A into A's reg (v0) and copies to p's reg (s0) ✓✓✓. And find_best_addr finds p's reg (s0) for the MEM's address ✓✓✓.

So we need: p = A where A is a pseudo holding the address, and the copy p = A is NOT collapsed to p = symbol_ref.

cse collapses it because A's reg_equiv = the symbol. So we need A's reg_equiv to be a REG — i.e., A is itself a copy of B, and B is a CONST pseudo. But cse collapses chains...

UNLESS the chain is broken by a block boundary! cse's forward scan is per-block: if A is set in block 1 and p = A in block 2, then in block 2 cse doesn't know A's value → the copy p = A is REAL ✓✓✓. And A's live range: block 1 → block 2, no calls in between (if the boundary is the early-return branch... hmm, the early return is a CALL? no, it's a return).

Hmm! But we established the materialization (17-18) is in block 2 (after the early-return branch at 12). And the copy (19) is also in block 2. ✗

Hmm, unless the materialization is in block 1 and scheduled... no.

Hmm, hold on. Is the early-return branch really at insn 12? `bnez v0,32a8` at insn 12 → 0x32a8. And the function's end (insn 113) = 0x3120+113*4 = 0x32A4, so 0x32a8 = one past the end = the "return" path? Hmm, the early return's target should be the function's epilogue (insns 106-113), not past the end.

Hmm! `bnez v0,32a8 <func_8018483C+0x1a8>` — 0x1a8 = 424 = 106*4 → so the target is insn 106 = the epilogue ✓. And 0x32a8 = 0x3120+0x188 = 0x32A8 ✓ (0x3120 + 106*4 = 0x3120+0x1A8 = 0x32A8 ✓). Good, so the function base is 0x3120 and the branch at insn 12 goes to the epilogue (insn 106).

So the block structure: block 1 = insns 0..13 (with the branch at 12 and the delay slot 13), block 2 = insns 14..31 (fall-through), block 3 = the loop (32..96).

And the materialization is at 17-18 (block 2) and the copy at 19 (block 2). Same block.

Hmm!! So cse's forward scan applies to both. ✗

UNLESS the copy's SOURCE is set in block 1 and the copy is in block 2, and the materialization (which is at 17-18) is the materialization of the SOURCE in block 2 — i.e., the source's value is materialized in block 2 but the source was SET in block 1?!

If the source A is set in block 1 (`A = &D_800B99DC;` before the early-return branch), then:
- block 1: A = the symbol → A's reg_equiv = the symbol (a CONST pseudo) → the materialization would be in block 1 (lui/addiu) ✗ (the target has it in block 2 at 17-18).

Hmm, unless the materialization is scheduled into block 2 — no, cross-block scheduling doesn't happen.

OK, I'm done theorizing. This item = WALL. Let me record it with the mechanism and move on. I have 3 more items and I should manage time.

Actually, hmm, wait. Let me try ONE more thing which is a completely different lever: the **"3-qty sort bug"** — no.

Hmm, what about the DEAD-RESET (item 2 style) applied here in the "load uses p" form:

```
    p = &D_800B99DC;         /* set 1: the address, cached */
    D_801E86BC = (*p & 1) + 3;   /* the load — the MEM's address = p */
    p = 0;                   /* DEAD RESET: invalidates the cached address */
    D_801E86C0 = D_800B99D8;
    for (...) { ... *p ... }   /* ✗ p is 0 here! */
```
✗ semantics (p = 0 in the loop).

BUT: what if the loop uses the RAW address and p is only used in the preheader?
```
    p = &D_800B99DC;
    D_801E86BC = (*p & 1) + 3;
    p = 0;                       /* dead reset */
    ... the loop uses *(u16 *)&D_800B99DC ...
```
The loop's MEM's address = the symbol → find_best_addr → A (a reg) → the materialization in v0 (if A is short-lived) or s0 (if live across calls). The loop's MEM crosses calls → A is in an $s reg → s0 → the load `lhu v0,0(s0)` ✓ (if the preheader's load also uses s0 — hmm, the preheader's load uses p, whose reg... p is dead after the preheader → p would get a caller-saved reg (v0) → `lhu v0,0(v0)` ✗).

Hmm! Unless the dead reset forces p's value to be re-derived...

OK, the deep problem: the target has ONE materialization used by BOTH the preheader load and the loop. So it's ONE variable (p) in ONE reg (s0), and the copy `move s0,v0` is the assignment of the address to p, where the source (v0) is a temp.

So: p's value is a REG (v0) at the assignment → p = A where A is a pseudo holding the address.

For A to be a pseudo (not a constant), A must be assigned from something that's a reg. And the only way to have a chain of 2 without collapsing is a block boundary or a non-forwarded copy.

**A BLOCK BOUNDARY!** What if the address assignment is in block 1 (before the early-return branch) and the copy p = A is in block 2? Then:
- block 1: A = &D_800B99DC → A's materialization in block 1 ✗ (the target has it in block 2).

Hmm, BUT: what if A is assigned in block 2 and the COPY is in block 3 (the loop)?! Then:
- block 2: A = &D_800B99DC → materialized in block 2 (v0? A's live range: block 2 → block 3's top, no calls → v0 ✓!!) → `lui v0; addiu v0,v0,0` at insns 17-18 ✓✓✓
- block 3 (the loop body top): p = A → a REAL COPY (cse's block-3 scan doesn't know A's value) → p = s0 (crosses calls) → `move s0,v0` ✓✓✓ — but it'd be scheduled at the loop top (insn 32+), not at 19! ✗

Hmm, the target has the move at 19. Hmm! But wait: could the scheduler hoist the move from the loop body into the preheader? The move defines s0, which is used by the preheader's load at 22 → so the move must be BEFORE 22. If the move is in the loop body (insn 32+), the preheader's load at 22 would use s0 before it's defined → impossible. So the preheader's load would use a different reg ✗.

UNLESS the preheader's load doesn't use p but the raw address (v9-style) → A! Then:
- block 2: A = &D_800B99DC (materialized in v0 at 17-18) and the load's address = A → `lhu v0,0(v0)` — hmm, the target has `lhu v0,0(s0)`. ✗

Hmm!! So the target's load uses s0 = the copy's destination, so the copy must precede the load → the copy is in block 2 → the source A must be set in block 1 → the materialization in block 1 ✗.

CONTRADICTION. So the copy's source is NOT a pseudo set in a previous block. It must be a hard reg (v0) — i.e., the asm.

Hmm, unless the materialization is in block 1 but SCHEDULED after the branch? Impossible.

Hmm, unless... the early-return branch's block structure is different: what if the assignment is in block 1 and the "materialization" (lui/addiu) is in block 2 because the PSEUDO A is assigned in block 1 but its VALUE is materialized lazily in block 2 by reload?! YES!!! That's how reload works: the pseudo A is assigned a constant in block 1; reload materializes the constant into A's register — and reload can do that at A's USE point (in block 2)! Actually, reload inserts the constant materialization right before the first use in the block where it's needed, or at the definition point. Hmm, reload typically materializes a CONST pseudo's value at its definition point... but if the pseudo is defined in block 1 and used in block 2, the materialization goes in block 1 (at the definition) — because reload1 assigns the "reload insn" at the def.

Hmm, but the target's materialization is at 17-18 which is in block 2 (after the branch at 12). If the definition were in block 1, the materialization would be in block 1 (insns 9-11).

Hmm, unless gcc's scheduler moved the `lui v0` from block 1 to block 2? Not possible across blocks.

Hmm, OK, BUT: what if the early-return branch is at insn 12 and the materialization at 17-18 is in block 2, and the definition of A is ALSO in block 2, and the copy p = A is in block 3 (the loop) — and the preheader's load at 22 uses... hmm.

WAIT. What if the preheader's load `lhu v0,0(s0)` uses s0 = p, and p is defined in block 2 by the copy p = A?! And A is defined in block 2 as well (A = &D_800B99DC), and cse's forward scan...

ARGH. The only way: cse's forward scan must NOT forward A's value to p. Within the same block, cse's forward scan WILL forward (as v11 showed: the double assignment was forwarded).

Hmm, unless the copy is not a plain copy but a MODE-changing copy! Let me reconsider: `p = (u16 *)A;` where A is `u16 *` — same mode. But what if A is declared as a `void *` or `char *`? Still Pmode.

Hmm, what if A is an INTEGER holding the address? `s32 A = (s32)&D_800B99DC;` → folds to a constant → the reloc would be lost ✗.

Hmm, what if A is declared as `u8 *` and p as `u16 *`? Both Pmode.

What about a copy that changes the mode: from a POINTER to an INTEGER and back? `p = (u16 *)(s32)A;` — the (s32) cast of a pointer to a global folds to a constant ✗ (loses the reloc).

Hmm, does it? Let me check fold-const.c's fold_convert for pointer→integer.

If (s32)&D_800B99DC does NOT fold to a constant (because gcc keeps it as a MEM or as the address), then `p = (u16 *)(s32)A` could be a real mode-changing copy → the copy survives → and the materialization would be `lui v0; addiu v0,v0,0` (the address into v0) + `move s0,v0` ✓✓✓!!!

Let me check fold-const.c.

Actually, on MIPS (32-bit), casting a pointer to `unsigned int` is a no-op in size; gcc's fold_convert has:

```c
    case INTEGER_MODE:
      if (POINTER_SIZE == GET_MODE_SIZE (mode)
	  && (GET_MODE (x) == mode || ...))
	{
	  ...
	  /* Only do this if the address is a constant. */
```
Let me actually read it.

Let me grep fold-const.c for "POINTER_SIZE".
