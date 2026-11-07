---
ts: 2026-11-06T20:12:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SbBlcY82vx5UyL6dFcNm
---
vD: "Loop from 60 to 152: 28 real insns" — the loop *range* grew by 3 insns (152 vs 149) but "28 real insns" stayed? Hmm, the dead store was inside the loop (range 60-152) yet real insns still 28? That means the dead store insn wasn't counted... or it replaced something. Wait vA: 60-149, 28 real. vD: 60-152, 28 real. The range end moved 3 insns later but real count same — the dead store may have been placed after the loop's end label? I put `z = 0;` before `off += 8;` — that's inside the loop.

Hmm, "real insns" counts insns that are not notes/labels. If the dead store survived, count should be 29. So it was deleted before loop.c (by delete_dead_from_cse, called after cse). Yes: toplev.c calls `delete_dead_from_cse (insns, max_reg_num ())` after cse, before loop. That deletes dead stores. So dead stores can't survive.

What about a dead insn that delete_dead_from_cse can't remove? That function deletes insns whose dest is a register not used later, with no side effects (like a pure set). It won't delete something with a memory side effect. A dead *load* (set reg = mem) has no side effect and would be deleted too if the reg is dead.

What survives cse1 and is deleted after loop.c? `delete_dead_from_cse` deletes: an insn setting a reg that is never used, unless it's a call or has side effects. So any dead store to a local gets deleted.

Alternative: make an insn that is NOT dead (its result IS used) so it survives, but whose final code is identical... that's impossible; a used insn adds code.

Hmm, but we can add an insn whose result is used only by another insn that is deleted... circular.

Alternative approach: raise insn_count differently — loop.c's insn_count is the count of insns in the loop at loop.c time. We can't add without final code.

Alternative: lower the hoist desirability via `m->lifetime` or `savings`. m->lifetime = length of live range? For the constant, life 1. We can't make it 0.

Alternative: make `m->cond` set: if the set is conditional, the hoist requires `1 == invariant_p(src) && (dependencies==0||...) && (consec==0 || ...)`. m->cond is set when the insn is only conditionally executed (inside an if within the loop). If we put the -1024 store inside a conditional that always executes? Then extra branch code. No.

Alternative: prevent the constant from being movable at all: `invariant_p` returns 0 for something that's not invariant. If the stored value depends on the loop variable, it's not invariant. But the target value is -1024 constant.

Hmm, what if we make the constant insn's destination register also used by something that forces it to stay? e.g., if the pseudo is used twice (n_times_used > 1), the hoist is still done if threshold*savings*lifetime >= insn_count; savings would be higher (2 uses), making hoist MORE likely.

What about making the constant pseudo live across a call or something so `loop_reg_used_before_after`? Not helpful.

Alternative: change the *loop structure* so the -1024 store is outside the loop entirely? Target has it inside. No.

Alternative: make the loop body bigger than 28 in a way that survives to final code but the target also has it? No.

OK, what about a completely different route to get v0/-1024 inside the loop: make the constant not hoistable by making it *not a constant in RTL*: e.g., `= (s16)0xFC00;` — still a constant.

What about storing a value loaded from a table that happens to be -1024? No, semantics.

Hmm. Let me reconsider: maybe the mechanism isn't only the threshold. With the pin, n_non_fixed_regs is 26 → threshold 27 < 28 → not hoisted. That's a 1-insn margin! So if I can make insn_count 29 (one more real insn at loop.c time that is later deleted or that doesn't matter)...

Wait — actually maybe I can make the loop *appear* to have more insns at loop.c time without adding final code: a dead insn deleted by a pass between loop.c and the final code. Which passes run after loop.c? cse2, jump_optimize(2), flow, combine, sched, local-alloc, global-alloc, reload, ... The dead insn must be deleted by one of these. flow's `life_analysis`+`delete_dead_insns`? Let me check toplev pass order and where dead insns are removed after loop.

Actually `delete_dead_from_cse` is only after cse1 (and cse2?). Let me look at toplev.c rest_of_compilation.
