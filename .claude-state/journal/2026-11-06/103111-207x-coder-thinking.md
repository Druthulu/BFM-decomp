---
ts: 2026-11-06T17:31:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7Zv6mLoZzcsO7A1RGgL2
---
So 75's defs: 396 (from 77), 419 (from 147); uses: 423, 424. No copies. The "preference: 3" must come from combine_regs on the shift insns: in combine_regs, for an insn `(set (reg 75) (ashift (reg 77) 16))`, the pattern's operands are checked: if the insn is a "copy" (single_set with src a REG), no. But combine_regs is called for each operand pair where one is set and the other used... Let me look at the caller: local-alloc's block_alloc calls combine_regs(r1, r0, ...) for various cases, including "if the insn is a shift and the operands tie"? 

Actually, for an insn like `(set (reg A) (OP (reg B) ...))`, local-alloc ties A and B if B dies (for 2-address machines). The MIPS ashlsi3 pattern may be a 3-operand pattern, but combine_regs might still tie the output to the first input (may_save_copy=0, so it's a "suggestion" not a copy preference).

So 75 gets suggestions from both defs: from 77 (the angle, in a0) and from 147 (the load, in v0). The dump says preference 3 (v1) — hmm, neither.

Wait, maybe I have the register numbering wrong: reg 3 = v1. The angle (77) is in... let me check the final asm: `sll $3,$4,16` → source $4 (a0), dest $3 (v1). So 77 (angle) is in a0 (4). The preference from 396 would be 4, from 419 would be 2 (147 in v0). The dump says 3.

Unless the preference comes from a later pass (regmove/global). The greg dump is after global-alloc; "preferences: 3" might be qty_phys_sugg from combine_regs with reg 3.

Hmm, whatever. The empirical result: sh16 lands in v1.

Let me try a *targeted* experiment: make the two shift sources be v1. If the load `p[0x79]` is in v1 (instead of v0), then the second sll could be `sll v1,v1,16` and sh16=v1 — that's mine. To get sh16=v0, the sources should be v0.

What if I change the first assignment to use a v0-valued expression? e.g., `sh16 = (s32)((u32)angle << 16);` — the angle is in a0, same.

What if angle is stored and reloaded: `p[0x79] = angle; sh16 = p[0x79] << 16;` in the then arm? Then the source is a fresh load (in v0 or v1) — changes instructions (extra load).

Hmm.

What if the then arm uses the *call result* directly (v0) instead of the angle variable? `sh16 = func_80029D3C(cmp79) << 16;` — but angle is also stored. The source order: angle = func(...); p[0x79] = angle; if (...) sh16 = angle << 16.

What if we write `sh16 = p[0x79] << 16;` in BOTH arms? In the then arm, p[0x79] was just set to angle. That would reload p[0x79] — an extra load. Hmm, but gcc might CSE it with the store value (angle). Actually `p[0x79] = angle; ... sh16 = p[0x79] << 16;` — cse could forward the stored value (angle) — likely the same.

Let me try: replace `sh16 = angle << 16;` with `sh16 = p[0x79] << 16;`. If cse forwards, the code is the same; if it reloads, it differs.

Also try: `sh16 = (s32)((u16)p[0x79] << 16);` — the load is lhu (zero-extend) in the else arm; in the then arm, angle is s32.

Let me run a batch of experiments (each scored on includer 0 only, ~1s).
