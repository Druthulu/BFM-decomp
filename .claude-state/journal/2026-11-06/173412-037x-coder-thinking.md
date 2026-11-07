---
ts: 2026-11-07T00:34:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_F0003TciGJr6fCJql7My
---
C0535: "The block boundary splits cse1's extended basic block, so the copies are not merged/re-ordered there". So the do-while(0) does split cse1's EBB (probably because the loop note causes cse_basic_block to end the block). And it costs 0 bytes in that case.

But in w2 it added 2 insns (69). Perhaps because the do-while around a store created a loop note that loop.c then handled, adding a jump? Hmm, 69 vs 68.

Let me reconsider: maybe I should wrap the *first use statement* (the big assignment) in a do-while? Or wrap both statements?

Actually, if the do-while splits the cse block, the memory table is flushed at the block boundary, so the second use reloads the pointer. But it costs instructions in my test. Let me see what w2 emitted. Let me look at the diff for w2.

Time: 17:53, 29 min elapsed. I'm past the 20-min mark. The rule: budget 20-30 min; past 30 min stop and record a wall, needing ≥30 tries. I have 4. Let me push hard for ~10 more minutes with a batch.

Let me first look at w2's diff quickly to see if the do-while is close.
