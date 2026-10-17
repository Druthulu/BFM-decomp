---
ts: 2026-10-17T10:37:06.027Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'm tracing register allocation across the two code paths, checking how arg0 and spd get assigned differently between free and m1 depending on whether prev reuses a1, and confirming m1's tail allocation looks correct.

Now I'm puzzled why diff's conflict set changed in m1 even though block 2's source looks identical -- something about local register life ranges around the D load must differ between the two schedules. I want to compare the actual sched1 dumps for block 2 insn-by-insn, so I'm checking if there's already a tool to summarize RTL insns before writing one myself.
