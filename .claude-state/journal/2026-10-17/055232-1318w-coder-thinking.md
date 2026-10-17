---
ts: 2026-10-17T11:52:32.443Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a54c7d32163ae0888
model: claude-opus-5-5[1m]
effort: medium
turnId: 06fcde63-5d28-4e8d-8c65-7414dbf4e61d
---
I'm noticing m and k both end up coalesced into a3, which means they didn't actually conflict since scheduling moved m's use before the lh instruction set k. But I see a discrepancy in ordering: the target places the address add after the lh at position 51-52, while mine differs in sequence.

Let me set this scheduling tangent aside and reconsider the register allocation question differently. The key idea is that k, having higher priority than j, gets allocated first — and if a lower-priority conflicting allocno has a full preference for a2, k would skip a2 during pass 0, provided a3 is already in regs_used_so_far. I need to check how regs_used_so_far is initialized in global_alloc, since the rule is you never allocate a register for the first time in pass 0 — I should look at where that set gets copied from.
