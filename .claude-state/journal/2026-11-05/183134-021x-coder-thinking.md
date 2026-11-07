---
ts: 2026-11-06T01:31:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iUDZmdX58MV321Qbw2rv
---
Now I see the merge: in mine, dec's tail is `lw v0,28(s0); j 1800; addiu v0,-1` — cross-jump merged dec's `sw v0,28(s0)` with zero's `sw v0,28(s0)` at 1808 (target 1808). Wait in mine, j 1800 with delay addiu v0,-1, then falls to zero block (17c8) which ends at ... let me see 140+.

Actually cross-jump merged the store `sw v0,28(s0)` shared between dec and zero, moving dec's jump target to the shared store at end of zero block. Target wants dec's own store in its delay slot.

So the C must be shaped so that the two `sw v0,28(s0)` don't look identical to find_cross_jump. Since the instruction sequences are identical in isolation, cross-jump (a RTL-level optimization) matches them by insn identity.

How to prevent without levers? Real C changes that alter the tail instruction's register or form: e.g. in zero, assign 0x1D via a variable used elsewhere, so the store is `sw v0,28(s0)` still. Hmm.

Alternative: change the *order* in zero: target order is li v0,29; sh zero,244; sw v0,28. If we put the unk1C store first: sw v0,28; then li; sh zero,244 — that changes target order, mismatch.

Maybe use `t` or another variable such that the store becomes from a different pseudo but same reg... it'd still be v0.

Wait — maybe cross-jump works on the *whole block* not individual insns; merging identical tails. Target zero block: last insn is sw v0,28(s0) which is the same as dec's last. find_cross_jump finds common tails. To avoid, one could make zero's final store use a different addressing form, e.g. via a pointer `p = a0; p->unk1C = 0x1D;` — but that still emits sw v0,28(s0) with base s0 if s0 aliases.

What about making the constant load not be li v0,29 but e.g. store an expression that yields v0 but through a different instruction... target requires li v0,29 exactly.

Hmm. Real-C approach used in other shards for barriers: do{}while(0) block splits cse1 EBB (C0535). Here the barrier is at the *end* of zero. C0535: do-while splits cse1 EBB — used to stop cse from merging? Here the optimization is jump2 cross-jump, not cse1. But a do-while around part of the zero block could create a different CFG such that cross-jump can't merge (e.g., an extra label). Would it add instructions? do{}while(0) is removed early unless it changes something. In the worked example it survived to affect alloc.

Alternative: use a goto/label to restructure zero so that the tail isn't a fallthrough from the same block? Target zero is a fall-through block ending at 1808 then 180c epilogue. Any label doesn't emit.

Maybe the trick is the opposite: make the *dec* block's store different from zero's by making dec's store not `sw v0,28(s0)` in RTL identity? Target dec: lw v0,28(s0); addiu v0,v0,-1; j 180c; sw v0,28(s0). Both are sw of v0. Can't change without breaking.

Cross-jump merges identical *suffixes* when one block jumps to the other. The `dec` block jumps to 180c (epilogue). zero falls through to 180c. Cross-jump sees dec's block tail `sw v0,28` and zero's block tail `sw v0,28` and redirects dec's jump to zero's store. To prevent, we need the CFG to not have that relationship or the insns to differ.

Since the target emits dec's store in a delay slot (j 180c; sw), maybe restructuring dec as `goto`... no.

Think about how the barrier got introduced: presumably the original C code (which this is reconstructing) naturally produced this. The barrier was added because a real-C equivalent wasn't found. Our job: find one.

Idea: In zero, the final store `((Unkstruct*)a0)->unk1C = 0x1D;` — if we express it as a store of a variable that is also used, e.g. `t = 0x1D; ((...)->unk1C = t;` — but t's pseudo may be v0 same.

Hmm what if we make zero's store go through a different base register? The target uses s0 for all. No.

What if the last statement in zero is *not* the unk1C store but the barrier was at end and the code order is sh zero,244 then sw. If we add a dummy statement after the sw that produces no code but breaks the basic block tail identity — like a `do{}while(0)` with a label? cse1/jump2 might still merge.

Actually wait. Cross-jump operates on blocks: for each pair of blocks ending with an unconditional jump, compare backwards. Here `dec` ends with `j 180c` (epilogue block). zero ends falling into 180c. The "duplicate" is the store preceding the jump. Actually find_cross_jump compares block1's jump target block with block2... Let me recall GCC 2.7 jump.c: `find_cross_jump` compares two blocks (b1 ends with jump to b2?) looking for common insns at their ends, then redirects. The tail comparison can match multiple insns.

So zero's last insn(s) identical to dec's last insn(s) before its jump. If we can make the *preceding* insn differ too... they already differ (li v0,29 vs addiu v0,-1). find_cross_jump typically requires at least one insn to match and won't cross a label. It matched exactly one (sw).

One standard real-C trick: make the store a *different kind* — e.g. store via a `u32` lvalue vs `s32` — same width, same insn. No.

What about using `CAST_WIDTH`? The struct unk1C is s32. Could write `*(s32 *)(a0 + 0x1C) = 0x1D;` same.

Different idea: in the zero block, replace `((Unk*)a0)->unk1C = 0x1D;` with `((Unk*)a0)->unk1C = (s32)0x1D;`? same.

Hmm, but what if the constant store in zero were emitted as `li v0,29; sw` while in dec the store is preceded by addiu; the shared insn is `sw v0,28(s0)`. What if zero's value goes to a different register? Target requires v0. But is v0 = 2 required? Yes target shows `2402001d li v0,29`.

Alternative: change dec's store register. Target shows `sw v0,28(s0)` in delay slot. Required.

So both must be `sw v0,28(s0)`. Cross-jump will see identical suffix. Unless the CFG makes them not comparable: e.g., if zero is not fall-through into epilogue but also has an explicit jump? That would add an instruction (target zero falls through: 1808 sw then 180c epilogue, no jump). Hmm target has no j for zero.

Wait, actually cross-jump matches dec's block tail with *any* block that is the target of dec's jump? dec jumps to 180c (epilogue). The merge in mine: `j 1800` — 1800 is zero's `li v0,29`. So it merged dec's block (lw; addiu; j 180c; sw) with zero's block? The merged store is zero's sw at 1808. Actually mine's dec: `lw; j 1800; addiu` — wait that's odd: j 1800 jumps to li v0,29 which is zero's start of tail, and the delay slot has addiu. Then zero's li; sh zero,244; sw v0,28. So dec now computes v0 = unk1C-1, jumps to zero's tail which does li v0,29 (overwrites!), sh zero,244, sw v0,28. That's wrong semantically! It stores 29 into unk1C for the dec path — a miscompile! That's why it's length-drift and "NEEDED DIFFERS". Wait no — cross-jump shouldn't miscompile. Let me re-read: 17c0 in mine is `j 1800` with delay `addiu v0,v0,-1`... then at 1800 (zero's block) li v0,29... that can't be right.

Hmm, wait. Maybe I misread the mine dump — mine's blocks are shifted. Let me see mine's full tail from 179c to end.
