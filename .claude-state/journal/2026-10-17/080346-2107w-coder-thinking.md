---
ts: 2026-10-17T14:03:46.151Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a715c83225823a44a
model: claude-opus-5-5[1m]
effort: medium
turnId: cb00494e-7b3a-4f28-b3fa-24b3d50bb0ef
---
I notice the a0←s0 move before the calls to func_8012C218 and func_8012CBF4 gets elided in mine, likely because a0 and s0 are already known to hold the same value at that point, so the register allocator skips the redundant copy before the jal.

Maybe cse doesn't recognize $4 equals s0 because s0 is set through an intermediate arg0 pseudo rather than directly, so the chain of equivalences should still hold — but something about how cse follows jumps along only one path might explain why the original lost the equivalence while the target retained it. I'm wondering if cse_end_of_basic_block only follows a jump target when it has a single use, which could determine whether the taken branch's equivalences carry forward correctly.

To break the equivalence, I need L425 to have more than one use — perhaps two separate branches jumping to the same label, or some intervening instruction like an asm clobber that kills the equivalence before reaching the call.

Actually, cse's path-following behavior depends on whether the jump target label has a single use — if LABEL_NUSES(L425) is exactly 1, cse follows the taken branch directly and carries equivalences through, which would explain why the move was eliminated in my version. In the original, if that label had multiple uses, cse would treat it as a separate block with no inherited equivalences, so the register move would survive.

I'm now thinking I need to engineer a second use of L425 that disappears before the final output but still exists when cse runs — something like a jump that jump1's early pass can't eliminate (since it only does simple constant folding) but that cse itself later recognizes as foldable once it has more information, such as a comparison between two expressions that are only provably equal after cse's analysis.

So the ordering matters: the fake jump needs to come after the bnez in instruction stream so it's processed later by cse, decrementing LABEL_NUSES on L425 from 2 down to 1 once folded and deleted, while the fallthrough block continues to a fresh cse block starting at L425.

I'm now considering whether `if (0)` would just get folded away at the tree level before even reaching RTL, which would defeat the purpose — I'd need a genuine variable holding 0 at that point so cse (not the frontend) does the folding. Trying to restructure the control flow naturally so the label legitimately has two uses, but it's hard to justify semantically with plain C, so I'm looking for another mechanism to kill the equivalence.

I'm checking whether changing how the argument gets copied into the local variable — different types, pointer casts, adding zero — would avoid being treated as a trivial register copy by cse, but each variant seems to fold back to the same thing. I'm also considering comparing the pin16 vs pin removed variants to see which one produces the single diff I actually want.

Now I'm trying restructuring the source with the branch polarity flipped — putting the "second part" inside the `if (x < 16)` block and the C218 call in the else — to see if that changes which label the branch targets and matches the expected RTL output.

Testing a goto-based trick with a dummy zero variable to fake a second jump to the same label, hoping GCC's RTL expansion wouldn't fold away the dead compare.

The equivalence loss likely stems from the label having multiple uses, which kept cse's follow-jumps from taking that path. I'll test this by adding a second jump to that label that survives jump1 but gets folded away by cse.
