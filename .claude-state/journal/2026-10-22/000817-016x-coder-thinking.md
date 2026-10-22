---
ts: 2026-10-22T06:08:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_OQYLMj0lqIVjVNP3qwca
---
So all previous attempts varied only the vol launder site. The residual (delay slot) was never attacked by restructuring the sx/shift part.

Now, my new plan: attack the delay slot. The key structural difference: the target has the sll duplicated (delay slot copy + join) with the branch redirected past the join's sll, whereas mine has the andi speculated into the delay slot.

Idea A: Make the andi NOT a candidate for the bne's delay slot. The andi is `andi a1,a1,0xffff` on the argument. What if the argument is masked in a way that produces a different instruction? E.g., if the arg expression is computed as u16: `func_8002D4C8(0x9E5, (u16)(vol | (0x3000 | sx)));` — that would emit `andi` too probably.

Hmm, but here's the thing: in mine, the andi appears in the delay slot AND at cc4. The one at cc4 is the "real" one in the jal's delay slot. The one at ca8 is the speculative copy. So reorg chose to copy the andi into the bne's delay slot. If instead the sll were chosen, we'd match.

Why would reorg prefer the andi over the sll? In gcc 2.7's reorg.c, `reorg_fill_slots` for a conditional jump with an empty delay slot:

```c
	  /* If this is a conditional branch, and the delay slot is empty,
	     then we can try to find an instruction to move into the delay
	     slot.  We search the instructions between the branch and the
	     target for a suitable candidate... */
```
Hmm.

Actually, gcc 2.7 reorg.c has this important part in `reorg_fill_slots`:

```c
      /* If this is a conditional branch, ... look at the instructions
	 after the branch (in the same basic block) ... */
```

But more importantly, gcc 2.7's reorg.c has "reorg_jump_to" which handles the case of a conditional branch whose target is the next block, and it uses `mips_fill_slot`? Hmm.

Wait — gcc 2.7 mips.c DOES have this function:

```c
/* Return the number of instructions in the delay slot ... */
...
/* Move an instruction into the delay slot of a branch if it is cheaper... */
static int
mips_reorder_insns (rtx insn, rtx branch, rtx delay_slot, struct pipelinable *pipelinable)
```

I'm now fairly confident: gcc 2.7 mips.c has `mips_reorder_insns` (a "machine_dependent" hook called from reorg.c as `machine_dependent(insn)`) that reorders instructions to improve delay slot filling. Its logic (from memory of gcc 2.7.2 mips.c):

```c
/* Reorder instructions to improve delay slot filling.  ...
   We try to find an instruction to move into the delay slot of a branch.
   The instructions we consider are those between the branch and the
   target of the branch.  We prefer instructions that are cheap and
   that don't increase register pressure.  */
static int
mips_reorder_insns (rtx insn, rtx branch, rtx delay_slot, struct pipelinable *pipelinable)
{
  rtx temp;
  ...
  /* Get the next few instructions after the branch.  */
  ...
  for (temp = first_insn_after (insn); temp && !LABEL_P (temp) ...; temp = next_insn (temp))
    {
      ...
      /* If the instruction is a call, don't move it. */
      /* If it modifies a register used by the branch ... */
      ...
    }
}
```

The key candidate properties in gcc 2.7's mips_reorder_insns (I recall the actual code now):

```c
      /* Ignore things that we can't move (calls, jumps, labels) */
      ...
      /* Ignore if the insn is the target of a jump */
      ...
      /* If the instruction is a "move" of a register, it's cheap */
      ...
      /* Prefer instructions that are not in the same register as the branch */
```

I really can't reconstruct it. EMPIRICAL.

Let me think about which property distinguishes the sll from the andi:
- The sll modifies a2 (the branch's operand!). If gcc's rule is "don't move an instruction that modifies a register used by the branch", the sll would be rejected. But the target HAS the sll in the delay slot... So that rule can't be absolute for MIPS (the branch's operands are read before the delay slot).

Hmm, wait. Maybe in the target, the branch's condition register is different! Let's look: `bne a2,v0,cb4` — a2 is compared with v0. And the delay slot `sll a2,a2,0x8` modifies a2. So the delay slot DOES modify the branch's operand. So gcc allowed it.

Hmm, unless the original source's shift was on a DIFFERENT variable than the one being compared! E.g.:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
```
Here the compared value and the shifted value are the same pseudo (a2).

But what if the source used two variables:
```
s32 t = (sx + 0xA0) / 0x14;
if (t == 0x10) t = 0xF;
sx = t << 8;
```
Then the branch compares t and the sll shifts t. Same.

What if the source were:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
```
and gcc reorg's rule allows modifying the branch's register ONLY if the branch's operands are "latched" (i.e., the machine has a separate condition register). MIPS doesn't have one, but in gcc's MIPS backend the branch operands are read at the branch, and the delay slot executes after — so it's safe. gcc 2.7 mips.c has a comment about this.

OK so the difference must be elsewhere. Let me consider: maybe in MY version the sll is not "movable" because of register pressure: moving the sll into the delay slot requires a2 to be live at that point (it is). Hmm.

ALTERNATIVE HYPOTHESIS: maybe the target's C has the sll TWICE (in both arms), as I discussed, and gcc's reorg then just had an easy job: the else block (single sll) got copied into the delay slot and the branch redirected to the join.

In that case, the C spelling that produces the target could be:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; sx = sx << 8; }
else { sx = sx << 8; }
```

Hmm, but wait: the target's THEN arm is `li a2,15; sll` and the ELSE is the delay-slot sll. If the source had the sll in both arms, the RTL would be:
```
bne a2,v0, ELSE
THEN: li a2,15 ; sll a2,a2,8
ELSE: sll a2,a2,8
JOIN:
```
and reorg would fill the bne's delay slot with a copy of ELSE's sll and redirect the branch to JOIN. The THEN block ends with the sll, and the delay slot's copy is dead there (li a2,15 overwrites a2 before cb0's sll). EXACTLY the target!

But hold on, would the RTL really keep the sll in both arms? gcc's expand of:
```
if (c) { A; B; } else { C; }
```
where B and C are the same operation on different values — yes, it keeps both.

Hmm, but would the retail source really be written that way? Maybe the retail source is:

```
if (sx == 0x10) {
    sx = 0xF;
    sx = sx << 8;
} else {
    sx = sx << 8;
}
```
Unlikely. More likely:
```
sx = (sx == 0x10) ? 0xF : sx;
sx = sx << 8;
```

Hmm. But you know what? There's another classic C spelling that duplicates the shift into both arms: using a **ternary inside the shift**:
```
sx = ((sx == 0x10) ? 0xF : sx) << 8;
```
How does gcc 2.7 expand this? expand_expr for COND_EXPR: it creates a branch, computes the two arms into a pseudo, joins. The shift is applied to the pseudo AFTER the join. So single sll in the join. Not duplicated.

What about:
```
sx = (sx == 0x10 ? (0xF) : sx) * 256;
```
Same.

Hmm, what if the source is:
```
if (sx == 0x10) sx = 0xF;
sx = sx * 0x100;
```

OK, so how about I consider that the ORIGINAL source had a helper that gcc expanded into duplicated code? E.g.:

```
if (sx == 0x10) { sx = 0xF; }
sx <<= 8;
```

Let me just TEST the "sll in both arms" hypothesis directly: write the C with the shift in both arms and see if the score becomes 0. If yes, great — it's a plain-C lever-free body (no asm), and it's a legitimate C spelling (equivalent semantics). Then I can try to find a prettier equivalent spelling.

Actually even better: think about which C produces the duplicated shift naturally:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) {
    sx = 0xF;
}
sx = sx << 8;
```
vs
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) {
    sx = 0xF;
    sx = sx << 8;
} else {
    sx = sx << 8;
}
```

Let me just try the second. Also try:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
```
with the arg computed differently.

Let me also consider: maybe the real difference is that in the target, the *whole* if-block was compiled with the shift inside because of how the ORIGINAL source was written:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) {
    sx = 0xF;
}
sx = sx << 8;
```
and gcc's *if-conversion*... no, gcc 2.7 has no if-conversion.

BUT: gcc 2.7 DOES have "expand" of a "PAD" ... hmm.

Let me just test. Fast scoring helps.

Another idea (Idea B): keep the single sll but make the *andi* not appear before the branch. The andi in the delay slot is a speculation. If the andi were scheduled later (e.g., if the argument mask were applied to a value computed after the shift), reorg might pick the sll.

Idea C: What if we swap the order: compute the argument mask before the shift? e.g.
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
arg = vol | (0x3000 | sx);
arg &= 0xFFFF;
sx = sx << 8;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
No, that changes the value.

Idea D: use a separate variable for the shifted value:
```
s32 t = (sx + 0xA0) / 0x14;
if (t == 0x10) t = 0xF;
sx = t << 8;
```
The RTL: the branch compares t, and the sll shifts t. Might change regalloc.

Let me now write a batch of variants and score them. I'll create a helper script to score many files at once. bin/sc.sh does that (one line per candidate). Let me use it.

Let me write the variants. I'll base them on q1.c (the best) and modify.

Variant list:
- r01: shift in both arms (explicit if/else).
- r02: t temp, shift from t.
- r03: `sx = sx << 8;` moved to just after the `if` but as a separate statement with the arg in a var.
- r04: arg computed into a var before the shift:
  ```
  s32 arg;
  ...
  sx = (sx+0xA0)/0x14;
  if (sx == 0x10) sx = 0xF;
  arg = (vol | (0x3000 | (sx << 8))) & 0xFFFF;   /* shift inside the arg */
  func_8002D4C8(0x9E5, arg);
  ```
  This puts the sll inside the argument expression, adjacent to the or chain. Then the RTL after the branch: sll; or; andi. Hmm, same order.
- r05: the shift as part of the arg expression inline: `func_8002D4C8(0x9E5, (vol | (0x3000 | (sx << 8))) & 0xFFFF);` with `sx = (sx+0xA0)/0x14; if (sx==0x10) sx=0xF;` before.

Hmm wait, careful: currently the source is:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```

r05 would be:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
func_8002D4C8(0x9E5, (vol | (0x3000 | (sx << 8))) & 0xFFFF);
```
The difference: the shift is now inside the arg. In the RTL, the sll is then in the arg computation, which is in the same block as the or/and. And the "sx" variable's final value isn't stored. Hmm, but then the "sx = 0xF" assignment and the shift are related: the shift's input is the result of the if. With the shift inside the arg expression, the RTL would be:
```
bne a2,v0, JOIN
li a2,15
JOIN: sll a2,a2,8
ori a1,a1,0x3000
or a1,a1,a2
jal
andi
```
Same as before basically. But the *scheduling* may differ: the shift is now part of the call-arg group, so it might be scheduled differently.

Actually here's a thought: the current source has `sx = sx << 8;` as a separate statement, and the comment says "in place, so reorg can steal it into the bne delay slot". The author of that comment presumably had the target and was trying.

Let me now think about the real difference once more, considering the target's RTL:

Target layout:
```
ca0: li v0,16
ca4: bne a2,v0,cb4
ca8: sll a2,a2,0x8     <- delay
cac: li a2,15
cb0: sll a2,a2,0x8
cb4: li a0,2533
```

vs mine:
```
ca0: li v0,16
ca4: bne a2,v0,cb0
ca8: andi a1,a1,0xffff  <- delay
cac: li a2,15
cb0: sll a2,a2,0x8
cb4: li a0,2533
```

Interesting: in the target, the branch target is the JOIN (cb4) and the sll at cb0 is in the fall-through path. In mine, the branch target is cb0 (the sll) — the classic "join" structure.

So in the target, the RTL is:
```
bne a2,v0, JOIN
delay: sll (copy)
li a2,15
sll
JOIN:
```
The delay-slot copy comes from a "copy_insn" of the join's first instruction, and the branch is redirected to skip it. Wait, but then the branch path would execute the sll twice? No: the branch path goes to JOIN (cb4) and executes the sll only in the delay slot. The fallthrough path executes li a2,15, then the sll at cb0, then JOIN. So the sll executes exactly once per path. So the sll is duplicated in the machine code but the RTL has ONE sll, in the join block, and reorg copied it into the delay slot AND redirected the branch to the instruction after the sll. That's exactly gcc 2.7's reorg "bypass the instruction in the target block" behavior. This is a known gcc 2.7 reorg feature! In reorg.c:

```c
  /* If we have a conditional branch, and the delay slot is empty, ...
     Try to find an instruction in the target block to copy into the
     delay slot.  If we do that, we can also redirect the branch to
     skip over the original instruction (if it is the first in the
     block).  */
```
Yes — gcc 2.7's reorg.c has `reorg_fill_slots` with:
```c
	      /* If we are jumping to a block that has only one instruction,
		 we can move that instruction into the delay slot and
		 redirect the jump.  */
```
I'm fairly confident this is real: gcc 2.7 reorg.c contains a "bypass" optimization where a one-instruction target block's instruction is copied into the delay slot and the branch is redirected to the block's successor.

So the target's structure is exactly one sll in the join, copied into the delay slot, and the branch redirected. That's the SAME RTL as mine! The difference is only that in mine reorg instead picked the andi as the delay-slot filler (and did not redirect the branch).

So the question is why reorg chose the andi over the sll in my version.

gcc 2.7's reorg.c `reorg_fill_slots` for a conditional branch: it looks for a candidate in the *fallthrough* path or in the target block. The candidate search is in `reorg_jump_to` / `fill_insn`.

I recall in gcc 2.7 reorg.c:

```c
/* Return true if we can fill the delay slot of INSN with the
   instruction at TGT ... */
static int
can_fall_through (rtx insn) ...

static int
invert_conditional_branch (rtx jump) ...

/* Find a new location for the instruction at TGT ... */
```

and:

```c
/* Try to find an instruction to move into the delay slot of the
   conditional branch at JUMP.  ... */
```

Honestly, empirical is the way. Let me consider what makes the sll a better candidate in the target:
- In the target, at the time of the bne, is the sll in the *target block*? Yes.
- In mine, the sll is also in the target block (cb0 = the branch target).

Hmm, so structurally the same! The difference must be in the *cost* of the candidates or in the availability of the andi.

In mine, the andi is available (it's in the call group). In the target, the andi is also in the call group. So why didn't reorg pick the andi in the target?

Because reorg picks the FIRST candidate it finds scanning forward from the branch: the sll comes first (in the join block) in both. Unless in mine, the andi was already IN the delay slot before reorg ran (i.e., the scheduler put it there) and reorg only fills EMPTY delay slots.

That's likely! In gcc 2.7 MIPS, the `sched2` pass (post-reload scheduler) has a "delay slot" filling step: the `mips_sched2` pipeline ends with a step that moves the last instruction of the block into the delay slot of a branch. Yes! In gcc 2.7's mips.md there's:

```
(define_sched ... )
```
and in mips.c, `mips_sched2` ... Hmm, actually the delay-slot filling in gcc 2.x MIPS was done by `reorg` using the `mips_fill_slot`... 

Hmm, hold on: gcc 2.7 mips.c contains this function:

```c
/* Return the number of instructions in the delay slot ... */
...
/* MIPS has a "delay slot" ... the instruction that follows a jump is
   executed before the jump is taken.  ... */
```

OK.

Let me take yet another approach: instead of theorizing, generate a broad matrix of variants and score them. The scoring takes ~1s. I can run 50 variants in a minute. Let me be systematic.

Variants (all based on q1.c's `vol = (u16)vol;` lever removal):

A. shift inside the arg expression (r05).
B. shift in both arms (r01).
C. t temp (r02).
D. arg into a variable (r04).
E. `sx <<= 8;` compound.
F. `sx = sx * 0x100;`
G. `sx = (sx << 3) << 5;` (probably wrong, but the target's sll is <<8 exactly, so no)
H. The `if` written as `if (sx == 0x10) sx = 0xF; else sx = sx;`
I. swap the order of the vol computation and the sx computation (statement order).
J. Compute vol after the sx chain.

Also, the andi: what if the mask is applied to a u16 variable?

Let me write these and score. I'll write a small Python generator to make the variants from orig.c with textual replacements. Actually simpler: write each variant file with the Write tool? That's many tool calls. Better: one Python script that generates all variants, then sc.sh to score them all.

But wait: the constraint says "no `register` vars, no `__asm__`" — the existing q1.c keeps `register s32 av __asm__("$5")` (the $5 pin). Is the pin a "row kind"? kinds = "launder" only. And the "levers of other kinds the def already had (pins under other causes) may stay". Hmm, but the CONSTRAINTS line says "no `register` vars, no `__asm__`". That's contradictory with "pins of other kinds may stay".

Look at the other G14 items: func_8018CDEC's win.c keeps `register s32 tmp __asm__("$2")` etc. and the result was MATCH with kinds=launder. So the established practice in this shard: pins stay (they're not the row kind). The CONSTRAINTS "no register vars, no __asm__" must mean "don't ADD any".

Hmm, but for the av pin: is it "under another cause"? The pin $5 is on av. In the target, is av in $5? Let's check the target asm: `c50: move a1,a2` (av = sx in a1=$5) and `c54: negu a1,a2`. Yes, av is in a1 = $5. So the pin is needed to match. Keep it.

So my lever-free body = q1.c (launder → `vol = (u16)vol;`) plus possibly more restructuring, keeping the $5 pin.

Wait, but hold on: is `vol = (u16)vol;` a "real 2nd set"? Yes, and it's value-preserving (vol is 0..127). Good, and it's the same trick that cracked other items.

Now, let me also consider: maybe I should try the `sx` restructure with different lever-free spellings of the vol site, combined. The handoff says the best is q1.c (u16 cast). Other vol spellings scored worse (s16=33, do-while=25, plain removal=39).

But maybe with a different sx structure, the vol spelling changes which is best. The search space is 2D. Let me first nail the sx structure with q1's vol spelling, then re-test vol spellings with the best sx structure.

Let me write the generator script.

Actually, let me think harder about one specific promising variant: the "sll in both arms" (r01). If gcc's reorg sees a one-instruction target block, it can copy it into the delay slot. But in my current version the target block (cb0) is ALSO a one-instruction block (just the sll). So reorg had the same opportunity and didn't take it (it filled the slot with the andi instead).

Hmm, so why? Because in mine, the andi was ALREADY in the delay slot (sched2 put it there). So reorg found the slot occupied and left it.

So the real question: why did sched2 (or whatever) put the andi in the bne's delay slot in mine, but not in the target?

In gcc 2.7's MIPS, the delay slot filling is done by `reorg` (reorg.c) which is called after sched2. But there's ALSO the `mips_sched2` custom pipeline? In gcc 2.7 mips.md:

```
(define_sched "mips_sched" ...)
```

Hmm.

Alternatively, the delay slot might be filled by the *reload* pass (reload.c has `reload_follow_jump`/`reload_find_slot`)! YES! In GCC, `reload.c` has a "reload_follow_jump" and importantly `reload_find_slot()` which finds a register to put in a branch's delay slot! reload.c's reload_find_slot is used for reloads: it tries to find a register whose value is needed in the delay slot. But there's also the general "fill the delay slot with a junk value" logic.

Hmm, but in gcc 2.7 mips.c, the delay slots are filled by `mips_final_prescan_insn`? no.

I recall in gcc 2.7, `final.c` has `final_prescan_insn` and the delay slot filling for MIPS is in `mips.c`'s `mips_final_prescan_insn`? Hmm, no: mips.c has

```c
/* Machine dependent end of compilation.  */
static int
mips_final_prescan_insn (rtx insn, ...)
```

Hmm.

Actually! In gcc 2.7, reorg.c is the pass that does "fill_delay_slots" and it has this comment: "Machine dependent reorg.  On machines where branches have delay slots, ...". And reorg is invoked from toplev as:

```
  NEXT_PASS (reorg);
  NEXT_PASS (final);
```

reorg.c's `reorg_fill_slots` does the work, using `machine_dependent ()` hook → mips.c's `mips_reorder_insns`? Hmm, no, gcc 2.7 mips.c's machine_dependent function is:

```c
/* Machine dependent function to see if we need to align ... */
static int
mips_machine_dependent (rtx insn, rtx *delay_slot, rtx branch, rtx new_label, int *safety, int *avail, int *ru_avail)
```

Hmm. In gcc 2.7 mips.c I definitely remember:

```c
/* Return the number of instructions we should skip ... */
...
/* Move a machine instruction into the delay slot ... */
static void
mips_move_to_delay_slot (rtx insn, rtx branch, rtx delay_slot, ...)
```

OK OK. Empirical time. Let me generate variants.

One more important idea: since the andi is the problem (it occupies the delay slot), maybe I can make the andi *not exist* before the branch by changing how the argument is masked. For instance, if the argument were computed as a u16 in the source:

```
func_8002D4C8(0x9E5, (u16)(vol | (0x3000 | sx)));
```
This might generate the andi in a different place (or the same).

Or: what if the mask is applied to `sx` alone? `(vol | (0x3000 | (sx & 0xFFFF)))` — the andi would depend on sx (a2) and be after the branch. But that changes semantics! (vol|0x3000|sx)&0xFFFF vs vol|(0x3000|(sx&0xFFFF)) — different if vol has bits above 0xFFFF (vol ≤ 0x7F so no) or 0x3000 has bits above (no). Actually (vol|0x3000|(sx&0xFFFF)) vs (vol|0x3000|sx)&0xFFFF: the RHS masks everything to 16 bits; the LHS keeps vol's high bits (none) and sx's high bits (masked). So they're equal IF vol ≤ 0xFFFF and sx's high bits are dropped in both. In the RHS, sx's high bits are dropped by the &0xFFFF. In the LHS, sx is masked first then ORed — same. And vol: RHS masks vol to 16 bits; LHS keeps vol unmasked. If vol ≤ 0x7F, equal. So it's semantically equivalent given vol ≤ 0x7F! And gcc can PROVE vol ≤ 0x7F? vol = ((0xA0-av)*0x7F)/0xA0 with av = |sx|, sx = (s16)sxy[0]. Hmm, av could be up to 32768 → (0xA0-av) could be negative → vol could be negative! Hmm: if sx < 0, av = -sx, so 0xA0-av could be negative → vol = negative/0xA0 = negative. So vol is NOT necessarily 0..127!

Hmm wait, in the target: `subu v0,v0,a1` (0xA0 - av) then `sll v1,v0,0x7; subu v1,v1,v0` (v0*0x7F) then mult by the magic → division by 0xA0. If the numerator is negative, the result is negative. So vol can be negative. Then (vol | 0x3000 | sx) & 0xFFFF vs vol | 0x3000 | (sx & 0xFFFF) differ if vol has high bits set (i.e., vol < 0). So the transformation is NOT semantics-preserving in general. But hold on — the *guard* is `L.flag >= 0 && (u32)((L.sxy[0]+0x9F)&0xFFFF) < 0x13F && ...` which bounds sxy[0] to [0x9F-0x13E, 0x9F] roughly → sx = (s16)sxy[0] in [-0x9F, 0x9F] ≈ [-159,159]. So av ≤ 159 < 0xA0=160 → 0xA0-av ≥ 1 → vol ≥ 0 and ≤ 127. But gcc can't prove that (the mask arithmetic is opaque). Anyway, I shouldn't rely on it; the transformation changes the emitted value only in unreachable cases, but the compiler doesn't know that. But since I'm writing C that the compiler compiles, the *semantics* of my C must match the ROM's for all inputs to be a legit decomp. The constraint is that my body must be "real C moves" faithful to the original. The original presumably had `& 0xFFFF` on the whole arg. So I should keep the mask on the whole expression.

Hmm, OK. But here's the thing: the ORIGINAL source (retail) is what produced the target asm. The retail source's argument expression produced `andi a1,a1,0xffff` in the jal delay slot — the whole-arg mask. Fine.

So the question remains: how did the retail source avoid the andi landing in the bne's delay slot?

Possibility: the retail source had a different statement ORDER, e.g. the shift `sx = sx << 8` written such that the RTL order differs. OR the retail source's `sx == 0x10` test used a different variable.

Hmm, here's another thought. What if the retail source was:

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
sx = sx << 8;
```

and the difference is the *vol* computation! In the target, the vol multiply comes BEFORE the pan multiply (mult v1,a0 at c70 then mult v0,a0 at c80). The launder's purpose was exactly to keep that order ("sched1 otherwise hoists the PAN multiply ahead of this one"). In my q1.c, the order IS the same (mult v1,a0 at c70, mult v0,a0 at c80). OK.

But what about the *scheduling* of the sll? In the target, the sll is in the delay slot. The sll depends on a2 (the divide result at c9c). The bne is at ca4.

What if, in the target, the RTL had the sll immediately after the branch in the SAME block? I.e., the RTL is:
```
bne a2,v0, ELSE_BLOCK
sll a2,a2,8      <- same block, becomes the delay slot naturally
...
```
Hmm! In gcc, a COND_JUMP's "jump" and the instructions after it in the same block: the block is split at the jump. The instructions after the jump in the same basic block become the fallthrough.

OK, let me now think about the *and the delay slot* difference from the perspective of "which instruction is cheapest/safest".

gcc 2.7 reorg.c's `reorg_fill_slots` → for each branch with an empty delay slot, it calls `fill_insn()`:

```c
/* Try to fill the delay slot of the branch at JUMP with an instruction.
   ...
   We search forward from JUMP for an instruction to move into the delay slot.
   The instruction must be:
     - not a call or jump
     - not the target of a jump
     - safe to execute before the branch (all its inputs live before the branch)
     - not modify a register used by the branch (unless the machine allows)
*/
```

and the search `find_by_class`... Honestly.

Let me look at this from a completely different angle: what if the andi in the delay slot in my version is NOT a speculation but a *sched2* artifact, and the real difference is that in the target the argument's mask was computed AFTER the shift in the RTL because the retail source computed the arg in a variable?

Let me try several and see.

Let me now actually write the generator. I'll create a Python script under the item dir (allowed: "write only under .run/P40/T11/G14/").

Variants to generate (each = orig.c with the vol launder replaced by `vol = (u16)vol;` plus a structural change):

I'll parameterize:
- VOLSPELL: "u16" (fixed for now, best)
- SXSTYLE: several variants of the sx/shift/arg block.

SXSTYLE variants:
 s0: current:
   ```
   sx = (sx + 0xA0) / 0x14;
   if (sx == 0x10) { sx = 0xF; }
   sx = sx << 8;
   func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
   ```
 s1: shift inside the arg:
   ```
   sx = (sx + 0xA0) / 0x14;
   if (sx == 0x10) { sx = 0xF; }
   func_8002D4C8(0x9E5, (vol | (0x3000 | (sx << 8))) & 0xFFFF);
   ```
 s2: shift in both arms:
   ```
   sx = (sx + 0xA0) / 0x14;
   if (sx == 0x10) { sx = 0xF; sx = sx << 8; } else { sx = sx << 8; }
   func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
   ```
 s3: temp t:
   ```
   { s32 t = (sx + 0xA0) / 0x14; if (t == 0x10) { t = 0xF; } sx = t << 8; }
   ```
 s4: arg into var:
   ```
   s32 arg;
   ...
   sx = (sx+0xA0)/0x14; if (sx==0x10) sx=0xF; sx = sx<<8;
   arg = (vol | (0x3000 | sx)) & 0xFFFF;
   func_8002D4C8(0x9E5, arg);
   ```
 s5: arg into var, and the shift after computing the arg? no, order matters.
 s6: `(sx << 8)` written as `sx * 0x100`.
 s7: `sx <<= 8;`
 s8: the if as `if (sx == 0x10) sx = 0xF; else ;`
 s9: swap: compute the arg mask earlier in the source:
   ```
   sx = (sx+0xA0)/0x14;
   if (sx == 0x10) sx = 0xF;
   sx = sx << 8;
   ```
   with the vol computed after the sx block (statement order swap).

Also: the position of the `vol` computation relative to the sx block (statement order) — the target's order is vol first, then sx.

Also try: does the andi get into the delay slot only because it's the LAST instruction before the call? What if the call's argument is `(vol | (0x3000 | sx)) & 0xFFFF` → the andi is the last op. If instead the source had the mask on a separate variable computed BEFORE the shift...

Let me also try: what if the whole arg expression is masked differently: `(vol | 0x3000 | sx) & 0xFFFF` (no inner parens) — the RTL might differ (the or chain associativity). Worth trying: `vol | 0x3000 | sx` vs `vol | (0x3000 | sx)` — different association → different RTL order! In the target, the order is: ori a1,a1,0x3000 then or a1,a1,a2 — so (vol|0x3000)|sx, i.e., left-assoc `vol | 0x3000 | sx`. My current source is `vol | (0x3000 | sx)` = vol | (0x3000|sx) → the RTL would be ori a1,a1,0x3000; or a1,a1,a2 → same (gcc reassociates? or the tree is (0x3000|sx) first then vol|that → or a1,a1,a2 first, then or with vol). The emitted order in mine is the same as the target (ori then or), so gcc canonicalized it.

OK, let me just generate and test. Enough theory.

Let me write the generator script.
