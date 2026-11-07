---
ts: 2026-11-06T23:50:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UQHfI7Hg4rGJxEndGVbe
---
All still 160 insns — the copy is folded in every case. So cse/combine removes it. Hmm.

Wait — the copy `p = q` where q = &D_800C7C60. The frontend probably doesn't even create two pseudos; it might fold `p = q` at the tree level into `p = &D_800C7C60`.

Hmm. What if the copy is a *different value* so the compiler must emit it? Like p = q where q is computed at runtime (not a constant). But we need the address.

Wait, actually — in the target the extra insn is `move a3,v0` where v0 holds the address. What if instead of a copy of the address, we make p hold the address through a runtime-dependent path that still yields the same value? E.g.:

p = &D_800C7C60; and q = &D_800C7C60; then p = q? same.

Hmm, what if the store is `*p = val` and p must equal &D_800C7C60, but we compute p from another pointer variable that holds the address. E.g. `p = base + 0x...`? No, base is D_800AF630.

Hmm, what about using `&D_800C7C64 - 1`? That's the same address but computed as an add from a different symbol. The target's insns: lui v0, D_800C7C60 reloc; addiu v0, v0, 0 reloc. So it IS the D_800C7C60 symbol. If we wrote `(s32 *)&D_800C7C64 - 1`, the reloc would be D_800C7C64 and the addiu offset -4. Different bytes. No.

OK so the address must be materialized into v0 and copied to a3. Both must be distinct pseudos and the copy must survive.

Why does cse merge? Because `p = q` with q known = address constant: cse replaces p's uses with q, and then... wait, if p is replaced by q, then q's reg holds the address, and the store uses it. Then combine/reload allocates one reg. So one insn pair.

The only way to keep two regs is if the copy insn exists in the final code. Combine could still merge a copy into a store if the copy's dest dies. Here p is used twice, so it can't die. So the copy should survive IF it's a real RTL copy `set p q` with q a different pseudo.

The problem is cse1 deleting it via make_regs_eqv.

So: prevent cse1 from equating p and q. The asm did it because cse's table was invalidated.

What invalidates cse's table between the address computation and the copy?
- an asm (not allowed)
- a call (cse clears table at calls? let's check cse.c)
- a label? Actually `cse_basic_block` starts fresh at a label (jump target).

Ooh — a LABEL! If the copy is in a different basic block than the address computation, cse's equivalence doesn't carry across blocks. So: put the address computation before a branch and the copy after the join? Hmm, but there's no branch there.

But wait: cse1 processes each basic block separately (cse_basic_block). Equivalences do NOT cross basic block boundaries (they're invalidated at labels). Actually cse1 can carry equivalences across blocks in some cases (it records at block end?) — in gcc 2.7.2, cse_basic_block handles one extended basic block, and equivalences are NOT propagated across basic block boundaries (except via REG_EQUIV notes). Hmm, actually cse does invalidate at each block start? Let me check: cse_main calls cse_basic_block for each basic block, and at the start of each block `table` is... `cse_basic_block` does `if (prev_insn ...)`. Actually there's code that clears the table at a label unless the block is a "branch target"? Let me check.

Alternatively: use a conditional so the address is computed in one block and the copy in another. E.g.:

```
if (cond) {
    q = &D_800C7C60;
} else {
    q = &D_800C7C60;
}
p = q;
```
That's silly but maybe jump1 merges arms and cse still... hmm.

Better: the structure already has an if/else:
```
if (A || B) {
    q = &D_800C7C60;
    p = q;
    *p = val;
} else {
    p = 0;
}
```
The block containing the copy is one basic block (the then-arm). The address and copy are in the same block.

What if we restructure:
```
s32 *q = &D_800C7C60;
if (A || B) {
    p = q;
    ...
}
```
A_hoist did that: q computed in the entry block, p=q in the then block. That's across a basic block boundary! But it still folded to 160. Hmm, because cc1's frontend/copy-prop at tree level merged it (p and q are the same SSA value).

Right — the folding likely happens in the tree optimizer (or even in expand), not cse. cc1 2.7.2 has very little tree optimization. Hmm. Actually, `p = q; *p = val;` — the RTL would be two insns. Then cse1 merges.

Let me verify by looking at the RTL. Better: let me use cc1 dumps (tools/cc1_dumps_tu.sh) or a per-pass dump. But wait — this is a *body* trial; I'd need to build the TU. There's `--keep` which keeps the scratch object; maybe also the cc1 dumps.

Alternative empirical approach: try a construct that cse definitely can't equate. For instance make q a `volatile` — no (barrier lever).

What about making p's value depend on q through a real operation: `p = q + 0;` → identity, and combine folds add 0.

Hmm, what about `p = (s32 *)((u32)q ^ 0)`? identity-ish.

OK, think about the target's real source. The target was compiled from real C. So there IS a C construct. In the original game source, what would produce `lui v0; addiu v0; move a3,v0`? Perhaps:

```
s32 *q = &D_800C7C60;
p = q;
```
where q is declared `s32 *q` but with a *second assignment* elsewhere in the block, or q is used later. Let's see: in the target, v0 is reused right after for D_800A2E20, and a3 holds the address. So q dies at the copy.

What if the real source had:
```
q = &D_800C7C60;
p = q;
*p = val;
```
and cse1 did NOT merge because... hmm.

Wait, maybe the real source is:
```
D_800C7C64 = &D_800A2E20;
q = &D_800C7C60;
```
Order? no.

Let me look at the actual cse behavior. Maybe cse does NOT merge `p = q` when q is set by a constant address in the SAME block because the address is loaded as a `symbol_ref` and cse's `make_regs_eqv` canonicalization... Actually make_regs_eqv makes p equivalent to q; then when p is used, `find_best_addr` / `use` replaces p with the canonical reg. Which reg becomes canonical? From the code: NEW=p, OLD=q. If p lives longer than q, p becomes canonical (qty_first_reg = p). Then the address computation `q = &sym` is... hmm, then uses of q would be replaced by p. So the address goes into p's register, and the store uses p. Still one reg, one insn pair. Right.

But if q lives LONGER than p, q stays canonical. Then p's uses → q. Still one reg.

So cse1 always collapses a simple copy. Unless the copy is not simple (source not a reg with valid qty).

So the C must produce a copy where the source is not cse-known. E.g. the source is loaded from memory, or the copy is at a different basic block where cse's table is fresh.

A_hoist put q in the entry block and p=q in the then block. Did cse still fold? The score says 160 ins, so yes (or the frontend merged). Hmm, wait: maybe the frontend (cc1's `expand_assignment`) merged because both are the same SSA-ish value? 2.7.2 has no SSA. But `expand_expr` for `p = q` emits a copy.

Hmm, but maybe the difference: cse1 across blocks. In 2.7.2 cse_main, `cse_basic_block` is called per extended basic block; but before that, there's `cse_end_of_basic_block` and the table is cleared at each block start EXCEPT it propagates... Let me look at cse.c's main loop.
