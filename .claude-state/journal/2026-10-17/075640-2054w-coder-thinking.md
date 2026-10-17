---
ts: 2026-10-17T13:56:40.981Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I'm comparing the sibling function's union-stack-packing approach against our target's bitwise andi/sll/or packing, trying to figure out if the frame size difference (padding for dead locals) reflects a different union layout rather than stack usage.

It clicks — GCC 2.7 can keep a 4-byte union register-resident when its address isn't taken, producing bit-insertion instructions instead of stack stores, which explains the andi/sll/or pattern. I map out the comparison logic (cx vs bx, ax vs cx, cy vs ay, cy vs by) and decide to rewrite the function using a register-packed union with the final result returned as a sign check on the nested function call, trying variants with and without a do-while(0) wrapper and extra padding.

I see that the sibling function `func_8017EFF4` uses register-resident unions for the same NCLIP wrapper, which gcc 2.7 compiles into the exact andi/sll/or packing seen in our target. I'll rewrite S13 using that same pattern.
