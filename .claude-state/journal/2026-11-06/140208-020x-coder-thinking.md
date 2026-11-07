---
ts: 2026-11-06T21:02:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_z5O6sDKNOjcwsFgZ2G84
---
Priority = floor_log2(n_refs) * n_refs * size / live_length. So priority is *inversely* proportional to live_length! Shorter live → higher priority.

off: live from sll to the addu in condition. e: live from lui/addiu to the addu. e is defined later and used at the same place → e has shorter live_length → higher priority → gets a0. But mine gives off a0... hmm.

Wait, maybe in mine the live lengths differ. Let me get the actual qty data. I could compile with -dl? Hmm, difficult. But let me use a cc1 dump. The helpers: tools/cc1_dumps_tu.sh and hdump.sh. Let me check what info they give.

Actually, let me reconsider: maybe off and e aren't the pseudos competing. The `a0` in mine might be a different pseudo. Let me get the full disassembly of mine and target to compare. dt.sh gives diff. Let me build the candidate object and disassemble. How does delever_search work? It builds into .run/P36/engine/score/<dir>/p<N>/. Let me check if the object is kept. Actually I can use hdump.sh / cc1 dumps.

Let me look at the tools available.
