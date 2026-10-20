---
ts: 2026-10-17T18:34:30.411Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac81395c556dc97c0
model: claude-opus-5-5[1m]
effort: medium
turnId: 2749fb46-32ea-40ac-942d-d9e5fb5596d6
---
I'm recalling that CSE got eliminated because it directly folded the memory set into instruction 75, making the earlier copy at 78 dead code — this matches the classic cse.c behavior where a register-to-register copy gets rewritten into its source instruction when that source was set immediately prior and dies there.

So I need something placed between the load and copy to block that swap, similar to how the func_8003388C move inserts a store between the tmp9 set and the lvl copy. I'm testing candidates like having a pointer computed from t get stored before the copy happens, but the instruction ordering and register usage (t vs s1, v0 vs a1) still don't line up with the target, so I keep searching for a filler statement that naturally belongs in the sequence without extra cost.

For the second block, having the store write directly before the copy actually matches the target's load/addiu/store/copy pattern. For the first block though, I can't easily insert the preceding call without forcing t to become callee-saved across it, so I think I need to check the exact condition in cse.c that triggers this copy-swap behavior.
