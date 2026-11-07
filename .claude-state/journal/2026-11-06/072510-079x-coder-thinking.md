---
ts: 2026-11-06T14:25:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SLJQcl9n5DBbXEJDlWra
---
The only difference is the frame size: 32 vs 24. The code is otherwise identical (240 ins). The extra 8 bytes of frame = 2 extra words. Since the same 3 callee-saved regs (s0,s1,s2) are saved but at offsets 16,20,24 instead of 8,12,16, and sp is -32 instead of -24, there's an 8-byte local (the `pad[8]` is already accounted for in target's 24). So mine has an extra 8-byte local.

Wait, the target frame is 24 with s0,s1,s2 saved at 8,12,16, and the pad[8] at 0..8? So frame = 24 = 8 (pad) + 12 (3 regs) + 4 (?) hmm. Target: frame 24, vars=8, regs=3. So 8 + 3*4 = 20, rounded to 24? Actually the .frame says vars=8, regs=3/0, so 8 + 12 = 20, rounded up to 24 (8-byte align). Yes.

Mine: frame 32 = vars 8 + regs 3 = 20 -> but 32? That means there's an extra 8 bytes of vars (16). So the while-loop form added an 8-byte local! Why? Maybe the `i` variable got a stack slot because it's live across the loop differently? Or the while loop form caused `i` to be spilled.

Hmm, "vars=8" in the target means only the pad[8] is a stack local. Mine has vars=16. So one more local (maybe i spilled to stack? or another temp).

Interesting — the while loop form spills something. Maybe the loop's top test requires an extra temp that spills.

OK, the do-while form is correct for the frame. So stick with do-while.

Let me go back to the priority problem. 

Let me reconsider the live_length route with a concrete experiment: dump a variant where i's live_length differs and see the effect. But b2 didn't change live_length.

Hmm, wait. Maybe the live_length for i is dominated by the fact that i is live across the loop back edge, so its live_length includes the ENTIRE loop body plus the setup. Moving i=0 by 2 insns should reduce it by 2. Unless flow's backward scan counts i as live from the block start (block 14) because of the back edge, and the setup block (13) is separate.

i's live_length = (insns in block 13 from i=0 to end) + (insns in block 14 where live) + (insns in block 17 where live). If i=0 moves later within block 13, the first term shrinks. b2 moved i=0 after src/dst, so it should shrink by 2. But it didn't. 

Unless expand puts i=0 at the same place. Let me verify by looking at the pre-flow RTL. Let me use the .jump dump (after jump_optimize, before cse/flow). Hmm, but cse1/cse2 run before flow, so the .jump dump is closest to the flow input (after jump, before cse). Actually there's .cse (after cse1) and .cse2 (after cse2). The .cse2 dump is closest to the flow input. Let me look at b2's .cse2 dump for the setup block.

Actually, the flow input is after cse2. Let me grep the .cse2 dump for reg 160/162 sets.

Wait, I dumped c1 and b2. Let me check b2's .cse2 (or .cse) for the insn order. But the dumps are huge. Let me grep for "(set (reg/v:SI 160)" and "(set (reg/v:SI 161)" and "(set (reg/v:SI 162)".
