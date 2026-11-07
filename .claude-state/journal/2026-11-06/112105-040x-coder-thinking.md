---
ts: 2026-11-06T18:21:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NgvmrHtHAqrq5WmxmtIX
---
Interesting! The .lreg dump shows REG_DEAD (reg/v:SI 72) at insn 32, and the jump at 34 goes to label 58 (not 45 as in .rtl). So jump/jump2/cse restructured: block A now jumps directly to the store block 58. And 72 is marked dead at insn 32!

But 72 is used at insns 40 and 53 too (in other blocks). That's fine: REG_DEAD at insn 32 means "dies here in this path"? No — REG_DEAD is per-insn, but 72 is live in blocks 3 and 4 too. GCC's flow computed per-block liveness; the REG_DEAD at insn 32 says 72 is dead after 32... but it's used later in other blocks. That's contradictory unless the CFG changed: maybe blocks 2,3,4 are exclusive branches (they are!). Block A (insn 29-34) jumps to 58. Blocks 2,3,4 are the arms: block 2 = insn 29-34? Let me map: block 2: 29-34; block 3: 36-47; block 4: 49-56; block 5: 58-61.

So the three arms are blocks 2,3,4, all reaching block 5. Each uses 72 and sets 76. Since the arms are exclusive, 72 "dies" at each arm's load (in that path) — but for the *last* arm... Hmm, actually 72 is live at the start of blocks 3 and 4 (as shown: "Registers live at start: 29 30 72"). At insn 32, why REG_DEAD? Because within block 2, 72 dies at 32 (it's not used later in block 2), and since block 2's successors (block 5) don't use 72, flow adds REG_DEAD at 32. But 72 is live in blocks 3,4 via the branch structure — those are different paths, and flow handles liveness per block; a REG_DEAD in block 2 is valid because 72 isn't live-out of block 2. Yes! Liveness: at block 2's end, 72 is dead (block 5 doesn't use it). So REG_DEAD at 32 is correct.

So at insn 32: REG_DEAD(72), and mark_reg_store(76) records conflict with live regs (72 was just marked dead → not live) → no conflict between 72 and 76. That's why. And expand_preferences merges 72's pref {4} into 76.

Now, in block 3 (insn 40): same pattern? Let me look further: does insn 40 have REG_DEAD 72? Block 3: 36-47: insn 40 load, 43 v0=2, jump 45... wait block 3 is 36-47, block 4 is 49-56. Let me see the rest of the .lreg dump.

Key insight: at each load, 72 dies (per-block) → 76's allocno gets pref 4 merged from 72 at that insn. Hmm, but 72 is ONE allocno with global prefs {4}; 76 gets it via expand_preferences.

Now how to prevent this? Make 72 and 76 CONFLICT. They conflict if 72 is live at the point 76 is born. 72 is live-out of block 2? No. If we make 72 live after the load in the same block (a use of a0 after the load in the same block), then 72 would be live-out (or at least live past the store) → conflict with 76 → prefs not merged → 76 gets $3.

Can we add a use of a0 after the load in the same block with zero extra instructions? The store `*(s32 *)(v1 + 0xB0) = v0` is in block 5, not the same block. Hmm, but what if the store were in each arm? No, target has a shared store.

Alternative: make 72 live-out of the arm blocks by using a0 in block 5 (the store block). E.g., the store address could involve a0... but the store is `sw v0,176(v1)`. If we wrote the store as `*(s32 *)((char*)v1 + 0xB0) = v0` — no a0.

What if the value stored uses a0? No.

What if we restructure so 72's last use is NOT at the load but after, in the same block? The load's base use IS the last use in each arm.

Hmm — what about making the load address expression use a0 twice? e.g., `v1 = *(s32 *)((char*)a0 + (s32)((char*)a0 - (char*)a0) + 0xCC)` — an identity launder; forbidden.

Alternative: make 76's birth not at the load but at a copy in a block where 72 is live? Hmm.

Alternative: kill 72's pref by making 72 conflict with $4? 72 IS $4 itself.

Alternative: make expand_preferences not merge: it requires `reg_allocno[REGNO(dead)] >= 0` (72 is global) and no conflict. If 72 were NOT a global allocno (i.e., block-local), the merge wouldn't happen. 72 is global because it's live in multiple blocks. Could we make a0's uses all in ONE block? The three arms... if the loads used a single shared variable loaded once... no.

Alternative: make 76 not global (block-local) so local-alloc handles it? 76 is live from the arms into block 5, so global.

Alternative: change 76's *priority* so it's allocated after 72? If 72 were allocated first: order 75 76 72 74. 72's pri is 8000, 76's 10000. If 76's pri dropped below 72's (e.g., longer live length), then 72 would be allocated first → 72 takes $4 (pref) → then 76: pref 4 is now conflicted? 76's conflicts include hard reg 4? If 72 is allocated $4 and 76 doesn't conflict with 72... but then find_reg for 76: pref 4 is in `hard_reg_conflicts[76]`? No: hard_reg_conflicts gets updated after each allocation: "For each other pseudo-reg conflicting with this one, mark it as conflicting with the hard regs this one occupies." 76 doesn't conflict with 72, so $4 is not added to 76's conflicts. But `regs_used_so_far` — find_reg checks if the preferred reg is already used by a non-conflicting allocno? Let me check find_reg's logic: it checks `hard_reg_conflicts[allocno]` and also `regs_someone_prefers`. Hmm, if 72 took $4 and 76 prefers $4 and doesn't conflict, find_reg might still give $4 to 76 (they don't conflict) — which is fine? No! Target needs 76 in $3.

Hmm.

Alternative: make the pref point to $3 instead of $4. The pref comes from the param copy `(set 72 (reg 4 a0))` → 72 prefers $4. If the param were not a0... can't change the signature.

Hmm, what if we make the a0 copy 72 die before the load (its REG_DEAD) but ALSO have another allocno with pref $3 merged in? expand_preferences merges prefs from ALL dies at the setting insn. If at insn 32 there were a REG_DEAD of a pseudo preferring $3, 76 would get both 4 and 3. Then find_reg's preference order? It uses `reg_preferred_class` and the pref bit set; find_reg iterates reg_alloc_order and checks `TEST_HARD_REG_BIT (allocno_pref, regno)`? Let me read find_reg to see how prefs are used — maybe the pref is only a tie-breaker and the lowest-numbered pref wins.

Actually in find_reg, the loop goes over reg_alloc_order and takes the first free reg; but there's logic: "if the register is preferred, give it a boost". Let me read find_reg.
