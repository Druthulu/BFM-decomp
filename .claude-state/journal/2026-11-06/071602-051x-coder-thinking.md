---
ts: 2026-11-06T14:16:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tSREQXb7pXELt62zmzSF
---
Let me look at lines 440-475 to see how basic_block_loop_depth is computed. Maybe loop depth is the number of loops containing the block, and the do-while body has depth 2, but perhaps the outer `while` plus... Let me just check the .loop dump or compute.

Actually, let me just empirically determine the loop depths by looking at the .flow dump? Or simpler: I'll trust the observed deltas.

Observed: the i asm (in block 14) added 3 refs. So loop_depth(block 14) = 3. Hmm, that suggests the do-while body is at depth 3. Why? Maybe gcc counts the `if ((arg0->cmd & 0xFFFF) == 9)` as... no. Maybe the `while` loop and the `do` loop, plus a third loop from the outer structure? Wait, maybe there's an enclosing loop I'm missing. Let me check: the function `func_8013D53C` — is there an outer loop? No. But maybe the loop analysis counts the do-while as depth 2 and the while as depth 1, and the body block is inside both = depth 2. Hmm, 2 not 3.

Unless... the asm ref is counted twice (once as a use at 2501/2711 and once as...). Or the asm has both an input and something. Hmm.

Actually wait: the src asm at insn 312 is in block 13, which added 2 refs (15-13). So loop_depth(block13)=2? But block 13 is outside the do-while, inside the while. So while=2? That means the while loop is at depth 2, meaning there's an enclosing loop at depth 1!

Is there? Let me look at the function again... The while is inside `if (arg0 != 0) { if (D_801C62C0 != 0) {...} else { while (...) {...} } }`. No outer loop. Unless the whole function is inside a loop? No.

Hmm, maybe flow's loop_depth counting has quirks. Let me just check the .loop dump for this function to see the loop structure.

Actually, let me look at basic_block_loop_depth computation lines 440-475.
