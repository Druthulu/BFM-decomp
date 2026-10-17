---
ts: 2026-10-17T12:31:43.372Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm noting that cse folds a memory address like (plus base k) into a constant symbol+offset, but when the address is just a bare register it keeps that reg form rather than substituting a constant—suggesting cse treats register-only addresses differently from computed ones in fold_rtx.

Now I'm tracing into find_best_addr to see whether it compares costs using COST (rtx_cost) versus ADDRESS_COST when deciding whether a folded address replacement is actually cheaper.
