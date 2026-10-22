---
ts: 2026-10-22T08:47:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_A9rNnjAyfbsVdXANUM1D
---
The RTL in the .greg dump doesn't mention 73 anymore (it's been replaced by hard reg 4 = a0 in the insn text). So the dump shows post-allocation RTL.

Now, the "preferences: 4" for pseudo 73. In GCC 2.7's global.c, the preferences come from `reg_preferred` — hmm.

Let me think about GCC 2.7's `global.c`:

```c
/* Record the preferences of a pseudo register... */
static void
dump_global_alloc (FILE *file)
{
  int i, j, k, n;
  ...
  for (i = 0; i < n; i++)
    {
      r = regno_order[i];
      ...
      fprintf (file, ";; %d conflicts:", r);
      for (j = 0; j < n; j++)
        if (i != j && conflicts_test[j][r]) ...
      /* Print the preferences of this pseudo: the regs it prefers. */
      for (j = 0; j < n; j++)
        if (reg_preferred[j] == r) ...
```

Hmm. Alternatively, in GCC 2.7 the "preferences" printed are from the `copy` chains: `reg_preferred` is set in `global.c` by:

```c
  /* Record the copy preferences: 
     (set (reg P) (reg Q)) means P and Q prefer the same register. */
```

and in `alloc.c`, `reg_preferred[regno]` is set by `make_reg_preferred` in `local_alloc`? Hmm.

Actually, in GCC 2.7 `global.c` there's:

```c
/* Return true if we should avoid allocating a register to this pseudo ... */
...
  /* Set up the preferences: 
     For each copy (set (reg P) (reg Q)) where Q is a pseudo and P is a hard reg,
     we set reg_preferred[Q] = P. */
```

I recall in `global.c` `global_alloc()`:

```c
  /* Process all the insns in the function, looking for copies to set up
     the preferences.  */
  for (insn = first_insn; insn; insn = next_insn (insn))
    {
      ...
      if (GET_CODE (PATTERN (insn)) == SET
          && GET_CODE (SET_SRC (PATTERN (insn))) == REG
          && GET_CODE (SET_DEST (PATTERN (insn))) == REG)
        {
          r1 = REGNO (SET_SRC (PATTERN (insn)));
          r2 = REGNO (SET_DEST (PATTERN (insn)));
          if (r1 != r2 && r1 < FIRST_PSEUDO_REGISTER && r2 >= FIRST_PSEUDO_REGISTER)
            reg_preferred[r2] = r1;
          ...
        }
    }
```

So the preference for pseudo 73 = reg 4 means there's an insn `(set (reg:SI 4 a0) (reg/v:SI 73))` — a copy FROM pseudo 73 INTO a0! Where? In the join block, the store's address: `(set (mem/s:HI (plus:SI (reg/v:SI 73) 2)) ...)` — hmm, that's a memory dest.

Hmm, but wait: the RTL I dumped (.rtl) is before "expand"? The .rtl dump is after flow analysis, before reload/expand/allocation. The copy `(set (reg:SI 4 a0) (reg/v:SI 73))` might be introduced by the *reload* pass (reload.c) — which inserts copies to reload a pseudo into a hard reg for the address! Yes! In reload.c, when a pseudo is used as an address and the pseudo gets a hard reg, the reload might insert a copy into a specific hard reg (like a0) — actually, MIPS's address computation: `(plus:SI (reg r73) (const_int 2))` → the reload pass computes the address in a register: it may create `(set (reg a0) (reg r73))` and then use (plus a0, 2)? Hmm, or it keeps the offset folded.

But in the final asm we have `sh v0,2(v1)` — the address is r73+2 folded into the store, so no copy needed. But the reload pass may still have created a copy earlier (which later got optimized away or folded).

The .greg dump is printed at the start of global_alloc, which is AFTER reload. So the copy `(set (reg:SI 4 a0) (reg/v:SI 73))` would be in the .greg dump's RTL. But my grep for "73" in the .greg section found only the conflict lines — because the dump's RTL section shows the post-allocation RTL (hard regs). Hmm, but the dump prints the RTL at the time of the dump — which is after the allocation was applied (the dispositions are printed at the end of global_alloc, and the RTL dump follows). So the copies are gone (replaced by hard regs).

OK. So the mechanism: the reload pass inserted a copy of pseudo 73 (q) into hard reg a0 (because MIPS needs the address in a register for the store, and it chose a0), and that created the preference "73 prefers 4" → global_alloc gave q → a0.

If I can change the reload's choice of a0 → v1, then q would prefer v1! But the target has the store as `sh v0,2(v1)` — with v1 = q's reg.

Hmm, so in the pinned version, the reload's copy would be `(set (reg:SI 3 v1) (reg 73))`? But q is hard $3 there.

Interesting: in the pinned version, the .greg "74 preferences: 4" exists (r74 = ptr, prefers a0 — the call arg copy) and r73 (q) doesn't exist.

So the lever: make the reload's copy for the q address use v1 instead of a0. The reload pass chooses a hard reg for the address computation based on... the reload's "reload_inp" and the "scratch" regs. For MIPS, the address computation for a store with an offset: `sh v0,2(v1)` — the base is the pseudo's reg with the offset folded, no separate address reg. But the reload pass computed the address in a0 and then the final assembly folded it back? MIPS's output pattern `(set (mem (plus (reg) (const_int 2))) ...)` → "sh %v0,2(%v1)" — yes, the final assembler folds the offset.

So during reload, the address `(plus:SI (reg r73) 2)` must be computed in a register: reload inserts `(set (reg a0) (plus (reg r73) 2))` or `(set (reg a0) (reg r73))`. The choice of a0 is by reload's allocation of "scratch" hard regs, and reload prefers certain regs.

Why a0? Because at that point, the available reload regs... reload.c allocates reload regs from a list; for MIPS the reload regs might be limited. Hmm, but the target uses v1 as the base. In the pinned version, the pseudo r73 doesn't exist (q is hard $3) → the address is (plus (reg 3) 2) → no reload needed → `sh v0,2(v1)` directly.

So in the lever-free version, the address needs a reload into a hard reg, and reload picks a0.

Can I influence the reload's reg choice? If the store's address were a "plus" of the pseudo with a constant, reload computes it. If the address were just the pseudo (offset 0), reload would still need a copy.

Hmm, what if the *pointer* used in the store is a different pseudo that reload handles differently?

Alternatively: what if the stores were done via a `u16 *` pointer variable (pointer reuse)? Then the address is (plus (reg p) 2) with p a pointer pseudo. Same issue.

Hmm, what about making the store's address have a *non-constant* offset? no.

OK, alternative: the score. What if the reload picks v1 for the address copy? Then q (which prefers the copy's reg) would be allocated v1! And the local const 0x9000 (in v1) would conflict → hmm, the global q in v1 and the local const in v1 in the same block → the global alloc would refuse v1 for q (block-granular conflict) → q gets something else. Ugh. Unless the local const isn't in v1 by then.

Wait, actually, hmm: the order is local_alloc FIRST, then global_alloc. In local_alloc, the local const 0x9000 in the arm block got v1. Then global_alloc: q's candidate v1 is blocked because the local const uses v1 in the arm blocks.

BUT: what if the *reload* copy for q's address happens in the JOIN block (block 98) — where the local const is NOT live? The conflict computation for global q is block-granular: q is live in blocks 40, 71, 98. The local const is in blocks 40 and 71. So v1 is blocked in those blocks → v1 unavailable for q.

Hmm. So the const in v1 in the arm blocks is the blocker.

Hmm, what if the const 0x9000 is NOT in v1 but the *slt result* is? Look at the target: `li v1,0x9000; slt v1,v1,v0` — both in v1. The slt is `(set (reg r79) (lt (reg r78) (reg r77)))` where r78=const, r77=call result, and the result r79 goes to v1 (the dump showed r78 in 3, r79 in 3).

So in the arm block, v1 is used by the const and the slt result. Both local.

For q to get v1 globally, the arm blocks must not use v1 for locals.

Since the target requires the const/slt in v1 in the arm blocks... the ONLY way is that q is a hard reg (the pin) — OR the q pseudo is not global.

Hmm hm. So: can q be a LOCAL pseudo? q must be defined in exactly one block. The target has 2 loads (one per arm). Both are "q = arg->unk64". If both loads wrote to the same pseudo, it's global.

UNLESS: the second load is not a "definition" of the pseudo but a *reload* of a pseudo that was already... hmm, in GCC, a pseudo with 2 defs in different blocks is global.

Hmm, what if the two loads are the SAME insn in a merged block? I.e., the arms are merged into one block? The arms differ (val 3 vs 4) but the q load is common. If the source were:

```
case 2: if (...) return 0; val = 3; break;
case 1: if (...) return 0; val = 4; break;
q = arg->unk64;   // AFTER the switch, one load
```
then only 1 load → 38 instructions vs 39 → score ≠ 0. Hmm! But wait: what if gcc duplicates the load into both arms (tail duplication / crossjumping)? GCC 2.7's crossjumping can duplicate? No, crossjumping merges, doesn't duplicate. But there IS "tail duplication" in later GCC (not 2.7).

Hmm, but what if the source has the load after the switch and gcc's *jump* pass (crossjump) duplicates... no.

OK, so a single load can't become 2 loads.

Alternatively: keep 2 loads but make them write to a LOCAL pseudo in each arm and have the join use a *global* copy... the global copy is the problem.

Hmm, wait. What if the join's store uses a pointer that is a *global* pseudo, and each arm copies its local into it? Then the global is the same problem (it's live across blocks and in the arm blocks).

Hmm, but here's the thing: the conflict for the global is with the LOCAL const in the arm blocks. The global pointer would be live in the arm blocks too (it's assigned there) → conflict.

OK. So it seems item 1 is a genuine wall with a clear mechanism:
- The target's q in $3 requires either a hard-reg pin or a local pseudo in the arm block.
- q must be global (2 definitions in 2 blocks; the join use).
- A global pseudo cannot take $3 in the arm blocks because the block-local 0x9000/slt pseudos hold $3 there (block-granular conflict), and the target requires exactly that local $3 usage.

Hmm, but wait. Let me double check the "block-granular" claim by an experiment: if I make the arm's local const NOT use v1 (e.g., by adding pressure so local_alloc picks another reg for it), does the global q then take v1? If yes, the mechanism is confirmed. But then the target's const wouldn't be in v1 → score > 0 anyway. Still, it confirms the mechanism, which is good evidence for the wall.

But hmm, what if there's a variant where BOTH work? Let's think: local_alloc assigns the const to v1 because v1 is the first free reg in the arm block. If the arm block had MORE local pressure such that the const goes elsewhere... we need it in v1.

Alternatively, what if the q's reload copy (which creates the a0 preference) went to a *different* reg, so that the preference doesn't force a0, and the global alloc's reg choice (v0? v1?) ... v0 is taken by the val pseudo? Let's see the order: r73 (q) first, then r74 (ptr), r76 (val), r83, r72.

If q had no preference, would it get v0 (the first in the class order)? v0 is used by the local const? no. Hmm, in the arm block, v0 holds the call result (local) → blocked. v1 holds the const (local) → blocked. So q would get a1? or a0? Hmm, the class order for MIPS GR_REGS: $2,$3,$4,$5,... (v0,v1,a0,a1,...) with $16-$23 (s0-s7) last? Then a0 ($4) is the first free → a0 again. So even without the preference, q → a0.

So the preference isn't even the deciding factor.

Therefore: to get q into $3, $3 must be free in the arm blocks (i.e., the const/slt not in v1) — contradicting the target. HARD WALL.

Unless... the q pseudo could be allocated $3 and the const/slt could be allocated $3 as well if the const/slt were NOT local but global — and then global_alloc would need to give both $3 — impossible (they conflict: const is live while q is live? the const dies before q's def, but the conflict sets are block-granular → they'd conflict).

Hmm, unless the const/slt pseudos are in a *different block* than q! What if the comparison `func_8012BD14(ptr) > 0x9000` were done in a block BEFORE the q load... it already is: in the arm, the order is call, const, slt, branch, then the q load. But they're in the SAME block (no branch between them, except the conditional branch to the default case).

Hmm! The branch `bnez v1,4030` splits the block! In GCC, a conditional branch ends the block. So the arm block is: call, const, slt, bnez → and the q load is in the FOLLOWING block (the "then" continuation). Let me check the block structure in the .rtl:

- code_label 40 (block 40): insn 43 (q load r73), insn 46 (const 3 → r76), jump to 98.
- The comparison block: insn 22-37 (call, const, slt, branch) — this is the block before 40 (block 18/19).

So the q load is in block 40 (after the branch), and the const/slt are in the block before (block 19/40?). So the const/slt and the q load are in DIFFERENT blocks!

Then why is v1 blocked for the global q? Because the global q is live in blocks 40, 71, 98 — hmm, and the const is in blocks 19 and 50 (the pre-branch blocks). Those are different blocks!

Hmm! So the block-granular conflict shouldn't block v1 for q... unless the liveness of the global q includes the earlier blocks (it's live *into* block 40 from the branch? no, q is defined in block 40).

Hmm, but the *conflict* computation for a global pseudo vs a hard reg: the hard reg v1 is used by locals in blocks 19 and 50. The global q is live in blocks 40, 71, 98. If the sets are disjoint → no conflict → v1 should be available!

But empirically q got a0, and v1 was taken by r83 (the switch value pseudo) — a GLOBAL allocated to v1! Order: 73 74 76 83 72 → r83 is processed AFTER r73, so it couldn't have blocked r73.

Hmm, so what blocked v1 for r73? Let's check: maybe nothing blocked it, and the preference "4" (a0) decided it! GCC's global_alloc honors the copy preference: if a pseudo has a preferred hard reg, it's allocated there if possible.

So the a0 preference (from the reload copy) IS the reason q got a0!

And in the target, q is hard $3 so no preference is involved.

So the lever: eliminate the reload copy into a0 (or make it into v1).

What creates that copy? The store's address computation. In the join block: `(set (mem/s:HI (plus:SI (reg/v:SI 73) 2)) (reg/v:HI 76))`. The reload pass must compute the address. For MIPS, `sh` can take a base+offset, so the reload would insert a copy of the pseudo into a hard reg (a0) to serve as the base.

Which hard reg does reload pick? reload.c's `choose_as_reload_operand` / the "reload_inp" allocation: for an address reload, reload allocates a "scratch" register. MIPS's reload regs... The copy is `(set (reg:SI 4 a0) (reg/v:SI 73))`? Let me verify by dumping the .reload pass? gcc 2.7 has -dr (reload) dump? The cc1_dumps_tu.sh uses -dr which is... hmm, "-dr" is the RTL dump (the .i.rtl). The reload dump might be -dq? Let me check gcc 2.7's dump flags: -dA, -dB, -dC, -dD (flow), -dE, -df (combine), -dg (global), -dh, -di (expand), -dj (jump), -dl (loop), -dm (sched), -dn, -do (cse2?), -dp, -dq (reload!), -dr (RTL), -ds (flow2), -dt, -du, -dv, -dA...

Yes! -dq is the reload dump. Let me produce it separately with a manual cc1 invocation (cc1_dumps_tu.sh has a fixed flag list; I can run cc1 myself with -dq).

Then I can see the reload decisions for the q address.

If the reload picks a0 for the address base, maybe I can influence it: the reload pass allocates reload regs preferring certain ones. If a0 were busy at that point, it'd pick another (v1?). In the join block, a0 is dead (the call arg was earlier). Hmm.

Hmm, but the *target* has the base in v1 — because q is hard $3 there, so the address is (plus (reg 3) 2) → no reload needed → the base is $3.

So for the lever-free version, the base reg for the store is chosen by reload: it copies the pseudo into some hard reg. If that hard reg were v1, then the preference would be "73 prefers 3" → global_alloc gives q → v1 (if v1 is not blocked). And then the local const/slt in the arm blocks are in v1 — different blocks → no conflict → OK!! And the final asm would be `sh v0,2(v1)` — matching the target!

So the lever: make the reload pick v1 for the address copy instead of a0.

How? The reload pass picks the reload register from the "reload regs" list, considering which are free. MIPS's reload reg preference: in reload.c, `reload_inp` uses `regclass` and picks a reg via `choose_as_reload_operand` → the reg is picked by "reg_alloc_order"-ish preference per class, and it prefers a reg that's not used elsewhere.

Hmm, both a0 and v1 are free in the join block. Why a0? The preference order for GR_REGS in MIPS reload: reload.c's `reload_class`... In reload.c, the function `choose_as_reload_operand` picks a reg using `reg_alloc_order`-like preference: for a class, it iterates over the class's regs in a preferred order. MIPS's REG_ALLOC_ORDER (in mips.h) is:

```
#define REG_ALLOC_ORDER \
  { 0, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 6, 7 }
```
Hmm, I'm not sure. But if the order is a0 ($4) before v1 ($3), then a0 wins.

How to change which reg reload picks? Make a0 unavailable at that point! E.g., if a0 were live across the join block... In the target, a0 is not live in the join.

Hmm, alternatively, make the address computation need a *different* kind of reload. E.g., if the store address were `(plus (reg q) (const 2))` — that's what it is. If instead the store were `((Unkstruct *)q)->unk2 = val` where unk2 is at offset 2 → same.

What if the store is at offset 0? Then the address is just the pseudo → still a reload copy.

Hmm, what if there are TWO stores (offsets 2 and 0x34)? Both need the base → reload would compute the base once (CSE in reload) into one reg.

The reload copy into a0: which pseudo? The reload dumps will tell. Let me generate a -dq dump and look.

Actually, maybe there's a smarter C-level trick: make the *pointer* a value that's already in a hard reg... no.

Alternatively: make the store address NOT need a reload by using a *pointer-typed* variable: if q is declared as `Unkstruct_801815AC_3 *q;` then the store is `(set (mem/s:HI (plus:SI (reg q) 2)) ...)`. Same.

Hmm, what if the offset were 0 for one of them? unk2 is at 2, unk34 at 0x34.

Alternatively, use a `u16 *` pointer: `u16 *qp = (u16 *)q; qp[1] = val; qp[0x1A] = 0;` → the address is (plus (reg qp) 2) and (plus (reg qp) 0x34). Same structure.

OK so the reload copy into a0 is the crux. Let me confirm with the -dq dump, then think about how to shift the reload's choice to v1.

Actually — wait. Alternative approach: what if the *preference* is not what decides? Let me test directly: make the q pointer a *hard-reg-preferred*... no.

Let me try a different, very promising idea: since the reload copy is `(set (reg:SI 4 a0) (reg/v:SI 73))`, the preference "73 prefers 4" arises. If the *same* pseudo is also copied into another hard reg... hmm.

Actually, here's a cleaner idea: what if the join's store used a pseudo that is a COPY of q, where the copy is made in the arm? E.g.:

```
case 2: q = load; qp = q; val = 3; break;
```
Then qp is global, and the reload copy would be for qp. Same structure.

OK let me get the reload dump. Let me run cc1 manually with -dq on the candidate TU (tu_c1.c) to see the reload decisions.

The cc1_dumps_tu.sh script does cpp then cc1. Let me do it manually in my shard dir, with only -dq (plus -dr maybe) to keep the output small.

Command:
mipsel-linux-gnu-cpp -lang-c -Iinclude -I<dir of tu_c1.c> -Isrc/shared -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -Dpsx -D_PSYQ -D_MIPSEL -D_LANGUAGE_C -Isrc '-DINCLUDE_ASM(a,b)=' tu_c1.c > tu.i
then cc1 -quiet -O2 ... -dq tu.i -o tu.s

Let me write a script for this in my bin dir.
