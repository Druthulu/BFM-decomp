---
ts: 2026-10-22T21:21:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Xq6ZsAEXTofsexQ4JrYa
---
Now clear. Target:
- arm1 (cond1): 144c-1468, full 8 insns.
- arm2 (cond2): 149c li 682; 14a0 sh 32; 14a4 j 14ec; 14a8 li 2048 (delay). Then continues at 14ec: sh v0,34(0x22); 14f0 sh zero,36; 14f4 sh zero,46; 14f8 sh zero,48; falls to 14fc.
  So arm2's tail (sh 34, sh 0, sh 0, sh 0) is shared with arm4 (14e0: li 682; 14e4 sh 32; 14e8 li 1536; 14ec sh 34 ...). So arm2 and arm4 DO share a tail! Their bodies: arm2 = 0x2AA,0x800,0,0,0; arm4 = 0x2AA,0x600,0,0,0. Different second store → common suffix = sh 34, sh 0, sh 0, sh 0 → merged at 14ec. Yes! Cross-jump merged arm2/arm4's tails.
- arm3 (cond3): 14c0-14dc full 8 insns, separate.
- arm4: 14e0-14e4, then joins 14ec.

So the ROM's compiler DID cross-jump (arm2/arm4 merged), but arm1 and arm3 were NOT merged despite being identical.

So the difference between arm1 and arm3 in the ROM's source must be real. Since cross-jump merges identical suffix insns, arm1 and arm3 must differ in the LAST insn (sh v0,48) at minimum — because their common suffix would otherwise merge.

Look: arm1's last store sh v0,48 where v0 = -80 (li at 1458). arm3's: li -80 at 14cc, sh v0,48 at 14dc. Same.

Unless... the register differs in the ROM's build? No, both v0.

Hmm, so cross-jump compares insns with rtx_equiv_p — maybe it does NOT rename registers across blocks in a way that... it does.

Wait, maybe the real reason: cross-jump's `find_cross_jump` requires that the blocks' *first* insn matched... no, it finds the longest matching suffix and requires the preceding insns to differ (it can't merge the whole block since blocks would be empty).

Hmm, actually! There's a subtlety in gcc's cross-jumping: it computes the longest common suffix, then it *trims* it: "don't allow the last insn to be a jump" etc. Also there's a constraint: it only merges if `i1 != BB_HEAD` etc.

But actually more important: cross-jump in gcc 2.7.2 (`jump.c: cross_jump` / `find_cross_jump`) has this: it stops at insns that are `JUMP_INSN`s or `CODE_LABEL`s, and it does NOT merge across a "barrier"... 

Hmm, another thought: maybe arm1 in the ROM source is NOT `unk30 = -0x50` but `unk30 = k` where k is a *separate* variable... doesn't matter for RTL if both are const.

Wait wait. Let me reconsider: is the difference maybe that arm3's stores are in a different ORDER in the ROM's source, and sched1 reorders them back? E.g. arm3 source order: unk20, unk22, unk24, unk2E, unk30 — but sched1 gives the target order. Since sched1 runs per-block after cross-jump? No: cross-jump (jump2) runs AFTER sched1 and reload. So by jump2 time the insns are already scheduled. If arm3's scheduled order differed, cross-jump wouldn't match.

So in the ROM: arm1's scheduled block and arm3's scheduled block must differ somewhere. From the disassembly they look identical... let me compare very carefully:

arm1: 
144c: a6020020 sh v0,32(s0)   [v0=113 from delay slot]
1450: 24020600 li v0,1536
1454: a6020022 sh v0,34(s0)
1458: 2402ffb0 li v0,-80
145c: a6000024 sh zero,36(s0)
1460: a600002e sh zero,46(s0)
1464: j 14fc
1468: a6020030 sh v0,48(s0)

arm3:
14c0: a6020020 sh v0,32(s0)  [v0=113]
14c4: 24020600 li 1536
14c8: sh v0,34
14cc: li v0,-80
14d0: sh zero,36
14d4: sh zero,46
14d8: j 14fc
14dc: sh v0,48

IDENTICAL. So cross-jump should have merged them... unless the RTL differs in a way invisible in the asm — e.g. REG_EQUAL notes? Notes are not compared by rtx_equiv_p (only PATTERN). Hmm.

Or... the merge requires the two blocks to have the same successor AND to not be the fall-through? Both jump to 14fc (the join).

Unless one of them was already the target of something... In gcc 2.7.2's jump.c `cross_jump`, there's `struct rtx_renaming` and it calls `merge` — maybe it's only applied to blocks that end with a jump and have identical successors.

Alternatively, maybe the ROM's compiler is different from ours and doesn't cross-jump; then arm2/arm4 sharing would come from the source itself being written to share (e.g. a goto or a common tail variable). Hmm! That's plausible: the ROM's source might have had arm2 and arm4 fall into a shared tail naturally.

But then arm1 and arm3 wouldn't merge only if our compiler merges them... and our score with the barrier is 0. OK.

Let me flip the approach: instead of preventing the merge, make the merge produce the target! I.e., accept the merge and restructure so the merged result matches.

In the target: arm2 and arm4 share a tail at 14ec, arm1 and arm3 are separate. If our compiler merges arm1 and arm3 (identical), we could instead give arm1 and arm3 a *shared* tail deliberately... no, the target has them separate.

Hmm, but what if the difference is which arms are identical? What if in the ROM's source, arm1's constant is written as `-0x50` and arm3's as a variable `k` that is used BEFORE... 

Let me look at the actual RTL difference. Since arm1 and arm3 are merged by our compiler at jump2, let me look at the jump2 dump of the WITH-barrier build (the current tree) to see how arm3's block differs there. If with the barrier the blocks differ only by the asm insn, then a plain-C difference must be found.

Better: let me look at what insns are in arm1 and arm3 blocks in the .jump2 dump of w2 and see the actual PATTERNs, to find where I can introduce a difference that survives to asm.

From w2, the merged suffix is sh zero,36; sh zero,46; sh v0,48 (3 insns). The first differing insn going backwards is `li v0,-80` vs ... wait no. In w2 arm1 = sh32, li1536, sh34, j, li-80(delay) then continues at 14c4 sh0,36. So the merge is of sh zero,36; sh zero,46; sh v0,48 (3 insns) — meaning arm1's `li -80` is in the delay slot while arm3's `li -80` is a normal insn at 14c0, i.e. positions differ, so only the last 3 match.

In the target, arm1's `li -80` is at 1458 (a normal insn, not in the j delay slot). So the target's arm1 has li -80 NOT in the delay slot. In w2 arm1, the li -80 was moved into the j delay slot at 145c! Because arm1's block is shorter now.

OK, so in the target arm1: sh32, li1536, sh34, li-80, sh0-36, sh0-46, j, sh-48. The li -80 sits 3 insns before its use.

Now, if I can make the compiler schedule arm1 that way and arm3 the same way, they'd still be identical and merge. Ugh.

So the fundamental question: how did the ROM avoid the merge? Something in the RTL must differ.

Idea: maybe in the ROM's source, arm1's last store is `unk30 = -0x50;` (const → movhi_internal2 with const) and arm3's is `unk30 = k;` where k is a *register* — so arm1's store insn is `(set (mem) (const_int -80))` while arm3's is `(set (mem) (reg))`. Different patterns → no merge. And the asm: movhi_internal2 with a const emits `li v0,-80; sh v0,...`, and movhi_internal with a reg emits `sh reg,...` — so in arm3 the reg must be $2 = v0, and the `li v0,-80` comes from k's own initialization.

That's exactly what w2 tried but combine folded k (SI) to a const. With `s16 k` (HI), w3 gave 106 (fully merged) — because the HImode k was folded.

How to keep k as a real register at jump2? The value must not be a known constant to cse. E.g. `s16 k = -0x50;` where cse2 doesn't propagate... 

What if k is not a constant at all but is loaded/stored such that the value equals -0x50 through a computation that folds at RTL only in the asm? Hmm.

Alternative: what if k is a *parameter-like* value: e.g. `s16 k = sp10.v[1] ...` no, must be exactly -80.

Alternative: use a value cse can't fold but which is computed cheaply... any computation costs an insn.

Hmm — what about a global variable? `unk30 = D_something;` costs a load.

Hmm, what about this: the constant -0x50 could come from an existing register value. Look at the target arm3: `li v0,-80` at 14cc. And the tail: `li v0,-1024` at 1510, `li v0,-258` at 152c. Nothing preloaded.

New idea: what if the difference is in the *store width*: arm3's unk30 stored as `*(s16*)` vs arm1's as a struct field — we tried (w5) but the struct-cast difference didn't survive... w5 changed arm1's store to a cast and got 106 (merged) — meaning the cast store's RTL is the same (mem:HI without /s maybe, but exp_equiv_p ignores it).

OK, what about making one of the *other* stores differ structurally so the common suffix is empty? The common suffix must be empty for the target (arm1 and arm3 both end with j + sh v0,48; if the last insn differed, the suffix is empty → no merge).

So: make the LAST store's insn pattern differ. Options:
- arm1: `unk30 = -0x50;` → const store pattern.
- arm3: store a register whose value isn't a known constant.

What if k is `s16 k;` assigned from a function of sp10? e.g. `k = (s16)(sp10.v[2] - sp10.v[2] - 0x50);` — folds to -0x50 in the frontend? Probably folds at RTL (combine) too.

What if k comes from a *volatile* read? no, adds a load.

Hmm, what about using the fact that in arm3, `sp10.v[2] < 0x380` — so we could set k from the condition: `k = sp10.v[2] < 0x380 ? -0x50 : 0;` → folds.

OK, think about cse2. cse2 runs after sched1? Order: cse, jump, sched1, lreg, greg, reload, cse2, jump2. So cse2 (post-reload) folds constants using REG_EQUAL notes. To prevent folding, the register must not carry a REG_EQUAL const note.

How about: `s16 k = -0x50; ... k` used in TWO places? Then cse may not propagate (it can propagate with multiple uses though).

Alternative: make k's definition an insn cse2 can't use: e.g. `s16 k = -0x50;` then `k = (s16)(k | 0);`? folds.

Hmm, what about deriving k from the pointer arithmetic: no.

Different angle: what if arm3 doesn't store the constant at all, but the target's arm3 store is a *copy* from another register that happens to hold -80... 

Actually! Look again at the target: is it possible that in the ROM's source, arm3 was `unk30 = k` where k is a variable initialized *before* the if-chain (a function-level variable)? Then k is a pseudo with a single const definition at function top. cse2 would propagate it too...

Unless the definition is in a different basic block than the use, and cse2 is per-extended-basic-block: a const definition at the function top is in the entry block; the use is in arm3 — different EBB (because of the branches). cse2 does constant propagation only within an extended basic block (from cse's own processing; REG_EQUAL notes can propagate constants across blocks though — that's `cse_set_around_loop`/`cse2` uses REG_EQUAL notes to replace uses of a reg by its constant value even in other blocks, when the reg is not modified).

Hmm, in gcc's cse.c, `fold_rtx` looks up `reg_eqv` for a reg and if there's a REG_EQUAL note with a constant and the reg is "constant" it substitutes. There's a check `reg->first_uid`... complicated.

Let me just EXPERIMENT: declare `s16 k = -0x50;` at the FUNCTION level (before the if-chain), store `unk30 = k;` in arm3. Test.

Also try: k declared at function level as s32.

Also: put `k` in the first arm too? No.

Let me also try making the *first* store differ: arm3's unk20 store as `unk20 = (s16)0x71;` — probably same.

And another idea: change arm1's body to store `-0x50` via a variable declared inside arm1 (mirror). Both would then be registers → merge again.

Let me try the function-level k variants.

Another idea: the target's arm1 stores `-0x50` and arm3 stores `k`. What if the difference is that arm3's store is `unk30 = k` where k is a *u16* and the value -0x50 → 0xFFB0, so the store insn would be... same sh.

Let me try a batch:
- w6: k declared at function top (`s16 k = -0x50;` before the if-chain), arm3 stores k.
- w7: same but s32 k.
- w8: k declared inside arm3 but assigned in two steps: `s16 k; k = -0x50;`? same.
- w9: arm3 stores `unk30 = k;` with `s16 k = -0x50;` and arm1 stores `unk30 = -0x50;` — that's the baseline w (13).

Also try: arm1's store via `*(s16*)((u8*)a0+0x30) = -0x50;` AND arm3's via struct — w5 was the opposite (I changed arm1). w5 got 106 = merged.

Hmm.

Let me think about what actually differs in the ROM at the RTL level. Since the asm is identical, the RTL difference must be invisible in asm. Candidates: (1) mem /s flag, (2) subreg wrappers, (3) REG_EQUAL notes (not compared), (4) different but equivalent patterns (movhi_internal vs movhi_internal2), (5) a different register with renaming allowed (no).

For the LAST insn (sh v0,48 in the delay slot), we need a pattern difference. In arm1: `(set (mem:HI (plus (reg) (const 0x30))) (const_int -80))` = movhi_internal2. In arm3, if the value is a reg → movhi_internal. Then the asm differs slightly? movhi_internal2 with a const: emits `li at/reg, const; sh reg, off`. movhi_internal with reg: `sh reg, off`. Both end up sh v0,48 if the reg is v0.

So the s32-k idea (w2) had the right shape but combine folded it. Let me check w2's RTL in .jump2 to see arm3's last store pattern.

Actually, better: let me check w2's cse2 dump for arm3's store.

Hmm, time. Let me be pragmatic and try a batch of ~8 variants and see which scores best. Time check: started 15:11, now ~15:35. I have until ~15:41 for 30 min. Hmm, the budget is 20-30 min per item and a WALL needs ≥20 min and ≥30 scored tries. I've done ~6 tries.

Let me push efficiently: batch of variants.

Variant ideas to keep k a real reg at jump2:
1. k at function level (s16).
2. k at function level (s32).
3. `s16 k = -0x50;` inside arm3, and arm3 stores `unk30 = k;` — plus a second (dead) use of k in the arm to prevent folding: e.g. `unk2E = k - k;`? That changes insns.
4. arm3: `s16 k = -0x50; ((...)->unk30) = k;` where the store is via a `volatile s16 *`? volatile adds nothing but changes RTL (mem:HI volatile) — same asm! `*(volatile s16 *)((u8*)a0+0x30) = k;` — the asm would be sh v0,48(s0) still. And cross-jump would not merge (volatile mem differs from non-volatile). This is promising! But is a volatile store a "lever"? The kinds row is `barrier` only; volatile isn't in walls.txt as a lever kind... but the brief says "no new lever of any kind". A volatile store is arguably a lever (semantic change). Hmm, risky. Actually volatile changes semantics (ordering), which is a lever. Avoid.

5. Different but equivalent addressing: arm3 stores via `a0` cast to s16*: `s16 *p = (s16 *)a0; p[0x10] = ...` (0x20/2 = 0x10). This gives `(mem:HI (plus (reg p) (const 16)))` and after cse p may fold to a0 → same. But at jump2, if p is a separate pseudo... after reload p becomes the same hard reg. Same.

6. Change arm3's first store to be to `unk20` as a *u16* field? Same insn.

Hmm, what about attacking it from the other side: make arm1 differ by storing the constant through a variable that ISN'T foldable, e.g. arm1 stores `unk30 = k1` where `s16 k1 = -0x50;` — merges.

OK here's another thought: maybe the ROM's difference is the *branch* into arm1 vs arm3 — no, blocks are compared by content.

Let me look at the actual .jump2 dump with the barrier present (current tree) to see exactly which insns differ between arm1 and arm3 there. That tells me the minimal RTL difference to reproduce. The current tree scores 0, so let me dump the *current tree* TU (src) — but I can't write outside my shard. I can dump the current src TU: cc1_dumps_tu.sh accepts a .c file: src/ov_SC02_026/ov_SC02_026_jr_8017C180.c. Dumps go under my item dir. 

Then compare arm1/arm3 blocks in .jump2.
