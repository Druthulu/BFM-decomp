---
ts: 2026-11-06T05:24:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cscr1JEYM5e3K3zcP0om
---
Target:
```
2a4c lh a0,16(v1)      iVar2 -> a0
2a54 beqz a0, 2aa4
2a58 move v0,a0        tmp = iVar2 (delay slot)
2a5c bgez a0, 2a80
2a60 nop
2a64 addiu v0,v0,128   tmp += 0x80
2a68 sh v0,16(v1)
2a6c sll v0,v0,0x10
2a70 blez v0, 2aa0
...
2a80 addiu v0,v0,-128  tmp -= 0x80
2a84 sh v0,16(v1)
2a88 sll v0,v0,0x10
2a8c bgez v0, 2aa0
2a94 lw v0,32(s0)
2a9c sh zero,16(v0)
2aa0 lw v1,32(s0)
2aa4 lh a0,18(v1)
```

So iVar2 = a0, tmp = v0, and v1 = iVar1 (the pinned pointer). Note v1 is the pin; lever-free, iVar1 is in v1? In mine the diff showed `lh v0,16(v1)` — so v1 holds iVar1 already in mine too! Good, the pin may be unnecessary (the diff only shows v0->a0 x6).

So we only need iVar2 in a0 and tmp in v0, with the copy.

Interesting: a0 is a caller-saved register; iVar2 lives across the arms. Since there are no calls inside, a0 is fine.

In mine, iVar2 and tmp merged into v0 (no copy). So: keep the copy.

How? The launder re-set tmp. Lever-free ideas:
1. HImode copy: a1 scored 18 (worse). Let me look at a1's diff.
2. A real 2nd set of tmp.
3. do-while.

a3/a4 (do-while) stayed 8 — the copy still merged.

Hmm. Why did a1 get worse? Let me check a1's diff.
