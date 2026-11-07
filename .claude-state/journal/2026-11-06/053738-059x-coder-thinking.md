---
ts: 2026-11-06T12:37:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mXBqDMNsXUsjPmMlVtLG
---
The greg dump prints the RTL after allocation (registers renamed), so pseudo numbers appear only in the header. I need the pre-allocation RTL. The `.lreg` dump is post-local-alloc, pre-global — it shows pseudos with REG_N_REFS and (insn ...) references. Let me look at the lreg dump for our function, find the pseudo that is `ret`.

Actually, better: use `-dg`'s conflict list. `73 conflicts: 72 73 2 3 29` — 73 conflicts with v0 (2) and v1 (3). Which pseudo is 73? The `Register dispositions` line: 73 in 4 (a0). And the arms' `li a0,7` — so 73 = ret.

So ret conflicts with v0. The conflict means at some instruction, ret is live while v0 is live.

In the target, ret is v0 and doesn't conflict with anything except where v0 is live... well, a hard reg can't conflict with itself.

So: what makes ret live where v0 is live? Let's look at the lreg dump for pseudo 73's live range. Let me search the lreg dump.

Actually, maybe the cleanest: the target's ret in v0 means in the target's C the allocator decided differently — likely because ret's live range is SHORT and v0 is dead at those points. In c2, ret is live across the `li v0,N` comparison constant — because the C's if-chain has ret live from the arm's assignment through to the STORE... but there's a goto.

Hmm, one candidate cause: the LAST arm (0x2D) — after its block, execution falls to `i70a = ...` etc. Wait no, that arm does `ret = 0x1D; goto STORE;`.

Another cause: ret's live range in the *first* region: `return ret` at line 55/60 was removed in c2.

Let me grep the lreg dump around the STORE for pseudo 73.
