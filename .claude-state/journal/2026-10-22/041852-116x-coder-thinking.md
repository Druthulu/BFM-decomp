---
ts: 2026-10-22T10:18:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8r0bAflHqgXoFhgUXG4O
---
Now I can see the target's tail clearly:

```
10: lui   a0,0x6666
11: ori   a0,a0,0x6667        ; the magic 0x66666667 in a0
12: li    v0,160
13: subu  v0,v0,a1            ; v0 = 160 - ax
14: sll   v1,v0,0x7           ; v1 = v0*128
15: subu  v1,v1,v0            ; v1 = v0*127
16: mult  v1,a0               ; v1 = (160-ax)*127 * magic
17: mfhi  t1
18: addiu v0,a2,160           ; v0 = x + 160
19: nop
20: mult  v0,a0               ; (x+160) * magic
21: sra   v1,v1,0x1f
22: sra   a0,t1,0x6           ; the high part >> 6  → the /160 division
23: subu  a1,a0,v1
24: sra   v0,v0,0x1f
25: mfhi  a2
26: sra   v1,a2,0x3           ; the /20 division
27: subu  a2,v1,v0
```
So the magic 0x66666667 is used for BOTH divisions! For the /160 division: mult then mfhi then sra 6 — hmm: (v1 * 0x66666667) >> 32 >> 6 = v1 * 0x66666667 / 2^38 ≈ v1/160 ✓ (since 0x66666667 * 160 ≈ 2^38 ✓ as I computed). So gcc uses the SAME magic for /160 and /20?! That means gcc computed the magic for ONE division and reused it — because both divisors share... hmm, 160 = 8*20. Interesting: gcc's magic for /160: M = ceil(2^38/160) = 274877907 — but the target uses 1717986919 with a shift of 6 = 2^38. So gcc used the /20 magic (0x66666667, shift 3) for /160 as well?? With a shift of 6: 1717986919/2^38... hmm: the quotient = (v1 * 1717986919) >> 38 = v1 * 1717986919 / 274877906944 ≈ v1/160.0000...? 1717986919/274877906944 = 1/160.0000003 — close enough ✓ (gcc's magic algorithm allows a "round down" magic when the error is acceptable? For d=160, gcc's algorithm might find M = 0x66666667 with a shift of 6 as the "add" variant or as a valid magic).

Hmm, in any case: the target materializes the magic ONCE (at the top, in a0) and uses it for both divisions. gcc's CSE then shares it.

In ours, the magic is materialized at the first mult (in v0) and the second division's magic (0x33333334?) hmm — no, ours must also share... hmm, ours: "lui v0,0x6666; ori v0,v0,0x6667; mult a1,v0" then "mult v1,v0" (the same v0!) — so ours also shares one magic, but materialized LATE (right before the first mult) and in v0.

So the only difference is the materialization's POSITION (top of the tail vs just before the first mult) and the register (a0 vs v0).

Interesting! So the target materializes the magic at the top of the tail block. Why? Because in the target's original source, the magic's pseudo was created at the top of the tail — e.g. because the division was expressed such that the magic was computed early.

Hmm! What creates the magic early? In gcc 2.7, the division by a constant is expanded by the FRONT END (c-type.c) into a multiply-by-magic sequence when the divisor is a constant: the front end generates the magic as a *tree constant* → expand materializes it where it's used.

Hmm, but the target has it at the top of the tail block (before the "li v0,160" and the subu). That's odd — the constant is materialized before its use by several instructions. That suggests the constant was created in the front end as a separate tree (a temp) at the start of the expression evaluation... Hmm, but gcc's front end expands `a / 20` into a sequence where the magic is a constant used by the MULT — the materialization would be adjacent to the mult.

Unless the magic is used by TWO mults (the /160 and the /20 divisions) — and gcc CSE'd them, keeping the FIRST materialization. Hmm, in ours the first mult is the /160 one (at 126) and the magic is materialized right before it.

Hmm, so why is the target's materialization at the very top (before "li v0,160")?

Ah, maybe because in the target, the two divisions were CSE'd such that the magic's single materialization was hoisted to the top of the block by sched1 (the "birth boost" for a constant used twice?).

Hmm, in ours the magic is used twice too (both mults) but materialized late.

Hmm, the difference might be that in ours the FIRST mult is the /160 division and in the target also... yes both.

Hmm, so what differs? The position of the materialization relative to "li v0,160" and "subu v0,v0,a1".

In the target: [lui a0][ori a0][li v0,160][subu v0,v0,a1][sll v1,v0,7][subu v1,v1,v0][mult v1,a0]...
In ours: [li v0,160][subu a1,v1,v0][lui v0,0x6666][ori v0,v0,0x6667][mult a1,v0]...

Hmm, ours has the magic right before the mult (adjacent) — the scheduler kept them together. The target has it at the top.

The scheduler (sched1/sched2) may hoist a constant materialization if it's beneficial (fewer live regs). Since the magic is used twice, hoisting it to the top is fine.

Hmm, so this is a scheduling decision. What could make gcc hoist it? If the magic were materialized at the top of the block (in the RTL order), the scheduler would keep it there.

The RTL order: the magic's set insn position. In the RTL, the division expansion (from the front end) puts the magic's set right before the mult — unless the magic is a shared temp.

Hmm! What if in the target's source, the division was written such that the magic was a *variable* used twice? E.g.:

```c
vol = (0xA0 - ax) * 0x7F / 0xA0;
x = (x + 0xA0) / 0x14;
```
gcc's front end expands each division separately, but CSE merges the two identical magic constants into one set — placed at the first use.

Hmm.

Alternatively, maybe in the target the two divisions were BOTH by the same divisor in the source?! E.g. `x = (x + 0xA0) / 0x14;` — hmm.

Hmm, what if the source had the x-division FIRST and the vol division SECOND? Then the magic (for /20 = 0x14) would be materialized at the x-division... but the target's first mult is for the vol computation (v1 = (160-ax)*127) — hmm, wait: which division does the FIRST mult belong to? "mult v1,a0" where v1 = (160-ax)*127 — that's the vol numerator. So the vol division comes first in the target's asm ✓ (as in our source).

But the magic is materialized BEFORE "li v0,160". Hmm, so it's hoisted above the whole vol computation.

Hmm, what if the magic's pseudo was created in the front end as part of the *first* division's expansion and the expansion order put the magic's set first? For the /160 division, gcc's front end (c-type.c) expands `a / 160` into:
```
t1 = a * 0x66666667   (the magic)
...
```
Hmm, and the magic's set would be adjacent to the mult.

Hmm, BUT: gcc's front end for a division by a constant may emit the magic as a separate statement BEFORE the whole sequence, e.g.:
```
tmp1 = 0x66666667;   /* the magic, as a separate expression */
tmp2 = a * tmp1;
...
```
Hmm! In gcc 2.7's c-type.c, the expansion of division by a constant is:

```c
	    case TRUNC_DIV_EXPR:
	      ...
	      /* We put the magic number in a separate variable to avoid
		 recomputing it... */
```
Hmm! Actually, I recall gcc's expand_divmod uses `expand_mult` and the magic is a constant.

Honestly, in the front end (c-type.c, gcc 2.7), the division by a constant is expanded like:

```c
	  case TRUNC_DIV_EXPR:
	    if (power_of_2_operand_p (operand)) {...}
	    else {
	      /* Divide by a constant: use a magic number */
	      ...
	      /* Note that the front end will create a temp for the magic */
	    }
```
Hmm, and gcc's c-type.c for TRUNC_DIV_EXPR with a constant divisor does:

```c
	      /* We handle the division by a constant by multiplying by
		 the magic number.  The magic number is put in a temp
		 (so that it is not recomputed).  */
```
Hmm, I think gcc's front end creates the magic as a *constant* directly in the MULT expression, and expand materializes it at the mult.

BUT: there's the "one expansion per division" detail: gcc's front end for a division by a constant creates the sequence in c-type.c `expand_expr` case TRUNC_DIV_EXPR:

```c
	    case TRUNC_DIV_EXPR:
	      if (TREE_CODE (operands[1]) == INTEGER_CST) {
		  /* constant division */
		  ...
		  /* Multiply by the magic number */
		  ...
	      }
```

And importantly, gcc 2.7's front end puts the magic number into a separate temporary via `save_expr`/`build1` — creating a statement `magic_tmp = 0x66666667;` BEFORE the rest of the sequence! That would explain the target's early materialization ✓✓.

And in OUR compile, the magic was materialized late — because... hmm, if the front end always creates the temp first, ours would also be early. Unless the difference is WHICH division: ours might have the magic temp created for the /20 division (which comes second in the source?) hmm.

Hmm! Wait: in ours, is the magic 0x66666667 for the /160 or the /20 division? Ours: "lui v0,0x6666; ori v0,v0,0x6667; mult a1,v0" where a1 = (160-ax)*127 → the magic for /160 = 0x66666667?! Hmm, and then "mult v1,v0" (the second mult, for x+160) uses the same v0 → so ours ALSO uses 0x66666667 for both ✓ (same as the target).

Hmm OK. So both use the same magic; the difference is only the placement.

So: in ours the magic's set is adjacent to the first mult; in the target it's at the top of the tail.

If the front end created a separate temp for the magic, the placement would be early in both. So maybe in the target the magic's temp was created by the SECOND division's expansion (the /20 one) and the two multiplies were CSE'd to use it...

Hmm, hmm. Alternatively, in the target the source's division ORDER might be different: if the x-division (the /20 one) came FIRST in the source, its magic temp would be created first (at the top of the tail) ✓, and then the vol division's magic would CSE to the same value ✓. But then the first mult in the asm would be the x-division's... hmm, unless the scheduler reordered them.

Our z05_swap_div (x's division first) gave 31 (worse) — hmm.

Let me look at z12_x_first_split (23) and z05 (31). Hmm.

OK, at this point, let me consider the launder's role: `__asm__("" : "=r"(vol) : "0"(vol));` — this forces vol (the division result) into a register and re-ties it. In the target, the division result is in a1 (the "subu a1,a0,v1" → the result in a1) — and the call's second arg is `ori a1,a1,0x3000` ✓ (a1 = vol | 0x3000). So vol ends up in a1 ✓.

In ours, the division result is in a1 too? The diff showed ours: "sra v0,a1,0x1f; subu a1,a0,v0" → the result in a1 ✓.

Hmm, so the v0/v1 differences are in the intermediate computation.

The real difference: the magic's materialization position and the register (a0 vs v0).

Hmm, since the magic is used twice, and in the target it's in a0 (a long-lived-ish reg), the allocation differs.

Idea: what if the magic's temp were created EARLIER in the source — e.g. by writing the division with an explicit magic? That's not "real C" (it would be hand-asm-ish). Hmm, but writing `vol = (0xA0 - ax) * 0x7F * 0x66666667 >> 38`? That's not the same semantics (no sign correction) and is definitely hand-optimized (not a "real C move").

Hmm.

OK, let me take stock. Time: ~3h20m spent. I still have item 8017D81C (best 20) to do, plus writing up everything (results.tsv, notes.md, moves.md, the log file).

Realistically, I should:
1. Spend ~20 more minutes on 8018389C (a couple more batches) → WALL with best 14.
2. Spend ~25 minutes on 8017D81C (2-3 batches) → WALL with best ~19-20.
3. Write the results, notes, moves.md lines, and the log.

Let me do a couple more batches for 8018389C focusing on the magic's placement:
- Make the vol division use a *variable* divisor? no.
- Hoist the division: `vol = ...;` hmm.
- What if the two divisions are written so that the SECOND one's magic is created first: e.g. compute the x-division's numerator first?
- What if the vol computation is moved into a separate statement earlier (e.g. before the `if (x < 0)`)?

Let me also try: what if the vol division is by a *variable* holding 0xA0? Then gcc emits a real division ✗.

Let me try:
w1: `vol = (0xA0 - ax) * 0x7F; vol = vol / 0xA0;` with the x-division written as two statements (x = x + 0xA0; x = x / 0x14;)
w2: the vol division first, then x, with the x division split.
w3: move the whole vol block before the `if (x < 0)` (i.e. compute vol before ax is finalized)? changes semantics.
w4: `ax` as a variable used twice?
w5: the magic hoisted by writing `x = x + 0xA0;` earlier (before the vol computation) → the x-division's magic would be created earlier.

w5 is interesting: if the x-division's *numerator* is computed earlier, gcc might create the magic earlier. But the magic comes from the division expansion, not the numerator.

Hmm, w6: write the x-division FIRST in the source but keep the vol computation's result used later:
```c
x = x + 0xA0;
x = x / 0x14;
vol = (0xA0 - ax) * 0x7F;
vol /= 0xA0;
```
= z12 (23).

Hmm.

Let me try instead: make the vol division's magic the one created FIRST by writing the vol division as a compound expression and the x-division as two statements. Tested (z03 = 15, z07 error).

Let me fix the erroring variants (decl at block top) and try a few more.

Actually, let me think about what "the magic at the top of the tail" means in terms of the RTL: the magic's set insn is the FIRST insn of the tail block. In the front end, that happens if the magic's temp was created before the other statements of the block. The tail block starts after the call `func_8012BD3C(...)` (the big if). Inside the if body, the statements are: L.v[0..2] assignments, the pin, the call, RotTransPers, the if condition, then the ax/vol/x computations.

The target's tail block (insns 112-145 in the listing above, which is the block containing the vol/x computation) starts with:
```
addiu v0,v0,119
andi v0,v0,0xffff
sltiu v0,v0,239
beqz v0,...
sll v0,v1,0x10
sra a2,v0,0x10
bgez a2,78fc
move a1,a2
negu a1,a2
lui a0,0x6666
ori a0,a0,0x6667
li v0,160
...
```
So the magic (lui a0/ori a0) comes right after "negu a1,a2" (the ax = -x computation) and before "li v0,160".

So the magic is materialized after the ax computation and before the vol numerator. That's consistent with the front end creating the magic temp for the *vol division* (the first division in the source) — but positioned BEFORE the numerator's computation!? Hmm, that's odd: the magic temp would be created when the division expression is expanded, which happens after the numerator.

Hmm, unless the ORDER of the source statements is different: e.g. the vol division comes FIRST in the source (before the ax computation)? But the vol division needs ax.

Hmm! Unless the source had the vol division's magic created early because gcc's front end expands the whole `if` body statement by statement, and the magic temp for the FIRST division encountered...

Hmm, hold on: what if in the target's source, the x-division came FIRST? Then the magic temp (for /20) would be created at the x-division's expansion — but the x-division needs x (which is fine) — and then the vol division later would CSE to the same magic ✓. But then the x-division's expansion would come before the vol's, and the asm's first mult would be the x-division's ✗ (the target's first mult is the vol's).

Unless the scheduler reordered them. Hmm! The scheduler could reorder the two independent division sequences.

Hmm, so: if the source order were [x-division first, vol division second], then:
- The magic temp is created at the x-division → early ✓ (but the target's magic is after the ax computation — hmm, the x-division doesn't depend on ax, so it could be scheduled anywhere).

Hmm, the target's order: [negu a1,a2][lui a0][ori a0][li v0,160][subu][sll][subu][mult v1,a0]... so the magic is right before the vol numerator's computation ✓ — i.e. the magic was created between the ax computation and the vol numerator. That means the magic's temp was created by the vol division's expansion, but the numerator's computation was scheduled AFTER the magic.

Hmm! That's plausible: the front end creates the magic temp as a separate statement BEFORE the division's multiply, and the numerator computation is a separate statement that the scheduler placed after. Hmm, but the numerator `vol = (0xA0 - ax) * 0x7F` is a separate statement in the source (c1.c) — so the order would be [numerator stmt][magic temp][div stmt]. The scheduler could hoist the magic above the numerator ✓ (since the magic is independent).

So why doesn't our compile hoist it? Because in ours, the magic's set is adjacent to the mult (sched2 keeps it close). Hmm.

OK you know what? Let me try a variant where the source's division is written to encourage the magic to be a separate statement: e.g.

```c
vol = (0xA0 - ax) * 0x7F;
vol = vol / 0xA0;
```
(z02 = 14, same).

Hmm.

What if we use a *volatile*... no.

What about the launder's effect: the launder `__asm__("" : "=r"(vol) : "0"(vol));` right after the division — in the target, this asm forces vol into a register ($a1) and acts as a barrier that prevents the scheduler from moving things around ✓!! That's the lever's role: the asm (priority 1) anchors the instruction order.

So the magic's early placement is a consequence of the asm's presence (it blocks the scheduler from sinking the magic next to the mult).

Without the asm, gcc's sched2 sinks the magic next to its use ✓ (ours).

Could a lever-free construct have the same anchoring effect? A *function call* acts as a barrier for scheduling (instructions can't move across a call). Hmm! But adding a call changes the asm.

What about a *memory barrier*: a store to memory prevents the scheduler from moving the magic across it. Hmm, our source has stores (the L.v[] assignments) before.

Hmm, the magic is materialized after the ax computation and the scheduler sinks it to the mult. In the target, the asm after the division prevented... hmm, the asm is AFTER the division, so it can't prevent the magic from sinking to the mult (which is before the asm).

Hmm, unless the asm's presence changed the whole block's scheduling.

Honestly, let me try a few things empirically:
- Put the vol computation into a separate *block* (e.g. braces) — no effect.
- Try `vol` being used twice (e.g. `vol | flg` and `vol & 0xFFFF`)? In the source: `func_8002D4C8(0xA9B, ((vol | flg) | x) & 0xFFFF);` — vol is used once. What if vol were used twice (e.g. `(vol | flg) | (vol & 0) | x`)? That changes the semantics? `vol & 0` = 0 — so it's semantically identical but adds a use! Hmm, that's an identity-ish trick (a launder-ish "keepalive"). Hmm, the brief forbids "no new lever of any kind" — an extra use to force a register is a keepalive-ish lever. Not allowed.

OK. Let me accept the wall for 8018389C at 14 and move to 8017D81C, then write everything up. Actually, let me do one more batch of ~10 tries for 8018389C to reach ≥30 tries for the item:

Prior tries for this item: the previous agent's (unknown count, notes say "Best lever-free body ... score 14") + my 14 = the previous agent's tries + mine. The wall needs ≥30 scored tries ON THAT ITEM — presumably counting the item's total attempts (including the previous ones). The previous agent's notes don't give a count. I'll count my own tries (14 so far) and do more to reach 30+.

Let me do a batch of 16 more variantsfor 8018389C.
