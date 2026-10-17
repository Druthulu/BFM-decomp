---
ts: 2026-10-17T12:47:36.535Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aa713f978f6769f98
model: claude-opus-5-5[1m]
effort: medium
turnId: 29f80c87-241a-492d-b40b-c42d868c661f
---
I'm noticing the free version has a branch structure where t==5 implies t!=3, making that inner check always true — which itself looks like the kind of redundant branch flagged as suspicious. But the target version keeps a similarly redundant test, comparing against 3 and 5 with a fallthrough case, so this redundancy seems intentional in both versions rather than a discrepancy.

I'm trying to figure out what keeps the merge alive at cse2 — in the target, the inner test still has multiple predecessors, so something else must jump into it besides the t==5 path. Since t is only assigned in case 5, I'm wondering if there's another entry point, like a different case label or a loop structure, that reaches the inner test with t unknown.

Checking if there's a goto elsewhere in case 5 pointing to the same label used in the redundant test — scanning through the later branches in case 5, none of them seem to jump to sel_094 or sel_054 directly. It seems more likely the inner test is reached via the original beq before threading gets applied, and after threading the target ends up branching straight to sel_054.

Now I'm wondering whether cse2 actually folds this case, since cse_end_of_basic_block with follow_jumps enabled extends basic blocks across conditional jumps whose target label has a single use, and continues through fallthrough paths — this matters because -O2 sets flag_cse_follow_jumps and flag_cse_skip_blocks, which could explain why the redundant comparison disappears.

So I need a label with uses (not threaded away) between the two comparisons to force cse to stop there and leave the fold intact. I'm considering an alternative structure where the first branch jumps directly into the inner test's target, so that thread_jumps could still thread it through to the same final label, but the question is whether the intermediate label retains any uses after that transformation.

Thread_jumps only threads when the target block is purely the comparison with no other instructions, so if I insert any real statement between the label and the inner branch, threading is blocked and the label would keep its use count nonzero. I'm now thinking through the switch statement's case layout, considering how the t==3 path and t==0 path set the selector variable before jumping to a shared label.

Maybe the duplicate check comes from the inner compare using a recomputed value (like a1 cast or masked differently) rather than reusing t directly, so CSE can't see they're equivalent and GCC leaves both comparisons in place rather than merging them. That could explain why the target ends up comparing against s0/v1 as separate registers instead of the same pseudo.

I should check the target assembly directly for the exact compare instructions being used there.
