---
ts: 2026-10-21T23:49:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_If0EIzvSePjDYQIZdYAl
---
Same: gcc coalesces the copy.

So I need to defeat the coalescing. Per §145(b) and the cookbook, a second SET of the source pseudo would prevent the coalescing? Let's think: if pb has 2 sets, then `p = pb` copies the value of pb's second set. gcc's copy propagation (cse's canon_reg) would forward pb's value to p... and then the copy disappears entirely, giving one pseudo again.

Hmm. What if instead we make the source a value that's NOT a simple symbol address — e.g. the address computed by an expression that gcc must compute into a reg and then copy? Like `pb = &D_800B99DC;` vs `pb = (u16 *)&D_800B99DC;` — same.

What about `pb = &D_800B99DC[0];`? same.

Hmm, what if the address is of a global ARRAY and we take the address of an element at offset 0: same.

What if we use a *pointer arithmetic* that yields the same address but through a different rtx: e.g. `pb = (u16 *)((u8 *)&D_800B99DC + 0);` → same rtx.

Hmm, what if the destination p is used in a way that requires a different MODE? p is u16*. What if we declare p as `u8 *` and cast at the use sites? Then p's value is still a pointer (Pmode). ✗

What if the copy is `p = pb` where pb is `u16 *` and p is `s16 *`? Still Pmode.

Hmm.

NEW IDEA: what if we make the address's pseudo be live across a CALL in a way that forces a specific register, while the copy happens...

Hmm, let's think about the target from a different angle: WHY would the original compiler emit `lui v0; addiu v0,v0,0; move s0,v0`?

In gcc 2.7.2, the mips backend materializes a symbol address as:
```
lui reg, %hi(sym)
addiu reg, reg, %lo(sym)
```
into ONE reg. But if the pseudo holding the symbol_ref is a "CONST" pseudo, reload materializes it in a scratch reg and copies it to the destination! YES! That's the classic gcc-2.7.2 behavior: a pseudo whose reg_equiv is a symbol_ref is a "CONST" pseudo; reload (reload.c) can't put a symbol_ref directly in a register (it must be built with lui/addiu), so reload builds it in a scratch register (reload's "scratch" or a temp) and then copies it to the destination pseudo's register.

Hmm, but that would apply to q and r too (they're also symbol addresses) — and the target shows `lui s3; addiu s3,s3,0` directly. So no.

UNLESS: q and r's pseudos are "address GIVs" or their reg_equiv is a (plus (symbol_ref) (const 0))...

Hmm, hold on: maybe the difference is that p's address is used in TWO different EBBs or in a way that the pseudo is a real "reg" (not CONST).

Hmm, alternatively: maybe p's pseudo is not a CONST pseudo but a real pseudo holding a REG_EQUIV of a symbol_ref, because it was assigned from another pseudo (the copy!): `p = pb` where pb is a CONST pseudo. Then p is a real pseudo with reg_equiv = pb (a pseudo), and reload must COPY pb's value into p's register → the materialization happens in a scratch reg (v0) and then `move s0,v0`!!

But that's exactly the case in x3 (the copy pb → p)! And gcc coalesced it. Because local-alloc's coalescing merged pb and p (the copy was eliminated at the RTL level: `p = pb` where pb's reg_equiv is the symbol_ref → p's reg_equiv becomes the symbol_ref directly).

So the question becomes: how to prevent local-alloc from coalescing pb and p?

Known blockers for coalescing in gcc 2.7.2's local-alloc:
1. Different modes.
2. The source is live across a call (so it must be in an $s reg) and the destination in a different $s reg — but the source would be an $s reg, not v0.
3. **The copy's source has "n_times_set > 1"** — i.e., pb is assigned more than once. Then the "copy" p = pb is not a simple reg_equiv copy.

Hmm, so: pb assigned twice. In our case, if pb were assigned twice with the SAME value, the second set is the one copied. gcc's cse would... hmm, cse's canon_reg would forward the value. But the point is: with 2 sets, the "copy" p = pb becomes a real move (from the pseudo pb, which now has 2 sets) rather than a reg_equiv copy.

Then pb's live range: from its 2nd set to the copy — short. But pb's 2nd set is a real computation → pb is a real pseudo → the value is computed into a reg (v0) and moved to s0 ✓.

And the 1st set would be dead (deleted) or... hmm, if the 1st set is dead, gcc's flow might delete the whole thing and re-fold.

Hmm. So we need pb to have 2 sets where the 2nd is used. The 1st set must be non-dead or must not be foldable back.

Hmm, hmm. What if the 1st set of pb is USED somewhere (so it's not dead) and the 2nd set is copied to p? E.g.:

```
u16 *pb = &D_800B99DC;
... use pb somewhere ...
p = pb;
```
But then pb is live across... hmm, if pb is used at a point before the copy, its live range is short but it has 2 sets.

Hmm, wait. But if pb is used somewhere, we'd need an extra use of the address that the target doesn't have. ✗ (the target has exactly one use of the address: s0).

Hmm, what if the "2nd set" of pb comes from a *different* pointer expression that happens to be the same address? e.g. `pb = &D_800B99DC;` then `pb = (u16 *)&D_800B99DC;` — identity-ish.

OK OK. Let me step back and consider the OTHER move: what if the copy is not from a temp but the address is *passed to a function* that returns it? no.

**RADICALLY DIFFERENT IDEA**: What if we get the `move s0,v0` from a *different* source — e.g. the address is loaded from a global pointer variable? No, the target has lui/addiu with the D_800B99DC reloc.

**IDEA**: What if the value in v0 is not the address but the address is computed twice: `lui v0; addiu v0,v0,0` (v0 = &D_800B99DC) and then `move s0,v0`. What if the C is:
```
p = &D_800B99DC;
```
and gcc decided to materialize the symbol address in a scratch (because of the `addiu` needing a temp) — this is a MIPS-specific "address of a symbol in a pseudo" thing.

Hmm! What about the SYMBOL being a "small data" symbol needing $gp? D_800B99DC is a u16 global. Hmm, the target uses lui/addiu (not gp-relative), so no.

**IDEA**: What if we make the address of D_800B99DC appear in TWO different address expressions: one for a load `*p` and one for a store `*p = ...`? The target has `lhu v0,0(s0)` and `sh v0,0(s0)`. Both use s0. Hmm.

OK, let me look at this from the "what would a T10/T11 agent do" angle. This is a 5-point residual. The lever is the launder. Maybe the answer is: the copy CAN be produced in real C by a **pointer reuse** or a **declaration order** change. Hmm.

Let me try a few quick experiments:
x4: `p = &D_800B99DC;` moved to a different position (e.g. after the `D_801E86BC = (*p & 1) + 3;`? no, p is used there).

x5: declare p as `u16 *p = &D_800B99DC;` (init at decl) — no copy at all.

x6: What if the loop's `*p = *p + c0;` and `*q = *p & 0xFFF;` cause p to be a "MEM" base...

x7: What if we make p a `volatile`-qualified pointer? ✗ (volatile would change codegen).

x8: What if we split the assignment: `p = &D_800B99DC;` and then in the loop `p = p;`? Hmm.

x9: **What if we add a second use of the address in the C, in a form that generates NO extra instructions?** E.g. `*p` is used several times already. Hmm, the address of p is used at 22, 32, 38, 63, 87 — all through s0.

Hmm hold on, let me re-examine: maybe the "copy" in the target isn't a copy of the ADDRESS but something else. `lui v0, %hi(D_800B99DC); addiu v0,v0,%lo(D_800B99DC); move s0,v0`. Yes, s0 = &D_800B99DC.

Hmm, what if the original C had TWO variables: `p` and something else, both = &D_800B99DC, where the second is dead? Hmm.

What if the original C had:
```
u16 *p = &D_800B99DC;
```
where the address is ALSO used in the preheader via a different variable, e.g.:
```
D_801E86BC = (*p & 1) + 3;
```
Hmm, `*p` uses s0 in the target.

OK, let me try the experiment where the address expression appears in a form that makes gcc's cse create a pseudo that is NOT a CONST pseudo but a real pseudo.

AH WAIT!!! IDEA! What if the assignment to p is done via a **conditional expression** or a **cast that gcc can't fold**? Like:

```
p = (u16 *)((u8 *)&D_800B99DC + 0);
```
Hmm.

What about: `p = &D_800B99DC[0];` where D_800B99DC is declared as `extern u16 D_800B99DC[];` (an array!) — then `&D_800B99DC[0]` is the array's address = symbol_ref. Same.

Hmm, what if the global is accessed via a *pointer to it*? no.

**LET ME RECONSIDER THE "LOOP" ANGLE**: the comment says "loop.md L4 preheader-copy". So the mechanism they relied on was loop.c creating a preheader copy. Maybe with a different C structure, gcc's loop.c will create that copy naturally!

The preheader copy happens when the loop's live-in value is computed in the preheader. In our C, `p = &D_800B99DC;` is before the loop, so no.

But what if the ORIGINAL C had the assignment inside the loop? Let me test x2: put `p = &D_800B99DC;` as the first statement INSIDE the loop. But p is used before the loop (`D_801E86BC = (*p & 1) + 3;`). Hmm — unless that use is also restructured. In the target, insn 22 `lhu v0,0(s0)` is the `*p & 1` load in the preheader. So p is used in the preheader.

Hmm, so p is assigned before the loop and used in the preheader and in the loop.

Hmm, so where does the preheader copy come from?!

Hmm, hold on. Maybe the copy is not from loop.c at all — maybe the ORIGINAL compiler just wasn't coalescing.

Let me try the "two sets" idea concretely. What if the C is:

```
    i = 0;
    q = &D_801E87B2;
    p = &D_800B99DC;
    r = &D_8018F078;
```
and the copy appears because p's pseudo is used in the preheader at insn 22 AND the loop. Hmm.

What if the ORDER of the assignments changes: `r = &D_8018F078;` before `p = ...`? The target order is s3(q), v0/s0(p), s2(r). Hmm, that IS the source order (q, p, r). ✓ So statement order is already right.

OK, so what distinguishes p from q and r?

- q = &D_801E87B2 (s16*): used as `*q = *p & 0xFFF;` and `func_80049CAC((s32)q - 2, ...)` — in the loop only.
- r = &D_8018F078 (s16*): `*r = ...` and `func_8012F14C(..., (s32)r - 4, ...)` — in the loop only.
- p = &D_800B99DC (u16*): `*p & 1` in the PREHEADER, plus in the loop.

So p is used in the preheader! And the preheader use requires s0 to be live from insn 19.

Hmm, so why the copy? Because... the value must be in s0 for the loop (crosses calls) AND the preheader use is a *load* `lhu v0,0(s0)`.

Hmm, so both q and r are live across calls in the loop too, and they're materialized directly into $s regs (s3, s2). So p's extra copy isn't about call-crossing.

WAIT. Maybe it's about the LOAD in the preheader: `*p` in the preheader at insn 22. What if the load is what forces the copy? Like: gcc computes the address into a reg for the load, and then... no, the load uses s0 as the base.

Hmm, hold on! Let me reconsider: maybe the v0 materialization and the move s0,v0 come from the fact that p's assignment is a *preheader copy* because the loop's p is a loop-invariant assignment that was hoisted. And the preheader use `*p & 1` is the ORIGINAL use (not hoisted)...

AH, here's a coherent story! The ORIGINAL game C might be:

```
for (i = 0; i < 4; i++) {
    p = &D_800B99DC;     /* loop-invariant */
    ...
    D_801E86BC = (*p & 1) + 3;   /* hmm */
}
```

Hmm no.

Alternatively, the original C:
```
p = &D_800B99DC;
D_801E86BC = (*p & 1) + 3;
for (i = 0; i < 4; i++) { ... }
```
and the original compiler (an OLD gcc, e.g. gcc 2.7.2 from 1995? or the SGI compiler) generated the copy. Hmm, but this project's compiler IS gcc 2.7.2 (the mips cross-compiler in the toolchain). Hmm! And the target is the ORIGINAL game binary, compiled by the ORIGINAL compiler (maybe gcc 2.7.2 for the SGI or a different one).

Hmm OK. So we need gcc-2.7.2 (this project's) to emit that copy.

Let me look at the residual_moves.md doc for more insight on "copy" moves (R-rules about copies). Let me grep for "copy" rows in that doc. It mentioned "Lane B class 2 row 6". Let me read the doc's table around there — it's the project's own map of gcc behaviors. Let me read rows 1-20 of that table. It might have a row about "a copy that gcc coalesces" and how to prevent it.

Let me find the file.
