---
ts: 2026-11-06T05:04:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kCdzxHAWrQ5Mw85uwjxu
---
r1: a1 (r73) refs 8 (up from 7 by 1) → pri 5000 > base 3181. So the do-while around the if added +1 ref to a1. Why? Because a1 is live across the loop and loop.c counts a "use" of a live-across register? Actually flow.c's loop weighting: `REG_N_REFS` is incremented for each insn in the loop that references the reg, and for registers live across the loop, `REG_N_REFS` might get +1 at the loop.

Hmm. In any case, any do-while increases a1's refs by 1 (one per loop? r1 has 3 do-whiles but only +1 ref... interesting; t2 has +3 for 3 do-whiles).

Wait, r1 has 3 do-while loops (lines 6,13,17) and a1 refs 7→8 (+1). t2 has 3 do-whiles around the stores and +3.

Hmm. So the loop weighting for a1: in r1, the loops don't contain a1 uses, but a1 is live across them; flow's `REG_N_REFS += loop_depth` might apply to regs live across the loop boundary... +1 per *loop*? But 3 loops → +1 only.

Anyway, we need a1 refs = 7 (pri 2916 < 3181). 

Alternative: raise base's priority above a1's without changing a1: base needs refs/live. Base has 14 refs, live 132. To exceed 5000, we'd need live_length ~89 or refs ~20.

Hmm, or lower a1's priority: a1 refs 7, live 48 → 2916. To be below base's 3181, that's already the case in v1.

So the cleanest is to avoid adding refs to a1. What block-splitter doesn't add refs? 

Idea: use a `do { ... } while (0)` that contains *no* live-across registers? Impossible, a1 is live across.

Idea: instead of a do-while, split the block with a `goto`/label? That adds a jump.

Idea: use the C0535 trick but *reduce* a1's refs elsewhere to compensate. E.g., a1's refs come from `D_80078EA4 += a1` (3 uses) and `*(s32*)(base+0x60) += a1` (3 uses) and `move s1,a1`. That's 7. If we could make one use count less... 

Hmm, what if we use `a1` directly vs a copy? The target has `move s1,a1` (a copy). If we use a1 directly, the copy disappears. Not allowed (the target has the copy).

What about the priority formula's `allocno_size`: pri *= allocno_size. allocno_size is the mode size (4 for SImode). All are SImode. No help.

Alternative: make base's live_length smaller while keeping its definition at the top? live_length = the number of insns between the first and last use (in the allocation sense, counting instructions the pseudo is live across). Base is defined at the top and used in the second half. Can't change without changing the code... 

Wait, actually: can we change base's *definition order*? The target's prologue:
```
sw s1,20(sp)
move s1,a1
sw s2,24(sp)
move s2,a2
sw s0,16(sp)
lui s0,0x0
addiu s0,s0,0
beqz s2,...
sw ra,28(sp)
```
So base (s0) is set up at the top, before the branch. The order of moves: s1=a1 first, then s2=a2, then s0=base. Interesting: the allocation/order.

Hmm, what if we make base live shorter by re-deriving it? E.g., use `D_80078E78` directly instead of a base pointer in some places? That changes the code (reloc).

OK, let me think differently: maybe use a do-while that wraps a block NOT containing any use of a1 AND where a1 is NOT live across. Is there such a block? a1 is live throughout (used in all 6 blocks). Hmm.

What if we reorder the code so the do-while is around a block before a1's first use? a1 is used from block 1.

Alternatively, use a different splitting mechanism that doesn't create a loop: **a `switch`?** No.

What about `if (0) { }`? No.

What about declaring a local `volatile`? lever.

Hmm, what about `__builtin_...`? no.

Let me reconsider: maybe the +1 ref in r1 is tolerable if we *also* reduce a1's refs by 1. Could we write one of the a1 uses in a way that doesn't count as a ref? E.g., the last use `*(s32 *)(base + 0x60) += a1` — what if we use `a1` in a different mode? No.

What if we *drop* the `move s1,a1` copy by using a1 directly, and compensate? The target requires the copy (s1 = a1). If a1 were used directly, the register would be a1 (not s1) — mismatch.

Hmm, what if we introduce a *different* register (say a0) with more refs to take s0 instead? The s-register assignment: s0 is given to the highest priority. If some other pseudo (e.g., a0) had a priority between base and a1... no, we need base to get s0 and a1 s1.

Wait, maybe I have the assignment direction wrong. In v1: base→s0, a1→s1, with base pri 3181 > a1 2916. So higher pri → s0. In t2: a1 pri 6000 → s0, base 3088 → s1. Yes.

So we need base's pri > a1's pri. Currently (t2): base 3088, a1 6000. We need a1 ≤ 3088 or base > 6000.

If we can get a1's refs to 7 while keeping the do-while: pri 2916 < 3088 ✓.

How does the do-while add refs? flow.c: for each loop, `REG_N_REFS (i) += REG_N_REFS (i) * loop_depth`? Let me look at flow.c's loop weighting. In flow.c (2.7.2), `regs_live_at`... The function `flow_loop_tree_node_add` / `count_reg_sets`? Let me grep "loop_depth" in flow.c.

Actually, in 2.7.2 flow.c there's:
```
/* If the register is used within the loop, ... */
REG_N_REFS (regno) += loop_depth;
```
inside `mark_regs_live_at_end`? Hmm. Let me grep.

The key: the +1 ref per loop for registers live across the loop. If so, each do-while adds +1 to a1 (live across). t2 had 3 do-whiles → +3 (7→10). r1 had 3 do-whiles → +1 (7→8)? That contradicts. Unless the loops are nested/merged.

Hmm, t2 wrapped the stores; r1 wrapped the ifs. Maybe r1's 3 ifs are in a different block structure so only one loop note survived.

Whatever. Let me try: a single do-while somewhere that fixes all three blocks? No — each block needs its own boundary.

Alternative approach: maybe I can fix the ordering in blocks 1 and 2 with a *different* mechanism that doesn't add refs, and only use the do-while in block 3 (where the reload is needed).

Hmm, what about the *inner* do-while (site 20)? s3 = 55/107: only the inner if wrapped. Let me check s3's alloc: if it doesn't add a1 refs, then combining s3 with something else...

Actually, let me reconsider the problem: maybe I should approach the register allocation directly. The target has base=14 refs, live=132 (in v1's table, matching). The target (with asm) has 114 insns, so base's live_length would be larger (~140), lowering its priority further. Hmm, but the target still gives base s0.

Wait — maybe in the target, a1's refs are *higher* than base's because the asm adds refs to a1? No, the asm doesn't reference a1.

Let me compute the target's priorities. The target's alloc table isn't available (we only have the built object). Hmm.

But the target: a1→s1, base→s0. If higher pri → s0, then base > a1 in the target. With the asm, base's live_length is longer (114 vs 107 insns) → priority lower, not higher. So how did base beat a1 in the target?

Unless a1's live_length also grew. a1 is live from the top to the last use. With 7 extra insns (the asm), both grow. Hmm.

Wait, maybe in the target a1's refs are 7 and base's 14, with live lengths such that base > a1. Our v1 has base 3181 > a1 2916 — consistent with the target! So in v1 (no do-while), the allocation already matches the target. The do-while broke it.

So I need a block splitter that doesn't change the refs. 

Idea: **a label + goto that produces no code**: In C, `goto` to a label immediately following creates a CODE_LABEL that splits the basic block. If the goto is redundant, gcc's jump optimization removes it AND the label. But what if the label is used by a *branch that's already there*? Hmm.

Idea: **`switch (0) { case 0: ... }`**? Adds code.

Idea: **an empty `if` with a `do-while`**? no.

Idea: Use a `do-while(0)` but *counteract* the +1 ref by removing a ref elsewhere. Which refs of a1 are there? 7 = 1 (move s1,a1) + 6 (addu). If we could make one of the 6 `addu v0,v0,s1` use a different expression that doesn't count as a separate ref... e.g., combine two uses? No.

Hmm, what about making a1's live_length longer to lower its priority? If we use a1 somewhere earlier... it's already at the top. Or make it live longer by using it at the very end (after the second half)? That would add an instruction (dead use) — but maybe a dead use gets eliminated. E.g., `if (a1 == 0x12345) return;`? adds code.

Alternatively, raise base's priority: base refs 14 → 15 would give pri = floor_log2(15)*15/live = 3*15/136 = 0.3308 → 3308 > a1's? a1 in t2 is 6000, no.

Hmm. So the do-while's +3 refs on a1 is the problem. Let me look for a block-splitter that doesn't add refs.

What about `do { } while (0)` placed so that a1 is NOT live across it? If the do-while is at the very end of a block after a1's last use in that block, a1 is still live across (it's used later in the function).

Hmm, what if we *reorder* the source so that a1's uses are all before the do-whiles? a1 is used in all 6 blocks, interleaved.

Alternative: **use a separate scope block `{ }`**? Doesn't create a boundary in RTL.

What about a `;` empty statement? No.

Hmm, let me look at flow.c's loop weighting to understand exactly what adds refs. Maybe only registers *used* inside the loop get +1, and the +3 in t2 is because a1 is used in all 3 loops. In r1, the if bodies don't use a1, yet +1 appeared... Maybe because the if body contains `D_80078EA4 = 0xA00000` and the *loop* is entered... hmm.

Wait, r1's do-whiles: the third one wraps the inner if (line 20? no, r1 wrapped {6,13,17} — the outer ifs at lines 7,14,18). Let me recheck: the grep showed ifs at lines 7,14,18,21 (1-based) → 0-based 6,13,17,20. r1 wrapped {6,13,17} = the three outer ifs. The bodies contain D_80078EA4 stores, no a1.

But r1's a1 refs = 8 (+1). Hmm, maybe the +1 comes from `flow`'s `REG_N_REFS += loop_depth` for regs live at the loop end? Let me grep flow.c.

Actually, maybe the refs change isn't from loop weighting but from `reg_used_between_p`... Let me check flow.c's `REG_N_REFS`.
