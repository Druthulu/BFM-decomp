---
ts: 2026-10-17T11:01:47.100Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5faba3cdb29155cb
model: claude-opus-5-5[1m]
turnId: e4e5bc1c-68a3-4a95-bce5-27c78dfaef1c
---
The function has to match the target without any levers. The residual is one extra `lui a0 / lhu a0,0(a0)` at the very top, which looks like a global halfword being loaded early (the compiler hoists or duplicates a load of a global short). I'll first find out which source expression causes that load, then try respellings that let the compiler reuse or reschedule it. Lane 1, the permuter, goes first.
