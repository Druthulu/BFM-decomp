---
ts: 2026-10-22T06:18:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YbIZeTWgVgnxhTsCxbg0
---
There ARE two andis: cb4 (the u16 cast, dead) and cc8 (the jal delay slot, the real mask). So this variant has an EXTRA andi (the dead u16 cast at cb4) compared to the target. The target has only the cc4 one.

So the "aftershift+nest" variant = the target + 1 extra dead andi at cb4, shifted by 1 instruction. Score 13.

So the ideal would be: no extra andi, with everything else matching.

Summary of the 4 key variants:
- q1 (aftervol+nest): extra andi in the bne delay slot (as a dead copy), the real mask at cc4 (jal delay) ✓. The branch goes to cb0 (not cb4). Score 2.
- aftershift+nest: extra dead andi at cb4, everything else ✓ (delay slot = sll, branch = cb4, registers ✓). Score 13.
- aftershift+left (t8): NO extra andi, but the or-chain is reassociated and vol is in a3. Score 5.
- aftervol+left: extra andi in the bne delay slot + reassociated chain. Score 7.

KEY INSIGHT: the "nest" or-form gives the target's or-chain and register allocation; the "left" or-form gives no extra andi but a reassociated chain.

Why does the or-form change the andi count?! In the "nest" form, gcc applies the mask distribution: (vol | (0x3000|sx)) & 0xFFFF → gcc distributes the mask: (vol&0xFFFF) | ((0x3000|sx)&0xFFFF). Hmm.

Hmm, but in the "left" form ((vol|0x3000)|sx)&0xFFFF, gcc would distribute the mask over the or-chain: ((vol&0xFFFF)|0x3000|(sx&0xFFFF)). Hmm, but sx&0xFFFF would be an extra andi on sx.

Hmm, the observed difference:
- "nest" → 2 andis total (the cast's andi + the final mask).
- "left" → 1 andi (the final mask) — the u16 cast's andi was ELIMINATED because the final mask subsumes it! (vol&0xFFFF)|0x3000|sx then &0xFFFF → the compiler can drop the early mask since the final mask makes it redundant? but the final mask is applied to the whole thing, and (vol&0xFFFF)|0x3000|sx & 0xFFFF = vol|0x3000|sx & 0xFFFF — so the early mask is redundant ✓).

So in the "left" form, gcc eliminates the redundant early mask (folding (x&0xFFFF) into the final mask) — that's why there's only 1 andi. In the "nest" form, gcc keeps the early mask (it doesn't do the redundancy elimination across the reassociation).

So the extra andi comes from the u16 cast. To avoid it, the u16 cast's andi must be *absorbed* into the final mask — which happens in the "left" form.

So I want: the "left" form (so the andi is absorbed) BUT with the or-chain in the target's order ((vol|0x3000)|pan) and vol in a1.

In the "left" form, gcc reassociated to ((pan|0x3000)|vol)?! Hmm, that's odd. Let me look at the "left" form's RTL again:
```
cb8: ori a1,a2,0x3000   ; a2 = pan
cbc: or a1,a3,a1        ; a3 = vol
```
Hmm interesting: `or a1,a3,a1` — the destination a1 = a3 | a1 = vol | (pan|0x3000). So the RTL is vol | (pan|0x3000)?? Hmm, that's the "left" form ((vol|0x3000)|sx) reassociated to vol|(sx|0x3000)!

So gcc's reassociation in the "left" case put the constant with the sx: (vol|0x3000)|sx → vol|(sx|0x3000)? That's a "constant sinking" reassociation. Hmm, weird but plausible: gcc's reassoc moves the constant to the operand with... hmm.

Whereas the "nest" form vol|(0x3000|sx) gives (vol|0x3000)|sx (the constant first). Hmm, so the "nest" form is preserved and the "left" form gets reassociated?

Hmm, wait. That's backwards from what I'd expect. Let me reconsider: maybe in the "left" form gcc keeps ((vol|0x3000)|sx) and the OUTPUT shows `or a1,a3,a1` = a3 | a1 where a1 = (pan|0x3000)?? That would mean the RTL is vol | (pan|0x3000).

Hmm, so the RTL is vol|(0x3000|pan) in the "left" case and (vol|0x3000)|pan in the "nest" case. That means gcc's reassociation DID happen in the "left" case: from ((vol|0x3000)|pan) to vol|(0x3000|pan)?? That's a "rotate" reassociation. gcc 2.7's reassociation for commutative ops with a constant: it tries to place the constant at the "end" of the chain or the "beginning" depending on the operand ordering rules.

Whatever — the point: the emitted operand order follows the reassociation.

So how do I get BOTH (a) the andi absorbed (so no extra andi) and (b) the or-chain (vol|0x3000)|pan?

Option: make the u16 cast's andi be absorbed by an explicit mask in the source. I.e., write the argument as:
```
func_8002D4C8(0x9E5, ((vol & 0xFFFF) | 0x3000 | sx) & 0xFFFF);
```
Hmm, that has 2 andis in the source but gcc would fold the redundant one.

Better idea: what if the u16 cast is applied to a value where the mask is NOT redundant... no, we want to avoid the extra andi entirely.

ALTERNATIVE: what if the 2nd set of vol is created WITHOUT an andi? Let's revisit: the 2nd set's purpose is to make sched1 keep the vol multiply first. What if the 2nd set is on a DIFFERENT variable — e.g. the pan value (sx)? Let's think: the target's structure has the vol multiply first and the pan multiply second, sharing the magic in a0.

In the plain body (no 2nd set at all), the pan multiply came first and the magic was duplicated (a0 and a2).

What if the 2nd set is on `sx`? E.g. `sx = (u16)sx;` — hmm, that would add an andi on sx (a2) and might land in the delay slot too.

What about a 2nd set on `av`? `av = (u16)av;` — av is in a1 (pinned $5!). Hmm, the pin means av is in a1 always. The andi would be on a1.

Hmm. What if the 2nd set is on the *magic* — no, the magic is a compiler temp.

Hmm, what if the 2nd set is a "real 2nd set" of vol that produces NO instruction? Options:
- `vol = vol;` → cse removes it. BUT: what if the assignment is to a DIFFERENT variable that is then used? E.g.:
  ```
  s32 vol2 = vol;   /* a copy */
  ... use vol2 ...
  ```
  The copy would be coalesced by cse/regmove → no extra instruction, but does it create a "2nd set" in the scheduler's view? The copy `vol2 = vol` is a MOVE (regmove) — gcc's regmove pass coalesces it, and the scheduler may or may not keep it as a separate set. Hmm, in the earlier G14 findings: "launder,pin | func_8017F584 | MATCH — field post-decrement per arm" and "launder | func_801A31CC | MATCH — pointer reuse". The "2nd set" trick was `pv = *p; pv &= mask` (2 real sets).

- A 2nd set that costs 0 instructions: e.g. `vol = (s16)vol;` costs 2 (sign extend). `vol = (u16)vol;` costs 1 (andi). `vol = vol & 0xFFFF;` costs 1.

Hmm what about `vol = (u16)(u16)vol;`? Still 1 andi.

What about a 2nd set via a "no-op" that gcc keeps as a copy: e.g. `vol = vol;` → the pseudo is the same → cse removes.

What about `vol += 0;` → combine folds.

What about making the 2nd set on a value that's already in a register: e.g. `vol = av;`? No, that changes the value.

Hmm. What about the ORDER of the source statements instead of a 2nd set? Recall the plain body has the pan multiply first. What if the source has the pan chain FIRST (panfirst)? From the u_ sweep, the panfirst variants all scored badly (33+). Hmm, but that sweep had the u16 cast everywhere. Let me test the plain (no cast) with panfirst! That might fix the multiply order by itself.

Wait, actually: the u_ sweep with panfirst + aftervol + nest = 33. Hmm, that's with the cast. Let me test plain+panfirst (no cast at all).

Let me generate a "v2" family: no u16 cast (plain) × statement order (volfirst/panfirst) × or-form (left/nest) × shift placement. And also: the launder replaced by the do-while × statement order.

Actually, let me think about the multiply order mechanism once more. In the plain body:
```
c6c: subu v1,v1,v0
c70: mfhi a3         <- the pan multiply's mfhi? 
c74: sll v1,v0,0x7
c78: subu v1,v1,v0
c7c: mult v1,a2      <- the PAN multiply with the magic in a2
c80: sra a0,a0,0x1f
c84: sra v0,a3,0x3
c88: subu a3,v0,a0   <- a3 = the pan value
c8c: sra v1,v1,0x1f
c90: mfhi t1         <- the vol multiply's mfhi
c94: sra v0,t1,0x6
c98: subu a1,v0,v1   <- a1 = vol
```
So in the plain body: the pan multiply (mult v1,a2) comes first with the magic in a2, and the vol multiply (mult v0,a0?) comes later with the magic in a0. Both magics exist (2 registers).

The target has ONE magic (a0) used by both multiplies, vol first.

So the difference is the *scheduling* of the two division chains. sched1 hoisted the pan chain above the vol chain.

Hmm, the launder asm prevented that. The u16 cast also prevented it (by giving vol a second set/longer live range).

What else could prevent it? The retail source must have had something. What if the retail source's vol expression was written so that its chain is *longer* or has a different shape?

Hmm, what if the retail source computed vol as:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
vs ours — same.

What if the retail source's av was computed differently, e.g. `av = abs(sx)`? Hmm! The target has:
```
c44: sll v0,v1,0x10
c48: sra a2,v0,0x10    ; sx = (s16)sxy[0]
c4c: bgez a2,c58
c50: move a1,a2        ; av = sx
c54: negu a1,a2        ; av = -sx
```
So av = |sx| computed with a branch (not abs). Same as ours.

OK here's another thought: maybe the retail source's *statement order* was different: the pan chain FIRST and the vol chain after. Then the scheduler might keep the vol chain first?? Hmm, that seems backwards, but the scheduler's choice might be driven by the "birth" of the magic constant.

Hmm, let me look at the target's order again:
```
c58: lui a0,0x6666      <- the magic is BORN here
c5c: ori a0,a0,0x6667
c60: li v0,160
c64: subu v0,v0,a1      <- 0xA0 - av
c68: sll v1,v0,0x7
c6c: subu v1,v1,v0      <- *0x7F
c70: mult v1,a0         <- the vol multiply
c74: mfhi t1
c78: addiu v0,a2,160    <- the pan chain starts
c7c: nop
c80: mult v0,a0         <- the pan multiply (reusing a0)
```
So the vol chain is entirely first, then the pan chain. This is exactly the source order (vol computed first, then the pan chain). So the scheduler did NOT reorder here — the source order was preserved.

In the plain body, the scheduler hoisted the pan chain's multiply. Hmm, the pan chain in the plain body:
```
c70: mfhi a3     <- ?
```
Let me get the full plain body listing to see the order. From the earlier dump:
```
c68: li v0,160
c6c: subu v0,v0,a1
c70: mfhi a3          <- ?
c74: sll v1,v0,0x7
c78: subu v1,v1,v0
c7c: mult v1,a2       <- the pan multiply
c80: sra a0,a0,0x1f
c84: sra v0,a3,0x3
c88: subu a3,v0,a0
c8c: sra v1,v1,0x1f
c90: mfhi t1
c94: sra v0,t1,0x6
c98: subu a1,v0,v1
```
Hmm, the plain body's earlier part (before c68) I haven't seen. The magic (lui/ori) is somewhere before. Let me dump the plain body's full region from c40.

Anyway: in the plain body, the pan chain comes first (the pan multiply at c7c) and the vol chain second (mfhi t1 at c90). So the two chains are SWAPPED relative to the source order.

The launder asm (in orig.c) sits between the vol computation and the pan chain — and it's a scheduling barrier that keeps the order.

So the question: what plain-C construct keeps the vol chain before the pan chain without adding an instruction?

Options:
1. A statement-order swap: put the pan chain FIRST in the source and the vol chain second. Then the scheduler might keep the vol chain first? Unlikely but cheap to test.
2. A 2nd set on vol that costs 0 instructions.
3. Something that lengthens the vol chain's live range.

Hmm, what about the DIVISION? Both divisions use the same magic. In the target, the magic is in a0 and used twice (both multiplies). In the plain body, two magics.

What if the source wrote the two divisions in a way that shares the constant expression? E.g. a macro or a common subexpression:
```
#define MAGIC 0x66666667
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
```
Both are divisions by a constant → the same magic. gcc computes the magic once per division expression (cse merges them if the values are the same). In the target, one magic in a0 used twice — so they WERE merged (cse) and the register allocator kept one register. In the plain body, they're in a0 and a2 — not merged?! That's odd; cse should merge the same constant.

Hmm, unless in the plain body, the magic is computed twice because the scheduler split it (the "birth boost" duplicates a constant). The moves.md mentions "sched1-birth-boost" and "sched1-split-const-hoist".

OK. Let me try a batch of "no-extra-instruction" ideas:

Idea A: statement order swap (pan chain first, vol chain after) with no launder at all.
Idea B: `vol = (s16)vol;` is 2 instructions - no.
Idea C: the vol chain with an explicit temp that is used later:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
{ s32 v2 = vol; vol = v2; }   /* no-op, cse removes */
```
no.

Idea D: Make the vol chain's result used twice? No.

Idea E: What if the u16 cast is applied to the ARG but the arg's mask is written so that the andi lands in the jal delay slot? We saw "aftershift+nest" gives the right everything but an extra dead andi at cb4. That extra andi is the u16 cast. What if the u16 cast is applied to a variable that is NOT part of the arg chain? E.g. apply the 2nd set to `sx` (the pan value):

```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = (u16)sx;      /* 2nd set on sx */
sx = sx << 8;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
Hmm, (u16)sx: sx = (sx+0xA0)/0x14 which for the reachable range is 0..15, so (u16) is a no-op value-wise. The andi would be on sx's register (a2). Would that andi land in the delay slot (the bne's)? Possibly! And would it fix the multiply order? The 2nd set is on sx (the pan chain), not vol. The mechanism for the multiply order was the vol 2nd set. Hmm, but maybe the mechanism is different: maybe any 2nd set that lengthens a chain's live range changes the balance.

Let me just try a bunch:
 - the cast on sx (u16/s16)
 - the cast on av
 - the cast on vol but with the shift in the arg, etc.

Let me be systematic and generate a new family "v2":
parameters:
 - CASTON: "vol" | "sx" | "av" | "none"
 - CASTTYPE: "u16" | "s16"
 - CASTPOS: for vol: aftervol/aftershift/beforecall; for sx: after the pan chain / after the shift
 - ORFORM: left/nest
 - ORDER: volfirst/panfirst
 - SHIFT: stmt/arg

That's too many. Let me do it in stages: first, a small family around the "aftershift+nest" structure (which has everything right except the extra dead andi) and try to eliminate that andi.

The "aftershift+nest" structure:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            vol = (u16)vol;                       <- the extra andi
            func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
The extra andi at cb4 = vol & 0xFFFF (dead, since the final mask covers it). Why didn't gcc eliminate it? Because the final mask is on the whole expression, and gcc's simplification (fold (x & C) | y → ... hmm) doesn't know that (vol&0xFFFF)|0x3000|sx & 0xFFFF = vol|0x3000|sx & 0xFFFF. It would need to push the mask through the OR: (a&0xFFFF)|b = (a|b)&0xFFFF only if b's bits are within the mask... So gcc can't remove it.

In the "left" form, gcc's reassociation produced vol|(0x3000|pan) and then the final mask → the early vol&0xFFFF became redundant? Hmm, in the "left" form the andi vanished entirely. Hmm, why?

Whatever. Let me try to find a form where the u16 cast's andi is either absorbed or harmless.

Alternatively: use a 2nd-set spelling with NO instruction. Let me think harder about what "2nd set" means for the scheduler. In gcc, the scheduler works on the RTL: the vol pseudo is set by the div chain and then used by the or-chain. With the u16 cast, the vol pseudo is set twice: once by the div, once by the andi. The second set extends vol's live range, and the andi depends on the div chain → the andi can't be hoisted above the div.

Without the 2nd set, vol's live range ends at the or-chain, so the scheduler can move the or-chain (and the whole pan chain?) earlier. Hmm, actually the pan chain is independent of vol. The scheduler (sched1) reorders independent instructions freely. The pan chain's multiply got hoisted above the vol chain's multiply — that's just scheduling freedom.

With the u16 cast, the vol pseudo has 2 sets, and the *second* set (the andi) must come after the first. The scheduler's "birth boost" gives a high priority to the instruction that sets a pseudo for the first time (to avoid the register being live longer)... hmm.

So the "2nd set" prevents the pan multiply from being hoisted above the vol multiply? That seems arbitrary. But empirically the u16 cast does it.

Hmm, so what else creates a 2nd set with no extra instruction?

What about `vol = vol;`? cse would fold it, but maybe not: cse's "make_regs_eqv" merges the copy. Hmm.

What about the "do { } while (0);" (the do-while lever)? It scored 25 — it doesn't fix the multiply order.

What about an empty statement between? No.

Hmm, what about giving vol a 2nd set via a *pointer* read? No.

What about: `vol = (u16)vol;` but where the andi is ABSORBED by the final mask. To get absorption, the value must be masked in a way gcc can fold. E.g.:

```
vol = (u16)vol;
...
func_8002D4C8(0x9E5, ((vol | 0x3000 | sx)) & 0xFFFF);
```
That's the "left" form which absorbed it but reassociated the chain.

What about the "nest" form with an explicit mask on the whole:
```
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
The "nest" form's andi wasn't absorbed.

Hmm, what if the reassociation is the issue and I can prevent it? gcc's reassoc might be triggered by the mask distribution. Let me try `(vol | 0x3000) | sx` with explicit parens (should be identical to the flat left form) and `(vol | (0x3000 | sx))` (nest).

Hmm, what about `sx | (vol | 0x3000)`? That would be (sx|(vol|0x3000)) → the emitted order would be ori(vol|0x3000) then or with sx ✓ — matching the target's chain order! And gcc's reassoc might not reorder it.

Hmm, but the "left" form got reassociated to vol|(0x3000|pan)...

Honestly, let me just try a bunch of or-forms:
 - (vol | 0x3000) | sx
 - sx | (vol | 0x3000)
 - (vol | 0x3000) | sx  (same as left)
 - vol | (0x3000 | sx)  (nest)
 - (0x3000 | vol) | sx
 - sx | 0x3000 | vol

and the cast position variants. Let me generate ~30 variants around the aftershift structure.

Actually — hold on. Let me reconsider the whole thing. Maybe there's a cleaner way to think: the target's RTL is what it is; I need a C that produces it. The target's key features:
(a) the vol chain entirely before the pan chain (source order preserved),
(b) one magic in a0 shared by both multiplies,
(c) the sll duplicated (delay slot),
(d) one andi (the final mask) in the jal's delay slot,
(e) vol→a1, pan→a2.

The plain body has (c), and (e)? no (the plain body has vol→a1? let me check: the plain body's `subu a1,v0,v1` at c98 → a1 = vol ✓ and the pan value in a3 ✗ (target a2)).

Hmm, the plain body: pan→a3, vol→a1. The target: pan→a2, vol→a1. So even the plain body's registers differ.

The u16 body (q1): vol→a1 ✓, pan→a2 ✓, the or-chain ✓, the jal delay mask ✓, but the extra andi in the bne delay slot (and the branch to cb0 instead of cb4).

So q1 is ONE structural thing away: the delay slot. And the "aftershift+nest" variant is also one thing away: an extra dead andi at cb4.

Hmm! What about combining: q1 (aftervol+nest) but with the u16 cast applied to sx instead of vol? Then the extra andi would be on sx (a2)...

Let me think about the "aftershift+nest" variant (13): it has the extra dead andi at cb4 (right after the branch). What if the u16 cast is on vol but the arg is `(vol | 0x3000 | sx)` — no, that's the "left" form (reassociation).

Hmm, what if the u16 cast is applied to vol and the argument is written as `(vol | (0x3000 | sx)) & 0xFFFF` (nest) and the cast is placed... The difference between aftervol (2) and aftershift (13) is where the cast is. In aftervol, the andi lands in the bne's delay slot (which is the wrong place but the instruction count matches 192). In aftershift, the andi lands at cb4 (an extra instruction → 193? no, the aftershift+nest has 193 ins: "mine 193 ins"). Yes, aftershift+nest = 193.

So:
- aftervol+nest = 192 ins, the andi in the bne delay slot (2 wrong insns: the delay slot content and the branch target).
- aftershift+nest = 193 ins, the andi at cb4 (an extra instruction).

Both have the extra andi (from the u16 cast).

The target has NO extra andi. So the u16 cast is not the right 2nd-set spelling! The right spelling creates a 2nd set WITHOUT an andi.

Hmm, so what if the 2nd set is a no-op copy that gcc keeps? Like `vol = vol;`? Let me test that — it's cheap. gcc's cse might fold it, but the *scheduler* sees the RTL: `vol = vol` would be optimized away by combine/cse before scheduling. Hmm.

But WAIT. What about the do-while? `do { } while (0);` — the do-while in gcc 2.7 creates a real basic block (with a branch), so it acts as a barrier for the scheduler. It scored 25 though: the multiply order was still wrong.

Hmm, why doesn't the do-while fix the order? Because the barrier is AFTER the vol computation (the do-while is where the launder was). sched1's reordering happens within a block; the do-while splits the block, so the vol chain and the pan chain are in different blocks → the pan chain can't be hoisted above the vol chain... but the multiply order was still wrong. Hmm, from the do-while diff:
```
124  --  | mfhi t1
125  --  | addiu v0,a2,160
126  --  | nop
127  --  | mult v0,a0
125  mfhi t0 | sra a0,t1,0x6
```
So in the target, the pan's `addiu v0,a2,160` + `mult v0,a0` come at 125-127, and in the do-while body they're at 128-129. And the do-while body has `mfhi t0` at 125 where the target has `mfhi t1` at 124. So the ORDER of the vol/pan chains is roughly right in the do-while body? The diff is a "replace mine[124:128] target[124:128]" — so the target has [mfhi t1, addiu, nop, mult] and mine has [mfhi t0, sra v0,t0,0x6, subu a1,v0,v1, addiu] hmm.

So in the do-while body, the order is: mult v1,a0 (vol) ... mfhi t0, sra, subu a1 (vol) then addiu v0,a2,160, mult v0,a0 (pan). Hmm, that looks like the vol chain first! But the register is t0 vs t1 and the diff continues.

The do-while body scored 25 with 191 instructions, so there's more than just the order.

Let me dump the do-while body's region to see. Actually, from the earlier diff:
```
  replace mine[63:64] target[63:64]
       63  j	d6c | j	d70
```
The `j d6c` vs `j d70` — the branch target differs (d6c vs d70): the target's epilogue is at d70 and mine's at d6c — a 4-byte (1 instruction) difference in the function's tail layout. So the do-while body has one fewer instruction somewhere in the tail.

OK, the do-while body is 191 ins and the target 192.

Let me now try a focused approach: find a 2nd-set spelling with 0 extra instructions. Candidates:
1. `vol = vol;` — probably folded.
2. `vol = (s32)(u16)vol;` — 1 andi.
3. `vol = vol + 0;` — folded.
4. `vol = vol * 1;` — folded.
5. `vol |= 0;` — folded.
6. `vol = (vol & 0xFFFF);` — 1 andi.
7. `vol = (u16)vol;` — 1 andi.
8. `vol = (s16)vol;` — 2 insns.
9. `vol = (u8)vol;` — 1 andi (0xff).
10. `if (vol) ; else ;` — no.
11. `vol = vol;` inside an if.

Hmm, all the "real 2nd set" spellings cost an instruction. And the target has 192 = 191 + 1 (the sll duplication). So the target's body = the plain body + the sll duplication. If the plain body has 191 instructions and the sll duplication adds 1 → 192 ✓. And the plain body's problem was the multiply order.

So the target's body = plain + a 2nd set that costs 0 instructions and fixes the order! Because the target's 192 = 191 (plain) + 1 (the sll copy).

Wait, is that right? The plain body is 191 and has 1 sll. The target has 2 sll's. So the target = plain + 1 sll. And the plain body's other difference from the target is the multiply order and the registers.

So the retail source had a 2nd set of vol that costs 0 instructions! What could that be?!

OH WAIT. Maybe the retail source's 2nd set wasn't on vol at all. Maybe the retail source's *statement order* was different, or the retail source computed vol in a way that the scheduler kept the order.

Hmm, hold on! Let me reconsider: maybe the retail source had NO 2nd set and the scheduler just happened to keep the order because of some other difference. What if the retail source's `av` was computed differently — e.g., using a different expression for |sx| that the scheduler handles differently?

Or what if the retail source's division was written as `(0xA0 - av) * 0x7F / 0xA0` vs `((0xA0 - av) * 0x7F) / 0xA0`? Same.

Hmm, what if the retail source's `sx` (the pan) was computed from a DIFFERENT variable, e.g. `sx = (L.sxy[0] + 0xA0) / 0x14;` (without the (s16) cast)? The target has `sll v0,v1,0x10; sra a2,v0,0x10` = the (s16) cast of L.sxy[0] → a2 = sx. Then `addiu v0,a2,160` = sx+0xA0 ✓.

What if the retail source used the same variable for both the (s16) cast and the division? Ours does.

Hmm, let me look at the plain body vs the target more comprehensively — maybe the plain body's difference is not just the order. Let me get the full diff of r_plain_s0 (39) — I saw it earlier:

```
  delete  mine[123:124] target[121:121]
      123  mfhi a3  | --
  replace mine[126:130] target[123:128]
      126  mult v1,a2 | mult v1,a0
      127  sra a0,a0,0x1f | mfhi t1
      128  sra v0,a3,0x3 | addiu v0,a2,160
      129  subu a3,v0,a0 | nop
      130  -- | mult v0,a0
  replace mine[131:134] target[129:135]
      131  mfhi t1 | sra a0,t1,0x6
      132  sra v0,t1,0x6 | subu a1,a0,v1
      133  subu a1,v0,v1 | --
      134  -- | sra v0,v0,0x1f
      135  -- | mfhi a2
      136  -- | sra v1,a2,0x3
      137  -- | subu a2,v1,v0
  replace mine[135:139] target[136:140]
      135  bne a3,v0,cb0 | bne a2,v0,cb4
      136  sll a3,a3,0x8 | sll a2,a2,0x8
      137  li a3,15 | li a2,15
      138  sll a3,a3,0x8 | sll a2,a2,0x8
  replace mine[141:142] target[142:143]
      141  or a1,a1,a3 | or a1,a1,a2
```
So in the plain body: the pan chain comes first (mfhi a3 at 123 = the pan's mfhi, mult v1,a2 at 126 = the pan multiply), and the vol chain second (mfhi t1 at 131, subu a1 = vol). Plus the pan value in a3 (target a2) and vol in a1 ✓.

So the plain body already has vol→a1 ✓ and the or-chain `or a1,a1,a3` (base a1 = vol ✓) — the chain ORDER is right! Only the pan value's register (a3 vs a2) and the multiply order differ.

So if I fix the multiply order in the plain body, the register allocation might follow.

So the goal: keep the plain body (no u16 cast) but make sched1 keep the vol chain before the pan chain.

What controls that? sched1 is the pre-RA scheduler. The pan chain: `sx = (sx + 0xA0) / 0x14` = a division by 0x14 → the magic 0x66666667, and the vol chain: a division by 0xA0 → the SAME magic 0x66666667!

In the target, the magic is materialized ONCE (a0) and used by both multiplies. In the plain body, TWO magics (a0 and a2) — so cse did NOT merge them (or the scheduler duplicated them).

Why would cse not merge them? Because the magic's live range is short and the scheduler's birth-boost duplicated it. Hmm, but cse runs before sched1 and would merge the two identical constants into one pseudo... unless cse's "birth" logic keeps both (cse has a heuristic: if a pseudo is used in a different block, it may not merge).

The two divisions are in the same block. Hmm.

OK, so what makes the target have ONE magic? Because the two multiplies are ADJACENT-ish in the scheduled order (vol's mult at c70 and the pan's mult at c80) and the magic's live range spans both. And in the plain body, the two magics are far apart (the pan's mult at 126, the vol's mult at ~130) so the scheduler duplicated the constant (the "sched1-birth-boost" mechanism: the constant's live range would be too long, so it's split).

So the ORDER of the chains determines whether the magic is shared or duplicated. Circular.

Let me try the simplest thing: swap the source order (pan chain first, vol chain after) with NO lever. Maybe then the vol chain (which would be second in the source) gets scheduled first?! Unlikely, but cheap.

Also try: make the pan chain's division use a different expression so the magic is a separate pseudo (e.g. write the pan division as a multiplication by a reciprocal? no, that changes the code).

Alternatively: the ORDER of the two divisions in the source. Let me test:
 v2a: pan chain first, vol chain after, no lever.
 v2b: vol chain first (current), no lever (= r_plain_s0, 39).
 v2c: vol chain first, but the pan chain's division written to use a variable (e.g. `t = sx + 0xA0; sx = t / 0x14;`).
 v2d: vol chain first with the magic shared explicitly: compute the magic once? Can't in C.

Hmm, what about making the two divisions share an explicit temp? Like:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
```
The magic 0x66666667 is used by both. gcc's cse should merge them into one pseudo (same value, same block). Then the register allocator gives it one register. The plain body has two magics — so cse did NOT merge. Why? Because cse's "birth" rule: a pseudo defined in one place and used in another; if the uses are far apart in the instruction stream, cse might still merge them but the *scheduler* then splits the constant (the "split-const-hoist" mechanism in moves.md!).

moves.md: "pin | func_800CF290 | WALL sched1-split-const-hoist — large-const split lui (dest set twice: no birthing boost) floats to top".

Hmm. And: "launder,pin | func_8001BBBC | WALL sched1-birth-boost — cse folds two-step 0xFFFFFF mask (split lui/ori consecutive LUIDs, li 4 can't sit between)".

OK. Let me try a different tack — what if the ORDER of the two divisions in the source is what makes the difference, and the u16 cast's real effect was just to change the order? Let me test the plain body with the source order swapped (pan first). It's cheap.

Let me generate a "v2" family:
 - ORDER: volfirst / panfirst
 - LEVER: none / dow / u16cast
 - ORFORM: left / nest
That's 12. Plus the shift stmt/arg. Let me do 24.

Let me write gen_v2.py. I'll reuse the structure. Actually, let me write a more flexible generator with a mini-DSL so I can iterate fast.

Let me write it.
