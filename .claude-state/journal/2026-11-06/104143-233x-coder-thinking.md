---
ts: 2026-11-06T17:41:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jrGMqJvJMWjI3Xo95Gvi
---
p2 changed the order: now sh16=v0 (matching the sll!), and the temp order is srl first then sra — the target has sra first. So p2 got sh16=v0! 

The residual: mine[171-175] has srl v1,v0,31; sra v0,v0,16; addu v0,v0,v1; sra v0,v0,1; sh v0. Target: sra v1,v0,16; srl v0,v0,31; addu v1,v1,v0; sra v1,v1,1; sh v1.

So the *order* of the two shifts is swapped (srl before sra) and the result regs differ (v0 vs v1).

p2 source:
```
s32 lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)(((sh16 >> 16) + lo) >> 1);
```
The lo computation comes first in the source → srl first.

The target's order is sra (>>16) then srl (>>31). So the source order should be hi first. p1 had hi first but got 7.

Interesting: p2 made sh16=v0! Why? Because the first temp (lo) got... hmm, the named temp `lo` is a variable declared at the block start; its birth is at the block entry (expand_decl) — so its pseudo is created early, changing the allocation. And the srl got v1 while sh16 got v0.

So with p2's structure, sh16=v0 (target!) but the shift order is wrong.

Let me try a variant with hi computed first but *declared* early:
```
s32 hi;
s32 lo;
lo = (s32)((u32)sh16 >> 31);   // hmm
```
Actually, the target's order is sra then srl. Let me try:
```
s32 hi;
s32 lo;
hi = sh16 >> 16;
lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)((hi + lo) >> 1);
```
p1 was `{ s32 hi = sh16>>16; s32 lo = ...; ...}` (declarations with initializers inside the block) → 7.

The difference between p1 and p2: p2 declares `lo` with an initializer and uses `(sh16 >> 16)` inline. p1 declares both with initializers.

p2 got sh16=v0 — the key! Maybe because the *first temp* is lo (srl), which prefers v1? Hmm.

Let me try variants that keep sh16=v0 and get the sra first:
q1:
```
s32 lo;
lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)(((sh16 >> 16) + lo) >> 1);
```
(same as p2 but declaration separate — p3-like).

q2:
```
s32 hi;
hi = sh16 >> 16;
s32 lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)((hi + lo) >> 1);
```
(mixed declaration styles — C89 requires declarations first, but gcc allows? Declaring mid-block is C99; gcc 2.7.2 may reject. Use declarations at the top.)

q3: declare both at the top of the enclosing block:
```
s32 hi, lo;
...
hi = sh16 >> 16;
lo = (s32)((u32)sh16 >> 31);
p[0x79] = (u16)((hi + lo) >> 1);
```

The order of the *statements* determines the instruction order (sched1 may reorder, but these are dependent on sh16).

The target: sra then srl. So the source should compute hi (>>16) first.

Let me try q3 and see if sh16 stays v0.

Also, maybe the reason p2 got sh16=v0 is the *named lo* temp changing the local-alloc priorities. Let me test q3 and variants.
