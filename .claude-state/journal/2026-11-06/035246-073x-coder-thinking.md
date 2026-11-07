---
ts: 2026-11-06T10:52:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JMvrQojlRfQayhCulBxE
---
Key: for a volatile asm, sched1 adds ANTI dependencies from the asm to all pending reads/sets: `add_dependence(insn, prev, REG_DEP_ANTI)` — wait, it adds a dependence FROM insn (the asm) ON the previous insns. That means the asm must come after them, but not vice versa. Hmm, "add_dependence (insn, elem, ...)" means insn depends on elem.

Hmm, so insns after the asm don't depend on it in the scheduling graph? They do via `flush_pending_lists(insn)`: pending lists are flushed, and subsequent memory insns get a dependence on `last_pending_memory_flush` (the asm) → anti dependence. So the load/store after the asm depend on it. But their mutual order is unchanged.

So sched1's schedule after the asm should be the same as without it. But the target differs. Therefore the difference must NOT be sched1's reordering but something earlier: maybe cse/combine or the RTL itself.

Wait — maybe with the barrier, cse1 does NOT merge the two memory ops, changing the RTL. Without the barrier, cse might CSE the load of 196 with the store? Or combine the ori/sw into a different insn? Hmm.

Actually, maybe without the barrier the sched1 pass produces the same order but then *dbr* (delayed branch) or the assembler reorders? No, the target's difference is in the middle of the block.

Hold on, let me compare the target's instructions with mine again:
Target: lw v0,196 / lui v1 / addiu v1 / sw v1,88 / ori v0,2 / sw v0,196 / lw v0,32 / li v1,16384 ...
Mine (v_ref3): lw v0,196 / lui v1 / addiu v1 / ori v0,2 / sw v0,196 / lw v0,32 / sw v1,88 / li v1,16384 ...

Both are valid schedules. The difference is sched1's choice.

Maybe the difference is the *local-alloc* result: in the target, the address is v1 and t v0; in mine (v_ref3) also v1/v0. Same regs. So the only difference is sched1's order.

Hmm, so with the asm in the block, sched1 chose sw88 before ori; without it, ori before sw88. How?

Because the asm resets `reg_last_uses` and `reg_last_sets` and sets `reg_pending_sets_all = 1`. This affects dependences for subsequent insns: each subsequent insn gets anti-dependences on... hmm, and `flush_pending_lists`.

Actually, there's a subtlety: `add_dependence` adds a dependence but sched1's priority computation uses the dependence graph. The asm creates anti-dependences from itself to the preceding insns, and subsequent insns depend on the asm.

But the relative order of sw88 and ori shouldn't change...

Unless: with the asm, the store to 88 gets a dependence on the asm AND the ori/store also depend on the asm; still equal.

Hmm, maybe the difference is not sched1 but the *register allocation* affecting the RTL: in the target, t is hard reg v0 (pin), so the ori is `(set (reg 2) (ior (reg 2) 2))` — an in-place RMW. Without the pin, the ori is `(set (pseudo t') (ior (reg t) 2))` then `(set (mem) t')` — a different RTL shape with an extra pseudo! That's why sched1 orders differently.

Ah, that's a real insight: with `t` pinned to $2, `unkC4 = t | 0x2` compiles to `ori v0,v0,2; sw v0` where the ori writes t itself (in place). Without the pin, `unkC4 = t | 0x2` may create a NEW pseudo for the result (t|2) and then store it, i.e., `ori v1,v0,2; sw v1`. But the target has ori v0,v0,2. Hmm, in my candidates the ori was `ori v0,v0,0x2` (in place) — because combine folds `t = t|2` into the same pseudo when t is dead after.

OK so the RTL is similar.

Let me try yet another approach: measure what happens with the barrier but lever-free pins — i.e., v_param + the original barrier. If that's 0, then the barrier alone preserves the schedule; then the task is to replace the barrier with a real-C block split that doesn't disturb allocation.

Actually, from the earlier tests: nopin (pins removed, barrier kept) = 22 — that's v_param + barrier? No: nopin removed only the pins, keeping the barrier. It scored 22 with the s0/s1 double copy. The double copy was due to the pin removal on s0. In v_param (parameter-direct) the double copy is gone. v_param + barrier (no pins) would be interesting.

Let me test: v_param + the barrier line. If it scores 0, then only the s0 pin is unnecessary and the barrier is needed; if it scores something small, the barrier's removal is the remaining issue.

Let me build it.
