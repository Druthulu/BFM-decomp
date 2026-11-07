---
ts: 2026-11-06T09:04:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a4PETL4EgGjL6ha9UM4g
---
Now write notes.md for items 1 and 3 (item 2's is done). Then the log.

Item 1 notes: 
- orig from src, baseline 0.
- strip both keepalives → score 9 (REG-caller, same 47 insns).
- each keepalive alone: off-kept 7, t3-kept 2 (so t3's liveness is the main one).
- dumps: local-alloc pri: r72 a0-copy 5 refs/27 → 3703; t3 2/5 → 4000; allocation ascending v0,v1,a0,a1,a2,a3; t3 gets a2, copy a3. Keepalive extends t3 to 3/18 → 1666 → copy a2, t3 a3. Off keepalive extends the addr temp r84 past the t4 load → t4 v1.
- real-C attempts: store-late (d3: store after h[1] → correct a2/a3 but the store emits at 34 not 21, t4 v0, best 4); load/store permutations (44) lose the load-delay nop (46 insns); direct fifth assignment, temp reuse, off reordering.
- wall lreg-qty-priority, best 4, 58 tries.

Item 3 notes:
- strip keepalive → 41, 121 insns (one lost), whole caller file shifts down (a1..t4 vs a2..t5).
- pal pinned $5; the keepalive keeps it live past the inner loop → a1 reserved through the loop.
- real-C: pal[i] (v1 18, address recomputed per iteration), dst=pal inside the guard (dp1 19: copy coalesced, loop uses a1), src=pal-n (34), dead dst=pal deleted by cse, while-loop (44), widths (22 variants, best 38).
- wall lreg-hardreg-live-end, best 19, 30 tries.

Then the log phase-ends/current/logs/T11.cG25.md.

Let me write the notes files.
