---
ts: 2026-11-07T00:10:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HxNwwcsK4YVo6EiJtNX8
---
The .greg printed no order line. Hmm. But the table shows the final hard regs (since they're assigned). Note: local-alloc assigned many (s0,s1,s4,s5).

Wait — the alloc_table shows r73=s1, r72=s0, r74=s4, r75=s0, r78=s5, r79=s1, r77=s2, r76=s3. These are the FINAL assignments (some from local-alloc).

Hmm, "16 pseudo(s)" and ".greg printed no order line" — so this function's allocnos were all handled by local-alloc? That means they're block-local. Interesting!

So this is a LOCAL-ALLOC assignment, not global! The alloc_table shows the hard regs directly.

The variables:
- r76 = s3, pri 714, refs 3, live 42, pointer → base = s3. ✓
- r77 = s2, refs 3, live 40 → white? (mine white=s2) 
- r78 = s5, refs 3, live 31 → y0 = s5
- r79 = s1, refs 3, live 31 → y1 = s1 (mine)
- r74 = s4, refs 3, live 29 → x1 = s4 (mine)
- r75 = s0, refs 3, live 29 → x0 = s0 (mine)

So local-alloc assigned in some order. The priorities: r74 1034 (live 29), r75 1034 (live 29) — TIE, lower allocno wins → r74 first? r74=s4, r75=s0. Hmm, that's odd: the tie-break "lower allocno wins" would give r74 the first free reg. But r74=s4 and r75=s0.

Hmm, these are local-alloc, which assigns per block in a different order. local-alloc.c: for blocks with exactly THREE quantities, allocated in birth order. Here block 0 has many quantities.

Let me think about local-alloc's algorithm: it processes pseudos in order of "qty" (number of references) and lifetime. The register assignment order in local-alloc is by `qty` (reg_qty from local-alloc's own numbering) — `local-alloc.c:1486-1507` "A block with exactly THREE quantities is allocated in BIRTH order".

Hmm. Since the pins forced x1=s0, x0=s1, white=s4, the natural local-alloc gives a different permutation.

This is the `lreg-*` wall family. Let me look at the walls list:
- lreg-index-conflict
- lreg-copy-pref-dying-base
- lreg-qty-priority
- lreg-v0-local-first
- lreg-callresult-copy-pref

The relevant one might be `lreg-qty-priority`.

Hmm. Let me think about how to change the local-alloc order lever-free. local-alloc assigns registers to pseudos in a block based on their "qty" — actually let me read local-alloc.c's main loop.

Actually, the practical lever: statement order / birth order changes which pseudo gets which reg. Let me try reordering the statements.

Current C:
```
y0 = a1 - 3;
x1 = a0 + 3;
[launder]
y1 = a1 + 3;
white = 0xFF;
x0 = a0 - 3;
line.tag = 0;
line.r = white;
line.g = 0;
line.b = 0;
line.x0 = x0;
line.y0 = y0;
line.x1 = x1;
line.y1 = y1;
GsSortLine(&line, &base[(u16)D_800B9A02 * 20], 0);
line.tag = 0;
...
```

Mine's regs: x0=s0, y1=s1, white=s2, base=s3, x1=s4, y0=s5.
Target: x1=s0, x0=s1, y1=s2, base=s3, white=s4, y0=s5.

Hmm, y0=s5 in both. base=s3 in both.

So we need: x1→s0 (mine s4), x0→s1 (mine s0), y1→s2 (mine s1), white→s4 (mine s2).

This looks like the variables are allocated in the order: (target) x1, x0, y1, base, white, y0 → s0,s1,s2,s3,s4,s5.
(mine) x0, y1, white, base, x1, y0 → s0,s1,s2,s3,s4,s5.

So the allocation ORDER differs: target's order is x1, x0, y1, base, white, y0; mine's is x0, y1, white, base, x1, y0.

Hmm, but base=s3 and y0=s5 in both, so base is 4th and y0 is 6th in both. The first three and the 5th differ: target x1,x0,y1,_,white; mine x0,y1,white,_,x1.

Interesting: mine's order is a rotation of the first three: x0, y1, white; target: x1, x0, y1.

So the target's allocation order is (x1, x0, y1, base, white, y0); mine is (x0, y1, white, base, x1, y0).

Hmm, mine's white is 3rd and x1 is 5th; target's white is 5th and x1 is 1st.

What determines the order? local-alloc processes the block's pseudos in some order. Let me look at local-alloc.c's allocation loop.

Actually, in local-alloc.c, `block_alloc` sorts the quantities by `qty_n_refs`/`qty_phys_reg`? Let me read the relevant part. The note said local-alloc.c:1486-1507 handles 3 quantities in birth order. For more quantities, it sorts.

Let me look at local-alloc.c around 1450-1550.
