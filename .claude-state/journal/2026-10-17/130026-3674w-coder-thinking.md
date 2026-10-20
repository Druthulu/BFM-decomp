---
ts: 2026-10-17T19:00:26.049Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm noticing sv gets recomputed after the function call but rot stays cached, likely because the pseudo for sv feeds into func_8012F14C's argument register directly through an address computation into a1, which then gets copied to a2.

So the real difference may be that sv's single-set pseudo is treated as equivalent to an invariant address and gets rematerialized by reload rather than allocated a register, while rot's pseudo is set in a different way — perhaps aliased through s0 for two separate stores — that keeps it from being flagged for the same rematerialization treatment.

I suspect reload treats a frame-pointer-plus-constant address as equivalent to a constant for this pseudo, which complicates whether global alloc assigns it s0 directly. Rather than keep chasing the register-allocation theory, I should just test empirically which variable (rot or mtx) actually ends up in s0 and how its store is generated.
