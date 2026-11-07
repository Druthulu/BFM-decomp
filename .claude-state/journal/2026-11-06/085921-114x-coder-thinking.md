---
ts: 2026-11-06T15:59:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QpY4YyBuILtzxrOx0YNF
---
The target: the first `if (n<4)` test at 287-289 branches to 182c. Then the OT store block (lbu/ori/sb, addu/lw/lw/and/and/or/sw/lw/and/and/or/sw). Then the second test at 299-301 branches to 18c0. Then the tpage body at 303+.

So the target has TWO tests but ONE shared body? The first test branches to 182c, the second to 18c0 — different addresses! 182c vs 18c0. Let me see what's at 182c. Hmm, the first test's branch target 182c is *before* the second test (18c0). The body at 303 (jal) is at some address. Let me compute: the disassembly doesn't show addresses, only offsets in the branch targets.

Actually 182c and 18c0 are absolute-ish offsets within the function (0x182c?). The function is 346 insns * 4 = 1384 bytes = 0x568. So 182c/18c0 are not function-relative? They're the printed target addresses (function starts at 0x14xx). Hmm.

Anyway, the target has two tests and presumably two bodies? But the insn count difference is only 2, so the bodies are shared/cross-jumped.

Wait, the target's second test at 299 is followed by the tpage body (jal func_80010A08). The first test at 287 branches to 182c — which might be the SAME tpage body (the shared one). And the second test at 299 branches to 18c0 — maybe the shared body's *entry* is at 18c0 and 182c is something else. Confusing.

Key: the target has the test computed twice (slti s0,4 twice), mine once. That's the 2-insn difference. So the launders prevent the *test unification*, not cross-jump of the body.

Why does mine compute the test once? Because cse sees `n < 4` computed in the first tail and reuses it in the second (n unchanged). Wait, but the two tails are in different branches; cse's global CSE can share the comparison result if it's available (a register holding n<4). The first tail's test is a `slti v0,s0,4` whose result is used by the branch; the result isn't kept in a register across the tail (it's used immediately). Hmm.

Unless jump.c's cross_jump merged the two `if (n<4) {body}` blocks: the first block's test and the second block's test are identical → cross_jump merges them, so the second test is replaced by a jump to the first test's block, eliminating the second slti. That's exactly cross_jump.

So it IS cross-jump of the *if blocks* (test+body). The target avoids it because the blocks differ — due to the asm insns.

So the tag `jump2-crossjump-arms` fits.

Now, to prevent cross_jump in plain C, the two blocks must differ. The asm made them differ. Without asm, any C that produces identical RTL merges.

One more idea: make the two blocks differ by using different *constants* that fold to the same value? e.g. first `if (n < 4)`, second `if (n < 0x4)`. Same RTL.

What about using a `long` vs `s32` comparison? Same.

OK. WALL confirmed.

Let me check the time and then write the row/notes. Time ~09:02. Need 20 min from 08:47 → 09:07. Let me do a few more tries to use the time, then finalize.

Try n1: in the LINE tail, use `if (n < 4)` but with n passed through a *local copy with a block scope* `{ s32 n3 = n; if (n3 < 4) {...} }` — the copy may coalesce and cse may still unify. Test.
n2: POLY tail uses `if (n < 4)`, LINE tail `if (n - 4 < 0)`? Same RTL after folding.

Let me test n1 and a couple of others.
