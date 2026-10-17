---
ts: 2026-10-17T13:37:03.468Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
I realize the dumpbody only copies the .c file, compiling against the real source header, so the dump reflects the original RTL — confirming that in the original, the store used reg 72 which also mapped to s0, same as in the target where pseudo 72 and hard s0 coincide.

To fix header dumping, I should compile the kept directory's .c file directly, since its includes resolve relatively through inc/../shared paths. I'll run cc1_dumps_tu.sh on the kept .c in place with the proper DUMP_ROOT rather than copying just the .c elsewhere.
