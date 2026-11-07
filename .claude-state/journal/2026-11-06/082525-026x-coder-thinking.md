---
ts: 2026-11-06T15:25:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XoBx4oZa7DF2FaalW6Sl
---
Target tail: `move v0,s2` appears twice: at 2244 (delay slot of beqz s1,2294) and at 2290 (delay slot of jal at 2288? no, 2290 is the delay slot of the jal 2288? Actually jal at 2288 with delay slot 228c `move a2,zero`; 2290 move v0,s2 then 2294 beqz v0). So the local `fire` pseudo in $v0 gets a copy from $s2 (ret). reorg duplicates the copy into delay slots.

In C, `fire = ret; if (fire)`. Without the launder, gcc merges fire into ret and the branch tests $s2 directly.

Real-C idea for this one: make `ret` and `fire` not coalescible. The moves list has: func_8017E178's sibling cases? Let's search moves.md for "fire" or "re-tie".

Search moves.md for "re-tie" and "copy".
