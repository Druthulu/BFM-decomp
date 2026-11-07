---
ts: 2026-11-06T09:07:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r32114t5UKjjXMcISi63
---
Baseline scores 0 with levers. Lever-free: score? The tail shows differences. Key: target has s2 = t? Let's see: target at [14] li s2,37 (t=0x25=37), mine li s3,37. Target keeps a0 in s2? Actually target [37] move s2,s0 = rv=found? Hmm.

Interesting: target uses s2 for t and s3 for a0? mine uses s3 for t and s4 for a0. So the pin of rv to $2 forces an extra allocation? Wait, no: target has s2 = t. With the pin, $2 rv... In the pinned version, `rv` is hard reg $2 and `found` maybe in s2? Hmm.

Look at the diff: mine is one reg "shifted" - mine li s3,37 vs target li s2,37; mine move s3,v1 vs target move s4,v1. So mine allocates one extra callee-saved (s4) because the pinned rv's hard reg $2... hmm actually pin means rv is a fixed $2 pseudo so no callee-save needed for it; without the pin, `rv = found` maybe got a callee-saved reg (s2) and everything shifts.

Wait — in the pinned version, rv is $2, so found gets s2, t gets s3, a0 gets s4? In the unpinned version, the dead `rv = found` might still allocate... Actually since `rv = found` is dead, it should be deleted. Then found gets s2, t gets s3... hmm mine has t in s3, a0 in s4, found presumably s2. Target: t in s2, a0 in s3, found/rv in ... target [37] move s2,s0? Wait that's in epilogue-ish region; maybe move s2,s0 is `rv = found` where found is s0? Hmm.

Let's get the full diff and target/mine dumps to understand. The dt.sh prints diff tail. Let me get more lines with tail 60 and also look at actual register assignment. Maybe better to use delever_search --explain? That reads residual.

Let me get the full diff.
