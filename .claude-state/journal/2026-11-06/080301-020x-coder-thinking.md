---
ts: 2026-11-06T15:03:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6wBGxDbOd46KddSUPq55
---
Almost: score 2. `vol = (u16)vol;` emits `andi a1,a1,0xffff` at 218 where target has `sll a2,a2,0x8`. So the andi is a real insn, but something else got deleted (237 total).

Hmm. So the u16 cast is not free; it emits an andi, but the target has a `sll a2,a2,0x8` there instead... and 237 = target count. So mine has an extra andi but is missing another insn (the sll pan<<8 that reorg put in the delay slot in target).

Target 217-219: `bne a2,v0; sll a2,a2,0x8` (delay slot); mine: `bne a2,v0; andi a1,a1,0xffff`. So reorg filled the delay slot with the andi instead of the sll. Because vol's andi is available.

So the u16 cast is nearly right but leaves an insn. What about a cast that's completely free? `vol = (s16)vol;` gave 239 (2 extra insns: sll/sra?). 

Options: keep the andi but make it fill differently... Actually maybe better: use a real 2nd set that emits no insn at all. Ideas:
- `vol = vol & -1;` folds.
- `vol = vol | 0;` folds.
- Cast to the same type via a temp: `{ s32 t2 = vol; vol = t2; }` — cse merges (moves.md says cse merges copies).

Hmm. But note the u16 version has vol's andi in the delay slot; target's delay slot has sll a2,a2,0x8. The sll (pan<<8) is `sx = sx << 8;` which is a separate statement after the if. In target, reorg stole it into the bne delay slot. In mine, the andi (born later? no, born at the cast which is before the pan computation) took the slot.

Wait — order: mine 218 andi in delay slot of bne at 217. Target: sll a2 in delay slot. Both bne at 217. So mine's andi is scheduled into the delay slot instead of the sll. If the andi weren't there, the sll would take the slot. So we need a 2nd set that emits zero instructions but still kills the sched1 birth boost.

Zero-width: `do { } while (0)` gave 16 (236). Hmm.

What about an empty statement trick like C0535? Already tried.

What else kills sched1 birth boost without an insn... The launder asm was a zero-width RTL insn (asm with tied operands). Plain C alternatives that produce zero-width RTL: a `do{}while(0)` (which produced 236, not 237 — the EBB split changed scheduling and lost one insn).

Hmm, wait: c_dw gives 236 ins with score 16. c_split 236 score 30. Plain drop 236 score 30.

Target 237. The 237th insn in target: from the diff of a1, target has an extra insn around 200-216: target 209 `addiu v0,a2,160` and 210 `nop` (hazard) vs mine 210 `subu`. Mine: 207 mult v1,a2, 208 sra a0,a0,0x1f, 209 sra v0,a3,0x3, 210 subu a3,v0,a0, 211 --, 212 mfhi t1... So mine lacks the `nop` (mfhi hazard) — that's the missing insn! Target has `nop` at 210 after mult at 209? Actually target: 209 addiu v0,a2,160; 210 nop; 211 mult v0,a0; 212 sra a0,t1,0x6 — hmm the nop is between addiu and mult? Weird; more likely it's the mfhi hazard nop after a mult.

So the missing insn is a hazard nop that appears when the two magic multiplies are ordered a certain way.

OK so u16 gets 237 ins and score 2, missing only the delay-slot fill. Options: change what's in the delay slot. Since the andi is the extra, maybe place the cast elsewhere or make it conditional-free.

Alternative: cast to u16 but on a different expression so the andi folds into the arg? e.g. instead of `vol = (u16)vol;` do `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then... hmm.

Wait — what if the andi gets folded into the final `(vol | ...) & 0xFFFF`? The final call arg is `(vol | (0x3000 | sx)) & 0xFFFF`. If vol is known to be u16 (zero-extended), the & 0xFFFF might still be needed.

Hmm, but the andi at 218 is on a1 (vol), and the final `& 0xFFFF` is applied to the or result. Since vol's high bits are zero, or with sx (<<8, sx<16 so ≤ 0xF00) keeps bits ≤ 0xFFF, so & 0xFFFF is redundant... but gcc emits it? In target there is `andi a1,a1,0xffff`? Let's look at target's tail. Target 222: `or a1,a1,a2`. Then presumably `andi a1,a1,0xffff` then jal. Mine 222 `or a1,a1,a3` then andi.

Hmm, in mine with u16, maybe the andi at 218 IS the final `& 0xFFFF` moved up by sched1! That is: the `& 0xFFFF` on the call arg got scheduled into the delay slot. And then the sll a2 went... wait but 237 count. If andi is the final mask and the sll also exists somewhere, then target's andi... Let me look at more of the diff — score 2 means only ONE insn pair differs. So everything else matches including the count. So mine has `andi a1,a1,0xffff` where target has `sll a2,a2,0x8`, and target's andi must appear elsewhere in both. Since only one pair differs, mine also has the andi somewhere? No — one "replace" of 2:2 means mine[217:219] vs target[217:219], i.e. mine has bne+andi, target has bne+sll, and both have the andi... hmm no: if mine has an extra andi and target has the sll, both would need the other insn elsewhere; count is equal (237) so each has one of them at a different place? The diff only reports one region though, so mine's sll must be elsewhere and target's andi elsewhere, but they'd be at matching positions then...

Let me just look at the full listing around 210-230 for both. I'll ask dt to print more, or use --keep and objdump. Simpler: the diff shows only region 217:219, so everything else identical. That means mine has: ... bne a2,v0; andi a1,a1,0xffff ; then presumably sll a2,a2,0x8 later? And target: bne a2,v0; sll a2,a2,0x8; ... andi somewhere later? But then mine's andi at 218 replaced target's sll, and target's andi at ~223 replaced mine's sll? The diff would show two regions. Unless the sll in mine moved to where target's andi was, and the diff tool aligned them as one region... It showed only one region 217:219.

Hmm, maybe: target = bne; sll a2,a2,0x8 ; (then andi a1,a1,0xffff at 219?) Mine = bne; andi a1,a1,0xffff. The diff region is mine[217:219] vs target[217:219] = 2 lines each: line 217 bne, line 218 differ. So both have 2 lines. Target 218 = sll. Where's target's andi? Perhaps target has no andi at all: the `& 0xFFFF` is folded into... the call arg computation? In the orig (with launder) the andi exists: `andi a1,a1,0xffff` likely at 222+. But the count matched.

I'm speculating. Let me dump both listings properly. Use --keep to get the object and objdump? Easier: run dt with tail 400 and read the whole diff; score 2 means short diff. Let me do that.
