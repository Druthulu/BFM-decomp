---
ts: 2026-11-06T15:09:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mwgfFiCNRrOhOmJ2IsbR
---
All score 2 with the same issue probably. The andi always lands in the delay slot.

Let me reconsider: maybe the andi should be eliminated by making the *final* mask unnecessary and letting the cast's andi be the ONLY one — i.e. exactly target's shape: one andi at 4ba0 (jal delay), sll at bne delay. For that, the cast's andi must be scheduled at the jal slot, and the final `& 0xFFFF` must fold away.

d1 did `(u16)(...)` at the call and the cast separate → vol went to a3. Because with a single andi (at the call), the def of vol's live range changed → alloc moved it.

Hmm, what if I keep `vol = (u16)vol;` and write the call arg as `(vol | (0x3000 | sx))` (no mask) — then gcc must still mask? vol is zero-extended, sx ≤ 0xF00 → the or can't exceed 0xFFFF, but gcc doesn't know sx's range... it might keep the andi (it does, as the jal slot in target). In c_u16 the final andi is present. If I remove it, I'd get 236 with one andi at the bne slot.

The real target: andi at jal slot = the final `& 0xFFFF`. So target's schedule puts the *call arg mask* in the jal delay slot and the *pan shift* in the bne delay slot. Mine puts the cast's andi in the bne slot.

What if the cast's andi were scheduled into the jal delay slot and the final mask folded? Not controllable.

Different tactic: give the vol a 2nd set that produces an insn scheduled EARLIER (not at the branch). What insns are scheduled early? Ones needed by the pan chain? The vol chain's mfhi comes at 4b50, so vol's value is ready at 4b68 (subu a1,a0,v1). Any insn on vol can only be after 4b68. The remaining slots are 4b6c..4b80 (pan tail) then the branch. So a vol-dependent insn competes for 4b84+.

In target, the vol value is used only at 4b94 (ori a1,a1,0x3000) — after the branch. sched1 can't put the ori before the branch because... it's after? Actually `ori a1,a1,0x3000` at 4b94 is after the branch on the fall-through path. So sched1 placed the vol use after the branch (in the fall-through), and reorg did NOT speculate it into the delay slot — because `ori a1,a1,0x3000` is not a "simple" insn? reorg can speculate only certain insns... Actually reorg fills delay slots only with insns it can move (simple, no side effects, and not using values...). The andi a1,a1,0xffff at the jal slot is the final mask, speculated from... hmm, it's after the or.

OK: so in target the bne delay slot got `sll a2,a2,0x8` — the pan shift, which was scheduled at 4b84 already by sched1 (the first of the two slls). So sched1 itself placed a sll right after the branch, and reorg left it there as the delay fill.

In mine (c_u16), sched1 placed the andi right after the branch and the slls later. So the andi is scheduled where target has a sll.

Why would sched1 place a vol-andi there? Because of the data dependency: vol's subu completes at 4b68; the andi can go anywhere after.

What if the vol 2nd set is NOT an andi but something with a dependency that forces it earlier or later? E.g. `vol = (u16)vol;` but where vol is used immediately after in the same expression as sx? Like `func_8002D4C8(0xA9B, ((vol = (u16)vol) | (0x3000 | sx)) & 0xFFFF)` — hmm.

Alternatively, place the cast AFTER the branch (in the fall-through), i.e. inside... there's no if there.

Hmm! What about putting the 2nd set inside the `if (sx == 0x10)` body? No, conditionally executed.

Wait — actually, what about putting the cast inside a `do {} while(0)` block? c_u16dw gave 236/18 (the do-while changed the EBB → different schedule). Not it.

New angle: rather than vol, kill the sched1 birth-boost of the PAN multiply. Target order: vol mult at 4b4c, pan mult at 4b5c. The pan mult's operand `addiu v0,a2,160` is at 4b54 — computed right before. Mine (plain drop) had pan's mult earlier.

What if we give `sx` a 2nd set before the pan division: `sx = (s16)sx;`? sx is s32 from sra. (s16)sx → sll+sra? Since sx = (s16)*(u16*)&sxy, gcc knows it's sign-extended; (s16)sx cast would be a no-op at RTL? Possibly produces a real 2nd set with no insn! That's the G14 trick: `v0 = (s16)v0` = real 2nd set.

Try: after `sx = (s16)*(u16 *)&sxy;` add `sx = (s16)sx;`? Hmm, but we need the 2nd set AFTER the pan computation? No — we want to break the pan multiply's birth boost, so a 2nd set of sx BEFORE the division... the division's result is assigned to sx (a 2nd set already! `sx = (sx + 0xA0)/0x14` is a 2nd set of sx). Hmm.

Actually vol is set once; sx is set multiple times. The launder is on vol.

Let me try: give vol a 2nd set that's a *copy through a temp*: `{ s32 v2 = vol; vol = v2; }` — cse merges, but maybe cse1's EBB split... no.

Alternatively `do { vol = vol; } while (0);` → folded.

Hmm, let me try the C0535 trick differently: put `vol = (u16)vol;` inside a do-while(0) that ALSO contains the pan computation, so the EBB split changes and the andi is not at the branch:
```
do { vol = (u16)vol; sx = (sx + 0xA0) / 0x14; } while (0);
```
Hmm.

Actually — think about `if (sx == 0x10) sx = 0xF;` The branch at 4b80 is this if. The delay slot is filled from after the branch. The andi from the cast is placed there by sched1? No! sched1 doesn't place insns after a branch; sched1 schedules basic blocks, and the block ENDS at the branch. So the insn at 4b84 is in the *successor* block (fall-through), placed there by sched1 of that block, or by reorg speculation.

Ah, so the andi is in the fall-through block, scheduled FIRST (before the slls). Target has the sll first there.

So within the fall-through block (after bne), order: mine = andi, li a2,15, sll; target = sll, li a2,15, sll.

Hmm wait, the bne is `bne a2,v0,4b90` — it skips 4b84-4b8c (li a2,15; sll) to 4b90. So 4b84 is the delay slot (executed always), 4b88/4b8c are the "sx = 0xF" path.

So the delay slot at 4b84: target has `sll a2,a2,0x8` (speculated from 4b8c? no — the sll at 4b8c is on the other path). Hmm: target 4b84 sll a2,a2,0x8; 4b88 li a2,15; 4b8c sll a2,a2,0x8. The first sll is the speculative shift for the fall-through (sx != 0x10 path), the second is for the ==0x10 path. So `sx = sx << 8` after the if got duplicated by reorg: speculated into the delay slot + the branch-target path keeps its own.

Mine: delay slot = andi (the vol cast), and the fall-through path's sll is missing?! Mine 4b8c sll is the ==0x10 path's. So on the fall-through path (sx != 16), mine has NO sll → WRONG code? No — mine's andi at 4b84... then 4b88 li a2,15 and 4b8c sll are the taken path; the fall-through continues at 4b90 with a2 unshifted?! That can't be right; the tool would report a semantic difference? It doesn't check semantics, only the insn sequence. But gcc wouldn't produce wrong code.

Hold on: bne a2,v0,4b8c (mine) vs 4b90 (target). Mine's branch target is 4b8c = the sll. So mine: bne → 4b8c (sll a2,a2,0x8) — correct fall-through path skips li a2,15. Target: bne → 4b90, with the sll speculated at 4b84 (delay) AND at 4b8c (for the taken path, after li a2,15).

Both are semantically right: mine puts the shift on the fall-through at 4b8c, target speculates it into the delay slot and branches past it.

So the difference is a reorg speculation choice: target speculated `sll` into the delay slot (dead on fall-through); mine speculated `andi a1,a1,0xffff` instead (also dead-safe) and kept the sll in the branch-target path.

So the andi is the only other "safe to speculate" insn, and reorg prefers it (it comes first in the block?). Where does the andi sit in the block? It must be in the block *after* the branch too? Hmm, reorg speculation for the delay slot picks insns from the block after the branch (the fall-through) that are safe. Mine's fall-through block starts with... 

Honestly: to fix, remove the andi. Then plain drop → the whole schedule changes (score 30). Unless... the andi is what fixes the schedule and ALSO breaks the delay slot.

Alternative: replace the vol 2nd set with a 2nd set that is NOT speculatable in a delay slot. Insns reorg won't speculate: anything with a hazard, or a load/store, or... Let's use a *use* of vol that involves a memory op? That'd add insns.

Hmm, what about `vol = (u16)vol;` combined with making the final mask not needed so the count is 236+1=237... no wait, mine already is 237 (with 2 andis, missing one sll). Target: 2 slls, 1 andi.

So I need: andi (cast) → placed at the jal delay slot (like target's final mask) and the final mask folded away, plus the sll speculated. d1 tried exactly that but vol went to a3.

In d1: `vol = (u16)vol;` + `(u16)(vol|...)` → 237, vol in a3, and the bne delay slot got `andi a3,a3,0xffff` (the cast's). So the cast's andi still took the slot, and the final mask vanished.

So the cast's andi is the problem in every variant. Need a 2nd set of vol with NO insn.

Zero-insn 2nd sets: what about `vol = vol * 1;`? folds. `vol = vol / 1;` folds. `vol = vol | 0;` folds. `vol = vol ^ 0;` folds. `vol = vol + 0;` folds.

What about `vol = -(-vol);`? folds.

What about a volatile-ish thing? `*(volatile s32*)&vol;` no.

What about making vol's type u32 vs s32? A type change of the declaration isn't a body change... it is inside the body (decl). `u32 vol;` then `vol = ((0xA0 - av) * 0x7F) / 0xA0;` — with u32, the division by 0xA0 (unsigned) uses a different magic (0xCCCCCCCD or shift). Would change the code. No.

What about `s16 vol;`? c_hvol (u16) gave 238/9.

Hmm, what about declaring vol as `s32` but assigning twice with the SAME computation... c_split gave 30.

Let me think about what the launder did in RTL: asm with a tied output. Maybe its real effect is the REG_UNUSED/REG_DEAD notes... The tied operand makes the asm both use and def vol.

Zero-insn alternative that creates a use+def in RTL: none in plain C.

So: accept an insn, but make it one that reorg will NOT speculate into the delay slot. Candidates: an insn with a "delay slot hazard" — reorg refuses to put loads in delay slots of branches? Actually reorg CAN speculate loads. Insns it won't: those that set a register needed in the branch's target path? No, it checks "insn in delay slot is not needed by the branch target"...

What if the 2nd set writes a *different* variable (a temp) and that temp is used in the call arg? E.g.:
```
s32 vol2;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
vol2 = (u16)vol;   // andi to vol2
... arg uses vol2
```
The andi would target vol2, a different pseudo. But it's still speculatable.

What if the extra insn is a `mult`-dependent op (mfhi)? no.

What if the 2nd set is `vol = vol >> 0;`? folds.

Hmm. Different idea: give vol's 2nd set inside the branch's TAKEN path? Not semantics-preserving.

OK alternative strategy: instead of vol, break the sched1 order using a different lever: the `av` computation. What if we make `av` a 2nd set... the target's pan mult is preceded by `addiu v0,a2,160` (sx+0xA0) — that's from sx.

Let me look at the plain-drop schedule (a1) again:
```
194 sra a3,v0,0x10       sx
195 bgez a3
196 move a1,a3           av=sx
197 negu a1,a3
198 lui a2,0x6666        magic
199 ori a2,a2,0x6667
200 addiu a0,a3,160      sx+0xA0
201 mult a0,a2           PAN mult
204 mfhi a3
207 mult v1,a2           VOL mult
208 sra a0,a0,0x1f
209 sra v0,a3,0x3
210 subu a3,v0,a0
212 mfhi t1
...
```
Wait, a0 is overwritten? 200 addiu a0,a3,160 then 201 mult a0,a2, then 208 sra a0,a0,0x1f — uses a0 after mult (fine).

So in plain drop: pan mult at 201, vol mult at 207. Target: vol mult at 4b4c (4b4c), pan mult at 4b5c.

Hmm interesting: in the target, both mults use a0 (magic) and are separated by the `addiu v0,a2,160; nop`.

What if I make the vol computation's operand chain shorter/longer so sched1 orders it first? E.g. change `((0xA0 - av) * 0x7F) / 0xA0` to `((0xA0 - av) * 0x7F) / 160` — same value, same insns. Or `(0xA0 - av) * 127 / 0xA0`. Identical.

What about `vol = (0xA0 - av) * 0x7F / 0xA0;` (no inner parens) — identical parse.

Hmm, what if the division is written as a compound: `vol = (0xA0 - av) * 0x7F; vol /= 0xA0;` — tried (30).

What if the vol numerator uses a temp: `s32 t2 = 0xA0 - av; vol = (t2 * 0x7F) / 0xA0;` — same.

OK, what about giving the *pan* computation a shape that sched1 values less, e.g. `sx = (sx + 0xA0) / 0x14;` → `sx = (sx + 160) / 20;` identical. 

What about `sx = (sx + 0xA0) / 0x14;` with sx reused... 

Let me revisit: maybe the real lever that makes target's order is the *nop* (mfhi hazard). Target has `mult v0,a0; nop`? no, the nop is before the mult (4b58 nop, 4b5c mult) — that's the hazard nop after `mfhi t1` (4b50)? mfhi t1 at 4b50, then 4b54 addiu, 4b58 nop, 4b5c mult. The nop is the "hilo" hazard: after mfhi, you can't do mult for 2 cycles. So the nop fills.

In mine (plain drop), the vol mult at 207 follows mfhi at 204 with only 2 insns between (208,209?) no...

This is deep. Time check: item 1 started ~08:00, now maybe 08:20. Budget 20-30 min. Let me try a few more cheap shots and then decide.

Cheap shots:
1. `vol = (u16)vol;` but with the pan shift moved BEFORE the if:
```
sx = (sx + 0xA0) / 0x14;
sx = sx << 8;
if (sx == 0x1000) sx = 0xF00;
```
That changes the if semantics — the target has `if (sx == 0x10) sx = 0xF;` then `sx <<= 8`. Rewriting as shift-then-compare is a different but equivalent computation: `sx << 8` then `if (sx == 0x1000) sx = 0xF00;`. This might change the schedule: the sll would be before the branch, and the delay slot would need something else. Probably worse.

2. Give vol's cast inside a `do{}while(0)` that also wraps the if? 

3. Accept score 2? No — must be 0.

4. Try `vol = (u16)vol;` where the final mask is dropped AND the cast is placed at the very end (late): c_u16late gave 238/6 (both andis? and vol in a1?). Let me check c_u16late's diff... it was 238.

5. Try `vol &= 0xFFFF;` — same as cast.

6. Try making vol's 2nd set a *shift-based* zero-extension: `vol = (vol << 16) >> 16;` → sll+sra 2 insns (239). Or `vol = (u32)vol << 16 >> 16;` same.

7. What about `vol = (u16)vol;` plus removing the final mask and instead making sx's shift produce the mask? 

8. What about a completely different lever for the ordering: make the pan division use a *different* magic by changing 0x14 to a different constant? No, semantics.

9. Reorder: move `vol = ...` to AFTER the pan computation (source order swap) + u16 cast:
```
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) sx = 0xF;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = sx << 8;
```
Then sched1 might naturally put vol first? Try both with and without the u16 cast.

10. Also try the same but with `vol` computed before `av`? no.

Let me try 9 and a couple of others in one batch.

Also idea 11: use `if (sx == 0x10) { sx = 0xF; }` braces? no change.

Idea 12: change the final arg expression to use `vol` twice: `(vol | (0x3000 | sx)) & 0xFFFF` → `((vol | 0x3000) | sx) & 0xFFFF`? fold reassociates. Or `(vol + 0 | ...)`.

Idea 13: make vol's 2nd set be `vol = (u16)vol;` AND give `sx` a 2nd set `sx = (s16)sx;` right before `sx = sx << 8` — maybe then the sll moves up.

Let me batch 9a, 9b, 13.

Actually wait. Let me reconsider idea: `sx = (sx + 0xA0) / 0x14;` — what if we split this into two statements with a temp:
```
sx = sx + 0xA0;
sx = sx / 0x14;
```
That's a real 2nd set of sx (multi-set), which kills sched1's birth boost for the pan multiply! And the addiu v0,a2,160 might be scheduled differently. This is in the C0505 catalog (statement splits). Let me try that! No extra insns.

And combined with vol unchanged (launder removed).

Similarly `vol` split gave 30, but sx split is new.

Let me try:
- f1: `sx = sx + 0xA0; sx = sx / 0x14;`
- f2: f1 + keep vol as is.
- f3: 9a (swap vol after pan).

Let me generate. The launder block replacement snippet can contain the reordering since it's contiguous with the sx line. mk.py replaces the two launder lines with the snippet; the following line `sx = (sx + 0xA0) / 0x14;` remains. I can include a replacement for that too via rep.py afterwards. Simpler: put the full replacement text including the sx lines in the snippet and then delete the original sx line via rep.py.

Hmm, mk.py replaces only the launder block. Let me instead use rep.py with the anchor being the launder block + following lines.

I'll build the "old" file as the text:
```
            /* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)
            sx = (sx + 0xA0) / 0x14;
```
and the new text accordingly. Let me create these files.

Note the em dash in the comment — need exact bytes. Easier: build the old text by extracting lines 88-90 from orig.c programmatically... I'll write a small script `block.py` that replaces a line range (start anchor, end anchor) with a file. mk.py already does that (first-anchor/last-anchor). mk.py supports custom anchors! mk.py <base> <out> <snippet> <a1> <a2>. So I can set a1='/* lever 3:' and a2='sx = (sx + 0xA0) / 0x14;' to replace the block plus the sx line.

Let me use that.
