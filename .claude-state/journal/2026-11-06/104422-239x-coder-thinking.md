---
ts: 2026-11-06T17:44:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_t8pTdwCovGSVGfSW2z0X
---
Time 18.7 min. Still 5.

Let me try 2-3 more then record at 20.

Hmm, actually let me reconsider the sra/srl order. In the target:
```
sra v1,v0,16
srl v0,v0,31
```
The sra is first. In mine (lo-first):
```
srl v1,v0,31
sra v0,v0,16
```
So sched1 scheduled them in source order.

What if I make the sra's *source* a different pseudo so it's scheduled first? Both use sh16.

What if I compute hi first into a named variable but keep lo's declaration first (r1) → 7.

What if I compute hi first inline in a separate statement: `p[0x79] = (u16)(((sh16 >> 16) + lo) >> 1);` with lo computed *after* via a comma? no.

What if the lo computation is moved into a *different basic block* after the hi shift? There's no branch there.

OK — one more idea: maybe the *order* difference doesn't matter if the two insns are identical in the mask? No, sra vs srl differ.

Let me accept the wall. Time 18.7; I need ~1.3 min. Let me run one more small batch (2 variants) and then a final verification, crossing 20.

Variants: 
w1: `lo = (s32)((u32)sh16 >> 31); hi = sh16 >> 16; p[0x79] = (u16)((hi + lo) >> 1);` (u3, 5)
w2: do-while around the whole block.

Let me run w2 and w3.
