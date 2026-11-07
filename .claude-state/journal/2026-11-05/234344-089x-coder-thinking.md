---
ts: 2026-11-06T06:43:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9vKLeiKzamu8Aj3TbO60
---
Item 4's lever-free body scores 54, 162 insns. The main difference: the v0/v1 swap and the ordering of the byte stores.

Look at the target: 
```
49 subu v0,v0,s0
50 move a0,v0
51 sll v0,v0,0x10
52 bgez v0,...
...
54 move a0,zero    (var_a0 = 0)
...
58 move v0,s8
59 move v1,s7
60 sb v0,52(sp)
61 sb v0,48(sp)
62 move v0,a0
63 sb v0,61(sp)
```
Mine:
```
49 subu v1,v0,s0
50 move v0,v1
51 sll v1,v1,0x10
52 bgez v1,...
53 move v1,s8
54 move v0,zero
55 sb v1,52(sp)
56 sb v1,48(sp)
...
```

So in the target, `var_a0 = 0x20 - var_s0` result goes to a0 ($4) and later `var_v0 = var_a0` → move v0,a0. Mine keeps it in v0/v1.

The pins were $3 (var_t7), $20 (k50), $18 (kF0), $19 (k100). Removing them changes things.

Hmm, the target: var_a0 in $4 (a0) — a caller-saved reg. Mine: var_a0 in v1? Hmm, mine at 50: `move v0,v1` — so var_a0 = v1? Then `move v1,s8` etc.

This looks like the classic local-alloc ordering issue.

Let me look at the whole diff, then try variants. Time: 23:45 start; I have until ~00:15.

Let me get the full diff.
