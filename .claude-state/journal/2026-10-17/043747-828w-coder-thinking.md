---
ts: 2026-10-17T10:37:47.610Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
I'm tracing through m1's sched1 ordering, checking how the abs and store instructions interleave with the loads, and verifying the live ranges for register values v0 and v1 across these reordered instructions in block 2.

Now I'm digging into why insn 61 gets scheduled before insn 48 in m1 versus free — it seems to stem from the diff pseudo now having two sets instead of one, which changes the birthing-priority boost in the scheduler and causes 61 to precede 48, overlapping the D-load register with v1 and creating a conflict with a1. So I'm considering alternate global variables to carry d instead of diff — maybe reusing `a` (already with two sets) or spd — to avoid disturbing the set count that triggers this reordering.

Checking spd: it's used right after as a constant and then for the abs result, so substituting it for d seems viable if spd isn't needed afterward, but swapping in `a` fails since a global pseudo can only occupy one hard register and would collide with d's own register. I conclude diff really is the only pseudo whose reuse keeps things consistent, since the arm-result temp isn't an actual source variable I can repurpose.

Now I'm keeping d=diff but trying to fix block 2's scheduling, since giving diff extra sets likely shifted instruction priorities — I want to see if I can respell block 2 so the scheduler still orders instruction 48 before 61, which means digging into the scheduler's priority dump for that block.
