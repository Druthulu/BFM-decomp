---
ts: 2026-11-06T10:07:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_URLWltvJP84JtkNP4H9h
---
No improvement. The register swap dominates.

Let me now think about whether I can add a *real* second variable that crosses the call and takes s0. If I add `s32 tmp;` used after the call in block 0, it must emit code. But maybe I can use an existing value: what if I compute `u6` via a temp that's born before the call? Hmm.

Actually — here's an idea: what if `u5` is computed *before* the call? No, u5 IS the call result.

What if `s1ang` is loaded AFTER the call (v2, score 32)? Then s1ang doesn't cross the call → gets a caller-saved reg, and d (global) gets s0. But then the load is after the call → different code (v2 worse).

Hmm, v2 scored 32 — let me look at its residual. Maybe it's closer in the register sense but different in load placement. Let me --explain v2... --explain only works on the tree body. I can use --try with tail. Let me check the diff for v2 with a big tail.

Actually, let me reconsider. What if we make s1ang's *live range* cross the call but NOT be a separate qty — i.e., tie it to u6 so the combined qty is global? If s1ang and u6 are combined into one qty, the qty is global (used in later blocks), and local-alloc won't assign s0. Then global-alloc: d (pri 5185) vs the combined s1ang/u6 qty (higher refs/live?). If the combined qty has HIGHER priority than d, it gets s0 — wrong. If lower, d gets s0 and the combined gets s1 — RIGHT.

So: tie s1ang and u6. How? In RTL, combine_regs ties them if the andi has a copy-like constraint. The MIPS andsi3 pattern... let me look at it. If I can make the C produce a `(set r77 (and r75 0xFFF))` where r75 and r77 are tied, local-alloc combines them. The current RTL is `(set (reg/v:SI 77) (and:SI (reg/v:SI 75) (const_int 4095)))`. combine_regs with may_save_copy=0 would still combine them if "the classes are compatible and it's profitable"? Let me read combine_regs logic for non-copy insns.

Actually, combine_regs is called for each insn with usedreg/setreg. For a non-copy insn, may_save_copy=0. It still combines if `regs have the same mode` and the classes allow, subject to "if (ureg >= FIRST_PSEUDO_REGISTER && sreg >= FIRST_PSEUDO_REGISTER)"... Let me read more of combine_regs.

Hmm, but in the dump they're separate (r75 local, r77 global). So they weren't combined. Why? Because combining a local (single-block) and a global (multi-block) qty: the combined qty would be global. combine_regs checks `qty_birth/death` and might refuse if it would extend the live range. Let me read.

Let me look at combine_regs further.
