---
ts: 2026-10-21T23:50:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xf8xmzHLyGnt4s40OLCh
---
The "giv-init fence" is an asm — banned. But the relevant note: "the giv-init MOVE (`loop.c:5556 if (reg != result) emit_move_insn`) = `addu dst,ba,$zero`" — the giv-init copy exists when the init is not coalesced.

And there's the vanilla gcc source at `tools/reference/gcc-2.7.2/`! I can READ the gcc source to understand local-alloc's coalescing! That's very useful. But it costs context. Let me be judicious.

Key question: how to prevent local-alloc from coalescing `p = pb`?

In gcc 2.7.2's local-alloc.c, `coalesce_cost` and the copy elimination. Let me look at the relevant part. Actually, there's a well-known condition in local-alloc.c:

```c
/* Return 1 if we don't want to attempt to coalesce between hard regs
   and pseudos... */
...
static int
coalesce_cost (reg, reg2)
{
  int reg_cost = 0;	/* pseudos are very expensive */
  int reg2_cost = 0;
  ...
  /* If this is a COPIED pseudo, copy the cost of the pseudo it is
     copied from.  */
  ...
  if (reg != reg2 && GET_MODE (reg) != GET_MODE (reg2))
    ...
```
and in `global_alloc`/`allocate_reg`, the copy coalescing happens in `local_alloc` via `equiv` and `reg_equiv`.

The actual coalescing of a copy `p = pb` happens in cse.c's `canon_reg` (forwarding) or in local-alloc's `reg_equiv` propagation. Hmm.

In gcc 2.7.2's local-alloc.c, `allocate_reg` → `find_reg` → and there's:
```c
      /* If we have a copy, and the destination is a pseudo, ... */
```
Hmm.

Actually the key function is `local_alloc`'s `coalesce_cost` used in `find_reg`:
```c
	  /* If this is a copy, and the source is a pseudo, ... */
```

Let me actually read the gcc source for "coalesce" in local-alloc.c. Since the tools/reference/gcc-2.7.2/ tree exists, let me grep it. This is the project's own reference — reading it is legitimate research. But it costs context. Let me grep narrowly.

Actually, maybe a faster path: think about what the LOCAL-ALLOC does with a pseudo whose reg_equiv is a symbol_ref (a "CONST" pseudo). In gcc 2.7.2, a pseudo assigned a symbol address: expand creates `(set (reg P) (symbol_ref SYM))`? No — expand creates the address as a MEM: `(set (reg P) (mem (symbol_ref SYM)))`? Hmm, for `p = &global`, expand creates `(set P (plus (symbol_ref SYM) (const 0)))`? Hmm, I think expand creates a "address" rtx.

Then local-alloc: P is a pseudo with reg_equiv = the symbol_ref (a CONST). local-alloc's `allocate_reg` will try to find a hard reg for P. Since P's value is a constant (the address), local-alloc treats it as a "CONST" pseudo and might just... hmm, in gcc 2.7.2, local-alloc doesn't do constant propagation into regs; reload does.

The KEY: in reload, a pseudo with reg_equiv = symbol_ref is a "CONST" pseudo; reload must materialize the symbol into a reg: reload's `reload` for a CONST reg_equiv calls `materialize_const` / emits `lui`+`addiu` into the reload's target reg. So p's reg would get the lui/addiu directly → `lui s0; addiu s0,s0,0`. That's the coalesced case. ✓ (matches x1/x3).

Now, when does reload instead emit a scratch + move? When the pseudo's reg_equiv is NOT a constant but another PSEUDO (i.e. a real copy). So we need p's reg_equiv to be another pseudo, not the symbol_ref.

p's reg_equiv becomes the symbol_ref because cse's canon_reg forwards pb's value to p (pb's reg_equiv = symbol_ref) — i.e., the copy `p = pb` is forwarded at the RTL level, making p a CONST pseudo.

To prevent that forwarding, the copy must not be a "canon_reg" candidate. cse's canon_reg forwards a value to a copy when the source is a pseudo with a known value. Blockers:
- The source pseudo is not a "single-set" pseudo? Hmm, canon_reg requires the reg to have only one set (in the block).
- The source's value is not a constant/simple rtx.

Hmm! So: if pb's value is NOT a simple rtx (e.g. it's a copy of a copy), canon_reg might not forward.

Hmm, so what if pb's value is itself a copy from another pseudo? Then p = pb, pb = pc, pc = symbol_ref. cse would forward the chain.

Alternatively, what if pb's value is an rtx that cse can't treat as a "simple" value — e.g. a MEM? Hmm.

Hmm, what if the source is a pseudo whose reg_equiv is a symbol_ref but the copy is "not a copy" because of a mode change?

OK, let me try the simplest thing: what if the SOURCE pb is used TWICE (so it's not a single-set pseudo that canon_reg can forward)? Then:
- pb = &D_800B99DC
- p = pb
- ... and pb used somewhere else?

But the target has no second use of the address. Hmm, unless the second use is a use of pb that generates no instructions, like `p == pb`? Hmm! A comparison would generate instructions.

Hmm.

OK, let me look at this from the "giv-init" angle mentioned in the def's comment: "loop.md L4 preheader-copy". The def's author (an earlier agent) found that the launder was needed. But maybe the ORIGINAL C (the real game code) had the assignment inside the loop and loop.c created a preheader copy. Let me look at the C: the `D_801E86BC = (*p & 1) + 3;` use of p is before the loop. Hmm.

But WAIT: what if the original C was:
```
    i = 0;
    q = &D_801E87B2;
    r = &D_8018F078;
    for (; i < 4; i++) {
        p = &D_800B99DC;     /* inside the loop */
        ...
    }
    D_801E86BC = (*p & 1) + 3;   /* hmm, after the loop */
```
No, the target has the load at 22 (preheader).

Hmm, hmm. Let me look at the target once more:

```
19 move s0,v0
20 lui s2,0x0  ; HI16 D_8018F078
21 addiu s2,s2,0
22 lhu v0,0(s0)
23 lui v1,0x0 ; HI16 D_800B99D8
24 lhu v1,0(v1)
25 andi v0,v0,0x1
26 addiu v0,v0,3
27 lui at,0x0 ; HI16 D_801E86BC
28 sw v0,0(at)
```

So the sequence: s3 = &D_801E87B2, v0→s0 = &D_800B99DC, s2 = &D_8018F078, then `*p & 1` → D_801E86BC = (*p & 1) + 3, then D_801E86C0 = D_800B99D8 (insn 23-24, 29-30).

Hmm interesting: the order of the address materializations: s3 (q), s0 (p), s2 (r). But the SOURCE order is q, p, r — matches.

But WHY would p's materialization use a different form than q's and r's?

Difference between p and q/r:
- p is `u16 *`, q and r are `s16 *`.
- p is used before the loop, q and r only inside.
- p's address is used with `*p` (a load/store of u16) and also `*p = *p + c0`.

Hmm! What if the difference is the TYPE: `u16 *p` vs `s16 *q`? The loads: `lhu v0,0(s0)` (unsigned) vs `sh` (store). q is only stored to (`*q = *p & 0xFFF` → sh). r only stored to (`*r = ...` → sh). p is loaded AND stored.

Hmm, what if p is loaded in the preheader (insn 22) and the load's base... no.

**IDEA**: What if the difference is that p's address is needed in the preheader, so p's pseudo is live from the preheader into the loop, and the *loop* needs a copy of it (the loop's own register) — that's the "preheader copy"! I.e., loop.c's "giv init" style: the preheader value is copied into the loop's register.

So if p's assignment were INSIDE the loop, loop.c would hoist it (invariant) and the preheader copy would be created. But p is used before the loop...

UNLESS the preheader use of p (`*p & 1`) is itself part of a hoisted/invariant thing! Hmm: `D_801E86BC = (*p & 1) + 3;` — is that inside the loop in the original? If the original C were:

```
for (i = 0; i < 4; i++) {
    p = &D_800B99DC;
    D_801E86BC = (*p & 1) + 3;   /* invariant, hoisted to the preheader */
    ...
}
```
then loop.c would hoist both the assignment and the invariant statement, creating a preheader copy of p!

Hmm! But then the target would have the hoisted statement in the preheader (it does: insn 22-30) and the loop would use p (s0).

And the preheader copy: loop.c hoists `p = &D_800B99DC` — the "giv init" or the copy. Hmm, but the hoisted assignment to p would just be `p = &D_800B99DC` in the preheader, with p being a register...

Hmm, but the def's comment says: "loop.md L4 preheader-copy: the target materializes &D_800B99DC into $v0 and then `addu $s0,$v0,$zero`." — so the agent found that the target's shape comes from loop.c's preheader copy. So the agent probably TRIED putting the assignment inside the loop and it didn't produce that (or they didn't try).

Let me just try it! Several variants:

y1: move `p = &D_800B99DC;` into the loop (first statement), and keep `D_801E86BC = (*p & 1) + 3;` before the loop → that would be a use-before-assign (undefined) — the compiler would still compile but p would be uninitialized. Hmm, gcc would warn but compile. The codegen: p is assigned in the loop, and used before → gcc would treat p as maybe-uninitialized. Risky but let's see.

y2: move BOTH the assignment and the `D_801E86BC = (*p & 1) + 3;` into the loop:
```
    i = 0;
    q = &D_801E87B2;
    r = &D_8018F078;
    for (; i < 4; i++) {
        s32 c0;
        p = &D_800B99DC;
        D_801E86BC = (*p & 1) + 3;
        D_801E86C0 = D_800B99D8;
        *q = *p & 0xFFF;
        ...
    }
```
Then loop.c would hoist the invariant parts (p = &D_800B99DC, D_801E86BC = ..., D_801E86C0 = ...) to the preheader, creating copies. The target's preheader has exactly: s3=q, s0=p, s2=r, then the *p&1 load, the D_800B99D8 load, the two stores, then the loop body. So the hoisted statements are in the preheader in the right order!

Hmm! And "D_801E86C0 = D_800B99D8" is loop-invariant → hoisted. In the target, insns 23-24 load D_800B99D8 into v1 and 29-30 store it. And the *p&1 load at 22.

So the preheader contains: the p materialization (with the copy), the *p&1 computation, and the D_801E86C0 assignment. That's consistent with loop.c hoisting them from the loop body!

And the ORDER: p's materialization (17-19) comes BEFORE the *p&1 (22) — consistent.

And q and r are materialized in the preheader too (15-16, 20-21) — they could be assignments before the loop OR hoisted from the loop. Hmm! If q and r were also assigned inside the loop, they'd be hoisted too — and their materializations would be direct (no copy). Why would p get a copy and not q/r?

Because p's assignment is hoisted with a "preheader copy" while q/r's are simple? Hmm.

Hmm, in loop.c's `hoistinvariant`/`maybe_replace_...`: when hoisting an assignment `x = expr` out of a loop, loop.c creates in the preheader a computation and then a copy into the loop's register. Actually loop.c's `hoistinvariant` for an assignment: it duplicates the assignment into the preheader as `x = expr` and then replaces the loop's assignment with a copy from the preheader's value: the classic "loop.c creates a copy in the preheader" — YES! loop.c's `hoistinvariant` does:

```
  /* Set up the data structures to describe the invariant value... */
  ...
  /* The value is computed in the preheader into a new reg, and the loop's
     assignment is replaced by a copy from that reg. */
```
Specifically, in gcc's loop.c `hoistinvariant`:
```c
      /* If the invariant is a copy from a source that is not a register,
	 ... */
      ...
	  /* Set up the invariant value in the preheader.  */
	  ...
	  emit_insns (seq);
```
and there's the "copy" creation:
```c
	  /* If this is the first time we have seen this invariant value,
	     create a new register to hold it.  */
```
Hmm, and there's `loop.c:5556 if (reg != result) emit_move_insn` — the giv-init copy.

OK, empiricism. Let me try y1/y2 and see. Let me write y2 (the most plausible: everything inside the loop).

Hmm, but careful: the loop body in the target is 31..96, and the preheader is 0..30. In the target, the loop body starts with `addiu a0,s3,-2` (the func_80049CAC call) — the `*q = *p & 0xFFF` store is at 37 (the delay slot of the jal at 36) and the `andi` at 35. So the loop body's first statements are `*q = *p & 0xFFF; func_80049CAC((s32)q - 2, (s32)&D_801E8788);`.

So the loop body does NOT contain the p assignment, the *p&1, or D_801E86C0 = D_800B99D8 — they're in the preheader. So the original C either had them before the loop, or they were hoisted.

Given the def has them before the loop (matching the target's preheader), and the ONLY residual is the copy — the "preheader copy" theory says the original had them INSIDE the loop and loop.c hoisted them (creating the copy).

So let me try y2: put `p = &D_800B99DC;`, `D_801E86BC = (*p & 1) + 3;`, `D_801E86C0 = D_800B99D8;` inside the loop.

Hmm, but hold on: if they're inside the loop, loop.c would hoist them to the preheader — but the ORDER of the hoisted statements vs. the other preheader code (q, r) might differ. The target's order: s3(q), s0(p), s2(r), *p&1, D_800B99D8 load+store. So q, p, r in source order, then the *p&1.

If p, *p&1, D_801E86C0 were inside the loop (at the top of the body) and q, r before the loop, the hoisting would put the hoisted statements in the preheader — in what order? loop.c hoists in the order it encounters them, appending to the preheader's sequence. The preheader would then be: q, r (original order), then the hoisted p, *p&1, D_801E86C0. But the target has q, p, r, *p&1, ... So p comes between q and r. That means p was assigned between q and r in the source, and hoisting put it... hmm, if p's assignment is in the source between q and r but inside the loop, the hoist order would be after r. ✗

Unless p's assignment is before the loop (between q and r) AND the copy comes from elsewhere.

Hmm. OK, let me consider yet another possibility for the copy: **the `*p` load in the preheader**. What if the load's address is computed as a separate expression?

Hmm, actually, WAIT. What if the source had p assigned in the preheader like `p = &D_800B99DC;` AND the preheader load `*p` is actually `*(u16 *)p` where p...

Hmm, let me think about the register allocation: s0 = p's address. p is used in the preheader (22) and in the loop. The loop crosses calls. So s0 must be live from 19 to the end of the loop. Fine.

Now, WHY would gcc materialize the symbol into v0 and copy to s0 instead of directly into s0? Because reload materializes a CONST pseudo's value into the destination reg... unless the pseudo is not CONST.

AH WAIT!!! What if p's pseudo IS live across the CALLS, and the value is a symbol address — gcc's reload would need to reload it after each call, but since it's callee-saved (s0), it's saved/restored. Fine.

Hmm, what if p is NOT the address but a DERIVED pointer? Hmm.

OK, let me try a different tactic: what if the "copy" comes from the fact that p's value is used with a *different type* in the preheader vs the loop? E.g. `*p & 1` (u16 load) in the preheader, and in the loop `*p = *p + c0` (u16 load + store). Same type.

Let me try the "two sets" approach concretely, using a legit-looking construct:

What if p is assigned TWICE in the preheader:
```
    p = &D_800B99DC;
    ...
    p = &D_800B99DC;   // ugh, identity
```

Hmm.

What about making the assignment come from a *pointer-to-pointer*:
```
    u16 *pp = &D_800B99DC;   // pp holds the address of the global
    p = pp;
```
Same as before (coalesced).

Hmm, what if the source of the copy is a **function parameter**? no.

What if we use `memcpy`? no.

OK, let me try a batch of experiments quickly:
y1: p = &D_800B99DC inside the loop (with the preheader use of p moved inside too).
y2: p = &D_800B99DC; and then p is used via a *different* variable in the preheader: e.g. `D_801E86BC = (*pp & 1) + 3;` where pp = &D_800B99DC (2 sets of the address expression? no, pp is another pseudo).

Hmm! y2 idea: introduce a second pointer variable `pp` = &D_800B99DC used ONLY in the preheader, and `p` = &D_800B99DC used in the loop. Then the address expression has 2 uses → cse creates a pseudo for the address; p = that pseudo and pp = that pseudo → both copies. Then gcc would materialize the address into ONE reg and copy to two? Hmm, the target has only ONE copy (move s0,v0) and the preheader load uses s0.

Hmm, so in the target the preheader load uses s0 — the same reg as the loop's p. So p is a single variable used in both places.

OK — let me look at the gcc source for local-alloc's coalescing to find the exact blocker. Actually, let me first try the SIMPLEST possible thing that might work: what if p is assigned in the preheader but ALSO the address is used in a way that forces a "reload" — e.g., if p were a *volatile* pointer? no.

Hmm, let me think about the "3-qty sort bug" (§34): a block with ≤3 quantities allocates in CREATION order! The preheader block has: s4 (a0), i, q, p, r, ... Hmm.

AH WAIT. **The 3-qty sort bug!** The preheader block's quantities. Hmm, that's about ORDER not copies.

Hmm, what about the "giv-init fence"? The target's `move s0,v0` — the def's comment says it's a "loop.md L4 preheader-copy". So the earlier agent concluded it comes from loop.c.

Let me just TRY the "assignment inside the loop" variant. If loop.c creates a preheader copy, we get `lui v0; addiu v0,v0,0; move s0,v0`! And the "coalesced" version (assignment before the loop) doesn't.

But as noted, the ORDER of q/p/r in the preheader must be q, p, r. If p's assignment is inside the loop, the hoisted p would come after q and r. Hmm — but wait, maybe loop.c's preheader insertion point is not at the end! loop.c inserts the hoisted code at the preheader's END (before the loop). Hmm.

Hmm, but the target has p's materialization BETWEEN q's and r's. If p's assignment were hoisted from the loop, it'd be after r's. So p's assignment must be in the source between q and r, i.e. BEFORE the loop. So the "preheader copy" theory doesn't fit the order.

Hmm, unless r's assignment is also from the loop! Let's see: if q, p are before the loop and r is inside the loop, then the preheader order would be q, p, [hoisted r] → q, p, r ✓!!! And the copy... hmm, but then r would be the one with the copy, not p.

Hmm. Unless BOTH p and r are inside the loop and q before: preheader = q, [hoisted p], [hoisted r]? The hoist order within loop.c follows the loop body's statement order. If the loop body is:
```
p = &D_800B99DC;   (hmm, p is used in the preheader)
...
```

Ugh, I'm going in circles. Let me look at the actual gcc 2.7.2 loop.c to understand the preheader copy. Let me grep the reference source.

Actually — better idea: let me look at the .loop dump! The project has cc1_dumps_tu.sh which dumps passes. I can dump the .loop pass for the candidate and see what loop.c does. But the brief says hdump.sh needs an absolute outdir under my shard dir, and cc1 dumps are big.

Hmm, time is limited (20-30 min per item). I've spent ~15 min on this item.

Let me take stock: 6 items, 2 cracked (one prior). This one is hard. Let me try a couple of quick experiments (each ~25s) and then decide.

Quick experiments:
e1: p's assignment inside the loop, with the *p&1 and D_801E86C0 assignments also inside the loop (all three hoisted).
e2: p's assignment inside the loop, *p&1 etc. before the loop (use before assign — gcc will still compile; the value would be garbage but the codegen might match).

Let me try e1 first.

Actually, hold on. Let me reconsider the problem completely differently!

**What if the copy is produced by the C0505 move "pointer reuse" — i.e., p is assigned from a pointer variable that is ALSO used for something else?**

Or **what if p is assigned in the preheader and the SAME address is used for a different variable that is assigned in the loop**?

Hmm, let me think about what makes gcc's reload emit `lui v0; addiu v0,v0,0; move s0,v0`:
- The pseudo for the symbol address is a CONST pseudo (reg_equiv = symbol_ref).
- Its destination register is s0.
- reload emits the materialization into a SCRATCH reg and copies.

When does reload use a scratch? When the value must be built with a lui+addiu pair and the destination reg is... hmm, reload's `reload` for a CONST reg_equiv: it calls `reload_in_non_pseudo_reg` or, for a pseudo with a constant reg_equiv, `materialize_const`? Hmm.

In gcc 2.7.2's reload.c, `reload()`:
```c
	  /* If this is a constant, ... */
	  if (GET_CODE (reg_equiv) == CONST)
	    ...
```
and there's:
```c
	  /* If this is a symbol ref, ... */
```
Hmm, actually in reload.c, for a pseudo with reg_equiv = (symbol_ref), the "reload" would emit the address computation into the destination register. But if the destination register is a hard reg that can't be used (e.g. because the lui/addiu needs a specific reg), reload might use a scratch.

Hmm, here's a KEY possibility: **the symbol's address needs %hi and %lo, and on MIPS the `lui`+`addiu` pair must go into the SAME register.** If the destination is s0, that's fine.

Hmm, so why the copy?

**AH — I BET I KNOW!** The `lui v0 / addiu v0,v0,0` pair: in gcc 2.7.2's mips backend, when a symbol address is needed in a register, the pattern is `lui reg,%hi(sym); addiu reg,reg,%lo(sym)`. But if the symbol is accessed with a "mips_split_symbol" or the address is a "CONST" pseudo needing the HI16/LO16 relocation, gcc may need a scratch for the `lui` because the destination pseudo is... hmm.

Actually, you know what? Let me look at the target's OTHER symbols: s3 = &D_801E87B2 → `lui s3; addiu s3,s3,0` — direct. So the same pattern works directly for s3. The ONLY difference for p is the extra move.

So the extra move is a genuine COPY in the original code's dataflow: two pseudos, one holding the address, one a copy.

So the original C had a copy that wasn't coalesced. In gcc 2.7.2, local-alloc's copy coalescing is defeated when the copy's destination is a pseudo that is "not a simple copy" — e.g., when the destination is in a different basic block, or when the source's value is needed later.

**!!!** What if the source pb is used LATER (after the copy) in a way that produces no extra instructions? Hmm, e.g. `p = pb;` and then `*p` — no.

Hmm, what if the source pb is used in the preheader load and p is the loop's copy? I.e.:
```
u16 *pb = &D_800B99DC;
D_801E86BC = (*pb & 1) + 3;    /* the preheader use, via pb */
p = pb;                        /* the copy */
```
Hmm, but the target's preheader load uses s0 (the same reg as the loop's p) — `lhu v0,0(s0)`. So the preheader use is via the SAME reg. Hmm, so no separate pb.

UNLESS: the copy direction is reversed: p is the source and pb the destination? Hmm.

OK. What if the C is:
```
p = &D_800B99DC;      /* the loop's p */
```
and the preheader use `*p` is actually a different variable...

Hmm, let me count the target's uses of s0: insns 22, 32, 38, 63, 87 → 5 uses. The C's uses of p: `*p & 1` (1), `*p & 0xFFF` (1), `a0 = *p` (1), `*p & 0x1C` (1), `*p = *p + c0` (2) = 6 uses. Close enough (the store `*p = *p + c0` has a load+store = 2 uses; the target at 87 `lhu v0,0(s0)` and 91 `sh v0,0(s0)`).

So all uses go through s0. One variable.

So the copy `move s0,v0` has a source (v0) that is dead right after. In gcc, that's a copy whose source is dead → coalesced. To prevent coalescing, the source must NOT be dead...

**!!!!! IDEA !!!!!** What if the source of the copy is a pseudo that is live ACROSS THE LOOP but in a way that... no.

**!!!!! IDEA 2 !!!!!** What if the copy is not a copy at all in the RTL, but the result of the "address" being needed in a register that is later moved? Like gcc's `mips_...`?

Hmm, let me look at this from the "what if the assignment is `p = &D_800B99DC;` but D_800B99DC is accessed through a DIFFERENT symbol spelling"? E.g., the target's reloc is HI16 D_800B99DC / LO16 D_800B99DC. If the C used a different but equivalent address (e.g. `D_800B99DC + 0`), the reloc would differ. The masked diff compares reloc operands, so the symbol must be the same.

Hmm, what if the C used `&D_800B99DC` where D_800B99DC is an `extern u16 D_800B99DC[]` array vs a scalar? Same address.

**IDEA 3**: What if the copy is created because p is assigned in a BLOCK SCOPE and the value is used after? no.

**IDEA 4 (promising!)**: What if the C has TWO assignments to p in the preheader, where the first is dead:
```
p = &D_800B99DC;   /* set 1 */
p = &D_800B99DC;   /* set 2 */
```
Hmm, gcc's cse would forward set1 to set2 and delete one. ✗

**IDEA 5 (promising!)**: What if p's address is computed via an expression that involves a LOAD, e.g. `p = (u16 *)&D_800B99DC;` vs `p = (u16 *)(D_800B99DC_ptr)`? The latter would be a load. ✗ (target has lui/addiu)

**IDEA 6**: What if the address is materialized by gcc's "mips_..." for a symbol in a *different section*? Hmm.

**IDEA 7 (VERY promising!)**: What if the C is:
```
    p = &D_800B99DC;
```
but the symbol D_800B99DC is accessed with an ADDEND of 0 in a way that produces `lui v0; addiu v0,v0,0` (two insns) vs `lui s0; addiu s0,s0,0`? Both are 2 insns. The difference is just which reg.

Hmm, what if the C computes the address as `&D_800B99DC` where the address is used in a context requiring a caller-saved reg (e.g. as a call argument) AND in a context requiring a callee-saved reg? Then gcc would materialize into a caller-saved reg and copy.

In the target, is &D_800B99DC passed to a call? Let me look... The calls: func_80049CAC((s32)q - 2, (s32)&D_801E8788), func_8012F14C((s32)&D_801E8788, (s32)r - 4, (s32)buf), func_8012C51C(&sp, s4), func_8018623C(0x4D6, 0), func_8013C9C4((s32)D_8018B358). No D_800B99DC.

Hmm.

**IDEA 8**: What if p's value is used in the preheader load, and the preheader load's address is computed separately? Like the C is `D_801E86BC = (*(u16 *)&D_800B99DC & 1) + 3;` and p is separately `p = &D_800B99DC;`? Then the address expression appears twice → cse creates a pseudo → the pseudo is CONST (symbol_ref) → used twice → hmm, and p = the pseudo → a copy!

Hmm! Let's think: `*(u16 *)&D_800B99DC` → a MEM with address (symbol_ref D_800B99DC). And `p = &D_800B99DC` → p = (symbol_ref D_800B99DC). cse's find_best_addr might replace the MEM's address with a register... Hmm.

That would give: the MEM's address computed into a reg (v0?) and p = the same reg. Hmm.

But then the preheader load would be `lhu v0,0(v0)`? The target has `lhu v0,0(s0)`. ✗

OK, I'm burning time. Let me do the empirical batch NOW: try 3-4 variants in sequence, and if none works, record a WALL for this item and move on (I have 4 more items; the brief says 20-30 min per item, and a wall is a legitimate outcome).

Variants to try:
v1: p = &D_800B99DC inside the loop body (with the preheader uses moved inside the loop as well).
v2: `u16 *pb = &D_800B99DC;` then `p = pb;` where pb is ALSO used in the preheader: `D_801E86BC = (*pb & 1) + 3;` and p used in the loop only.
v3: p = &D_800B99DC; and in the loop, `p = p;`? no.
v4: The "dead-reset" style: since the issue is a missing COPY, maybe use a different trick: make p's value come from an expression with two sets.

Let me do v1 and v2.

v2 is interesting: it gives the address two USES (pb in the preheader, p in the loop) → the address pseudo has 2 uses → cse creates a pseudo → the pseudo is CONST → materialized into a reg. But which reg? If the pseudo is used in the preheader (before any call) it could be a caller-saved reg (v0)... and then p = that reg would be a copy — but p is live across calls, so p must be an $s reg → `move s0,v0`!!! ✓✓✓

THAT'S IT! The copy appears when the address value is materialized into a caller-saved reg (because its first use is before any call) and then copied into a callee-saved reg (because p lives across calls).

But in the target, the preheader load uses s0, not v0. Hmm. So the address's materialization reg IS s0 and the copy source v0 is dead.

Hmm. Unless: the address pseudo is materialized in v0 (its first use context), and the preheader load `lhu v0,0(s0)` uses s0 — so the load's address reg is s0, meaning the pseudo was assigned to s0 and the copy is v0→s0 (v0 = the materialization reg, s0 = the pseudo's reg). So: the pseudo (CONST, symbol_ref) is allocated s0, and reload materializes the symbol into a scratch v0 and copies to s0.

YES — that's the reload behavior for a CONST pseudo in a *callee-saved* reg! Because reload must save/restore s0 across calls and can't rebuild a symbol address in s0 directly? Hmm, no...

OK: when does reload materialize a CONST pseudo via a scratch + move? In reload.c, `reload()`:
```c
	  /* If this is a constant, ... */
```
Hmm, there's a known gcc behavior: a CONST pseudo (reg_equiv = symbol_ref) allocated to a hard reg gets the lui/addiu directly in that reg (that's the s3 case). So why would p differ?

DIFFERENCE: p's value is used at 22 (the preheader load) — hmm, s3's value (q) is used only in the loop.

Hmm, what if the difference is that p is used in a MEM (the load `*p`) while q and r are used in MEMs too (`*q = ...` store, `*r = ...` store). Hmm, q and r are only STORED to; p is LOADED from and stored to.

Hmm! The load `*p` in the preheader — the load's address needs a reg; the load is `lhu v0,0(s0)`.

OK. Hmm, let me think about gcc's find_best_addr (from the doc row 6): "an address in the table is replaced by the cheapest equivalent — ADDRESS_COST(REG)=1 vs SYMBOL_REF = 2 → every (mem (symbol)) in the EBB becomes (mem (reg))". So for a MEM whose address is a symbol_ref, cse replaces the address with a REGISTER holding that address (if a reg is available). "the pseudo then survives calls and crosses them in an $s-reg".

So: the MEM `*p` (the preheader load) has address (symbol_ref) → hmm, no: `*p` where p is a variable → the MEM's address is p's value (a pseudo), not a symbol_ref. But after cse's canon_reg, p's value is (symbol_ref D_800B99DC) → the MEM becomes (mem (symbol_ref)) → then find_best_addr replaces it with (mem (reg)) where reg holds the address!

THAT'S THE MECHANISM! The MEM's address (symbol_ref) is replaced by a REGISTER (because ADDRESS_COST(REG)=1 < SYMBOL_REF=2). The register holding the address is a pseudo → and that pseudo is the one that crosses calls in an $s-reg.

And the materialization: the pseudo holds the symbol address; reload materializes it into a reg. If the pseudo is a CONST pseudo (reg_equiv = symbol_ref) allocated to s0 → `lui s0; addiu s0,s0,0`. Hmm, still direct.

BUT: if the pseudo is NOT a CONST pseudo (i.e. it's a real pseudo whose value is a copy of another pseudo), then reload emits the source's value and copies.

Hmm, so we need: the address pseudo to be a real pseudo (not CONST) — i.e., p's value = a copy of another pseudo's value.

And the source pseudo (holding the symbol) would be materialized in v0 and copied to s0. The source is short-lived → v0 (caller-saved). ✓✓

So: we need the address to be computed into one pseudo and then copied into another, WITHOUT coalescing. The asm did it.

How to prevent coalescing in real C? The copy `p = pb` is coalesced because pb is dead after and cse forwards it.

**What if pb is NOT dead after the copy — because it's used in a MEM that cse turns into (mem (reg))?** Hmm, circular.

**What if the copy is `p = pb` where pb is a pseudo whose value is a symbol_ref, and the coalescing is blocked because p is in a different basic block?** Hmm! Coalescing across blocks: cse's canon_reg forwards within a block; local-alloc's coalescing works on the whole function.

Hmm, what if p is assigned in one block and pb in another? Both in the preheader here.

OK, let me try the most promising real-C trick I can think of: **give pb a second use that is FREE (generates no instructions)**.

Hmm, what generates no instructions? A comparison would. An assignment to a dead variable: `dead = pb;`? Hmm, that's a copy.

What about: `if (pb == p) {}` — generates a branch.

Hmm, what about `p = pb;` where pb is ALSO the value stored...

AH WAIT!!! **What about using pb as the ARGUMENT to the same expression?** Like:

```
u16 *pb = &D_800B99DC;
p = pb;
D_801E86BC = (*pb & 1) + 3;   /* pb used in the preheader */
```
Then pb has 2 uses: the copy to p and the load. The load's MEM address = pb's value (symbol_ref) → find_best_addr → (mem (reg)) where reg = the reg holding the address. Since the address is used twice (p and the load), cse creates a pseudo for it → the pseudo is the address holder → allocated s0 (crosses calls) → and the materialization...

Hmm, and pb (the local variable) would be coalesced with the address pseudo → the address pseudo IS pb → so p = pb is a copy of pb into p, where pb = the address pseudo (a CONST pseudo? or a real pseudo?).

If the address pseudo is a real pseudo (because it's used by a MEM via find_best_addr), then reload would need to materialize the symbol into it: the pseudo's reg_equiv = symbol_ref → reload emits lui/addiu into the pseudo's reg (s0) → `lui s0; addiu s0,s0,0` — direct again. Hmm, unless reload uses a scratch because the pseudo's reg_equiv is a symbol_ref AND the pseudo needs to be in a specific reg...

Hmm! Actually, here's the thing: **reload in gcc 2.7.2 CANNOT put a symbol_ref directly into a pseudo's reg if the pseudo is a "CONST" pseudo — it materializes it via `mips_...`**. Hmm, no: reload's `reload` for a CONST reg_equiv emits the const into the reg via `emit_move_insn` after `reload_in_const_mode`...

Honestly: EMPIRICISM. Let me try v2 (pb used in the preheader load + copied to p) and v1 (assignment inside the loop). Let me write both and score.

v2:
```
    i = 0;
    q = &D_801E87B2;
    {
        u16 *pb = &D_800B99DC;
        p = pb;
        D_801E86BC = (*pb & 1) + 3;
    }
    r = &D_8018F078;
    D_801E86C0 = D_800B99D8;
```
Hmm, the statement order: the target's preheader has q, p, r materializations then the *p&1. So the *p&1 comes after r's materialization. In my v2, the *pb&1 is before r's materialization → different order → the load would be scheduled differently. Hmm. Let me instead:

```
    i = 0;
    q = &D_801E87B2;
    {
        u16 *pb = &D_800B99DC;
        p = pb;
    }
    r = &D_8018F078;
    D_801E86BC = (*pb & 1) + 3;    /* pb used here — but pb is out of scope! */
```
Need pb in function scope. OK:
```
    u16 *pb;
    i = 0;
    q = &D_801E87B2;
    pb = &D_800B99DC;
    p = pb;
    r = &D_8018F078;
    D_801E86BC = (*pb & 1) + 3;
    D_801E86C0 = D_800B99D8;
```
Hmm, but this changes the decl list (adds pb) — allowed ("decl order/scope" is in the catalog).

Let me try that as v2. And v1 (assignment in the loop).

Let me write v2 first.
