---
ts: 2026-10-17T11:17:40.331Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
effort: medium
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
I'm puzzled why the store at block 58-73 still got replaced despite being in a new EBB where pe's class should only contain itself—unless cse's follow-jumps or skip_blocks behavior is carrying table entries across block boundaries in a way I hadn't accounted for.

The reused register 92 in the re-test jump insn from BB0 suggests cse1 actually treated the range 2 to 73 as one continuous block via skip_blocks, meaning the bne branch jumps around BB2 with no other entries into it, which would explain why equivalences from BB0 persisted into this later point.

I bet jump.c's pre-cse1 pass already threads a conditional jump to another conditional jump sharing the same condition, which is why label 57 shows only one use by the time cse1 runs — the front end reusing the same zero-extended register made the two tests identical enough to trigger that optimization. So to prevent this premature threading, I need the second comparison to be syntactically distinct enough to dodge jump1's threading while still letting cse1 catch it later.

But then I realize cse2 itself might just fold the retest directly: if label 57 still has two uses at cse1 but drops to one by cse2, record_jump_equiv could recognize from the first branch that pad is nonzero and eliminate the redundant check without needing explicit jump threading at all. I'm now considering whether writing the retest in a different surface form, like `else if (pad)` instead of `pad != 0`, would produce the same RTL and sidestep the issue, or whether I need to look more carefully at what triggers the use-count change between passes.

I should check the fn.jump target from the pre-cse pass for jump 21, and look at fn.rtl for context.
