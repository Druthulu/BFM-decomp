---
ts: 2026-11-06T17:06:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YVt037mvU4XAWKAlDElQ
---
Exactly as the comment says: mine has the 0xE100008E constant in t6 and the mask in t7; target has the constant in t7 and the mask in t6. So we need to swap which constant gets t6.

Both constants are block-local pseudos. The allocation order decides. The 0xE100008E constant is used 6 times? No: `*q2 = 0xE100008E` etc. — six different constants (0xE100008A, 8C, 8E, 9A, 9C, 9E) each used once. The mask 0xFFFFFF is used 12 times.

Mine: the 0xE100008E (first constant) got t6, the mask t7. Target: mask t6.

Priority: mask (12 refs) vs constant (1-2 refs). The mask should have higher priority → t6. But mine gives the constant t6. Why? Because local-alloc processes the block; the constants are born earlier (their insns are earlier: the 0xE100008A is at insn 5, the mask at insn 16). Priority = refs*size/life. The mask: 12 refs, life from insn 16 to the end (~200) → 24/200 = 0.12. The constant: 1 ref, life 2 → 1/2 = 0.5. So the constant wins t6!

Target wants the mask in t6. So the mask must have priority > the constant, or the constants must take t7 first.

Hmm, the mask's life is very long (the whole function's tail). The constants are short-lived. So the constants win t6 by priority. In the target, the mask is in t6 (pinned).

Lever-free approaches:
1. Increase the mask's refs: 12 already; refs*floor_log2(12)=3*12=36 / life 200 = 0.18 vs constant 0.5. Need much more.
2. Reduce the mask's life: if m24's definition were later (closer to its uses), its life shrinks. In the source, `m24 = 0xFFFFFF;` is at line 6846, just before the 12 uses (lines 6848-6859). The uses are all in the last 12 statements. So its life is from insn 16? Wait, mine[16] shows the mask materialization at insn 16, near the top! That means the mask was HOISTED to the top by sched1 (or expand put it there?).

Actually mine[5:7] shows the 0xE100008E constant at insns 5-6 (that's the first packet's q0 constant 0xE100008A? The diff shows t6/t7 swapped at insn 5). And the mask at insn 16-17.

Hmm, so the mask is materialized at insn 16, near the top, far from its uses at 146+. Why? sched1 hoisted it? Or cse hoisted it out of... The source has `m24 = 0xFFFFFF;` at line 6846, but expand may create the constant at first use; cse/loop/sched1 could hoist.

Wait, the diff positions are in the final instruction stream. Mine insn 16-17 = the mask lui/ori. The source order: all the packet stores (6 blocks) then obase/ot/m24 then the 12 and/or statements. The mask at insn 16 means it was hoisted early — probably by sched1 (constant hoisting) or by cse's constant loading at the first use... 

The target also has the mask at insn 16-17 (`lui t6,0xff; ori t6,t6,0xffff`). So both hoist it to insn 16. Fine.

So the difference is purely which pseudo gets t6 vs t7. The mask (12 refs) vs the 0xE100008E constant (used once at insn 76, `sw t6/t7,0(v0)`).

Hmm wait, the constant at insn 5-6 is 0xE100008E — but the first packet's constant is 0xE100008A. The 0xE100008E is the third packet's. Interesting: the diff shows mine insn 5-6 `lui t6,0xe100; ori t6,t6,0x8e` — so the 0x8E constant was hoisted to insn 5! And it's used at insn 76 (`sw t6,0(v0)`). So its life is 5→76 (71 insns), refs 2 → 2/71 = 0.03. And the mask: refs 12 → 36/life(~200) = 0.18. Mask > constant. Yet mine gives t6 to the constant!

Hmm, so my priority model is wrong. Maybe the mask is not 12 refs in one qty: the mask is used in 12 `and` instructions in the last block; it's a single pseudo. Priority = floor_log2(12)*12 = 3*12=36; life from 16 to 210 = 194 → 0.185. Constant 0x8E: refs 2 (def + use), floor_log2(2)*2=2; life 5→76 = 71 → 0.028. Mask wins. But mine gives t6 to the constant.

Unless the mask pseudo is NOT block-local (it crosses blocks?) and the constant is local... Both are in the same block (the whole function body is one block? There are no branches — the function is straight-line!). So one basic block. All pseudos are local.

Then local-alloc's priority ordering... maybe I have the formula wrong: pri = floor_log2(n_refs)*n_refs*size/(death-birth). For the mask: n_refs might be 13 (12 uses + 1 def) → floor_log2(13)=3, 3*13=39. Constant: n_refs=2 → 2. Hmm.

But maybe the constant's death is earlier: birth 5, death 76 → 71. Mask birth 16, death ~210 → 194.

39/194 = 0.20 vs 2/71 = 0.028. Mask should win.

Unless the allocation order is by *regno* when priorities are within the same "class"? qsort with qty_compare_1 → priority first, then qty number.

Hmm, but mine clearly gives t6 to the constant. Let me check the dumps to see the actual priorities. But wait — maybe the "constant" in t6 at insn 5 is not 0xE100008E but something else, and the mask's register t7 is due to something else.

Let me get a faithful dump for item 3 (need a d.sh for this TU) and inspect the lreg priorities... The lreg dump doesn't print priorities, but the dispositions and the qty list do.

Alternatively, empirically: try to give the mask more refs or make the constants take t7.

Idea: the six 0xE1 constants each take a register briefly. The one that matters is the first materialized (0xE100008E at insn 5). If we could make the mask's priority higher: e.g., use the mask in more places (it's used 12 times). Or shorten the mask's life by moving its definition later — but it's already at the first use; the compiler hoisted it to insn 16 (both mine and target). Hmm, why insn 16? Maybe that's where the first `and`-related code... no, the ands are at 146+.

Actually, insn 16 might be where the mask is *defined* in the RTL after cse hoisting (cse hoists loop-invariant? no loop). Sched1 hoists constants to the top of the block to fill slots.

OK let me just experiment:
1. Give m24 more refs by using it in a way that's free? Not free.
2. Change the mask constant spelling: `0xFFFFFF` vs `~0xFF000000` vs `0x00FFFFFF` — same.
3. Change the declaration order of m24 (declared after ot, before i). Moving its declaration to the top might change the pseudo number, but priority is by refs.
4. Change the type: `s32 m24` vs `u32`.
5. Use the mask inline in each expression instead of a variable: `(... & 0xFFFFFF)`. Then the constant might be CSE'd into one pseudo anyway (cse hoists it). The register might differ.
6. Use a different mask value with the same bits: `0xFFFFFFu`.

Let me first get a faithful dump to understand. I need d.sh for the SC07 TU. Let me create t.i and a generic splice for func_801817D0.

Actually, maybe faster: try variants directly.

Key question: which pass decides? Both constants are in one block; local-alloc priority. The mask has more refs but a longer life. Let me compute more carefully using the actual insn counts from the dump.

Let me create the dump infrastructure (t.i + splice + d.sh) — it's quick.
