---
ts: 2026-11-06T04:57:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vDui3WOmn2i8Koz5nnve
---
In orig (barrier): insn 66 sets a0 from `(mem:SI (reg/v:SI 75))` — a real load via reg 75 (the pointer). The barrier insn 63 (asm with mem clobber) prevents cse from forwarding. In a1: insn 64 `(set (reg:SI 4 a0) (reg/v:SI 76))` — cse forwarded the store.

So cse1 (or cse2?) forwarded the load to the stored value despite the jump and the unknown store. Let's look at cse1 for a1. The dump .cse is cse1. Let me check.

Actually the dump labeled .cse2 is the second cse. Both a1 and orig cse2 show the state. In a1's cse2, insn 64 is already `(reg/v:SI 76)`, so the forwarding happened in cse1 (the .cse dump) probably. Let's check a1.i.cse.

Wait, but there's a jump between the store and the load. cse1 processes each basic block independently... unless the jump is a *conditional* and the block continues? No.

Hmm, maybe cse1's `cse_basic_block` follows the fall-through path: it processes the block, then follows jumps to labels with a single use, merging blocks into an EBB. For a conditional jump, the fall-through and target both continue? cse1 scans linearly through the insn chain, and at a jump it may continue into the next insn if the jump is a conditional? Let me recall: cse_basic_block(insn, to, ...) processes insns until `to`; for JUMP_INSN, if it's a conditional and the next insn is not the target, it continues? Actually it does: `if (GET_CODE (insn) == JUMP_INSN && condjump_p(insn) && ...)` it continues into the fall-through block, but invalidates the table at the jump? Let me check.

Rather than reverse-engineer, the practical move: we need a real-C construct that makes cse not forward. Since cse1 forwards the store `*p = v0` into the later load `*p` even across the conditional, we need to break the memory equivalence. Options:
1. Make the store address not equal to the load address in cse's view: e.g., store via `p` and load via a *different* expression that cse can't fold to the same thing. In target, the load is `(mem:SI (reg/v 75))` — via the pointer reg. The store is also `(mem:SI (reg/v 75))`. If we make the load go through a different pseudo that cse can't prove equal, forwarding stops. But cse's REG_EQUAL on reg 75 = symbol D_80127524 lets it fold. If we prevent reg 75 from having REG_EQUAL, e.g., assign p in a way that loses the equivalence: `s32 *p = &D_80127524;` gives REG_EQUAL. If we instead obtain p from a memory load, cse won't know its value: e.g., `s32 *p = (s32 *)D_8012xxxx` where D_8012xxxx holds &D_80127524? There's no such pointer.

2. Insert a store that invalidates the memory entry before the load. cse's note_mem_written with a varying address (register-based) invalidates all memory. The `sh` store to `(mem:HI (plus (reg 84) 26))` — reg 84 is a loaded value (varying address). That should invalidate everything! But the forwarding still happened. Why? Because cse's table at the time of the call-arg load: after insn 57's load, the table has (mem D_80127524) -> reg 84. Then insn 61 stores through reg 84+26 → invalidates memory entries... but wait, the *store* at insn 50 created the entry (mem D_80127524) -> reg 76. Then insn 57's load of the same mem: cse would have forwarded it to reg 76 too, but it didn't (insn 57 is a real load). Hmm, so at insn 57 the entry wasn't there. Then why at insn 64?

Let me look at cse1 to understand. Maybe the store at insn 50 is in a different block and the forwarding at 64 comes from the *load* at 57: cse records (mem D_80127524) -> reg 84 from insn 57, then insn 61's store (varying address) invalidates... maybe not (it's a HI store at reg+26; note_mem_written may only invalidate when the address is not fixed — let me check note_mem_written).

Actually if cse invalidated on insn 61, insn 64 wouldn't forward. So note_mem_written for a store with a register address (plus reg const) — is that "fixed"? Let me read note_mem_written.
