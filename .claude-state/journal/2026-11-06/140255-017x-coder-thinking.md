---
ts: 2026-11-06T21:02:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gwEd4Gmof9RTXKSFN2Fy
---
The --keep scratch goes to .run/P36/engine/score/... which is not under my shard. The brief says scratch under my shard; but the tool writes there by default. Hmm, the brief says "`--keep` scratch is removed after use". It writes under .run/P36 — that's the shared engine. I shouldn't leave it. Let me not use --keep; instead build my own dump TU.

Let me instead create a small TU in the item dir. I need Unkstruct_80126948 definition. Let me grep it.

Actually, better approach: run cc1 dumps on the full real TU with my body spliced. But splicing means editing the 132k file. The delever tool does that. Hmm.

Alternative: use the object and objdump. The --keep cand.o could be disassembled; but the pass dump is what I need (combine vs local-alloc). Let me use the "engine" scratch but delete after.

Actually, a cleaner route: create a minimal TU in my item dir:
```
typedef ... Unkstruct_80126948 ...
extern ...
<w1 body>
```
Then run tools/cc1_dumps_tu.sh on it. But the struct definition needs to match. Let me grep.

Hmm, but the score is computed against the full TU. A minimal TU might allocate differently (different global layout doesn't matter much for this fn; the fn only uses globals and the struct). Should be fine for pass inspection.

Let me grep Unkstruct_80126948 definition.
