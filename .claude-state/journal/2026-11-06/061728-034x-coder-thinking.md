---
ts: 2026-11-06T13:17:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_m5CEM2fFBQFXcp6d3kHI
---
Critical: cross-jump happens AFTER register allocation (post-reload, after sched2)! So at cross-jump time, registers are HARD registers, and `rtx_renumbered_equal_p` compares hard reg numbers. The renumbering is for... hmm, at that point, all pseudos are gone (reload_completed). So two copies that use the same hard registers are equal; if one uses v0 and the other uses v1, renumbered_equal would map v0↔v1 (consistent within insn) → still equal! That's why "jump2 cross-jump renames regs so const-vs-var stores do not differ".

So we need an insn whose register usage differs *inconsistently within one insn*, or a pattern difference.

Zero-byte possibilities at post-reload:
- A no-op move `move v0,v0` — the pass is called with noop_moves=1, so no-op moves are deleted IN THE SAME PASS. Order within jump_optimize: does it delete no-op moves before cross-jumping? If deleted first, then no help.
- A pattern difference that produces the same bytes: at post-reload, the insn is already matched (INSN_CODE) with a specific pattern. Two identical machine instructions always have identical patterns? Mostly yes — pattern is the RTL that matched, and the same mnemonic with the same operands gives the same pattern.

Hmm, so the only way is a difference in the *registers* used inconsistently or a different instruction sequence that has the same encoding.

Interesting: the target's two copies use the same hard regs (v0, s0) and are identical. So how did the ORIGINAL binary avoid the merge?! 

Unless... cross-jump couldn't merge them because the two blocks are not connected in a way find_cross_jump explores. Cross-jumping merges when two jumps target the same label. Here both copies end with `j TAIL` (goto TAIL, label a70). Both jumps target TAIL. find_cross_jump(insn=j, JUMP_LABEL=j → the TAIL label, minimum=1). Wait, e2 = JUMP_LABEL(insn) — that's the label INSN, not the jump. Let me read the call sites 1941-2030.
