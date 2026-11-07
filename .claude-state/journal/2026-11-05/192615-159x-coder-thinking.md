---
ts: 2026-11-06T02:26:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DwYAejCchSv2jHURssqg
---
Confirmed: mine at a80 has `addiu v0,a0,1` in the bnez delay slot; target has nop. Everything else matches (the branch targets shift by 4 due to the missing nop).

Real-C moves to prevent reorg from filling the delay slot with the addiu:
1. Make the addiu depend on the branch: e.g., the value stored could be computed from something that's only available after the branch — but it's `state + 1` where state = unk34 loaded before.
2. Reorder the statements inside the if so that the first insn after the branch is not the addiu but something reorg won't steal. The target's first insn after the branch is `addiu v0,a0+1; sh v0,52(s0)` (the store of unk34 = state+1). Wait, the target at a84: addiu v0,a0,1; a88: sh v0,52(s0). So the target's code after the nop is exactly the addiu. So the target's delay slot is nop because reorg couldn't steal the addiu — why? The addiu is a computation whose result is used by the next insn (sh). reorg's fill_simple can steal a computation into the delay slot if it's safe (the value isn't needed on the branch path). Here the branch goes to b3c (the epilogue), and the addiu's result is only used by the sh on the fall-through. Stealing the addiu into the delay slot executes it on BOTH paths — but since it's just `addiu v0,a0,1` (no side effects), it's safe; the value is dead on the branch path. So reorg steals it. In the target, it didn't — why? Maybe because in the target, the value in v0 is... hmm, a0 is the loaded state (lhu a0,52(s0)) — a0 is dead after? reorg checks register liveness: stealing the addiu means v0 is set on the branch path where it's not needed; fine.

The barrier (asm memory clobber) sat between the bnez and the addiu, so reorg couldn't reach the addiu.

Lever-free ways: make the addiu not stealable, e.g.:
- The addiu's source (a0 = state) must be live on the branch path? If a0 is used after the branch (on the branch path), stealing the addiu is still fine (it doesn't clobber a0). 
- Make the insn after the branch a store instead of a computation? The target has the addiu immediately after the branch (after the nop), so the first insn IS the addiu.
- reorg's fill_simple_delay_slots scans forward from the branch for candidate insns: it can steal an insn from the fall-through if it's a "simple" insn that can be executed unconditionally. Conditions: not a jump, not a store to memory (can't move stores before a branch? it can if safe), the registers must be dead on the branch path, etc.
- The known wall tag: `dbr-delay-fill` (line 53, 116, 126, 129 in moves.md). Many WALLs. So this is likely a WALL too.

But maybe there's a C shape: make the addiu's destination v0 conflict with something live on the branch path. The branch goes to the epilogue (b3c), where the epilogue uses v0? The epilogue: lw ra; lw s0; addiu sp; jr ra; nop. v0 is not used. Hmm, but if the function returned a value... it's void.

What if the addiu's dest were a register that's live on the branch path (e.g., a1)? Then reorg can't steal (it would clobber). But the target has v0.

Alternative: make the stolen insn unsafe because the branch target uses the value: e.g., if the epilogue's first insn were `lw v0,...`? no.

Hmm, what about making the addiu *depend on the branch* (i.e., its source is only available on the fall-through path)? The addiu's source is a0 = state, available on both.

What if we change the code so the insn after the branch is a *load* from memory that could fault? reorg doesn't steal potentially trapping insns? Actually it can steal loads if safe (may_trap_p). The target's next insn after the nop is the addiu, so no.

What if the insn after the branch is the store `sh v0,52(s0)` and the addiu comes later? Target order: addiu; sh. If the source order were `unk34 = state+1` computed as `state+1` in the store directly (no temp), the compiler emits addiu+sh anyway.

What about computing `state + 1` from `unk34` reload: `((Unk*)s0)->unk34 = ((Unk*)s0)->unk34 + 1;` → lhu; addiu; sh? The target uses the cached a0. Hmm.

The wall tag `dbr-delay-fill` says "reorg steals ... into the ... branch slot (target nop)". Given the moves.md has several such WALLs, this item is likely a WALL too. But the brief wants a lever-free body scoring 0; if not, WALL with best.

Let me try a few cheap real-C variants:
1. `((Unk*)s0)->unk34 = state + 1;` with the addiu computed via `state + 1` (already).
2. Reorder: put the two calls before the store? No, target order is store, then calls.
3. Make the addiu's result used in a way that requires the fall-through: e.g., `((Unk*)s0)->unk34 = state + 1;` — the store uses it.
4. Use a different register: `u16 ns = state + 1; ... unk34 = ns;` — the addiu dest may be a different reg (still stolen).
5. Add a dependency: compute the stored value from the *stored* field: `((Unk*)s0)->unk34 = ((Unk*)s0)->unk34 + 1;` → the compiler may reload unk34 (lhu) after the branch, making the first insn a load which reorg... could still steal.
6. Make the addiu depend on a value that's only defined on the fall-through path: e.g., `if (unk98 == 0) { ...; }` — the addiu uses state (defined before). Hmm.
7. Use `state` after the branch in a way that prevents... no.

Actually, the classic trick to stop dbr stealing: make the candidate insn's destination register live at the branch target (the epilogue). The epilogue uses ra, s0, sp. v0 is not. If we could make the addiu write s0 or ra... no.

Another classic: put the addiu in a place where it's not the first insn after the branch — e.g., make the first insn after the branch a store (stores are not stolen if they might alias? reorg can steal stores only if safe). Target's first insn after the branch is the addiu, so no.

Another: make the addiu's source register die at the branch? no.

What if the value stored is `state + 1` where state is a *u16* local and the addiu is 32-bit; the target uses a0 (the loaded state). Fine.

Hmm, what about the possibility that the target's nop is not a delay slot but an alignment? It's right after bnez, so it's the delay slot.

Given the moves.md `dbr-delay-fill` walls, and the score is only 8 with one missing nop, this is a classic WALL. But let me try ~10 variants quickly. Budget: I have ~4 items and limited time; item 1 took too long. Let me aim for ~15-20 min per item now.

Variants for item 2 (case 0):
a) `((Unk*)s0)->unk34 = state + 1;` (same as orig minus barrier) — nopin, 8.
b) reload: `((Unk*)s0)->unk34 += 1;` or `= ((Unk*)s0)->unk34 + 1;`
c) compute ns from the lhu with a temp: `u16 ns; ns = state + 1; unk34 = ns;`
d) reorder: move the unk34 store AFTER the calls? Target order says store first.
e) use `state++`? `state = state + 1; unk34 = state;`
f) make the branch condition use a different expression so the first insn after is a load: `if (((Unk*)s0)->unk98 == 0)` already.
g) insert a do-while around the if body? do { ... } while (0) — could change the block structure and prevent dbr? The barrier is inside the if body, after the test. A do-while wrapping the body might make the bnez target different.
h) use a goto: `if (unk98 != 0) goto skip; ...; skip: ;` — changes structure.
i) `if (unk98 == 0) { ... } else { }`?
j) Add a `volatile`? lever, not allowed.
k) Make the store `s16`/`u16` cast variants.

Also: the wall mechanism says reorg steals the addiu because it's safe. To make it unsafe, the addiu's dest must be live at the branch target. What if the branch target (epilogue) uses v0 because the function returns a value? The function is void. Hmm.

What if we make the addiu write to `a0` (state) instead of v0? `state = state + 1;` then `unk34 = state;` — the addiu dest would be a0 or v0. If it writes a0 and a0 is live at the branch target... a0 isn't used in the epilogue. Hmm.

What if the addiu's source is `s0` (used in the epilogue!): e.g., `((Unk*)s0)->unk34 = (s0 & 0) + state + 1;` silly.

Reorg's fill_simple steals an insn only if the registers it sets are dead after the branch AND the insn can't trap. If the addiu's dest were s0 (live at the epilogue), it couldn't steal. But the target's addiu dest is v0.

So the target's nop must come from something else: maybe reorg didn't steal because the insn after the branch was NOT stealable for a structural reason — e.g., it was a jump target (a label)! If a label sits between the branch and the addiu, reorg's scan stops at the label (it can't move an insn that's a branch target into the delay slot). YES! That's a classic real-C lever: the addiu is a branch target (some other branch jumps to it), so reorg won't steal it.

In the target, is a84 (the addiu) a branch target? Looking at the target asm: branches to b3c, b0c, ab0, a60, a74, b08... none to a84. Hmm, a84 is not a target in the final asm. But at RTL time it could have been, with the label later optimized away? If a label is at a84, the branch to it must exist. In the target, no branch targets a84. So no.

Hmm. What else stops reorg's fill? Let me read reorg.c's fill_simple_delay_slots conditions. The relevant: `stop_search_p`, `resources_scheduled`, `eligible_for_delay`, `insn_references_resource_p`, `sets_cc0_p`, and `! insn_is_jump`. For MIPS, a simple addiu is eligible. The scan looks BACKWARD from the jump? For a conditional branch, the delay slot is filled from the insns BEFORE the branch? No — for a branch, the delay slot can be filled by an insn from the *target* (fill_slots_from_thread) or by the fall-through? Hmm: the delay slot is the insn right after the branch, which executes before the branch. The code after the branch in the instruction stream IS the delay slot position. To fill it, reorg moves an insn from... the target path? Actually for a conditional branch, reorg's `fill_simple_delay_slots` handles the fall-through: it tries to fill the delay slot with an insn from the fall-through path that is safe to execute when the branch is taken. The insn right after the branch is already the fall-through's first insn; moving it into the delay slot = same position! Since the delay slot IS the position right after the branch, filling it with the fall-through's first insn means that insn executes regardless. Reorg moves it from after the branch into the slot — but physically they're the same place. Hmm, no: the delay slot is a distinct slot; the fall-through's first insn is at the address after the branch+slot. So reorg moves it up one.

In the target, the delay slot is nop and the addiu is after. Why didn't reorg move it? Because moving it would make it execute on the branch-taken path. Safe if its dest is dead there. v0's liveness at the branch target (b3c = epilogue): the epilogue doesn't use v0, so v0 is dead → safe. Unless reorg sees a USE of v0 somewhere. 

Hmm, what if the epilogue's `jr ra` is preceded by... no.

Maybe reorg's decision is based on the *resources*: the branch and the addiu? No.

Maybe the reason is that in the target, the addiu's dest is used by the store which is also after — moving the addiu doesn't break that.

Alternatively, maybe the target's nop comes from the *second* pass of reorg or from a different structure: e.g., the addiu couldn't be stolen because the insn after the branch in RTL was a NOTE/label? 

Hmm, wait: maybe in the target's RTL, the insn right after the bnez was NOT the addiu but something else (e.g., the `li a0,0x948` or a `move`). Reorg would steal that one if safe, else nop. Let me think: the target's fall-through after the branch: addiu v0,a0,1; sh v0,52(s0); li a0,0x948; jal; move a1,zero; li a0,0x383; move a1,zero; jal; move a2,s0; j; nop.

Reorg's fill for the bnez at a7c: it scans forward from the branch for an insn to move into the slot. It considers the first few insns of the fall-through (up to some limit) and picks one whose registers are safe. The addiu is the first candidate. It didn't take it in the target. Why? Because its dest v0 is live at the branch target? Let's check: the branch target b3c is the epilogue; the epilogue code at b3c: lw ra,20(sp); lw s0,16(sp); addiu sp,sp,24; jr ra; nop. v0 not used. So dead.

Unless reorg's `fill_simple_delay_slots` for a *forward* branch uses `fill_slots_from_thread` from the target path and doesn't steal from the fall-through when... Hmm.

Let me look at reorg.c's logic for conditional jumps (fill_simple_delay_slots): it processes insns and for a JUMP_INSN, `fill_slots_from_thread(insn, condition, fallthrough, ..., 1)` and `fill_slots_from_thread(insn, condition, target, ..., 0)`; then if not filled, `fill_simple_delay_slots` tries the fall-through insns after the jump: it scans `next_trial = next_nonnote_insn (insn)` (the delay slot region) etc. There's a notion of "eligible_for_delay" and "delete_from_delay_slot". 

In the target, the nop suggests reorg tried but failed. A common reason: the candidate insn sets a register that's live on the taken path; or the candidate is a store that might alias; or the branch's condition register is clobbered by the candidate.

The addiu sets v0. The branch condition is v0! `bnez v0, b3c` uses v0 as the condition. The addiu sets v0 = a0+1. If moved into the delay slot, it executes BEFORE the branch resolves... wait, the delay slot executes after the branch is fetched but the branch condition was already computed. On MIPS, the delay slot instruction executes regardless; the branch condition is evaluated at the branch. So setting v0 in the delay slot is fine for the branch itself, but the value of v0 at the target changes. If v0 is live at the target → unsafe. It's not.

Hmm, but reorg has a specific check: it won't put an insn in the delay slot if it sets a register used by the branch's condition? Actually the branch condition is already in the register; the branch insn reads v0 at issue; the delay slot executes after. So no hazard.

Hmm.

Let me look at the actual dbr dump of the nopin to see why reorg filled it. Then try to find a C shape. Let me dump the dbr pass for nopin (correct scratch dir p4).

Actually, time. Let me try the cheap variants first and score them. If one hits 0, great.

Variants:
b1: `((Unk*)s0)->unk34 = ((Unk*)s0)->unk34 + 1;` (reload)
b2: `state = state + 1; ((Unk*)s0)->unk34 = state;`
b3: `((Unk*)s0)->unk34 = (u16)(state + 1);`
b4: do-while around the if body
b5: goto-skip structure: `if (unk98 != 0) goto skip0; ... skip0: ;`
b6: move the store after the first call? (target order would break)
b7: `u16 ns = state + 1; ... unk34 = ns;`
b8: make the addiu's dest different by using `s32` state: `s32 st = state; unk34 = st + 1;`
b9: `((Unk*)s0)->unk34++;` (post-increment)
b10: reorder the if body: put the unk34 store after `func_8002D4C8(0x948,0)`? target order says store first, but the delay slot fill might change.

Let me score b1-b10.
