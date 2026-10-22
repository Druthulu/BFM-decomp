---
ts: 2026-10-22T09:18:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_iqbbixkikhr3uSQNLaul
---
Good — I get a clear diff view. `addu v0,v0,a1` vs `addu v0,a1,v0`.

The claim in notes: gcc-2.7.2's combine canonicalises the commutative add to index-first. Hmm, but wait — maybe it's not canonicalisation but rather the order in which operands are set: the "plus" tree. In gcc-2.7.2 RTL, `plus` is commutative and combine/combine_regs swaps to a canonical form? Actually in gcc 2.7, `plus` with both operands REG is commutative; `combine` has code: "Check if commutative, and if so, put the operands in a canonical order" — canonical order is by register number? v0 < a1? No: a1 = $5, v0 = $2. Canonical order by regno would put $2 (v0) first. The target has a1 first ($5). Hmm.

Wait but the notes say the target is `addu v0,a1,v0` (pointer+index) and ours is `addu v0,v0,a1`. So target has pointer (a1) first. That contradicts "canonical by regno". So maybe the mechanism is different: the ordering comes from how the address expression is built: `(plus (reg a1) (mul ...))`? Actually the multiply `sll v0,v0,0x3` produces index in v0; then addu v0,a1,v0 → (plus a1 v0).

In gcc 2.7 combine, there's a rule: for commutative ops with two register operands, it checks `COMMUTATIVE_P` and may swap to make the "hard reg" operand first? Actually there is code in combine.c:

```
      /* Now try to reorder the operands to make the second operand a
	 constant...  */
```
and in `convert_to_scc`? Hmm.

Actually in gcc 2.7.2 combine.c there is:
```
	  /* If we are adding a constant to a register, ... */
```
and also for commutative:
```
	  if (COMMUTATIVE_P (code) && GET_MODE_CLASS (GET_MODE (x)) == MODE_INT)
	    {
	      /* Try to put the constant in the second operand... */
```
Also, `canon_reg`/`reg_equiv`?

Hmm. Alternatively the ordering might come from the *address* being computed via `(plus (mem) ...)` and then the load/store.

Wait actually, the difference here: the target instruction is at index 85/86, in a context where a1 holds &D_80195AF6 (materialized at insns 69-70 into $a1) and re-materialized into $at (71-73) for the newval load. Ours: a1 holds the pointer, v0 the index.

Since the notes say 11 tries all gave 1, maybe the mechanism is truly combine's commutativity canonicalization. But hmm — actually wait. In gcc 2.7.2 combine.c there's this code in the "plus" handling:

```
	    case PLUS:
	      ...
	      /* If we have a plus of two registers, and one is a constant... */
```

And also there's `swap_commutative_operands`? Let me think about which is the true reason: In gcc, `combine` handles commutative ops by trying both orders? There's code:

```
      /* If we can, we can try to swap the operands of a commutative
	 operation, and see if the result is better.  */
```
Hmm, I recall gcc 2.7 combine.c has in `simplify`:
```
	  else if (COMMUTATIVE_P (code))
	    {
	      rtx temp = x;
	      x = y; y = temp; ...
	    }
```
Actually in `simplify_rtx` / `simplify_binary`, for commutative operations, if the first operand is "expensive" and second is cheap, they swap.

Hmm, there's a known gcc behavior: in `simplify_rtx`, for commutative ops:
```
	  /* If we have a commutative operation, try swapping the operands. */
```
In gcc-2.7.2 `simplify_rtx` for commutative:
```
	      else if (COMMUTATIVE_P (code)
		       && ... )
```

Rather than theorize, I could test experimentally. The lever-free body: can I get the target order by making the pointer an operand in a way that combine doesn't swap? The notes tried 11 spellings.

Alternative idea: maybe the difference isn't about plus but about the *whole* expression tree: the target computes `addu v0,a1,v0` where a1 = pointer and v0 = index. In our body, we compute the address `(u8*)p + off + 4` for the load `D_801270C8 = *(s16 *)((u8 *)p + off + 4);`. Wait, target at 84: `sll v0,v0,0x3`, 85: `addu v0,a1,v0` → that's the address p+off. Then load at +4.

Hmm, so the address sum is (plus p (mul idx 8)). Our version: (plus (mul idx 8) p)? i.e. index first. gcc's combine canonicalizes commutative adds by putting... In gcc-2.7.2, `combine` has this in `simplify_rtx`? There is definitely code in combine.c:

```
	  /* If we have a commutative operation with one operand being
	     a constant and the other a register, put the constant second. */
```

For two registers there's the "swap" in `simplify_rtx`? Hmm, there's `known_eq`?

Actually! I recall: gcc 2.7 combine.c has this specific code for PLUS/MINUS/AND/OR/XOR commutative:

```
	      /* Now, if this is a commutative operation with one operand
		 being a register and the other being a constant, ... */
```

and separately, in `combine` there's the notion of `reg_equiv`.

OK let me try a different empirical route: what does the *target* code look like in the original decomp? We don't have target source (it's a ROM binary). But we have the asm dumps! tools/cc1_dumps_tu.sh + alloc_table.py can dump the RTL. The notes say "R3.40-013 helpers".

An alternative trick: use a C expression that produces a non-commutative-looking but equivalent add, e.g. `(u8*)p + off` where off is `int` — pointer arithmetic gives (plus p off) — pointer first! But off = unk100 * 8 is a multiple of 8 so it's still a valid pointer arithmetic. But then the offset +4 part: `*(s16*)((u8*)p + off + 4)`.

Hmm, in our body, `off = unk100 * 8` then `(u8*)p + off + 4`. That should be (plus (plus p off) 4) → pointer first. But we got index first?! Because gcc turned the multiply into sll and then... the plus chain (plus (plus p off) 4) where off=(mul unk100 8): combine rewrites (plus p (mul x 8)) into (plus (sll x 3) p)? That's the reassociation: combine turns (plus p (mult x 8)) into (plus (mult x 8) p) — I think there's a rule in combine.c:

```
	    /* Handle multiplication by 2^n in sum: (plus (mult x 2^n) p) */
```
Hmm, and there's `combine` code that converts `plus` of a `mult` by power of 2 into a shift: in gcc 2.7 combine.c:

```
	  /* If we have a plus of a multiply by a power of 2, ... */
```
Actually the specific known optimization: `x*8 + p` → `sll x,3; addu p, x`. gcc 2.7's combine does that: it converts MULT by power of 2 into shift and re-associates.

Anyway — the notes already tried the index inlined etc.

New idea: make the multiply NOT a power of 2 in the tree: e.g. compute `off = unk100 * 8` as `(unk100 << 3)` — tried (v5). Or use `unk100 * 4 * 2`? Or use a non-shifted multiply: `off = unk100 * 8` — the combine converts mult-by-8 to sll and reorders.

The target has `sll v0,v0,0x3` then `addu v0,a1,v0`. So the target also has the shift. So both have the shift. The difference is only the add operand order.

In gcc 2.7.2 combine.c there IS this code (I recall reading it):

```
	    case PLUS:
	      ...
	      /* If we are adding two values and one is a constant, ... */
```
and there's the function `combine_insns` with:
```
	  /* If we can, put the operand that is a register in the first
	     position and the constant in the second. */
```

Hmm.

Another thought: maybe the ordering is determined by `reg_equiv`/`copy` and not by canonicalization: the target's a1 (pointer) is a *pseudo* (like the hard-reg pin on a1?) Actually the notes say the target materializes &D_80195AF6 into $a1 at insns 69-70, re-materializes into $at for the load. That means the pointer value is in a pseudo that got allocated $a1, and the *index* is in a pseudo that got $v0. Then the add `(plus a1 v0)`...

In gcc, the RTL for `p + off` where p is a pointer pseudo (reg) and off is `unk100*8`: combine transforms into shift+plus. The canonicalization in combine.c for commutative operations with two register operands is in `simplify_rtx`? Let me actually check the source! The gcc 2.7.2 source might be available in the repo (the toolchain). Let me look for it: maybe under tools/ or a gcc source dir. That could tell me exactly the rule, e.g. in combine.c:

Actually, I recall in gcc-2.7.2 combine.c:

```
/* Return 1 if we have a PLUS of two registers and can simplify ... */
```
and importantly:

```
	      /* If this is a commutative operation, and we have one operand
		 that is a constant and one that is not, move the constant
		 to the second operand. */
```

There's also this in combine.c (gcc 2.7):
```
  /* This case is needed to avoid a bug in ... */
```

I think the actual relevant code is in `simplify_rtx` in simplify.c:
```
	    case PLUS:
	      ...
```
no.

Alternatively, the swap could come from **cse**! cse.c has `make_regs_eqv` and also in cse there's code that swaps commutative operands? Hmm.

Better: the tooling. There are cc1 dumps: tools/cc1_dumps_tu.sh dumps the RTL passes. Then I can look at the actual RTL tree for our candidate and compare with the target's RTL (the target is known via the "other" asm). The dump shows the tree forms; if in the dump the tree is `(plus (reg ...) (reg ...))` vs `(plus (reg a1) (reg v0))`, I can see which pass swaps.

But wait — for the target, do we have RTL dumps? The target asm comes from the original binary (byte-identical asm in build/?). The `delever_search --try` compares my compiled asm with the target asm from build/ (the "other" asm presumably from the ground-truth asm file). We don't have the target's RTL. But the asm tells us the operand order.

Given the notes claim 11 tries all fail, and this is one of the "wall" items, but I have budget to try new moves. Let me think about what determines the order.

In gcc 2.7.2 combine.c, there is this function `simplify_rtx`? Let me check if gcc source is available in the repo. Let me search for "combine.c" in the project.

Actually the toolchain is presumably a prebuilt gcc 2.7.2 (mips). The source may not be in the repo. But maybe under /home/musashi/bfm-decomp/tools or a gcc-src dir. Let me check quickly (allowed within project).

Let me plan: for each item, I need 30+ tries and 20+ min. That's a lot of turns of work but scoring is fast (1s). The real challenge is generating meaningfully different candidates. I can write a generator script that produces many candidate variants programmatically (e.g. permuting spellings) and score them in a batch, then read the best.

Key insight: since scoring is cheap (1s), I can do a broad search. Let me build a small Python "mutator" harness that takes the base lever-free body and applies a list of textual/semantic transformations, scoring each. But the brief says "real C moves only" — the moves must be legitimate C-level rewrites (temps, decl order/scope, widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse). Programmatic generation of these variants is fine.

Also note: `--budget` limits compiles per body; the --try path just compiles once per candidate presumably.

Also there might be a --try with multiple files? sc.sh loops over files. I'll write my own batch runner script that scores a list of candidate files and prints compact results, running maybe 10-20 candidates per call.

Let's check how long a batch of 20 takes: 20s. Fine. But each Bash call has a 285s cap. So batches of ~50 (50s) are fine.

First, let me look at the remaining items' defs and the current residual diffs so I understand each.

Item order: let me pick the most promising first. Item 80184828 (best 1) — a single instruction. Item 8018483C (best 5). Item 8017D81C (best 20). Item 8017DA30 (best 4). Item 8018389C (best 14).

Let me now look at each residual diff in detail. For 80184828, the diff shows one instruction.

Let me check the gcc source availability and the dump tools, since understanding the pass that swaps the operands could crack it.

Actually, wait. Let me reconsider: `addu v0,v0,a1` vs `addu v0,a1,v0`. In gcc 2.7.2 combine.c, there IS a known behavior: **combine's commutative operand swap to put the operand with the lower "hard reg number" second?** Hmm no.

Hold on, actually maybe it's the opposite of canonicalization: maybe in our build the pointer ends up in $a1 and the index in $v0, and the *target* has the pointer in $a1 too. Both have same regs, just operand order swapped. gcc 2.7.2 combine.c contains this code (I'm fairly confident now):

```
      /* Now, if the operation is commutative, and the operands are
	 not the same, we can swap them to see if that gives a better
	 result.  */
```
Hmm.

Actually here's a concrete memory of gcc 2.7.2 combine.c, function `simplify_rtx`... no. It's in `combine_insns`:

```
	      /* If we have a commutative operation and one operand is
		 a register and the other is a constant, canonicalize. */
```

OK. Empirical approach: use cc1 dumps on our candidate to see the RTL tree and which pass changes the order. tools/cc1_dumps_tu.sh exists. Let me read its usage and alloc_table.py.

Given the budget (30 min/item, 5 items), and the fact that all 5 items were previously walled, maybe some are crackable with fresh insight. The notes for 8018389C (best 14) mention the residual is "identical to func_801832A8" and involves the magic 0x66666667 sunk next to its mult instead of at the tail top. That's a division: `vol = (0xA0 - ax) * 0x7F; vol /= 0xA0;` — the compound division. Score 14 with exact count.

Let me start with the "closest" item: 80184828 (1 ins off). Understanding the pass would be valuable. Let me check dump tooling.

Let me read tools/cc1_dumps_tu.sh and alloc_table.py quickly.
