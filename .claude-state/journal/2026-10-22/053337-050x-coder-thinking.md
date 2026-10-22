---
ts: 2026-10-22T11:33:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ZMhmOd3EwGmLm9b889v9
---
The ORIGINAL matches the target exactly. So in the original, the constant is born at 198 (top of the join block) in a0.

So the question: **how does the launder cause the constant to be born at the top of the join block (in a0) rather than just before its first use?**

Hmm. Interesting: in the original, the `vol` computation is `vol = ((0xA0 - av) * 0x7F) / 0xA0;` — a single expression with TWO multiplies: `*0x7F` (sll) and the division's magic multiply. And the sx chain: `sx = (sx + 0xA0) / 0x14` — one magic multiply.

So the constant 0x66666667 is used by TWO multiplies: one in the vol chain, one in the sx chain.

Now, the launder is between them. With the launder, the vol chain's result `vol` is set by the asm → the asm is a barrier between the chains. So the PAN chain (sx) can't be hoisted above the VOL chain.

But WHY does the constant get born at the top?

**HYPOTHESIS**: The constant's birth (lui/ori) is placed by GCC's "split constant" logic (in `split_constant` / `reload`) at the point where the constant is FIRST needed in the RTL... and then the SCHEDULER moves it. In the target, it's at the top.

Hmm, alternatively: **the launder's asm makes `vol` have 2 sets → `reg_n_sets[vol] == 2` → the "birthing boost" is killed for something.**

Hmm, let me think about which pseudo is involved. The constant 0x66666667 is a pseudo (reg) with 1 set (the lui/ori pair). Its 2 uses are the two mults. In sched1's priority, a 2-use pseudo's definition has fanout 2 → high priority → scheduled EARLY.

In the candidate w4, the constant is scheduled LATE (right before the first mult). So the fanout-based priority didn't apply. Hmm, maybe because the constant is a HARD REG (v0 in w4? no, `lui v0,0x6666` — v0 is a hard reg!).

Hmm! In the candidate, the constant is materialized directly into v0 (a hard reg). In the target, it's in a0 (also a hard reg). So both are hard regs.

The difference is the POSITION.

OK, so what's different in the RTL? Let's think about "reload": GCC's reload pass assigns the constant to a register and creates the lui/ori. The reload pass runs AFTER scheduling (in GCC 2.7, reload runs after sched1 and before local-alloc/global-alloc). Hmm, actually in GCC 2.7: `pass_reload` runs after `pass_sched`? The order: expand → sched → reload → local-alloc → global-alloc.

Hmm! If reload creates the lui/ori, then its position is determined by reload, not sched1.

Hmm, but reload inserts the constant materialization where the pseudo is set. If the pseudo is a pseudo reg (not a hard reg), reload creates the lui/ori at the pseudo's definition point.

OK, I think I should stop theorizing and just try things. The difference is quite localized: the constant's birth position.

**IDEA**: what if we give the constant's pseudo a SECOND set in plain C? E.g. by making the two chains use a variable that is set twice? Hmm, the constant is a compiler-generated literal.

**IDEA 2**: What if we express the divisions differently so the constant is shared explicitly? E.g., compute the magic constant ourselves? We can't add instructions.

**IDEA 3**: The real question: WHY does the candidate's constant get born late? Because in the candidate, the two chains are... hmm, in w4 the VOL chain comes first (matching), and the constant is born before the VOL chain's mult.

WAIT. Actually, look again at the candidate:
```
198: li v0,160
199: subu v0,v0,a1      (0xA0 - av)
200: sll v1,v0,0x7
201: subu a1,v1,v0      (*0x7F)
202: lui v0,0x6666
203: ori v0,v0,0x6667
204: mult a1,v0
```
So the constant is born right before its use. Whereas the target has it 4 instructions earlier.

So the target's constant is HOISTED. This is GCC's "constant hoisting" — `combine`/`reload` hoists a constant that's used multiple times to the earliest point? Hmm, GCC doesn't hoist constants across blocks.

Hmm, but hold on: in the target, the constant is born at the top of the JOIN block. Both chains are in the join block. So it's the earliest possible point within the block.

**IDEA**: What if in the candidate, the two chains are NOT both in the join block? In w4, `vol` is computed with the compound division `vol = vol / 0xA0` — all in the join block. Hmm.

**IDEA 4**: What if the difference is that in the original, the `vol` chain and the `sx` chain are SEPARATE basic blocks (because of the launder's asm), and the constant is born in the FIRST block (the vol chain's block) — hmm, but it's at the top of the join.

Hmm, actually! With the launder, the asm splits the block: block1 = [sx calc, av calc, vol chain], block2 = [asm, sx chain]. Then the constant (used in both blocks) would be born in block1 — at the top of block1? The join block starts at 198 (lui). Then the vol chain. So block1 = [lui, ori, li v0,160, subu, sll, subu, mult, mfhi, ...]. And block2 = [asm(nop), addiu v0,a2,160, nop, mult, ...].

But in the CANDIDATE w4 (no asm), the whole thing is ONE block: [li v0,160, subu, sll, subu, lui, ori, mult, mfhi, addiu, nop, mult, ...]. And the constant is born just before its first use.

So in the original (with the asm = 2 blocks), the constant is hoisted to the top of block1; in the candidate (1 block), it's born just before its use.

**WHY?** Because in a 1-block case, the constant's pseudo is defined by the lui/ori which reload inserts... hmm, but reload would put it at the definition point regardless.

Hmm, unless: the constant's pseudo is defined ONCE in the RTL (as a pseudo reg set by lui/ori) and its position in the block is decided by sched1. In the original, sched1 placed it first; in the candidate, later.

What could change sched1's placement? The presence of the asm between the chains! With the asm, the constant's definition must be in block1 (before the asm) because it's used in block2. sched1 (which schedules per block) would place the constant's definition at the top of block1 to satisfy... hmm, actually it must be before the asm anyway.

Without the asm, the constant's definition is in the same block as both uses, and sched1 places it... later.

Hmm, why would sched1 place it later in a 1-block case? Because of the priority: the constant's def has fanout 2 → should be early.

Hmm, unless in the 1-block case the constant is NOT a separate pseudo but is duplicated... no, only one lui/ori.

OK, ANOTHER THOUGHT: maybe in the 1-block case, the constant's pseudo is defined by a `set` that got COALESCED with something. Hmm.

**PRACTICAL IDEA**: Make the two chains be in TWO blocks in plain C — i.e., create a block boundary between the vol chain and the sx chain, WITHOUT an asm. That's exactly what the launder does!

What plain-C construct creates a block boundary that survives to scheduling?

We tested goto/switch/do-while for item 2 and they didn't survive. BUT maybe for item 4 the situation is different — hmm, same compiler.

Hmm, hold on. Actually the asm doesn't create a CFG block in the RTL — earlier for item 2 I saw the orig's block was ONE block (232-248) containing the load, asm, and the call. So the asm does NOT create a block boundary in the RTL!

But in item 4, the asm between the chains... does it create a block? Let me check the orig's RTL block structure. Hmm.

OK OK. Let me think about it completely differently:

**What if the fix is to give `vol` a second set in plain C?** The successful cracks in moves.md used exactly that: "launder->real 2nd set". For example: `pv = *p; pv &= mask split (real 2nd set)`.

Here, `vol` would need a second set. In plain C: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` gives vol 1 set. If we write:
```c
vol = (0xA0 - av) * 0x7F;
vol = vol / 0xA0;      /* compound → vol has 2 sets! */
```
That's w5 (score 25) — because `vol = 0xA0 - av; vol *= 0x7F; vol /= 0xA0;` gives 3 sets. But w1/w4 use `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` → 2 sets of vol → score 14.

So the 2nd set of vol gives 14 (VOL chain first, exact count). The remaining residual is the constant's birth.

Hmm, so what does the launder give beyond the 2nd set? The launder's asm ALSO sets vol (3rd set effectively? or the asm's set). Hmm.

In the ORIGINAL, `vol` has: set 1 = the division result, set 2 = the asm output. So 2 sets (same count as w4!). Hmm, but w4 has `vol` set twice too (the multiply result and the division result).

Wait: in w4, `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` → vol is set twice. In the orig: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` → vol set once, then the asm sets it → 2 sets.

So both have 2 sets. Yet the constant's position differs.

**AH WAIT!** Maybe the difference is the ORDER of the sets! In w4, vol's sets are: (1) the *0x7F product, (2) the division result. The division result is the FINAL value used in the OR expression. In the orig, vol's sets are: (1) the division result, (2) the asm's copy.

So in the orig, the "real" division result is set FIRST and then re-set by the asm. So the value used later is the asm's copy, whose definition is the asm. The asm comes AFTER the division. So the division result is DEAD (only the asm's copy is live).

**AH HA! That's the key!** In the orig:
- vol = division result (set 1)
- asm sets vol = vol (set 2) — the asm's output is what's used.

So the division result is dead after the asm. The asm is a barrier. The PAN chain (sx) comes after the asm.

In w4:
- vol = product (set 1)
- vol = division result (set 2) — used later.

Different.

Hmm, but both give the VOL chain first and the same instruction sequence except the constant's position.

OK, let me try to think about what makes the constant's birth position differ, empirically. Let me try a bunch of variants for item 4:

g01: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` (w4 = 14)
g02: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` (w1 = 14)
g03: `vol = ((0xA0 - av) * 0x7F) / 0xA0; vol = vol;` (self copy → 3rd set?)
g04: `vol = ((0xA0 - av) * 0x7F) / 0xA0; vol = vol + 0;`
g05: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then use `vol` twice? no.
g06: put the sx chain BEFORE the vol chain but with the compound division → w8 = 33.
g07: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0; sx = (sx + 0xA0) / 0x14;` (w4)
g08: same but `sx` chain first then vol chain with compound → w7 = 33.

Hmm. The key: the constant must be born at the TOP of the join block.

**IDEA**: What if the constant is used by an EARLIER chain? I.e., if the PAN chain (sx) came first, the constant would be born before the PAN chain → but the PAN chain must come after in the target.

**IDEA**: What if we could make GCC hoist the constant explicitly? E.g., write the constant as a variable:
```c
s32 magic = 0x66666667;   /* local */
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
No, that doesn't control the division's magic.

**IDEA**: Write the division manually so the constant is a named local used twice:
```c
s32 m = 0x66666667;
```
That would produce a lui/ori for m... but the division expansion already uses its own constant. If we write `m` and the compiler uses it for both multiplies, maybe. But the magic multiply pattern (mult + mfhi + sra + subu) is only generated by the division expansion. Writing it manually would produce different code.

Hmm.

**IDEA**: What if we use a `static const`? Hmm.

OK, let's approach empirically: the constant's birth position is a SCHEDULER decision (or reload). Let's find what makes it early.

The constant's pseudo has 2 uses. In the original, the constant's set is in the SAME block as its first use. Hmm.

Let me look at the RTL dumps for the original vs w4 around this area. That's the most direct way. Let me dump both and compare the pre-sched RTL.

Actually, hold on! Let me reconsider — maybe it's the RELOAD pass. In GCC 2.7, the reload pass decides where to materialize a constant. For a pseudo used in multiple places, reload might split it. And `reload`'s placement of the constant... hmm, reload runs after sched1 in GCC 2.7? Let's check: the dump order was sched, sched2, lreg, greg. There's no reload dump. In GCC 2.7 the order is: sched1 → reload → local-alloc → global-alloc → reload1 → ...

Hmm, in GCC 2.7 `pass_all_optimizations`:
```
  /* Scheduling.  */
  NEXT_PASS (pass_sched);
  /* Register allocation.  */
  NEXT_PASS (pass_local_alloc);
  NEXT_PASS (pass_global_alloc);
  ...
```
and reload happens in `pass_expand`? Hmm, in GCC 2.7 reload is split: `pass_reload` (in pass_all_early_optimizations? no).

OK. Let me just DUMP both and diff the RTL. That's the fastest way to see the difference.

Let me dump the orig and w4 candidate for item 4 and look at the region.

Actually — since the score is only 14 and the structure is IDENTICAL except for the constant's birth and the register allocation, maybe I should consider: is the register allocation (a0 vs v0 for the constant) a consequence of the birth position? Probably yes: if the constant is born at the top of the block (before the branch's other path), it might get a0 (a caller-saved reg available at the top).

Let me try the DUMP approach for item 4.

Hmm, time. Let me instead try a bunch of quick variants for item 4 — maybe some will hit.

Variants for the tail region:
h01: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` (w4, 14)
h02: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` (w1, 14)
h03: `vol = ((0xA0 - av) * 0x7F) / 0xA0; vol = vol;`
h04: `vol = ((0xA0 - av) * 0x7F) / 0xA0; vol = vol + 0;`
h05: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` + `sx = (sx + 0xA0) / 0x14;` — the plain version (30)
h06: with `sx` chain first and vol chain (compound) second → 33
h07: swap the order of the `if (sx<0)` block and the vol computation
h08: use `s32` vs `u32` for vol
h09: make the sx division a compound too: `sx = sx + 0xA0; sx = sx / 0x14;`
h10: `sx = (sx + 0xA0); sx /= 0x14;`
h11: use `av` differently.
h12: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` with the `sx` chain using a compound division.
h13: put the vol computation BEFORE the `if (sx < 0)` block? Not possible (needs av).
h14: Change `av`'s if to a different form: `av = sx < 0 ? -sx : sx;`

Also: the "0x66666667" constant — the divisions are /0xA0 and /0x14?? Wait, /0xA0 = /160 → magic 0x0A0A0A0A? Hmm. But the disassembly shows mult by 0x66666667 and `sra a0,t1,0x6` (>>6) and `sra v1,a2,0x3` (>>3) and `sra v0,v0,0x1f`. That's the signed division by 10 pattern: for /10, magic = 0x66666667, shift 3 (n = 3), and the "add" correction. Hmm: `mult v1,a0` then `mfhi t1` then `sra a0,t1,0x6` (>>6 = >>3 + >>3? no)...

Hmm, for division by 10: q = (mulhi(n, 0x66666667) >> 3) + ... Actually the standard: for d=10, magic m=0x66666667, shift s=3. q = mulhi(n,m) >> 3, then adjust. The code: `sra a0,t1,0x6` = t1 >> 6 = (t1>>3)>>3. Hmm.

Whatever — the point is that BOTH divisions (by 0xA0 and by 0x14) end up using the same magic 0x66666667?? That seems odd. Let me look: the first mult is `mult v1,a0` where v1 = (0xA0-av)*0x7F. Then mfhi t1, sra a0,t1,0x6, subu a1,a0,v1(with sra 0x1f). That's the /0xA0 division?? Hmm: /0xA0 = /160.

Hmm, whatever — maybe GCC's expansion for /0xA0 with a signed numerator uses a different magic and the `0x66666667` is for /10? Hmm, but the source says `/ 0xA0` and `/ 0x14`.

Hmm, hold on: the second chain: `addiu v0,a2,160` (sx+0xA0), then `mult v0,a0`, `sra v0,v0,0x1f`, `mfhi a2`, `sra v1,a2,0x3`, `subu a2,v1,v0`. That's the /0x14 division (shift 3? for /20 the magic is 0xCCCCCCCD with shift 2). Hmm, but it uses 0x66666667...

Hmm, 0x66666667 * n >> 32 gives n/10 roughly. Then `sra v1,a2,0x3` = >>3, `subu a2,v1,v0` where v0 = n>>31. That's the /10 pattern!

So the second chain is a division by 10?? But the source says `/ 0x14` = /20. Hmm, magic for /20: m = 0xCCCCCCCD, shift 2. For /10: m=0x66666667, shift 3.

Hmm, so the source's `/0x14` gives a /10-like expansion? That can't be.

Unless... GCC's division expansion for /20: since 20 = 4*5, GCC might transform x/20 into (x/5)/4 or use the magic for /10 then >>1. Indeed! GCC transforms division by 20 into division by 10 followed by a shift right by 1! Hmm, but where's the shift? `sra v1,a2,0x3` then `subu a2,v1,v0` gives q = (mulhi>>3) - (n>>31). Hmm, that's /10 exactly. Then... hmm, but for /20 we'd need >>1 more.

Hmm, whatever. Maybe the source's `/0x14` isn't what I think. Let me recheck: `sx = (sx + 0xA0) / 0x14;` — hmm. But maybe GCC turned `sx/0x14` where sx+0xA0... hmm, hold on: maybe GCC rewrote `/0x14` as `/0xA` then `/2`? The disasm has no shift.

Hmm, hold on: maybe I mis-assigned the chains. Let me re-read:
```
200: li v0,160
201: subu v0,v0,a1       ; v0 = 0xA0 - av
202: sll v1,v0,0x7       ; v1 = v0 * 128
203: subu v1,v1,v0       ; v1 = v1 - v0 = v0*127  (the *0x7F)
204: mult v1,a0          ; v1 = v1 * 0x66666667
205: mfhi t1
206: addiu v0,a2,160     ; v0 = sx + 0xA0
207: nop
208: mult v0,a0          ; v0 = v0 * 0x66666667
209: sra v1,v1,0x1f      ; sign of (v0*127)
210: sra a0,t1,0x6       ; t1 >> 6
211: subu a1,a0,v1       ; q1 = (t1>>6) - sign
212: sra v0,v0,0x1f      ; sign of (sx+0xA0)
213: mfhi a2
214: sra v1,a2,0x3       ; a2 >> 3
215: subu a2,v1,v0       ; q2 = (a2>>3) - sign
```

Hmm, for the vol chain: n = v0*127, and the division is n/0xA0 = n/160. The magic for /160: m = 0x0A0A0A0A? Hmm, but here m = 0x66666667 and the shift is 6. Hmm: for /160, GCC might use: n/160 = (n/10)/16. And n/10 uses magic 0x66666667 with shift 3. Then >>4. So (mulhi>>3)>>4 = mulhi>>7? Hmm, the code has `sra a0,t1,0x6` = t1>>6. Hmm, >>6 = >>3 >>3, so /10 then /8? That'd be /80. Hmm.

Hmm, whatever — GCC's exact expansion. Note `mult` produces a 64-bit result in hi:lo; `mfhi t1` gets the high 32 bits. Then `sra a0,t1,0x6`.

For the sx chain: n = sx+0xA0, divided by 0x14=20. GCC: n/20 = (n/10)>>1. The code: `mfhi a2; sra v1,a2,0x3; subu a2,v1,v0` = n/10, then where's the >>1? Hmm, `sra v1,a2,0x3` then `subu a2,v1,v0` — that's n/10. Then no >>1. Hmm.

Hmm, so maybe sx is divided by 10, not 20! Which would mean the source's `/0x14`... hmm. OH WAIT. Maybe the source in the CURRENT src is different from what's in the item's orig.c? No, orig.c = the current def.

Hmm, whatever. The important thing is the constant 0x66666667 is SHARED by both divisions. That means both are /10-ish.

Hmm, 0xA0 = 160 and 0x14 = 20. Hmm, 160/16 = 10 and 20/2 = 10. So GCC turned both into "divide by 10" plus shifts. But the shifts: for /160 = /10 /16 → needs >>4. The code has >>6 (>>3 then >>3). Hmm, >>6 = >>3 (for /10) then >>3. Hmm, /10 then /8 = /80. Hmm.

Hmm, maybe GCC's magic for /160 is different and I'm misreading which shift belongs to which. Let me not worry.

**IMPORTANT INSIGHT**: The two divisions SHARE the constant 0x66666667 in the target. In the candidate w4, they ALSO share it (one lui/ori). Good.

So the only difference is the birth position of the shared constant.

**Now, KEY IDEA**: what if the birth position is determined by the ORDER in which the RTL sees the two uses, and by the "block" structure? In the target, the constant's definition is at the top of the join block — that looks like the constant was HOISTED to the block's top.

In GCC's RTL, a constant used in a block is represented by a pseudo reg set by a `lui`/`ori` (or a single `li` if it fits). The position of that set within the block is determined by the scheduler.

The constant has 2 uses → the scheduler should place it EARLY (to shorten the live range? no, later is better for the live range... hmm).

Hmm, in sched1 the priority is by fanout: an insn with more dependents gets scheduled earlier. The constant's def has 2 dependents → high priority → early. But in w4 it's late.

Unless in w4 the constant's def has fanout 1 at sched time (i.e., only ONE use at that point) and the second use was created later (in reload/reload1). Interesting! If the two divisions' magic constants are separate pseudos at sched time and get merged later (in reload1 or combine), then the position would be that of the first one.

In the ORIGINAL, the launder splits the block into two, so the two constants live in different blocks and one must be materialized in the first block... hmm.

OK, ENOUGH. Let me get empirical with a batch of variants for item 4 and also dump the RTL.

Let me first dump the RTL for orig vs w4 for item 4, comparing the region. That's the fastest way to find the difference. The function is big (237 ins) but let me look at the relevant part.

Actually, let me be smart: let me check whether the constant's pseudo in the two versions is the same reg and where its set insn is in the RTL (pre-sched).

Let me dump both.
