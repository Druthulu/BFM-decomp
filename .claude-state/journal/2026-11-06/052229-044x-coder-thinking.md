---
ts: 2026-11-06T12:22:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IBEZwJcC88P8X1O3oiwX
---
Two effects:

1. Register swap t0 <-> a2 for `pb`/`pb2` (both are `(u16 *)&D_800B9A02`). The keepalive asm with 5 uses of pb boosted pb's priority so it got a2 (target) instead of t0.

2. A store order difference at 141-144: `sh v0,-8(a1)` — that's `q[-8] = 0x78;`? No: q[-8] is a byte store `sb`. `sh v0,-8(a1)` where a1 = q... `*(s16 *)(q - 0xC)`? no that's -0xC. -8 = q[-8] as s16? Hmm, in target: insert sh v0,-8(a1) at 141, and mine has it at 143. This is `q[-7] = 0x30`/`0x38` (byte) and `*(s16 *)(q - 10) = y` (sh at -10). -8 is `q[-8] = 0x78` (byte). Hmm, `sh v0,-8(a1)` is a halfword store to q-8. Not in the C... unless the compiler merges `q[-7]` and `q[-8]`? No.

Wait — maybe a1 isn't q. Let me look at more context. Actually the C has `*((u32 *)(q - 0x10)) = 0x64808080;` (word store at q-0x10) and `q[-8] = 0x78`. Hmm, `sh v0,-8(a1)`: maybe a1 = q - ... whatever.

Let me dump target 130-150 to see.

Actually, the barrier memory's job: prevent sched1 from moving stores around. Its removal changed the order of a store at 141-144.

Let me handle them separately: first the keepalive (the register swap t0/a2, 11 pairs) — that's the bulk.

The keepalive `"r"(pb) x5` gives pb 5 extra refs so it wins a2 over pb2 (both point to the same address; pb and pb2 are separate variables).

Real-C replacement: make pb have more real uses. Note pb is used at line 36-38 (`D_800AE7BC[*pb]`) and pb2 at 86-89. Since pb and pb2 have the same value, an obvious real-C move: use ONE variable (pb) for both (drop pb2, use pb). Then pb has more refs naturally and there's one fewer pseudo. Let's try that: replace `pb2` uses with `pb` and delete the pb2 declaration.

That's a clean real-C move. Let me test: v1 = v0 with pb2 removed (use pb).

Careful: target has both loads? Target: `lhu a0,0(a2)` at 59 and `lhu v1,0(a2)` at 73 — two separate loads from the same address. If I use pb everywhere, cse might merge... no, separate blocks.

Let's try. Also the 5x keepalive on pb was about ref count; using pb in pb2's place gives it exactly those extra refs (5 uses: `D_800AE7BC[*pb2]` x2 + op = D_800AE7BC[*pb].ot... that's 3 uses of pb in that region vs 5 asm operands). Let's measure.

Then the barrier: `__asm__("" ::: "memory")` at line 78 between `*(s16 *)(q - 10) = y;` and `*((u32 *)ot) = 0x4000000;`. Real-C replacement: hmm, a memory barrier prevents store reordering. Alternatives: reorder statements in C so that the target order comes out naturally, or make the stores depend on each other.

Let me do the keepalive first.
