---
ts: 2026-11-06T11:40:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_X3ndMWOVlwYQE7QIMzs5
---
04:40. Started 04:32 → only 8 min. Hmm, the WALL needs ≥20 min. I need to keep working on this item until 04:52 at least, OR interpret the 20 min as per-item and I should keep trying. But that seems wasteful. The rule: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

So a WALL record requires 20 min. I could keep trying more variants for 12 more minutes. Let me use that time productively: try genuinely different real-C structures that might create the dependency:

1. Pointer variables for the Blk8 copies (d/s pointers).
2. Union trick: `union { Blk8 b; s32 w[2]; }` — maybe the copy goes through s32 temps.
3. Copy via a temporary Blk8 variable.
4. Copy as two s32 through r2/r3 using unaligned struct member access.
5. Use `((Blk8*)&D_80126960)->...`.

Also, maybe there's a completely different structure: what if the original didn't have Blk8 copies at all, but 8 individual s16 assignments? No, target uses lwl/lwr.

Let me test a batch of ~10 structural variants. Let me write them.

Variant ideas:
v1: pointer vars:
```
Blk8 *s1 = (Blk8 *)&D_80120210;
Blk8 *d1 = &D_80126960;
...
*d1 = *s1;
```
But declaring pointer vars inside the body is fine (real C). Would produce lui/addiu for the pointers and BLKmode copy. Let's test.

v2: temp Blk8:
```
Blk8 t;
t = *(Blk8*)&D_80120210;
D_80126960 = t;
```
v3: copy through a union with s32:
```
union U { Blk8 b; s32 w[2]; } u;
u.b = *(Blk8*)&D_80120210;
D_80126960 = u.b;
```
v4: the Blk8 copies adjacent at the top.
v5: Blk8 copies at the end.
v6: use s16 temps for everything (r2..r5 as s16? no, they're s32).
v7: declare the temps as `s32` but load u16 with a cast to s32 then store as u16.
v8: use `u32` instead of `s32`.
v9: put the two Blk8 copies into a separate function? No.
v10: use array `Blk8 tmp[2]` and copy.

Let me also consider the possibility that the ORIGINAL used a struct type for the whole copy destination/source and did:
```
typedef struct { s32 a,b,c,d; Blk8 e; u16 f...; } S;
*(S*)&D_80126950 = *(S*)&D_80120200;  // would be one BLKmode copy — no
```

Let me try the variants.

Actually, a cleverer idea: the WAR edge comes from v0/v1 being reused. If I make the Blk8 copy's data registers naturally the same pseudo as r2/r3, I could write the copy as a 64-bit type: e.g., `*(long long*)&D_80126960 = *(long long*)&D_80120210;` — DImode move needs 2 registers, chosen by the compiler; not tied to r2/r3. But maybe with sched1, the DImode move's regs are pseudos → no edge. Same problem.

What if I use `s64` type... same.

OK let me just test the structural variants. 10-12 variants, then conclude WALL at ~04:52.

Let me write them as a script generating files v01..v12.
