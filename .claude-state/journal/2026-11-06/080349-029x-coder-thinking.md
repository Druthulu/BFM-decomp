---
ts: 2026-11-06T15:03:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ieIyUQl3Orh8IG4jwzlT
---
Target:
```
584 li v0,16
588 bne a2,v0,598
58c sll a2,a2,0x8        <- delay slot: sx = sx << 8 (in place, before the ==0x10 check?? no)
590 li a2,15
594 sll a2,a2,0x8
598 li a0,2715
59c ori a1,a1,0x3000
5a0 or a1,a1,a2
5a4 jal
5a8 andi a1,a1,0xffff
```

Interesting: the target does `sll a2,a2,8` in the branch delay slot (with the unclamped sx), then `li a2,15`, then `sll a2,a2,8` again for the clamped path. That's the reorg delay-slot steal the comment mentions: `sx = sx << 8;` in place so reorg can steal the shift into the bne delay slot (it's dead on fall-through because the fall-through overwrites a2 with 15).

Mine: the `andi a1,a1,0xffff` got moved into the delay slot at 58c, and `sll a2,a2,8` stayed at 594. So my extra andi changed which insn reorg steals into the delay slot. Target's delay slot is the sll (steal); mine's is the andi.

Hmm interesting — mine's andi is a *separate* insn after the `or`? No: mine at 58c andi a1,a1,0xffff is before the li a0,2715 — it's the `& 0xFFFF` that in target is at 5a8 after the jal. So mine's andi moved up (sched/reorg) to the delay slot, and it's placed... Actually mine's andi at 58c computes a1 masked (a1 = vol), before `ori a1,a1,0x3000`. The mask is redundant there? `(vol | (0x3000|sx)) & 0xFFFF` — if vol & 0xFFFF is computed then ori 0x3000, or sx... then the final & 0xFFFF still needed since sx<<8 can exceed 16 bits. So the outer andi remains at 5a8. So mine has an EXTRA andi (the one I added) at 58c, and the target's delay slot sll was displaced... but mine has only 237 insns too? Mine: count from 550 to 5d4: same addresses! Both end at 5d4. Mine at 58c andi, 590 li a2,15, 594 sll, 598 li a0... Target: 58c sll, 590 li a2,15, 594 sll, 598 li a0.

So mine replaced target's delay-slot sll (at 58c) with andi, and then mine has sll at 594. But target also has sll at 594! Wait target has sll at 58c AND sll at 594 (two shifts: delay-slot steal + the real one). Mine has only one sll (at 594) plus the extra andi at 58c. Same count. That's why the bne offset differs (target jumps to 598, mine to 594).

OK so a2's mask did NOT get folded into the outer andi; it became a real andi, and reorg stole it into the delay slot instead of the sll. Score 2.

I need a zero-insn second set. Options:
1. Split vol computation into two sets (a1) — score 14, bad (COUNT: probably the mult schedule changed).
2. Some other way to give vol a second set at zero cost: e.g. `vol = vol;`? Would fold delete? Let's test t5 (`vol = vol;` after split) — but that's after the split which already gave 2 sets. Test plain `vol = vol;` instead of the launder.
3. `vol |= 0;` → folded.
4. Use a compound assignment that folds to identity: `vol += 0;` → folded.
5. Assign through a union/bitfield? Hmm.
6. Reuse a variable: what about making the *pan* (sx) the variable with 2 sets instead? The birth boost is on the vol division (the one that got hoisted). Actually wait: the target order is: vol's mult/div (550-580) FIRST, then sx's addiu/mult/div (55c? no)... Let me look at the sequence: at 550-580 we have two mults interleaved:
- 554 mult v1,a0 ; 564 mult v0,a0 — two multiplies back-to-back.
- mfhi t1 (from first), mfhi a2 (from second).
So the two magic divisions are interleaved. The order: first is vol = ((0xA0-av)*0x7F)/0xA0? and second sx=(sx+0xA0)/0x14. The comment says sched1 hoisted the PAN multiply first. Target has the non-pan first.

With the launder (orig) it's correct. Without, sched1 boosts the vol division (birthing) and hoists it... hmm wait, the launder made vol have 2 sets, so no birth boost for vol's div → so what gets boosted? Hmm, the note says the launder *prevents* hoisting the PAN multiply first. Let's re-read: "Both magic-multiplies write the same match_scratch, so sched1 ... is free to swap them and always hoisted the PAN multiply first, inverting the whole tail schedule... Source statement order does NOT move it; only the re-tie does."

So without the launder, PAN multiply goes first. With it, PAN multiply second (target). The mechanism: the re-tie makes vol's div a non-birthing insn, so it doesn't get max_priority... wait, if vol's div is NOT boosted, then it has lower priority and PAN (boosted?) goes first. That contradicts.

Hmm. Let's think again: birth boost raises priority of the insn that births a value (dest live at bb start, reg_n_sets==1). Which value is live at block start? Both vol and sx? sx is set at `sx = (s16)*(u16*)&sxy;` earlier in the block. vol is set once. In the target, vol's division comes FIRST, PAN second. With the launder, vol's division is not a birth (2 sets) → no boost. Then... hmm, then PAN's division would be boosted (sx set once? sx is set multiple times: `sx = (s16)...`, `sx = (sx+0xA0)/0x14`, `sx = 0xF`, `sx = sx<<8` — many sets, so reg_n_sets>1, no boost). So neither boosted with the launder; order follows source: vol first. Without the launder: vol's div is birthing → boosted to max → goes first. But that would make vol first, which is the TARGET order... and the note says without launder PAN goes first.

I'm confusing which multiply is which. Let me map the disassembly:
- 550 subu v1,v1,v0
- 554 mult v1,a0      <- mult v1 by a0 (magic const)
- 558 mfhi t1
- 55c addiu v0,a2,160   <- 0xA0
- 560 nop
- 564 mult v0,a0
- 568 sra v1,v1,0x1f
- 56c sra a0,t1,0x6
- 570 subu a1,a0,v1     <- vol result in a1
- 574 sra v0,v0,0x1f
- 578 mfhi a2
- 57c sra v1,a2,0x3
- 580 subu a2,v1,v0     <- sx/0x14 result in a2

So 554's mult produces vol (a1), 564's produces pan (a2). vol's magic: `/0xA0` → mult by magic a0, shift >>6 (sra a0,t1,0x6). pan: `/0x14` → shift >>3. So vol mult (554) first, pan mult (564) second — target.

Without launder, sched1 hoists pan first. Why? Because pan's `addiu v0,a2,160` (55c) is a fresh value? Hmm, pan's computation is `(sx + 0xA0)/0x14` where sx is set earlier in the block, so sx is live at block start. The `addiu` is not birthing. Hmm.

Actually the birth boost: "Prefer scheduling insns which make registers live". The `mult` insns write match_scratch (hi/lo) which is a pseudo? The `birthing_insn_p` checks SET_DEST is REG. mult's pattern sets (reg:SI 32?) hmm match_scratch isn't a reg set. Actually `mult` RTL is `(set (match_scratch:SI 0) ...)`? Let me not go down this hole.

Empirical: the launder works. I need a zero-cost replacement giving the same effect. Options to try:

(a) `vol = vol;` (self-assignment). gcc might keep it as a set (reg_n_sets=2) and delete later? Actually cse would notice it's a no-op set and remove it. Test.
(b) Reuse: `vol` as an alias for the div result via compound assignment: `vol /= 0xA0;` — but then vol's set count: `vol = (0xA0-av)*0x7F` then `vol /= 0xA0` = 2 sets. This is t4 (same as t1 essentially). t1 scored 14.
   Why did t1 score 14? Maybe because the mult result now lands in vol's reg (a1) directly instead of a scratch, changing allocation. Let me look at t1's diff.
(c) Dead-reset after vol: `vol = 0;` then use? No, dead store deleted by flow.
(d) Reassign a *different* variable to vol's value? e.g. `t = vol;`? That's a copy, +insn.
(e) `vol &= 0x7F;`? vol range 0..0x7F; the andi would be folded by combine into the `|`/`&0xFFFF`? Probably a real andi.
(f) Make the vol division insn non-birthing by adding a second set to *the destination* in a way that's zero-insn: e.g. declare `vol` as `u16`? A u16 local: `vol = ((0xA0-av)*0x7F)/0xA0;` with u16 type — the set gets a SUBREG copy (cse can't fold), possibly changing codegen. Hmm, from C0505: "Widths: an s16/u16/u8 local for a value used narrow keeps a SUBREG copy". That could be zero-cost? It might add an andi.

(g) The classic: make the multiply itself not a birth by assigning the intermediate to vol twice via the *expression* split but keeping allocation: `vol = (0xA0 - av) * 0x7F / 0xA0;` — still one set (the whole expr). Splitting requires 2 sets.

Hmm wait. Maybe the birth boost is on a different pseudo. Let me actually check which insn moves without the launder. Generate a candidate = orig with launder simply deleted (t0) and look at the diff — that tells us exactly what changes and by how much.

Let me do that.
