---
ts: 2026-10-17T17:11:08.921Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm tracing how pseudo 72, which holds arg0, needs to survive the call to LoaderResetReadState before being used to compute sector, meaning it must get a callee-saved register since it isn't part of the global allocation list.

In the target code, s2 holds arg0 and then gets incremented to produce sector, so I'm checking whether sector's addition happens before or after the call — if before, arg0 itself would need to cross the call rather than sector, which changes which register local-alloc should prefer.

I'm also wondering whether calls actually end basic blocks for local-alloc purposes in gcc 2.7; if they don't, then both pseudos live within a single block, and local-alloc's register ordering plus the copy-preference heuristic from the increment instruction would determine whether s0 or s2 gets chosen first.

Maybe arg0 itself is the sector variable rather than a separate pseudo, making it a global allocation. If q/r take s0/s1 first due to conflicts, sector could then end up getting s2 — that matches the target, so I want to try replacing sector with arg0 directly.
