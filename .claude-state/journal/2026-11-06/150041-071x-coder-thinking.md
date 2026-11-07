---
ts: 2026-11-06T22:00:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ltJcxTUGFb3Y1pMMeZRu
---
Same as w9 (57 ins) — the label didn't change anything; the then-arm copy is the extra.

So the structure needs the then arm to NOT have a copy.

Key insight: the target's copy executes unconditionally at the join. The only way to have an unconditional copy at the join that survives combine... 

Hmm, wait. Let me reconsider: what if the copy's DESTINATION is used later — we showed that blocks combine (w11 coalesced because iVar2 died). What if iVar2 does NOT die at the copy? In w11, iVar2 was dead after the copy (only used in r, which we switched to iv2c).

What if we keep `r = (uint)(iVar2 << 3) | c6b;` AND use iv2c somewhere later for free? 

Hmm, what if iv2c is used in the loop condition or the `cont` computation? `cont = (sx >> 0x10) < 7;` — no.

What if we use iv2c as the loop counter's... no.

OK, radical alternative: what if the *compare* uses iv2c and iv2c is ALSO the value stored... no.

Let me reconsider whether the target's move really must be a copy of iVar2. Look at the target insn 27: `move v1,a0` — v1 = a0. a0 = iVar2 (from 21/25). Yes.

Alright. Let me try ONE more idea: **make the compare's operand a HImode variable that is stored and the compare is done via a *signed* compare against the pinned int**, so reload needs... no.

Alternatively, maybe I can make combine fail by giving the compare a `REG_DEAD` note conflict... no.

Actually — here's a thought I haven't tried: **`use_crosses_set_p`**. can_combine_p checks `! all_adjacent && use_crosses_set_p(src, INSN_CUID(insn))`. all_adjacent requires next_active_insn(insn)==succ && next_active_insn(succ)==i3. If I insert a *real insn* between the copy and the compare that is NOT combinable... we need it to be free.

What if the li `one = 1` is replaced by something that is already needed? No.

Hmm, what if we put the copy AFTER `one = 1` (already is: copy at 40, one at 42, compare at 43). Order: copy, one, compare.

What if we could get order: one, copy, compare? Then i1=li, i2=copy, i3=compare. combine would merge the copy into the compare (i2 into i3), same.

What if: copy, X, one, compare where X is... no free insn.

OK, let me now think about whether the item can be a PARTIAL with the launder replaced by a *different* lever of the same kind? No — MATCH requires the kind gone.

Given the time, let me do a few more scored tries (to reach 30) and then record a WALL with evidence "combine-copy-merge". 

But wait — before that, let me reconsider one thing: the notes say "p1 = c1 + the launder restored (non-volatile): score 2, 56/56 ins; only `sw v0,-4(t0)` placement (mine 41, target 39) left -> the keepalive's position between the uVar1 store and the r store."

And q1 = p1 + do-while on the uVar1 store = 0.

So with the launder, everything matches. Without it: 55 ins, score 5.

Hmm, what if the launder's role can be played by the **existing pinned `one`**? For example, if `iv2c` were assigned from a variable pinned to $2... 

WAIT. What about making the copy's source a hard register! Look at can_combine_p:

```
	  && ((REGNO (dest) < FIRST_PSEUDO_REGISTER && ! HARD_REGNO_MODE_OK (...))
	      || (REGNO (src) < FIRST_PSEUDO_REGISTER
		  && (! HARD_REGNO_MODE_OK (REGNO (src), GET_MODE (src))
#ifdef SMALL_REGISTER_CLASSES
		      || ! REG_USERVAR_P (src)
#endif
```
If src is a hard register and NOT a user variable → return 0 (no combine). On MIPS, SMALL_REGISTER_CLASSES is defined. So a copy from a non-user-variable hard register can't be combined!

Is there a hard register holding iVar2 at that point? No. But what if the copy is from `one`? `one` is a user variable (register int one asm("$2")) → REG_USERVAR_P is true → combinable.

What if the source is a hard register that is NOT a user variable — e.g., a value produced by an insn that must be in a specific register (like a call result in $2, or a division result in LO/HI)? 

There's no such thing here.

Hmm, what about **$0 (zero)**: `iv2c = iVar2 + zr`? pin — forbidden.

OK, let me also consider: maybe the score-5 body could be turned into 0 by *changing something else* so that the missing move doesn't matter — e.g., if the compare used a register that happens to be v1 anyway. In mine, the compare uses a0 (iVar2's reg). What if we force iVar2 into v1 instead of a0? Then the compare would be `beq v1,v0` matching! And the later `sll v0,a0,0x3` uses iVar2 — which would then be v1, so it'd be `sll v0,v1,0x3` — mismatch at that position. Hmm, but maybe we can get a copy there instead?

The target: `move v1,a0` at 27 and `sll v0,a0,0x3` at 42. So a0 = iVar2, v1 = iv2c.

What if instead we arrange: iv2c in a0 and iVar2 in v1? Then the compare would be `beq a0,v0` — no.

Hmm.

What if the *else arm* computes t+1 into v1 (iVar2 in v1) and then the copy at the join is `move a0,v1`? That's the reverse — bytes differ.

So no.

Let me try one more class of ideas: **making the copy a 64-bit (DImode) copy**? no.

**Making iv2c a pointer?** `uint *iv2c; iv2c = (uint *)iVar2;`? Hmm! A cast between int and pointer is a plain copy in RTL (same mode). cse would equate them? Different types but same mode; cse works on modes, so yes, a copy.

What about **float**: `float iv2c; iv2c = (float)iVar2;` — that's an integer-to-float conversion (mtc1/cvt), not a move.

OK. Let me count my scored tries so far on this item: w1, w2, w3, w4? (w4 wasn't created), w6, w7, w8, w9, w10, w11, w12 = 11 scored candidates + orig baseline. I need 30 for a WALL. Hmm, that's a lot. But maybe I can do a batch of cheap variants.

Let me think about which variants have a real chance:

1. `one` declared as `int one` (not pinned)? That's dropping an existing pin — allowed to *keep*, not required. Dropping a pin is removing a lever (fine, it's not a row kind). But `one`'s pin gives `li v0,1` and the compare reg-reg. Without the pin, the compare might use an immediate... MIPS has no branch-immediate, so GCC would still need a register. Hmm, but the register could differ. Actually, the pin $2 matters for matching (target uses v0). Not helpful for the move.

2. Reorder: `one = 1;` BEFORE `iv2c = iVar2;`. Combine window: li, copy, beq → merges the copy into beq. Same.

3. Insert the copy inside the `if` of the compare... no.

4. **Use a conditional to compute uVar5 without a copy**: `uVar5 = (iv2c != one) ? 0 : uVar5;` — might produce a different branch structure. Probably the same code.

5. `if (iv2c - one) uVar5 = 0;` — different code.

6. Make the copy's destination a `u16`/`s16` and compare with `one`: produces sll/sra.

7. Try `iv2c = (int)iVar2;` — no-op.

8. Try declaring iv2c as `volatile`? Not allowed.

Hmm.

Let me revisit the possibility of blocking combine with a *call*. Is there a call nearby? `func_8005A600((s32)ot, 0, 0, 0x15, 0);` comes after the loop. Not in the middle.

What about the `puVar3[-1] = uVar1;` store — that's a memory store; if placed between the copy and the compare... it's semantically after uVar1 which depends on uVar5. No.

OK — actually, WAIT. What about `use_crosses_set_p`? If the insns are NOT all_adjacent, combine checks whether the source register (iVar2) is set between the copy and i3. If I insert an insn that sets iVar2 between the copy and the compare — but iVar2's value must be preserved... 

What if we write:
```
iv2c = iVar2;
iVar2 = iVar2;      // launder — no
```

Hmm.

What about `iv2c = iVar2; one = 1;` where `one = 1` also *uses* iVar2? Like `one = 1 & iVar2`? no.

Let me try yet another thing: **the `do { } while (0)` around `one = 1`** — no.

Let me try: what if the copy is `iv2c = iVar2;` and the compare is `if (one != iv2c)` — tested (w10) = 5.

Let me look at whether there's an existing successful header crack with a similar "copy adjacent to compare". Let me grep moves.md for header items (141/141) with a move v1,a0-like pattern... Hard.

Alternatively, look at the R3.40-013 helpers mentioned in the brief — maybe there's a tool that suggests moves. Not needed.

Decision time: I've spent ~30 min on this item (14:43 → now ~15:10?). Let me check the time. If I'm at 30 min with 11 tries, the rule says a WALL needs ≥20 min AND ≥30 scored tries. So I can't record a WALL yet — I must do 30 tries or keep going. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So to record a WALL I need 30 scored tries.

Alternatively, if I can't crack it in 30 minutes, I record... the brief says "Budget 20-30 min wall per item; past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries". So both conditions.

Let me generate a batch of ~20 variants cheaply and score them all with sc.sh (each ~5-8 s → ~2-3 min). Let me design a diverse batch:

a1: copy in then+else arms with `iv2c = 1` in then (w9 variant) — done.
a2: `one = 1;` moved before the copy.
a3: iv2c declared s16; compare with one.
a4: iv2c declared u16.
a5: iv2c declared unsigned.
a6: copy via `iv2c = iVar2;` inside a do-while around BOTH the copy and the compare.
a7: `do { iv2c = iVar2; one = 1; } while (0); if (iv2c != one) uVar5 = 0;`
a8: `if (iv2c != one) uVar5 = 0;` where iv2c is assigned in a do-while with the one assignment inside.
a9: `uVar5 = (iv2c != one) ? 0 : uVar5;`
a10: compare with `(s32)` cast.
a11: `iv2c = iVar2; iv2c += one - one;`? launder.
a12: use `iv2c` as a `long`.
a13: `iv2c = iVar2;` then `if (iv2c != one) { uVar5 = 0; }` with braces.
a14: `if (iv2c != one) { uVar5 = 0; } else { }`.
a15: swap the order: `one = 1; iv2c = iVar2; if (iv2c != one)`.

Many will be identical codegen. Hmm, that's a waste.

Let me think harder about a fundamentally different approach instead.

**KEY IDEA**: What if we make iv2c's copy have a source that is a *hard register* that is not a user variable? On MIPS, SMALL_REGISTER_CLASSES is defined, so `can_combine_p` returns 0 when `REGNO(src) < FIRST_PSEUDO_REGISTER && !REG_USERVAR_P(src)`.

Wait, re-read:

```
	      || (REGNO (src) < FIRST_PSEUDO_REGISTER
		  && (! HARD_REGNO_MODE_OK (REGNO (src), GET_MODE (src))
#ifdef SMALL_REGISTER_CLASSES
		      || ! REG_USERVAR_P (src)
#endif
		      ))))
	return 0;
```
So if src is a hard reg AND (mode not ok OR (SMALL_REGISTER_CLASSES && !uservar)) → return 0.

So a copy from a hard register that is not a user variable blocks combine. 

Which hard registers exist here? The pins: `one` ($2, a user variable — uservar), `puVar3` ($8), `nx` ($2), `c74` ($4), `c3` ($3), `m` ($2), `six` ($2), `c6b` ($3), `sx` ($2).

`one` is a user variable, so it doesn't block. But what if the copy's source is `one`? Hmm, we need the value iVar2.

Hmm, is there any hard reg that is NOT a user variable at that point? The pinned variables are all user variables (declared with register+asm). 

What about a value forced into a hard register by an insn constraint (e.g., a shift by a variable needs $rs? no).

OK so that route needs a pin — forbidden.

**ANOTHER IDEA**: What if the copy's *destination* is used in the compare in a way that combine's `combinable_i3pat` rejects? E.g., if the compare insn is a PARALLEL with a clobber... The branch_equality insn is a jump_insn with `(if_then_else ...)`. 

Hmm, what if the compare uses the value in a MEM address? no.

**IDEA**: What if we make the compare's second operand a *memory* value? no.

Let me look at the problem from the *reload* angle once more: the move is reload-inserted because of a tie. Ties come from asm and calls. 

Could a real C construct create a tie? **Yes**: a function call argument that must be in a specific register and is used again later. But there's no call at the join.

Hmm, unless... we move the compare into a context with a call? No.

OK, let me look at the target's move position once more: index 27, right after `sll a1,a1,0x4` (the else arm's last insn) and before `li v0,1`. 

What if this move is actually the *join* block's phi-like copy from a different structure: e.g., if iv2c were assigned in both arms, the join would have... no, assignments in arms are copies.

Hmm hold on, what if the source code had TWO variables: `iv2c` and another one, where `iv2c = iVar2` is a real copy that's used twice? Let me re-examine: is `iv2c` maybe used in the ORIGINAL source for something else that the banked body dropped? The banked body is the current best; the target code is what it is. The target has only one use of v1 after the move (the compare at 29). So no.

OK. Let me try the reload-class idea: what if iv2c is used in an insn with a *register class constraint* that reload must satisfy — e.g., a shift by iv2c? `x << iv2c` requires the shift amount in a register (any). No move needed.

What about a *division*? `x / iv2c` requires $2/$3 (HI/LO) — that would force moves. But it changes code.

Alright, let me consider: maybe the answer is to give up on this item (WALL) after 30 tries. But first, let me reconsider whether the item might be crackable with a *different* structural approach: what if the `one` pin ($2) is used as the copy destination... 

Actually here's a NEW idea: **make the copy's source die and the destination live, so local-alloc coalesces them into one register — but then the compare uses the same register as iVar2. Not matching.**

**Another idea**: what if we change which variable is copied: `iVar2 = iv2c`? Let's think: assign iv2c in both arms (then: 1; else: t+1), then at the join `iVar2 = iv2c`, then compare iv2c.

Then:
- else arm: `sra; andi; addiu v1,v0,1` (iv2c born in v1?) 
- then arm: `li v1,1`
- join: `move a0,v1` (iVar2 = iv2c)
- compare: `beq v1,v0`
- later: `sll v0,a0,0x3` (iVar2)

Insn count: the then arm has `li a0,1` replaced by `li v1,1`; the else `addiu a0` → `addiu v1`; the join has `move a0,v1` (target has `move v1,a0`). Same count = 56! But the register roles are swapped: target has iv2c in v1 and iVar2 in a0; ours has iv2c in v1 and iVar2 in a0 as well IF the allocator chooses so. The difference is the direction of the move: target `move v1,a0` (v1 = a0); ours `move a0,v1`.

Hmm, but the allocator might assign iv2c = a0 and iVar2 = v1! Then the else arm computes `addiu a0,...`, the then arm `li a0,1`, the join `move v1,a0` — EXACTLY the target!

Which assignment would the allocator choose? It depends on preferences. iv2c is live from the else arm to the compare; iVar2 from the join to the sll. Hmm, the target has iv2c in v1 (short-lived) and iVar2 in a0 (used later).

In our inverted version, iv2c is live across the join; iVar2 from the join to the sll.

It's plausible that iv2c lands in a0 (it's born in the else arm where a0 was the temp) and iVar2 in v1... Actually in the else arm, `t` is computed in v0, then `t+1` into a register — local-alloc picks a0 for it (since a0 is free). Then the join `iVar2 = iv2c` → v1? and the compare uses iv2c = a0... but the target's compare uses v1.

Hmm, so we'd get `beq a0,v0` and `move v1,a0` — the move direction matches but the compare operand differs!

Target: move v1,a0; beq v1,v0.
Ours: move v1,a0; beq a0,v0. — mismatch at the compare.

Unless the allocator puts iv2c in v1 and iVar2 in a0: then the else arm's addiu goes to v1, then move a0,v1 — direction differs.

Ugh.

OK. Let me estimate the value of continuing vs. recording a WALL. The brief says items 1&2 were PARTIAL with kinds kept; my job is to remove them. For the header item, if I can't, the result is a WALL with best = the lever-free best (5) and evidence.

But hold on — maybe I should reconsider the "launder" definition. The launder line is `__asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c))`. The kinds file says `launder`. What if I replace it with a *non-volatile* asm? No — still asm.

What if the launder could be replaced by the *keepalive* kind? No, kinds must be gone.

Hmm, but what about the "do{}while(0)" C0535 trick — it's a real-C move. It didn't work here.

Let me try the do-while around the *compare* with the copy outside:
```
iv2c = iVar2;
do {
    one = 1;
    if (iv2c != one) uVar5 = 0;
} while (0);
```
Here the copy is outside the block; the use is inside → different EBB? jump1 merges the do-while body into the preceding block (it's a jump-to-next). Probably merged.

What if the do-while is placed so the body's end label is a jump target... no.

Let me try a *loop* that the compiler keeps: no.

OK, let me take a completely different tack: check if maybe the *first* body (prev_win) can be made to score 0 without the launder by changing something ELSE so that the extra instruction appears elsewhere and the compare matches. For instance, if we accept `beq a0,v0` (no move), the target has `beq v1,v0` and an extra move. Total 55 vs 56. Since the target has an extra instruction, we MUST create one.

Could we create the extra instruction elsewhere (not the move) and still match? No — the diff shows the move's exact position.

Alright, one more idea: **make the compare use a *different* variable that is a genuine second value, computed by a copy that combine can't merge because the copy's source is a constant**! 

E.g., in the THEN arm the value is constant 1; in the ELSE arm it's t+1. What if we write:

```
iv2c = iVar2;
```
where iVar2 is... hmm.

What about making the copy `iv2c = iVar2` where iVar2 is *volatile*? forbidden.

What about making iv2c a *bitfield member of a local struct*? That's memory.

Hmm, hold on: what about making iv2c a **`s16` field of a local struct**? no, memory.

What about **`register`**? forbidden.

Let me try the "inverted copy" (iVar2 = iv2c) empirically — it's cheap and might just work if the allocator cooperates. Let me write it:

```
            {
                int iv2c;
                register int one __asm__("$2");  // pin
                if ((short)iVar4 == six) { iv2c = 1; uVar5 = 0; }
                else {
                    int t;
                    t = param_2 >> 0x10 & 0xf;
                    iv2c = t + 1;
                    param_2 = param_2 << 4;
                }
                iVar2 = iv2c;
                one = 1;
                if (iv2c != one) uVar5 = 0;
            }
```
Semantics: iv2c = 1 in the then arm; else t+1; iVar2 = iv2c (needed later for r); compare iv2c.

Wait, but in the then arm the target has `li a0,1` (iVar2 = 1). In my version iVar2 = iv2c happens at the join as a copy. Good.

Combine: the copy `iVar2 = iv2c` at the join; iVar2's use is far (insn 42) → combine can't merge (not within 3 insns... well, between the copy and the sll there are several insns). Actually combine only merges i1 with i3 if they're linked by LOG_LINKS and adjacent-ish; here the use is far, so the copy survives. And local-alloc: iv2c is live at the copy (dies at the compare) — iVar2 is born at the copy. They conflict only briefly... local_alloc may coalesce if iv2c dies at the copy — it doesn't (it's used at the compare after). So no coalescing → a move is emitted!

Then the register assignment: the compare uses iv2c; the sll uses iVar2. Target wants compare on v1, sll on a0.

Let's test it!
