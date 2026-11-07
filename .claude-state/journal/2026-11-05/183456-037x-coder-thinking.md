---
ts: 2026-11-06T01:34:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L8bHDQ0E7g7xF2GV9itr
---
So the first call (minimum=1) compares the jump insn's preceding insns with those preceding the target label. In mine, at whatever pass, the label before is zero's sw. In target, apparently the match fails. The difference must be the *pseudo identity* at the pre-reload pass, OR the post-reload pass where the target's insns differ.

Which pass produced the merge? Since the comment in src says "find_cross_jump merges this block's trailing sw with the identical one ending the dec: block", and the barrier is a zero-byte asm insn, which only affects passes where insns exist (pre-reload jump passes too). The asm is a NOTE_INSN? `__asm__ __volatile__("")` with no operands emits a `(insn (asm_operands ...))` — a real insn with empty template? Actually an empty asm with no operands: gcc might emit nothing (no insn) or emit an ASM_INPUT note. For volatile empty asm, gcc 2.7.2 emits `(note (asm_operands))`? Hmm, in old gcc, `asm("")` without operands and volatile produces a `NOTE_INSN_ASM`? Let's check: in gcc 2.7.2, an asm with no operands produces `gen_rtx (ASM_INPUT, VOIDmode, "")` inside an insn? If it produces no insn, the barrier works via... the coder's note says zero-byte barrier. In expand_asm_operands, if no outputs and no inputs, it emits `emit_insn (gen_rtx (ASM_INPUT, VOIDmode, ""))`? Hmm, actually for empty asm with no operands, gcc 2.7.2 emits nothing but creates a `NOTE_INSN_...`? The barrier effect: prev_nonnote_insn skips notes, so a NOTE wouldn't be a barrier. But it does work as a barrier per the comment. Perhaps it emits an `(insn (asm_input))` which is a real insn that prev_nonnote_insn sees, and it's removed later by... the "empty asm" optimization? In final, an ASM_INPUT with empty template emits nothing, so it's zero-byte.

Actually in gcc 2.7.2, expand_asm_operands: "If there are no operands and no outputs, ... emit nothing"? Let me not go down this hole. The key is the merge pass.

If the merge is pre-reload, rtx_equal_p requires the same pseudo. Let's test by experiment: variants that change the pseudo in zero.

Actually, the simplest empirical approach: try a batch of candidate bodies with sc.sh and see scores. Let me write ~8 variants quickly.

Variants for item 1 (barrier at end of zero):
v1: `t = 0x1D; ((Unk*)a0)->unk1C = t;` (t declared s32)
v2: `do { ((Unk*)a0)->unk1C = 0x1D; } while (0);`
v3: swap sh/sw order (test)
v4: `r = 0x1D; ((Unk*)a0)->unk1C = r;` and use r? no.
v5: make the zero store's value come from a helper expression: `((Unk*)a0)->unk1C = 0x1D + 0;`
v6: use u32 cast: `*(u32*)&((Unk*)a0)->unk1C = 0x1D;`
v7: restructure dec to `unk1C = unk1C - 1;` vs `--unk1C;` (same)
v8: move the `sh zero,244` store after? 

Let me also consider: target's zero block tail order li; sh; sw. What if in source we write the sh after the sw but the compiler's scheduler reorders? No, sched1 could reorder stores? Stores to different addresses could reorder. Hmm, sched1 might reorder independent stores. Target has sh before sw. If we write sw then sh, sched1 might keep order.

Better idea: the real source might have the assignment order: `unk1C = 0x1D;` then `sh zero,244`? No.

Let me think about the pseudo-identity theory more concretely. Pre-reload RTL for zero block:
(set (reg P_li) (const 29))
(set (mem (plus (reg s0) 244)) (const 0))
(set (mem (plus (reg s0) 28)) (reg P_li))

dec block:
(set (reg P_lw) (mem (plus (reg s0) 28)))
(set (reg P_add) (plus (reg P_lw) (const -1)))
(jump)
and the store? In target dec, store is after jump (delay slot) but pre-reload it's before the jump:
(set (mem (plus s0 28)) (reg P_add))
(jump_insn)

Hmm, so pre-reload, dec's store is (mem..) <- P_add and zero's <- P_li. Different pseudos → rtx_equal_p false. So no pre-reload merge. Hence the merge is post-reload jump2, where both are `sw v0,28(s0)` and reg_renumber set → match.

But wait: post-reload, the delay slot insns are separate insns after the jump? At jump2 (after reload, before reorg), the jump insn and its delay slot are still separate insns; the delay slot is the insn following the jump. So dec block: lw; nop; addiu; sw; j; (delay slot empty or filled later). prev_nonnote_insn(jump) = sw. Label prev = zero's sw. Both `sw v0,28(s0)` → match, minimum 1 satisfied → merge. Then reorg fills dec's new j delay slot with addiu (since after merge the addiu is in the delay slot region? Actually do_cross_jump moves things).

In the target, the merge did NOT happen at jump2 either. So the target's insns at jump2 must differ: maybe zero's store is `sw v0,28(s0)` and dec's is `sw v0,28(s0)`... identical. Contradiction. Unless the target's jump2 pass saw a different order: maybe in the target, the epilogue label's preceding insn at jump2 time was NOT the sw (e.g., because the epilogue block was laid out elsewhere or the sw was in a different block).

Alternatively, maybe the target's dec block ends with the store as a *delay slot already* at jump2? No, delay slots are filled by reorg after jump2.

Hmm, but maybe jump2 (the post-reload jump pass) has `cross_jump` disabled? Let me check toplev.c: the jump2 pass might run with cross_jump off? Let me check where jump_optimize is called with what. Actually there's a variable `cross_jump` set by flag. Let me grep toplev.c for jump_optimize.
