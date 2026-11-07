---
ts: 2026-11-06T21:48:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_U4y81Pv5pPCORlISpogL
---
Key: pseudo-pseudo tie happens when the *used* reg (ureg) dies at this insn. For the ashift insn `set (r84) (ashift (r181) 2)`: which is ureg and setreg? In block_alloc, r0 = dest (r84), r1 = operand (r181). It calls combine_regs(r1, r0, ...) → usedreg=r1=r181, setreg=r0=r84. ureg=r181, sreg=r84. r181 dies at this insn → tie sreg(r84) into ureg's (r181's) quantity! So r84 and r181 become the SAME quantity. Great — so oidx and otz-load are one qty, whose n_refs = 2 (r181) + 3 (r84) = 5? qty_n_refs[sqty] += reg_n_refs[sreg] → 2+3 = 5. qty_size stays 1. qty_death = max? The qty's death updates on uses.

So the oidx/otz qty has refs 5, birth at r181's birth (insn 343), death at r84's last use (insn 375). live 14 positions. pri = floor_log2(5)*5/14 = 2*5/14 = 0.714 → 7142.

Similarly, other ties may happen. The packet chain: r183 = and(r182, r184). Does r182 die? Yes at insn 350 (REG_DEAD r182). So r183 ties into r182's qty! refs 2+2=4, birth at r182's birth (pos12), death at r183's death (pos16). live 4. pri = floor_log2(4)*4/4 = 2*4/4 = 2 → 20000. Hmm that's high.

And r194 = ior(r183, r192): r183 dies at 366? Yes REG_DEAD r183. So r194 ties into r183's qty (which is r182's). refs 4+2=6, birth pos12, death pos17. live 5. pri = floor_log2(6)*6/5 = 2*6/5 = 2.4 → 24000. Even higher!

And r192 = and(r191, r193): r191 dies → tie r192 into r191's qty. refs 2+2=4, birth r191 pos13, death r192 pos16 → live 3. pri = 2*4/3 = 2.67 → 26666.

So the packet chain qty (r182+183+194) = refs 6, live 5, pri 24000. The oidx qty (r181+r84) = refs 5, live 14, pri 7142. Packet wins $3.

In the target (reference), the same structure presumably exists... but the reference's oidx won. So the reference's oidx qty must have had higher priority, or the packet qty lower. Hmm.

Wait, but the target's source may differ in the *tail expression* such that the packet chain ties differently. In the target disassembly, the packet chain is coalesced into a0 (as ours into v1). The allocation order: packet qty pri 24000 allocated first → takes $2 (v0)? But target has it in a0 ($4). So $2 and $3 were taken by other qtys at its live range.

At the packet qty's live range (positions 12-17), which other qtys overlap and are allocated first (higher priority)?
- r192/r191 qty: pri 26666 > 24000, live pos13-16. Allocated first → takes $2 (v0). Indeed r191 = v0 in both (the loaded D_800A6614 value). Good: `lw v0,0(at)`.
- Then packet qty (24000) → takes $3? In mine yes (v1). In target it took $4. So in the target, some other qty with pri >24000 and overlapping pos12-17 took $3.

What could take $3 in target? The oidx qty has pri 7142 (lower). Something else... Maybe in the reference, the oidx qty had a *copy suggestion* to a hard reg, or the reference's oidx qty priority was higher.

Alternatively, in the reference, the packet qty's live range was longer (lower priority). If the reference's packet chain had live > 7 with refs 6: 12/7=1.71 → 17142, below the r192 qty (26666) and possibly below a $3 taker.

Hmm. What else could take $3 in target? Let's list target's $3 users: oidx (v1) at 178-204. That's the oidx qty. So oidx took $3. For that, oidx's pri must be > packet's at allocation time, or oidx allocated earlier due to suggestions.

Reference oidx qty pri: refs? If the reference source had oidx tied only to otz load (refs 5) and live 14 → 7142. Packet 24000. Packet would win $3. Unless in the reference the packet chain did NOT tie into one qty (e.g., r182 didn't die at the and?).

Hmm wait, maybe in the reference the packet word load was NOT a separate pseudo tied to the and result, because combine merged `(mem & mask) | x` differently. Actually combine (the pass) runs before sched1 and can merge. In our body, combine didn't merge these (still separate insns). In the reference, maybe the RTL was identical.

I wonder if the reference's oidx qty had a *hard-reg copy suggestion* from a `move` — e.g., if the original source assigned `oidx` from a call result? No.

Alternatively, maybe the reference's $3 assignment comes from the *global* allocator: if oidx were live across a basic block, global-alloc would assign it. Is the tail block actually split? The `if (*(u16*)(pkt+0x16) & 0x10)` branch for w2 is before; the tail after is one block. But maybe the compiler's basic block boundaries put oidx in a global allocno? No, oidx defined after the branch.

Hmm, wait: look at the target disassembly at 174-177: `lw a0,0(a3); addu v0,v0,a2; lui a2,0xff00; sh v0,32(a3)`. Then 178 `lw v1,20(sp)`. In the reference, the packet word load (r182) is at 174 in a0 ($4). It was allocated $4. For that, at its live range, $2 and $3 were both busy with higher-priority qtys. $2 = r191 (loaded value, pri 26666). $3 = ? something with pri > 24000 overlapping pos12-17.

Candidates with pri > 24000 in our RTL: r192/r191 (26666). Any qty with refs 2, live 1 = 20000 (below). refs 4, live 2 = 4 → 40000? Let's compute other ties: r187 = ashift(r186,14), r186 dies → tie: refs 4, birth r186 pos8, death r187 pos11 → live 3 → 2*4/3 = 26666. That qty (r186+r187) overlaps pos12-17? No, dies at pos11.
r189 = plus(r84, r187), r187 dies → tie r189 into r84's qty! So the oidx qty absorbs r189 (the index sum). refs 5+2=7, birth pos5, death max(pos13 for r189's death? r189 used at insn 362 pos13, dies there). So oidx qty death = pos13? But r84 is used again at pos21 (insn 375). qty_death updates to the last use → pos21. refs 7, live 16 → floor_log2(7)*7/16 = 2*7/16 = 0.875 → 8750.
r198 = plus(r84, r197), r84 dies → tie r198 into r84's qty too! refs 7+2=9, death pos21 (r198's death later). So oidx qty refs 9, live 16 → floor_log2(9)*9/16 = 3*9/16 = 1.6875 → 16875.

Hmm, so the oidx qty = r181+r84+r189+r198? But wait, can r189 tie into r84's qty? r84 is used (ureg) in `set (r189) (plus (r84) (r187))`. r84 doesn't die there (used again later). combine_regs requires ureg die (`already_dead || find_regno_note(REG_DEAD, ureg)`). r84 doesn't die at insn 358. So no tie; instead a *suggestion* (qty_phys_sugg) maybe: if ureg is a pseudo and doesn't die, combine_regs returns 0 earlier? Let's see: after the pseudo-pseudo block, if not (already_dead||REG_DEAD), return 0. So no suggestion at all for non-dying pseudo-pseudo? Actually the earlier code only handles ureg hard or sreg hard. For pseudo-pseudo with ureg not dying → return 0. So no tie.

But r198 = plus(r84, r197) at insn 375, r84 dies there → tie r198 into r84's qty. refs 5+2=7, death pos21+? r198's death is at the next insn (379) beyond our window (store). So qty refs 7, live 16 → 8750.

OK so oidx qty ≈ 8750, packet qty 24000. Packet still wins.

In target, packet got $4. So in the reference, $3 was taken by a qty with pri > 24000 overlapping. What could it be? Perhaps the reference's r191 qty (loaded value) took $2, and another qty took $3. Maybe the reference had an extra qty from the `pkt[0xC]`/`pkt[0xD]` byte computations in the same block? Those are earlier.

Wait — actually the block boundary! The basic block might start before the div; many qtys. The packet chain's live range might overlap with earlier qtys allocated first.

Hmm, the sh stores at 160-177 use temps r180, r178, etc. Those are in the same block (the sh's after the div are in the tail block). E.g., r180 (pri 20000, live 2) etc. Some could take $3 and die before the packet chain's birth, so no conflict.

This is extremely intricate. Let me step back and consider that the target may simply have used a pin. But the task explicitly says the item was banked PARTIAL with pin kind, and my job is to remove it with real C moves. The shard may expect some WALLs.

Given the time budget, let me allocate: item 1 gets maybe 10 more minutes / 20 more tries, then record WALL with the best lever-free 13 if no crack. Then items 2-4 (twins).

But before giving up, let me try moves that directly target the qty tie: the packet chain qty is formed by ties at r182→r183→r194 (dying inputs). If I break one tie, the chain splits and priorities change. E.g., make the loaded word not die at the `and`: use it in a way that keeps it live (adds a use). Or prevent the tie by making the and result not tie to the load (different modes? no).

How to prevent r183 from tying into r182? The tie happens because r182 dies at the `and`. If r182 is used again later, it doesn't die there. Could we use the loaded packet word later? Not without changing code.

Alternatively break the r194 tie: make r183 not die at the or. If we store r183 to memory? no.

Hmm, but breaking ties raises priority usually (fewer refs? no, refs stay; live range of the smaller qty shorter). Actually splitting: r182 qty (refs2, live2 → 10000), r183 (refs2, live2 → 10000), r194 (refs2, live1 → 20000). Then the highest is r194 (20000) — still > oidx 8750. But then the coalescing would be lost (the disassembly would use different regs for and/or → mismatch).

What if we lengthen the packet chain's live range so its priority drops below oidx's? The chain's death is the store. If the store happens later... source order: after the packet store there's the otp block. If we move the packet store to AFTER the otp store, the chain's live extends. But then instruction order changes (target: packet store at 193, otp at 209). Hmm, but maybe sched1 keeps the original source order and it wouldn't match.

What if we lengthen the *birth* by loading the packet word earlier? We tried a5 (early load with (void)pw0) — that added a separate dead load (probably deleted). Let me instead load it into a variable used in the store expression, placed early:
```
u32 pw = *(u32*)pkt;  // right after pkt advance
...
*(u32*)pkt = (pw & 0xFF000000) | ...;
```
This keeps the load early in source; sched1 might keep it early → the chain's live from early position to store. That could lower its priority below oidx's. But the disassembly would have `lw` early (target has it at 174, after the sh's at 160-173). Since sched1 hoisted it to 174 in the original (source position after sh's? Actually the source has the packet store after all the sh's, yet sched1 moved the load up to 174, interleaved). If placed before the sh's, sched1 might keep it at the very start → mismatch (score up).

Let me just try it and see the score. a5 was a dummy dead load; let me do a real early load variable.

Also try: put the packet store BEFORE the sh stores? no.

Let me also try: extend the chain's death by moving the store later (after otp store) — test.

Let me generate b1 (early real load), b2 (store moved after otp), b3 (split ties: use a separate var for the and result and the or result), b4 (make r182 live by reusing pw in the otp store as an unused operand? no).

Also b5: make oidx's qty refs higher by adding a tie: use `oidx` as a dying input in another expression, e.g., compute `oidx2 = oidx + 0;`? That's an identity launder (not allowed) and adds a move.

Hmm what about `oidx = g.otz << 2;` then use `oidx` in both addresses and also in a `do{}while(0)`? no refs.

Let me try b1/b2 and a few.
