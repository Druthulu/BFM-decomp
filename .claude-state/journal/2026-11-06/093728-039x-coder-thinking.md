---
ts: 2026-11-06T16:37:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ynqSiI3YbvCTxzYE7d2T
---
10.4 minutes. Need 20. Let me use the next 10 minutes for a few more substantive tries. Let me think about whether the target's structure could arise differently.

Actually — here's a new idea for the cross-jump: the target has the first if's block A at 0x158 and block B at 0x198. Notice the *branch instruction* for if1 is `beqz v0,180` (branch when false) and if2 is `beqz v0,1c0`. The code layout is: if1-test, blockA, if2-test, blockB, continuation. This is the "if (c) {tail} ; if (c2) {tail}" layout. Cross-jump merges the tails.

To prevent cross-jump, the two tails must differ in RTL. The target's tails are byte-identical. So the original source must have had a zero-byte RTL difference — i.e., an asm. Therefore the original source DID have an asm or an equivalent (e.g., a `volatile` on... no). Wait, could the original have had a *function call* between that got inlined? no.

Hmm, actually maybe the original had `#define X ...` with an asm barrier. The decomp project would then accept that this function needs a barrier (it's a "NEEDED DIFFERS" fake). The task asks to crack it lever-free; if impossible, WALL.

But hold on: maybe the difference is that the two blocks in the ORIGINAL source had different *arguments* that are both zero but spelled differently AND the compiler kept them as different RTL because one used a SYMBOL address? E.g., `func_800D2AA0(0)` vs `func_800D2AA0((u8*)D_800EC9A4 - (u8*)D_800EC9A4)`? That computes, emits subu. no.

I'm confident.

For the remaining time, let me try 8 more candidates that mix the best (c38 reorder) with keepalive tricks to see if best drops to 4, and a couple of new cross-jump ideas:
- h01: c38 + `(void)v0r;`
- h02: c38 + `i = v0r;`
- h03: c38 + `v0r = 1;` before func_80010A98
- h04: c38 + `if (v0r) {}`
- h05: c38 with v0r declared u8
- h06: c38 with `v0r = 1;` as `return;`? 
- h07: block1 reorder by ONE call: (D2D44, D468FC, D2AA0, D2D8D4) is c38; try (D2D44, D2D8D4, D468FC, D2AA0) = c18 (15). try (D468FC, D2D44, D2D8D4, D2AA0) = c40 (19). try (D2D44, D2AA0, D468FC, D2D8D4)?
- h08: try reordering just the last two with a *different* call: c38 is best.

Let me also try a completely different merge-block: make the second block jump to `ret` but the first block *fall through* to ret by placing block A last (reorder the whole ifs) — bytes differ.

Let me run h01-h06 and a couple of reorder variants. Then wait until 09:47, write results, move on.

Actually, maybe more valuable: try to see if the merge can be blocked by making block A end with `goto done;`? No, semantics.

Let me just run the batch.
