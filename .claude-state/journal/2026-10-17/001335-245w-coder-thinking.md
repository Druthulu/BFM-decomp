---
ts: 2026-10-17T06:13:35.035Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
I'm not sure the pin variant actually compiles identically outside its own translation unit, since context differences could matter. I want to test this by taking the SC01_000 variant, renaming its data references to match SC07_006, and checking whether the required types actually exist in that TU.

If it works across all eight copies, I could run `--all-defs --map-data` once for all 131 and also incidentally clear the fake $3 pin regression that was reintroduced — which is actually aligned with the phase's goal of removing fake levers, even if it's a side effect worth reporting rather than scope creep. I still need to verify whether the Thing type is actually defined in the SC07_006 translation unit before committing to this approach.
