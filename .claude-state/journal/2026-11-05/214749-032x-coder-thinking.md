---
ts: 2026-11-06T04:47:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wGi3kUuqbYyEDry1if0P
---
There it is: `stop_search_p` returns true for an asm insn (`ASM_INPUT` or `asm_noperands >= 0`). So in fill_eager_delay_slots, `for (trial = thread; ! stop_search_p (trial, ! thread_if_true) ...` — the asm as the first insn stops the search immediately → no delay fill → nop. That's the mechanism.

So to replicate lever-free: we need the first insn of the fall-through thread after the branch to be something that `stop_search_p` stops on: a JUMP_INSN, BARRIER, or an asm. Real C can't produce asm. A JUMP_INSN as the first insn after the branch would mean the if-body starts with a jump — that's an unconditional jump in the body, i.e., an if/else where the then-arm immediately jumps. Hmm, that would add a jump.

Wait, but what about `thread`? `thread = next_active_insn(insn)` probably. If the fall-through starts with a label, eager's `own_thread=0` and the loop: `for (trial = thread; ! stop_search_p (trial, ! thread_if_true) && (! lose || own_thread); ...)`. stop_search_p with labels_p = !thread_if_true. If thread_if_true is 1, labels_p=0 → label doesn't stop. If thread_if_true is 0, labels_p=1 → label stops!

Hmm, which is it here? For a conditional branch, `thread_if_true` = whether the likely direction is the branch target. Let me look at how fill_eager_delay_slots is invoked (the caller at 4170). Let me read around 4130-4180.

Also another idea: a CODE_LABEL at the start of the fall-through block stops the scan when labels_p is set. If some other branch jumps to the body start, a label exists. But gcc would delete an unused label.

Let me think about the caller logic.
