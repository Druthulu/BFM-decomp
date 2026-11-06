---
ts: 2026-10-22T20:53:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sYcHO4eZ6DC2XwNUE8Pg
---
Target corner-1 block order:
```
1520 addiu s4,s2,-93      (by = bx - 0x5D)
1524 addiu s0,s1,123      (ax = ay + 0x7B)
1528 addiu s2,s2,-87      (bx = bx - 0x57)
... (index computation, GsSortLine args)
153c addiu s1,s1,117      (ay += 0x75)
1540 sh s1,36(sp)  (prim.x0 = ay)
1544 sh s4,38(sp)  (prim.y0 = by)
1548 sh s0,40(sp)  (prim.x1 = ax)
1550 sh s2,42(sp)  (prim.y1 = bx)  [delay slot]
```

So the target order: by, ax, bx, then the index chain, then ay, then the 4 stores.

Mine (gen_o3): by at 73 (one later), ay at 75 (earlier). So mine: ... by, ax, ay?, bx? Let me see the candidate's disassembly around there.

The source order (orig.c):
```
bx = out.vy;
ay = out.vx;
by = bx - 0x5D;
ax = ay + 0x7B;
bx = bx - 0x57;
{ op launder }
ay = ay + 0x75;
prim.x0 = ay; prim.y0 = by; prim.x1 = ax; prim.y1 = bx;
aGsSortLine(&prim, op, 0);
```
The target has the op/index computation between bx's add and ay's add. In the source, the `op` launder is between bx = bx-0x57 and ay += 0x75. Removing the launder moves the index computation (op) elsewhere (cse folds op into the call args).

The prior coder's gen_o3: u16 ay/bx and no `by = (u16)by`. Score 4 ORDER: mine's by addiu is one slot late and ay's is 4 slots early.

Let me see gen_o3's disassembly around the block.
