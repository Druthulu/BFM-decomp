---
ts: 2026-10-22T09:02:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_z6dtA2j6M6O2uO31fZNb
---
Very interesting! In d2 (the second store uses ptr instead of q):
- The first store's base is a0 (q) and the second store's base is s1 (ptr — now live across the call → callee-saved s1!).

So the address copies went to a0 (for q) and s1 (for ptr, which is call-crossing).

So the address copy DOES pick a call-clobbered reg (a0) when the value isn't live across the call, and a callee-saved one when it is.

Hmm, so the choice of a0 among {v0, v1, a0}: the call-crossing rule explains s1. But why a0 and not v1?

Let me test: what if the q value were live across the call (i.e. the second store after the call)? Then q would be in a callee-saved reg (s1/s2) ✗ (the target has v1).

Hmm.

OK, let me try ONE more idea to get v1: what if the *value* (val) is what's live across... no.

Hmm, what if there were an extra *live* value in v0 at the address copy point? Hmm.

Let me think about local_alloc's find_reg for the hard reg copy: local-alloc.c (2.7):

```c
/* Find a block in which REG is available... */
static int
find_reg (reg, class, qty, n, life, ...)
```
Hmm.

And there's this in local-alloc.c (2.7):
```c
	  /* If this is a hard reg copy, and the reg is not used elsewhere in this
	     block, use it. */
```

Hmm, and importantly, in local-alloc.c there's the notion of "local_reg" and the copy's reg is chosen by `find_reg` which iterates over the class's regs in order and checks `reg_occupied[j][r]` (per block) and `regs_ever_live`.

In the join block: v0 is occupied? The call result (v0) is at insn 107, after the address copy at 101. But `reg_occupied` in local_alloc is computed per-block as a whole: "reg_occupied[block][reg]" is set if the reg is used anywhere in the block! So v0 IS occupied in block 9 (the call result and the return value) → v0 is out ✓. v1: is v1 occupied in block 9? Hmm — v1 is used in blocks 0, 2, 5 (the switch value, the const/slt) but NOT in block 9 → v1 should be free in block 9!

Hmm, unless `regs_ever_live` (function-wide) is the test: v1 is used elsewhere → out. And a0 is used elsewhere → also out?! Hmm, but a0 was chosen.

Hmm! Unless the test is "the reg is occupied in this block" — then v1 (not occupied in block 9) would be chosen over a0 (not occupied in block 9 either). Hmm, both free in block 9 → the first in regno order: v0 (occupied → out), v1 (free → IN!). So v1 should be chosen. But a0 was.

ARGH.

Unless the scan order is not v0, v1, a0. K3 says: "MIPS defines no REG_ALLOC_ORDER → every scan is plain regno order: $v0,$v1,$a0..$a3,$t0..$t7,$s0..$s7,$t8,$t9,$fp". So v1 before a0.

Hmm, so v1 must be excluded for another reason: maybe because v1 is *reserved* by the local allocation of the const/slt pseudos? Hmm! Local_alloc assigns hard regs to the local qtys FIRST (the const 36864 → v1 in blocks 2/5, the slt → v1). Then, for the hard reg copy in block 9, local_alloc's find_reg checks the regs already assigned to other qtys... but those are in different blocks. Hmm, but maybe local_alloc's `reg_occupied` is a 2D array [block][reg] — per block ✓.

Hmm, but there's ALSO the global "local_reg" bookkeeping: in local-alloc.c, when a qty gets a hard reg, it sets `local_reg[regno] = qty` — a SINGLE global mapping per reg! And `local_reg_n_refs` etc. So if the const qty in block 2 got v1, then `local_reg[3] = qty` — and later, when allocating the hard reg copy in block 9, find_reg might skip regs that have `local_reg[r] != 0` (i.e. already used by another qty) unless the block allows sharing!

YES — that's likely: local_alloc's find_reg has:
```c
	  /* Don't use a reg that is already occupied by a local qty in another block,
	     unless we can prove they don't conflict... */
```
Hmm, in local-alloc.c (2.7) find_reg:
```c
      /* If we are allocating a hard reg for a local qty, and the reg is
	 already allocated to another qty, check whether they conflict. */
```
Something like that. So v1 is taken by the const/slt qtys (in blocks 2/5) → not available for the hard reg copy in block 9 → the next: a0 ✓✓✓ (a0 isn't used by any local qty — the call-arg copies are hard-reg copies, not qtys).

So the mechanism: v1 is consumed by the local const/slt pseudos (in blocks 2/5), so the address copy in block 9 takes a0.

Interesting! But wait: in the TARGET (pinned), the const/slt are ALSO in v1 (blocks 2/5) and the q is hard $3 (no address copy needed since the base is already a hard reg) ✓.

So: in a lever-free version, the address copy for the store's base needs a hard reg that is not already used by a local qty. v0 (used by the call-result qty? hmm, the call result is a pseudo → a local qty → v0!), v1 (the const/slt qtys) → so a0 is the first free ✓✓✓.

So to make the address copy take v1, the const/slt pseudos must NOT take v1! But the target requires the const 0x9000 in v1 (in the arms)!

Hmm!!! Wait, does it? The target: `li v1,0x9000; slt v1,v1,v0`. Yes, v1.

Hmm, so v1 is taken by the const qty → the address copy takes a0.

Hmm, BUT: the const qty is in blocks 2/5 and the address copy is in block 9. If the reg-availability check were per-block, v1 would be free in block 9. The evidence says it's not (a0 was chosen).

Hmm, but hold on: local_alloc assigns the local qtys in some order. The const qty (r78) in block 2: the available regs in block 2: v0 (the call result qty r77 → v0?), v1, a0... The scan picks the first free: v0 is occupied (the call result), so v1 ✓ (the target agrees).

Then the slt qty (r79) in block 2: v0 (the call result is dead by then? the slt uses v0 → the call result is live at the slt) → v0 occupied → v1 (the const died at the slt? no, the const is an operand of the slt, so it's live AT the slt) → hmm, the slt's dest could be v0 (the call result dies at the slt) → but the target has the slt result in v1! (`slt v1,v1,v0` — the dest is v1, overwriting the const ✓). So the slt qty got v1 (the const's reg, freed after the slt).

So in block 2, the qtys: r77 (call result) → v0, r78 (const) → v1, r79 (slt) → v1.

Then in block 9 (the join): the hard reg copy for the address → the available regs: v0 (occupied by a qty in another block? hmm, the call-result qty r77 is in blocks 2/5), v1 (occupied by the const qty r78 in blocks 2/5) → a0 ✓.

So local_alloc's find_reg seems to treat a reg as unavailable if ANY qty in the function has it (not per-block). That's the "local_reg[reg]" single-mapping behavior.

So: to free v1 for the address copy, the const/slt qtys must not take v1. But the target needs them in v1!

Hmm, unless the const/slt take v1 in a *different* way: what if the const 0x9000 were NOT a pseudo but a hard reg in the RTL? Hmm! If the constant were materialized in the RTL as a hard reg (v1), then it wouldn't be a local qty and wouldn't block v1!

Hmm, how would a constant become a hard reg in the RTL? Hmm.

Hmm! What if the comparison were done with a *hard reg* operand? Hmm.

Hmm, what if the constant 36864 were part of a *larger* expression that gcc keeps in a hard reg? Hmm.

Alternatively: what if the const/slt qtys took a DIFFERENT reg than v1 in the lever-free version, freeing v1 for the address copy? Then the target's `li v1,0x9000` wouldn't match ✗.

Hmm, wait. Hmm! What if the *order* of the local qtys changed: what if the address copy's reg were chosen BEFORE the const qty got v1? The order of local_alloc's processing is by qty priority. Hmm, if the address copy's qty had a HIGHER priority than the const qty, the address copy would take v1 (the first free after v0) and the const would take a0?? Then the target's `li v1,0x9000` would be `li a0,0x9000` ✗.

Hmm, unless... the const takes v1 and the address copy takes v1 TOO (they're in different blocks!). If the reg-availability check is per-block for qtys (which it must be, since the same reg is used by qtys in blocks 2, 5, and also 0/1: r84/r85 → v0 in blocks 0/1 and r77/r80 → v0 in blocks 2/5 — the same reg v0 in different blocks ✓ so the check IS per-block for qtys!).

Hmm! So qtys CAN share regs across blocks. Then why is v1 not available for the address copy in block 9?

Hmm, because the address copy is not a qty but a "hard reg copy" (a copy into a hard reg for an operand). In local-alloc.c, the hard reg copies are handled by a separate mechanism (`hard_reg_copy`), and their reg choice is made by `find_reg` with a *global* constraint: the hard reg copy's reg must not conflict with any qty's reg assignment in the *same block*... Hmm.

Hmm, in local-alloc.c (2.7) there's:

```c
  /* Now allocate the hard regs for the hard reg copies... */
  for (i = 0; i < n; i++)  /* over hard_reg_copy entries */
    {
      ...
      reg = find_reg (class, 0, 0, ...);
```
and find_reg has the "reg_occupied" per-block check plus:
```c
	      /* If the reg is used by a local qty in a block where our copy is live... */
```

Hmm, in GCC 2.7's local-alloc.c, the hard reg copy mechanism: `hard_reg_copy` is indexed by [insn][operand] and the copies are made in `reload`? Hmm, actually I recall in GCC 2.7 local-alloc.c:

```c
/* Return true if we can use REG for the hard reg copy... */
```

OK. Whatever the exact rule, the EMPIRICAL finding is: the address copy lands in a0 while v1 is "used" by the const/slt qtys (in other blocks). And v0 is used by the call-result qty.

Hmm! So the rule might be: the hard reg copy's reg must not be used by ANY qty in the function (a global restriction, because the copy's value is live across the block and the qty's reg is live in another block — conservative). So v0 (the call-result qty) and v1 (the const qty) are excluded → a0 (no qty uses a0) ✓✓✓.

Hmm, but a0 IS used by the call-arg copies (hard reg copies too!). Hmm, those are hard reg copies as well, so they'd also be excluded... but they got a0. Hmm, maybe the rule is: the hard reg copies are allocated in order, each taking a reg not used by a *qty* (and not conflicting with the other copies).

So: the address copy's reg ∈ {regs not used by any qty} = {a0, a1, a2, a3, t0-t9, s1-s7, ...} → the first in regno order = a0 ✓.

And in the target, the base is a hard reg ($3) — no copy needed.

CONCLUSION for item 1: the q pseudo's register is decided by a hard-reg copy of the store's base, which local_alloc puts in the first reg not used by any local qty — a0 — and the copy then becomes the q pseudo's preference, so global_alloc gives q → a0. To get $3, the constant/slt qtys must not hold $3 — but the target requires `li v1,0x9000`/`slt v1,v1,v0` there.

Hmm, hold on!! What if the *constant* 0x9000 were in v1 as a HARD REG in the RTL (not a qty)? Then v1 wouldn't be "used by a qty" → the address copy could take v1 ✓✓. And the asm would be `li v1,0x9000` ✓ (a hard reg use of v1 → the const would be materialized... hmm, but then the const would be a hard reg in the RTL: `(set (reg:SI 3 v1) (const_int 36864))` — hmm, would gcc do that? Only if the const is a hard reg in the RTL (e.g. from a copy).

Hmm! Here's a thought: what if the comparison were against a *variable* (not a literal)? E.g. if the source had a local `s32 lim = 0x9000;` — then the const would be a pseudo (a qty) → the same problem, and the asm would differ (the li would be outside the loop...). Hmm, but wait: the C0505 catalog mentions "THE RELOAD-REMAT CONSTANT: a FUNCTION-SCOPE single-set local, assigned once at entry, used constant-first" (cookbook §368)! That technique makes a constant a *rematerializable* pseudo.

Hmm! But the target's `li v1,0x9000` is inside the arm block (per-arm). If the const were a function-scope local assigned at entry, the `li` would be at the entry (hoisted) → the asm would differ ✗ (the target has the li in each arm).

Hmm, but hold on: what if the const were a function-scope local *assigned in the arm*? Hmm, "assigned once at entry" is the technique; but a local assigned in the arm would be a local qty in that block → same as now.

Hmm, hmm. But here's the thing: if the const 0x9000 were a *rematerializable* pseudo (reg_equiv_constant), then reload would rematerialize it (`li v1,0x9000` right before the slt) — and the *hard reg* used for the remat is chosen by reload's order_regs_for_reload = "the first wholly-UNUSED call-clobbered reg in regno order" → v1 (if v1 is unused elsewhere) or v0/v1... hmm.

Hmm! And the address copy: if the const is rematerialized, the *qty* wouldn't hold v1 → v1 would be free for the address copy → the address copy takes v1 → q → v1 ✓✓✓!!!

Hmm!! That's a promising path: make the constant 0x9000 a *rematerializable* constant (reg_equiv_constant) so that it's not a qty holding v1.

How does a pseudo get reg_equiv_constant? When it's assigned a constant and never modified: gcc's `reg_equiv_constant` is set in flow.c for a pseudo that is assigned a constant and has no other sets (the "equivalence" mechanism) — actually, in flow.c, `reg_equiv_constant[regno]` is set for a REG whose only def is a constant (this is the "constant propagation" equivalence). Hmm, that's for the *front-end* pseudos (like `p = 3;`).

Hmm! In our case, the const 36864 (r78) is a *compiler temporary* (the literal 0x9000 in the comparison), assigned directly by expand → it gets reg_equiv_constant? The .lreg dump shows `(expr_list:REG_EQUIV (const_int 36864))` for insn 28! Yes: REG_EQUIV (const_int 36864) — so r78 IS a rematerializable constant!

Hmm, so r78 has reg_equiv_constant. But it's still a qty that takes v1 in local_alloc.

Hmm, hmm. But the cookbook §368 says: "Reload then records reg_equiv_constant, DELETES the init insn (instruction-count-neutral) and REMATERIALIZES `addiu <reload-reg>,$zero,K` immediately before each use, picking the register by reload1.c order_regs_for_reload preference rather than local-alloc's ascending scan."

So in that scenario, the constant is NOT held in a reg across the block; instead it's rematerialized before each use, in a reg chosen by reload's preference. In OUR case, the const is used ONCE (in the slt) → hmm, the current code has `li v1,0x9000; slt v1,v1,v0` — the const is materialized into v1 and the slt overwrites v1. If the const were rematerialized, we'd get the same `li v1,0x9000` but the reg would be chosen by reload's order_regs_for_reload ("the first wholly-unused call-clobbered reg in regno order") → v1 (if unused) or v0?

Hmm! In the current (non-remat) case, local_alloc gave v1 to the const qty. In the remat case, reload would pick the reg: "the first wholly-UNUSED call-clobbered reg in regno order" — v0 is used (the call result), v1: is it "wholly unused"? The switch value (r83 → v1) is a global allocated to v1 → hmm, that's after reload? No: reload runs after global alloc, so at reload time v1 IS used (by the switch value global). Hmm, so reload would pick a1? Hmm, that would give `li a1,0x9000` ✗ (the target has v1).

Hmm, wait. But hold on: in the PINNED version, the const is also rematerializable and the reload picks v1 ✓ (the target). So the pinned version's const IS rematerialized (or the local alloc gives v1).

Hmm, I can't tell from the asm alone.

OK, so how do I get the const to be rematerialized in the lever-free version? Per §368, the technique is: a FUNCTION-SCOPE single-set local assigned once at entry, used constant-first. E.g.:

```c
s32 func_801815AC(void *arg)
{
    s32 lim = 0x9000;      /* function scope, assigned once */
    s32 q;
    ...
    if (func_8012BD14(ptr) > lim) { return 0; }
```
Then `lim` is a pseudo with reg_equiv_constant → reload rematerializes it → the `li` insn is deleted from the init and rematerialized before each use. The instruction count stays the same (2 li's, one per arm) ✓✓!! And the reg for the remat is chosen by reload's preference.

Hmm! But the ORDER of the insns changes: the `li` would be right before the slt (in the arm) — the same place as now ✓.

And if the remat reg is v1 → `li v1,0x9000; slt v1,v1,v0` ✓ matching the target! And then v1 is not held by a qty → the address copy could take v1 → q → v1 ✓✓✓!!!

Hmm, but the address copy is created by LOCAL_ALLOC (before reload). Hmm! If the const is rematerialized by RELOAD (after global alloc), then at local_alloc time the const qty still holds v1 → the address copy → a0 → q → a0. Hmm!!

Unless the "hard reg copy" for the address is created by RELOAD (not local_alloc). The pass order: local_alloc → global_alloc → reload. If the address copy is created by reload, then the preference (q → a0) would be created AFTER global_alloc → the preference wouldn't exist at global_alloc time ✗ (but the .greg dump shows it!). Hmm, so the copy exists before global_alloc → created by local_alloc.

Hmm, so local_alloc creates the address copy → and the const qty holds v1 at that time → a0.

Unless the const pseudo is NOT a qty at local_alloc time. Hmm, in the current code the const 36864 is a pseudo (r78) — a qty. With the §368 technique (a function-scope local `lim = 0x9000`), the pseudo `lim` is still a pseudo at local_alloc time (with reg_equiv_constant) → still a qty → still holds v1 (or some reg) → the address copy still → a0.

Hmm! BUT: the difference is WHERE the li is emitted: with remat, the li is emitted by reload (after allocation) — so the const qty would NOT be allocated a reg at all (reload deletes the init insn and rematerializes). Hmm, but at local_alloc time, the const qty is still a qty (it has a def and a use) → it gets a reg (v1) → and the address copy is created in the same pass → a0.

Hmm, unless the const qty's live range is such that it doesn't conflict...

Hmm, hmm. But actually, hold on: if the const is rematerialized, does local_alloc still allocate it a hard reg? The qty's reg assignment happens in local_alloc regardless. But the *reload* pass then deletes the init and rematerializes. The final asm: the const would be materialized in the reload-chosen reg.

Hmm, so with the §368 technique, the asm's `li v1,0x9000` reg would be chosen by reload (order_regs_for_reload) rather than local_alloc. And the address copy would still be a0 (created at local_alloc) → q → a0 ✗.

Hmm. Hmm! Unless the address copy is created by reload too.

OK, let me just TEST the §368 technique on item 1 — it's cheap and it's a documented technique. If the const becomes rematerialized, the whole allocation might shift.

Let me write it:
```c
s32 func_801815AC(void *arg)
{
    s32 lim = 0x9000;
    s32 q;
    s32 ptr;
    u16 st;
    u16 val;

    ptr = ((Unkstruct_801815AC_2 *)arg)->unk64;
    st = ((Unkstruct_801815AC_3 *)ptr)->unk2;
    switch (st) {
    case 2:
        if (func_8012BD14(ptr) > lim) { return 0; }
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 3;
        break;
    case 1:
        if (func_8012BD14(ptr) > lim) { return 0; }
        q = ((Unkstruct_801815AC_2 *)arg)->unk64;
        val = 4;
        break;
    default:
        return 0;
    }
    ((Unkstruct_801815AC_3 *)q)->unk2 = val;
    ((Unkstruct_801815AC_3 *)q)->unk34 = 0;
    func_80178BF8();
    return (s32)func_80172710;
}
```
Let me test this and a couple of variants (lim as u16/s32, lim used in both arms, etc.).

Let me try it now.
