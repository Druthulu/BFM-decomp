---
ts: 2026-11-06T05:30:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LLd13U8r1DhA5h5dUcsv
---
Interesting: in inv1, mine has the epilogue at 5fec and target at 5fe8 — mine is 4 bytes longer (61 vs 60 insns), and mine's last return-0 block is `j 5fec; nop; move v0,zero` (deleted at the end). The target has the early return-0 as `j 5fe8; move v0,zero` at insn 10-11 (which mine lacks).

Hmm, so in inv1 the merge still happened (the early return at the end merges with the default). The difference is the block layout.

Let me try more shapes: do-while(0), goto to a label, and a `while(1)` with breaks.

Actually, let me think about what could produce the target's exact layout:
Target: 
- early check: `bnez v0, body` (fallthrough return-0)
- the return-0 is emitted as `j epilogue; move v0,zero` (a jump, not fallthrough!) — because the epilogue is far (the body is in between). So the early return must be *before* the body and jump over it.

In mine (base), the early return is `beqz v0, return0_block` where the return0_block is shared with the default and placed after the body. So the early check branches forward.

Why does the target branch *into* the body (bnez) instead of branching to the return block? Because the return-0 is a jump block (`j epilogue; move v0,zero`), and the compiler inverted the branch to make the body fall through. That's the "cheapest" layout: the body follows the check, and the return-0 is a jump.

In mine, the return-0 is shared and placed after the body, so branching to it is cheaper than jumping.

So the fundamental difference is the *merge* of return-0 blocks. If we prevent the merge, the early return becomes its own jump block → the branch inverts → matches.

How to prevent cross-jump in pure C? Cross-jump merges blocks with identical insns. If the two return-0 blocks differ by *something* that is optimized to the same bytes... impossible.

But maybe we can arrange for the default return to be a *fall-through* to the epilogue (not a jump), so it's not identical to the early return's jump block. In the target, the default IS a jump (5f68 j 5fe8). Hmm.

Alternatively: make the early return-0 block contain an extra insn that the target also has. Target early return-0: `j 5fe8; move v0,zero` (2 insns). Target default return-0: `j 5fe8; move v0,zero` (2 insns). Identical! So cross-jump *should* merge them in the target too — but the asm blocks it.

Hmm, unless cross-jump requires the blocks to be adjacent-ish or reachable. The asm insn is between them in the instruction stream. Cross-jump merges only if the blocks are "at the end" of the function? jump2's cross-jump looks at the last block and jumps to it.

Anyway, pure C can't insert an insn. WALL.

Let me do the remaining tries (need 30). I'll add variants: do-while(0), while(1), goto labels, duplicated returns with different constants (e.g., return (s32)0 vs return 0 — same), and a version where the early return is `return st & 0` (adds code), etc.

Actually, let me reconsider whether the *item is even meant to crack*. The source comment says `!FAKE: barrier — NEEDED DIFFERS (P36 rung B headers2)`. The P36 rung B added barriers to headers. So these are known crutches. The shard's job is to find real-C replacements. Some will crack, some wall.

Let me be pragmatic: item 5 is a wall. Let me do 10 more tries (31 total) and record.

Then item 1 and the family. Let me write the extra variants quickly.
